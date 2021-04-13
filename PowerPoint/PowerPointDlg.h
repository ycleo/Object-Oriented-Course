
// PowerPointDlg.h: 標頭檔
//

#pragma once


// CPowerPointDlg 對話方塊
class CPowerPointDlg : public CDialogEx
{
// 建構
public:
	CPowerPointDlg(CWnd* pParent = nullptr);	// 標準建構函式

	//自行定義之成員變數 & 函式
	HDC hdc;    //視窗代碼(繪圖用)
	BOOL Flag;  //紀錄滑鼠左鍵是否按下之狀態
	BOOL Tag;
	int bx, by; //紀錄滑鼠按下之座標
	int	ex, ey; //紀錄滑鼠最後一次移動位置
	void Line(int x1, int y1, int x2, int y2, int C, int W);
	void Rect(int x1, int y1, int x2, int y2, int C, int W);
	void Circle(int cx, int cy, int r, int C, int W);
	void Ellipse (int cx, int cy, int rx, int ry, int C, int W);
	void Rose(int cx, int cy, int r, int C, int W);
	void UpHalfCircle(int cx, int cy, int r, int C, int W);
	void DownHalfCircle(int cx, int cy, int r, int C, int W);

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POWERPOINT_DIALOG };
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
