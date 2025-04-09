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

#include <hardware/i2c.h>
#include <hardware/dma.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ADS7830 registers/messages
#define ADS7830_ADDRESS     0x48    // | 1 for read
#define ADS7830_CMD_CH0     0x8C    // last nibble = internal ref = on, A/D converter = on
#define ADS7830_CMD_CH1     0xCC

//globals
const uint16_t ADS7830_DMA_WRITE_CH0 = (((ADS7830_ADDRESS|1)<<8)|(ADS7830_CMD_CH0));
const uint16_t ADS7830_DMA_WRITE_CH1 = (((ADS7830_ADDRESS|1)<<8)|(ADS7830_CMD_CH1));
volatile uint8_t v_x = 0;           // voltages for x and y from joystick
volatile uint8_t v_y = 0;


//function to initialize the joystick i2c and dma
void joystick_init(voiid) {

}

void i2c0_init(void) {

}

void dma_init(void){

}

void i2c0_write(uint32_t nbytes, uint32_t* data) {

}

//prototype of dma write complete
void dma_write_complete(void){
    //stop condition
    IC_DATA_CMD.STOP = 1;
    i2c_write_byte_raw(i2c0, (ADS7830_ADDRESS|1));
}

void dma_read_complete(void){

}



