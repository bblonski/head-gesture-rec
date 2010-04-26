// ContextGestures.cpp : main project file.

#include "NaiveLauncher.h"

using namespace System;

static int timer;
static NaiveLauncher* launch;
HANDLE hMutex;
static int questionCount;

static void Log(char* message)
{
    ofstream stream;
    stream.open("log.txt", ios::app);
    char buffer[100];
    Utils::getTime(buffer);
    stream << buffer <<  message << endl;
    stream.close();
}
static void Thread(void* pParams);

static void Thread2(void* pParams)
{
    questionCount++;
    srand((int)time(NULL));
    Sleep(timer);
    uintptr_t hand = _beginthread(Thread, 0, NULL);
    WaitForSingleObject(hMutex, INFINITE); 
    launch->run();
    ReleaseMutex(hMutex);
    if(questionCount > 20)
    {
        WaitForSingleObject((HANDLE)hand, INFINITE); 
        MessageBox(NULL, L"Test has finished.\nThank You for your participation.", 
            L"You're Done!", MB_SYSTEMMODAL|MB_ICONINFORMATION);
        exit(0);
    }
    _endthread();
}

static void Thread(void* pParams)
{
    srand((int)time(NULL));
    Sleep(3000);
    if(rand() % 2)
    {
        Log("Nod expected");
        while(MessageBox(NULL, L"Please nod your head", L"Nod", MB_SYSTEMMODAL|MB_ICONHAND) == IDOK){
            Log("Nod clicked");
        }
        Log("Nod received");
    }
    else
    {
        Log("Shake expected");
        while(MessageBox(NULL, L"Please shake your head", L"Shake", MB_SYSTEMMODAL|MB_ICONEXCLAMATION) == IDOK)
        {
            Log("Shake clicked");
        }
        Log("Shake received");
    }
    launch->stop();
    timer = (30 + rand() % 5) * 1000;
    uintptr_t hand = _beginthread(Thread2, 0, &timer);
    _endthread();
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
    questionCount = 0;
    hMutex = CreateMutex(NULL, false, L"myMutex");
    char* argv[1] = {0};
    int argc = 1;
    launch = new NaiveLauncher();
    srand((int)time(NULL));
    timer = (rand() % 15) * 1000;
    uintptr_t hand = _beginthread(Thread2, 0, &timer);
    
    while(1)
    {
        Sleep(1000);
    }
    
	return 0;
}
