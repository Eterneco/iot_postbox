#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// simplelink includes
#include "device.h"

// driverlib includes
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_ints.h"
#include "interrupt.h"
#include "prcm.h"
#include "rom.h"
#include "rom_map.h"
#include "pin.h"
#include "timer.h"
#include "utils.h"
#include "pin_mux_config.h"
#include "system.h"


//Free_rtos/ti-rtos includes
#include "osi.h"

// email
#include "email.h"

// common interface includes
#ifndef NOTERM
#include "uart_if.h"
#endif
#include "gpio.h"
#include "gpio_if.h"
#include "configure.h"
#include "uartA0.h"
#include "time.h"
#include "network_if.h"
#include "udma_if.h"
#include "hibernate.h"



#define SLEEP_TIME              8000000
#define SPAWN_TASK_PRIORITY     9
#define OSI_STACK_SIZE          6000




// GLOBAL VARIABLES -- Start

uInt8			g_hibWakeUp = 0;
cInt8          	acSendBuff[TX_BUFF_SIZE];	 // 1024
cInt8          	acRecvbuff[RX_BUFF_SIZE]; 	 // 1024
SlSecParams_t 	SecurityParams = {0};  		 // AP Security Parameters



/********************************************************************************
   global procedures
********************************************************************************/

void SystemStartCheck()
{
	g_hibWakeUp = 0;

	if(MAP_PRCMSysResetCauseGet() == 0)
	{
		g_hibWakeUp = 0;
		DBG_PRINT("HIB: Wake up on Power ON\n\r");
	}
	else if(MAP_PRCMSysResetCauseGet() == PRCM_HIB_EXIT)
	{
		g_hibWakeUp = 1;
		DBG_PRINT("HIB: Woken up from Hibernate\n\r");
	}
}

static sInt16 Connect2AccessPoint()
{
    // Reset The state of the machine
    Network_IF_ResetMCUStateMachine();

    //
    // Start the driver
    Network_IF_InitDriver(ROLE_STA);

    // Initialize AP security params
    SecurityParams.Key = (signed char *) SECURITY_KEY;
    SecurityParams.KeyLen = strlen(SECURITY_KEY);
    SecurityParams.Type = SECURITY_TYPE;

    // Connect to the Access Point
    return(Network_IF_ConnectAP(SSID_NAME,SecurityParams));
}


/********************************************************************************
                           Email
********************************************************************************/


long  SetAdvancedEmailParameters(unsigned long destinationIp)
{
	SlNetAppEmailOpt_t    eMailParameters;

    // Set Email Server Parameters
    eMailParameters.Family  = AF_INET;
    eMailParameters.Port    = GMAIL_HOST_PORT;
    eMailParameters.Ip      = destinationIp;
    eMailParameters.SecurityMethod = SL_SO_SEC_METHOD_SSLV3;
    eMailParameters.SecurityCypher = SL_SEC_MASK_SSL_RSA_WITH_RC4_128_MD5;

    return (sl_NetAppEmailSet(SL_NET_APP_EMAIL_ID, NETAPP_ADVANCED_OPT, \
                      sizeof(SlNetAppEmailOpt_t),(unsigned char*)&eMailParameters));
}

long  SetSourceEmail()
{
    SlNetAppSourceEmail_t sourceEmailId;

    memcpy(sourceEmailId.Username,GMAIL_USER_NAME,strlen(GMAIL_USER_NAME)+1);

    return (sl_NetAppEmailSet(SL_NET_APP_EMAIL_ID,NETAPP_SOURCE_EMAIL, \
            strlen(GMAIL_USER_NAME)+1, (unsigned char*)&sourceEmailId));
}

long  SetSourceEmailPassword()
{
    SlNetAppSourcePassword_t sourceEmailPwd;

    memcpy(sourceEmailPwd.Password,GMAIL_USER_PASS,strlen(GMAIL_USER_PASS)+1);

    return (sl_NetAppEmailSet(SL_NET_APP_EMAIL_ID,NETAPP_PASSWORD, \
            strlen(GMAIL_USER_PASS)+1, (unsigned char*)&sourceEmailPwd));
}

long  SetDestinationEmail()
{
    SlNetAppDestination_t destEmailAdd;

    memcpy(destEmailAdd.Email,RCPT_RFC,strlen(RCPT_RFC)+1);


    return (sl_NetAppEmailSet(SL_NET_APP_EMAIL_ID,NETAPP_DEST_EMAIL, \
            strlen(RCPT_RFC)+1, (unsigned char *)&destEmailAdd));
}

long  SetEmailSubject()
{
	SlNetAppEmailSubject_t emailSubject;

	memcpy(emailSubject.Value,EMAIL_SUB,strlen(EMAIL_SUB)+1);


    return (sl_NetAppEmailSet(SL_NET_APP_EMAIL_ID,NETAPP_SUBJECT, \
            strlen(EMAIL_SUB)+1, (unsigned char *)&emailSubject));
}


long SetEmailMessage(char * message)
{
	char const  value[] = "Hi\r\n"  \
			              "From this site your postbox\r\n" \
						  "\r\n"  \
						  "New letter is Available !";

	if(strlen(value)>63)    return -1;

	memcpy(message,value,strlen(value));
	*(message + strlen(value)) = 0;
	return 1;
}

