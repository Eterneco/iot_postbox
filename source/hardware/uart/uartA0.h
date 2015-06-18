#ifndef __UART_A0_H
#define __UART_A0_H

#include "typeDefs.h"

#ifdef NOTERM
#define UART_PRINT(x, ...)
#define DBG_PRINT (x, ...)
#else
#define UART_PRINT UartA0Write
#define DBG_PRINT  UartA0Write
#endif

extern void   UartA0Init();
extern uInt8  UartA0Get();
extern int    UartA0Write(char *format, ...);


#endif
