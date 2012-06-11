// AboutDialog.cpp : implementation file
//

#include "stdafx.h"
#include "proiect_poo_tema_2_agenda_gui_patterns.h"
#include "AboutDialog.h"
#include "afxdialogex.h"


// AboutDialog dialog

IMPLEMENT_DYNAMIC(AboutDialog, CDialogEx)

AboutDialog::AboutDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(AboutDialog::IDD, pParent)
{

}

AboutDialog::~AboutDialog()
{
}

void AboutDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutDialog, CDialogEx)
END_MESSAGE_MAP()


// AboutDialog message handlers
