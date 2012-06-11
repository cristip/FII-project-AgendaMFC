#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// AddNewContactDialog dialog

class AddNewContactDialog : public CDialogEx
{
	DECLARE_DYNAMIC(AddNewContactDialog)

public:
	AddNewContactDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddNewContactDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit firstNameTxt;
	CEdit lastNameTxt;
	CEdit phoneTxt;
	CComboBox contactTypeCmb;
	CEdit extraInfoTxt;
	afx_msg void OnBnClickedOk();
	CDateTimeCtrl dateTimePicker;
	afx_msg void OnCbnSelchangeCombo1();
};
