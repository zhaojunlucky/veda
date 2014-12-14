#ifndef DROP_TARGET_EX_H
#define DROP_TARGET_EX_H

#include <OleIdl.h>
#include <shobjidl.h>
#include <shlguid.h>

typedef DWORD DROPEFFECT;

class CDropTargetBase : public IDropTarget
{
public:
	CDropTargetBase();
	virtual ~CDropTargetBase();
	BOOL DragDropRegister(HWND hWnd, DWORD AcceptKeyState = MK_LBUTTON);

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject);

	ULONG STDMETHODCALLTYPE AddRef(void);

	ULONG STDMETHODCALLTYPE Release(void);

	HRESULT STDMETHODCALLTYPE DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);

	HRESULT STDMETHODCALLTYPE DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);

	HRESULT STDMETHODCALLTYPE DragLeave(void);

	HRESULT STDMETHODCALLTYPE Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD __RPC_FAR *pdwEffect);

	BOOL GetDragData(IDataObject *pDataObject, FORMATETC cFmt);

	//枚举数据格式的函数，我这里并没有用到，但是将来可能会用,函数目前只枚举了HDROP类型
	BOOL EnumDragData(IDataObject *pDataObject);

	virtual DROPEFFECT onDragEnter(HWND hwnd, IDataObject* dataObj, DWORD grfKeyState, POINT pt){ return DROPEFFECT_NONE; }
	virtual DROPEFFECT onDragOver(HWND hwnd, DWORD grfKeyState, POINT pt){ return DROPEFFECT_NONE; }
	virtual void onDragLeave(HWND hwnd){};
	virtual HRESULT onDrop(HWND hwnd, IDataObject* dataObj, DWORD grfKeyState, POINT pt){ return E_FAIL; }
private:

	ULONG	tb_RefCount;
	HWND	m_hTargetWnd;
	DWORD	m_AcceptKeyState;
	IDropTargetHelper* m_piDropHelper;
};
#endif	//DROP_TARGET_EX_H