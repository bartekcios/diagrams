#include "stdafx.h"
#include "Class.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

CClass::CClass(string a_szName, string a_szFilesPathH, CFilesFinder * a_pFilesFinder)

{
	m_szName = a_szName;
	m_szFilesPathH = a_szFilesPathH;
	m_pFilesFinder = a_pFilesFinder;

	int iPosition = m_szFilesPathH.size();
	for (int i = iPosition-1; i > 0; i--)
	{
		if ('\\' == m_szFilesPathH[i])
		{
			iPosition = i + 1;
			break;
		}
	}
	char * temp = &m_szFilesPathH[0];
	m_szFilesHName = m_szFilesPathH.substr(iPosition, m_szFilesPathH.size()-iPosition-2);
	
	if (false == FindCPPFile())
	{
		cout << "[WARR]: not found cpp file" << endl;
	}
}

CClass::~CClass()
{
}

bool CClass::FindFunctions()
{
	// variables to regex
	std::smatch m;
	std::regex e("([^ ]*)([a-zA-Z]*)(\\()");   // matches words beginning by "sub"

	//open file
	string line;
	ifstream myfile(m_szFilesPathH);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			while (std::regex_search(line, m, e))
			{
				if ("(" != m[0] && "$(" != m[0])
				{
					
					//check if exists 
					bool fExists = false;
					for (int i = 0; i < m_funcFunctions.size(); i++)
					{
						if (m[0] == m_funcFunctions[i].szName)
						{
							fExists = true;
						}
					}
					if (false == fExists)
					{
						SFunction sFunction;
						sFunction.szName = m[0];
						m_funcFunctions.push_back(sFunction);
					}
				}
				
				line = m.suffix().str();
			}
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file: " << m_szFilesPathH << endl;
		return false;
	}
	return true;
}

bool CClass::FindCalls()
{
	//open file
	string line;
	ifstream myfile(m_szFilesPathCPP);
	if (myfile.is_open())
	{
		bool fFound = false;					// if function found
		while (getline(myfile, line))
		{
			//if function is not found
			if (false == fFound)
			{

				// check each line for all functions
				for (int i = 0; i < m_funcFunctions.size(); i++)
				{

					// variables to regex, every line should be searched
					int iCounter = 0;										// No found functions
					std::smatch m;
					std::regex e(m_funcFunctions[i].szName);
					while (std::regex_search(line, m, e))
					{
						iCounter++;
						line = m.suffix().str();
					}
					if (0 != iCounter)
					{
						fFound == true;
					}
				}
			}
			else
			{

			}
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file: " << m_szFilesPathH << endl;
		return false;
	}
	return true;
}

bool CClass::FindCPPFile()
{
	for (int i = 0; i < m_pFilesFinder->m_VectorOfFilesCPP.size(); i++)
	{
		if (m_szFilesHName == m_pFilesFinder->m_VectorOfFilesCPP[i].szNameOfFile)
		{
			m_szFilesPathCPP = m_pFilesFinder->m_VectorOfFilesCPP[i].szPathToFile;
			cout << m_szFilesPathCPP << endl;
			return true;
		}
	}

	return false;
}

void CClass::ShowFunctions()
{
	for (int i = 0; i < m_funcFunctions.size(); i++)
	{
		cout << m_funcFunctions[i].szName << endl;
	}
	return;
}