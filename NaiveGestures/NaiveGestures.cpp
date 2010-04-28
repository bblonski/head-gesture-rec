// NaiveGestures.cpp : main project file.

#include "NaiveLauncher.h"
using namespace System;

static int timer;
static int questionCount;
static NaiveLauncher* launch;

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
    questionCount++;
    if(questionCount <= 10)
    {
        srand((int)time(NULL));
        Sleep(*((int*)pParams));
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
        if(result == IDCANCEL)
        {
            Log("abort");
            launch->stop();
            questionCount = 11;
            _endthread();
        }else{
            timer = (15 + rand() % 5) * 1000;
            uintptr_t hand = _beginthread(Thread, 0, &timer);
        }
    }else{
        launch->stop();
    }
    _endthread();
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
    MessageBox(NULL, L"Once you click ok, the system will start.  Please answer all dialog boxes with nods or shakes of the head.", 
    L"System Starting", MB_SYSTEMMODAL|MB_ICONINFORMATION);
    questionCount = 0;
    char* argv[1] = {0};
    int argc = 1;

    timer = (rand() % 15) * 1000;
    uintptr_t hand = _beginthread(Thread, 0, &timer);
    launch = new NaiveLauncher();
    int result = launch->run();
    delete launch;
    MessageBox(NULL, L"Test has finished.\nThank You for your participation.", 
        L"You're Done!", MB_SYSTEMMODAL|MB_ICONINFORMATION);
    
	return result;
}

