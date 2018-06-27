#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <adns.h>
#include <netdb.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>
#include <arpa/inet.h>
int main(int argc, char **argv)
 {
 struct sockaddr_in Stataddr;
 int kq, fd, ret;
  Stataddr.sin_family = AF_INET;
  Stataddr.sin_port = htons(80);
  Stataddr.sin_addr.s_addr=htonl(INADDR_ANY);   
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  fcntl(fd, F_SETFL, O_NONBLOCK);
  if (connect(fd, (struct sockaddr*) Stataddr,sizeof (struct sockaddr_in)) == 0) {
	  
  }
  int m_iEq=kqueue();
  struct kevent event = {fd,EVFILT_WRITE,EV_ADD|EV_ENABLE,0,0,NULL};
  kevent(m_iEq, &event, 1, NULL, 0, NULL);
  struct timespec timeout = {5,0};
  struct kevent eventlist[1024];
  int incoming = kevent(m_iEq, NULL, 0, eventlist, 1024, &timeout);
  for(int iter = 0; iter < incoming; iter++){
	  
	struct kevent event = eventlist[iter];
  
	if (event.flags & EV_ERROR){
		printf("File=%s:Line=%d:Func=%s,value = %d\n", __FILE__,__LINE__,__func__,event.ident);
	}
	if(event.filter & EVFILT_WRITE){
		 printf("File=%s:Line=%d:Func=%s,value = %d\n", __FILE__,__LINE__,__func__,event.ident);
	}
	if(event.filter & EVFILT_READ){
		printf("File=%s:Line=%d:Func=%s,value = %d\n", __FILE__,__LINE__,__func__,event.ident);
	}
    
  }
}