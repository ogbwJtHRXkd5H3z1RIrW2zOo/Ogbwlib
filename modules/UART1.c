#include <p33Fxxxx.h>
#include <string.h>
#include "../ogbwlib.h"
#include "../algos/lists/ByteFIFO.h"
#include "./UART1.h"

U8 internal_intProtect;
ByteFIFO txBuffer;
ByteFIFO rxBuffer;

UART_Error UART1_init(U8 txPin, U16 txBufferSize, U8 txIntPriority, U8 rxPin, U16 rxBufferSize, U8 rxIntPriority, U32 baudrate, U8 intProtect) {
    // We are in a memory well-controlled environnement. If this fail, the programmer made a critical mistake. We don't even try to recover, let's just return an error code.
    txBuffer = ByteFIFO_new(txBufferSize);
    rxBuffer = ByteFIFO_new(rxBufferSize);

    if(txBuffer == null || rxBuffer == null) {
        return UART_OUT_OF_MEMORY;
    }
    
    // Port Mapping
    PPSInput(U1RX, rxPin);
    PPSOutput(U1TX, txPin);

    // Baudrate setting
    U1MODE = 0x0008; // fast mode (works for baurates from ~200bps (@Fcy=40MHz) to several Mbps)
    U1BRG = ((FCY / baudrate) / 4) - 1;
    U1STA = 0;

    // Interruption initialisation
    if(intProtect>txIntPriority && intProtect>rxIntPriority) {
        internal_intProtect = intProtect;
    } else {
        internal_intProtect =   txIntPriority>rxIntPriority ? txIntPriority : rxIntPriority;
    }

    _U1TXIF = 0;
    _U1TXIP = txIntPriority;
    _U1TXIE = 1;

    U1STAbits.URXISEL = 0;
    _U1RXIF = 0;
    _U1RXIP = rxIntPriority;
    _U1RXIE = rxIntPriority>0?1:0;

    // Start module
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;

    return UART_OK;
}

UART_Error UART1_sendByte(S8 b) {
    U8 ret;
    INTERRUPT_PROTECT(internal_intProtect, {
        ret = ByteFIFO_pushByte(txBuffer, b);
    });

    _U1TXIF = 1;
    return ret ? UART_OK : UART_BUFFER_OVERFLOW;
}

UART_Error UART1_sendTab(const void * tab, U16 size) {
    U8 ret;
    INTERRUPT_PROTECT(internal_intProtect, {
        ret = ByteFIFO_pushBlock(txBuffer, size, tab);
    });
    
    _U1TXIF = 1;
    return ret ? UART_OK : UART_BUFFER_OVERFLOW;
}

UART_Error UART1_sendStr(const char* str) {
    U8 ret;
    INTERRUPT_PROTECT(internal_intProtect, {
        ret = ByteFIFO_pushStr(txBuffer, str);
    });

    _U1TXIF = 1;
    return ret ? UART_OK : UART_BUFFER_OVERFLOW;
}

U16 UART1_getRxBufferDataSize(void) {
    U16 ret;
    INTERRUPT_PROTECT(internal_intProtect, {
        ret = ByteFIFO_getDataSize(rxBuffer);
    });
    return ret;
}

S8 UART1_readByte(void) {
    S8 ret=0;
    INTERRUPT_PROTECT(internal_intProtect, {
        if(ByteFIFO_getDataSize != 0) { // ByteFIFO_pop has no protection against pop on empty FIFO. We don't want UART to transmit this responsability to the user.
            ret = ByteFIFO_pop(rxBuffer);
        }
    });
    return ret;
}

S8 UART1_readTab(void* data, U16 size) {
    S8 ret;
    INTERRUPT_PROTECT(internal_intProtect, {
        ret = ByteFIFO_popBlock(rxBuffer, size, data);
    });
    return ret;
}

void UART1_onU1TXInterrupt(void) {
    if (_U1TXIF) {
        INTERRUPT_PROTECT(internal_intProtect, {
            while (!U1STAbits.UTXBF && ByteFIFO_isNotEmpty(txBuffer)) {
                U1TXREG = ByteFIFO_pop(txBuffer);
            }
        });
        _U1TXIF = 0;
    }
}

UART_Error UART1_onU1RXInterrupt() {
    if(_U1RXIF) {
        _U1RXIF=0;
        while(U1STAbits.URXDA) {
            U8 value = U1RXREG;

            INTERRUPT_PROTECT(internal_intProtect, {
                if(ByteFIFO_pushByte(rxBuffer, value) == ByteFIFO_FULL){
                    INTERRUPT_PROTECT_return(UART_BUFFER_OVERFLOW);
                }
            });
        }
        return UART_OK;
    }
}

