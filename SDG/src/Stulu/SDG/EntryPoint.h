#pragma once

#ifdef ST_PLATFORM_WINDOWS
#include <Windows.h>
	extern SDG::Application* SDG::CreateApplication();
	int main(int argc, char** argv) {
#if ST_SHOWCONSOLE
		ShowWindow(GetConsoleWindow(), SW_SHOW);
#else
		ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif // ST_SHOWCONSOLE

		auto application = SDG::CreateApplication();

		application->run();

		delete application;

		return 0;
	}

#endif
