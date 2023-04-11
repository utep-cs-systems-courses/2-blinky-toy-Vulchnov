	.arch msp430g2553
	.p2align 1,0
	.text


	.global greenOn
	.extern P1OUT

greenOn:
	bis #64, &P1OUT
	pop r0
