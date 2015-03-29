
struct ObjectFIFO_Elem_struct {
	U16 next;
	U8 __attribute__((aligned(2))) data[];
};
typedef struct ObjectFIFO_Elem_struct ObjectFIFO_Elem;

struct ObjectFIFO_struct{
	U16 size;                               /// taille de la file
	U16 write;                              /// lieu ou on écrira le prochain bloc
	ObjectFIFO_Elem* lastWritten;           /// lieu du dernier bloc écrit
	U16 read;                               /// lieu du prochain block à lire
	U16 objNb;                              /// nombre de blocs stockés
	U8 __attribute__((aligned(2))) data[];  /// tableau servant à stocker les données
};
typedef struct ObjectFIFO_struct* ObjectFIFO;



inline ObjectFIFO ObjectFIFO_new(const U16 size);
inline U8 ObjectFIFO_isEmpty(const ObjectFIFO fifo);
inline U8 ObjectFIFO_isFull(const ObjectFIFO fifo);
inline U16 ObjectFIFO_getAvailableSize(const ObjectFIFO fifo);
inline U16 ObjectFIFO_getAllocatedSize(const ObjectFIFO fifo);
inline U16 ObjectFIFO_getObjectNb(const ObjectFIFO fifo);
inline void ObjectFIFO_clear(ObjectFIFO fifo);
inline void ObjectFIFO_free(ObjectFIFO fifo);
inline void* ObjectFIFO_get(const ObjectFIFO fifo);
inline void* ObjectFIFO_pop(ObjectFIFO fifo);
inline void* ObjectFIFO_push(ObjectFIFO fifo, const U16 size, const void* data);
void* ObjectFIFO_allocate(ObjectFIFO fifo, const U16 size);



























