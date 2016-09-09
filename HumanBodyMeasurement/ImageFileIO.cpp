
#include "ImageFileIO.h"

using namespace std;



int FileIO::GetAllFilesInFolder(string folderName, vector<string>& fileNames, bool isFullPathRequired)
{
	string originalString;
	originalString = folderName;
	//Add "/*" at and of folder name
	folderName.append("/*");
	//folderName = "E:\\Shared folder\\RefDataSets\\LAS-Cap";
	//char *ch = "E:\\Shared folder\\RefDataSets\\LAS-Cap";
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR tDir[MAX_PATH];
	char szFileinFolder[260];
	char cDefaultCharacter = ' ';


	MultiByteToWideChar(CP_ACP, 0, folderName.c_str(), -1, tDir, 260);
	//MultiByteToWideChar(CP_ACP, 0, folderName.c_str(), -1, tDir,260);

	// Find the first file in the v_strDirectory.
	HANDLE hFind = FindFirstFile(tDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		return -5;
	}

	// List all the files in the v_strDirectory with some info about them.
	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//printf("  %s   <DIR>\n", ffd.cFileName);
		}
		else
		{
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			WideCharToMultiByte(CP_ACP, 0, ffd.cFileName, -1, szFileinFolder, 260, &cDefaultCharacter, NULL);
			std::string fileName(szFileinFolder);
			fileNames.push_back(fileName);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);

	if (true == isFullPathRequired)
	{
		GetFullPath(originalString, fileNames);
	}

	return 1;
}

int FileIO::GetImageFilesInFolder(string folderName, vector<string>& fileNames, bool isFullPathRequired)
{
	//Find all files in folder
	vector<string> v_strAllFilesName;
	GetAllFilesInFolder(folderName, v_strAllFilesName, false);

	//filter image files from all files
	FilterImagesFiles(v_strAllFilesName, fileNames);

	//Release memory
	//v_strAllFilesName.clear();

	if (true == isFullPathRequired)
	{
		GetFullPath(folderName, fileNames);
	}

	return 1;
}

void FileIO::FilterImagesFiles(vector<string>& input, vector<string>& output)
{
	for (int nIterator = 0; nIterator < (int)input.size(); nIterator++)
	{
		char szBuffer[256];

		std::strcpy(szBuffer, input[nIterator].c_str());

		if (szBuffer[0] != '.')
		{
			char szFormat[20];
			char szName[100];

			char *pcText = strtok(szBuffer, ".");
			if (pcText == NULL)
				break;
			std::strcpy(szName, pcText);
			pcText = strtok(NULL, ".");
			if (pcText == NULL)
				continue;
			std::strcpy(szFormat, pcText);
			pcText = strtok(NULL, ".");

			std::string strString(szName);
			string strSubString;
			strSubString = strString.substr(0, 4);

			//if (((strcmp(strSubString.c_str(), "img_") == 0) || (strcmp(strSubString.c_str(), "Img_") == 0) || (strcmp(strSubString.c_str(), "IMG_") == 0)) && pcText == NULL)
			//{
			if ((strcmp(szFormat, "tif") == 0) || (strcmp(szFormat, "jpg") == 0)
				|| (strcmp(szFormat, "bmp") == 0) || (strcmp(szFormat, "png") == 0) || (strcmp(szFormat, "tiff") == 0))
			{
				output.push_back(input[nIterator]);
			}
			//}				
		}
	}
}

void FileIO::GetFullPath(string folderName, vector<string>& fileNames)
{
	vector<string>tempFileNames;
	for (int itr = 0; itr < (int)fileNames.size(); ++itr)
	{
		char szFilePath[MAX_PATH];
		sprintf(szFilePath, "%s/%s", folderName.c_str(), fileNames[itr].c_str());
		tempFileNames.push_back(szFilePath);
	}

	fileNames.clear();
	fileNames.resize(tempFileNames.size());

	copy(tempFileNames.begin(), tempFileNames.end(), fileNames.begin());

	tempFileNames.clear();
}

// Function to Read SubFolders
bool FileIO::FindSubDirectories(char* pcDirectory, vector<string>& v_strDirectory, vector<string>& v_strFolderNames)
{
	_chdir(pcDirectory);
	_finddata_t fileinfo;
	intptr_t handle = _findfirst("*", &fileinfo);
	if (handle == -1)
	{
		std::cerr << "Error: The system cannot find the Path specified ( " << pcDirectory << " )...Program Terminating..." << endl;
		return false;
	}

	do
	{
		if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
			continue;
		if (fileinfo.attrib & _A_SUBDIR) // Use bitmask to see if this is a v_strDirectory
		{
			char fpath[300];
			sprintf_s(fpath, "%s\\%s", pcDirectory, fileinfo.name);
			v_strDirectory.push_back(fpath);
			v_strFolderNames.push_back(fileinfo.name);
		}
	} while (_findnext(handle, &fileinfo) == 0);
	_findclose(handle); // Close the stream		

	if (v_strDirectory.empty())
	{
		std::cerr << "Error: No folder found in Input v_strDirectory...Program Terminating...!\n\n" << endl;
		system("PAUSE");
		return false;
	}

	return true;
}


//Function to check if it is a valid Directory
bool FileIO::ValidDirectory(const string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}

int FileIO::GetTextFilesInFolder(string folderName, vector<string>& fileNames)
{
	//Find all files in folder
	vector<string> v_strAllFilesName;
	GetAllFilesInFolder(folderName, v_strAllFilesName, true);

	for (int nItr = 0; nItr < (int)v_strAllFilesName.size(); nItr++)
	{
		string strFileName = v_strAllFilesName[nItr].substr(v_strAllFilesName[nItr].find_last_of("\\/") + 1);
		if (strFileName.substr(strFileName.find_last_of(".")) == ".txt")
		{
			fileNames.push_back(v_strAllFilesName[nItr]);
		}
	}

	////filter image files from all files
	//FilterImagesFiles(v_strAllFilesName, fileNames);

	////Release memory
	////v_strAllFilesName.clear();

	//if (true == isFullPathRequired)
	//{
	//	GetFullPath(folderName, fileNames);
	//}

	return 1;
}