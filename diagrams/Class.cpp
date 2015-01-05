#include "stdafx.h"
#include "Class.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <windows.h>

using namespace std;

CClass::CClass(string a_szName, string a_szFilesPathH, CFilesFinder * a_pFilesFinder)

{
	m_szName = a_szName;
	m_szFilesPathH = a_szFilesPathH;
	m_pFilesFinder = a_pFilesFinder;

    //cut m_szFilesPathH to file.h
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
    // copy file name without .h part
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
    //open file
	string line;
	ifstream myfile(m_szFilesPathH);
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
                std::regex e("([^ ]*)(\w*)(\\()");
                if (std::regex_search(line, m, e))
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
        // variables to regex, every line should be searched, creates string with all functions in form ::f|::f1|::f2...
        string szConditions = "";
        for (int i = 0; i < m_funcFunctions.size(); i++)
        {
            szConditions += "(";
            szConditions += m_funcFunctions[i].szName;
            szConditions.erase(szConditions.size() - 1, 1);
            szConditions += ")";
            if (m_funcFunctions.size() - 1 != i)
            {
                szConditions += "|";
            }
        }
        //cout << szConditions << endl << endl;
        
        std::smatch m;
        std::regex e(szConditions);
        int iCurrFuncId = 0;
		bool fFound = false;					                    // if function found

        int iCounterPrev = 0;										// No { chars
        int iCounterNext = 0;										// No } chars
        int iLinesCounter = 0;
		while (getline(myfile, line))
		{
            iLinesCounter++;
			//if function is not found
			if (false == fFound)
			{
				if (std::regex_search(line, m, e))
				{
                    // if any function found search which one
                    for (int i = 0; i < m_funcFunctions.size(); i++)
                    {
                        
                        // correct string to regex form ( char
                        string szCondition = "::";
                        szCondition += m_funcFunctions[i].szName;

                        szCondition.erase(szCondition.size()-1, 1);

                        std::smatch mFind;
                        std::regex eFind(szCondition);
                        if (std::regex_search(line, mFind, eFind))
                        {
                            cout << iLinesCounter << mFind[0] << mFind[1] << mFind[2] << endl;
                            iCurrFuncId = i;
                            fFound = true;
                            break;
                        }
                    }

					line = m.suffix().str();
				}
			}
			else
			{
                // if found - search calls

                std::smatch mPrev;
                std::regex ePrev("\\{");
                string linePrev = line;
                std::smatch mNext;
                std::regex eNext("\\}");
                string lineNext = line;

                // count No {} chars
                while (std::regex_search(linePrev, mPrev, ePrev))
                {
                    //cout << "found {" << endl;
                    //cout << iCounterPrev;
                    ++iCounterPrev;
                    //cout << iCounterPrev << endl;
                    linePrev = mPrev.suffix().str();
                }
                while (std::regex_search(lineNext, mNext, eNext))
                {
                    //cout << "found }" << endl;
                    iCounterNext++;
                    lineNext = mNext.suffix().str();
                }

                // check each line for all functions - firstly for all functions, after that each function
                // variables to regex, every line should be searched, creates string with all functions in form f|f1|f2...
                string szConditions = "";
                for (int i = 0; i < m_funcFunctions.size(); i++)
                {
                    szConditions += "(";
                    szConditions += m_funcFunctions[i].szName;
                    szConditions[szConditions.size() - 1] = '\\';
                    szConditions += '(';
                    szConditions += ")";
                    if (m_funcFunctions.size() - 1 != i)
                    {
                        szConditions += "|";
                    }
                }
                std::smatch mAll;
                std::regex eAll(szConditions);
                if (std::regex_search(line, mAll, eAll) && 0 != iCounterPrev)
                {
                    for (int i = 0; i < m_funcFunctions.size(); i++)
                    {
                        string szEach = m_funcFunctions[i].szName;
                        szEach[szEach.size() - 1] = '\\';
                        szEach += '(';
                        std::regex eEach(szEach);
                        

                        while (std::regex_search(line, m, eEach))
                        {
                            int iCallsFuncId = 0;
                            //find function
                            for (int j = 0; j < m_funcFunctions.size(); j++)
                            {
                                if (m_funcFunctions[j].szName == m[0])
                                {
                                    iCallsFuncId = j;
                                    break;
                                }
                            }
                            // puts call function to callers vector
                            m_funcFunctions[iCurrFuncId].funcCalls.push_back(m_funcFunctions[iCallsFuncId]);
                            // puts callers function to calls vector
                            m_funcFunctions[iCallsFuncId].funcCallers.push_back(m_funcFunctions[iCurrFuncId]);

                            cout << "      : " << m_funcFunctions[iCurrFuncId].funcCalls[m_funcFunctions[iCurrFuncId].funcCalls.size()-1].szName << endl;
                            cout << "      : " << m_funcFunctions[iCallsFuncId].funcCallers[m_funcFunctions[iCallsFuncId].funcCallers.size() - 1].szName << endl;
                            

                            line = m.suffix().str();
                        }
                    }
                }
                // check if is end of function
                if (0 != iCounterPrev && iCounterPrev == iCounterNext)
                {
                    cout << "                  Function is finished, press any button " << endl;
                    fFound = false;
                    iCounterPrev = 0;
                    iCounterNext = 0;
                    getchar();
                    continue;
                }
                else
                {
                    //cout << line << endl;
                }
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
			//cout << m_szFilesPathCPP << endl;
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