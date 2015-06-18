#include "uartA0.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "hw_types.h"
#include "hw_memmap.h"
#include "prcm.h"
#include "pin.h"
#include "uart.h"
#include "rom.h"
#include "rom_map.h"



void MessageSend(char *str)
{
#ifndef NOTERM
    if(str != NULL)
    {
        while(*str!='\0')
        {
            MAP_UARTCharPut(UARTA0_BASE,*str++);
        }
    }
#endif
}


void UartA0Init()
{

  MAP_UARTConfigSetExpClk(UARTA0_BASE,MAP_PRCMPeripheralClockGet(PRCM_UARTA0), 115200,
                         (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}





uInt8 UartA0Get()
{
   // Wait to receive a character over UART
   return ( MAP_UARTCharGet(UARTA0_BASE));
}


int UartA0Write(char *pcFormat, ...)
{
 int iRet = 0;
#ifndef NOTERM

  char *pcBuff, *pcTemp;
  int iSize = 256;
 
  va_list list;
  pcBuff = (char*)malloc(iSize);
  if(pcBuff == NULL)
  {
	  return -1;
  }
  while(1)
  {
      va_start(list,pcFormat);
      iRet = vsnprintf(pcBuff,iSize,pcFormat,list);
      va_end(list);
      if(iRet > -1 && iRet < iSize)
      {
          break;
      }
      else
      {
          iSize*=2;
          if((pcTemp=realloc(pcBuff,iSize))==NULL)
          { 
        	  MessageSend("Could not reallocate memory\n\r");
              iRet = -1;
              break;
          }
          else
          {
              pcBuff=pcTemp;
          }
          
      }
  }
  MessageSend(pcBuff);
  free(pcBuff);
  
#endif
  return iRet;
}
