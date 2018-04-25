#include <sys/param.h>
#include <sys/cpuset.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
int main(int argc,char *argv[])
{
	int ret;
	cpusetid_t setid;

	cpusetid_t setid1;
	ret = cpuset(&setid);

	printf("ret= %d %s\n",ret,strerror(errno));
	ret =getpid();

	printf("ret= %d %s\n",ret,strerror(errno));
	ret = cpuset_getid(CPU_LEVEL_CPUSET,CPU_WHICH_PID,getpid(),&setid);
	printf("ret= %d %s\n",ret,strerror(errno));

	ret = cpuset_getid(CPU_LEVEL_ROOT,CPU_WHICH_PID,getpid(),&setid1);
	if(setid == setid1)
	{

	printf("ret\n");
	}

}
