/**
 * Copyright (c) 2019 - Frederic Mes, RTLOC
 * 
 * This file is part of Zephyr-DWM1001.
 *
 *   Zephyr-DWM1001 is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Zephyr-DWM1001 is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Zephyr-DWM1001.  If not, see <https://www.gnu.org/licenses/>.
 * 
 */
#include <zephyr.h>
#include <sys/printk.h>

#define STACKSIZE 1024
#define PRIORITY 99
#define DELAY_TIME   K_MSEC(1000)

extern int dw_main(void);


#ifdef CONFIG_BT
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
#include "ble_device.h"

void bluetooth_thread(void * id, void * unused1, void * unused2)
{
    printk("%s\n", __func__);

    k_sleep(K_MSEC(500));

	ble_device_init();

	while(1) { /* spin */}
}

K_THREAD_DEFINE(bluetooth_id, STACKSIZE, bluetooth_thread, 
                NULL, NULL, NULL, PRIORITY, 0, 0);
#endif

#ifdef CONFIG_LIS2DH
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
#include "ex_13a_accelerometer.h"

void accel_thread(void * id, void * unused1, void * unused2)
{
    printk("%s\n", __func__);

    accel_init();

    while (1) { /* spin */}
}

K_THREAD_DEFINE(accel_id, STACKSIZE, accel_thread, 
                NULL, NULL, NULL, PRIORITY, 0, 0);
#endif

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
void main_thread(void * id, void * unused1, void * unused2)
{
    printk("%s\n", __func__);

    k_sleep( K_MSEC(1000));

	dw_main();

	while(1) { /* spin */}
}

K_THREAD_DEFINE(main_id, STACKSIZE, main_thread, 
                NULL, NULL, NULL, PRIORITY, 0, 0);
