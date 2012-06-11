
// AgendaDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "observer.h"


// AgendaDlg dialog
class AgendaDlg : public CDialogEx, public IObserver
{
// Construction
public:
	AgendaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PROIECT_POO_TEMA_2_AGENDA_GUI_PATTERNS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void Update(void* pSubject);

// Implementation
protected:
	HICON m_hIcon;
	bool isInitialized;
	void saveCurrentFile();
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void onMenuFileNew();
	afx_msg void onMenuFileOpen();
	afx_msg void OnMenuFileSave();
	afx_msg void OnMenuFileSaveAs();
	afx_msg void OnMenuFileExit();
	afx_msg void OnMenuEditAdd();
	afx_msg void OnMenuHelpAbout();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// lista care afiseaza contactele pe fereastra principala
	CListCtrl contactList;
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
};
