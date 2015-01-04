#include "stdafx.h"
#include "ClassManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

CClassManager::CClassManager(CFilesFinder * a_pFilesFinder)
:m_pFilesFinder(a_pFilesFinder)
{
}

CClassManager::~CClassManager()
{
}

bool CClassManager::FindClass(string a_szFilesPath)
{
	// variables to regex
	std::smatch m;
	std::regex e("^(class )([^ ]*)");   // matches words beginning by "sub"

	//open file
	string line;
	ifstream myfile(a_szFilesPath);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			while (std::regex_search(line, m, e)) 
			{
				CClass oClass(m[2], a_szFilesPath, m_pFilesFinder);
				m_szClassesList.push_back(oClass);
				line = m.suffix().str();
			}
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file: " << a_szFilesPath << endl;
		return false;
	}
	return true;
}

bool CClassManager::FindAllClasses()
{
	bool fRetVal = true;
	for (int i = 0; i < m_pFilesFinder->m_VectorOfFilesH.size(); i++)
	{
		fRetVal &= FindClass(m_pFilesFinder->m_VectorOfFilesH[i].szPathToFile);
	}

	return fRetVal;
}

void CClassManager::ShowAllClasses()
{
	cout << "Class List:" << endl;
	for (int i = 0; i < m_szClassesList.size(); i++)
	{
		cout << "Class: " << m_szClassesList[i].m_szName << endl;
		m_szClassesList[i].ShowFunctions();
	}
}

bool CClassManager::FindFunctions()
{
	for (int i = 0; i < m_szClassesList.size(); i++)
	{
		m_szClassesList[i].FindFunctions();
	}

	return true;
}