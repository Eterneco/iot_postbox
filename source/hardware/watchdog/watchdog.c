#include "watchdog.h"

#include "hw_wdt.h"
#include "hw_types.h"
#include "hw_memmap.h"
#include "wdt.h"
#include "prcm.h"
#include "rom.h"
#include "rom_map.h"
#include "hibernate.h"
#include "wdt_if.h"



#define WD_PERIOD_SEC             50


void WatchdogIntHandler(void);

void WatchdogInit()
{
#ifdef WATCHDOG_ON

    tBoolean bRetcode;
    unsigned long period = ((unsigned long)80000000 * WD_PERIOD_SEC);

    // Set up the watchdog interrupt handler.
    WDT_IF_Init(WatchdogIntHandler, period);

    bRetcode = MAP_WatchdogRunning(WDT_BASE);
    if(!bRetcode)
    {
       WDT_IF_DeInit();
    }

#endif
}

void WatchdogGo()
{
#ifdef WATCHDOG_ON

	MAP_WatchdogIntClear(WDT_BASE);

#endif
}


void WatchdogIntHandler(void)
{
#ifdef WATCHDOG_ON

	 HibernateWatchdog();

#endif
}
