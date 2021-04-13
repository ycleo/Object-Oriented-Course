
// BitmapDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "Bitmap.h"
#include "BitmapDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CBitmapDlg 對話方塊



CBitmapDlg::CBitmapDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BITMAP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBitmapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBitmapDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CBitmapDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CBitmapDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CBitmapDlg 訊息處理常式

BOOL CBitmapDlg::OnInitDialog()
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

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CBitmapDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBitmapDlg::OnPaint()
{
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
HCURSOR CBitmapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBitmapDlg::OnBnClickedButton1()
{
	//1. 開啟(*.BMP)檔案
	errno_t err;
	FILE *In;
	err = fopen_s(&In, "yo.bmp", "rb");
	if (err != 0) {
		SetWindowText(L"File not Found:");
		return;
	}
	else
		SetWindowText(L"File open success!");
	//2. 讀取 width & height
	int Width, Height;
	unsigned char UCBuf[54];
	fread(UCBuf, 1, 54, In);   //一次讀完file header & info header: 54 bytes
	Width = ((int)UCBuf[18] << 0) + ((int)UCBuf[19] << 8) + ((int)UCBuf[20] << 16) + ((int)UCBuf[21] << 24);
	Height = ((int)UCBuf[22] << 0) + ((int)UCBuf[23] << 8) + ((int)UCBuf[24] << 16) + ((int)UCBuf[25] << 24);

	//3. 繪出圖形
	HDC hdc = ::GetDC(m_hWnd);		//
	int x, y, z;
	z = (4 - ((Width * 3) % 4)) % 4;
	for (y = 0;y < Height;y++) {		//垂直掃描線
		for (x = 0;x < Width;x++) {		//水平掃描線
			fread(UCBuf, 1, 3, In);		//讀取RGB data
			/*換色 red([2]) --> green([1])
			if ((UCBuf[2] > 128) && (UCBuf[1] < 128) && (UCBuf[0] < 128)) {  //檢查red是否過半
				UCBuf[3] = UCBuf[1];  //UCBuf[3] is tmp
				UCBuf[1] = UCBuf[2]; 
				UCBuf[2] = UCBuf[3];
			}
			*/
		    //換色 white -- > green([1])
			if ((UCBuf[2] > 228) && (UCBuf[1] > 228) && (UCBuf[0] > 228)) {  
				UCBuf[0] = 0;  
				UCBuf[1] = 255;
				UCBuf[2] = 0;
			}

			CPen P(PS_SOLID, 1, RGB(UCBuf[2], UCBuf[1], UCBuf[0])); //color setting
			SelectObject(hdc, P);  //色筆
			MoveToEx(hdc, x, Height - y, 0); LineTo(hdc, x + 1, Height - y);  //畫圖
		}
		fread(UCBuf, 1, z, In);
	}
	
	
}




void CBitmapDlg::OnBnClickedButton2() //快速畫
{
	//1. 讀檔案
	//2. 取得寬高
	errno_t err;
	FILE *In;
	err = fopen_s(&In, "yo.bmp", "rb");
	if (err != 0) {
		SetWindowText(L"File not Found:");
		return;
	}
	else
		SetWindowText(L"File open success!");
	
	int Width, Height;
	unsigned char UCBuf[54];
	fread(UCBuf, 1, 54, In);   //一次讀完file header & info header: 54 bytes
	Width = ((int)UCBuf[18] << 0) + ((int)UCBuf[19] << 8) + ((int)UCBuf[20] << 16) + ((int)UCBuf[21] << 24);
	Height = ((int)UCBuf[22] << 0) + ((int)UCBuf[23] << 8) + ((int)UCBuf[24] << 16) + ((int)UCBuf[25] << 24);


	//3. 宣告記憶體
	unsigned char *lp = (unsigned char *)malloc((Width+1)* 3 * Height);

	//4. 讀取圖案
	fread(lp, Width * 3, Height, In);
	//5. 快速繪圖
	Draw_BitMap(Width, Height, 0, 0, lp);
}

// =============================================================
// === Draw_BitMap()
// =============================================================
int CBitmapDlg::Draw_BitMap(int x, int y, int PX, int PY, unsigned char *Data)//x=寬 y=長  PX=x軸起始點 PY=y軸起始點
{
	char ErrMsg[200];
	HDC        hdc;
	HDRAWDIB   hdd;
	BITMAPINFO bmpinfo;

	// ====== Draw Init ================= 
	bmpinfo.bmiHeader.biSize = 40;
	bmpinfo.bmiHeader.biWidth = x;
	bmpinfo.bmiHeader.biHeight = y;
	bmpinfo.bmiHeader.biPlanes = 1;
	bmpinfo.bmiHeader.biBitCount = 24;
	bmpinfo.bmiHeader.biCompression = 0;
	bmpinfo.bmiHeader.biSizeImage = x * y * 3;
	bmpinfo.bmiHeader.biXPelsPerMeter = 0;
	bmpinfo.bmiHeader.biYPelsPerMeter = 0;
	bmpinfo.bmiHeader.biClrUsed = 0;
	bmpinfo.bmiHeader.biClrImportant = 0;

	if (!(hdd = DrawDibOpen()))
	{
		strcpy_s(ErrMsg, "DrawDipOpen Error!"); return -1;
	}
	if (!(hdc = ::GetDC(m_hWnd)))
	{
		strcpy_s(ErrMsg, " GetDC Error!"); return -1;
	}
	if (!DrawDibBegin(hdd, hdc, -1, -1, &bmpinfo.bmiHeader, x, y, NULL))
	{
		strcpy_s(ErrMsg, "DrawDibBegin error!"); return -1;
	}
	if (!DrawDibDraw(hdd, hdc, PX, PY, x, y, &bmpinfo.bmiHeader, Data, 0, 0, x, y, DDF_SAME_DRAW | DDF_SAME_HDC))
	{
		strcpy_s(ErrMsg, "DrawDibDraw error"); return -1;
	}
	if (!DrawDibEnd(hdd))
	{
		strcpy_s(ErrMsg, "initDisplay DrawDibBegin Error!"); return -1;
	}
	return 0;
}