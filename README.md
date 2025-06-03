# RP2040-GB for Pico-GB

This is a fork of the [RP2040-GB Game Boy (DMG) emulator from deltabeard](https://github.com/deltabeard/RP2040-GB). RP2040-GB is a Game Boy (DMG) emulator Peanut-GB on the Raspberry Pi RP2040 microcontroller, using an ILI9225 screen. Runs at more than 70 fps without audio emulation. With frame skip and interlacing, can run at up to 120 fps.

This fork includes changes done by me for [Pico-GB](https://www.youmaketech.com/pico-gb-gameboy-emulator-handheld-for-raspberry-pi-pico/):
* push buttons support
* overclocking to 266MHz for more accurate framerate (~60 FPS)
* I2S sound support (44.1kHz 16 bits stereo audio)
* SD card support (store roms and save games) + game selection menu
* automatic color palette selection for some games (emulation of Game Boy Color Bootstrap ROM) + manual color palette selection

Pico-GB is a [3d-printed Game Boy emulator handheld gaming console for Raspberry Pi Pico](https://www.youmaketech.com/pico-gb-gameboy-emulator-handheld-for-raspberry-pi-pico/) that ressembles to the original Nintendo Game Boy released in 1989.

# Videos
* [Let's build a Game Boy Emulator on a Breadboard!](https://youtu.be/ThmwXpIsGWs)
* [Build the ULTIMATE GameBoy Emulator for Raspberry Pi Pico](https://youtu.be/yauNQSS6nC4)

# Hardware
## What you need
* (1x) [Raspberry Pi Pico](https://amzn.to/3rAcmDy)
* (1x) [2.2inch ILI9225 176×220 LCD Display Module](https://amzn.to/3aNAMD7)
* (1x) [FAT 32 formatted Micro SD card + adapter](https://amzn.to/3ICKzcm) with roms you legally own. Roms must have the .gb extension and must be copied to the root folder.
* (1x) [MAX98357A amplifier](https://www.youmaketech.com/max98357)
* (1x) [2W 8ohms speaker](https://amzn.to/3ikDy6S)
* (8x) [Micro Push Button Switch, Momentary Tactile Tact Touch, 6x6x6 mm, 4 pins](https://amzn.to/3dyXBsx)
* (1x) [Solderable Breadboard](https://amzn.to/3lwvfDi)
* [Dupont Wires Assorted Kit (Male to Female + Male to Male + Female to Female)](https://amzn.to/3HtbvdO)
* [Preformed Breadboard Jumper Wires](https://amzn.to/3rxwVjM)

DISCLAIMER: Some links are affiliate links. As an Amazon Associate I receive a small commission (at no extra cost to you) if you make a purchase after clicking one of the affiliate links. Thanks for your support!

## Setting up the hardware
[Pico-GB assembly instructions, circuit diagrams, 3d printed files etc.](https://www.youmaketech.com/pico-gb-gameboy-emulator-handheld-for-raspberry-pi-pico/)

# Pinout
* UP = GP2
* DOWN = GP3
* LEFT = GP4
* RIGHT = GP5
* BUTTON A = GP6
* BUTTON B = GP7
* SELECT = GP8
* START = GP9
* SD MISO = GP12
* SD CS = GP13
* SD CSK = GP14
* SD MOSI = GP15
* LCD CS = GP17
* LCD CLK = GP18
* LCD SDI = GP19
* LCD RS = GP20
* LCD RST = GP21
* LCD LED = GP22
* MAX98357A DIN = GP26
* MAX98357A BCLK = GP27
* MAX98357A LRC = GP28

# Flashing the firmware
* Download RP2040_GB.uf2 from the [releases page](https://github.com/YouMakeTech/Pico-GB/releases)
* Push and hold the BOOTSEL button on the Pico, then connect to your computer using a micro USB cable. Release BOOTSEL once the drive RPI-RP2 appears on your computer.
* Drag and drop the UF2 file on to the RPI-RP2 drive. The Raspberry Pi Pico will reboot and will now run the emulator.

# Preparing the SD card
The SD card is used to store game roms and save game progress. For this project, you will need a FAT 32 formatted Micro SD card with roms you legally own. Roms must have the .gb extension.

* Insert your SD card in a Windows computer and format it as FAT 32
* Copy your .gb files to the SD card root folder (subfolders are not supported at this time)
* Insert the SD card into the ILI9225 SD card slot using a Micro SD adapter

# Building from source
The [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) is required to build this project. 
To start, clone the SDK in a known folder (labeled as sdk-path in future commands), update CMake and submodules, and export the pico sdk path:
```
git clone git@github.com:raspberrypi/pico-sdk.git
git submodule update --init
sudo apt install cmake python3 build-essential gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib 
export PICO_SDK_PATH=<sdk-path>
```
Clone this repository and create a build folder:
```
git clone git@github.com:osu-esdc/pico-gb-capstone.git
cd pico-gb-capstone
mkdir build
cd build
```

Build a Makefile for the project (no debugging):
```
cmake ..
```

Build a Makefile for the project (with debugging):
```
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

Create the executable and program the Pico:
```
make
sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program RP2040_GB.elf verify reset exit"
```

For debugging using a Pico Tool (using gdb server and client):
Run the following in one window:
```
sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000"
```
Then run this in the other window:
```
arm-none-eabi-gdb
(gdb) start_pico
```
For tips on setting up debugging tools, follow the (arm GNU Toolchain setup guide)[https://github.com/osu-esdc/Arm-GNU-Toolchain-Setup]


# Known issues and limitations
* No copyrighted games are included with Pico-GB / RP2040-GB. For this project, you will need a FAT 32 formatted Micro SD card with roms you legally own. Roms must have the .gb extension.
* The RP2040-GB emulator is able to run at full speed on the Pico, at the expense of emulation accuracy. Some games may not work as expected or may not work at all. RP2040-GB is still experimental and not all features are guaranteed to work.
* RP2040-GB is only compatible with [original Game Boy DMG games](https://en.wikipedia.org/wiki/List_of_Game_Boy_games) (not compatible with Game Boy Color or Game Boy Advance games)
* Repeatedly flashing your Pico will eventually wear out the flash memory (Pico is qualified for min. 100K flash/erase cycles)
* The emulator overclocks the Pico in order to get the emulator working fast enough. Overclocking can reduce the Pico’s lifespan.
* Use this software and instructions at your own risk! I will not be responsible in any way for any damage to your Pico and/or connected peripherals caused by using this software. I also do not take responsibility in any way when damage is caused to the Pico or display due to incorrect wiring or voltages.

# License
MIT
