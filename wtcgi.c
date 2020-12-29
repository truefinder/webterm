/* wtcgi.c
 * truefinder, seo@igrus.inha.ac.kr
 */
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>

#define TMPFILE	"/tmp/local.sock"

void print_header(void);

main()
{
	struct sockaddr_un to;
	int  s;
	int  tolen, len, n, maxlen;
	char msg[512], inbuf[512];
	FILE *fp;
	int i;
	char *ch;
	maxlen = 512;

	len = atol(getenv("CONTENT_LENGTH"));
	ch = (char*)malloc( sizeof(char)*(len+1) );
	fgets( ch , len + 1 , stdin);
	
	print_header();

#ifdef	DEBUGZ
	printf("CLIENT KEY IS LIKE  %c(%x)\n", *ch , *ch);
#endif


	s = socket(AF_UNIX,SOCK_STREAM,0);

	to.sun_family = AF_UNIX;       
	strcpy(to.sun_path, TMPFILE );
	tolen = sizeof(to.sun_family) + sizeof(to.sun_path);
	connect(s,(struct sockaddr *) &to, tolen);

	write( s, ch, 1 );
	while( (i =read(s,inbuf, sizeof(inbuf)))){
		printf("%s", inbuf);
		bzero( inbuf, sizeof(inbuf));
	}

	close(s);                      
}

void print_header(void)
{
	printf("Content-Type : text/html\n\n");
}

