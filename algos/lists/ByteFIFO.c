/** @file       ByteFIFO.c
 *  @author     ogbwJtHRXkd5H3z1RIrW2zOo
 *  @version    1.1
 *  @date       07/03/2015
 *
 *  ByteFIFO est a data container with a fixed data size (it's internally implemented by an array).
 *  As its name may suggest, it works in a FIFO (fisrt in first out), meaning the data are read in the same order they were written.
 *  This is the natural behaviour for a buffer, feel free to use it than way.
 *  The implementation offers no garanties against interrupt. If you need to use it on different IPL, I strongly suggest you protect every call to this library.
 *
 *  The ByteFIFO type is a pointer to a struct, but you should never need to use it directly (if done incorrectly, it may lead to corruption).
*/

#include <stdlib.h>
#include <string.h>
#include "typedef.h"
#include "ByteFIFO.h"

/**
 * Creates a new container.
 * @param size  size allocated for data (in bytes)
 * @return      the container created
 * @warning     Memory is allocated with a malloc. You have to set the linker so it allocates at least size + 8 bytes on the heap. You can free the memory with the ByteFIFO_free function.
 */
inline ByteFIFO ByteFIFO_new(const U16 size) {
    ByteFIFO ret = malloc(sizeof(struct ByteFIFO_struct) + size * sizeof(U8));
    if (ret != null) {
        ret->size = size;
        ret->readPtr = 0;
        ret->writePtr = 0;
        ret->dataSize = 0;
    }
    return ret;
}

/**
 * Checks if the container is empty
 * @return      true if and only if the container is empty
 */
inline bool ByteFIFO_isEmpty(const ByteFIFO fifo) {
    return fifo->dataSize == 0;
}

/**
 * Checks if the container contains anything
 * @return      true if and only if the container is not empty
 */
inline bool ByteFIFO_isNotEmpty(const ByteFIFO fifo) {
    return fifo->dataSize != 0;
}

/**
 * Checks if the container is full
 * @return      true if and only if the container is full
 */
inline bool ByteFIFO_isFull(const ByteFIFO fifo) {
    return fifo->dataSize == fifo->size;
}

/**
 * Get the size of the data actually contained
 * @return      size of contained data (in bytes)
 */
inline U16 ByteFIFO_getDataSize(const ByteFIFO fifo) {
    return fifo->dataSize;
}

/**
 * Get the free space remaining
 * @return      size of the free space (in bytes)
 */
inline U16 ByteFIFO_getAvailableSize(const ByteFIFO fifo) {
    return fifo->size - fifo->dataSize;
}

/**
 * Clear the container.
 * @warning     This function clear the container, but does not free the associated memory. For this, you have to use the ByteFIFO_free function.
 */
inline void ByteFIFO_clear(ByteFIFO fifo) {
    fifo->readPtr = fifo->writePtr = 0;
    fifo->dataSize = 0;
}

/**
 * Unallocate the memory used by this container. It can be called regardless of the state of the container (empty, full, clean, corrupted...).
 * @warning     Don't call this function on a non-initialized container (it's just like calling free on a random ptr). Of course, don't use the container after you unallocated it's memory.
 */
inline void ByteFIFO_free(ByteFIFO fifo) {
    free(fifo);
}

/**
 * Read the first byte contained. Unlike ByteFIFO_pop, the byte is not removed from the container.
 * @return      Read byte. If the container was empty, it can be anything.
 * @warning	As it is impossible to know from the value returned if the container was empty or not, it is highly recommended to check wether the containre is empty or not before you use this function. However, if you don't, there is no risk to corrupt the container, you just get carppy data.
 */
inline S8 ByteFIFO_get(const ByteFIFO fifo) {
    return fifo->data[fifo->readPtr];
}

/**
 * Read and remove the first byte contained. Unlike ByteFIFO_get, the byte is removed from the container, so you have to use the value returned if you don't want to lose it.
 * @return      Read byte.
 * @warning	Using this function on an empty container WILL corrupt it. Always check its state before with the BYTEFIFO_isEmpty function before (be extra-carefull if you use it with interrupt, it may be emptied between the time you check and the time you pop if not interrupt-protected).
 */
