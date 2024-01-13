#include <iostream>

#include "Everything.h"

int main() {
	DWORD i;

	Everything_SetSearch(L"_projects");

	Everything_Query(true);

	for (i = 0; i < Everything_GetNumResults(); i++) {
		std::cout << "Name: " << Everything_GetResultFileName(i)
				  << "Path: " << Everything_GetResultPath(i) << std::endl;
	}

	return 0;
}
