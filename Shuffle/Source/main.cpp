#include "Shuffle.h"

int main(int argc, const char *argv[]) {
	Shuffle app = Shuffle::init();

	if (argc < 2) {
		app.print_version_info();
		app.deinit();
		return 0;
	}
	
	std::string option = argv[1];
	if (option == "run")
		app.run();
	else if (option == "add") {
		if (argc > 2) app.add_folder(std::wstring(argv[2], argv[2] + strlen(argv[2])));
		else std::cout << "Info: Please provide valid folder path <arg>" << std::endl;
	}
	else if (option == "version")
		app.print_version_info();
	else if (option == "help") 
		app.print_help_message();
	else 
		app.print_help_message();

	app.deinit();
	return 0;
}
