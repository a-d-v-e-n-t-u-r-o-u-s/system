/*!
 * \file
 * \brief System time API
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
#ifndef SYSTEM_TIMER_H
#define SYSTEM_TIMER_H

#include <stdint.h>

/*!
 *
 * \addtogroup system
 * \ingroup modules
 * \brief System module
 */

/*@{*/

typedef void (*SYSTEM_timer_callback_t)(void);

/*!
 * \brief Registers system tick callback
 *
 * \callback function to be called in case of system tick triggers
 *
 * \retval 0 success, callback registered
 * \retval -1 failure
 */
int8_t SYSTEM_timer_register(SYSTEM_timer_callback_t callback);

/*!
 * \brief Gets system tick value
 *
 * \returns system tick value
 */
uint32_t SYSTEM_timer_get_tick(void);

/*!
 * \brief Gets difference between two system ticks values
 *
 * \param prev first system tick value for comparison
 * \param next second system tick value for comparison
 *
 * \returns difference value
 */
uint32_t SYSTEM_timer_tick_difference(uint32_t prev, uint32_t next);

/* \todo (DB) does nothing, maybe should be removed */
void SYSTEM_timer_delay(uint8_t val);

/*!
 * \brief Initializes system timer module
 */
uint8_t SYSTEM_timer_init(void);

/*@}*/
#endif
