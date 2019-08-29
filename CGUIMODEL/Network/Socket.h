#ifndef CSOCKET_H
#define CSOCKET_H
#ifdef _WIN32
#include<WinSock2.h>
#include<Windows.h>
#else
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#endif

#include <string>

class CSocket
{
public:
    CSocket();
    bool initSock();
    bool sockSock();
    bool bindSock();
    bool connSock(const std::string& servip,const unsigned int port);
    bool closeSock();
private:
    bool m_bConn;
    unsigned int m_iSockfd;
};
#endif // CSOCKET_H
