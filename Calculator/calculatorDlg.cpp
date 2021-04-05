
// calculatorDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "calculator.h"
#include "calculatorDlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

double Eval2(char *expr, char **end) {
	double Eval0(char*, char**);
	double res = 0;
	if (*(*end = expr) == '(') {
		res = Eval0(*end + 1, end);
		if (**end == ')')++*end;
	}
	else { res = strtod(*end, end); }
	return res;
}

double Eval1(char* expr, char** end) {
	double res = Eval2(expr, end);
	while (**end == '*' || **end == '/')
		(**end == '*') ? (res *= Eval2(*end + 1, end)) : (res /= Eval2(*end + 1, end));
	return res;
}

double Eval0(char* expr, char** end) {
	double res = Eval1(expr, end);
	while (**end == '+' || **end == '-')
		res += (**end == '+') ? Eval1(*end + 1, end) : -Eval1(*end + 1, end);
	return res;
}

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


// CcalculatorDlg 對話方塊



CcalculatorDlg::CcalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, m_Edit1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_Edit1);
}

BEGIN_MESSAGE_MAP(CcalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT2, &CcalculatorDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &CcalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CcalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CcalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON10, &CcalculatorDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON4, &CcalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CcalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CcalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CcalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CcalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CcalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON14, &CcalculatorDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CcalculatorDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CcalculatorDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON23, &CcalculatorDlg::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON25, &CcalculatorDlg::OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON26, &CcalculatorDlg::OnBnClickedButton26)
	ON_BN_CLICKED(IDC_BUTTON24, &CcalculatorDlg::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON22, &CcalculatorDlg::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON13, &CcalculatorDlg::OnBnClickedButton13)
END_MESSAGE_MAP()


// CcalculatorDlg 訊息處理常式

BOOL CcalculatorDlg::OnInitDialog()
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
	SetWindowText(L"Calculator, Designer: Leo Lee");
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CcalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcalculatorDlg::OnPaint()
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
HCURSOR CcalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CcalculatorDlg::Add(int a, int b)
{
	return(a + b);
}


void CcalculatorDlg::OnEnChangeEdit2()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼
}

void CcalculatorDlg::OnBnClickedButton10()
{
	UpdateData(1); //開啟變數/視窗資料交換   
	m_Edit1 += '0';
	UpdateData(0);  //關閉變數/視窗資料交換
}

void CcalculatorDlg::OnBnClickedButton1()
{ UpdateData(1); m_Edit1 += '1';  SetWindowText(L"You Press 1");  UpdateData(0); }
void CcalculatorDlg::OnBnClickedButton2()
{ UpdateData(1); m_Edit1 += '2';  UpdateData(0);}
void CcalculatorDlg::OnBnClickedButton3()
{ UpdateData(1); m_Edit1 += '3';  UpdateData(0);}
void CcalculatorDlg::OnBnClickedButton4()
{ UpdateData(1); m_Edit1 += '4';  UpdateData(0);}
void CcalculatorDlg::OnBnClickedButton5()
{ UpdateData(1); m_Edit1 += '5';  UpdateData(0);}
void CcalculatorDlg::OnBnClickedButton6()
{ UpdateData(1); m_Edit1 += '6';  UpdateData(0);}
void CcalculatorDlg::OnBnClickedButton7()
{ UpdateData(1); m_Edit1 += '7';  UpdateData(0);}

void CcalculatorDlg::OnBnClickedButton8()
{ UpdateData(1); m_Edit1 += '8';  UpdateData(0);}

void CcalculatorDlg::OnBnClickedButton9()
{ UpdateData(1); m_Edit1 += '9';  UpdateData(0);}

void CcalculatorDlg::OnBnClickedButton14()   //+
{ UpdateData(1); m_Edit1 += '+';  UpdateData(0);}


void CcalculatorDlg::OnBnClickedButton15()  //-
{ UpdateData(1); m_Edit1 += '-';  UpdateData(0);}

void CcalculatorDlg::OnBnClickedButton16()   //x
{ UpdateData(1); m_Edit1 += '*';  UpdateData(0);}


void CcalculatorDlg::OnBnClickedButton23() // ÷
{ UpdateData(1); m_Edit1 += '/';  UpdateData(0);}

void CcalculatorDlg::OnBnClickedButton25() // (
{ UpdateData(1); m_Edit1 += '(';  UpdateData(0);}


void CcalculatorDlg::OnBnClickedButton26()  // )
{ UpdateData(1); m_Edit1 += ')';  UpdateData(0);}

void CcalculatorDlg::OnBnClickedButton13()  // =
{	
	char In[100];   //四則運算式
	char Out[100];  //答案
	wchar_t B[100];
	// 1. 將m_Edit1的wchar_t*格式轉成 char*
	int i, j;
	i = m_Edit1.GetLength();
	for (j = 0; j <= i; j++) In[j] = (char)m_Edit1.GetAt(j);

	// 2. 做四則運算
	Op(In, Out);

	// 3. 將答案從 char* 轉成wchar_t*
	for (j = 0; j <= strlen(Out); j++)
		B[j] = (wchar_t)Out[j];

	// 4. 顯示答案
	UpdateData(1); m_Edit1 = B;   UpdateData(0);
}
void CcalculatorDlg::OnBnClickedButton24()  // <=
{
	UpdateData(1);
	int i = m_Edit1.GetLength();
	if(i) m_Edit1.SetAt(i - 1, 0x0000);
	UpdateData(0);
}

void CcalculatorDlg::OnBnClickedButton22()  //C
{ UpdateData(1); m_Edit1 = "";  UpdateData(0);}

char A[100]; //100 Bytes string (1 byte char)
wchar_t B[100]; //200 Bytes string (2 bytes char)

void CcalculatorDlg::Op(char *In, char *Out)  //四則運算
{
	float a, b;
	float c = 0;
	//char expr[128] = { 0 }, *pos = 0;
	char *pos = 0;
	//printf("Exp : ");
	//scanf("%s", In);
	//printf("Ans : %f\n", Eval0(In, &pos));
	//1. 簡易版,個位數的四則運算

	//a = (float)(In[0] - 0x30);
	//b = (float)(In[2] - 0x30);
	//if		(In[1] == '+') { c = a + b; }
	//else if (In[1] == '-') { c = a - b; }
	//else if (In[1] == '*') { c = a * b; }
	//else if (In[1] == '/') { c = a / b; }
	sprintf_s(Out, 99, "%f", Eval0(In, &pos));
}
//printf: 列印到螢幕上
//fprintf: 列印到檔案上
//sprintf: 列印到字串陣列上
