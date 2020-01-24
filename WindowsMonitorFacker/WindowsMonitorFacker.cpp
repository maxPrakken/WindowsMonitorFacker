#include <iostream>
#include <string.h>
#include <Windows.h>
#include <cstdlib>
#include <time.h>
#include <chrono> 
#include <lowlevelmonitorconfigurationapi.h>

void SleepMonitors();
void WakeMonitors();
using namespace std::chrono;

int main()
{
    ShowWindow(GetConsoleWindow(), false);

    auto start = steady_clock::now();

    srand(time(NULL));
    int minTime = rand() % 10 + 15;
    int maxTime = minTime + 5;

    while (1) {
        Sleep(1000);
        auto end = steady_clock::now(); // get time

        int timeGone = duration_cast<seconds>(end - start).count(); // check how much time has passed
        if (timeGone > minTime&& timeGone < maxTime) { // if more than X and less than Y
            SleepMonitors(); // sleeps monitors
        }
        if (timeGone >= maxTime) { // if more than X
            WakeMonitors(); // wake monitors
            start = steady_clock::now(); // reset start clock
            minTime = rand() % 50 + 15; // give new random time
            int maxTime = minTime + 5;
        }
    }
}

void SleepMonitors() {
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)2);
}

void WakeMonitors() {
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)-1);
}
