
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "DirectInputTest.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	pDirectInput = NULL;
	pMouseDevice = NULL;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if(m_DrawTexts.GetSize()>0)
	{
		int y=0;
		for(int i=m_DrawTexts.GetUpperBound();i>=0;i--)
		{
			CString s;
			s.Format("[%ld] %s",i,m_DrawTexts[i]);
			dc.TextOut(5,5+y,s);
			y+=16;
			if(y>=300) break;
		}
	}
	// TODO: Add your message handler code here
	if (!pDirectInput)
	{
		CString s;
		HRESULT hr = DirectInput8Create(AfxGetApp()->m_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&pDirectInput, NULL);
		if (hr == DI_OK)
		{
			hr = pDirectInput->CreateDevice(GUID_SysMouse,&pMouseDevice,NULL);
			if (hr == DI_OK)
			{
				pMouseDevice->SetDataFormat(&c_dfDIMouse);
				pMouseDevice->SetCooperativeLevel(AfxGetApp()->GetMainWnd()->GetSafeHwnd(),DISCL_NONEXCLUSIVE|DISCL_BACKGROUND);

				hr = pMouseDevice->Acquire();
				if (hr == DI_OK)
				{
					//SetTimer(0,16,NULL);					
				}
				else
				{
					s.Format("Acquire error(%ld)",hr);
					AfxMessageBox(s);
				}
			}
			else
			{
				s.Format("CreateDevice error(%ld)",hr);
				AfxMessageBox(s);
			}
		}
		else
		{
			s.Format("DirectInput8Create error(%ld)",hr);
			AfxMessageBox(s);
		}
	}
	// Do not call CWnd::OnPaint() for painting messages
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if(pMouseDevice)
	{
		CString s;
		HRESULT hr = S_OK;//pMouseDevice->Acquire();
		if(SUCCEEDED(hr))
		{
			DIMOUSESTATE state;
			hr = pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE),(LPVOID)&state);
			if(hr==DI_OK)
			{
				if(state.lZ!=0)
				{
					s.Format("%u:%ld",GetTickCount(),state.lZ);
					m_DrawTexts.Add(s);
					state.lZ=0;
					Invalidate();
				}
			}
			else
			{
				s.Format("GetDeviceState error(%ld)",hr);
				AfxMessageBox(s);
			}
		}
		else
		{
			s.Format("Acquire error(%ld)",hr);
			AfxMessageBox(s);
		}
	}

	CWnd::OnTimer(nIDEvent);
}

BOOL CChildView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	CString s;
	s.Format("%u:%ld",GetTickCount(),zDelta);
	m_DrawTexts.Add(s);
	Invalidate();
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}
