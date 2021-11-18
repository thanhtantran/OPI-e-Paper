#!/usr/bin/python
# -*- coding:utf-8 -*-
import sys
import os
picdir = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'pic')
libdir = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'lib')
if os.path.exists(libdir):
    sys.path.append(libdir)

import logging
from waveshare_epd import epd2in7
import time
from PIL import Image,ImageDraw,ImageFont
import traceback

logging.basicConfig(level=logging.DEBUG)

try:

    logging.info("epd2in7 Demo")   
    epd = epd2in7.EPD()
    
    '''2Gray(Black and white) display'''
    logging.info("init and Clear")
    epd.init()
    epd.Clear(0xFF)
    font24 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 24)
    font18 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 18)
    font35 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 35)
   
    # Drawing on the Vertical image
    logging.info("Drawing on ...")
    Limage = Image.new('1', (epd.width, epd.height), 255)  # 255: clear the frame
    bmp = Image.open(os.path.join(picdir, 'logo.bmp'))
    draw = ImageDraw.Draw(Limage)
    draw.text((20, 170), u'Orange Pi Vietnam', font = font18, fill = 0)
    draw.text((10, 200), u'https://orangepi.vn', font = font18, fill = 0)
    Limage.paste(bmp, (10,10))    
    epd.display(epd.getbuffer(Limage))

    time.sleep(60)
    
    logging.info("Clear...")
    epd.Clear(0xFF)
    logging.info("Goto Sleep...")
    epd.sleep()
    time.sleep(3)
    
    epd.Dev_exit()
        
except IOError as e:
    logging.info(e)
    
except KeyboardInterrupt:    
    logging.info("ctrl + c:")
    epd2in7.epdconfig.module_exit()
    exit()
