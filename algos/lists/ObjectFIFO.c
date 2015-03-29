/**@file       ObjectFIFO.c
 * @author     ogbwJtHRXkd5H3z1RIrW2zOo
 * @version    1.0
 * @date       21/10/2012
 *
 * Ce fichier fourni les fonctions de base pour maintenir une file "d'objets" dont la taille maximale est fixée (l'implémentation repose sur un tableau).
 * Un objet est une suite d'octets quelconque. Le plus souvent, il s'agira d'une structure. La mémoire est organisée de façon à ce qu'on puisse lire l'objet à partir d'un pointeur. L'ordre les octets représentant les object n'est pas affecté.
 * Par file, on entend une liste FIFO (first in first out). Les objets sont lus dans le même ordre qu'ils sont ajoutés.
 * Le système ne prévois pas en lui-même une protection contre les interruptions. La meilleure méthode est a priori de protéger toutes les fonctions d'ajout ou de lecture de données.
*/

#include <stdlib.h>
#include <string.h>
#include "typedef.h"
#include "ObjectFIFO.h"

#define ALIGN_ATTRIBUTE __attribute__((aligned(2)))
#define ALIGN(x)        (((x)+1) 	& 0b1111111111111110)

/**
 * Crée une nouvelle FIFO.
 * @param size  taille maximale des données à stoquer (en octets). Cette taille doit contenir aussi les données maintenant la liste (2 à 3 octets par objet)
 * @return      un pointeur vers cette FIFO
 * @warning     Il s'agit en arrière plan d'un malloc, il faut donc libérer la mémoire avec ObjectFIFO_free.
 *
 * Le dimensionnement se fait ainsi : à tout instant, il faut vérifier
 *  size >= 3*(nb+1) + somme(j=1..nb, Sj) + max(j=1..nb, Sj)
 *  où  nb est le nombre d'éléments de la file
 *      Sj est la taille du j-ième élément
 */
inline ObjectFIFO ObjectFIFO_new(U16 size) {
    ObjectFIFO fifo = malloc(sizeof(*fifo));
    if(fifo != null) {
        fifo->size = size;
        ObjectFIFO_clear(fifo);
    }
    return fifo;
}

/**
 * Teste si la FIFO contient des données
 * @param fifo  FIFO à tester
 * @return      vrai si et seulement si la FIFO est vide
 */
inline U8 ObjectFIFO_isEmpty(const ObjectFIFO fifo) {
    return fifo->objNb == 0;
}

/**
 * Teste si la FIFO est pleine
 * @param fifo  FIFO à tester
 * @return      vrai si et seulement si la FIFO est pleine
 */
inline U8 ObjectFIFO_isFull(const ObjectFIFO fifo) {
    return ObjectFIFO_getAvailableSize(fifo) < sizeof(ObjectFIFO_Elem);
}

/**
 * Détermine le nombre d'octets libres dans la FIFO
 * @param fifo  FIFO à tester
 * @return      Nombre d'octets libres
 * @warning     La taille renvoyée n'est pas nécessairement utilisable. Cela dépend de la façon dont sont rangés les données.
 */
inline U16 ObjectFIFO_getAvailableSize(const ObjectFIFO fifo) {
    if(fifo->read == fifo->write) {
        return fifo->objNb==0?fifo->size:0;
    } else if(fifo->read < fifo->write) {
        return fifo->size + fifo->read - fifo->write;
    } else {
        return fifo->read - fifo->write;
    }
}

/**
 * Détermine le nombre d'octets de données stockées dans la FIFO
 * @param fifo  FIFO à tester
 * @return      Nombre d'octets de données. Comprends la mémoire utilisée pour la gestion de la file.
 */
inline U16 ObjectFIFO_getAllocatedSize(const ObjectFIFO fifo) {
    if(fifo->read == fifo->write) {
        return fifo->objNb==0?0:fifo->size;
    } else if(fifo->read > fifo->write) {
        return fifo->size + fifo->write - fifo->read;
    } else {
        return fifo->write - fifo->read;
    }
}

/**
 * Détermine le nombre d'objets stockés dans la FIFO
 * @param fifo  FIFO à tester
 * @return      Nombre d'objets.
 */
inline U16 ObjectFIFO_getObjectNb(const ObjectFIFO fifo) {
    return fifo->objNb;
}

/**
 * Vide la FIFO
 * @param fifo      FIFO à vider
 * @warning         La fonction ne libère pas la mémoire associée. Pour ça, il faut utiliser ByteFIFO_free
 */
