#include <msp430.h>

unsigned int i;
const unsigned int max_length = 100;
const char hello_string[100] = {"Hello!\n"};

void main() {
	WDTCTL = WDTPW + WDTHOLD;

	P1SEL = BIT1 | BIT2;
	P1SEL2 = BIT1 | BIT2;

	DCOCTL = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;

	UCA0CTL1 = UCSWRST;

	UCA0CTL1 |= UCSSEL_2;
	UCA0BR0 = 104;
	UCA0BR1 = 0;
	UCA0MCTL = UCBRS0;

	UCA0CTL1 &= ~UCSWRST;

	IE2 = UCA0RXIE;

	__bis_SR_register(LPM0_bits + GIE);
}


#pragma vector=USCIAB0RX_VECTOR
__interrupt void UART_Recieve_ISR(void) {
	if(UCA0RXBUF == 's') {
		i = 0;
		IE2 |= UCA0TXIE;
	}
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void UART_Transmit_ISR(void) {
	char next_char;

	while(i < max_length) {
		next_char = hello_string[i++];
		
		while(!(IFG2 & UCA0TXIFG)); // loop until ready to transmit again

		UCA0TXBUF = next_char;
	}

	while(!(IFG2 & UCA0TXIFG));
	UCA0TXBUF = 'h';

	IE2 = UCA0RXIE;
}