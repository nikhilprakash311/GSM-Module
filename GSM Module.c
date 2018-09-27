#include <xc.h>
#include <CONFIGBITS.h>
#define _XTAL_FREQ 16000000

void uart_init(unsigned long);
void uart_send(unsigned char);
void uart_string(unsigned char*);

void uart_init(unsigned long baud)
{
    unsigned int n;
    TXSTA = 0x00;
    RCSTA = 0x00;
    SYNC = 0;               // Asynchronous mode
    BRG16 = 1;              // Use SPBREGH and SPBREG
    SPEN = 1;           // Enable tx and rx pins
    CREN = 1;           // Enable continous receive mode
    BRGH = 1;           // High Speed transmission enable
    TXEN = 1;           // Enable transmission
    
    n = ((_XTAL_FREQ/4)/baud) - 1;
    SPBRGH = (n>>8);
    SPBRG = n & 0xFF;
       
}

void uart_send(unsigned char ch)
{
    //Wait for TXREG Buffer to become available
	while(!TXIF);

	//Write data
	TXREG=ch;
}

void uart_string(unsigned char *str)
{
	while((*str)!='\0')
	{
		//Wait for TXREG Buffer to become available
		while(!TXIF);

		//Write data
		TXREG=(*str);

		//Next goto char
		str++;
	}
}

void main(void) 
{
    uart_init(9600);
    
    uart_string("AT");
    uart_send(13);   // 13 ASCII FOR enter character
    uart_string("ATD9873647421;"); // calling to 9873647421
    uart_send(13);   
           
    return;
}
