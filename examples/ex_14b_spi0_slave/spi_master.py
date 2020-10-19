#Script to run on Raspberry Pi
#Pinout - see example 14b overlay file
import spidev
import time
spi = spidev.SpiDev()

bus = 0 # spi bus 0 or 1
device = 0 # chip select

spi.open(bus,device) #opens /dev/spidev<bus>.<device>

spi.max_speed_hz = 500000
spi.mode = 0

while(1):
    #Get user input (2 bytes)
    send_data = int(input('Send: 0x'),16)
    print("Sending 0x%x (%d)\n" % (send_data,send_data))
    send_array = send_data.to_bytes(2, byteorder = 'little')
    
    spi.writebytes(send_array) # writebytes wants an array of bytes
    #time.sleep(1.0)

    #DWM1001 should +1 to the user input value and return
    rcvd_array = spi.readbytes(2)
    rcvd_data = int.from_bytes(rcvd_array, byteorder = 'little')
    print("Received 0x%x (%d)\n" % (rcvd_data,rcvd_data))

