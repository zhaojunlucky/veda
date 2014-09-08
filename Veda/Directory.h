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
	};
	
	enum  FileSearchMode
	{
		Files,
		Directories,
		All
	};

	class DirectoryIterator : public Iterator < FileInfo >
	{
		friend class Directory;
	public:
		~DirectoryIterator();
		bool hasNext() const;
		const FileInfo & get();
	private:
		DirectoryIterator(const wchar_t* dirPath, FileSearchMode mode);
		DirectoryIterator(const wchar_t* dirPath,const wchar_t* extension);
		bool processNextFile();
	private:
		FileSearchMode mSearchMode;
		wstring mExtension;
		wstring mDirPath;
		PathUtil mPathUtil;
		WIN32_FIND_DATA mWFD;
		HANDLE mHandle;
		bool mHasNext;
		FileInfo mFileInfo;
	};

	typedef shared_ptr<DirectoryIterator> DirectoryIteratorPtr;

	class Directory
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


