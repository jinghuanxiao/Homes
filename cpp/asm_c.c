#include <stdio.h>


int a = 10;
int b = 20;
int result ;

int main(int argc,char *argv[])
{
	__asm__ __volatile__(
			
			"movq a,%rax\n\t"
			"movq b,%rbx\n\t"
			"imulq %rbx,%rax\n\t"
			"movq %rax,result\n\t"
			);
	printf("the answer is %d\n",result);
	return 0;
}
