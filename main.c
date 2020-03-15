#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

void sigroutine(int signo){
	switch (signo){
	case SIGALRM:
		printf("Catch a signal -- SIGALRM \n");
		// signal(SIGALRM, sigroutine);
		break;
	case SIGVTALRM:
		printf("Catch a signal -- SIGVTALRM \n");
		// signal(SIGVTALRM, sigroutine);
		break;
	case SIGPROF:
		printf("Catch a signal -- SIGPROF \n");
		// signal(SIGPROF, sigroutine);
		break;
	}
	return;
}

int main()
{
	// old_value save old timer value
	struct itimerval ALRM_value, 
			 VTALRM_value,
			 PROF_value,
			 old_value;
	
	printf("process id is %d\n", getpid());
	
	signal(SIGALRM,   sigroutine);
	signal(SIGVTALRM, sigroutine);
	signal(SIGPROF,   sigroutine);
	
	ALRM_value.it_value.tv_sec       = 1;
	ALRM_value.it_value.tv_usec      = 0;
	ALRM_value.it_interval.tv_sec    = 1;
	ALRM_value.it_interval.tv_usec   = 0;
	setitimer(ITIMER_REAL, &ALRM_value, &old_value);
	
	VTALRM_value.it_value.tv_sec     = 0;
	VTALRM_value.it_value.tv_usec    = 500000;
	VTALRM_value.it_interval.tv_sec  = 0;
	VTALRM_value.it_interval.tv_usec = 500000;
	setitimer(ITIMER_VIRTUAL, &VTALRM_value, &old_value);

	PROF_value.it_value.tv_sec       = 0;
	PROF_value.it_value.tv_usec      = 250000;
	PROF_value.it_interval.tv_sec    = 0;
	PROF_value.it_interval.tv_usec   = 250000;
	setitimer(ITIMER_PROF, &PROF_value, &old_value);
	
	for(;;);
}
