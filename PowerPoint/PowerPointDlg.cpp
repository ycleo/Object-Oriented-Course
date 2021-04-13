
// PowerPointDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "PowerPoint.h"
#include "PowerPointDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CPoint B[10000];
CPoint E[10000];
long i = 0;

// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPowerPointDlg 對話方塊



CPowerPointDlg::CPowerPointDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POWERPOINT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPowerPointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPowerPointDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPowerPointDlg::OnBnClickedButton1)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPowerPointDlg 訊息處理常式

BOOL CPowerPointDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	hdc = ::GetDC(m_hWnd);  //取得繪圖代碼

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CPowerPointDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CPowerPointDlg::OnPaint()
{
	for (int j = 0; j < i; j++) {
		Line(B[j].x, B[j].y, E[j].x, E[j].y, 0x000000, 2);
	}
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CPowerPointDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPowerPointDlg::Line(int x1, int y1, int x2, int y2, int C, int W) {
	CPen P(PS_SOLID, W, RGB(C >> 16, (C >> 8) & 0xFF, C & 0xFF));
	SelectObject(hdc, P);
	MoveToEx(hdc, x1, y1, 0);
	LineTo(hdc, x2, y2);
}

void CPowerPointDlg::Rect(int x1, int y1, int x2, int y2, int C, int W) {
	CPen P(PS_SOLID, W, RGB(C >> 16, (C >> 8) & 0xFF, C & 0xFF));
	SelectObject(hdc, P);
	MoveToEx(hdc, x1, y1, 0);
	LineTo(hdc, x1, y2);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x2, y1);
	LineTo(hdc, x1, y1);
}

void  CPowerPointDlg::Circle(int cx, int cy, int r, int C, int W) {
	int x, y;
	CPen P(PS_SOLID, W, RGB(C >> 16, (C >> 8) & 0xFF, C & 0xFF));
	SelectObject(hdc, P);
	MoveToEx(hdc, cx+r, cy, 0);
	for (int i = 0; i < 360; i++) {
		x = cx + (int)((float)r*cos(i*6.28318/ 360));
		y = cy + (int)((float)r*sin(i*6.28318/ 360));
		LineTo(hdc, x, y);
	}
}

void  CPowerPointDlg::Ellipse(int cx, int cy, int rx, int ry,int C, int W) {
	int x, y;
	CPen P(PS_SOLID, W, RGB(C >> 16, (C >> 8) & 0xFF, C & 0xFF));
	SelectObject(hdc, P);
	MoveToEx(hdc, cx + rx, cy, 0);
	for (int i = 0; i < 360; i++) {
		x = cx + (int)((float)rx*cos(i*6.28318 / 360));
		y = cy + (int)((float)ry*sin(i*6.28318 / 360));
		LineTo(hdc, x, y);
	}
}
void  CPowerPointDlg::Rose(int cx, int cy, int r, int C, int W) {
	int x, y;
	float a;
	CPen P(PS_SOLID, W, RGB(C >> 16, (C >> 8) & 0xFF, C & 0xFF));
	SelectObject(hdc, P);
	MoveToEx(hdc, cx + r, cy, 0);
	for (int i = 0; i < 360; i++) {
		a = (float)i*6.28318 / 360.0;
		x = cx + (int)((float)r*cos(7*a)*cos(a));
		y = cy + (int)((float)r*cos(7*a)*sin(a));
		LineTo(hdc, x, y);
	}
}

void CPowerPointDlg::UpHalfCircle(int cx, int cy, int r, int C, int W) {
	int x, y;
	CPen P(PS_SOLID, W, RGB(C >> 16, (C >> 8) & 0xFF, C & 0xFF));
	SelectObject(hdc, P);
	MoveToEx(hdc, cx + r, cy, 0);
	for (int i = 0; i <= 180; i++) {
		x = cx + (int)((float)r*cos(i*6.28318 / 360));
		y = cy + (int)((float)r*sin(i*6.28318 / 360));
		LineTo(hdc, x, y);
	}
}
void CPowerPointDlg::DownHalfCircle(int cx, int cy, int r, int C, int W) {
	int x, y;
	CPen P(PS_SOLID, W, RGB(C >> 16, (C >> 8) & 0xFF, C & 0xFF));
	SelectObject(hdc, P);
	MoveToEx(hdc, cx + r, cy, 0);
	for (int i = 0; i >= -180; i--) {
		x = cx + (int)((float)r*cos(i*6.28318 / 360));
		y = cy + (int)((float)r*sin(i*6.28318 / 360));
		LineTo(hdc, x, y);
	}
}

