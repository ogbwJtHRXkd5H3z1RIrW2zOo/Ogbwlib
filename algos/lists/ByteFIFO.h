#ifndef BYTEFIFO_H
#define BYTEFIFO_H

#include "../../typedef.h"

struct ByteFIFO_struct {
    U16 size;       /// FIFO size (= max size of the data it can contain
    U16 readPtr;    /// n° of next byte to read
    U16 writePtr;   /// n° of next byte to write
    U16 dataSize;   /// size of actually stored data
    S8 data[];      /// data container
};
typedef struct ByteFIFO_struct* ByteFIFO;

typedef enum { 
    ByteFIFO_OK = 0,
    ByteFIFO_FULL = 1,
    ByteFIFO_NOT_ENOUGHT_DATA = 2
} ByteFIFO_Error;

inline ByteFIFO ByteFIFO_new(const U16 size);

inline bool ByteFIFO_isEmpty(const ByteFIFO fifo);
inline bool ByteFIFO_isNotEmpty(const ByteFIFO fifo);
inline bool ByteFIFO_isFull(const ByteFIFO fifo);
inline U16 ByteFIFO_getDataSize(const ByteFIFO fifo);
inline U16 ByteFIFO_getAvailableSize(const ByteFIFO fifo);

inline void ByteFIFO_clear(ByteFIFO fifo);
inline void ByteFIFO_free(ByteFIFO fifo);

inline S8 ByteFIFO_get(const ByteFIFO fifo);
inline S8 ByteFIFO_pop(ByteFIFO fifo);
inline ByteFIFO_Error ByteFIFO_pushByte(ByteFIFO fifo, const S8 data);
inline ByteFIFO_Error ByteFIFO_pushBlock(ByteFIFO fifo, const U16 size, const void* data);
inline ByteFIFO_Error ByteFIFO_pushStr(ByteFIFO fifo, const void* data);
inline ByteFIFO_Error ByteFIFO_popBlock(ByteFIFO fifo, const U16 size, void* data);

#endif // BYTEFIFO_H
