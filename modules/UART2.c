#include <p33Fxxxx.h>
#include <string.h>
#include "../Ogbwlib.h"
#include "../algos/lists/ByteFIFO.h"
#include "./UART2.h"

U8 internal_intProtect;
ByteFIFO txBuffer;
ByteFIFO rxBuffer;

UART_Error UART2_init(U8 txPin, U16 txBufferSize, U8 txIntPriority, U8 rxPin, U16 rxBufferSize, U8 rxIntPriority, U32 baudrate, U8 intProtect) {
    // We are in a memory well-controlled environnement. If this fail, the programmer made a critical mistake. We don't even try to recover, let's just return an error code.
    txBuffer = ByteFIFO_new(txBufferSize);
    rxBuffer = ByteFIFO_new(rxBufferSize);

    if(txBuffer == null || rxBuffer == null) {
        return UART_OUT_OF_MEMORY;
    }

    // Port Mapping
    PPSInput(U2RX, rxPin);
    PPSOutput(U2TX, txPin);

    // Baudrate setting
    U2MODE = 0x0008; // fast mode (works for baurates from ~200bps (@Fcy=40MHz) to several Mbps)
    U2BRG = ((FCY / baudrate) / 4) - 1;
    U2STA = 0;

    // Interruption initialisation
    if(intProtect>txIntPriority && intProtect>rxIntPriority) {
        internal_intProtect = intProtect;
    } else {
        internal_intProtect =   txIntPriority>rxIntPriority ? txIntPriority : rxIntPriority;
    }

    _U2TXIF = 0;
    _U2TXIP = txIntPriority;
    _U2TXIE = 1;

    U2STAbits.URXISEL = 0;
    _U2RXIF = 0;
    _U2RXIP = rxIntPriority;
    _U2RXIE = rxIntPriority>0?1:0;

    // Start module
    U2MODEbits.UARTEN = 1;
    U2STAbits.UTXEN = 1;

    return UART_OK;
}

UART_Error UART2_sendByte(S8 b) {
    U8 ret;
    INTERRUPT_PROTECT(internal_intProtect, {
        ret = ByteFIFO_pushByte(txBuffer, b);
    });

    _U2TXIF = 1;
    return ret ? UART_OK : UART_BUFFER_OVERFLOW;
}

UART_Error UART2_sendTab(const void * tab, U16 size) {
    U8 ret;
    INTERRUPT_PROTECT(internal_intProtect, {
        ret = ByteFIFO_pushBlock(txBuffer, size, tab);
    });

    _U2TXIF = 1;
    return ret ? UART_OK : UART_BUFFER_OVERFLOW;
}

UART_Error UART2_sendStr(const char* str) {
    U8 ret;
    INTERRUPT_PROTECT(internal_intProtect, {
        ret = ByteFIFO_pushStr(txBuffer, str);
    });

    _U2TXIF = 1;
    return ret ? UART_OK : UART_BUFFER_OVERFLOW;
}

U16 UART2_getRxBufferDataSize(void) {
    U16 ret;
    INTERRUPT_PROTECT(internal_intProtect, {
        ret = ByteFIFO_getDataSize(rxBuffer);
    });
    return ret;
}

S8 UART2_readByte(void) {
    S8 ret=0;
    INTERRUPT_PROTECT(internal_intProtect, {
        if(ByteFIFO_getDataSize != 0) { // ByteFIFO_pop has no protection against pop on empty FIFO. We don't want UART to transmit this responsability to the user.
            ret = ByteFIFO_pop(rxBuffer);
        }
    });
    return ret;
}

S8 UART2_readTab(void* data, U16 size) {
    S8 ret;
    INTERRUPT_PROTECT(internal_intProtect, {
        ret = ByteFIFO_popBlock(rxBuffer, size, data);
    });
    return ret;
}

void UART2_onU2TXInterrupt(void) {
    if (_U2TXIF) {
        INTERRUPT_PROTECT(internal_intProtect, {
            while (!U2STAbits.UTXBF && ByteFIFO_isNotEmpty(txBuffer)) {
                U2TXREG = ByteFIFO_pop(txBuffer);
            }
        });
        _U2TXIF = 0;
    }
}

UART_Error UART1_onU1RXInterrupt() {
    if(_U2RXIF) {
        _U2RXIF=0;
        while(U2STAbits.URXDA) {
            U8 value = U2RXREG;

            INTERRUPT_PROTECT(internal_intProtect, {
                if(ByteFIFO_pushByte(rxBuffer, value) == ByteFIFO_FULL){
                    INTERRUPT_PROTECT_return(UART_BUFFER_OVERFLOW);
                }
            });
        }
        return UART_OK;
    }
}

