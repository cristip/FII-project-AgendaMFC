#include "stdafx.h"
#include "ModelContact.h"
#include "resource.h"		// main symbols



Contact::Contact()
{
	dataNasterii = NULL;
}

Contact::~Contact()
{
	//for debug purpose
}

void Contact::setFirstName(const CString& newFirstName)
{
	prenume = newFirstName;
}
CString Contact::getFirstName()
{
	return prenume;
};
void Contact::setLastName(const CString& newLastName)
{
	nume = newLastName;
}
CString Contact::getLastName()
{
	return nume;
}
void Contact::setContactType(const CString& newContactType)
{
	tipContact = newContactType;
}
void Contact::setContactType(int type)
{
	if(type < 0 || type > 2)
	{
		//throw new Error or smth...
		return;
	}
	tipContactKey = type;
	CString strTip;
	switch(type)
	{
	case Contact::FRIEND:
		strTip.LoadStringW(IDS_STRING132);
		break;
	case Contact::COLLEAGUE:
		strTip.LoadStringW(IDS_STRING133);
		break;
	case Contact::ACQUAINTANCE:
		strTip.LoadStringW(IDS_STRING134);
		break;
	}	
	setContactType(strTip);
}
CString Contact::getContactType()
{
	return tipContact;
}

int Contact::getContactTypeIndex()
{

	/*if(tipContact == FRIEND)
	{
		return 0;
	}
	if(tipContact == COLLEAGUE)
	{
		return 1;
	}
	return 2;
	*/
	return tipContactKey;

}

void Contact::setPhoneNumber(const CString& newPhoneNumber)
{
	telefon = newPhoneNumber;
}
CString Contact::getPhoneNumber()
{
	return telefon;
}
void Contact::setExtraInfo(const CString& newExtraInfo)
{
	extraInfo = newExtraInfo;
}
CString Contact::getExtraInfo()
{
	return extraInfo;
}

CTime Contact::getBirtday()
{
	if(!birthday_set)
	{
		time_t osBinaryTime(_ttoi(extraInfo));
		dataNasterii = CTime(osBinaryTime);
		birthday_set = true;
	}
	return dataNasterii;
}

void Contact::setBirthday(CTime newBirthday)
{
	dataNasterii = CTime(newBirthday);
	time_t osBinaryTime = dataNasterii.GetTime();
	char time_ch[50];
	sprintf(time_ch, "%ld", osBinaryTime);
	CString birthday(time_ch);
	extraInfo = birthday;
	birthday_set = true;

}

CString Contact::toString()
{
	TCHAR* tip = new TCHAR();
	_itow( tipContactKey, tip, 10);
	
	return prenume + SEPARATOR + nume + SEPARATOR + telefon + SEPARATOR + tip + SEPARATOR + extraInfo;
}

Contact * Contact::fromString(const CString& buff)
{
	Contact * c = new Contact();
	int i = 0;
	int property_index = 0;
	CString propertyData;
	while(true)
	{
		if(buff[i] == SEPARATOR || buff[i] == 0)
		{
			switch(property_index)
			{
			case 0:
				//nume
				c->setFirstName(propertyData);
			break;
			case 1:
				//prenume
				c->setLastName(propertyData);
			break;
			case 2:
				//telefon
				c->setPhoneNumber(propertyData);
			break;
			case 3:
				//tip contact
				c->setContactType(StrToInt(propertyData));
			break;
			case 4:
				//extra info
				c->setExtraInfo(propertyData);
			break;

			}
			if(buff[i] == 0)
			{
				break;
			}
			property_index++;
			propertyData.Empty();
			
		}else
		{
			propertyData.AppendChar( buff[i] );
		}
		i++;
	}
	return c;
}
