/*!
 * \file
 * \brief Hardware configuration file
 * \author Dawid Babula
 * \email dbabula@adventurous.pl
 *
 * \par Copyright (C) Dawid Babula, 2018
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#define DEBUG_ENABLED DEBUG_SYS_ENABLED
#define DEBUG_LEVEL DEBUG_SYS_LEVEL
#define DEBUG_APP_ID "SYS"

#include "system.h"
#include "system_timer.h"
#include "system_common.h"
#include <stdbool.h>
#include "debug.h"

#define SYSTEM_MAX_TASKS        (5)
#define STACK_CANARY            (0xC5U)

typedef struct
{
    SYSTEM_task_t task;
    uint32_t last_tick;
    uint16_t interval;
} task_data_t;


static task_data_t tasks[SYSTEM_MAX_TASKS];
static uint8_t task_counter;

void SYSTEM_stack_paint(void) __attribute__ ((naked)) __attribute__ ((section (".init1")));

void SYSTEM_stack_paint(void)
{
#if 0
    uint8_t *p = &_end;

    while(p <= &__stack)
    {
        *p = STACK_CANARY;
        p++;
    }
#else
    __asm volatile ("    ldi r30,lo8(_end)\n"
                    "    ldi r31,hi8(_end)\n"
                    "    ldi r24,lo8(0xc5)\n" /* STACK_CANARY = 0xc5 */
                    "    ldi r25,hi8(__stack)\n"
                    "    rjmp .cmp\n"
                    ".loop:\n"
                    "    st Z+,r24\n"
                    ".cmp:\n"
                    "    cpi r30,lo8(__stack)\n"
                    "    cpc r31,r25\n"
                    "    brlo .loop\n"
                    "    breq .loop"::);
#endif
}

uint16_t SYSTEM_get_stack_left(void)
{
    const uint8_t *p = &_end;
    uint16_t       c = 0;

    while(*p == STACK_CANARY && p <= &__stack)
    {
        p++;
        c++;
    }

    return c;
}

uint16_t SYSTEM_get_stack_size(void)
{
    return (&__stack - &_end);
}

void SYSTEM_register_task(SYSTEM_task_t task, uint16_t interval)
{
    ASSERT(task != NULL);
    ASSERT(task_counter != SYSTEM_MAX_TASKS);

    tasks[task_counter].task = task;
    tasks[task_counter].interval = interval;
    task_counter++;
}

void SYSTEM_main(void)
{
    uint8_t i = 0;

    for(i=0;i<task_counter;i++)
    {
        uint32_t curr_tick = SYSTEM_timer_get_tick();

        if(SYSTEM_timer_tick_difference(tasks[i].last_tick, curr_tick) >= tasks[i].interval)
        {
            tasks[i].task();
            tasks[i].last_tick = curr_tick;
        }
    }
}

void SYSTEM_init(void)
{
    SYSTEM_timer_init();
}
