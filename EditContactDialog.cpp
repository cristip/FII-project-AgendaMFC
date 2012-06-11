// EditContactDialog.cpp : implementation file
//

#include "stdafx.h"
#include "proiect_poo_tema_2_agenda_gui_patterns.h"
#include "EditContactDialog.h"
#include "afxdialogex.h"


// EditContactDialog dialog

IMPLEMENT_DYNAMIC(EditContactDialog, CDialogEx)

EditContactDialog::EditContactDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(EditContactDialog::IDD, pParent)
{

}

EditContactDialog::~EditContactDialog()
{
}

BOOL EditContactDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString item1, item2, item3;
	item1.LoadStringW(IDS_STRING132);
	item2.LoadStringW(IDS_STRING133);
	item3.LoadStringW(IDS_STRING134);

	contactTypeCmb.AddString(item1);
	contactTypeCmb.AddString(item2);
	contactTypeCmb.AddString(item3);

	int contactIndex = contact->getContactTypeIndex();

	contactTypeCmb.SetCurSel(contactIndex);

	firstNameTxt.SetWindowTextW(contact->getFirstName());
	lastNameTxt.SetWindowTextW(contact->getLastName());
	phoneTxt.SetWindowTextW(contact->getPhoneNumber());
	if(contactIndex == 0)
	{
		dateTimePicker.ShowWindow(SW_NORMAL);
		dateTimePicker.SetTime(&contact->getBirtday());

		dateTimePicker.SetWindowTextW(contact->getExtraInfo());
		extraInfoTxt.ShowWindow(SW_HIDE);
		SetDlgItemText(IDC_STATIC11,_T("Data nașterii"));
	}else
	{
		dateTimePicker.ShowWindow(SW_HIDE);
		extraInfoTxt.SetWindowTextW(contact->getExtraInfo());
		extraInfoTxt.ShowWindow(SW_NORMAL);
		SetDlgItemText(IDC_STATIC11,_T("Alte informații"));
		dateTimePicker.SetWindowTextW(contact->getExtraInfo());
	}

	return TRUE;
}


void EditContactDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, firstNameTxt);
	DDX_Control(pDX, IDC_EDIT2, lastNameTxt);
	DDX_Control(pDX, IDC_EDIT3, phoneTxt);
	DDX_Control(pDX, IDC_COMBO1, contactTypeCmb);
	DDX_Control(pDX, IDC_EDIT4, extraInfoTxt);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, dateTimePicker);
}


BEGIN_MESSAGE_MAP(EditContactDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &EditContactDialog::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &EditContactDialog::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &EditContactDialog::OnBnClickedButton1)
END_MESSAGE_MAP()


// EditContactDialog message handlers


void EditContactDialog::EditContact(Contact& contact)
{
	this->contact = &contact;
	this->DoModal();

}

void EditContactDialog::OnBnClickedOk()
{
	if(firstNameTxt.GetWindowTextLengthW() == 0 || lastNameTxt.GetWindowTextLengthW() == 0)
	{
		MessageBox(_T("Pentru a adăuga un contact, introduceți măcar numele, prenumele și tipul contactului!"), _T("Date invalide"), MB_ICONASTERISK);
		return;
	}

	TCHAR firstName[50];
	TCHAR lastName[50];
	TCHAR phone[50];

	TCHAR extraInfo[50];

	firstNameTxt.GetWindowTextW(firstName, 50);
	lastNameTxt.GetWindowTextW(lastName, 50);
	phoneTxt.GetWindowTextW(phone, 50);
	
	if(contactTypeCmb.GetCurSel() == 0)
	{
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
	contact->setExtraInfo(extraInfo);

	Agenda::getInstance().isSaved = false;
	Agenda::getInstance().notifyObservers();

	CDialogEx::OnOK();
}


void EditContactDialog::OnCbnSelchangeCombo1()
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


void EditContactDialog::OnBnClickedButton1()
{
	int userResponse = MessageBoxW(_T("Confirmaţi ştegerea contactului ") + contact->getFirstName() + _T(" ") + contact->getLastName(), _T("Ştergeţi contactul?"), MB_ICONQUESTION | MB_YESNOCANCEL); 
	switch(userResponse)
	{
	case IDYES:
		Agenda::getInstance().removeContact(*contact);
		CDialog::OnOK();
		break;
	case IDCANCEL:
		return;
	}
}
