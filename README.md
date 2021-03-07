

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
 Now no more maintenanced, only for academic purpose ... 


 Install 
 ==========================================================================

 ```
 $ git clone git@github.com:truefinder/webterm.git
 $ cd webterm 
 $ make 
 ```
 
 Please make sure your pwned cgi-bin directory which is excutable, 
 because wtserver creates unix domain socket for comunication to wtcgi.cgi
 
 
 Usage 
 ==========================================================================
 
 Install pacakge in cgi forlder on your target server after pwned
 Run wtserver with privilege  equal with target web server 
 
 ```
 (pwned server)$ wtserver &
 ```
 
 And, please connect to your server thru the wterm
 
 ```
 (your linux)$ wterm -h <target_ip> -p 80 -l /cgi-bin/wtcgi.cgi
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


 Contact
 ======================================================================

 Seunghyun Seo