inline void ObjectFIFO_clear(ObjectFIFO fifo) {
    fifo->write = 0;
    fifo->read = 0;
    fifo->objNb = 0;
}

/**
 * Libère la mémoire de la FIFO
 * @param fifo      FIFO à supprimer
 * @warning         La fonction libère la mémoire associée. Il faut donc l'utiliser comme un free : ne pas l'éxécuter sur une FIFO non initialisée, et ne pas essayer d'utiliser la FIFO aprè-s en avoir libéré la mémoire
 */
inline void ObjectFIFO_free(ObjectFIFO fifo) {
    free(fifo);
}

/**
 * Renvoie un pointeur vers le premier objet de la FIFO. Contrairement à ObjectFIFO_pop, il n'est pas retiré de la FIFO.
 * @param fifo  FIFO à lire
 * @return      Objet lu, null si la file était vide
 */
inline void* ObjectFIFO_get(const ObjectFIFO fifo) {
    if(!ObjectFIFO_isEmpty(fifo)) {
        return fifo->data + fifo->read + offsetof(ObjectFIFO_Elem, data);
    } else {
        return null;
    }
}

/**
 * Renvoie un pointeur vers le premier objet de la FIFO. Contrairement à ObjectFIFO_get, l'objet est retiré de la FIFO.
 * @param fifo  FIFO à lire
 * @return      Octet lu
 * @warning	Le pointeur renvoyé est valide pour accéder aux donnée que dans la mesure où aucune donnée n'est écrite par dessus, ce qui n'est garanti que tant qu'on n'ajoute pas d'objet dans la pile. Si le programme ne garantie pas une parfaite maitrise des ajouts dans la file, il vaudra mieux utiliser ObjectFIFO_get, puis ObjectFIFO_pop une fois qu'on a fini de traiter les données.
 */
inline void* ObjectFIFO_pop(ObjectFIFO fifo) {
    if(ObjectFIFO_isEmpty(fifo)) {
        return null;
    } else {
        ObjectFIFO_Elem* elem = (ObjectFIFO_Elem*)(fifo->data+fifo->read);
        fifo->read = elem->next;
        fifo->objNb--;
        return elem->data;
    }
}

/**
 * Ajoute un objet dans la FIFO.
 * @param fifo  FIFO dans laquelle écrire
 * @param size  Taille de l'objet
 * @param data	Object a àjouter
 * @return      Pointeur vers la copie de l'objet dans la FIFO. null s'il n'y avait pas assez de place
 */
inline void* ObjectFIFO_push(ObjectFIFO fifo, const U16 size, const void* data) {
    U8* blockData = (U8*) ObjectFIFO_allocate(fifo, size);
    if(blockData == null) {
        return null;
    }
    memcpy(blockData, data, size);
    return blockData;
}

/**
 * Réserve la place pour ajouter un objet dans la FIFO. Cette méthode peut être utile si on veut placer un objet dans la file dont on ne connais pas le contenu. Il suffira d'écrire dedans plus tard grâce au pointeur retourné. Par contre, il faudra faire attention à ne pas risquer de lire un objet pas encore initialisé.
 * @param fifo  FIFO dans laquelle écrire
 * @param size  Taille de la méméoire à réserver
 * @return      Pointeur vers la mémoire allouée dans la FIFO. null s'il n'y avait pas assez de place
 */
void* ObjectFIFO_allocate(ObjectFIFO fifo, const U16 size) {
    const U16 neededSize = ALIGN(sizeof(ObjectFIFO_Elem) + size);
    ObjectFIFO_Elem* block;
    U16 blockPtr;

    if(fifo->objNb==0) {
        blockPtr = 0;
    } else if(fifo->write <= fifo->read) {
        if((U8*)fifo->write + neededSize <= (U8*)fifo->read) {
            blockPtr = fifo->write;
        } else {
            return null;
        }
    } else { //write > read
        if(fifo->write + neededSize <= fifo->size) {  // assez de place à la fin du tableau
            blockPtr = fifo->write;
        } else if(neededSize <= fifo->read) { // assez de place au début du tableau
            blockPtr = 0;
        } else {
            return null;
        }
    }

    block = (ObjectFIFO_Elem*)(fifo->data + blockPtr);

    if(fifo->objNb == 0) {
        fifo->read = blockPtr;
    } else {
        fifo->lastWritten->next = blockPtr;
    }

    fifo->objNb++;
    fifo->lastWritten = block;
    fifo->write = blockPtr + neededSize;

    return block->data;
}






























