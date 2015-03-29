struct ObjectLIFO_Elem_struct {
	struct ObjectLIFO_Elem_struct* prec;
	U8 __attribute__((aligned(2))) data[];
};
typedef struct ObjectLIFO_Elem_struct ObjectLIFO_Elem;

struct ObjectLIFO_struct {
	U16 size;
	U16 allocatedSize;
	U16 objNb;
	ObjectLIFO_Elem* current;
	U8 __attribute__((aligned(2))) data[];
};
typedef struct ObjectLIFO_struct* ObjectLIFO;

inline ObjectLIFO ObjectLIFO_new(const U16 size);

inline U8 ObjectLIFO_isEmpty(const ObjectLIFO lifo);
inline U8 ObjectLIFO_isFull(const ObjectLIFO lifo);
inline U16 ObjectLIFO_getAvailableSize(const ObjectLIFO lifo);
inline U16 ObjectLIFO_getObjectNb(const ObjectLIFO lifo);

inline void ObjectLIFO_clear(ObjectLIFO lifo);
inline void ObjectLIFO_free(ObjectLIFO lifo);

inline void* ObjectLIFO_get(const ObjectLIFO lifo);
inline void* ObjectLIFO_pop(ObjectLIFO lifo);
inline void* ObjectLIFO_push(ObjectLIFO lifo, const U16 size, const void* data);
