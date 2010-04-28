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
    if(questionCount > 10)
    {
        MessageBox(NULL, L"Test has finished.\nThank You for your participation.", 
            L"You're Done!", MB_SYSTEMMODAL|MB_ICONINFORMATION);
            char dir[FILENAME_MAX];
        Utils::getTime(dir);
        System::String^ logDir = gcnew System::String(dir);
        logDir = logDir->Replace(":", "-");
        logDir = logDir->Replace("/", "-");
        Directory::CreateDirectory(logDir);
        System::String^ logFile = logDir + "/log.avi";
        File::Move("log.avi", logFile);
        logFile = logDir + "/log.txt";
        File::Move("log.txt", logFile);
        exit(0);
    }
    srand((int)time(NULL));
    Sleep(timer);
    uintptr_t hand = _beginthread(Thread, 0, NULL);
    WaitForSingleObject(hMutex, INFINITE); 
    launch->run();
    ReleaseMutex(hMutex);

    _endthread();
}

static void Thread(void* pParams)
{
    srand((int)time(NULL));
    Sleep(3000);
    int result;
    if(rand() % 2)
    {
        Log("Nod expected");
        while((result = MessageBox(NULL, L"Please nod your head", L"Nod", MB_SYSTEMMODAL|MB_ICONEXCLAMATION|MB_RETRYCANCEL)) == IDRETRY){
            Log("Nod clicked");
        }
        Log("Nod received");
    }
    else
    {
        Log("Shake expected");
        while((result = MessageBox(NULL, L"Please shake your head", L"Shake", MB_SYSTEMMODAL|MB_ICONEXCLAMATION|MB_RETRYCANCEL)) == IDRETRY)
        {
            Log("Shake clicked");
        }
        Log("Shake received");
    }
    launch->stop();
    if(result == IDCANCEL)
    {
        Log("abort");
        questionCount = 11;
        exit (1);
    }else if(questionCount <= 10)
    {
        timer = (12 + rand() % 5) * 1000;
        uintptr_t hand = _beginthread(Thread2, 0, &timer);
    }
    _endthread();
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
    MessageBox(NULL, L"Once you click ok, the system will start.  Please answer all dialog boxes with nods or shakes of the head.", 
    L"System Starting", MB_SYSTEMMODAL|MB_ICONINFORMATION);
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
