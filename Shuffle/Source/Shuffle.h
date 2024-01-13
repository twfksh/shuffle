#pragma once

#include <iostream>
#include <xstring>
#include <vector>

class Shuffle 
{
public:
	Shuffle();
	static Shuffle init();
	void deinit();
	void run();
	void add_folder(const std::wstring& path);
	static std::wstring version_info();

private:
	static std::vector<std::wstring> ParseFolderPathFrom(const std::wstring& fileToParse);
	static void WriteFolderPathOn(const std::wstring& fileToWriteOn, const std::wstring& folderPath);
	std::wstring GenSearchQuery();

private:
	static const std::wstring m_VersionInfo;

	std::vector<std::wstring> m_FolderPathCache;
};