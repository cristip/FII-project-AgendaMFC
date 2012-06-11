
// AgendaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "proiect_poo_tema_2_agenda_gui_patterns.h"
#include "AgendaDlg.h"
#include "ModelAgenda.h"
#include "ModelContact.h"
#include "AddNewContactDialog.h"
#include "EditContactDialog.h"
#include "AboutDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// AgendaDlg dialog




AgendaDlg::AgendaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AgendaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	isInitialized = false;
}

void AgendaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, contactList);
}

BEGIN_MESSAGE_MAP(AgendaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FI32771, &AgendaDlg::onMenuFileNew)
	ON_COMMAND(ID_FI32772, &AgendaDlg::onMenuFileOpen)
	ON_COMMAND(ID_FI32773, &AgendaDlg::OnMenuFileSave)
	ON_COMMAND(ID_FI32774, &AgendaDlg::OnMenuFileSaveAs)
	ON_COMMAND(ID_FI32775, &AgendaDlg::OnMenuFileExit)
	ON_COMMAND(ID_EDITEAZ32776, &AgendaDlg::OnMenuEditAdd)
	ON_COMMAND(ID_AJUTOR_DESPREAGENDA, &AgendaDlg::OnMenuHelpAbout)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &AgendaDlg::OnNMDblclkList1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// AgendaDlg message handlers

BOOL AgendaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	isInitialized = true;
	Agenda::getInstance().addObserver(this);
	Agenda::getInstance().isSaved = true;
	
	contactList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_REPORT | LVS_EX_AUTOSIZECOLUMNS | LVS_EX_HEADERINALLVIEWS);
	
	
	contactList.InsertColumn(0, _T("Prenume"), LVCFMT_LEFT, 120);
	contactList.InsertColumn(1, _T("Nume"), LVCFMT_LEFT, 120);
	contactList.InsertColumn(2, _T("Telefon"), LVCFMT_LEFT, 80);
	contactList.InsertColumn(3, _T("Tip Contact"), LVCFMT_LEFT, 80);
	contactList.InsertColumn(4, _T("Extra"), LVCFMT_LEFT, 80);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void AgendaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void AgendaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR AgendaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void AgendaDlg::onMenuFileNew()
{
	// TODO: Add your command handler code here
}


void AgendaDlg::onMenuFileOpen()
{
	CFileDialog openFDialog(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("Fisiere text (*.txt)|*.txt"));
	int iRet = openFDialog.DoModal();
	if(iRet != IDOK)
	{
		return;
	}
	CString currentFilePath;
	currentFilePath = openFDialog.GetPathName();
	//salveaza referinta de pe disc in model
	Agenda& agenda = Agenda::getInstance();
	agenda.setCurrentFilePath(currentFilePath);
	

	CStdioFile f;
	
	CFileException e;
	if(!f.Open(currentFilePath,  CFile::modeReadWrite, &e))
	{
		MessageBoxW(_T("Eroare la deschiderea fisierului ")+ currentFilePath);
		return;
	}
	unsigned int dwLength=f.GetLength();
	//char * buff = (char*) malloc(dwLength*sizeof(char));
	//f.Read(buff, dwLength);

	CString buff;
	

	f.ReadString(buff);
	f.Close();
	//buff[dwLength] = 0;
	//USES_CONVERSION;
	//agenda.load(A2T(buff));
	agenda.load(buff);
	agenda.isSaved = true;
}


void AgendaDlg::OnMenuFileSave()
{
	if(Agenda::getInstance().getCurrentFilePath() == "")
	{
		OnMenuFileSaveAs();
		return;
	}
	saveCurrentFile();
}


void AgendaDlg::OnMenuFileSaveAs()
{
	CFileDialog fileDialog(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Fișiere agendă (*.txt)|*.txt"));
	int iRet = fileDialog.DoModal();
	if(iRet != IDOK)
	{
		return;
	}
	Agenda::getInstance().setCurrentFilePath(fileDialog.GetPathName());
	saveCurrentFile();
}

void AgendaDlg::saveCurrentFile()
{
	Agenda &agenda = Agenda::getInstance();
	CString fPath = agenda.getCurrentFilePath();

	
	CFile f;
	CFileException e;


	fPath.MakeLower();

	int extensionPos = fPath.Find(_T(".txt"));
	UINT pathLength = fPath.GetLength();


	if(extensionPos == -1 || extensionPos != pathLength-4)
	{
		fPath += _T(".txt");
	}

	if(!f.Open(fPath,  CFile::modeReadWrite | CFile::modeCreate, &e))
	{
		MessageBoxW(_T("Eroare la deschiderea fișierului ") + fPath);
		return;
	}

	CString agendaStr = agenda.toString();
	
	CT2CA outputString(agendaStr, CP_UTF8); 

	int str_length = strlen(outputString);
	
	f.Write(outputString, str_length);
	f.Close();
	agenda.isSaved = true;
}


void AgendaDlg::OnMenuFileExit()
{
	OnClose();
	CDialog::OnOK();
}

void AgendaDlg::OnClose()
{
	if(!Agenda::getInstance().isSaved)
	{
		int userResponse = MessageBoxW(_T("Agenda curentă are modificari care nu au fost salvate. Doriți salvarea lor?"), _T("Salvați fișierul curent?"), MB_ICONQUESTION | MB_YESNOCANCEL);
		switch(userResponse)
		{
		case IDYES:
			OnMenuFileSave();
			break;
		case IDCANCEL:
			return;
		}
	}
	__super::OnClose();
}

void AgendaDlg::OnMenuEditAdd()
{
	AddNewContactDialog addDialog;
	addDialog.DoModal();
}


void AgendaDlg::OnMenuHelpAbout()
{
	AboutDialog about;
	about.DoModal();
}


void AgendaDlg::OnSize(UINT nType, int cx, int cy)
{
	if(!isInitialized)
	{
		return;
	}
	CDialogEx::OnSize(nType, cx, cy);

	contactList.MoveWindow(7, 39, cx-14, cy-46);
}


void AgendaDlg::Update(void* pSubject)
{
	contactList.DeleteAllItems();
	int i;
	vector <Contact>	 &contacts = Agenda::getInstance().getContacts();
	for(i = 0; i< contacts.size(); i++)
	{
		int nItem;
		Contact &contact = contacts.at(i);
		nItem = contactList.InsertItem(i, contact.getFirstName() );

		contactList.SetItemText(i, 1, contact.getLastName());

		contactList.SetItemText(i, 2, contact.getPhoneNumber());
		contactList.SetItemText(i, 3, contact.getContactType());
		if(contact.getContactType() == Contact::FRIEND)
		{
			contactList.SetItemText(i, 4, contact.getBirtday().Format(_T("%d %B %Y")));
		}else
		{
			contactList.SetItemText(i, 4, contact.getExtraInfo());
		}
	}
}


void AgendaDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int selectedIndex = pNMItemActivate->iItem;
	*pResult = 0;

	Contact& contact = Agenda::getInstance().getContactAt(selectedIndex);
	
	EditContactDialog editDialog;
	editDialog.EditContact(contact);
}



