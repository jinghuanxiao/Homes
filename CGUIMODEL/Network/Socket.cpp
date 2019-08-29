#include "Socket.h"
#include <cstring>

#ifdef _WIN32
#pragma comment(lib,"ws2_32.lib")
#endif

CSocket::CSocket():m_iSockfd(-1)
{
}
bool CSocket::initSock()
{

#ifdef _WIN32
    WORD VersionRequest;
    WSADATA wsaData;
    VersionRequest=MAKEWORD(2,2);
    int nError = WSAStartup(VersionRequest,&wsaData);
    if(!nError)
        return true;
    return false;
#else
    return true;
#endif
}
bool CSocket::sockSock()
{
    m_iSockfd = socket(AF_INET,SOCK_STREAM,0);
    if(INVALID_SOCKET == m_iSockfd){
        return false;
    }
    return true;
}

bool CSocket::bindSock()
{
    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_port = htons(0);
#ifdef _WIN32
    client.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
#else
    client.sin_addr.s_addr = htonl(INNADDR_ANY);
#endif
    int nError = bind(m_iSockfd,(struct sockaddr*)&client,sizeof(client));
    if(0 ==nError){
        return true;
    }
    closeSock();
    return false;
}
bool CSocket::closeSock()
{
#ifdef _WIN32
    closesocket(m_iSockfd);
#else
    close(m_iSockfd);
#endif
    return true;
}
bool CSocket::connSock(const std::string &servip, const unsigned int port)
{
    struct sockaddr_in servAddr;
    memset(&servAddr,0,sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
#ifdef _WIN32
    servAddr.sin_addr.S_un.S_addr = inet_addr(servip.c_str());
#else
    servAddr.sin_addr.s_addr = inet_addr(servip.c_str());
#endif
    int nError = connect(m_iSockfd,(struct sockaddr*)&servAddr,sizeof(servAddr));
    if(0 == nError){
        return true;
    }
    closeSock();
    return false;
}
