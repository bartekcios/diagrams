#include "stdafx.h"
#include "Class.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <windows.h>

using namespace std;

CClass::CClass(string a_szName, string a_szFilesPathH, CFilesFinder * a_pFilesFinder):
    m_szName(a_szName),
    m_szFilesPathH(a_szFilesPathH),
    m_pFilesFinder(a_pFilesFinder)
{
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
    // copy file name without .h part
	m_szFilesHName = m_szFilesPathH.substr(iPosition, m_szFilesPathH.size()-iPosition-2);
	
	if (false == FindCPPFile())
	{
        printf("[WARR]: not found cpp file\n");
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

    //check if line is commented
    std::smatch mCommented;
    std::regex eCommented("([//\*]|[////])(.*)(\\()");
    // variables to regex
    std::smatch mFinder;
    std::regex eFinder("([^ ]*)([a-zA-Z0-9])(\\()");

	if (myfile.is_open())
	{

		while (getline(myfile, line))
		{


            if (!std::regex_search(line, mCommented, eCommented))
            {

                if (std::regex_search(line, mFinder, eFinder))
                {
                    if ("(" != mFinder[0] && "$(" != mFinder[0])
                    {

                        /*
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
                        */
                        SFunction sFunction;
                        sFunction.szName = mFinder[0];
                        m_funcFunctions.push_back(sFunction);

                    }

                    line = mFinder.suffix().str();
                }
            }
		}

		myfile.close();
        
	}
	else
	{
        printf("Unable to open file: %s\n", m_szFilesPathH.c_str());

		return false;
	}

	return true;
}

bool CClass::FindCalls()
{
    
	//open file
    string szLine;
    ifstream ifMyFile(m_szFilesPathCPP);
    if (ifMyFile.is_open())
	{
        string szConditions = "::([a-zA-Z0-9~])+(\())";
        std::smatch mFunction;
        std::regex eFunction(szConditions);

        std::smatch mPrev;
        std::regex ePrev("\\{");
        std::smatch mNext;
        std::regex eNext("\\}");

        string szAll = "([a-zA-Z0-9~])+(\\()";
        std::smatch mAll;
        std::regex eAll(szAll);

        int iCurrFuncId = 0;
        bool fFoundFunction = false;					                    // if function found

        int iCounterPrev = 0;										// No { chars
        int iCounterNext = 0;										// No } chars
        int iLinesCounter = 0;
        while (getline(ifMyFile, szLine))
		{
            iLinesCounter++;
			//if function is not found
            if (false == fFoundFunction)
			{
                if (std::regex_search(szLine, mFunction, eFunction))
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
                        if (std::regex_search(szLine, mFind, eFind))
                        {
                            iCurrFuncId = i;
                            fFoundFunction = true;
                            break;
                        }
                    }

                    szLine = mFunction.suffix().str();
				}
			}
			else
			{
                // if found - search calls
                string linePrev = szLine;
                string lineNext = szLine;

                // count No {} chars
                while (std::regex_search(linePrev, mPrev, ePrev))
                {
                    ++iCounterPrev;
                    linePrev = mPrev.suffix().str();
                }
                while (std::regex_search(lineNext, mNext, eNext))
                {
                    iCounterNext++;
                    lineNext = mNext.suffix().str();
                }

                if (std::regex_search(szLine, mAll, eAll) && 0 != iCounterPrev)
                {
					if (("if(" != mAll[0]) && ("gate(" != mAll[0]) && ("LOG_INF(" != mAll[0]) && ("LOG_ERR(" != mAll[0]) && ("LOG_WRN(" != mAll[0]) && ("LOG_DBG(" != mAll[0]) && ("(" != mAll[0]) && ("switch" != mAll[0]))
                    {
						//check if function already exists
						bool fExist = false;
                        /*for (int i = 0; i < m_funcFunctions[iCurrFuncId].szCalls.size(); i++)
						{
							if (mAll[0] == m_funcFunctions[iCurrFuncId].szCalls[i])
							{
								fExist = true;
							}
                        }*/
						if (false == fExist)
						{
							m_funcFunctions[iCurrFuncId].szCalls.push_back(mAll[0]);
						}
                    }
                    szLine = mFunction.suffix().str();
                }
                // check if is end of function
                if (0 != iCounterPrev && iCounterPrev == iCounterNext)
                {
                    fFoundFunction = false;
                    iCounterPrev = 0;
                    iCounterNext = 0;

                    continue;
                }
                else
                {

                }
			}
		}
        
        ifMyFile.close();
        SaveAllCalls();
        //SaveCalls("getDiscSettOptList(");
        printf("smth\n");
	}
	else
	{
        printf("Unable to open file: %s\n", m_szFilesPathH.c_str());
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

			return true;
		}
	}

	return false;
}

