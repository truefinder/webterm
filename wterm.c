/* wterm.c
 * truefinder, seo@igrus.inha.ac.kr
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <getopt.h>
#include "kbhit.h"

void print_banner(void);
void print_usage( char *argv[]);

#define BUFSIZE	4096
#define HTTP_METHOD "POST"
#define HTTP_PROTO "HTTP/1.0\r\nContent-Length: 1\r\n\r\n"

int
main( int argc, char *argv[] )
{
	char cmd[1024];
	char *msg_h = HTTP_METHOD; 	
	char *msg_t = HTTP_PROTO;
	char ch ;
	int len, i, j ;

	struct sockaddr_in s ;
	int sock; int n;
	char buf[BUFSIZE];
	char *needle;

	static char *optstr = "h:p:l:";
	char oc;
	char *host;
	char *location;
	char *port;

	fd_set fds ;

	if ( argc < 3 ) {
		print_usage(argv);
		exit(0);
	}

	while( (oc = getopt( argc, argv, optstr)) != -1 )  {
		switch (oc) {
			case 'h':
				host = optarg;
				break;
			case 'p':
				port = optarg;
				break;
			case 'l':
				location= optarg;
				break;
			default:
				exit(-1);
		}
	}
	printf("%s %s %s \n", host ,port, location);

	print_banner();


	init_keyboard();
	
	do {

		if ( kbhit()) {
			ch = readch();
			if (ch == '\n') ch = '\r';
			
		} else continue;

		sprintf( cmd , "%s %s %s%c", msg_h, location, msg_t, ch);
		len = strlen(cmd);
		
		sock = socket( PF_INET, SOCK_STREAM, 0 );
		if ( sock < 0 ){
			perror("socket");
			exit(0);
		}

		bzero( &s, sizeof(s) );
		s.sin_family = PF_INET ;
		s.sin_port = htons(atoi(port));
		s.sin_addr.s_addr = inet_addr(host);

		if ( connect( sock , (struct sockaddr*)&s, sizeof(s) ) <0 ) {
			perror("connect");
			exit(0);
		}

		write( sock, cmd , len );

		bzero( buf, sizeof(buf) );
		i = read( sock, buf, sizeof(buf) );

		needle = strstr(buf, "\r\n\r\n" );
		needle += 4;
		j = strlen( needle);
	
		write( STDOUT_FILENO, needle, j );
		
		close(sock);

	} while(1);

	close_keyboard();

	// Author : Seunghyun Seo 
	// Last update : at Aug 24 03:20:31 KST 2002
	// seo@igrus.inha.ac.kr , frog@hackerslab.com
				
}


void
print_usage(char* argv[])
{
	fprintf(stderr, "Usage : %s -h [ip] -p [port] -l [location]\n", argv[0] );
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "\t[ip] host ip\n" );
	fprintf(stderr, "\t[port] port of webserver\n" );
	fprintf(stderr, "\t[location] location of wtcgi.cgi\n\n" );
	fprintf(stderr, "\tex)\n" );
	fprintf(stderr, "\t%s -h 192.168.1.1 -p 80 -l /cgi-bin/wtcgi.cgi\n", argv[0] );
}

void 
print_banner(void)
{
	printf("+-----------------------------------------------------------+\n");
	printf("|                                                           |\n");
	printf("|           Welcome to Web Terminal                         |\n");
	printf("|                                                           |\n");
	printf("|                            by truefinder                  |\n");
	printf("|                  seo@igrus.inha.ac.kr, frog@hackerslab.com|\n");
	printf("|                                                           |\n");
	printf("+-----------------------------------------------------------+\n");
}

