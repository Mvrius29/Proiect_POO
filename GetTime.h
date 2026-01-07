#pragma once
#include <ctime>
#include <string>
#include <iomanip>
#include <chrono>
#include <sstream>
using namespace std;

class GetTime {
public:
    static int getcurentYear();
    static int getcurentMonth();
    static int getcurentDay();

    static int getcurentHour();
    static int getcurentMinute();
    static int getcurentSecond();
    static string getfulltime();

};