// test.cpp : main project file.

#include "Launcher.h"

int main(int argc, char* argv[])
{
    Launcher* launcher = new Launcher();
    launcher->run();
    delete launcher;
	return 0;
}
