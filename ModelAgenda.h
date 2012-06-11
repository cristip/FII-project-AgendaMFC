#ifndef MODEL_AGENDA_H
#define MODEL_AGENDA_H

#include "stdafx.h"
#include "ModelContact.h"
#include <iostream>
#include <algorithm>
#include <vector> 

using namespace std;


class Agenda : public ISubject
{
public:
	static Agenda& getInstance()
	{
		static Agenda instance;
		return instance;
	};
	void load(CString);
	void setCurrentFilePath(CString const&);
	CString& getCurrentFilePath();
	void addContact(Contact &);
	void removeContact(Contact &);
	vector <Contact> getContacts();
	Contact& getContactAt(int index);
	bool isSaved;
	CString toString();
	

private:
	Agenda(){};
	//constructorul de copiere si operatorul
	//nu vor fi implementate ca sa nu se poata creea copii
	Agenda(Agenda const&);
	void operator=(Agenda const&);
	CString currentFilePath;
	vector <Contact> contacts;

};

#endif