void CPowerPointDlg::OnBnClickedButton1()  //畫線副程式
{	/*
	CPen P(PS_SOLID, 10, RGB(255, 0, 0)); //紅色
	hdc = ::GetDC(m_hWnd);     //取得繪圖代碼
	SelectObject(hdc, P);      //選擇顏色畫筆
	MoveToEx(hdc, 10, 10, 0);  //線之起始點 (落點)
	LineTo(hdc, 400, 500);     //線之終點  */
	
	//Line(x1, y1, x2, y2, Color, W);
	float r = 100.0;
	float a = 3^(1/2);
	printf("%d", a);
	for (int i = 0; i < 360; i = i + 30) {
		int j = i + 180;
		Line(300 + r * cos(i*6.28318 / 360), 200 + r * sin(i*6.28318 / 360), 300 + r * cos(j*6.28318 / 360), 200 + r * sin(j*6.28318 / 360), 0xFF0000, 1);
	}
	
	//Rect(10, 10, 600, 200, 0x00FF00, 10);
	
	Circle(300, 200, 100, 0x0000FF, 3);
	Circle(300, 200, 80, 0x0000FF, 3);
	Circle(300, 200, 60, 0x0000FF, 3);
	Circle(300, 200, 40, 0x0000FF, 3);
	Circle(300, 200, 20, 0x0000FF, 3);
	Rose(300, 200, 100, 0x0000FF, 3);
	int chx = 700;
	int chy = 500;
	int rh = 1;
	for (int i = 0; i < 9; i++) {
		if (i % 2 == 0) {
			UpHalfCircle(chx, chy, rh*pow(2,i), 0x0000FF, 3);
			chx = chx - rh * pow(2, i);
		}
		else {
			DownHalfCircle(chx, chy, rh*pow(2, i), 0x0000FF, 3);
			chx = chx + rh * pow(2, i);
		}
			
	}
	
}



//滑鼠按下: 紀錄按下狀態 Flag = TRUE，以及按下之座標 (bx, by)
void CPowerPointDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	Flag = TRUE;
	Tag = FALSE;
	bx = point.x; by = point.y;
	ex = bx; ey = by;
	
	
	CDialogEx::OnLButtonDown(nFlags, point);
}

//滑鼠放開: 紀錄按下狀態 Flag = FALSE
void CPowerPointDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	Flag = FALSE;
	Tag = TRUE;
	B[i].x = bx;
	B[i].y = by;
	E[i].x = ex;
	E[i].y = ey;
	i++;
	
	CDialogEx::OnLButtonUp(nFlags, point);
	
}

//滑鼠移動: 若Flag == TRUE，塗銷舊線，畫新線

void CPowerPointDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	int midx;
	int midy;
	int dia;
	int radius;
	for (int j = 0; j < i; j++) {
		Line(B[j].x, B[j].y, E[j].x, E[j].y, 0x000000, 2);
	}
	if (Flag) {
		if (Tag == FALSE)/*
			Ellipse((bx + ex) / 2, (by + ey) / 2, abs(ex - bx) / 2, abs(ey - by) / 2, 0xF0F0F0, 2); //塗銷
		ex = point.x; ey = point.y;
		Ellipse((bx + ex) / 2, (by + ey) / 2, abs(ex - bx) / 2, abs(ey - by) / 2, 0x00000, 2);
		for (int j=0; j <= i; j++) {
			Ellipse((Bx[j].x + Ex[j].x) / 2, (By[j].y + Ey[j].y) / 2, abs(Ex[j].x - Bx[j].x) / 2, abs(Ey[j].y - By[j].y) / 2, 0x00000, 2);
		}*/
		//畫線跟矩形
		{
			Line(bx, by, ex, ey, 0xF0F0F0, 2);  //塗銷圖案
			for (int j = 0; j < i; j++) {
				Line(B[j].x, B[j].y, E[j].x, E[j].y, 0x000000, 2);
			}
		}
		ex = point.x;
		ey = point.y;                       //更新移動位置
		Line(bx, by, ex, ey, 0x000000, 2);  //黑線
		
		
		/*
		//紀錄滑鼠按下之座標bx, by;
		//紀錄滑鼠最後一次移動位置ex, ey;
		midx = (bx + ex) / 2;
		midy = (by + ey) / 2;
		dia = (int)(((bx - ex) ^ 2 + (by - ey) ^ 2) ^ (1 / 2));
		radius = dia / 2;

		Circle(midx, midy, radius, 0xF0F0F0, 2);
		ex = point.x;
		ey = point.y;
		midx = (bx + ex) / 2;
		midy = (by + ey) / 2;
		dia = (int)(((bx - ex) ^ 2 + (by - ey) ^ 2) ^ (1 / 2));
		radius = dia / 2;
		Circle(midx, midy, radius, 0x00000, 2);
		*/
	}
	
	
	CDialogEx::OnMouseMove(nFlags, point);
}

