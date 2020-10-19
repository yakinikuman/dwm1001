
# DWM1001 - ex_14b_spi0_slave

## Overview

This example project give a simple template for using the DWM1001 as a 'SPI Slave' device.
This allows the DWM1001 board to appear to a 'SPI Master' system as a SPI device. The accompanying spi_master.py script may be run on an appropriately configured (SPI enabled and Python 3 with py-spidev installed) Raspberry Pi to interact as master with the DWM1001 slave code.  This project was developed using a DWM1001-DEV board and a Raspberry Pi Zero W.

The focus of this project is to provide an example of SPI-Slave IO connectivity, and not so much the SPI-device "functionality".

Currently, this example does not implement a interrupt line to the SPI Master host, although the Device Tree does define a potential line for interrupts.

The choice using of "SPI_0" is due to "SPI-1" being used for DWM1000 communications. Also note that SPI_0 and I2C_0 can not operated at the same time, as the share a common serial controller on the nRF52 SoC. 

Verified working with baseline Zephyr branch v2.4.0.

## Hardware Setup

The SPI0 pins on the Pi should be connected to the corresponding pins on the DWM1001-DEV board's "Module Development Board RPi connector".  The pin mapping is somewhat user-configurable; see notes in nrf52_dwm1001.overlay.

Pi GPIO 10 (MOSI) <-----> DWM1001 [N].P06

Pi GPIO  9 (MISO) <-----> DWM1001 [N].P07

Pi GPIO 11 (SCLK) <-----> DWM1001 [N].P04

Pi GPIO  8 (CS)   <-----> DWM1001 [N].P03

Pi GND (any ground pin) <-----> DWM1001 GND (any ground pin)


## Building and Running
The build and running is similar to the other examples.
The only complexity is coordinating the operation of two SPI-based systems. But as a DWM1001 developer this is standard procedures.  ;-)
The spi_master.py script is meant to be run on the Raspberry Pi acting as SPI master. The DWM1001 SPI slave will receive a 2-byte user input from the Raspberry Pi over SPI, add 1 to the received value and return it back to the Pi.

## Sample Output


<u>
**Master Side (Raspberry Pi)**</u>

```
pi@raspberrypi:~/ $ python spi_master.py 
Send: 0x1234
Sending 0x1234 (4660)

Received 0x1235 (4661)

Send: 0x2345
Sending 0x2345 (9029)

Received 0x2346 (9030)

Send: 0x3456
Sending 0x3456 (13398)

Received 0x3457 (13399)

```


<u>
**Slave Side (DWM1001)**</u>

```
*** Booting Zephyr OS build zephyr-v2.4.0  ***
spi_slave_thread
SPI Slave example application
rx_data buffer at 0x20000e08
spi_slave_init: slave config @ 0x20000e0c: wordsize(8), mode(0/0/0)
spi_slave_init: SPI pin config -- MOSI(P0.6), MISO(P0.7), SCK(P0.4), CS(P0.3)
Received: 0x1234
Received: 0x2345
Received: 0x3456


```

