#pragma once
#include <map>

namespace DuiLib
{
typedef DWORD color_t;
class CWaterfallList;
class CWaterfallListCell;

class DUILIB_API CWaterfallListDataSource
{
public:
	virtual ~CWaterfallListDataSource(){};

	virtual int NumberOfIndex(CWaterfallList *listView) = 0;

	virtual int ListViewHeightForIndex(CWaterfallList *listView, int index) = 0;

	virtual CWaterfallListCell* ListViewCellAtIndex(CWaterfallList *listView, const SIZE& cellSize, int index) = 0;

	virtual void ListViewWillDisplayCellAtIndex(CWaterfallList* table, CWaterfallListCell* cell, int index) {};
};

//动态加载控件，rcItem之外的控件动态释放掉
class DUILIB_API CWaterfallList:public CContainerUI
{
public:
	CWaterfallList(void);
	~CWaterfallList(void);

    LPCTSTR GetClass() const { return DUI_CTR_WATERFALLLIST; }
    LPVOID GetInterface(LPCTSTR pstrName);

//signal:
	virtual void SignalCellSelect(CWaterfallList* list,int index){}
	virtual void SignalCellDeselect(CWaterfallList* list,int index){}

	struct DUILIB_API ListInfo{
		ListInfo()
			:itemBkColor(0),itemHotColor(0),itemSelColor(0)
		{}
		color_t itemBkColor;
		color_t itemHotColor;
		color_t itemSelColor;

        TDrawInfo itemBkImage;
        TDrawInfo itemHotImage;
        TDrawInfo itemSelImage;
	};

	void SetDataSource(CWaterfallListDataSource* dataSrc){m_dataSource=dataSrc;}
	void SetPos(RECT rc, bool bNeedInvalidate = true) override;
    bool DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl) override;
	void SetScrollPos(SIZE szPos) override;
	void Reload();
	void SetSelect(int selIndex);
	int GetSelect(){return m_selectedItemIdx;}

	CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags)override;

	CWaterfallListCell* DequeueReusableCell(uint32_t identifier);

	ListInfo* GetListInfo(){return &m_listInfo;}
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue) override;
private:
	CWaterfallListCell* findDisplayCell(int id)
	{
		auto find=m_displayItems.find(id);
		if (find!=m_displayItems.end())
		{
			return find->second;
		}
		return NULL;
	}

	CWaterfallListDataSource* m_dataSource;
	CDuiPtrArray m_removedItems;//重用的控件
	std::map<int,CWaterfallListCell*> m_displayItems;//显示的控件
	int      m_selectedItemIdx;//选中的控件的索引
	int      m_itemHeight;
	ListInfo m_listInfo;
};



class DUILIB_API CWaterfallListCell : public CContainerUI
{
public:
	CWaterfallListCell();
	~CWaterfallListCell();

    LPCTSTR GetClass() const { return DUI_CTR_WATERFALLLIST_CELL; }
    LPVOID GetInterface(LPCTSTR pstrName);

	void SetReuseIdentifier(uint32_t identifier);
	uint32_t GetReuseIdentifier();

	void SetOwner(CWaterfallList*  owner);
	CWaterfallList* GetOwner();


	void SetIndex(int idx);
	int GetIndex();

	virtual void DoEvent(TEventUI& event);
    virtual void PaintStatusImage(HDC hDC);
private:
	CWaterfallList*  m_owner;
	int     m_index;
	uint32_t m_buttonState;
	uint32_t m_reuseIdentifier;
};

}//namespace


