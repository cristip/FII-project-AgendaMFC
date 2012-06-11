// AddNewContactDialog.cpp : implementation file
//

#include "stdafx.h"
#include "proiect_poo_tema_2_agenda_gui_patterns.h"
#include "AddNewContactDialog.h"
#include "ModelAgenda.h"
#include "afxdialogex.h"


// AddNewContactDialog dialog

IMPLEMENT_DYNAMIC(AddNewContactDialog, CDialogEx)

AddNewContactDialog::AddNewContactDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddNewContactDialog::IDD, pParent)
{
	
}

AddNewContactDialog::~AddNewContactDialog()
{
}

void AddNewContactDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, firstNameTxt);
	DDX_Control(pDX, IDC_EDIT2, lastNameTxt);
	DDX_Control(pDX, IDC_EDIT3, phoneTxt);
	DDX_Control(pDX, IDC_COMBO1, contactTypeCmb);
	DDX_Control(pDX, IDC_EDIT4, extraInfoTxt);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, dateTimePicker);
}


BEGIN_MESSAGE_MAP(AddNewContactDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddNewContactDialog::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &AddNewContactDialog::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()




BOOL AddNewContactDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString item1, item2, item3;
	item1.LoadStringW(IDS_STRING132);
	item2.LoadStringW(IDS_STRING133);
	item3.LoadStringW(IDS_STRING134);

	contactTypeCmb.AddString(item1);
	contactTypeCmb.AddString(item2);
	contactTypeCmb.AddString(item3);
	return TRUE;
}

// AddNewContactDialog message handlers

void AddNewContactDialog::OnBnClickedOk()
{

	if(firstNameTxt.GetWindowTextLengthW() == 0 || lastNameTxt.GetWindowTextLengthW() == 0)
	{
		MessageBox(_T("Pentru a adăuga un contact, introduceți măcar numele și prenumele!"), _T("Date invalide"), MB_ICONASTERISK);
		return;
	}

	Contact * contact = new Contact();
	TCHAR firstName[50];
	TCHAR lastName[50];
	TCHAR phone[50];
	TCHAR extraInfo[50];

	firstNameTxt.GetWindowTextW(firstName, 50);
	lastNameTxt.GetWindowTextW(lastName, 50);
	phoneTxt.GetWindowTextW(phone, 50);
	
	if(contactTypeCmb.GetCurSel() == 0)
	{
		//dateTimePicker.GetWindowTextW(extraInfo, 50);
		CTime time;
		DWORD result = dateTimePicker.GetTime(time);
		contact->setBirthday(time);
	}else
	{
		extraInfoTxt.GetWindowTextW(extraInfo, 50);
		contact->setExtraInfo(extraInfo);
	}

	
	contact->setFirstName(firstName);
	contact->setLastName(lastName);
	contact->setPhoneNumber(phone);
	contact->setContactType(contactTypeCmb.GetCurSel());
	

	Agenda::getInstance().addContact(*contact);

	CDialogEx::OnOK();
}


void AddNewContactDialog::OnCbnSelchangeCombo1()
{
	if(contactTypeCmb.GetCurSel() == 0)
	{
		dateTimePicker.ShowWindow(SW_NORMAL);
		extraInfoTxt.ShowWindow(SW_HIDE);
		SetDlgItemText(IDC_STATIC11,_T("Data nașterii"));
	}else
	{
		dateTimePicker.ShowWindow(SW_HIDE);
		extraInfoTxt.ShowWindow(SW_NORMAL);
		SetDlgItemText(IDC_STATIC11,_T("Alte informații"));
	}
}

