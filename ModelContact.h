#ifndef MODEL_CONTACT_H
#define MODEL_CONTACT_H

#include "stdafx.h"
#include "observer.h"




class Contact	
{
public:

	/*static const CString FRIEND;
	static const CString COLLEAGUE;
	static const CString ACQUAINTANCE;
	*/
	static enum CONTACT_TYPE{
		FRIEND, COLLEAGUE, ACQUAINTANCE
	};

	Contact();

	void setFirstName(const CString& newFirstName);
	CString getFirstName();
	void setLastName(const CString& newLastName);
	CString getLastName();
	void setContactType(const CString& newContactType);
	void setContactType(const int type);
	CString getContactType();
	int getContactTypeIndex();
	void setPhoneNumber(const CString& newPhoneNumber);
	CString getPhoneNumber();
	void setExtraInfo(const CString& newExtraInfo);
	CString getExtraInfo();
	CTime getBirtday();
	void setBirthday(CTime newBirthday);
	static const TCHAR SEPARATOR = '|';
	static Contact * fromString(const CString& newName);
	CString toString();

	~Contact();

private:
	CString nume;
	CString prenume;
	CString tipContact;
	int tipContactKey;
	CString telefon;
	CString extraInfo;
	CTime dataNasterii;
	bool birthday_set;
	
};
#endif