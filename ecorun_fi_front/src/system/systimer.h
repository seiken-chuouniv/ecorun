/*
 * systimer.h
 *
 *  Created on: 2015/04/03
 *      Author: Yoshio
 */

#ifndef CORE_SYSTIMER_H_
#define CORE_SYSTIMER_H_

#if defined(__cplusplus)
extern "C"
{
#endif

void systimer_init(void);

typedef struct
{
	uint32_t high_part;
	uint32_t low_part;
} systime_t;

systime_t systimer_tick(void);
uint32_t systimer_freq(void);

#if defined(__cplusplus)
}
#endif

#endif /* CORE_SYSTIMER_H_ */
