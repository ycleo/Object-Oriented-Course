
// file_listDlg.cpp: 實作檔案
//
#include <iostream>
#include <cstdlib>
#include "pch.h"
#include "framework.h"
#include "file_list.h"
#include "file_listDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

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


// CfilelistDlg 對話方塊



CfilelistDlg::CfilelistDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILE_LIST_DIALOG, pParent)
	, m_Edit1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CfilelistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_LIST1, m_list1);
}

BEGIN_MESSAGE_MAP(CfilelistDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CfilelistDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CfilelistDlg::OnBnClickedButton2)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CfilelistDlg::OnItemclickList1)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CfilelistDlg::OnColumnclickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CfilelistDlg::OnClickList1)
END_MESSAGE_MAP()


// CfilelistDlg 訊息處理常式
CToolTipCtrl m_TP;
BOOL CfilelistDlg::OnInitDialog()
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
	m_TP.Create(this);
	m_TP.Activate(TRUE);

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CfilelistDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CfilelistDlg::OnPaint()
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
HCURSOR CfilelistDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}
int partition(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j < high; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return(i + 1);
}

void quickSort(int arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}


void CfilelistDlg::OnBnClickedButton1()
{
	//0. initialization
	int S[100][4];  //4 subjects score
	char N[100][10], S1[100]; //names
	errno_t err;
	FILE *f;
	int no = 0;
	//1. open the file
	err = fopen_s(&f, "Book1.txt", "rb");
	if (err != 0) {
		SetWindowText(L"Book1 not found");
		return;
	}
	//2. read the file
	while (!(feof(f))) {
		fscanf_s(f, "%s %d %d %d %d\n", &N[no], 10, &S[no][0], &S[no][1], &S[no][2], &S[no][3]);  //read the content of Book1 to the arrays
		sprintf_s(S1, "%s %d %d %d %d\r\n", N[no], S[no][0], S[no][1], S[no][2], S[no][3]);
		UpdateData(1); 
		m_Edit1 += S1; 
		UpdateData(0);
		no++;
	}
	fclose(f);
}
void Big5toUnicode(char *Big5, wchar_t *Unicode, int Len) {
	MultiByteToWideChar(950, 0, Big5, -1, Unicode, Len + 1);
}
int no = 0;
int S[100][4];    //4 subjects score
char N[100][10];  //names
void CfilelistDlg::OnBnClickedButton2()
{   //0. initialize the list
	m_list1.InsertColumn(0, L"Name");		m_list1.SetColumnWidth(0, 60);
	m_list1.InsertColumn(1, L"English");	m_list1.SetColumnWidth(1, 60);
	m_list1.InsertColumn(2, L"Physics");	m_list1.SetColumnWidth(2, 60);
	m_list1.InsertColumn(3, L"Chemistry");	m_list1.SetColumnWidth(3, 60);
	m_list1.InsertColumn(4, L"History");	m_list1.SetColumnWidth(4, 60);

	  
	char S1[100]; //names
	errno_t err;
	FILE *f;
	
	//1. open the file
	err = fopen_s(&f, "Book1.txt", "rb");
	if (err != 0) {
		SetWindowText(L"Book1 not found");
		return;
	}
	//2. read the file
	wchar_t temp[10];  //English word or number => 2 bytes, (ex) 'A' -> 0x0000 0065
	while (!(feof(f))) {
		fscanf_s(f, "%s %d %d %d %d\n", &N[no], 10, &S[no][0], &S[no][1], &S[no][2], &S[no][3]);  //read the content of Book1 to the arrays
		
		Big5toUnicode(&N[no][0], temp, strlen(&N[no][0]));
		
		m_list1.InsertItem(no, temp);
		for (int i = 0; i < 4; i++) {
			sprintf_s(S1, "%d", S[no][i]);
			Big5toUnicode(S1, temp, strlen(S1));
			m_list1.SetItemText(no, i + 1, temp);
		}
		no++;
	}
	fclose(f);
	
}


void Swap(char Name[][10], int Score[][4], int a, int b) {
	// exchange names
	char T[10];
	strcpy_s(T, &Name[a][0]);
	strcpy_s(&Name[a][0], 10, &Name[b][0]);
	strcpy_s(&Name[b][0], 10, T);

	// exchange scores
	for (int i = 0; i < 4; i++) {
		Score[a][i] += Score[b][i];
		Score[b][i] = Score[a][i] - Score[b][i];
		Score[a][i] -= Score[b][i];
	}
}

