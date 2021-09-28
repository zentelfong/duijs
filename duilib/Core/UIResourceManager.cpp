#include "StdAfx.h"
#include "UIResourceManager.h"

namespace DuiLib {
	
	CResourceManager::CResourceManager(void)
	{
		m_pQuerypInterface = NULL;
		
	}

	CResourceManager::~CResourceManager(void)
	{
		ResetResourceMap();
	}

	BOOL CResourceManager::LoadResource(STRINGorID xml, LPCTSTR type)
	{
		if( HIWORD(xml.m_lpstr) != NULL ) 
		{
			if( *(xml.m_lpstr) == _T('<') ) 
			{
				if( !m_xml.Load(xml.m_lpstr) ) return NULL;
			}
			else 
			{
				if( !m_xml.LoadFromFile(xml.m_lpstr) ) return NULL;
			}
		}
		else
		{
			HRSRC hResource = ::FindResource(CPaintManagerUI::GetResourceDll(), xml.m_lpstr, type);
			if( hResource == NULL ) return NULL;
			HGLOBAL hGlobal = ::LoadResource(CPaintManagerUI::GetResourceDll(), hResource);
			if( hGlobal == NULL ) 
			{
				FreeResource(hResource);
				return NULL;
			}

			if( !m_xml.LoadFromMem((BYTE*)::LockResource(hGlobal), ::SizeofResource(CPaintManagerUI::GetResourceDll(), hResource) )) {
				return NULL;
			}
			::FreeResource(hResource);
		}

		return LoadResource(m_xml.GetRoot());
	}


#define _Failed(msg) _tcscpy(lpstrErrorMsg,msg),NULL;


	BYTE* CResourceManager::LoadFile(LPCTSTR pstrFilename, DWORD* pSize, LPTSTR lpstrErrorMsg) {
		CDuiString sFile = CPaintManagerUI::GetResourcePath();
		if (CPaintManagerUI::GetResourceZip().IsEmpty()) {
			sFile += pstrFilename;
			HANDLE hFile = ::CreateFile(sFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE) return _Failed(_T("Error opening file"));
			DWORD dwSize = ::GetFileSize(hFile, NULL);
			if (dwSize == 0) return _Failed(_T("File is empty"));
			if (dwSize > 4096 * 1024) return _Failed(_T("File too large"));

			DWORD dwRead = 0;
			BYTE* pByte = new BYTE[dwSize + 1];
			::ReadFile(hFile, pByte, dwSize, &dwRead, NULL);
			::CloseHandle(hFile);
			if (dwRead != dwSize) {
				delete[] pByte;
				pByte = NULL;
				return _Failed(_T("Could not read file"));
			}

			pByte[dwSize] = '\0';
			*pSize = dwSize;
			
			return pByte;
		}
		else {
			sFile += CPaintManagerUI::GetResourceZip();
			HZIP hz = NULL;
			if (CPaintManagerUI::IsCachedResourceZip()) hz = (HZIP)CPaintManagerUI::GetResourceZipHandle();
			else {
				CDuiString sFilePwd = CPaintManagerUI::GetResourceZipPwd();
#ifdef UNICODE
				char* pwd = w2a((wchar_t*)sFilePwd.GetData());
				hz = OpenZip(sFile.GetData(), pwd);
				if (pwd) delete[] pwd;
#else
				hz = OpenZip(sFile.GetData(), sFilePwd.GetData());
#endif
			}
			if (hz == NULL) return _Failed(_T("Error opening zip file"));
			ZIPENTRY ze;
			int i = 0;
			CDuiString key = pstrFilename;
			key.Replace(_T("\\"), _T("/"));
			if (FindZipItem(hz, key, true, &i, &ze) != 0) return _Failed(_T("Could not find ziped file"));
			DWORD dwSize = ze.unc_size;
			if (dwSize == 0) return _Failed(_T("File is empty"));
			if (dwSize > 4096 * 1024) return _Failed(_T("File too large"));
			BYTE* pByte = new BYTE[dwSize + 1];
			int res = UnzipItem(hz, i, pByte, dwSize);
			if (res != 0x00000000 && res != 0x00000600) {
				delete[] pByte;
				if (!CPaintManagerUI::IsCachedResourceZip()) CloseZip(hz);
				return _Failed(_T("Could not unzip file"));
			}
			if (!CPaintManagerUI::IsCachedResourceZip()) CloseZip(hz);

			pByte[dwSize] = '\0';
			*pSize = dwSize;
			return pByte;
		}
	}


