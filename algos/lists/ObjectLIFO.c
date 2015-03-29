/**@file        ObjectLIFO.c
 * @author     ogbwJtHRXkd5H3z1RIrW2zOo
 * @version    1.0
 * @date       21/10/2012
 *
 * Ce fichier fourni les fonctions de base pour maintenir une pile "d'objets" dont la taille maximale est fixée (l'implémentation repose sur un tableau).
 * Un objet est une suite d'octets quelconque. Le plus souvent, il s'agira d'une structure. La mémoire est organisée de façon à ce qu'on puisse lire l'objet à partir d'un pointeur. L'ordre les octets représentant les object n'est pas affecté.
 * Par pile, on entend une liste LIFO (last in first out).
 * Le système ne prévois pas en lui-même une protection contre les interruptions. La meilleure méthode est a priori de protéger toutes les fonctions d'ajout ou de lecture de données.
 * L'utilisateur doit être capable de connaitre la taille de ses données. La LIFO ne prévoit pas de moyen de la calculer (bien que ce soit en théorie possible)
 */

#include "Ogbwlib.h"
#include "ObjectLIFO.h"
#include <stdlib.h>
#include <string.h>

/**
 * Crée une nouvelle LIFO.
 * @param size  taille maximale des données à stoquer (en octets). Cette taille doit contenir aussi les données maintenant la liste (2 à 3 octets par objet)
 * @return      un pointeur vers cette LIFO
 * @warning     Il s'agit en arrière plan d'un malloc, il faut donc libérer la mémoire avec ObjectLIFO_free.
 *
 * Le dimensionnement se fait ainsi : à tout instant, il faut vérifier
 *  size >= 3*(nb+1) + somme(j=1..nb, Sj)
 *  où  nb est le nombre d'éléments de la file
 *      Sj est la taille du j-ième élément
 */
inline ObjectLIFO ObjectLIFO_new(const U16 size) {
	ObjectLIFO lifo = (ObjectLIFO) malloc(size+sizeof(struct ObjectLIFO_struct));
	if(lifo != null) {
		lifo->size = size;
		ObjectLIFO_clear(lifo);
	}
	return lifo;
}

/**
 * Teste si la LIFO contient des données
 * @param lifo  LIFO à tester
 * @return      vrai si et seulement si la LIFO est vide
 */
inline U8 ObjectLIFO_isEmpty(const ObjectLIFO lifo) {
	return lifo->allocatedSize == 0;
}

/**
 * Teste si la LIFO est pleine
 * @param lifo  LIFO à tester
 * @return      vrai si et seulement si la LIFO est pleine
 */
inline U8 ObjectLIFO_isFull(const ObjectLIFO lifo) {
	return lifo->allocatedSize == lifo->size;
}

/**
 * Détermine le nombre d'octets libres dans la LIFO
 * @param lifo  LIFO à tester
 * @return      Nombre d'octets libres
 * @warning     La taille renvoyée n'est pas totalement utilisable, il faut retirer 3 octets pour avoir la taille du plus gros objet stockable.
 */
inline U16 ObjectLIFO_getAvailableSize(const ObjectLIFO lifo) {
	return lifo->size - lifo->allocatedSize;
}

/**
 * Détermine le nombre d'octets de données stockées dans la LIFO
 * @param lifo  LIFO à tester
 * @return      Nombre d'octets de données. Comprends la mémoire utilisée pour la gestion de la file.
 */
inline U16 ObjectLIFO_getAllocatedSize(const ObjectLIFO lifo) {
	return lifo->allocatedSize;
}

/**
 * Détermine le nombre d'objets stockés dans la LIFO
 * @param lifo  LIFO à tester
 * @return      Nombre d'objets.
 */
inline U16 ObjectLIFO_getObjectNb(const ObjectLIFO lifo) {
	return lifo->objNb;
}

/**
 * Vide la LIFO
 * @param lifo      LIFO à vider
 * @warning         La fonction ne libère pas la mémoire associée. Pour ça, il faut utiliser ByteLIFO_free
 */
inline void ObjectLIFO_clear(ObjectLIFO lifo) {
	lifo->allocatedSize = 0;
	lifo->current = null;
	lifo->objNb = 0;
}

