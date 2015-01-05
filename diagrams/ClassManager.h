#pragma once
#include "FilesFinder.h"
#include "Class.h"
#include <vector>
#include <string>

using namespace std;
class CClassManager
{
public:
	CClassManager(CFilesFinder * a_pFilesFinder);
	~CClassManager();
	bool FindAllClasses();								// search all classes from FilesFInder m_VectorOfFilesH
	void ShowAllClasses();								// shows all classes 
	bool FindFunctions();								// search functions in all classes
    bool FindCallsForFunctions();                       // search calls for each function in each class
protected:
	std::vector <CClass> m_szClassesList;				// list of found and created classes

private:
	CFilesFinder * m_pFilesFinder;						// pointer to CFilesFinder, used to get files pathes
	bool FindClass(string a_szFilesPath);				// search class inside a_szFilesPath file
};