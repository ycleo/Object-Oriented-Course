
// file_listDlg.h: 標頭檔
//

#pragma once


// CfilelistDlg 對話方塊
class CfilelistDlg : public CDialogEx
{
// 建構
public:
	CfilelistDlg(CWnd* pParent = nullptr);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILE_LIST_DIALOG };
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
	CString m_Edit1;
	afx_msg void OnBnClickedButton1();
	CListCtrl m_list1;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
