// diagrams.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>

#include "FilesFinder.h"
#include "ClassManager.h"

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	CFilesFinder oFilesFinder("D:\\workarea\\VP2_CVTO\\src\\veh\\LtmIpcSetup\\backend\\DynamicSettingDB\\");
	//CFilesFinder oFilesFinder("C:\\Users\\Bartek\\Documents\\Visual Studio 2013\\Projects\\todiagramstest\\todiagramstest\\");
	oFilesFinder.FindFilesH();
	//oFilesFinder.ShowFilesH();

	oFilesFinder.FindFilesCPP();
	//oFilesFinder.ShowFilesCPP();

	oFilesFinder.ShowHCounter();
	oFilesFinder.ShowCPPCounter();
	
	CClassManager oClassManager(&oFilesFinder);
	oClassManager.FindAllClasses();

	oClassManager.FindFunctions();

	oClassManager.ShowAllClasses();

	


	cout << "Work finished" << endl;
	getchar();
	return 0;
}