void  EmailHandleERROR(long error, char * servermessage)
{
    switch(error)
    {

        case SL_EMAIL_ERROR_INIT:   // Server connection could not be established
									DBG_PRINT((char*)"Server connection error.\r\n");
									break;

        case SL_EMAIL_ERROR_HELO:   // Server did not accept the HELO command from server
									DBG_PRINT((char*)"Server did not accept HELO:\r\n");
									DBG_PRINT((char*)servermessage);
									break;

        case SL_EMAIL_ERROR_AUTH:   // Server did not accept authorization credentials
									DBG_PRINT((char*)"Authorization unsuccessful, check username/password.\r\n");
									DBG_PRINT((char*)servermessage);
									break;

        case SL_EMAIL_ERROR_FROM:   // Server did not accept source email.
									DBG_PRINT((char*)"Email of sender not accepted by server.\r\n");
									DBG_PRINT((char*)servermessage);
									break;

        case SL_EMAIL_ERROR_RCPT:	// Server did not accept destination email
									DBG_PRINT((char*)"Email of recipient not accepted by server.\r\n");
									DBG_PRINT((char*)servermessage);
									break;

        case SL_EMAIL_ERROR_DATA:	// 'DATA' command to server was unsuccessful
									DBG_PRINT((char*)"smtp 'DATA' command not accepted by server.\r\n");
									DBG_PRINT((char*)servermessage);
									break;

        case SL_EMAIL_ERROR_MESSAGE: // Message body could not be sent to server
									DBG_PRINT((char*)"Email Message was not accepted by the server.\r\n");
									DBG_PRINT((char*)servermessage);
									break;

        case SL_EMAIL_ERROR_QUIT:   // Message could not be finalized
        						    DBG_PRINT((char*)"Connection could not be properly closed. Message not sent.\r\n");
									DBG_PRINT((char*)servermessage);
									break;
        default:
        							break;
  }
    	DBG_PRINT("\r\n");
}


void EmailSendTask()
{
    sInt16  apConnection;

	long ulStatus;
	unsigned long ulDestinationIP;

	char 				   l_message[64];
    SlNetAppServerError_t  sEmailErrorInfo;

    DBG_PRINT("Send Email Task Begin \n\r");


    while(1)
    {
        /******************* Connect to specific AP ***************************/
        apConnection = Connect2AccessPoint();

        if(apConnection < 0)
        {
            DBG_PRINT("can't connect to %s AP",SSID_NAME);
            break;
        }
        else
        {
            DBG_PRINT("connected to %s AP",SSID_NAME);
        }


        /********************* SEND EMAIL *************************************/

        // Get the serverhost IP address using the DNS lookup
        ulStatus = Network_IF_GetHostIP(GMAIL_HOST_NAME, &ulDestinationIP);
        if(ulStatus < 0)
        {
            DBG_PRINT("EMAIL SERVER DNS lookup failed. \n\r");
            break;
        }

        // Set Advanced Email Parameters
        ulStatus =  SetAdvancedEmailParameters(ulDestinationIP);
        if(ulStatus < 0)
        {
            DBG_PRINT("Set Advanced EMAIL Server Parameteres failed. \n\r");
            break;
        }

        // Set Source Email
        ulStatus =  SetSourceEmail();
        if(ulStatus < 0)
        {
            DBG_PRINT("Set Source EMAIL failed. \n\r");
            break;
        }

        // Set Source Email Password
        ulStatus =  SetSourceEmailPassword();
        if(ulStatus < 0)
        {
            DBG_PRINT("Set Source EMAIL Password failed. \n\r");
            break;
        }

        // Connect to Email Server
        ulStatus = sl_NetAppEmailConnect();
        if(ulStatus < 0)
        {
			DBG_PRINT("n\r Connect to Email Server Failed\r");
        	break;
        }

        // Set Destination Email
        ulStatus =  SetDestinationEmail();
        if(ulStatus < 0)
        {
            DBG_PRINT("Set Destination EMAIL failed. \n\r");
            break;
        }

        // Set Email Subject
        ulStatus =  SetEmailSubject();
        if(ulStatus < 0)
        {
            DBG_PRINT("Set EMAIL Subject failed. \n\r");
            break;
        }

        // Set Email Message
        ulStatus =  SetEmailMessage(l_message);
        if(ulStatus < 0)
        {
            DBG_PRINT("Set EMAIL message failed. \n\r");
            break;
        }

        // Send Email
        ulStatus = sl_NetAppEmailSend("","", l_message, &sEmailErrorInfo);
        if(ulStatus != SL_EMAIL_ERROR_NONE)
        {
        	EmailHandleERROR(ulStatus,(char*)sEmailErrorInfo.Value);
        	break;
        }

        DBG_PRINT("EMAIL HAS SENT \n\r");
        DBG_PRINT("\n\r");
        break;
    }

    // Stop the driver
    Network_IF_DeInitDriver();
    DBG_PRINT("Send Email Task End\n\r");
}



//--------------------------------------------------------------------------------

void SystemTaskManager(void *pvParameters)
{

    while(1)
    {
    	   if(g_hibWakeUp == 1) EmailSendTask();
    	   HibernateEnter();
    }

}

void SystemTaskCreate()
{
    // Initializing DMA
    UDMAInit();


    // Start the SimpleLink Host
    //
    VStartSimpleLinkSpawnTask(SPAWN_TASK_PRIORITY);

    //
    // Start the GetWeather task
    //
    osi_TaskCreate(SystemTaskManager,
                    (const signed char *)"system",
                    OSI_STACK_SIZE,
                    NULL,
                    1,
                    NULL );

}
