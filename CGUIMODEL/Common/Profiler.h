#ifndef CPROFILER_H
#define CPROFILER_H
#ifdef __cplusplus >= 201103L
    #include <chrono>
#else
    #include <ctime>
#endif

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

class Uncopyable {
public:
   Uncopyable() {}
  ~Uncopyable() {}
private:
  Uncopyable(const Uncopyable&);
  Uncopyable& operator=(const Uncopyable&);
};

class CProfiler :private Uncopyable
{
public:
    explicit CProfiler(const char *pFile,int pLine,const char* pFun);
    ~CProfiler();
private:

#ifdef __cplusplus >= 201103L
    std::chrono::system_clock::time_point m_tmPoint;
#else

#ifdef _WIN32
    bool gettimeofday(struct timeval *pTime, void *tzp)
#endif
    struct timeval tv;
#endif
    const char * m_pFun;
    int m_iLine;
    const char * m_pFile;
private:

};

#define PROFILER() do{ CProfiler __profiler_instance(__FILE__,__LINE__,__FUNCTION__);}while(0)

#endif // CPROFILER_H
