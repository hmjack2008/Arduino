/*
Arduino Serial Interrupts
http://stackoverflow.com/questions/10201590/arduino-serial-interrupts


*/

#include <avr/interrupt.h>
#include <avr/io.h>

void setup()
{
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
  /*
  Serial.begin(115200);
  Serial.println("ready");
  */
	UBRR0H = 0; // Load upper 8-bits of the baud rate value into the high byte of the UBRR register 
	UBRR0L = 8; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register 
	UCSR0C |= (1 << UCSZ00) ; // | (1 << UCSZ10); // Use 8-bit character sizes 
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);   // Turn on the transmission, reception, and Receive interrupt      

	interrupts(); // to enable the global interrupt
}


void loop()
{
  // Serial.println("send");
  digitalWrite(13, HIGH);
  delay(5000); //Do nothing
  digitalWrite(13, LOW);
  delay(5000);
}

ISR(USART_RX_vect)
{
  noInterrupts();
  digitalWrite(13, HIGH);  // set the LED on
  digitalWrite(13, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(13, HIGH);
	// delay(500);              // wait for a second
	// digitalWrite(13, LOW);
  return;
}

