#include "consdbg.h"

#define LOGBUF_SIZE 8192

void CConsDbg::Init(int iDebugLevel)
{
    m_bEnabled=true;
    m_iDebugLevel=iDebugLevel;
}

void CConsDbg::DeInit()
{
    m_bEnabled=false;
}

#ifdef DBGCONSOLE
void CConsDbg::Log(int iDebugLevel, const char *logfmt, ...)
{
    if(!m_bEnabled || m_iDebugLevel<iDebugLevel){
        return;
    }
    va_list va_alist;
    char logbuf[LOGBUF_SIZE];
    char logbuf2[LOGBUF_SIZE];
    va_start(va_alist, logfmt);
    vsprintf(logbuf2, logfmt, va_alist);
    va_end(va_alist);
	sprintf(logbuf, "[%d/%d] %s", iDebugLevel, m_iDebugLevel, logbuf2);
	fprintf(stdout, "%s", logbuf);

}
void CConsDbg::LogErr(int iDebugLevel, const char *logfmt, ...)
{
    if(!m_bEnabled || m_iDebugLevel<iDebugLevel){
        return;
     }
    va_list va_alist;
    char logbuf[LOGBUF_SIZE];
    char logbuf2[LOGBUF_SIZE];
    va_start(va_alist, logfmt);
    vsprintf(logbuf2, logfmt, va_alist); va_end(va_alist);
	sprintf(logbuf, "[%d/%d] %s", iDebugLevel, m_iDebugLevel, logbuf2);
	fprintf(stderr, "%s", logbuf);
}
#endif // DBGCONSOLE