inline S8 ByteFIFO_pop(ByteFIFO fifo) {
    S8 ret = fifo->data[fifo->readPtr++];
    if(fifo->readPtr == fifo->size) {
        fifo->readPtr=0;
    }
    fifo->dataSize--;
    return ret;
}

/**
 * Write a byte in the container.
 * @param data	Byte to write
 * @return      ByteFIFO_full if the container was full. In this case, nothing is written. ByteFIFO_ok otherwise.
 */
inline ByteFIFO_Error ByteFIFO_pushByte(ByteFIFO fifo, const S8 data) {
    if(!ByteFIFO_isFull(fifo)) {
        fifo->data[fifo->writePtr++] = data;
        if(fifo->writePtr == fifo->size) {
            fifo->writePtr=0;
        }
        fifo->dataSize ++;
        return ByteFIFO_OK;
    } else {
        return ByteFIFO_FULL;
    }
}

/**
 * Write several bytes in the container.
 * @param size	size of the data
 * @param data	ptr to the data to write
 * @return      ByteFIFO_full if the container was full, or did not has enought free space to write everything. In this case, nothing is written. ByteFIFO_ok otherwise.
 */
inline ByteFIFO_Error ByteFIFO_pushBlock(ByteFIFO fifo, const U16 size, const void* data) {
    if (ByteFIFO_getAvailableSize(fifo) >= size) {
        U8* data_ = (U8*) data;
        if (fifo->writePtr + size >= fifo->size) { // writeptr se doit faire un modulo (qu'on doive ou non écrire au début du tableau)
            memcpy(fifo->data + fifo->writePtr, data_, fifo->size - fifo->writePtr);
            memcpy(fifo->data, data_ + fifo->size - fifo->writePtr, size + fifo->writePtr - fifo->size);
            fifo->writePtr = size + fifo->writePtr - fifo->size;
        } else {
            memcpy(fifo->data + fifo->writePtr, data_, size);
            fifo->writePtr += size;
        }
	fifo->dataSize += size;
        return ByteFIFO_OK;
    } else {
        return ByteFIFO_FULL;
    }
}

/**
 * Write a string in the container.
 * @param str	string to write
 * @return      ByteFIFO_full if the container was full, or did not has enought free space to write everything. In this case, nothing is written. ByteFIFO_ok otherwise.
 */
inline ByteFIFO_Error ByteFIFO_pushStr(ByteFIFO fifo, const void* data) {
    return ByteFIFO_pushBlock(fifo, strlen(data), data);
}

/**
 * Read and remove several bytes from the container.
 * You can use it two ways : either you use i
 * @param size  number of bytes to read
 * @param data  buffer you want the data to be copied in
 * @return      ByteFIFO_notEnoughtData if the container did not contained as much data as you requested. In this case nothing is read nor removed from the container. ByteFIFO_ok otherwise.
 * @remark      The internal implementation of this function makes it prefectly fine to use it as a 'check if there is at least n bytes and read them if yes'. It is just as efficient as doing it explicitly with ByteFIFO_getDataSize.
 */
inline ByteFIFO_Error ByteFIFO_popBlock(ByteFIFO fifo, const U16 size, void* data) {
    if (ByteFIFO_getDataSize(fifo) >= size) {
        U8* data_ = (U8*) data;
        if (fifo->readPtr + size >= fifo->size) {
            memcpy(data_, fifo->data + fifo->readPtr, fifo->size - fifo->readPtr);
            memcpy(data_ + fifo->size - fifo->readPtr, fifo->data, size + fifo->readPtr - fifo->size);
            fifo->readPtr = size + fifo->readPtr - fifo->size;
        } else {
            memcpy(data_, fifo->data + fifo->readPtr, size);
            fifo->readPtr += size;
        }
	fifo->dataSize -= size;
        return ByteFIFO_OK;
    } else {
        return ByteFIFO_NOT_ENOUGHT_DATA;
    }
}
