# AdaGPS
 This is my Raspberry Pi port of the Adafruit_GPS (Arduino) GPS library and parsing example.
 
 Ported specifically to Raspbian/wheezy and tested using an SMK53 GPS receiver, connected to the
 Pi's UART (/dev/ttyAMA0), running at 9600 baud.
 
 Note the change to GPS.begin((char*)"/dev/ttyAMA0", 9600);
 

...
