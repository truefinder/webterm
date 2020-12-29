/* wtserver.c
 * truefinder seo@igrus.inha.ac.kr
 */
#include <errno.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <assert.h>
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include "ptypair.h"

#define TMPFILE	"/tmp/local.sock"
#define BUFSIZE 4096

jmp_buf env ;
sigjmp_buf sigenv;
static int sfd , cfd ;


void 
close_domain(void)
{
#ifdef	DEBUGZ
	printf("DEBUG : server closed\n");
#endif
	unlink(TMPFILE);
}

void 
sig_handler( int signum )
{
	if ( signum == SIGALRM ) {
#ifdef	DEBUGZ
		printf("DEBUG : alarm\n");
#endif
		close(cfd) ;
		siglongjmp( sigenv, 1 );
	}
	
	if ( signum == SIGINT ) {
		exit(0);
	}
}

int
main( void )
{
	int master ; int pid ;
	char *name ; int i ; 
	char ch = 0;
	char buf[BUFSIZE];
	struct termios ot , t ;
	fd_set ready;
	int done = 0;
	int pipe;
	FILE *fp1, *fp2 ;
	int flag = 1;

	//socket
	struct sockaddr_un sa, ca;
	int  slen, clen ;

	//signal
	sigset_t sigs;
	struct sigaction sa_old;
	struct sigaction sa_new ;
	int mask;

	//timer
	struct sigaction siga;
	struct itimerval timer;


	master = get_master_pty(&name);
	if ( master < 0 ) {
		perror("ptypair: master open failed");
		exit(1);
	}

	pid = fork() ;
	if ( pid == 0 ) { //child
		int slave ;
		close(master);

		slave = get_slave_pty(name);
		if ( slave < 0 ) {
			perror("ptypair: slave open failed");
			exit(1);
		}
		free(name);

		setsid();

		ioctl(slave, TIOCSCTTY, NULL );

		dup2(slave, STDIN_FILENO );
		dup2(slave, STDOUT_FILENO );
		dup2(slave, STDERR_FILENO );
		
		execl("/bin/sh", "sh", 0 );

		exit(1);
	}

	//parent
	
	unlink(TMPFILE);
	atexit( close_domain);
	free(name);
	fp1 = fdopen( master, "r");	

	/*
	tcgetattr( master, &ot );
        t = ot ;
        t.c_lflag &= ~(ICANON | ISIG | ECHO | ECHOCTL | ECHOE |
                        ECHOK | ECHOKE | ECHONL | ECHOPRT );

        t.c_iflag |= IGNBRK;
        t.c_cc[VMIN] = 1;
        t.c_cc[VTIME] = 0;
        tcsetattr( master, TCSANOW, &t);
	*/

	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 250000;

	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 250000;

	signal( SIGALRM, sig_handler );
	signal( SIGINT, sig_handler );
	signal( SIGPIPE, SIG_IGN);

	sfd = socket( AF_UNIX, SOCK_STREAM, 0 );
	if ( sfd < 0 ) { perror("socket"); exit(-1); }

	sa.sun_family = AF_UNIX;
	strcpy( sa.sun_path, TMPFILE);
	slen = sizeof( sa.sun_family) + sizeof(sa.sun_path);

	bind( sfd, (struct sockaddr *) &sa, slen );
	listen( sfd, 5 );
	do {

		sigsetjmp( sigenv, 1 );

		cfd =  accept( sfd, (struct sockaddr*) &sa, &slen );
#ifdef DEBUGZ
		pritnf("DEBUG : accept client");
#endif

		read( cfd, &ch , 1 );
		write( master, &ch, 1 );

		//alarm(1); 
		setitimer( ITIMER_REAL, &timer, NULL );

		while(1){
			bzero( buf, sizeof(buf));
			i = read( master , buf, sizeof(buf)) ;
			if ( i <= 0   ) { 
				close( cfd ); break;
#ifdef DEBUGZ
				if ( i == 0 ) printf("it's i = 0 \n");
				else printf("it's i < 0\n");
#endif
			}
			write(cfd, buf, i);
#ifdef DEBUGZ
			printf("DEBUG : buf = [%s]", buf );
#endif
		}

		close( cfd ); 
		printf("DEBUG : sucked miss operation\n");

	} while (!done);

	/* this really doesn't matter because each time a master pty is
	** opened, the corresponding slave pty has its termios settings
	** reset
	**/
	//tcsetattr(STDIN_FILENO, TCSANOW, &ot);
	unlink(TMPFILE);
	exit(0);
}