void CClass::ShowFunctions()
{
	for (int i = 0; i < m_funcFunctions.size(); i++)
	{
        printf("  %s\n", m_funcFunctions[i].szName.c_str());
	}
    printf("___  %d\n", m_funcFunctions.size());
	return;
}

bool CClass::SaveAllCalls()
{
    ofstream myfile;
	m_szFilesPathDOT = "c:\\Qt\\" + m_szName + ".dot";
	myfile.open(m_szFilesPathDOT, ios::trunc);
    if (myfile.is_open())
    {
		myfile << "digraph {" << endl;
		myfile << "rankdir = LR;" << endl;

    }
    for (int i = 0; i < m_funcFunctions.size(); i++)
    {
        for (int j = 0; j < m_funcFunctions[i].szCalls.size(); j++)
        {
            string F = m_funcFunctions[i].szName;
            string S = m_funcFunctions[i].szCalls[j];

            F.erase(F.size() - 1, 1);
            S.erase(S.size() - 1, 1);

			myfile << "\"" << F << "\"" << " -> " << "\"" << S << "\"" << ";" << endl;
        }
    }
	myfile << "}" << endl;
    myfile.close();
    printf("Class %s saved to file\n", m_szName.c_str());
	CreateGraph();
    return true;
}

bool CClass::SaveCalls(string a_szFunctionName)
{
    vector <int> iFunctions;
    ofstream myfile;
    m_szFilesPathDOT = "c:\\Qt\\" + m_szName + ".dot";
    myfile.open(m_szFilesPathDOT, ios::trunc);
    if (myfile.is_open())
    {
        myfile << "digraph {" << endl;
        myfile << "rankdir = LR;" << endl;
    }
    //find and add id function to vector
    int iFunctionId = FindFunctionInVector(a_szFunctionName);
    //if wrong argument
    if (-1 == iFunctionId)
    {
        return false;
    }
    iFunctions.push_back(iFunctionId);

    bool fAdded = true;

    while (true == fAdded)
    {
        fAdded = false;
        for (int p = 0; p < iFunctions.size(); p++)
        {
            // each call
            for (int j = 0; j < m_funcFunctions[iFunctions[p]].szCalls.size(); j++)
            {
                //if calls function exists in vector
                bool fExistsIniFunctions = false;
                for (int h = 0; h < iFunctions.size(); h++)
                {
                    if (iFunctions[h] == FindFunctionInVector(m_funcFunctions[iFunctions[p]].szCalls[j]))
                    {
                        fExistsIniFunctions = true;
                    }
                }
                if (false == fExistsIniFunctions)
                {
                    fAdded = true;
                    string F = m_funcFunctions[iFunctions[p]].szName;
                    string S = m_funcFunctions[iFunctions[p]].szCalls[j];

                    F.erase(F.size() - 1, 1);
                    S.erase(S.size() - 1, 1);

                    myfile << "\"" << F << "\"" << " -> " << "\"" << S << "\"" << ";" << endl;
                }
            }
        }
    }
    myfile << "}" << endl;
    myfile.close();
    printf("Class %s saved to file", m_szName.c_str());
    CreateGraph();

    return true;
}

bool CClass::AddCalls(string a_szFunctionName)
{

}

bool CClass::CreateGraph()
{
	
	//create command
	string szCommand = m_szGraphVizPath + "dot" + " -Tpng " + m_szFilesPathDOT + " -o " + m_szGraphVizPath + m_szName + ".png";

	system(szCommand.c_str());
    printf("Graph created\n");

	return true;
}

int CClass::FindFunctionInVector(string a_szFunctionName)
{
    int iRetVal = -1;
    //find a_szFunctionName function
    for (int i = 0; i < m_funcFunctions.size(); i++)
    {
        if (a_szFunctionName == m_funcFunctions[i].szName)
        {
            iRetVal = i;
        }
    }

    return iRetVal;
}
