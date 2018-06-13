adns_state   adns;
adns_query   query;
adns_answer   *answer;

int adns_init(adns_state *newstate_r, adns_initflags flags, FILE *diagfile /*0=>stderr*/);

例：adns_init(&adns,   adns_if_noenv,   0);

其中flags值如下

typedef enum {                 /* In general, or together the desired flags: */
 adns_if_none=        0x0000,                 /* no flags.  nicer than 0 for some compilers */
 adns_if_noenv=       0x0001,                /* do not look at environment */
 adns_if_noerrprint=  0x0002,               /* never print to stderr (_debug overrides) */
 adns_if_noserverwarn=0x0004,         /* do not warn to stderr about duff servers etc */
 adns_if_debug=       0x0008,               /* enable all output to stderr plus debug msgs */
 adns_if_logpid=      0x0080,                /* include pid in diagnostic output */
 adns_if_noautosys=   0x0010,           /* do not make syscalls at every opportunity */
 adns_if_eintr=       0x0020,                  /* allow _wait and _synchronous to return EINTR */
 adns_if_nosigpipe=   0x0040,            /* applic has SIGPIPE ignored, do not protect */
 adns_if_checkc_entex=0x0100,         /* consistency checks on entry/exit to adns fns */
 adns_if_checkc_freq= 0x0300           /* consistency checks very frequently (slow!) */
} adns_initflags;

int adns_submit(adns_state ads,
		const char *owner,
		adns_rrtype type,
		adns_queryflags flags,
		void *context,
		adns_query *query_r);

例：adns_submit(adns,   argv[1],   adns_r_a,  (adns_queryflags) 0,   NULL,   &query);

int adns_check(adns_state ads,
	       adns_query *query_io,
	       adns_answer **answer_r,
	       void **context_r);

例：adns_check(adns,   &query,   &answer,   NULL);

int adns_wait(adns_state ads,
	      adns_query *query_io,
	      adns_answer **answer_r,
	      void **context_r);

例：adns_wait(adns,   &query,   &answer,   NULL);

void adns_finish(adns_state ads);

例：adns_finish(adns);

#include "adns.h"
#include <sys/errno.h>
#include <sys/socket.h>                     
#include <netinet/in.h>                     
#include <arpa/inet.h>

int test_dns(char *host)  
{
    adns_state ads;
    adns_initflags flags;  
    flags = adns_if_nosigpipe | adns_if_noerrprint;
    adns_init(&ads, flags, NULL);
        
    adns_query quer = NULL;
    adns_submit(ads, host, (adns_rrtype) adns_r_a, (adns_queryflags) 0, NULL, &quer);
        
    int tryCount = -1;
    int adns_cname = 0;
    while(tryCount < 32) {
        tryCount += 1;
        
        adns_answer *ans;
        int res = adns_check(ads, &quer, &ans, NULL);
       
        if(res == 0) {
            
            if (ans->status == adns_s_prohibitedcname) {
                char cname[128];
                strncpy(cname, ans->cname, 127);
                cname[strlen(ans->cname)] = '\0';
    
                adns_query quer = NULL;
                adns_submit(ads, cname, (adns_rrtype) adns_r_addr, (adns_queryflags) 0, NULL, &quer);
    
                adns_cname = 1;
            } else { 
                
                if(adns_cname)
                    printf("ip: %s\n", ans->status == adns_s_ok ? inet_ntoa(ans->rrs.addr->addr.inet.sin_addr) : "no");
                else
                    printf("ip: %s\n", ans->status == adns_s_ok ? inet_ntoa(*(ans->rrs.inaddr)) : "no");
                adns_finish(ads);
                break;
            }
                
        }       
        else if (res == ESRCH || res == EAGAIN) {
            sleep(1);
        } else {
            printf("host(%s) is err!\n", host);
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    char host[128];

    while(1) {
        scanf("%s", host);
        if(strlen(host) == 3 && strcmp(host, "eof")) break;

        test_dns(host);
    }

    return 0;
}
                                                                                                                                                                                               

Makefile

CFLAGS= -g

TARGETS=libadns.a

LIBOBJS=types.o event.o query.o reply.o general.o setup.o transmit.o \
                parse.o poll.o check.o

all: testdns

testdns: testdns.c libadns.a
libadns.a: $(LIBOBJS)
                rm -f $@
                $(AR) cq $@ $(LIBOBJS)

clean:
        rm -f $(LIBOBJS) libadns.a *~ config.status

distclean: clean
        rm -f config.h .depend

$(LIBOBJS):     adns.h internal.h config.h