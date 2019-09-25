#ifndef CPROFILER_H
#define CPROFILER_H
#ifdef __cplusplus >= 201103L
    #include <chrono>
    using namespace std;
    using namespace std::chrono;
#else
    #include <ctime>
#endif

#ifdef WIN32
#include <WinSock2.h>
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

#define PROFILER()  CProfiler __profiler_instance(__FILE__,__LINE__,__FUNCTION__)
class Timer
{
public:
    Timer() : m_begin(high_resolution_clock::now()) {}
    void reset() { m_begin = high_resolution_clock::now(); }
    //默认输出毫秒
    int64_t elapsed() const
    {
        return duration_cast<chrono::milliseconds>(high_resolution_clock::now() - m_begin).count();
    }
    //微秒
    int64_t elapsed_micro() const
    {
        return duration_cast<chrono::microseconds>(high_resolution_clock::now() - m_begin).count();
    }
    //纳秒
    int64_t elapsed_nano() const
    {
        return duration_cast<chrono::nanoseconds>(high_resolution_clock::now() - m_begin).count();
    }
    //秒
    int64_t elapsed_seconds() const
    {
        return duration_cast<chrono::seconds>(high_resolution_clock::now() - m_begin).count();
    }
    //分
    int64_t elapsed_minutes() const
    {
        return duration_cast<chrono::minutes>(high_resolution_clock::now() - m_begin).count();
    }
    //时
    int64_t elapsed_hours() const
    {
        return duration_cast<chrono::hours>(high_resolution_clock::now() - m_begin).count();
    }
private:
    time_point<high_resolution_clock> m_begin;
};

#endif // CPROFILER_H
