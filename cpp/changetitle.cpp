#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
extern char** environ;
void my_initproctitle(char* argv[], char** last);
void my_setproctitle(char* argv[], char** last, char* title);
int main(int argc, char* argv[])
{
     char s_title[] = "ymc title ymc title";
     char* p_last = NULL;

     my_initproctitle(argv, &p_last);
     my_setproctitle(argv, &p_last, s_title);
     while(1)
   {
         system("ps -ef|awk '$8 ~ /ymc/ {print $0}'");
         sleep(10);
    }
     return 0;
 }



void my_initproctitle(char* argv[], char** last)
{
     int i = 0;
     char* p_tmp = NULL;
     size_t i_size = 0;

     for(i = 0; environ[i]; i++){

         i_size += strlen(environ[i]) + 1;

     }

     p_tmp = (char*)malloc(i_size);

     if(p_tmp == NULL){

         return ;
     }

     *last = argv[0];

     for(i = 0; argv[i]; i++){
         *last += strlen(argv[i]) + 1;
     }

     for(i = 0; environ[i]; i++){
         i_size = strlen(environ[i]) + 1;
         *last += i_size;

         strncpy(p_tmp, environ[i], i_size);
         environ[i] = p_tmp;
         p_tmp += i_size;

     }

     (*last)--;
     return ;
 }
 void my_setproctitle(char* argv[], char** last, char* title)

 {
     char* p_tmp = NULL;
     p_tmp = argv[0];
     /* memset(p_tmp, 0, *last - p_tmp); */
     strncpy(p_tmp, title, *last - p_tmp);
     return ;
 }
