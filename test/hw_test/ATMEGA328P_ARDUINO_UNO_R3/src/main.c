#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "project_config.h"
#if DEBUG_CONSOLE == ON
#include "debug.h"
#endif

#include "hw_test_main.h"

int main(void)
{

#if DEBUG_CONSOLE == ON
    // Init the debug UART allowing us to use `printf`
    debug_console_init();
#endif

    while (1)
    {
        main_hw_test();
    }
    return 0;
}