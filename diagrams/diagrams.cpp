// diagrams.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <windows.h>

#include "FilesFinder.h"
#include "ClassManager.h"

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
    bool fShowTimes = true;
    DWORD t[100];

    if (false != fShowTimes)
    {
        t[1] = GetTickCount();
    }
    CFilesFinder oFilesFinder("c:\\Users\\ciosebar\\Desktop\\Workarea\\9 setup\\LtmIpcSetup\\backend\\DynamicSettingDB\\");
	//CFilesFinder oFilesFinder("D:\\workarea\\VP2_CVTO\\src\\veh\\LtmIpcSetup\\backend\\DynamicSettingDB\\");
	//CFilesFinder oFilesFinder("C:\\Users\\Bartek\\Documents\\Visual Studio 2013\\Projects\\todiagramstest\\todiagramstest\\");
    if (false != fShowTimes)
    {
        t[2] = GetTickCount() - t[1];
        cout << "oFilesFinder() : " << t[2] << endl;
    }

    if (false != fShowTimes)
    {
        t[1] = GetTickCount();
    }
	oFilesFinder.FindFilesH();
	//oFilesFinder.ShowFilesH();
    if (false != fShowTimes)
    {
        t[2] = GetTickCount() - t[1];
        cout << "oFilesFinder.FindFilesH() : " << t[2] << endl;
    }

    if (false != fShowTimes)
    {
        t[1] = GetTickCount();
    }
    oFilesFinder.FindFilesCPP();
    //oFilesFinder.ShowFilesCPP();
    if (false != fShowTimes)
    {
        t[2] = GetTickCount() - t[1];
        cout << "oFilesFinder.FindFilesCPP() : " << t[2] << endl;
    }

	oFilesFinder.ShowHCounter();
	oFilesFinder.ShowCPPCounter();
	
    if (false != fShowTimes)
    {
        t[1] = GetTickCount();
    }
	CClassManager oClassManager(&oFilesFinder);
    if (false != fShowTimes)
    {
        t[2] = GetTickCount() - t[1];
        cout << "oClassManager() : " << t[2] << endl;
    }

    if (false != fShowTimes)
    {
        t[1] = GetTickCount();
    }
	oClassManager.FindAllClasses();
    if (false != fShowTimes)
    {
        t[2] = GetTickCount() - t[1];
        cout << "oClassManager.FindAllClasses() : " << t[2] << endl;
    }

    if (false != fShowTimes)
    {
        t[1] = GetTickCount();
    }
	oClassManager.FindFunctions();
    if (false != fShowTimes)
    {
        t[2] = GetTickCount() - t[1];
        cout << "oClassManager.FindFunctions() : " << t[2] << endl;
    }

	//oClassManager.ShowAllClasses();

    if (false != fShowTimes)
    {
        t[1] = GetTickCount();
    }
    oClassManager.FindCallsForFunctions();
    if (false != fShowTimes)
    {
        t[2] = GetTickCount() - t[1];
        cout << "oClassManager.FindCallsForFunctions() : " << t[2] << endl;
    }


	cout << "Work finished" << endl;
	getchar();
	return 0;
}

