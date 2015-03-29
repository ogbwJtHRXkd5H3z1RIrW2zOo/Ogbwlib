#include <p33Fxxxx.h>

inline void oscConfig(void) {
	_TUN = 0x3C;		// Il vaut mieux le mettre en binaire, car les nombre négatifs ne sont pas gérés sur un nombre de bit atypique
	_FRCDIV = 0;		// la valeur du postscaler est 2^_FRCDIV
	_PLLPRE = 5-2;		// pour la méme raison que ci-dessous, _PLLPRE = 0 correspond Ã  un /2, _PLLPRE = 1 correspond à  un /3, etc...
	_PLLDIV = 111-2;	// attention!! pour coder la plus grande gamme de fréquence possible en 9 bits, _PLLDIV=0 correspond à  un x2, _PLLDIV=1 correspond à  un x3, etc...
	_PLLPOST = 0x0;		// ici, il n'y a pas de relation mathématique entre le nombre donné et le postscaler : 0b00 correspond à  2, 0b01 à  4, et 0b11 à  8. 0b10 est interdit

	while(OSCCONbits.LOCK!=1); // Wait for PLL to lock
}
