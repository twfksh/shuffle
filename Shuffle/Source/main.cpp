#include "Shuffle.h"

int main(int argc, const std::wstring argv[]) {
	Shuffle app = Shuffle::init();

	if (argc < 2) {
		std::wcout << app.version_info() << std::endl;
		app.deinit();
		return 0;
	}

	std::wstring option = argv[1];

	app.deinit();
	return 0;
}
