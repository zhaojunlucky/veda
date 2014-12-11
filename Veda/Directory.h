#pragma once
#include <Windows.h>
#include <string>
#include <memory>
using namespace std;
#include "ReadOnlyIterator.h"
#include "PathUtil.h"
namespace veda
{
	struct FileInfo
	{
		bool isDirectory;
		wstring fileName;
		wstring fullPath;
		time_t lastModifiedTime;
		time_t creationTime;
		time_t lastAccessTime;
		__int64 fileSize;
	};
	
	enum  FileSearchMode
	{
		Files,
		Directories,
		All
	};

	class VEDA_EXPORT DirectoryIterator : public Iterator < FileInfo >
	{
		friend class Directory;
	public:
		~DirectoryIterator();
		bool hasNext();
		const FileInfo & get();
	private:
		DirectoryIterator(const wchar_t* dirPath, FileSearchMode mode);
		DirectoryIterator(const wchar_t* dirPath,const wchar_t* extension);
		bool processFirstFile();
		bool processNextFile();
		time_t localFileTimeToUTC(FILETIME& ft);
	private:
		FileSearchMode mSearchMode;
		wstring mExtension;
		wstring mDirPath;
		PathUtil mPathUtil;
		WIN32_FIND_DATA mWFD;
		HANDLE mHandle;
		FileInfo mFileInfo;
		bool mFirst;
	};

	typedef shared_ptr<DirectoryIterator> DirectoryIteratorPtr;

	class VEDA_EXPORT Directory
	{
	public:
		Directory(const wchar_t* dirPath);
		~Directory();
		bool isExists() const;
		DirectoryIteratorPtr searchFiles(const wchar_t* extension = L"*.*");
		DirectoryIteratorPtr searchDirectories();
		DirectoryIteratorPtr searchAll();
	private:
		wstring mDirPath;
		bool mIsExist;
	};
}


