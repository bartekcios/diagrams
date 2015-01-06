#pragma once
#include <vector>
#include <string>
#include "FilesFinder.h"

using namespace std;

class CClass
{
public:
	struct SFunction
	{
		string szName;
		vector <SFunction> funcCallers;				// list of functions which calls this function
		vector <string> szCalls;				    // list of functions which are called by this function
	};
	CClass(string a_szName, string a_szFilesPathH, CFilesFinder * a_pFilesFinder);
	~CClass();
	bool FindFunctions();							// search all functions inside h file
	bool FindCalls();								// search all calls inside cpp file
	bool FindCPPFile();								// finds file with the same 
	void ShowFunctions();							// shows all functions
    bool SaveCalls();                               // saves all calls to file
	bool CreateGraph();								// creates graph for each class
	string m_szName;
	string m_szFilesHName;
	string m_szFilesPathH;
	string m_szFilesPathCPP;
	string m_szFilesPathDOT;
	const string m_szGraphVizPath = "C:\\release\\bin\\";
private:
	CFilesFinder * m_pFilesFinder;						// pointer to CFilesFinder, used to get files pathes
	vector <SFunction> m_funcFunctions;
};