// Name[][10]: record names
// Score[][4]: record 4 subjects scores
// N: record number of people
// I: record the column which is going to sort (0: Name, 1~4: Subjects)
// F: sorting Direction (0: decreasing, 1: increasing)
void Sorting(char Name[][10], int Score[][4], int N, int I, int F) {
	int i, j, k;
	// use bubble sort to sort 4 subjects
	if (F == 0) {
		if (I >= 1 && I <= 4) {
			for (i = 0; i < N; i++) {
				for (j = i + 1; j < N; j++) {
					if (Score[i][I - 1] < Score[j][I - 1]) {
						Swap(Name, Score, i, j);
					}
				}
			}
		}
		else {
			for (i = 0; i < N; i++) {
				for (j = 0; j < N - 1; j++) {
					if (strcmp(&Name[i][0], &Name[j][0]) < 0) {
						Swap(Name, Score, i, j);
					}
				}
			}
		}
	}
	else {
		if (I >= 1 && I <= 4) {
			for (i = 0; i < N; i++) {
				for (j = i + 1; j < N; j++) {
					if (Score[i][I - 1] > Score[j][I - 1]) {
						Swap(Name, Score, i, j);
					}
				}
			}
		}
		else {
			for (i = 0; i < N; i++) {
				for (j = 0; j < N - 1; j++) {
					if (strcmp(&Name[i][0], &Name[j][0]) < 0) {
						Swap(Name, Score, i, j);
					}
				}
			}
		}
	}
}

int F = 0;
void CfilelistDlg::OnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//1. get the item number
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	NMLISTVIEW *pLV = (NMLISTVIEW *)pNMHDR;
	int I = pLV->iItem;
	
	//2. sorting the specific item data
	Sorting(N, S, no, I, F);
	F = ~F;
	//re-show
	wchar_t temp[10];
	char S1[100];
	m_list1.DeleteAllItems();

	for (int i = 0; i < no; i++) {
		//add -> name
		Big5toUnicode(&N[i][0], temp, strlen(&N[i][0]));
		m_list1.InsertItem(i, temp);
		//set the 4 subject scores for the name
		for (int j = 0; j < 4; j++) {
			sprintf_s(S1, "%d", S[i][j]);
			Big5toUnicode(S1, temp, strlen(S1));
			m_list1.SetItemText(i, j+1, temp);

		}
	}


	*pResult = 0;
}

//錯誤,多餘函式
void CfilelistDlg::OnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NMLISTVIEW *pLV = (NMLISTVIEW *)pNMHDR;

	int I = pLV->iItem, J=pLV->iSubItem;
	
	if (J == 0 && I >= 0) {
		int T = S[I][0] + S[I][1] + S[I][2] + S[I][3];
		char S1[100];
		wchar_t temp[100];
		sprintf_s(S1, "%s-總分=%d", &N[I][0], T);
		Big5toUnicode(S1, temp, strlen(S1));
		SetWindowText(temp);
		m_TP.AddTool(GetDlgItem(IDC_LIST1), temp, 0, 0);
	}
		*pResult = 0;
}


BOOL CfilelistDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
	if (m_TP.m_hWnd != NULL) m_TP.RelayEvent(pMsg);
	//m_TP.RelayEvent(pMsg);
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CfilelistDlg::OnClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NMLISTVIEW *pLV = (NMLISTVIEW *)pNMHDR;

	int I = pLV->iItem, J = pLV->iSubItem;
	//2. 計算該欄位總分
	if (J == 0 && I >= 0) {
		int T = S[I][0] + S[I][1] + S[I][2] + S[I][3];
		char S1[100];
		wchar_t temp[100];
		sprintf_s(S1, "%s-總分=%d", &N[I][0], T);
		Big5toUnicode(S1, temp, strlen(S1));
		//3. 顯示在視窗title
		SetWindowText(temp);
		//4. 顯示Tool Tip(小提示) 
		m_TP.AddTool(GetDlgItem(IDC_LIST1), temp, 0, 0);
	}
	*pResult = 0;
}
