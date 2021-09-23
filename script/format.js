
export const format = (function() {
    // Copyright Joyent, Inc. and other Node contributors.
    //
    // Permission is hereby granted, free of charge, to any person obtaining a
    // copy of this software and associated documentation files (the
    // "Software"), to deal in the Software without restriction, including
    // without limitation the rights to use, copy, modify, merge, publish,
    // distribute, sublicense, and/or sell copies of the Software, and to permit
    // persons to whom the Software is furnished to do so, subject to the
    // following conditions:
    //
    // The above copyright notice and this permission notice shall be included
    // in all copies or substantial portions of the Software.
    //
    // THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
    // OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    // MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
    // NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
    // DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
    // OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
    // USE OR OTHER DEALINGS IN THE SOFTWARE.
    //
    // https://github.com/joyent/node/blob/master/lib/util.js
  
    var formatRegExp = /%[sdj%]/g;
    function format(f) {
        if (!isString(f)) {
            var objects = [];
            for (var i = 0; i < arguments.length; i++) {
            objects.push(inspect(arguments[i], {}));
            }
            return objects.join(' ');
        }

        var i = 1;
        var args = arguments;
        var len = args.length;
        var str = String(f).replace(formatRegExp, function(x) {
            if (x === '%%') return '%';
            if (i >= len) return x;
            switch (x) {
            case '%s': return String(args[i++]);
            case '%d': return Number(args[i++]);
            case '%j':
                try {
                return JSON.stringify(args[i++]);
                } catch (_) {
                return '[Circular]';
                }
            default:
                return x;
            }
        });
        for (var x = args[i]; i < len; x = args[++i]) {
            if (isNull(x) || !isObject(x)) {
            str += ' ' + x;
            } else {
            str += ' ' + inspect(x, {});
            }
        }
        return str;
    }

    function inspect(obj, opts) {
      var ctx = {
        seen: [],
        stylize: stylizeNoColor,
      };
      return formatValue(ctx, obj, opts.depth);
    }
  
    function stylizeNoColor(str, styleType) {
      return str;
    }
  
    function arrayToHash(array) {
      var hash = {};
  
      array.forEach(function(val, idx) {
        hash[val] = true;
      });
  
      return hash;
    }
  
    function formatValue(ctx, value, recurseTimes) {  
      // Primitive types cannot have properties
      var primitive = formatPrimitive(ctx, value);
      if (primitive) {
        return primitive;
      }
  
      // Look up the keys of the object.
      var keys = Object.keys(value);
      var visibleKeys = arrayToHash(keys);
  
      // IE doesn't make error fields non-enumerable
      // http://msdn.microsoft.com/en-us/library/ie/dww52sbt(v=vs.94).aspx
      if (
        isError(value) &&
        (keys.indexOf('message') >= 0 || keys.indexOf('description') >= 0)
      ) {
        return formatError(value);
      }
  
      // Some type of object without properties can be shortcutted.
      if (keys.length === 0) {
        if (isFunction(value)) {
          var name = value.name ? ': ' + value.name : '';
          return ctx.stylize('[Function' + name + ']', 'special');
        }
        if (isRegExp(value)) {
          return ctx.stylize(RegExp.prototype.toString.call(value), 'regexp');
        }
        if (isDate(value)) {
          return ctx.stylize(Date.prototype.toString.call(value), 'date');
        }
        if (isError(value)) {
          return formatError(value);
        }
      }
  
      var base = '',
        array = false,
        braces = ['{', '}'];
  
      // Make Array say that they are Array
      if (isArray(value)) {
        array = true;
        braces = ['[', ']'];
      }
  
      // Make functions say that they are functions
      if (isFunction(value)) {
        var n = value.name ? ': ' + value.name : '';
        base = ' [Function' + n + ']';
      }
  
      // Make RegExps say that they are RegExps
      if (isRegExp(value)) {
        base = ' ' + RegExp.prototype.toString.call(value);
      }
  
      // Make dates with properties first say the date
      if (isDate(value)) {
        base = ' ' + Date.prototype.toUTCString.call(value);
      }
  
      // Make error with message first say the error
      if (isError(value)) {
        base = ' ' + formatError(value);
      }
  
      if (keys.length === 0 && (!array || value.length == 0)) {
        return braces[0] + base + braces[1];
      }
  
      if (recurseTimes < 0) {
        if (isRegExp(value)) {
          return ctx.stylize(RegExp.prototype.toString.call(value), 'regexp');
        } else {
          return ctx.stylize('[Object]', 'special');
        }
      }
  
      ctx.seen.push(value);
  
      var output;
      if (array) {
        output = formatArray(ctx, value, recurseTimes, visibleKeys, keys);
      } else {
        output = keys.map(function(key) {
          return formatProperty(
            ctx,
            value,
            recurseTimes,
            visibleKeys,
            key,
            array,
          );
        });
      }
  
      ctx.seen.pop();
  
      return reduceToSingleString(output, base, braces);
    }
  
    function formatPrimitive(ctx, value) {
      if (isUndefined(value)) return ctx.stylize('undefined', 'undefined');
      if (isString(value)) {
        var simple =
          "'" +
          JSON.stringify(value)
            .replace(/^"|"$/g, '')
            .replace(/'/g, "\\'")
            .replace(/\\"/g, '"') +
          "'";
        return ctx.stylize(simple, 'string');
      }
      if (isNumber(value)) {
        if (value == 0) {
          if (1 / value < 0)
            value = "-0";
          else
            value = "0";
        }
        return ctx.stylize('' + value, 'number');
      }
      if (isBoolean(value)) return ctx.stylize('' + value, 'boolean');
      // For some reason typeof null is "object", so special case here.
      if (isNull(value)) return ctx.stylize('null', 'null');
      if (isBigInt(value)) return ctx.stylize('' + value + 'n', 'bigint');
      if (isBigFloat(value)) return ctx.stylize('' + value + 'l', 'bigfloat');
    }
  
    function formatError(value) {
      return `${Error.prototype.toString.call(value)}\n${value.stack}`;
    }
  
    function formatArray(ctx, value, recurseTimes, visibleKeys, keys) {
      var output = [];
      for (var i = 0, l = value.length; i < l; ++i) {
        if (hasOwnProperty(value, String(i))) {
          output.push(
            formatProperty(
              ctx,
              value,
              recurseTimes,
              visibleKeys,
              String(i),
              true,
            ),
          );
        } else {
          output.push('');
        }
      }
      keys.forEach(function(key) {
        if (!key.match(/^\d+$/)) {
          output.push(
            formatProperty(ctx, value, recurseTimes, visibleKeys, key, true),
          );
        }
      });
      return output;
    }
  
    function formatProperty(ctx, value, recurseTimes, visibleKeys, key, array) {
      var name, str, desc;
      desc = Object.getOwnPropertyDescriptor(value, key) || {value: value[key]};
      if (desc.get) {
        if (desc.set) {
          str = ctx.stylize('[Getter/Setter]', 'special');
        } else {
          str = ctx.stylize('[Getter]', 'special');
        }
      } else {
        if (desc.set) {
          str = ctx.stylize('[Setter]', 'special');
        }
      }
      if (!hasOwnProperty(visibleKeys, key)) {
        name = '[' + key + ']';
      }
      if (!str) {
        if (ctx.seen.indexOf(desc.value) < 0) {
          if (isNull(recurseTimes)) {
            str = formatValue(ctx, desc.value, null);
          } else {
            str = formatValue(ctx, desc.value, recurseTimes - 1);
          }
          if (str.indexOf('\n') > -1) {
            if (array) {
              str = str
                .split('\n')
                .map(function(line) {
                  return '  ' + line;
                })
                .join('\n')
                .substr(2);
            } else {
              str =
                '\n' +
                str
                  .split('\n')
                  .map(function(line) {
                    return '   ' + line;
                  })
                  .join('\n');
            }
          }
        } else {
          str = ctx.stylize('[Circular]', 'special');
        }
      }
      if (isUndefined(name)) {
        if (array && key.match(/^\d+$/)) {
          return str;
        }
        name = JSON.stringify('' + key);
        if (name.match(/^"([a-zA-Z_][a-zA-Z_0-9]*)"$/)) {
          name = name.substr(1, name.length - 2);
          name = ctx.stylize(name, 'name');
        } else {
          name = name
            .replace(/'/g, "\\'")
            .replace(/\\"/g, '"')
            .replace(/(^"|"$)/g, "'");
          name = ctx.stylize(name, 'string');
        }
      }
  
      return name + ': ' + str;
    }
  
    function reduceToSingleString(output, base, braces) {
      var numLinesEst = 0;
      var length = output.reduce(function(prev, cur) {
        numLinesEst++;
        if (cur.indexOf('\n') >= 0) numLinesEst++;
        return prev + cur.replace(/\u001b\[\d\d?m/g, '').length + 1;
      }, 0);
  
      if (length > 60) {
        return (
          braces[0] +
          (base === '' ? '' : base + '\n ') +
          ' ' +
          output.join(',\n  ') +
          ' ' +
          braces[1]
        );
      }
  
      return braces[0] + base + ' ' + output.join(', ') + ' ' + braces[1];
    }
  
    // NOTE: These type checking functions intentionally don't use `instanceof`
    // because it is fragile and can be easily faked with `Object.create()`.
    function isArray(ar) {
      return Array.isArray(ar);
    }
  
    function isBigInt(arg) {
      return typeof arg === 'bigint';
    }

    function isBigFloat(arg) {
        return typeof arg === 'bigfloat';
    }

    function isBoolean(arg) {
      return typeof arg === 'boolean';
    }
  
    function isNull(arg) {
      return arg === null;
    }
  
    function isNullOrUndefined(arg) {
      return arg == null;
    }
  
    function isNumber(arg) {
      return typeof arg === 'number';
    }
  
    function isString(arg) {
      return typeof arg === 'string';
    }
  
    function isSymbol(arg) {
      return typeof arg === 'symbol';
    }
  
    function isUndefined(arg) {
      return arg === void 0;
    }
  
    function isRegExp(re) {
      return isObject(re) && objectToString(re) === '[object RegExp]';
    }
  
    function isObject(arg) {
      return typeof arg === 'object' && arg !== null;
    }
  
    function isDate(d) {
      return isObject(d) && objectToString(d) === '[object Date]';
    }
  
    function isError(e) {
      return (
        isObject(e) &&
        (objectToString(e) === '[object Error]' || e instanceof Error)
      );
    }
  
    function isFunction(arg) {
      return typeof arg === 'function';
    }
  
    function objectToString(o) {
      return Object.prototype.toString.call(o);
    }
  
    function hasOwnProperty(obj, prop) {
      return Object.prototype.hasOwnProperty.call(obj, prop);
    }
  
    return format;
  })();
