

 WebTerm  
 =========================================================================
 Connection orientied cgi web ppty terminal, worte for security researchre and pentester 
 You may even use vim thru webterm cgi 



 Description
 ==========================================================================

 Webterm is a terminal which makes to be able to communicate with unix shell via 
 HTTP. it could be used over firewall that only allows HTTP (port 80).
 package consists with there modules. wtcgi.cgi, wterm, wtserver.
 
 * "wterm" is a client interface like CRT. 
 * "wtcgi.cgi" is traditional cgi program comunicates with a server using unix domain socket. 
 * "wtserver" is a domain socket server which manages pseudo terminal of sub shell process "/bin/sh"

 Package firstly released at http://underground.or.kr/project/webterm/ , 2002
 no more maintenanced, only for academic purpose ... 


 Install 
 ==========================================================================

 First, you should move your tarball to cgi-bin directory could be excutable 
 and read-writable by web user in your web server. 
 ( bcoz, server creates unix domain socket for comunication with wtcgi.cgi ) 
 
 And next, extract tar file  and type 'make'
 if there were no bugs in procedure and three modules which refered above 
 created, then server installation completly done.  
 if not, plz config your detail set in each source file or send email to me.
 
 Usage 
 ==========================================================================
 
 Unpack all pacakge in cgi forlder on your target server after pwned
 Run wtserver with privilege  equal with target web server 
 
 ```
 $ wtserver &
 ```
 
 And, please connect to your server thru the wterm
 
 ```
 $ wterm -h <target_ip> -p 80 -l /cgi-bin/wtcgi.cgi
 ```

 Changes
 ==========================================================================

 Confer 'ChangeLog' in this package


 Copying
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




