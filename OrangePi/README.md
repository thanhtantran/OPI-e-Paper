# 2.13inch e-Paper HAT
Examples for Orange Pi Lite board
## Hardware/Software setup
### Orange Pi Lite
#### Hardware connection
If the board you get is the HAT version like 2.13inch e-Paper HAT, you can directly attach it on the 40PIN GPIO of Orange Pi (reversed compared to Raspberry Pi). Or you can wire it to Orange Pi with 8PIN cable.

|**Connect to Orange Pi** |||
|- |- |-|
|  e-Paper | BCM2835 | GPIO |
|VCC|3.3V|3.3V|
|GND|GND|GND|
|DIN|MOSI|19|
|CLK|SCLK|23|
|CS|CE1|26|
|DC|25|22|
|RST|17|11|
|BUSY|24|18|

#### Enable SPI interface

 - Add these two lines to `/boot/armbianEnv.txt`:
> overlays=spi-spidev
> param_spidev_spi_bus=0
```
sudo echo overlays=spi-spidev>>/boot/armbianEnv.txt;
sudo echo param_spidev_spi_bus=0>>/boot/armbianEnv.txt;
sudo reboot now;
```
 - Confirm that spi is accessible and make it available for all users :
```
ll /dev/spidev*;
```
![spidev0.0](https://lh3.googleusercontent.com/u/0/d/1yJRSVAcWzIsOMU8RPNHjI1d5xYdBLaBG=w1920-h937-iv1)

#### Libraries
##### WiringOP
    mkdir -m 777 /opt/WiringOP;
    git clone https://github.com/zhaolei/WiringOP.git -b h3 /opt/WiringOP;
    cd /opt/WiringOP;
    chmod +x ./build;
    sudo ./build;

 - Confirm that it worked by running the `gpio readall` command and confirming there is a BCM column:
 ![gpio readall](https://lh3.googleusercontent.com/u/0/d/14x9T6az7orXUInLT06qFlbyR_UlqtkYD=w1920-h937-iv1)

##### Python
```
# python2
sudo apt-get update
sudo apt-get install python-dev python-pip python-pil python-numpy
sudo pip install setuptools
sudo pip install wheel
sudo pip install OrangePi.GPIO
sudo pip install spidev
```
#### Download samples

 - Open a terminal and download samples from git:
```
git clone https://github.com/Masatrad-com/e-Paper.git /opt/e-Paper;
cd /opt/e-Paper/OrangePi
```
#### Running examples
##### C codes
Find the main.c file, uncomment the definition of e-Paper types, then compile and run the codes.
```
cd c
make clean
make
sudo ./epd
```
##### python

Run examples, xxx is the name of the e-Paper. For example, if you want to run codes of 2.13inch V2 e-Paper Module, you xxx should be epd_1in13_V2  
```
cd python/examples
# python2
sudo python xxx.py
```

 - Known issue: I still don't know why, but when I first run the python script for the first time after rebooting I get the following error:
 > INFO:root:epd2in13_V2 Demo
INFO:root:init and Clear
Traceback (most recent call last):
  File "examples/epd_2in13_V2_test.py", line 23, in <module>
    epd.init(epd.FULL_UPDATE)
  File "/opt/e-Paper/OrangePi/python/lib/waveshare_epd/epd2in13_V2.py", line 124, in init
    if (epdconfig.module_init() != 0):
  File "/opt/e-Paper/OrangePi/python/lib/waveshare_epd/epdconfig.py", line 70, in module_init
    self.GPIO.setup(self.CS_PIN, self.GPIO.OUT)
ValueError: This channel is already in use by system as SPI0_CS.

For the moment the only workaround that I found is runing first  a couple of times the c example. That frees the systemp SPI0_CS and enable communications with e-paper. I would be very grateful if anyonce could help here.
<!--stackedit_data:
eyJoaXN0b3J5IjpbMTcxNDk2ODQxNSw2NDQ5MzAxNzQsMTA1MD
E2OTU2OCwtMTMzMDA1MzcxMywtMTc3NjUwNjYzMCwtOTk3MjY0
NjEzLDU1NDU4MDc3OCwxMDU0NTM3OTMxLDgwODczNjU1NSwtNT
E5ODA4MjIsMTY2NTkzMjEwNiwxMzk4NzQ2NzksLTIzMTUyNjU4
NywtOTU2ODEzNjA4LC0xMjg3MDQwNjIzLDEzMDQ1MDM5LDQ3Nj
M4NDI1OSw3MzA3NzM4ODAsLTEwMzY1MDY5MjcsMTY4ODM4MjIw
OF19
-->