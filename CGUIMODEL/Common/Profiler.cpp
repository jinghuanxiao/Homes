#include "Profiler.h"
#include<iostream>

#ifdef __cplusplus >= 201103L

#else

#ifdef _WIN32
int CProfiler::gettimeofday(struct timeval *pTime, void *tzp)
{
    time_t clock;
    struct tm Clock;
    SYSTEMTIME winTm;
    GetLocalTime(&winTm);
    Clock.tm_year = winTm.wYear - 1900;
    Clock.tm_mon  = winTm.wMonth - 1;
    Clock.tm_mday = winTm.wDay;
    Clock.tm_hour = winTm.wHour;
    Clock.tm_min  = winTm.wMinute;
    Clock.tm_sec  = winTm.wSecond;
    Clock.tm_isdst  = -1;
    clock = mktime(&Clock);
    pTime->tv_sec = clock;
    pTime->tv_usec = winTm.wMilliseconds * 1000;
    return true;
}
#endif

#endif

#if defined(_WIN32)

#endif

CProfiler::CProfiler(const char *pFile, int pLine, const char *pFun):Uncopyable()
{
#ifdef __cplusplus >= 201103L
    m_tmPoint= std::chrono::system_clock::now();
#else
    gettimeofday(&tv, NULL);
#endif
    m_pFile = pFile;
    m_iLine = pLine;
    m_pFun = pFun;
}

CProfiler::~CProfiler()
{
#ifdef __cplusplus >= 201103L
    std::chrono::microseconds cost= std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()-m_tmPoint);
    std::cout<<"File:("<<m_pFile<<") Func:("<<m_pFun<<") Line:("<<m_iLine<<") INFO:"<< cost.count() <<"us"<<std::endl;
#else
    struct timeval tv2;
    gettimeofday(&tv2, NULL);
    long cost = (tv.tv_sec - tv.tv_sec) * 1000000 + (tv.tv_usec - tv.tv_usec);
    std::cout<<"File:("<<m_pFile<<") Func:("<<m_pFun<<") Line:("<<m_iLine<<") INFO:"<< cost <<"us"<<std::endl;
#endif

}

