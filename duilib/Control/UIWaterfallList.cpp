#include "StdAfx.h"
#include "UIWaterfallList.h"

namespace DuiLib
{

CWaterfallList::CWaterfallList(void)
	:m_dataSource(NULL),m_selectedItemIdx(0),m_itemHeight(-1)
{
}


CWaterfallList::~CWaterfallList(void)
{
	for (int i=0;i<m_removedItems.GetSize();++i)
	{
		delete (CWaterfallListCell*)m_removedItems[i];
	}
}

LPVOID CWaterfallList::GetInterface(LPCTSTR pstrName)
{
    if (_tcscmp(pstrName, DUI_CTR_WATERFALLLIST) == 0) 
        return static_cast<CWaterfallList*>(this);
    return CContainerUI::GetInterface(pstrName);
}

void CWaterfallList::SetPos(RECT rc, bool bNeedInvalidate)
{
	CControlUI::SetPos(rc, bNeedInvalidate);
	rc = m_rcItem;
	if (!m_dataSource)
		return;

	// Adjust for inset
	rc.left += (m_rcInset.left);
	rc.top += (m_rcInset.top);
	rc.right -= (m_rcInset.right);
	rc.bottom -= (m_rcInset.bottom);
	if( m_pVerticalScrollBar && m_pVerticalScrollBar->IsVisible() ) rc.right -= (m_pVerticalScrollBar->GetFixedWidth());
	if( m_pHorizontalScrollBar && m_pHorizontalScrollBar->IsVisible() ) rc.bottom -= (m_pHorizontalScrollBar->GetFixedHeight());

	int itemNumber=m_dataSource->NumberOfIndex(this);
	if( itemNumber== 0) {
		ProcessScrollBar(rc, 0, 0);
		return;
	}

	// Determine the minimum size
	SIZE szAvailable = { rc.right - rc.left, rc.bottom - rc.top };
	if( m_pHorizontalScrollBar && m_pHorizontalScrollBar->IsVisible() ) 
		szAvailable.cx += m_pHorizontalScrollBar->GetScrollRange();

	int nAdjustables = 0;
	int cyFixed = 0;
	int nEstimateNum = 0;
	for(int it1 = 0; it1 < itemNumber; it1++ ) {
		int height=m_itemHeight>0 ?m_itemHeight:m_dataSource->ListViewHeightForIndex(this,it1);
		if( height == 0 ) {
			nAdjustables++;
		}
		cyFixed += height;
		nEstimateNum++;
	}
	cyFixed += (nEstimateNum - 1) * (m_iChildPadding);

	// Place elements
	int cyNeeded = 0;
	int cyExpand = 0;
	if( nAdjustables > 0 ) cyExpand = MAX(0, (szAvailable.cy - cyFixed) / nAdjustables);
	// Position the elements
	SIZE szRemaining = szAvailable;
	int iPosY = rc.top;
	if( m_pVerticalScrollBar && m_pVerticalScrollBar->IsVisible() ) {
		iPosY -= m_pVerticalScrollBar->GetScrollPos();
	}
	int iPosX = rc.left;
	if( m_pHorizontalScrollBar && m_pHorizontalScrollBar->IsVisible() ) {
		iPosX -= m_pHorizontalScrollBar->GetScrollPos();
	}

	for( int it2 = 0; it2 < itemNumber; it2++ )
	{
		SIZE sz;
		sz.cy =m_itemHeight>0 ?m_itemHeight:m_dataSource->ListViewHeightForIndex(this,it2);
		sz.cx = szRemaining.cx;
		RECT rcCtrl = { iPosX, iPosY, iPosX + sz.cx, iPosY + sz.cy };
		RECT rcTemp;
		if (IntersectRect(&rcTemp,&rcCtrl,&rc))
		{
			//如果控件在显示范围之内
			CWaterfallListCell* listCell=findDisplayCell(it2);
			if (!listCell)
			{
				listCell=m_dataSource->ListViewCellAtIndex(this,sz,it2);
				m_displayItems[it2]=listCell;
				listCell->SetOwner(this);
				listCell->SetManager(GetManager(),this,true);
				listCell->SetIndex(it2);
				m_dataSource->ListViewWillDisplayCellAtIndex(this,listCell,it2);
			}
			listCell->SetPos(rcCtrl, bNeedInvalidate);
		}
		else
		{
			//list列表之外的控件移除
			CWaterfallListCell* listCell=findDisplayCell(it2);
			if (listCell)
			{
                if (m_removedItems.GetSize() < 1000)
                    m_removedItems.Add(listCell);
                else
                    delete listCell;
				m_displayItems.erase(it2);
			}
		}

		iPosY += sz.cy + (m_iChildPadding);
		cyNeeded += sz.cy;
		szRemaining.cy -= sz.cy + (m_iChildPadding);
	}
	cyNeeded += (nEstimateNum - 1) * (m_iChildPadding);

	// Process the scrollbar
	ProcessScrollBar(rc, 0, cyNeeded);
}

bool CWaterfallList::DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl)
{
	RECT rcTemp = { 0 };
	if( !IntersectRect(&rcTemp, &rcPaint, &m_rcItem) ) 
        return true;

    CRenderClip clip;
    CRenderClip::GenerateClip(hDC, rcTemp, clip);

	CControlUI::DoPaint(hDC, rcPaint, pStopControl);
	if (!m_dataSource)
		return true;

	if( m_displayItems.size() > 0 ) 
	{
		RECT rc = m_rcItem;
		rc.left += (m_rcInset.left);
		rc.top += (m_rcInset.top);
		rc.right -= (m_rcInset.right);
		rc.bottom -= (m_rcInset.bottom);

		if( m_pVerticalScrollBar && m_pVerticalScrollBar->IsVisible() ) 
            rc.right -= (m_pVerticalScrollBar->GetFixedWidth());
		if( m_pHorizontalScrollBar && m_pHorizontalScrollBar->IsVisible() ) 
            rc.bottom -= (m_pHorizontalScrollBar->GetFixedHeight());


		if( IntersectRect(&rcTemp, &rcPaint, &rc) ){
			for (auto i=m_displayItems.begin();i!=m_displayItems.end();++i) {
				CWaterfallListCell* pControl = static_cast<CWaterfallListCell*>(i->second);
				if( !pControl->IsVisible() ) 
                    continue;
				if( !IntersectRect(&rcTemp, &rcPaint, &pControl->GetPos()) ) 
                    continue;
				pControl->DoPaint(hDC, rcTemp, pStopControl);
			}
		}
	}

	if( m_pVerticalScrollBar != NULL && m_pVerticalScrollBar->IsVisible() ) {
		if( IntersectRect(&rcTemp, &rcPaint, &m_pVerticalScrollBar->GetPos()) ) {
			m_pVerticalScrollBar->Paint(hDC, rcTemp, pStopControl);
		}
	}

	if( m_pHorizontalScrollBar != NULL && m_pHorizontalScrollBar->IsVisible() ) {
		if( IntersectRect(&rcTemp, &rcPaint, &m_pHorizontalScrollBar->GetPos()) ) {
			m_pHorizontalScrollBar->Paint(hDC, rcTemp, pStopControl);
		}
	}

    return true;
}

