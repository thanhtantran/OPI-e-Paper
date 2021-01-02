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
|CS|CE0|24|
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
 - Confirm that spi is accessible :
```
ll /dev/spidev*;
```
![spidev0.0](https://lh6.googleusercontent.com/SucDwCPKHGtDnbgmvXJsPbOkZISM687Tg1UocDhTPzyizZ4s5LwDgw0ob2fRY5sX00NA-JOvnn1NiQ=w1920-h937)

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

<!--stackedit_data:
eyJoaXN0b3J5IjpbMTM5ODc0Njc5LC0yMzE1MjY1ODcsLTk1Nj
gxMzYwOCwtMTI4NzA0MDYyMywxMzA0NTAzOSw0NzYzODQyNTks
NzMwNzczODgwLC0xMDM2NTA2OTI3LDE2ODgzODIyMDhdfQ==
-->