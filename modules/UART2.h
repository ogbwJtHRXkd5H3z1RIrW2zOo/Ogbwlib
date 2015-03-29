/**
 * @file    UART2.h
 *
 * Library providing UART2 management, with buffering.
 * It needs ISR for both RX and TX correctly set to work properly. You can either use the macros UART2_setU2RXInterruptForMe and UART2_setU2TXInterruptForMe for basic use (no overflow management, no read in interrupt body...), or you can define your own ISR based on the ones set by the macros.
 * Internally uses ByteFIFO for buffering, which means space is allocated with malloc, and therefore linker set to allocate some space on the heap.
 *
 * @author  ogbwJtHRXkd5H3z1RIrW2zOo
 * @sa      ByteFIFO.h UART2.h
 * @version 1.1
*/

#ifndef UART2_H
#define UART2_H

#include "../typedef.h"
#include "../algos/lists/ByteFIFO.h"

#ifndef UART_Error_declaration
#define UART_Error_declaration
typedef enum {
    UART_OK,
    UART_OUT_OF_MEMORY,
    UART_NOT_ENOUGHT_DATA,
    UART_BUFFER_OVERFLOW
} UART_Error;
#endif


/**
 * UART2 initialization.    This function sets pins, initialize buffer, interrputs, and hardware module. UART2 in usable imediatly after a call to this function.
 * @param txPin             N° of the pin used for U2TX output (5 means RP5, not the n°5 pin of the dsPIC)
 * @param txBufferSize      transmission buffer size.
 * @param txIntPriority     transmission interrupt priority. This interrput reads data from the buffer and manages the hardware module. High priority is strongly advised.
 * @param rxPin             N° of the pin used for U2RX input (4 means RP5, not the n°5 pin of the dsPIC)
 * @param rxBufferSize      receive buffer size
 * @param rxIntPriority     receive interrupt priority. As you may want to manage received data in this interrupt, mabye you don't want to have this set too high. Keep in mind however, that if can't be executed while more than 4 bytes are recieved, you may lose some data.
 * @param baudrate          Transmission speed, in bps
 * @param intProtect        Highest IPL at which the user code is susceptible too use UART2. This is important to protect the buffer reads and write. If you don't know, and no time-sensitive interrupt exists, 7 is a good choice.
 * @return                  UART_ERROR_OUTOFMEMORY if heap size was not enought to start, .
 * @return                  UART_OK if the initiallization was successfull.
 * @warning                 _U2TXInterrupt and _U2RXInterrupt must be correctly set. You can use UART2_setU2RXInterruptForMe and UART2_setU2TXInterruptForMe, or derive their code for your personnal use.
 * @warning                 Internally uses ByteFIFO. You must set the linker to allocate a heap sapce allowing two ByteFIFO with a txBufferSize and rxBufferSize size. With the current implementation of ByteFIFO, it means txBufferSize + rxBufferSize + 16 byte in the heap, but you should keep a margin to take into account future evolutions, or allignement constraints.
 */
UART_Error UART2_init(U8 txPin, U16 txBufferSize, U8 txIntPriority, U8 rxPin, U16 rxBufferSize, U8 rxIntPriority, U32 baudrate, U8 intProtect);

/**
 * Adds a byte to the transmit buffer. It will be sent as soon as possible, but after the bytes already present in the buffer.
 * @param b     byte to send
 * @return      UART_BUFFER_OVERFLOW if the transmit buffer was already full, in this case, the byte is ignored.
 * @return      UART_OK if the operation was successfull.
 * @warning     Due to buffering, real transmission may be delayed.
 */
UART_Error UART2_sendByte(S8 b);


/**
 * Adds an array to the transmit buffer. Data will be sent as soon as possible, but after the bytes already present in the buffer. Order is preserved.
 * @param tab   array to send
 * @param size  size of the array (in bytes)
 * @return      UART_BUFFER_OVERFLOW if the transmit buffer didn't have enought space for the array. In this case, nothing is written in the buffer (you can try again later, without having to manage a partial transmit).
 * @return      UART_OK if the operation was successfull.
 */
UART_Error UART2_sendTab(const void * tab, U16 size);

/**
 * Adds an character string to the transmit buffer. Data will be sent as soon as possible, but after the bytes already present in the buffer. Order is preserved.
 * @param str   string to send
 * @return      UART_BUFFER_OVERFLOW if the transmit buffer didn't have enought space for the string.  In this case, nothing is written in the buffer (you can try again later, without having to manage a partial transmit).
 * @return      UART_OK if the operation was successfull.
 * @warning     The final 0 of the string is not transmitted.
 * @warning     no security is provided against infinite string. You have to make sure it never happends.
 */
UART_Error UART2_sendStr(const char * str);