/**
 * Libère la mémoire de la LIFO
 * @param lifo      LIFO à supprimer
 * @warning         La fonction libère la mémoire associée. Il faut donc l'utiliser comme un free : ne pas l'éxécuter sur une LIFO non initialisée, et ne pas essayer d'utiliser la LIFO aprè-s en avoir libéré la mémoire
 */
inline void ObjectLIFO_free(ObjectLIFO lifo) {
	free(lifo);
}

/**
 * Renvoie un pointeur vers le premier objet de la LIFO (et donc le dernier ajouté). Contrairement à ObjectLIFO_pop, il n'est pas retiré de la LIFO.
 * @param lifo  LIFO à lire
 * @return      Objet lu, null si la file était vide
 */
inline void* ObjectLIFO_get(const ObjectLIFO lifo) {
	if(lifo->current == null) {
		return null;
	 } else {
		return lifo->current->data;
	}
}

/**
 * Renvoie un pointeur vers le premier objet de la LIFO (le dernier qui a été ajouté). Contrairement à ObjectLIFO_get, l'objet est retiré de la LIFO.
 * @param lifo  LIFO à lire
 * @return      Octet lu
 * @warning	Le pointeur renvoyé est valide pour accéder aux donnée que dans la mesure où aucune donnée n'est écrite par dessus, ce qui n'est garanti que tant qu'on n'ajoute pas d'objet dans la pile. Si le programme ne garantie pas une parfaite maitrise des ajouts dans la file, il vaudra mieux utiliser ObjectLIFO_get, puis ObjectLIFO_pop une fois qu'on a fini de traiter les données.
 */
inline void* ObjectLIFO_pop(ObjectLIFO lifo) {
	if(lifo->current != null) {
		U8* ret = lifo->current->data;
		lifo->allocatedSize = (U8*)lifo->current - lifo->data;
		lifo->current = lifo->current->prec;
		lifo->objNb--;
		return ret;
	}
	return null;
}

/**
 * Ajoute un objet dans la LIFO.
 * @param lifo  LIFO dans laquelle écrire
 * @param size  Taille de l'objet
 * @param data	Object a àjouter
 * @return      Pointeur vers la copie de l'objet dans la LIFO. null s'il n'y avait pas assez de place
 */
inline void* ObjectLIFO_push(ObjectLIFO lifo, const U16 size, const void* data) {
	if(ObjectLIFO_getAvailableSize(lifo) < size + sizeof(ObjectLIFO_Elem)) {
		return null;
	}
	ObjectLIFO_Elem* new = (ObjectLIFO_Elem*) (lifo->data + lifo->allocatedSize);
	new->prec = lifo->current;
	lifo-> current = new;
	lifo->allocatedSize += size + sizeof(ObjectLIFO_Elem);
	lifo->allocatedSize += lifo->allocatedSize&1?1:0; // always align on word
	
	memcpy(new->data, data, size);
	return new->data;
}

/**
 * Réserve la place pour ajouter un objet dans la LIFO. Cette méthode peut être utile si on veut placer un objet dans la pile dont on ne connais pas le contenu. Il suffira d'écrire dedans plus tard grâce au pointeur retourné. Par contre, il faudra faire attention à ne pas risquer de lire un objet pas encore initialisé.
 * @param lifo  LIFO dans laquelle écrire
 * @param size  Taille de la méméoire à réserver
 * @return      Pointeur vers la mémoire allouée dans la LIFO. null s'il n'y avait pas assez de place
 */
inline void* ObjectLIFO_alloc(ObjectLIFO lifo, const U16 size) {
	if(ObjectLIFO_getAvailableSize(lifo) < size + sizeof(ObjectLIFO_Elem)) {
		return null;
	}
	ObjectLIFO_Elem* new = (ObjectLIFO_Elem*) (lifo->data + lifo->allocatedSize);
	new->prec = lifo->current;
	lifo-> current = new;
	lifo->allocatedSize += size + sizeof(ObjectLIFO_Elem);
	lifo->allocatedSize += lifo->allocatedSize&1?1:0; // always align on word
	
	return new->data;
}




	






