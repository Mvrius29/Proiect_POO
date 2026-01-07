#include "GetTime.h"

int GetTime::getcurentYear() {
    time_t t = time(nullptr);
    tm* acum = localtime(&t);
    return acum->tm_year + 1900;
}

int GetTime::getcurentMonth() {
    time_t t = time(nullptr);
    tm* acum =  localtime(&t);
    return acum->tm_mon + 1;
}

int GetTime::getcurentDay() {
    time_t t =  time(nullptr);
    tm* acum = localtime(&t);
    return acum->tm_mday;
}

tm getNowStruct() {
    auto acum = std::chrono::system_clock::now();
    std::time_t timp_t = std::chrono::system_clock::to_time_t(acum);
    return *std::localtime(&timp_t);
}

int GetTime::getcurentHour() {
    tm acum = getNowStruct();
    return acum.tm_hour;
}

int GetTime::getcurentMinute() {
    tm acum = getNowStruct();
    return acum.tm_min;
}
int GetTime::getcurentSecond() {
    tm acum = getNowStruct();
    return acum.tm_sec;
}

string GetTime::getfulltime() {
    tm acum = getNowStruct();
    stringstream ss;
    ss << std::put_time(&acum, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}