void CWaterfallList::SetScrollPos(SIZE szPos)
{
	int cx = 0;
	int cy = 0;
	if( m_pVerticalScrollBar && m_pVerticalScrollBar->IsVisible() ) {
		int iLastScrollPos = m_pVerticalScrollBar->GetScrollPos();
		m_pVerticalScrollBar->SetScrollPos(szPos.cy);
		cy = m_pVerticalScrollBar->GetScrollPos() - iLastScrollPos;
	}

	if( m_pHorizontalScrollBar && m_pHorizontalScrollBar->IsVisible() ) {
		int iLastScrollPos = m_pHorizontalScrollBar->GetScrollPos();
		m_pHorizontalScrollBar->SetScrollPos(szPos.cx);
		cx = m_pHorizontalScrollBar->GetScrollPos() - iLastScrollPos;
	}

	if( cx == 0 && cy == 0 ) return;
	if (!m_dataSource)
		return;
	RECT rc = m_rcItem;

	// Adjust for inset
	rc.left += (m_rcInset.left);
	rc.top += (m_rcInset.top);
	rc.right -= (m_rcInset.right);
	rc.bottom -= (m_rcInset.bottom);
	if( m_pVerticalScrollBar && m_pVerticalScrollBar->IsVisible() ) rc.right -= (m_pVerticalScrollBar->GetFixedWidth());
	if( m_pHorizontalScrollBar && m_pHorizontalScrollBar->IsVisible() ) rc.bottom -= (m_pHorizontalScrollBar->GetFixedHeight());

	int itemNumber=m_dataSource->NumberOfIndex(this);

	// Determine the minimum size
	int iPosX=rc.left;
	int iPosY=rc.top;

	SIZE szAvailable = { rc.right - rc.left, rc.bottom - rc.top };
	if( m_pHorizontalScrollBar && m_pHorizontalScrollBar->IsVisible() ) 
	{
		szAvailable.cx += m_pHorizontalScrollBar->GetScrollRange();
		iPosX -= m_pHorizontalScrollBar->GetScrollPos();
	}
	
	if( m_pVerticalScrollBar && m_pVerticalScrollBar->IsVisible() ) 
	{
		szAvailable.cy += m_pVerticalScrollBar->GetScrollRange();
		iPosY -= m_pVerticalScrollBar->GetScrollPos();
	}

	// Place elements
	for( int it2 = 0; it2 < itemNumber; it2++ )
	{
		SIZE sz;
		sz.cy = (m_dataSource->ListViewHeightForIndex(this,it2));
		sz.cx = rc.right-rc.left;
		RECT rcCtrl = { iPosX, iPosY, iPosX + sz.cx, iPosY + sz.cy };
		RECT rcTemp;
		if (IntersectRect(&rcTemp,&rcCtrl,&rc))
		{
			//如果控件在显示范围之内
			auto find=m_displayItems.find(it2);
			CWaterfallListCell* listCell=NULL;
			if (find==m_displayItems.end())
			{
				listCell=m_dataSource->ListViewCellAtIndex(this,sz,it2);
				m_displayItems[it2]=listCell;
				listCell->SetOwner(this);
				listCell->SetManager(GetManager(),this,true);
				listCell->SetIndex(it2);
				m_dataSource->ListViewWillDisplayCellAtIndex(this,listCell,it2);
			}
			else
				listCell=find->second;
			listCell->SetPos(rcCtrl);
		}
		else
		{
			//list列表之外的控件移除
			auto listCell=m_displayItems.find(it2);
			if (listCell!=m_displayItems.end())
			{
                if (m_removedItems.GetSize() < 1000)
                    m_removedItems.Add(listCell->second);
                else
                    delete listCell->second;
				m_displayItems.erase(listCell);
			}
		}
		iPosY += sz.cy + (m_iChildPadding);
	}

	Invalidate();
}

