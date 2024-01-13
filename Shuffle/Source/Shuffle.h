#pragma once

#include <format>
#include <iostream>
#include <string>
#include <xstring>
#include <vector>

class Shuffle 
{
public:
	Shuffle();
	static Shuffle init();
	void deinit();

	void run();										// run
	void add_folder(const std::wstring& folderPath);		// add <arg>
	void print_version_info() const;				// version
	void print_help_message() const;				// help

private:
	static std::vector<std::wstring> ParseFolderPathFrom(const std::wstring& fileToParse);
	static void WriteFolderPathOn(const std::wstring& fileToWriteOn, const std::wstring& folderPath);
	std::wstring GenSearchQuery();

private:
	std::vector<std::wstring> m_FolderPathCache;
};