/*! --------------------------------------------------------------------------
 *  @file    ex_11b_main.c
 *  @brief   Example of LED usage. The 4 user controlled LEDs will turn on 
 *           one by one.
 * Copyright 2019 (c) Frederic Mes, RTLOC.
 *
 * All rights reserved.
 *
 */
#include <zephyr.h>
#include <drivers/gpio.h>
#include <sys/printk.h>
#include <drivers/gpio.h>
#include <sys/util.h>

#include "port.h"

#define LOG_LEVEL 3
#include <logging/log.h>
LOG_MODULE_REGISTER(main);

/* Defines */
#define APP_HEADER  "\nDWM1001 & Zephyr\n"
#define APP_NAME    "Example 11b - LEDs\n"
#define APP_VERSION "Version - 1.0\n"
#define APP_LINE    "=================\n"

/* 
 * See ./build/zephyr/include/generated/generated_dts_board.conf for details
 */
#define GPIO_DRV_NAME       DT_LABEL(DT_NODELABEL(gpio0))

#define GPIO_OUT_PIN_RED    DT_GPIO_PIN(DT_ALIAS(led0), gpios)
#define GPIO_OUT_PIN_GREEN  DT_GPIO_PIN(DT_ALIAS(led1), gpios)
#define GPIO_OUT_PIN_RED2   DT_GPIO_PIN(DT_ALIAS(led2), gpios)
#define GPIO_OUT_PIN_BLUE   DT_GPIO_PIN(DT_ALIAS(led3), gpios)

const struct device * gpiob;

void led_red1_off(void)
{
    gpio_pin_set(gpiob, GPIO_OUT_PIN_RED, 1);
}
void led_green_off(void)
{
    gpio_pin_set(gpiob, GPIO_OUT_PIN_GREEN, 1);
}

void led_blue_off(void)
{
    gpio_pin_set(gpiob, GPIO_OUT_PIN_BLUE, 1);
}

void led_red2_off(void)
{
    gpio_pin_set(gpiob, GPIO_OUT_PIN_RED2, 1);
}

void led_red1_on(void)
{
    gpio_pin_set(gpiob, GPIO_OUT_PIN_RED, 0);
}

void led_green_on(void)
{
    gpio_pin_set(gpiob, GPIO_OUT_PIN_GREEN, 0);
}

void led_blue_on(void)
{
    gpio_pin_set(gpiob, GPIO_OUT_PIN_BLUE, 0);
}

void led_red2_on(void)
{
    gpio_pin_set(gpiob, GPIO_OUT_PIN_RED2, 0);
}

/**
 * Application entry point.
 */
int dw_main(void)
{
    int ret;

    /* Display application name on console. */
    printk(APP_HEADER);
    printk(APP_NAME);
    printk(APP_VERSION);
    printk(APP_LINE);
    
    /* Get GPIO device binding */
    gpiob = device_get_binding(GPIO_DRV_NAME);
    if (!gpiob) {
        printk("Cannot find %s!\n", GPIO_DRV_NAME);
        return -1;
    }

    /* Setup GPIO output */
    ret = gpio_pin_configure(gpiob, GPIO_OUT_PIN_RED, (GPIO_OUTPUT));
    if (ret) {
        printk("Error configuring " GPIO_DRV_NAME "%d!\n", GPIO_OUT_PIN_RED);
    }

    ret = gpio_pin_configure(gpiob, GPIO_OUT_PIN_GREEN, (GPIO_OUTPUT));
    if (ret) {
        printk("Error configuring " GPIO_DRV_NAME "%d!\n", GPIO_OUT_PIN_GREEN);
    }

    ret = gpio_pin_configure(gpiob, GPIO_OUT_PIN_BLUE, (GPIO_OUTPUT));
    if (ret) {
        printk("Error configuring " GPIO_DRV_NAME "%d!\n", GPIO_OUT_PIN_BLUE);
    }

    ret = gpio_pin_configure(gpiob, GPIO_OUT_PIN_RED2, (GPIO_OUTPUT));
    if (ret) {
        printk("Error configuring " GPIO_DRV_NAME "%d!\n", GPIO_OUT_PIN_RED2);
    }

    int i = 0;

    /* Main loop */
    while (1) {

        switch (i % 4) {
            
            case 0:
                led_red1_on();
                led_green_off();
                led_blue_off();
                led_red2_off();
                printk("red1\n");
                break;
            
            case 1:
                led_red1_off();
                led_green_on();
                led_blue_off();
                led_red2_off();
                printk("green\n");          
                break;
            
            case 2:
                led_red1_off();
                led_green_off();
                led_blue_on();
                led_red2_off();
                printk("blue\n");
                break;      
            
            case 3:
                led_red1_off();
                led_green_off();
                led_blue_off();
                led_red2_on();
                printk("red2\n");
                break;                      
        }
        i++;
        
        Sleep(500);
    }

    return 0;
}