CControlUI* CWaterfallList::FindControl(FINDCONTROLPROC Proc,LPVOID pData, UINT uFlags)
{
    // Check if this guy is valid
    if( (uFlags & UIFIND_VISIBLE) != 0 && !IsVisible() ) return NULL;
    if( (uFlags & UIFIND_ENABLED) != 0 && !IsEnabled() ) return NULL;
    if( (uFlags & UIFIND_HITTEST) != 0 ) {
        if( !PtInRect(&m_rcItem, *(static_cast<LPPOINT>(pData))) ) return NULL;
        if( !m_bMouseChildEnabled ) {
            CControlUI* pResult = NULL;
            if( m_pVerticalScrollBar != NULL ) 
                pResult = m_pVerticalScrollBar->FindControl(Proc, pData, uFlags);
            if( pResult == NULL && m_pHorizontalScrollBar != NULL ) 
                pResult = m_pHorizontalScrollBar->FindControl(Proc, pData, uFlags);
            if( pResult == NULL ) 
                pResult = CControlUI::FindControl(Proc, pData, uFlags);
            return pResult;
        }
    }

    CControlUI* pResult = NULL;
    if( m_pVerticalScrollBar != NULL ) 
        pResult = m_pVerticalScrollBar->FindControl(Proc, pData, uFlags);
    if( pResult == NULL && m_pHorizontalScrollBar != NULL )
        pResult = m_pHorizontalScrollBar->FindControl(Proc, pData, uFlags);
    if( pResult != NULL ) 
        return pResult;

    if( (uFlags & UIFIND_ME_FIRST) != 0 ) {
        CControlUI* pControl = CControlUI::FindControl(Proc, pData, uFlags);
        if( pControl != NULL ) return pControl;
    }
    RECT rc = m_rcItem;
    rc.left += (m_rcInset.left);
    rc.top += (m_rcInset.top);
    rc.right -= (m_rcInset.right);
    rc.bottom -= (m_rcInset.bottom);
    if( m_pVerticalScrollBar && m_pVerticalScrollBar->IsVisible() ) 
        rc.right -= (m_pVerticalScrollBar->GetFixedWidth());
    if( m_pHorizontalScrollBar && m_pHorizontalScrollBar->IsVisible() ) 
        rc.bottom -= (m_pHorizontalScrollBar->GetFixedHeight());

	{
		for (auto i=m_displayItems.begin();i!=m_displayItems.end();++i) {
			CWaterfallListCell* pListCell = static_cast<CWaterfallListCell*>(i->second);
            CControlUI* pControl = pListCell->FindControl(Proc, pData, uFlags);
            if( pControl != NULL ) {
                if( (uFlags & UIFIND_HITTEST) != 0 && !pControl->IsFloat() 
                    && !PtInRect(&rc, *(static_cast<LPPOINT>(pData))) )
                    continue;
                else 
                    return pControl;
            } 
        }
    }

    if( pResult == NULL && (uFlags & UIFIND_ME_FIRST) == 0 ) 
        pResult = CControlUI::FindControl(Proc, pData, uFlags);
    return pResult;
}

