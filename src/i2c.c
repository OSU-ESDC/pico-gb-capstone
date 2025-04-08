//This file contains code to do I2C communication with an ADS7830
//By Gabriel Rodgers

#include <hardware/pio.h>
#include <hardware/clocks.h>
#include <hardware/dma.h>
#include <hardware/spi.h>
#include <hardware/sync.h>
#include <hardware/flash.h>
#include <hardware/timer.h>
#include <hardware/vreg.h>
#include <pico/bootrom.h>
#include <pico/stdio.h>
#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <sys/unistd.h>
#include <hardware/irq.h>
#include <hardware/i2c>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ADS7830 registers/messages
#define ADS7830_ADDRESS     0x48    // | 1 for read
#define ADS7830_CMD_CH0     0x8C    // last nibble = internal ref = on, A/D converter = on
#define ADS7830_CMD_CH1     0xCC



