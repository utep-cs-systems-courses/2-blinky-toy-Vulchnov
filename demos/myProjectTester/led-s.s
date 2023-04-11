	.arch msp430g2553
	.p2align 1,0
	.text


	.global greenOn
	.global greenOff
	.global redOn
	.global redOff
	.global led_init
	.extern P1OUT

greenOn:
	bis #64, &P1OUT
	pop r0
	
greenOff:
	bic #64, &P1OUT
	pop r0

redOn:
	bis #1, &P1OUT
	pop r0

redOff:
	bic #1, &P1OUT
	pop r0

led_init:
	bis #65, &P1DIR
	bic #65, &P1OUT
	pop r0
