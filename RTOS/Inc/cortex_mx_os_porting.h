/**
 * @file           cortex_mx_os_porting.h
 * @author         Mohamed Ali Haoufa
 * @brief          
 * @version        0.1
 * @date           2025-04-15
 *
 *
 * @copyright      Copyright (c) 2024 Mohamed Ali Haoufa. All rights reserved.
 */

#ifndef INC_CORTEXMX_OS_PORTING_H_
#define INC_CORTEXMX_OS_PORTING_H_

#include "core_cm4.h"
#include "task_scheduler.h"

extern int _estack ;
extern int _eheap  ;
#define MainStackSize 	3072


#define OS_SET_PSP(add)              __asm volatile("mov r0,%0 \n\t msr PSP,r0" : : "r" (add) )
#define OS_GET_PSP(add)              __asm volatile("mrs r0,PSP \n\t mov %0,r0"   : "=r" (add) )

#define OS_SWITCH_SP_to_PSP          __asm volatile("mrs r0, CONTROL \n\t mov r1,#0x02 \n\t orr r0,r0,r1 \n\t msr CONTROL,r0")
#define OS_SWITCH_SP_to_MSP          __asm volatile("mrs r0, CONTROL \n\t mov r1,#0x05 \n\t and r0,r0,r1 \n\t msr CONTROL,r0")


//clear Bit 0 CONTROL register
#define OS_SWITCH_to_privileged   		__asm(" mrs r3, CONTROL  \n\t" \
										" lsr r3,r3,#0x1   \n\t"       \
										" lsl r3,r3,#0x1   \n\t"	   \
										" msr CONTROL, r3");

//set Bit 0 CONTROL register
#define OS_SWITCH_to_unprivileged		__asm(" mrs r3, CONTROL  \n\t" \
											  " orr r3,r3,#0x1   \n\t" \
											  " msr CONTROL, r3 ");

void trigger_OS_PendSV();
void Start_Ticker();
void HW_init();

#endif /* INC_CORTEXMX_OS_PORTING_H_ */