void CWaterfallList::SetSelect(int selIndex)
{
	if (m_selectedItemIdx==selIndex)
		return;

	auto listCell=m_displayItems.find(m_selectedItemIdx);
	if (listCell != m_displayItems.end())
	{
		listCell->second->Invalidate();
	}

	SignalCellDeselect(this,m_selectedItemIdx);
	m_selectedItemIdx=selIndex;

	listCell=m_displayItems.find(selIndex);
	if (listCell != m_displayItems.end())
	{
		listCell->second->Invalidate();
	}
	SignalCellSelect(this,m_selectedItemIdx);
}

void CWaterfallList::Reload()
{
	if (!m_dataSource)
		return;

	for (auto i=m_displayItems.begin();i!=m_displayItems.end();++i)
	{
		delete (i->second);
	}
	m_displayItems.clear();
    if(IsVisible())
	    SetPos(m_rcItem);
}

void CWaterfallList::SetAttribute(LPCTSTR pstrName,LPCTSTR pstrValue)
{
	if (_tcscmp(pstrName,_T("itembkcolor"))==0)
	{
		while( *pstrValue > '\0' && *pstrValue <= ' ') pstrValue = CharNext(pstrValue);
        if( *pstrValue == '#') pstrValue = CharNext(pstrValue);
        TCHAR* pstr = NULL;
        uint32_t clrColor = _tcstoul(pstrValue, &pstr, 16);
        m_listInfo.itemBkColor= (clrColor);
	}
	else if (_tcscmp(pstrName,_T("itemhotcolor"))==0)
	{
		while( *pstrValue > '\0' && *pstrValue <= ' ') pstrValue = CharNext(pstrValue);
        if( *pstrValue == '#') pstrValue = CharNext(pstrValue);
        TCHAR* pstr = NULL;
        uint32_t clrColor = _tcstoul(pstrValue, &pstr, 16);
        m_listInfo.itemHotColor= (clrColor);
	}
	else if (_tcscmp(pstrName,_T("itemselcolor"))==0)
	{
		while( *pstrValue > '\0' && *pstrValue <= ' ') pstrValue = CharNext(pstrValue);
        if( *pstrValue == '#') pstrValue = CharNext(pstrValue);
        TCHAR* pstr = NULL;
        uint32_t clrColor = _tcstoul(pstrValue, &pstr, 16);
        m_listInfo.itemSelColor= (clrColor);
	}
	else if (_tcscmp(pstrName,_T("itembkimage"))==0)
	{
		m_listInfo.itemBkImage=pstrValue;
	}
	else if (_tcscmp(pstrName,_T("itemhotimage"))==0)
	{
		m_listInfo.itemHotImage=pstrValue;
	}
	else if (_tcscmp(pstrName,_T("itemselimage"))==0)
	{
		m_listInfo.itemSelImage=pstrValue;
	}
	else if (_tcscmp(pstrName,_T("itemheight"))==0)
	{
		m_itemHeight=_ttoi(pstrValue);
	}
	else
		CContainerUI::SetAttribute(pstrName,pstrValue);
}


