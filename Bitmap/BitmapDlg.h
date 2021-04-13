
// BitmapDlg.h: 標頭檔
//

//繪圖用 Header File & Library
#pragma once
#include "vfw.h"
#pragma comment(lib, "vfw32.lib")


// CBitmapDlg 對話方塊
class CBitmapDlg : public CDialogEx
{
// 建構
public:
	CBitmapDlg(CWnd* pParent = nullptr);	// 標準建構函式
	int Draw_BitMap(int x, int y, int PX, int PY, unsigned char *Data);//x=寬 y=長  PX=x軸起始點 PY=y軸起始點

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BITMAP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
