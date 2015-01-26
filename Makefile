ALL = parsing Adafruit_GPS.o

all: parsing

Adafruit_GPS.o: Adafruit_GPS.cpp Adafruit_GPS.h
	g++ -g -c Adafruit_GPS.cpp Adafruit_GPS.h 
	/bin/rm -f *.h.gch

parsing:	parsing.c Adafruit_GPS.o
	g++ -g -o parsing parsing.c Adafruit_GPS.o
	/bin/rm -f *.h.gch

clean:	
	/bin/rm -f $(ALL)
#ident "$Name:  $ $Header: /projRCS/rpi/AdaGPS/Makefile,v 1.3 2015/01/24 19:57:31 dmk%raspi Exp $"
