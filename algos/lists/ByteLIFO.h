typedef struct {
	U16 size;   /// Taille de la pile
	U8* next;   /// Pointeur vers le premier emplacement libre
	U8 data[];  /// Tableau servant à stocker les données
}* ByteLIFO;

typedef enum { 
	ByteLIFO_ok,
	ByteLIFO_full,
	ByteLIFO_notEnoughtData
} ByteLIFO_Error;

inline ByteLIFO ByteLIFO_new(const U16 size);

inline U8 ByteLIFO_isEmpty(const ByteLIFO lifo);
inline U8 ByteLIFO_isFull(const ByteLIFO lifo);
inline U16 ByteLIFO_getDataSize(const ByteLIFO lifo);
inline U16 ByteLIFO_getAvailableSize(const ByteLIFO lifo);

inline void ByteLIFO_clear(ByteLIFO lifo);
inline void ByteLIFO_free(ByteLIFO lifo);

inline U8 ByteLIFO_get(const ByteLIFO lifo);
inline U8 ByteLIFO_pop(ByteLIFO lifo);
inline ByteLIFO_Error ByteLIFO_push(ByteLIFO lifo, const U8 data);

inline ByteLIFO_Error ByteLIFO_pushBlock(ByteLIFO lifo, const U16 size, const void* data);
inline ByteLIFO_Error ByteLIFO_rpushBlock(ByteLIFO lifo, const U16 size, const void* data);
inline ByteLIFO_Error ByteLIFO_popBlock(ByteLIFO lifo, const U16 size, void* data);
inline ByteLIFO_Error ByteLIFO_rpopBlock(ByteLIFO lifo, const U16 size, void* data);

