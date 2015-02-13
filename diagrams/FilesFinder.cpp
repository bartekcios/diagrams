#include "stdafx.h"
#include "FilesFinder.h"
#include <iostream>
#include <io.h>
#include <windows.h>

CFilesFinder::CFilesFinder( string a_RootDirectory):
m_RootDirectory(a_RootDirectory)
{
}


CFilesFinder::~CFilesFinder()
{
}

bool CFilesFinder::FindFilesH()

{
	

	//searching for subdirectories
	//prepare path to use
	std::wstring wsRootDirecoryHDir = std::wstring(m_RootDirectory.begin(), m_RootDirectory.end());
	LPCWSTR lpcwstrRootDirectoryHDir = wsRootDirecoryHDir.c_str();
	SetCurrentDirectory(lpcwstrRootDirectoryHDir);

	_finddata_t FilesDataHDir;
	long lHandlerHDir = _findfirst("*", &FilesDataHDir);

	do
	{
		// if file is dir go inside and search again
		if (_A_SUBDIR == FilesDataHDir.attrib && '.' != (*FilesDataHDir.name))
		{
			FindFilesH(m_RootDirectory + FilesDataHDir.name);
		}
	} while (-1 != _findnext(lHandlerHDir, &FilesDataHDir));

	//searching for h files
	//prepare path to use
	std::wstring wsRootDirecoryH = std::wstring(m_RootDirectory.begin(), m_RootDirectory.end());
	LPCWSTR lpcwstrRootDirectoryH = wsRootDirecoryH.c_str();
	SetCurrentDirectory(lpcwstrRootDirectoryH);

	//if no h files exit
	_finddata_t FilesDataH;
	long lHandlerH = _findfirst("*.h", &FilesDataH);

	if (-1 == lHandlerH)
	{
		return false;
	}

	do
	{
		SFile sFile;
		sFile.szNameOfFileWExtension = FilesDataH.name;
		sFile.szNameOfFile = sFile.szNameOfFileWExtension;
		sFile.szNameOfFile.resize(sFile.szNameOfFile.size() - 2);
		sFile.szNameOfFileWExtension = m_RootDirectory + FilesDataH.name;

		m_VectorOfFilesH.push_back(sFile);
	} while (-1 != _findnext(lHandlerH, &FilesDataH));

	return true;
}

bool CFilesFinder::FindFilesH(string a_RootDirectory)

{	
	//searching for subdirectories
	//prepare path to use
	std::wstring wsRootDirecoryHDir = std::wstring(a_RootDirectory.begin(), a_RootDirectory.end());
	LPCWSTR lpcwstrRootDirectoryHDir = wsRootDirecoryHDir.c_str();
	SetCurrentDirectory(lpcwstrRootDirectoryHDir);

	_finddata_t FilesDataHDir;
	long lHandler = _findfirst("*", &FilesDataHDir);

	do
	{
		// if file is dir go inside and search again
		if (_A_SUBDIR == FilesDataHDir.attrib && '.' != (*FilesDataHDir.name))
		{
			FindFilesH(a_RootDirectory + "\\" + FilesDataHDir.name);
		}
	} while (-1 != _findnext(lHandler, &FilesDataHDir));

	//searching for h files
	//prepare path to use
	std::wstring wsRootDirecoryH = std::wstring(a_RootDirectory.begin(), a_RootDirectory.end());
	LPCWSTR lpcwstrRootDirectoryH = wsRootDirecoryH.c_str();
	SetCurrentDirectory(lpcwstrRootDirectoryH);

	//if no h files - exit
	_finddata_t FilesDataH;
	long lHandlerH = _findfirst("*.h", &FilesDataH);

	if (-1 == lHandlerH)
	{
		return false;
	}

	do
	{
		SFile sFile;
		sFile.szNameOfFileWExtension = FilesDataH.name;
		sFile.szNameOfFile = sFile.szNameOfFileWExtension;
		sFile.szNameOfFile.resize(sFile.szNameOfFile.size() - 2);
		sFile.szPathToFile = a_RootDirectory + "\\" + FilesDataH.name;

		m_VectorOfFilesH.push_back(sFile);
	} while (-1 != _findnext(lHandlerH, &FilesDataH));

	return true;
}

bool CFilesFinder::FindFilesCPP()

