#pragma once
namespace SDG {
	extern Application* CreateApplication();

	int main_entry(int argc, char** argv) {

		auto application = SDG::CreateApplication();

		application->run();

		delete application;

		return 0;
	}
}

#ifdef ST_PLATFORM_WINDOWS
#include <Windows.h>
#ifdef ST_DIST
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
	return SDG::main_entry(__argc, __argv);
}
#else
int main(int argc, char** argv) {
	return SDG::main_entry(argc, argv);
}
#endif //ST_DIST
#endif //ST_PLATFORM_WINDOWS
