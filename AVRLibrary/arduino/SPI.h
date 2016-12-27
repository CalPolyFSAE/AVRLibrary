/** SPI Library
 * Nick Mah
 * Library contains various SPI functions to be used
 */
#include <stdio.h>
#include <avr/io.h>

uint16_t Transmit_SPI_Master_16(uint8_t Data1, uint8_t Data2, uint8_t CS) //Function for ATMega to write data to. Must be rewritten to read data from ADC
{
	char receive;
	PORTB &= ~(1 << CS);			// assert the slave select
	SPDR = Data1;     			// Start transmission, send high byte first
	while (!(SPSR & (1<<SPIF)));// Wait (poll) for transmission complete
	receive = SPDR;	//save first return
	SPDR = Data2;		//start second transmission
	while(!(SPSR & (1 <<SPIF)));	//wait for transmission complete
	PORTB |= 1 << CS;			// deassert the slave select
	return (receive << 8) | SPDR; //return first return concatenated with second return
}

uint16_t Transmit_SPI_Master(uint8_t Data, uint8_t CS) //Function for ATMega to write data to. Must be rewritten to read data from ADC
{
	char receive;
	PORTB &= ~(1 << CS);			// assert the slave select
	SPDR = Data;     			// Start transmission, send high byte first
	while (!(SPSR & (1<<SPIF)));// Wait (poll) for transmission complete
	receive = SPDR;	//save first return
	PORTB |= 1 << CS;			// deassert the slave select
	return (receive << 8) | SPDR; //return first return concatenated with second return
}

void Initialize_SPI_Master(uint8_t CS) //correct values for each register still need to be determined
		{
	SPCR = (0 << SPIE) | 		//No interrupts
			(1 << SPE) | 				//SPI enabled
			(0 << DORD) | 			//send MSB first
			(1 << MSTR) | 			//master
			(0 << CPOL) | 			//clock idles low
			(0 << CPHA) | 			//sample leading edge
			(0 << SPR1) | (0 << SPR0); //clock speed
	SPSR = (0 << SPIF) | 		//SPI interrupt flag
			(0 << WCOL) | 			//Write collision flag
			(0 << SPI2X); 			//Doubles SPI clock
	PORTB = 1 << CS;  		// make sure SS is high

}
