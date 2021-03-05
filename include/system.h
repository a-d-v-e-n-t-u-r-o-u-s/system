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
#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>


extern uint8_t _end;
extern uint8_t __stack;

typedef void (*SYSTEM_task_t)(void);

uint16_t SYSTEM_get_stack_left(void);
uint16_t SYSTEM_get_stack_size(void);
void SYSTEM_register_task(SYSTEM_task_t task, uint16_t interval);
void SYSTEM_main(void);
void SYSTEM_init(void);

#endif // SYSTEM_H
