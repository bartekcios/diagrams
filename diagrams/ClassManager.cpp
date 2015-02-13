#include "stdafx.h"
#include "ClassManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#include <windows.h>
#include <process.h>

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
	//open file
	string line;
	ifstream myfile(a_szFilesPath);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
            //check if line is commented
            std::smatch m;
            std::regex e("([//\*])(.*)(\\()");

            if (!std::regex_search(line, m, e))
            {
                // variables to regex
                std::smatch m;
                std::regex e("^(class )([^ ]*)");
                if (std::regex_search(line, m, e))
                {
                    CClass oClass(m[2], a_szFilesPath, m_pFilesFinder);
                    m_szClassesList.push_back(oClass);
                    line = m.suffix().str();
                    return true;
                }
            }
		}
		myfile.close();
	}
	else
	{
        printf("Unable to open file: %s\n", a_szFilesPath.c_str());
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
    printf("Class list:\n");
	for (int i = 0; i < m_szClassesList.size(); i++)
	{
        printf("Class %s\n", m_szClassesList[i].m_szName.c_str());
		m_szClassesList[i].ShowFunctions();
	}
}

bool CClassManager::FindFunctions()
{
	for (int i = 0; i < m_szClassesList.size(); i++)
	{
        bool fShowTimes = true;
        DWORD t[2];

        if (false != fShowTimes)
        {
            t[0] = GetTickCount();
        }
		m_szClassesList[i].FindFunctions();
        if (false != fShowTimes)
        {
            t[1] = GetTickCount() - t[0];
            printf("FindFunctions: %s :%d\n", m_szClassesList[i].m_szName.c_str(), t[1]);
        }
	}

	return true;
}

void __cdecl ThreadProc(void * Args)
{
    CClass * poClass = (CClass*)Args;
    poClass->FindCalls();

    _endthread();
}

bool CClassManager::FindCallsForFunctions()
{
    vector <HANDLE> hThreadVector;
    for (int i = 0; i < m_szClassesList.size(); i++)
    {
        
        CClass * poClass = &m_szClassesList[i];
        hThreadVector.push_back((HANDLE)_beginthread(ThreadProc, 0, (void*)poClass));
        //m_szClassesList[i].FindCalls();
    }
    WaitForMultipleObjects(hThreadVector.size(), &hThreadVector[0], true, INFINITE);
    printf("\n\n");

    return true;
}
