#include "DropTargetBase.h"

CDropTargetBase::CDropTargetBase() :
tb_RefCount(0),
m_hTargetWnd(0),
m_AcceptKeyState(0),
m_piDropHelper(NULL)
{
	// Create an instance of the shell DnD helper object.
	HRESULT hr = CoCreateInstance(CLSID_DragDropHelper, NULL,
		CLSCTX_INPROC_SERVER,
		IID_IDropTargetHelper,
		(void**)&m_piDropHelper);
}

CDropTargetBase::~CDropTargetBase()
{
	RevokeDragDrop(m_hTargetWnd);
	if (NULL != m_piDropHelper)
		m_piDropHelper->Release();
}

BOOL CDropTargetBase::DragDropRegister(HWND hWnd, DWORD AcceptKeyState)
{
	if (!IsWindow(hWnd))return false;
	HRESULT s = ::RegisterDragDrop(hWnd, this);
	if (SUCCEEDED(s))
	{
		m_hTargetWnd = hWnd;
		m_AcceptKeyState = AcceptKeyState;
		return true;
	}
	else
	{
		return false;
	}

}

HRESULT STDMETHODCALLTYPE CDropTargetBase::QueryInterface(REFIID iid, void ** ppvObject)
{
	*ppvObject = NULL;

	if (iid == IID_IDropTarget)
		*ppvObject = static_cast<IDropTarget*>(this);

	if (*ppvObject != NULL)
		AddRef();
	return *ppvObject == NULL ? E_NOINTERFACE : S_OK;
}


ULONG STDMETHODCALLTYPE CDropTargetBase::AddRef(void)
{
	InterlockedIncrement(&tb_RefCount);
	return tb_RefCount;
}

ULONG STDMETHODCALLTYPE CDropTargetBase::Release(void)
{
	ULONG ulRefCount = InterlockedDecrement(&tb_RefCount);
	return ulRefCount;
}

HRESULT STDMETHODCALLTYPE CDropTargetBase::DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	POINT ppt = { pt.x, pt.y };
	DWORD dwEffect = onDragOver(m_hTargetWnd, grfKeyState, ppt);
	*pdwEffect &= dwEffect;
	if (m_piDropHelper != NULL)
	{
		m_piDropHelper->DragOver((LPPOINT)&pt, *pdwEffect);
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDropTargetBase::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	if (grfKeyState != m_AcceptKeyState)
	{
		*pdwEffect = DROPEFFECT_NONE;
		return S_OK;
	}
	POINT ppt = { pt.x, pt.y };
	DROPEFFECT dwEffect = onDragEnter(m_hTargetWnd, pDataObject, grfKeyState, ppt);
	*pdwEffect &= dwEffect;

	if (m_piDropHelper != NULL)
	{
		m_piDropHelper->DragEnter(m_hTargetWnd, pDataObject, (LPPOINT)&pt, *pdwEffect);
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDropTargetBase::DragLeave(void)
{
	
	onDragLeave(m_hTargetWnd);
	if (m_piDropHelper != NULL)
	{
		m_piDropHelper->DragLeave();
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDropTargetBase::Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD __RPC_FAR *pdwEffect)
{

	if (NULL == pDataObj)
	{
		return E_INVALIDARG;
	}

	POINT ppt = { pt.x, pt.y };
	if (NULL != m_piDropHelper)
	{
		m_piDropHelper->Drop(pDataObj, &ppt, *pdwEffect);
	}

	return onDrop(m_hTargetWnd, pDataObj, grfKeyState, ppt);
}

BOOL CDropTargetBase::EnumDragData(IDataObject *pDataObject)
{
	IEnumFORMATETC *pEnumFmt = NULL;

	//�����ȡ�ɹ��������ͨ��IEnumFORMATETC�ӿڵ�Next��������ö�����е����ݸ�ʽ��
	HRESULT ret = pDataObject->EnumFormatEtc(DATADIR_GET, &pEnumFmt);
	pEnumFmt->Reset();

	HRESULT Ret = S_OK;
	FORMATETC cFmt = { 0 };
	ULONG Fetched = 0;

	while (Ret != S_OK)
	{
		Ret = pEnumFmt->Next(1, &cFmt, &Fetched);

		if (SUCCEEDED(ret))
		{
			if (cFmt.cfFormat == CF_HDROP)
			{
				if (GetDragData(pDataObject, cFmt))
					return TRUE;
			}
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CDropTargetBase::GetDragData(IDataObject *pDataObject, FORMATETC cFmt)
{
	HRESULT ret = S_OK;
	STGMEDIUM stgMedium;

	ret = pDataObject->GetData(&cFmt, &stgMedium);

	if (FAILED(ret))
		return FALSE;

	if (stgMedium.pUnkForRelease != NULL)
		return FALSE;


	switch (stgMedium.tymed)
	{
		//�������������룬���EnumDragData����������������͵�����
	case TYMED_HGLOBAL:
	{

		/*LPDRAGDATA pData = new DRAGDATA;

		pData->cfFormat = cFmt.cfFormat;
		memcpy(&pData->stgMedium, &stgMedium, sizeof(STGMEDIUM));

		m_Array.push_back(pData);*/

		return true;
		break;

	}
	default:
		// type not supported, so return error
	{
		::ReleaseStgMedium(&stgMedium);
	}
	break;
	}

	return false;

}

