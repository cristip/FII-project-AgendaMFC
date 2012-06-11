// File: observer.h

#ifndef OBSERVER_H
#define OBSERVER_H

#include "stdafx.h"
#include<iostream>
#include <algorithm>
#include<vector> 

using namespace std;

// interfata de observator
class IObserver 
{
public:
	// update
	virtual void Update(void* pSubject) = 0;
	virtual ~IObserver(){};
}; 

// interfata de subiect
struct ISubject 
{
	// observatorii
	vector<IObserver*> allObservers;

	// addObserver 
	void addObserver(IObserver* newObserver)
	{
		allObservers.push_back(newObserver);
		return;
	}

	// removeObserver 
	void removeObserver(IObserver* oldObserver)
	{
		allObservers.erase( remove(allObservers.begin(),allObservers.end(), oldObserver), allObservers.end());
		return;
	}

 
	// notifyObservers 
	void notifyObservers() 
	{ 
		for (	vector<IObserver*>::const_iterator observer_iterator = allObservers.begin();
				observer_iterator != allObservers.end();
				++observer_iterator
			) 
		{
			(*observer_iterator)->Update( this); 
		}
		
		return;
	}

	virtual ~ISubject(){};
};

#endif