	BOOL CResourceManager::LoadResource(CMarkupNode Root)
	{
		if( !Root.IsValid() ) return FALSE;

		LPCTSTR pstrClass = NULL;
		int nAttributes = 0;
		LPCTSTR pstrName = NULL;
		LPCTSTR pstrValue = NULL;
		LPTSTR pstr = NULL;

		//加载图片资源
		LPCTSTR pstrId = NULL;
		LPCTSTR pstrPath = NULL;
		for( CMarkupNode node = Root.GetChild() ; node.IsValid(); node = node.GetSibling() ) 
		{
			pstrClass = node.GetName();
			CMarkupNode ChildNode = node.GetChild();
			if(ChildNode.IsValid()) LoadResource(node);
			else if ((_tcsicmp(pstrClass,_T("Image")) == 0) && node.HasAttributes())
			{
				//加载图片资源
				nAttributes = node.GetAttributeCount();
				for( int i = 0; i < nAttributes; i++ ) 
				{
					pstrName = node.GetAttributeName(i);
					pstrValue = node.GetAttributeValue(i);

					if( _tcsicmp(pstrName, _T("id")) == 0 ) 
					{
						pstrId = pstrValue;
					}
					else if( _tcsicmp(pstrName, _T("path")) == 0 ) 
					{
						pstrPath = pstrValue;
					}
				}
				if( pstrId == NULL ||  pstrPath == NULL) continue;
				CDuiString * pstrFind = static_cast<CDuiString *>(m_mImageHashMap.Find(pstrId));
				if(pstrFind != NULL) continue;
				m_mImageHashMap.Insert(pstrId, (LPVOID)new CDuiString(pstrPath));
			}
			else if( _tcsicmp(pstrClass,_T("Xml")) == 0 && node.HasAttributes()) {
				//加载XML配置文件
				nAttributes = node.GetAttributeCount();
				for( int i = 0; i < nAttributes; i++ ) 
				{
					pstrName = node.GetAttributeName(i);
					pstrValue = node.GetAttributeValue(i);

					if( _tcsicmp(pstrName, _T("id")) == 0 ) 
					{
						pstrId = pstrValue;
					}
					else if( _tcsicmp(pstrName, _T("path")) == 0 ) 
					{
						pstrPath = pstrValue;
					}
				}
				if( pstrId == NULL ||  pstrPath == NULL) continue;
				CDuiString * pstrFind = static_cast<CDuiString *>(m_mXmlHashMap.Find(pstrId));
				if(pstrFind != NULL) continue;
				m_mXmlHashMap.Insert(pstrId, (LPVOID)new CDuiString(pstrPath));
			}
			else continue;
		}
		return TRUE;
	}

	LPCTSTR CResourceManager::GetImagePath(LPCTSTR lpstrId)
	{
		CDuiString * lpStr = static_cast<CDuiString *>(m_mImageHashMap.Find(lpstrId));
		return lpStr == NULL? NULL:lpStr->GetData();
	}

	LPCTSTR CResourceManager::GetXmlPath(LPCTSTR lpstrId)
	{
		CDuiString * lpStr = static_cast<CDuiString *>(m_mXmlHashMap.Find(lpstrId));
		return lpStr == NULL? NULL:lpStr->GetData();
	}

	void CResourceManager::ResetResourceMap()
	{
		CDuiString* lpStr;
		for( int i = 0; i< m_mImageHashMap.GetSize(); i++ )
		{
			if(LPCTSTR key = m_mImageHashMap.GetAt(i))
			{
				lpStr = static_cast<CDuiString *>(m_mImageHashMap.Find(key));
				delete lpStr;
				lpStr = NULL;
			}
		}
		for( int i = 0; i< m_mXmlHashMap.GetSize(); i++ )
		{
			if(LPCTSTR key = m_mXmlHashMap.GetAt(i))
			{
				lpStr = static_cast<CDuiString *>(m_mXmlHashMap.Find(key));
				delete lpStr;
				lpStr = NULL;
			}
		}
		for( int i = 0; i< m_mTextResourceHashMap.GetSize(); i++ )
		{
			if(LPCTSTR key = m_mTextResourceHashMap.GetAt(i))
			{
				lpStr = static_cast<CDuiString *>(m_mTextResourceHashMap.Find(key));
				delete lpStr;
				lpStr = NULL;
			}
		}
	}

