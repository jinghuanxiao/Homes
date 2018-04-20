#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<errno.h>
#include<arpa/inet.h>
#include<signal.h>
#include<netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/in_systm.h>
#define BUFSIZE 1500     //发送缓存最大值

//数据类型别名
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

char hello[]="hello this is  a ping test.";

char *hostname; //被ping的主机
int  datalen=56;//ICMP消息携带的数据长度
char sendbuf[BUFSIZE];
char recvbuf[BUFSIZE];
int nsent;//发送的ICMP消息序号
int nrecv;
pid_t pid;//ping程序的进程pid
struct timeval recvtime; //收到ICMP应答的时间戳
int sockfd; //发送和接收原始套接字
struct sockaddr_in dest;//被ping主机的ip
struct sockaddr_in from;//发送ping应答消息的主机ip

struct sigaction act_alarm;
struct sigaction act_int;


//设置的时间是一个结构体，倒计时设置，重复倒时，超时值设为1秒
struct itimerval val_alarm;

//函数原型
void alarm_handler(int);//SIGALRM处理程序
void int_handler(int);//SIGINT处理程序
void set_sighandler();//设置信号处理程序
void send_ping();//发送ping消息
void recv_reply();//接收ping应答
u16 checksum(u8 *buf,int len);//计算校验和
int handle_pkt(int len);//ICMP应答消息处理
void get_statistics(int ,int);//统计ping命令的检测结果
void bail(const char *);//错误报告
int main(int argc,char **argv)  //argc表示隐形程序命令行中参数的数目，argv是一个指向字符串数组指针，其中每一个字符对应一个参数
{
    val_alarm.it_interval.tv_sec = 1;
    val_alarm .it_interval.tv_usec=0;
    val_alarm  .it_value.tv_sec=0;
    val_alarm  .it_value.tv_usec=1;
    struct hostent *host; //该结构体属于include<netdb.h>
    int on =1;

    if(argc<2){      //判断是否输入了地址
        printf("Usage: %s hostname\n",argv[0]);
        exit(1);
    }

    if((host=gethostbyname(argv[1]))==NULL)
    {    //gethostbyname()返回对应于给定主机名的包含主机名字和地址信息的结构指针,
        perror("can not understand the host name");   //理解不了输入的地址
        exit(1);
    }

    hostname=argv[1];//取出地址名

    memset(&dest,0,sizeof dest);  //将dest中前sizeof(dest)个字节替换为0并返回s,此处为初始化,给最大内存清零
    dest.sin_family=PF_INET;  //PF_INET为IPV4，internet协议，在<netinet/in.h>中，地址族
    dest.sin_port=ntohs(0);   //端口号,ntohs()返回一个以主机字节顺序表达的数。
    dest.sin_addr=*(struct in_addr *)host->h_addr_list[0];//host->h_addr_list[0]是地址的指针.返回IP地址，初始化

    if((sockfd = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP))<0)
    { //PF_INEI套接字协议族，SOCK_RAW套接字类型，IPPROTO_ICMP使用协议，调用socket函数来创建一个能够进行网络通信的套接字。这里判断是否创建成功
        perror("raw socket created error");
        exit(1);
    }

    setuid(getuid());//getuid()函数返回一个调用程序的真实用户ID,setuid()是让普通用户可以以root用户的角色运行只有root帐号才能运行的程序或命令。
    pid=getpid(); //getpid函数用来取得目前进程的进程识别码
    printf("PID:%d\n",pid);
    set_sighandler();//对信号处理
    printf("Ping %s(%s): %d bytes data in ICMP packets.\n",argv[1],inet_ntoa(dest.sin_addr),datalen);

    if((setitimer(ITIMER_REAL,&val_alarm,NULL))==-1) //定时函数
        bail("setitimer fails.");


    recv_reply();//接收ping应答

    return 0;
}
//发送ping消息
void send_ping()
{

    struct ip *ip;   //ip为IP头部结构体
    struct icmp *icmp;   //icmp为ICMP头部结构体
    int len;
    int len1;
    icmp=(struct icmp *)(sendbuf);  //字符串指针
    icmp->icmp_type=ICMP_ECHO;//初始化ICMP消息类型type

    icmp->icmp_code=0;    //初始化消息代码code
    icmp->icmp_id=pid;   //把进程标识码初始给icmp_id
    icmp->icmp_seq=nsent++;  //发送的ICMP消息序号赋值给icmp序号
    gettimeofday((struct timeval *)icmp->icmp_data,NULL); // 获取当前时间
    memcpy(icmp->icmp_data+sizeof(timeval), hello, strlen(hello));
    len=8+sizeof(timeval)+strlen(hello);
    printf("%d\n",len);
    icmp->icmp_cksum=0;    //初始化
    icmp->icmp_cksum=checksum((u8 *)icmp,len);  //计算校验和
    sendto(sockfd,sendbuf,len,0,(struct sockaddr *)&dest,sizeof (dest)); //经socket传送数据
}
//接收程序发出的ping命令的应答
void recv_reply()
{
    int n;
    socklen_t len;
    int errno;
    n=nrecv=0;

    while(nrecv<4)
    {
        if((n=recvfrom(sockfd,recvbuf,sizeof recvbuf,0,(struct sockaddr *)&from,&len))<0)
        { //经socket接收数据,如果正确接收返回接收到的字节数，失败返回0.
            if(errno==EINTR)  //EINTR表示信号中断
                continue;
            bail("recvfrom error");
        }

        gettimeofday(&recvtime,NULL);   //记录收到应答的时间

        if(handle_pkt(n))    //接收到错误的ICMP应答信息

            continue;
        nrecv++;
    }

    get_statistics(nsent,nrecv);     //统计ping命令的检测结果
}
//计算校验和
u16 checksum(u8 *buf,int len)
{
    u32 sum=0;
    u16 *cbuf;

    cbuf=(u16 *)buf;

    while(len>1)
    {
        sum+=*cbuf++;
        len-=2;
    }

    if(len)
        sum+=*(u8 *)cbuf;

    sum=(sum>>16)+(sum & 0xffff);
    sum+=(sum>>16);

    return ~sum;
}
//ICMP应答消息处理
int handle_pkt(int len)
{
    struct ip *ip;
    struct icmp *icmp;

    int ip_hlen,icmplen;
    double rtt; // 往返时间
    struct timeval *sendtime;

    ip=(struct ip *)recvbuf;

    ip_hlen=ip->ip_hl<< 2;
    icmp=(struct icmp *)(recvbuf+ip_hlen);
    icmplen=len-ip_hlen;
    if(icmp->icmp_id!=pid)
        return -1;
    if(icmp->icmp_type!=ICMP_ECHOREPLY)
        return -1;

    sendtime=(struct timeval *)icmp->icmp_data; //发送时间

    if((recvtime.tv_usec-=sendtime->tv_usec)<0)
    {
        recvtime.tv_sec--;
        recvtime.tv_usec+=1000000;
    }
    recvtime.tv_sec-=sendtime->tv_sec;

    rtt=recvtime.tv_sec*1000.0+recvtime.tv_usec/1000.0;// 往返时间
    //打印结果
    printf("%d bytes from %s:icmp_seq=%u ttl=%d rtt=%.3f ms\n",
           icmplen, //icmp数据长度
           inet_ntoa(from.sin_addr),    //目的ip地址
           icmp->icmp_seq, //icmp报文序列号
           ip->ip_ttl,  //生存时间
           rtt);    //往返时间

    return 0;
}
//设置信号处理程序
void set_sighandler()
{
    act_alarm.sa_handler=alarm_handler;
    if(sigaction(SIGALRM,&act_alarm,NULL)==-1)  //sigaction()会依参数signum指定的信号编号来设置该信号的处理函数。参数signum指所要捕获信号或忽略的信号，&act代表新设置的信号共用体，NULL代表之前设置的信号处理结构体。这里判断对信号的处理是否成功。
        bail("SIGALRM handler setting fails.");

    act_int.sa_handler=int_handler;
    if(sigaction(SIGINT,&act_int,NULL)==-1)
        bail("SIGALRM handler setting fails.");
}
//统计ping命令的检测结果
void get_statistics(int nsent,int nrecv)
{
    printf("--- %s ping statistics ---\n",inet_ntoa(dest.sin_addr)); //将网络地址转换成“.”点隔的字符串格式。
    printf("%d packets transmitted, %d received, %0.0f%% ""packet loss\n",
           nsent,nrecv,1.0*(nsent-nrecv)/nsent*100);
}
//错误报告
void bail(const char * on_what)
{
    fputs(strerror(errno),stderr);  //:向指定的文件写入一个字符串（不写入字符串结束标记符‘\0’）。成功写入一个字符串后，文件的位置指针会自动后移，函数返回值为0；否则返回EOR(符号常量，其值为-1)。
    fputs(":",stderr);
    fputs(on_what,stderr);
    fputc('\n',stderr); //送一个字符到一个流中
    exit(1);
}

//SIGINT（中断信号）处理程序
void int_handler(int sig)
{
    get_statistics(nsent,nrecv);    //统计ping命令的检测结果
    close(sockfd);  //关闭网络套接字
    exit(1);
}
//SIGALRM（终止进程）处理程序
void alarm_handler(int signo)
{
    send_ping();    //发送ping消息

}
