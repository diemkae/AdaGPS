# AdaGPS
 This is my Raspberry Pi port of the Adafruit_GPS (arduino) library and parsing example
 Ported specifically to Rspbian/wheezy and tested using an SMK53 GPS receiver connected to the
 Pi's UART (/dev/ttyAMA0), running at 9600 baud.
 
 Note the following change to GPS.begin((char*)"/dev/ttyAMA0", 9600);
 
 Output (stdout) from a run looks like:
 
dmk@raspi ~/rpi%/AdaGPS $ parsing | tee logfile 
Adafruit_GPS.sendCommand:[$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28]
Adafruit_GPS.sendCommand:[$PMTK220,1000*1F]
Adafruit_GPS.sendCommand:[$PMTK605*31]
PMTK_Q_RELEASE:$PMTK705,AXN_1.30,0049,M49_20110517,*37

GPS.lastNMEA OK:1 FAILED:4
Time: 00:00:00.000 Date: 00/00/0
Fix: 0 quality: 0

GPS.lastNMEA OK:7 FAILED:5
Time: 20:04:37.000 Date: 26/01/15
Fix: 1 quality: 2
Location: 3706.952393 N, 8034.951660, W
Speed (knots): 0.000000
Angle: 305.070007
Altitude: 616.700012
Satellites: 6

GPS.lastNMEA OK:8 FAILED:4
Time: 20:04:39.000 Date: 26/01/15
Fix: 1 quality: 2
Location: 3706.952393 N, 8034.951660, W
Speed (knots): 0.000000
Angle: 305.070007
Altitude: 616.700012
Satellites: 6

...
