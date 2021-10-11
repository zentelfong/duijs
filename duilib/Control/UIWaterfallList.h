#pragma once
#include <map>

namespace DuiLib
{
typedef DWORD color_t;
class CWaterfallListUI;
class CWaterfallListCellUI;

class UILIB_API CWaterfallListDataSource
{
public:
	virtual ~CWaterfallListDataSource(){};

	virtual int NumberOfIndex(CWaterfallListUI*listView) = 0;

	virtual int ListViewHeightForIndex(CWaterfallListUI*listView, int index) = 0;

	virtual CWaterfallListCellUI* ListViewCellAtIndex(CWaterfallListUI*listView, const SIZE& cellSize, int index) = 0;

	virtual void ListViewWillDisplayCellAtIndex(CWaterfallListUI* table, CWaterfallListCellUI* cell, int index) {};
};

//动态加载控件，rcItem之外的控件动态释放掉
class UILIB_API CWaterfallListUI:public CContainerUI
{
	DECLARE_DUICONTROL(CWaterfallListUI)
public:
	CWaterfallListUI(void);
	~CWaterfallListUI(void);

    LPCTSTR GetClass() const { return _T("WaterfallListUI"); }
    LPVOID GetInterface(LPCTSTR pstrName);

	void NotifyCellSelect(int index);
	void NotifyCellDeselect(int index);

	struct UILIB_API ListInfo{
		ListInfo()
			:itemBkColor(0),itemHotColor(0),itemSelColor(0)
		{}
		color_t itemBkColor;
		color_t itemHotColor;
		color_t itemSelColor;

        CDuiString itemBkImage;
		CDuiString itemHotImage;
		CDuiString itemSelImage;
	};

	void SetDataSource(CWaterfallListDataSource* dataSrc){m_dataSource=dataSrc;}
	void SetPos(RECT rc, bool bNeedInvalidate = true) override;
    bool DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl) override;
	void SetScrollPos(SIZE szPos, bool bMsg = true) override;
	void Reload();
	void SetSelect(int selIndex);
	int GetSelect(){return m_selectedItemIdx;}

	CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags)override;

	CWaterfallListCellUI* DequeueReusableCell(uint32_t identifier);

	ListInfo* GetListInfo(){return &m_listInfo;}
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue) override;
private:
	CWaterfallListCellUI* findDisplayCell(int id)
	{
		auto find=m_displayItems.find(id);
		if (find!=m_displayItems.end())
		{
			return find->second;
		}
		return NULL;
	}

	CWaterfallListDataSource* m_dataSource;
	CStdPtrArray m_removedItems;//重用的控件
	std::map<int, CWaterfallListCellUI*> m_displayItems;//显示的控件
	int      m_selectedItemIdx;//选中的控件的索引
	int      m_itemHeight;
	ListInfo m_listInfo;
};



class UILIB_API CWaterfallListCellUI : public CContainerUI
{
	DECLARE_DUICONTROL(CWaterfallListCellUI)
public:
	CWaterfallListCellUI();
	~CWaterfallListCellUI();

    LPCTSTR GetClass() const { return DUI_CTR_WATERFALLLIST_CELL; }
    LPVOID GetInterface(LPCTSTR pstrName);

	void SetReuseIdentifier(uint32_t identifier);
	uint32_t GetReuseIdentifier();

	void SetOwner(CWaterfallListUI*  owner);
	CWaterfallListUI* GetOwner();


	void SetIndex(int idx);
	int GetIndex();

	void DoEvent(TEventUI& event) override;
    void PaintStatusImage(HDC hDC) override;
private:
	CWaterfallListUI*  m_owner;
	int     m_index;
	uint32_t m_buttonState;
	uint32_t m_reuseIdentifier;
};

}//namespace


