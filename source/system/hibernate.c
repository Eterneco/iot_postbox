#include "hibernate.h"

#include "hw_types.h"
#include "utils.h"
#include "prcm.h"
#include "uartA0.h"
#include "rom_map.h"
#include "configure.h"
#include "wdt_if.h"



#define SLOW_CLK_FREQ           32768


void HibernateInit()
{
    //
    // Configure the HIB module GPIO wake up conditions
    //
	PRCMHibernateWakeUpGPIOSelect(PRCM_HIB_GPIO17, PRCM_HIB_FALL_EDGE);

    //
    // Enable the HIB GPIO
    //
	PRCMHibernateWakeupSourceEnable(PRCM_HIB_GPIO17);
}

void HibernateEnter()
{
    //
    // Enter debugger info
    //
    DBG_PRINT("HIB: Entering HIBernate...\n\r");
    MAP_UtilsDelay(80000);

    //
    // Enter HIBernate mode
    //
    MAP_PRCMHibernateEnter();
}

void HibernateWatchdog()
{
    MAP_PRCMHibernateIntervalSet(SLOW_CLK_FREQ);
    MAP_PRCMHibernateWakeupSourceEnable(PRCM_HIB_SLOW_CLK_CTR);

    DBG_PRINT("WDT: Entering HIBernate...\n\r");
    MAP_UtilsDelay(80000);
    MAP_PRCMHibernateEnter();
}
