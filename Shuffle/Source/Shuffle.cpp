#include "Shuffle.h"

#include <fstream>

#include "Everything.h"

Shuffle::Shuffle() : m_FolderPathCache(Shuffle::ParseFolderPathFrom(L"scanner.in"))
{
}

Shuffle Shuffle::init()
{
	Everything_CleanUp();
	return Shuffle();
}

void Shuffle::deinit()
{
	Everything_CleanUp();
	m_FolderPathCache.clear();
}

void Shuffle::run()
{
	std::wstring searchQuery = GenSearchQuery();
	
	DWORD i;

	Everything_SetSearch(searchQuery.c_str());
	Everything_Query(true);

	std::wcout << "Result(s): " << Everything_GetNumResults() << " objects" << std::endl;
	
	for (i = 0; i < Everything_GetNumResults(); i++) 
		std::wcout << i + 1 << ": " << Everything_GetResultFileName(i) << std::endl;

	std::srand(static_cast<unsigned int>(std::time(0)));
	i = std::rand() % Everything_GetNumResults() + 1;

	std::wstring file_name = Everything_GetResultFileName(i);
	std::wstring file_path = Everything_GetResultPath(i);
	std::wstring cmd = L"\"" + file_path + L"\\" + file_name + L"\"";

	std::wcout << cmd << std::endl;

	_wsystem(cmd.c_str());
}

void Shuffle::add_folder(const std::wstring& folderPath)
{
	Shuffle::WriteFolderPathOn(L"scanner.in", folderPath);
}

void Shuffle::print_version_info() const 
{
	std::wcout << 
		L"Shuffle v0.1.1\n"
		L"Copyright(c) 2024 Toufiq A. Shishir\n"
		L"https ://github.com/toufiq7r/shuffle\n\n"
	<< std::endl;
}

void Shuffle::print_help_message() const
{
	print_version_info();

	std::wcout << L"Usage: cli app shuffle [option] <arg>" << std::endl;
	std::wcout << L"Options:" << std::endl;
	std::wcout << L"  play              Play the game" << std::endl;
	std::wcout << L"  add <arg>         Add a folder path as <arg> item" << std::endl;
	std::wcout << L"  version           Print program version info" << std::endl;
	std::wcout << L"  help              Print help message" << std::endl;
}

std::vector<std::wstring> Shuffle::ParseFolderPathFrom(const std::wstring& fileToParse)
{
	std::wifstream inFile(fileToParse);
	if (!inFile.is_open()) {
		std::wcerr << "Error: Failed to open file '" << fileToParse << "'" << std::endl;
		exit(1);
	}

	std::vector<std::wstring> folderPathCache;
	std::wstring line;
	bool isFolderPath = false;
	while (std::getline(inFile, line)) {
		if (line.find(L"[folder_path]") != std::wstring::npos) {
			isFolderPath = true; continue;
		}
		else if (line.find(L"[]") != std::wstring::npos)
			isFolderPath = false;

		if (isFolderPath) folderPathCache.push_back(line);
	}

	inFile.close();
	return folderPathCache;
}

void Shuffle::WriteFolderPathOn(const std::wstring& fileToWriteOn, const std::wstring& folderPath)
{
	std::wfstream inFile(fileToWriteOn);
	if (!inFile.is_open()) {
		std::wcerr << "Error: Failed to open file '" << fileToWriteOn << "'" << std::endl;
		exit(1);
	}

	inFile << "[folder_path]" << std::endl;
	inFile << folderPath.c_str() << std::endl;
	inFile << "[]" << std::endl;

	inFile.close();
}

std::wstring Shuffle::GenSearchQuery() 
{
	std::wstring query = L"";
	for (auto x : m_FolderPathCache) {
		query += std::format(L"{}\\*.mp4|{}\\*.mkv|{}\\*.avi|{}\\*.mov", x.c_str(), x.c_str(), x.c_str(), x.c_str());
		query += L"|";
	}
	query.pop_back();
	
	return query;
}
