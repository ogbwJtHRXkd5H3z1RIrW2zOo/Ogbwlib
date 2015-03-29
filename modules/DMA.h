#ifndef __DMA_H__
#define __DMA_H__

#define DMA_settings ((DMA_settings_ *) 0x0380)


typedef struct {
	union {
		U16 CON;
		struct {
			unsigned int MODE : 2;
			unsigned int  : 2;
			unsigned int AMODE : 2;
			unsigned int  : 5;
			unsigned int NULLW : 1;
			unsigned int HALF : 1;
			unsigned int DIR : 1;
			unsigned int SIZE : 1;
			unsigned int CHEN : 1;
		};
	};
	
	union {
		U16 REQ;
		struct {
			unsigned int IRQSEL : 7;
			unsigned int  : 8;
			unsigned int FORCE : 1;
		};
	};
	U16 STA;
	U16 STB;
	U16 PAD;
	union {
		U16 CNT_;
		struct {
			unsigned int CNT : 9;
			unsigned int  : 7;
		};
	};
} DMA_settings_;			
		

#endif


