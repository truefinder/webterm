

 WebTerm  
 =========================================================================
 connection orientied cgi web terminal, worte for pentester 



 DESCRIPTION
 ==========================================================================

  Wterm is terminal which make be able to communicate with unix shell via 
 HTTP. it could be used over firewall that allow only HTTP (port 80).
 there are three modules in this package. wtcgi.cgi, wterm, wtserver.
 "wterm" is a client interface like CRT. "wtcgi.cgi" is traditional 
 cgi program comunicates server with unix domain socket. and "wtserver" 
 is a domain socket server which manages pseudo terminal of sub process 
 "/bin/sh"

 The latest information about Wterm can be found at :
 http://underground.or.kr/project/webterm/


 INSTALL & USAGE 
 ==========================================================================

 First, you should move your tarball to cgi-bin directory could be excutable 
 and read-writable by web user in your web server. 
 ( bcoz, server creates unix domain socket for comunication with wtcgi.cgi ) 
 
 And next, extract tar file  and type 'make'
 if there were no bugs in procedure and three modules which refered above 
 created, then server installation completly done.  
 if not, plz config your detail set in each source file or send email to me.
 
 Next, run server with privilege  equal to 
 web server
 ex)
	./wtserver &

 and move wterm into your linux box which use as terminal client 
 Now, you can connect your server with your wterm
 ex)
	./wterm -h 192.168.1.200 -p 80 -l /cgi-bin/wtcgi.cgi


 CHANGES
 ==========================================================================

 Confer 'ChangeLog' in this package


 COPYING
 ==========================================================================

 This program is free software; you can  redistribute it and/or modify
 it under the terms  of the GNU General Public  License as published by
 the  Free Software Foundation; either version  2,  or (at your option)
 any later version.

 This program is distributed  in the hope that  it will be  useful, but
 WITHOUT    ANY  WARRANTY;  without   even   the  implied  warranty  of
 MERCHANTABILITY  or  FITNESS FOR  A PARTICULAR   PURPOSE.  See the GNU
 General Public License for more details.

 You should  have received a  copy of  the GNU  General Public  License
 along with   this  program; if   not,  write  to   the Free   Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


 WARNNING !  It's for only educational purpose and warning to ppls
 about senstive security of MSN messenger.
 i have no responsibility for usnig this program for another purpose.

 WTERM - Web Terminal
 (C) COPYRIGHT Seunghyun Seo
 All right reserverd ( Aug 27, 2002 )


 CONTACT
 ======================================================================

 Send bug (error) reports, questions and comments to below email

 Seunghyun Seo, seo@igrus.inha.ac.kr or frog@hackerslab.com
 http://igrus.inha.ac.kr/~seo/




