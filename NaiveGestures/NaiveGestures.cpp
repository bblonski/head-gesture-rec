// NaiveGestures.cpp : main project file.

#include "NaiveLauncher.h"
using namespace System;

static int timer;

static void Log(char* message)
{
    ofstream stream;
    stream.open("log.txt", ios::app);
    char buffer[100];
    Utils::getTime(buffer);
    stream << buffer <<  message << endl;
    stream.close();
}

static void Thread(void* pParams)
{
    srand((int)time(NULL));
    Sleep(*((int*)pParams));
    if(rand() % 2)
    {
        Log("Nod expected");
        while(MessageBox(NULL, L"Please nod your head", L"Nod", MB_SYSTEMMODAL) == IDOK){
            Log("Nod clicked");
        }
        Log("Nod received");
    }
    else
    {
        Log("Shake expected");
        while(MessageBox(NULL, L"Please shake your head", L"Shake", MB_SYSTEMMODAL) == IDOK)
        {
            Log("Shake clicked");
        }
        Log("Shake received");
    }
    timer = (10 + rand() % 5) * 1000;
    uintptr_t hand = _beginthread(Thread, 0, &timer);
    _endthread();
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
    char* argv[1] = {0};
    int argc = 1;

    timer = (rand() % 15) * 1000;
    uintptr_t hand = _beginthread(Thread, 0, &timer);
    NaiveLauncher* launch = new NaiveLauncher();
    int result = launch->run();
    delete launch;
    
	return result;
}

