ALL = parsing Adafruit_GPS.o hdeps

all: parsing

Adafruit_GPS.o: Adafruit_GPS.cpp Adafruit_GPS.h
	g++ -g -c Adafruit_GPS.cpp Adafruit_GPS.h 
	/bin/rm -f *.h.gch

parsing:	parsing.c Adafruit_GPS.o
	g++ -g -o parsing parsing.c Adafruit_GPS.o
	/bin/rm -f *.h.gch

clean:	
	/bin/rm -f $(ALL)
#ident "$Name:  $ $Header: /projRCS/rpi/AdaGPS/Makefile,v 1.4 2015/01/27 16:10:15 dmk%raspi Exp $"
