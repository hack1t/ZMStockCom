#pragma once
#include <atlstr.h>

/// 事件通知对应的消息
#define WM_TRADEEVENT_INITRETURN		WM_USER + 901
#define WM_TRADEEVENT_LOGINRETURN		WM_USER + 902
#define WM_TRADEEVENT_STOCKQUOTE		WM_USER + 903
#define WM_TRADEEVENT_STOCKQUOTE10		WM_USER + 904
#define WM_TRADEEVENT_STOCKMINUTE		WM_USER + 905
#define WM_TRADEEVENT_STOCKTRANS		WM_USER + 906
#define WM_TRADEEVENT_STOCKBARS			WM_USER + 907
#define WM_TRADEEVENT_STOCKDETAILTRANS	WM_USER + 908
#define WM_TRADEEVENT_STOCKDETAILORDER	WM_USER + 909
#define WM_TRADEEVENT_STOCKORDERLIST	WM_USER + 910
#define WM_TRADEEVENT_SERVERERRVER		WM_USER + 911

#define WM_TRADEEVENT_SENDORDER			WM_USER + 920
#define WM_TRADEEVENT_ORDERSUCCESS		WM_USER + 921
#define WM_TRADEEVENT_ORDERERROR		WM_USER + 922
#define WM_TRADEEVENT_CHANGESERVER		WM_USER + 923

// 交易事件处理辅助类
class CStockComEvent : 
	public CComObjectRoot,
	//实现交易事件通知接口
	public _ITradeEvents
{
protected:

	/// 父窗口
	HWND			m_hParentWnd;

	/// 返回数据缓存
//	ITradeRecordPtr	m_spiTradeRecord;

public:
	CStockComEvent()
		:m_hParentWnd(NULL)
	{
	}

	~CStockComEvent()
	{
	}

	void SetCallPara(HWND hParentWnd)
	{
		if(NULL != hParentWnd)
		{
			if(!::IsWindow(hParentWnd))
				return;
		}
		m_hParentWnd = hParentWnd;
	}

BEGIN_COM_MAP(CStockComEvent)
	COM_INTERFACE_ENTRY(_ITradeEvents)
END_COM_MAP()

public:

	STDMETHODIMP GetTypeInfoCount(UINT*)
    {
       return E_NOTIMPL;
    }

    STDMETHODIMP GetTypeInfo( UINT iTInfo,LCID lcid,ITypeInfo **ppTInfo)
    { 
       return E_NOTIMPL;
    }

    STDMETHODIMP GetIDsOfNames( REFIID riid,LPOLESTR *rgszNames,UINT cNames,
                    LCID lcid,DISPID *rgDispId)
    { 
      return E_NOTIMPL;
    }

	STDMETHOD(Invoke)(DISPID dispIdMember,REFIID riid,LCID lcid,WORD wFlags,DISPPARAMS *pDispParams,
               VARIANT *pVarResult,EXCEPINFO *pExcepInfo,UINT *puArgErr);
	
	//  _ITradeEvents
	/// 初始化接口结果通知
	STDMETHOD(InitEvent)(IDispatch* piTrade,VARIANT_BOOL bOK);
	/// 登录服务器结果通知
	STDMETHOD(LoginEvent)(IDispatch* piTrade,USHORT nTradeID,BSTR bstrHost,USHORT nPort,VARIANT_BOOL bOK);
	/// 交易委托成功回报
	STDMETHOD(OrderOKEvent)(ULONG OrderOKEvent,EZMExchangeType eExchangeType,IDispatch* piRecordInfo);
	/// 交易委托失败回报
	STDMETHOD(OrderErrEvent)(ULONG nReqID,BSTR bstrErrInfo);
	/// 查询指定股票实时5档行情回报
	STDMETHOD(StockQuoteEvent)(ULONG nReqID,BSTR bstrCode,IDispatch* piRecordInfo);
	/// 交易委托成交回报
	STDMETHOD(OrderSuccessEvent)(BSTR bstrOrderID,BSTR bstrJson);

	/// 服务器错误通知
	STDMETHOD(ServerErrEvent)(USHORT nTradeID,ULONG nReqID);
	/// 服务器切换通知，多服务器才有
	STDMETHOD(ServerChangedEvent)(USHORT nPreTradeID,USHORT nCurTradeID);
};