

//#include "ver_led.h"

#if !defined(TRUE) 
#define TRUE 1
#endif

#if !defined(FALSE)
#define FALSE 0
#endif

// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

//For Atmega328P's
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX


void setup()
{
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(9600);
  Serial.begin(9600);
//  ver_led_setup(3);
}

void check_and_print_debug( void )
{
  // current implementation uses only strings, and uses newlines to demarcate packets.  
  // We'll print out "JEEP: <string>" to show that this is coming from the Jeep.
  
  static bool start_of_string=TRUE;
  char c;
  
  while (XBee.available())
  { 
    // if this is the first character after a newline (or the very first) we've gotten in the serial link,
    // print out the "JEEP:" header.
    if (start_of_string)
    {
      Serial.print("JEEP: ");
      start_of_string = FALSE;
    }

    // print out any subsequent characters, including newlines.
    // Note that if we get a newline, the next string is going to be a new message, so we
    // Want to again print "JEEP:"
    c = XBee.read();  
    Serial.write(c);
    if (c == '\n') 
    {
      start_of_string = TRUE;
    }
    
  }  // end of processing characters.
}


void loop()
{
 // ver_led_run();
  check_and_print_debug();
}
