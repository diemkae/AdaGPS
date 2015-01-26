// Test code for Adafruit GPS modules using MTK3329/MTK3339 driver
//
// This code shows how to listen to the GPS module in an interrupt
// which allows the program to have more 'freedom' - just parse
// when a new NMEA sentence is available! Then access data when
// desired.
//
// Tested and works great with the Adafruit Ultimate GPS module
// using MTK33x9 chipset
//    ------> http://www.adafruit.com/products/746
// Pick one up today at the Adafruit electronics shop 
// and help support open source hardware & software! -ada
/*
 
20150125 Originally written to run with Arduino core, this has been
Ported to run with Raspberry Pi Linux (raspbian wheezy) by David Knight
(diemkae@gmail.com) and tested with SKM53 GPS receiver running at
9600 baud.

 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

//#include <Adafruit_GPS.h>
#include "Adafruit_GPS.h"

extern int debug;  // lets parsing.c control debug output

// on the Pi, we use fopen() and fgetc() to read the GPS "messages"
Adafruit_GPS GPS (NULL);

void
setup ()
{
  int rc = 0;

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800

  GPS.begin ((char *)"/dev/ttyAMA0",9600);

  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand ((char *) PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand((char *)PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time

  // Set the update rate
  GPS.sendCommand ((char *) PMTK_SET_NMEA_UPDATE_1HZ);	// 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Ask for firmware version
  //mySerial.println(PMTK_Q_RELEASE);
  //    printf ("setup():%s\n", PMTK_Q_RELEASE);
  //
  // I believe that should be a sendCommand(), as below. See also change
  // to Adafruit_GPS.cpp to recognize & print the response sentence (dmk)
  //
  GPS.sendCommand ((char *) PMTK_Q_RELEASE);
  // don't sleep here, or the PMTK_Q_RELEASE response will be missed.
}

unsigned int now = 0;
unsigned int lastPrint = 0;
unsigned int goodParse = 0;
unsigned int badParse = 0;

void
loop ()				// run over and over again
{
  char c = GPS.read ();

  now = time (0);

  // if a good NMEA sentence is received, we can check the checksum, parse it...
  //
  if (GPS.newNMEAreceived ())
  {
    if (GPS.parse (GPS.lastNMEA ()))
	{  	// call to GPS.lastNMEA() sets the newNMEAreceived() flag to false
	  goodParse++;
	}
      else
	{
	  badParse++;
	  if(debug)printf("GPS.parse ERROR\n");
	  return;  // ignore bad sentence, wait for another
	}
    //  GPS.lastNMEA parse OK, see if it's time to print
    if (now >= lastPrint + 2)
	{
	  lastPrint = now;
	  printf ("\nGPS.lastNMEA OK:%d FAILED:%d\n", goodParse, badParse);
	  goodParse = badParse = 0;
	  printf ("Time: %02d:%02d:%02d.%03d ",
	   GPS.hour, GPS.minute, GPS.seconds, GPS.milliseconds);
	  printf ("Date: %02d/%02d/%d\n", GPS.day, GPS.month, GPS.year);
	  printf ("Fix: %d quality: %d\n", GPS.fix, GPS.fixquality);
	  if (GPS.fix)
	  {
	    printf ("Location: %f %c, ", GPS.latitude, GPS.lat);
	    printf ("%f, %c\n", GPS.longitude, GPS.lon);
	    printf ("Speed (knots): %f\n", GPS.speed);
	    printf ("Angle: %f\n", GPS.angle);
	    printf ("Altitude: %f\n", GPS.altitude);
	    printf ("Satellites: %d\n", GPS.satellites);
	  }
	}
  }
}

// -----------------------------------------------------------------
// 
//  main() is an Arduino "core" analog
//
int main (int argc, char **argv)
{
  int rc = 0;

  // set stdout stream to "line buffered" mode, to facilitate "useful" 
  //  redirect to to a pipe or a file .
  rc = setvbuf(stdout, NULL, _IOLBF, 0);
  if ( rc != 0 ) {
    perror("parsing.setvbuf");
	exit(1);
  }

  // debug: 1/enable, 0/disable debug output here 
  //         and in the Adafruit_GPS methods
  debug = 0;

  setup ();
  for (;;)
    {		
      loop ();
    }
}

#ident "$Name:  $ $Header: /projRCS/rpi/AdaGPS/parsing.c,v 1.5 2015/01/26 00:51:56 dmk%raspi Exp $"
