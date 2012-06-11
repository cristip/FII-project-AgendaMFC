#pragma once

#include "ModelAgenda.h"
#include "afxwin.h"
#include "afxdtctl.h"

// EditContactDialog dialog

class EditContactDialog : public CDialogEx
{
	DECLARE_DYNAMIC(EditContactDialog)

public:
	EditContactDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~EditContactDialog();

	void EditContact(Contact& contact);

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	Contact * contact;
	DECLARE_MESSAGE_MAP()
public:
	CEdit firstNameTxt;
	CEdit lastNameTxt;
	CEdit phoneTxt;
	CComboBox contactTypeCmb;
	CEdit extraInfoTxt;
	CDateTimeCtrl dateTimePicker;
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
};
