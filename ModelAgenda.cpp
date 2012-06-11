#include "stdafx.h"
#include "ModelAgenda.h"
#include "ModelContact.h"

/**
 * incarca un fisier cu linii de forma
 * prenume|nume|numar telefon|tip contact|extra data
 */
void Agenda::load(CString buff)
{
	int current_position_in_contact_data = 0;
	int num_of_contacts = 0;
	int i = 0;

	TCHAR contactData[250];

	Contact * contactTemporar;

	while(true)
	{
		if(buff[i] == '\n' || buff[i] == 0)
		{
			contactTemporar = Contact::fromString(contactData);
			addContact(*contactTemporar);
			if(buff[i] == 0)
			{
				break;
			}
			current_position_in_contact_data = 0;
		}else
		{
			contactData[current_position_in_contact_data] = buff[i];
			current_position_in_contact_data++;
		}
		i++;
		contactData[current_position_in_contact_data] = 0;
	}
}
void Agenda::setCurrentFilePath(CString const& newPath)
{
	currentFilePath = newPath;
}
CString& Agenda::getCurrentFilePath()
{
	return currentFilePath;
}

void Agenda::addContact(Contact &contact)
{
	contacts.push_back(contact);
	notifyObservers();
}
void Agenda::removeContact(Contact &contact)
{
	for(int i =0 ; i < contacts.size(); i++)
	{
		Contact &item = contacts.at(i);
		if(&item == &contact)
		{
			contacts.erase(contacts.begin() + i);
			break;
		}
	}
	delete &contact;
	notifyObservers();
}

vector <Contact> Agenda::getContacts()
{
	return contacts;
}

Contact& Agenda::getContactAt(int index)
{
	return contacts.at(index);
}

CString Agenda::toString()
{
	CString value;
	int num_of_contacts = contacts.size();
	for(int i = 0; i < num_of_contacts; i++)
	{
		value += contacts.at(i).toString();
		value += "\n";
	}
	return value;
}
