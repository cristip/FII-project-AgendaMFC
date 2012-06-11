
// proiect_poo_tema_2_agenda_gui_patterns.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// AgendaApp:
// See proiect_poo_tema_2_agenda_gui_patterns.cpp for the implementation of this class
//

class AgendaApp : public CWinApp
{
public:
	AgendaApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern AgendaApp theApp;