/**
 * Get the number of bytes available in the receive buffer.
 * @return      Number of bytes available
 */
U16 UART2_getRxBufferDataSize(void);

/**
 * Read a single byte from the receive buffer
 * @return      byte read. Undefeined if the buffer was empty.
 * @warning     The only way to make sure the value returned is valid is to check beforhand if there was some data to read. Use UART2_getRxBufferDataSize before you use UART2_readByte
 */
S8 UART2_readByte(void);

/**
 * Read a serie of bytes from the receive buffer
 * @param tab   place you want the read data to be written.
 * @param size  number of bytes to read
 * @return      UART_ERROR_NOTENOUGHTDATA if the buffer did not contain at least as much data as you asked for. In this case no data is read.
 * @return      UART_OK if the operation was successfull.
 *
 */
S8 UART2_readTab(void*, U16);

/**
 * Function in charge of the transmit buffer managment. It must be called in the _U2TXInterrupt ISR. You can either do this using the macro UART2_setU2TXInterruptForMe, or by customizing the ISR.
 * Cutomizing is not advised as this ISR probably has a quite high priority, and should be kept as simple as possible. Do it carfully.
 * For maximum efficiency, make sure this ISR can be executed often enought to avoid pauses in data transmission (hardware module has a 4 bytes buffer)
 */
void UART2_onU2TXInterrupt(void);

/**
 * Fonction qui gère la partie buffering du module s'il est activé. Il faut l'executer depuis l'interrption _U2RXInterrupt, mais seulement si le buffering est activé (sinon on est à peu près certain de cracher le dsPIC).
 * Si on n'utilise pas le buffering, il n'est pas obligatoire d'activer l'interrption (cf UART2_init)
 * Que l'on utilise ou non le buffer, il est possible de traiter les données reçues dans la suite de l'interruption, ou tout simplement de gérer le retour de la fonction.
 * @return UART_ERROR_OK ou UART_ERROR_BUFFERALMOSTFULL si le buffering s'est bien fait (UART_ERROR_BUFFERALMOSTFULL est seulement un avertissement qui indique que 90% du buffer est plein). UART_ERROR_BUFFEROVERFLOW si le buffer est plein et qu'il a été impossible de recopier les données; il y a dans ce cas eu perte de données
 */
/**
 * Function in charge of the receive buffer managment. It must be called in the _U2RXInterrupt ISR. You can either do this using the macro UART2_setU2RXInterruptForMe, or by customizing the ISR.
 * Typical customization will be buffer overflow managment, or direct management or received data.
 * Make sure the ISR can de executed often enought to avoid a buffer overflow in the hardware module (4 bytes buffer).
 * @return UART_ERROR_BUFFERALMOSTFULL if the received buffer was full. This means one byte of data has been lost. Quickly make some space to avoid losing every incoming bytes.
 * @return UART_OK if the received byte has been written in the buffer without any problem.
 */
UART_Error UART2_onU2RXInterrupt(void);

/**
 * This macro sets an basic _U2TXInterrupt ISR managing transmit buffer
 * @warning Do not use several times in the same project, nor together with a custom ISR (you wont get very far, it will not compile)
 * @warning Use outside of any function.
 */
#define UART2_setU2TXInterruptForMe(); void __attribute__((interrupt,no_auto_psv))_U2TXInterrupt(void)     {        UART2_onU2TXInterrupt();    }

/**
 * This macro sets an basic _U2RXInterrupt ISR managing receive buffer
 * @warning Do not use several times in the same project, nor together with a custom ISR (you wont get very far, it will not compile)
 * @warning Use outside of any function.
 */
#define UART2_setU2RXInterruptForMe(); void __attribute__((interrupt,no_auto_psv))_U2RXInterrupt(void)     {        UART2_onU2RXInterrupt();    }

/**
 * Send data to UART2 just as if UART2 was your screen and you use printf. Usefull for debugging.
 * @param   same as good old printf
 * @warning if the transmit buffer can't contain the produced string, no data is sent.
 */
#define UART2_printf(...); {char __msg__[255]; sprintf(__msg__,__VA_ARGS__); UART2_sendStr(__msg__);}

/**
 * Send data to UART2 just as if UART2 was your screen and you use printf. Usefull for debugging.
 * If the transmit buffer has not enought space to contain the produced string, this macro waits until it emptied itself.
 * @param   same as good old printf
 * @warning the waiting time can be quite long, compared to basic function.
 * @warning if the produced string is bigger than the transmit buffer, this is an infinite loop. Use carefully.
 */
#define UART2_printfBlock(...) {char __msg__[255]; sprintf(__msg__,__VA_ARGS__); while(UART2_sendStr(__msg__)==UART_ERROR_BUFFEROVERFLOW); }

#endif //UART2_H