{
	//searching for subdirectories
	//prepare path to use
	std::wstring wsRootDirecoryCPPDir = std::wstring(m_RootDirectory.begin(), m_RootDirectory.end());
	LPCWSTR lpcwstrRootDirectoryCPPDir = wsRootDirecoryCPPDir.c_str();
	SetCurrentDirectory(lpcwstrRootDirectoryCPPDir);

	_finddata_t FilesDataCPPDir;
	long lHandlerCPPDir = _findfirst("*", &FilesDataCPPDir);

	do
	{
		// if file is dir go inside and search again
		if (_A_SUBDIR == FilesDataCPPDir.attrib && '.' != (*FilesDataCPPDir.name))
		{
			FindFilesCPP(m_RootDirectory + FilesDataCPPDir.name);
		}
	} while (-1 != _findnext(lHandlerCPPDir, &FilesDataCPPDir));

	//searching for h files
	//prepare path to use
	std::wstring wsRootDirecoryCPP = std::wstring(m_RootDirectory.begin(), m_RootDirectory.end());
	LPCWSTR lpcwstrRootDirectoryCPP = wsRootDirecoryCPP.c_str();
	SetCurrentDirectory(lpcwstrRootDirectoryCPP);

	// if no cpp files exit
	_finddata_t FilesDataCPP;
	long lHandlerCPP = _findfirst("*.cpp", &FilesDataCPP);

	if (-1 == lHandlerCPP)
	{
		return false;
	}

	do
	{
		SFile sFile;
		sFile.szNameOfFileWExtension = FilesDataCPP.name;
		sFile.szNameOfFile = sFile.szNameOfFileWExtension;
		sFile.szNameOfFile.resize(sFile.szNameOfFile.size() - 4);
		sFile.szPathToFile = m_RootDirectory + FilesDataCPP.name;

		m_VectorOfFilesCPP.push_back(sFile);
	} while (-1 != _findnext(lHandlerCPP, &FilesDataCPP));

	return true;
}

bool CFilesFinder::FindFilesCPP(string a_RootDirectory)

{	
	//searching for subdirectories
	//prepare path to use
	std::wstring wsRootDirecoryCPPDir = std::wstring(a_RootDirectory.begin(), a_RootDirectory.end());
	LPCWSTR lpcwstrRootDirectoryCPPDir = wsRootDirecoryCPPDir.c_str();
	SetCurrentDirectory(lpcwstrRootDirectoryCPPDir);

	_finddata_t FilesDataCPPDir;
	long lHandler = _findfirst("*", &FilesDataCPPDir);

	do
	{
		// if file is dir go inside and search again
		if (_A_SUBDIR == FilesDataCPPDir.attrib && '.' != (*FilesDataCPPDir.name))
		{
			FindFilesCPP(a_RootDirectory + "\\" + FilesDataCPPDir.name);
		}
	} while (-1 != _findnext(lHandler, &FilesDataCPPDir));
	
	//searching for h files
	//prepare path to use
	std::wstring wsRootDirecoryCPP = std::wstring(a_RootDirectory.begin(), a_RootDirectory.end());
	LPCWSTR lpcwstrRootDirectoryCPP = wsRootDirecoryCPP.c_str();
	SetCurrentDirectory(lpcwstrRootDirectoryCPP);

	//if no cpp files exit
	_finddata_t FilesDataCPP;
	long lHandlerCPP = _findfirst("*.cpp", &FilesDataCPP);

	if (-1 == lHandlerCPP)
	{
		return false;
	}

	do
	{
		SFile sFile;
		sFile.szNameOfFileWExtension = FilesDataCPP.name;
		sFile.szNameOfFile = sFile.szNameOfFileWExtension;
		sFile.szNameOfFile.resize(sFile.szNameOfFile.size() - 4);
		sFile.szPathToFile = a_RootDirectory + "\\" + FilesDataCPP.name;

		m_VectorOfFilesCPP.push_back(sFile);
	} while (-1 != _findnext(lHandlerCPP, &FilesDataCPP));

	return true;
}

void CFilesFinder::ShowFilesH()
{
	for (int i = 0; i < m_VectorOfFilesH.size(); i++)
	{
        printf("File: %s\n", m_VectorOfFilesH[i].szNameOfFileWExtension.c_str());
        printf("File: %s\n", m_VectorOfFilesH[i].szNameOfFile.c_str());
        //printf("Path: %s\n", m_VectorOfFilesH[i].szPathToFile.c_str());
	}
	return;
}

void CFilesFinder::ShowFilesCPP()
{
	for (int i = 0; i < m_VectorOfFilesCPP.size(); i++)
	{
        printf("File: %s\n", m_VectorOfFilesCPP[i].szNameOfFileWExtension.c_str());
        printf("File: %s\n", m_VectorOfFilesCPP[i].szNameOfFile.c_str());
        //printf("Path: %s\n", m_VectorOfFilesCPP[i].szPathToFile.c_str());
	}

	return;
}

void CFilesFinder::ShowHCounter()
{
    printf("Found %d files .H\n", m_VectorOfFilesH.size());

	return;
}

void CFilesFinder::ShowCPPCounter()
{
    printf("Found %d files .CPP\n", m_VectorOfFilesCPP.size());

	return;
}