	BOOL CResourceManager::LoadLanguage(LPCTSTR pstrXml)
	{
		CMarkup xml;
		if( *(pstrXml) == _T('<') ) {
			if( !xml.Load(pstrXml) ) return FALSE;
		}
		else {
			if( !xml.LoadFromFile(pstrXml) ) return FALSE;
		}
		CMarkupNode Root = xml.GetRoot();
		if( !Root.IsValid() ) return FALSE;

		LPCTSTR pstrClass = NULL;
		int nAttributes = 0;
		LPCTSTR pstrName = NULL;
		LPCTSTR pstrValue = NULL;
		LPTSTR pstr = NULL;

		//加载图片资源
		LPCTSTR pstrId = NULL;
		LPCTSTR pstrText = NULL;
		for( CMarkupNode node = Root.GetChild() ; node.IsValid(); node = node.GetSibling() ) 
		{
			pstrClass = node.GetName();
			if ((_tcsicmp(pstrClass,_T("Text")) == 0) && node.HasAttributes())
			{
				//加载图片资源
				nAttributes = node.GetAttributeCount();
				for( int i = 0; i < nAttributes; i++ ) 
				{
					pstrName = node.GetAttributeName(i);
					pstrValue = node.GetAttributeValue(i);

					if( _tcsicmp(pstrName, _T("id")) == 0 ) 
					{
						pstrId = pstrValue;
					}
					else if( _tcsicmp(pstrName, _T("value")) == 0 ) 
					{
						pstrText = pstrValue;
					}
				}

				//如果没有value属性则从data内读取
				if(!pstrText) pstrText = node.GetValue();

				if( pstrId == NULL ||  pstrText == NULL) continue;

				CDuiString *lpstrFind = static_cast<CDuiString *>(m_mTextResourceHashMap.Find(pstrId));
				if(lpstrFind != NULL) {
					lpstrFind->Assign(pstrText);
				}
				else {
					m_mTextResourceHashMap.Insert(pstrId, (LPVOID)new CDuiString(pstrText));
				}
			}
			else continue;
		}

		return TRUE;
	}

	CDuiString CResourceManager::GetText(LPCTSTR lpstrId, LPCTSTR lpstrType)
	{
		if(lpstrId == NULL) return _T("");

		CDuiString *lpstrFind = static_cast<CDuiString *>(m_mTextResourceHashMap.Find(lpstrId));
		if (lpstrFind == NULL && m_pQuerypInterface)
		{
			lpstrFind = m_pQuerypInterface->QueryControlText(lpstrId, lpstrType);
			m_mTextResourceHashMap.Insert(lpstrId, (LPVOID)lpstrFind);
		}
		return lpstrFind == NULL ? lpstrId : *lpstrFind;
	}

	void CResourceManager::ReloadText()
	{
		if(m_pQuerypInterface == NULL) return;
		//重载文字描述
		LPCTSTR lpstrId = NULL;
		CDuiString* lpstrText;
		for( int i = 0; i < m_mTextResourceHashMap.GetSize(); i++ )
		{
			lpstrId = m_mTextResourceHashMap.GetAt(i);
			if (lpstrId == NULL) continue;
			lpstrText = m_pQuerypInterface->QueryControlText(lpstrId, NULL);
			if(lpstrText != NULL) {
				CDuiString * lpStr = static_cast<CDuiString *>(m_mTextResourceHashMap.Find(lpstrId));
				lpStr->Assign(*lpstrText);
				delete lpstrText;
			}
		}
	}
	void CResourceManager::ResetTextMap()
	{
		CDuiString * lpStr;
		for( int i = 0; i< m_mTextResourceHashMap.GetSize(); i++ )
		{
			if(LPCTSTR key = m_mTextResourceHashMap.GetAt(i))
			{
				lpStr = static_cast<CDuiString *>(m_mTextResourceHashMap.Find(key));
				delete lpStr;
			}
		}
	}

	
} // namespace DuiLib