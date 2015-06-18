#ifndef __CONFIGURE_H
#define __CONFIGURE_H

#include "typeDefs.h"

/********************************************************************************
    network connection
********************************************************************************/
#define SSID_NAME               "LG-E610_8464"              /* AP SSID */
#define SECURITY_TYPE            SL_SEC_TYPE_WPA_WPA2       /* Security type (OPEN or WEP or WPA)*/
#define SECURITY_KEY            "password"                  /* Password of the secured AP */



/********************************************************************************
    EMAIL
********************************************************************************/

#define EMAIL_SUB               "[postbox no.1] New Letter !"	          // email title
#define GMAIL_HOST_NAME         "smtp.gmail.com"			  // gmail smtp server
#define GMAIL_HOST_PORT          465				          // gmail smtp port

#define GMAIL_USER_NAME         "iot.postbox@gmail.com"			  /* gmail account    */
#define GMAIL_USER_PASS         "password"				  /* gmail password   */
#define RCPT_RFC                "<name.surname@ti.com.pl>"                /* recipient e-mail */



#endif
