#pragma once
#include <vector>
#include <string>

using namespace std;

class CFilesFinder
{
	friend class CClassManager;
	friend class CClass;
	struct SFile
	{
		string szNameOfFile;
		string szNameOfFileWExtension;
		string szPathToFile;
	};
public:
	CFilesFinder(string a_RootDirectory);
	~CFilesFinder();
	bool FindFilesH();											// used to search files inside root directory
	bool FindFilesH(string a_RootDirectory);					// used to search files inside subdirectories
	bool FindFilesCPP();										// used to search files inside root directory
	bool FindFilesCPP(string a_RootDirectory);					// used to search files inside subdirectories
	void ShowFilesH();											// shows all files h with paths
	void ShowFilesCPP();										// shows all files h with paths
	void ShowHCounter();										// shows No found h files
	void ShowCPPCounter();										// shows No found cpp files

protected:
	vector <SFile> m_VectorOfFilesH;							// list of h files
	vector <SFile> m_VectorOfFilesCPP;							// list of cpp files

private:
	string m_RootDirectory;										// path to root dir
};

