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
    DWORD t[2];

    if (false != fShowTimes)
    {
        t[1] = GetTickCount();
    }
    CFilesFinder oFilesFinder("D:\\CCM_WA\\VP2_CVTO\\src\\veh\\LtmIpcSetup\\backend\\DynamicSettingDB\\");
	//CFilesFinder oFilesFinder("D:\\workarea\\VP2_CVTO\\src\\veh\\LtmIpcSetup\\");
	//CFilesFinder oFilesFinder("C:\\Users\\Bartek\\Documents\\Visual Studio 2013\\Projects\\diagrams\\");
    if (false != fShowTimes)
    {
        t[2] = GetTickCount() - t[1];
        printf("oFilesFinder() :%d\n", t[2]);
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
        printf("oFilesFinder.FindFilesH() :%d\n", t[2]);
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
        printf("oFilesFinder.FindFilesCPP() :%d\n", t[2]);
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
        printf("oClassManager() :%d\n", t[2]);
    }

    if (false != fShowTimes)
    {
        t[1] = GetTickCount();
    }
	oClassManager.FindAllClasses();
    if (false != fShowTimes)
    {
        t[2] = GetTickCount() - t[1];
        printf("oClassManager.FindAllClasses() :%d\n", t[2]);
    }
    
    if (false != fShowTimes)
    {
        t[1] = GetTickCount();
    }
	oClassManager.FindFunctions();
    if (false != fShowTimes)
    {
        t[2] = GetTickCount() - t[1];
        printf("oClassManager.FindFunctions() :%d\n", t[2]);
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
        printf("oClassManager.FindCallsForFunctions() :%d\n", t[2]);
    }


    printf("Work finished\n");

	getchar();
	return 0;
}