CWaterfallListCell* CWaterfallList::DequeueReusableCell(uint32_t identifier)
{
	for (int i=0;i<m_removedItems.GetSize();++i)
	{
		CWaterfallListCell* cell=static_cast<CWaterfallListCell*>(m_removedItems.GetAt(i));
		if (cell->GetReuseIdentifier()==identifier)
		{
			m_removedItems.Remove(i);
			return cell;
		}
	}
	return NULL;
}


CWaterfallListCell::CWaterfallListCell()
	:m_owner(NULL),m_index(-1),m_buttonState(0),m_reuseIdentifier(0)
{

}

CWaterfallListCell::~CWaterfallListCell()
{

}

LPVOID CWaterfallListCell::GetInterface(LPCTSTR pstrName)
{
    if (_tcscmp(pstrName, DUI_CTR_WATERFALLLIST_CELL) == 0)
        return static_cast<CWaterfallListCell*>(this);
    return CContainerUI::GetInterface(pstrName);
}

void CWaterfallListCell::SetReuseIdentifier(uint32_t identifier)
{
	m_reuseIdentifier=identifier;
}

uint32_t CWaterfallListCell::GetReuseIdentifier()
{
	return m_reuseIdentifier;
}

void CWaterfallListCell::SetIndex(int idx)
{
	m_index=idx;
}

int CWaterfallListCell::GetIndex()
{
	return m_index;
}

void CWaterfallListCell::SetOwner(CWaterfallList*  owner)
{
	m_owner=owner;
}

CWaterfallList* CWaterfallListCell::GetOwner()
{
	return m_owner;
}

void CWaterfallListCell::DoEvent(TEventUI& event)
{
	switch(event.Type)
	{
	case UIEVENT_BUTTONDOWN:
		 if( PtInRect(&m_rcItem, event.ptMouse) && IsEnabled() ) 
		 {
            m_buttonState|= UISTATE_PUSHED | UISTATE_CAPTURED;
			if(m_owner)
				m_owner->SetSelect(m_index);
        }
		break;
	case UIEVENT_BUTTONUP:
		m_buttonState&=~UISTATE_PUSHED;
		break;

	case UIEVENT_MOUSEENTER:
		{
			if( IsEnabled() ) {
				m_pManager->SendNotify(this, DUI_MSGTYPE_MOUSEENTER);
				m_buttonState |= UISTATE_HOT;
				Invalidate();
			}
			return;
		}
	case UIEVENT_MOUSELEAVE:
		{
			if( IsEnabled() ) {
				m_pManager->SendNotify(this, DUI_MSGTYPE_MOUSELEAVE);
				m_buttonState &= ~UISTATE_HOT;
				Invalidate();
			}
			return;
		}
	default:
		GetOwner()->DoEvent(event);
	}
}



void CWaterfallListCell::PaintStatusImage(HDC hDC)
{
	if( !IsEnabled() ) 
		m_buttonState |= UISTATE_DISABLED;
	else
		m_buttonState &= ~ UISTATE_DISABLED;

	CWaterfallList::ListInfo* info=GetOwner()->GetListInfo();

	if(GetOwner()->GetSelect()==m_index) {
		if (info->itemSelColor)
		{
			CRenderEngine::DrawColor(hDC,m_rcItem,info->itemSelColor);
		}

        if (DrawImage(hDC, info->itemSelImage))
            return;
    }
	else if( (m_buttonState & UISTATE_HOT) != 0 ) {
		if (info->itemHotColor)
		{
			CRenderEngine::DrawColor(hDC,m_rcItem,info->itemHotColor);
		}

        if (DrawImage(hDC, info->itemHotImage))
            return;
    }
	else
	{
		if (info->itemBkColor)
		{
			CRenderEngine::DrawColor(hDC,m_rcItem,info->itemBkColor);
		}

        if (DrawImage(hDC, info->itemBkImage))
            return;
	}
}


}//namespace


