/** @file		ByteLIFO.c
	@author		ogbwJtHRXkd5H3z1RIrW2zOo
	@version	1.0
	@date		12/10/2012
	
	Ce fichier fourni les fonctions de base pour maintenir une pile d'octets dont la taille maximale est fixée (l'implémentation repose sur un tableau). Par pile, on entend une liste d'octets, réglé en mode "last in first out" (LIFO). Le dernier octet ajouté sur la pile sera le premier lu.
	Le système ne prévois pas en lui-même une protection contre les interruptions. La meilleure méthode est a priori de protéger toutes les fonctions d'ajout ou de lecture de données.
*/	

#include <stdlib.h>
#include <string.h>
#include "typedef.h"
#include "ByteLIFO.h"

/**
 * Crée une nouvelle LIFO.
 * @param size  taille maximale des données à stoquer (en octets)
 * @return      un pointeur vers cette LIFO
 * @warning     Il s'agit en arrière plan d'un malloc, il faut donc libérer la mémoire avec ByteLIFO_free.
 */
inline ByteLIFO ByteLIFO_new(const U16 size) {
	ByteLIFO lifo = (ByteLIFO) malloc(size + sizeof(*lifo));
	if(lifo != null) {
		lifo->size = size;
		lifo->next = lifo->data;
	}
	return lifo;
}

/**
 * Teste si la LIFO contient des données
 * @param lifo  LIFO à tester
 * @return      vrai si et seulement si la LIFO est vide
 */
inline U8 ByteLIFO_isEmpty(const ByteLIFO lifo) {
	return lifo->next == lifo->data;
}

/**
 * Teste si la LIFO est pleine
 * @param lifo  LIFO à tester
 * @return      vrai si et seulement si la LIFO est pleine
 */
inline U8 ByteLIFO_isFull(const ByteLIFO lifo) {
	return lifo->next == lifo->data + lifo->size;
}

/**
 * Détermine le nombre d'octets de données stockées dans la LIFO
 * @param lifo  LIFO à tester
 * @return      Nombre d'octets de données
 */
inline U16 ByteLIFO_getDataSize(const ByteLIFO lifo) {
	return lifo->next - lifo->data;
}

/**
 * Détermine le nombre d'octets libres dans la LIFO
 * @param lifo  LIFO à tester
 * @return      Nombre d'octets libres
 */
inline U16 ByteLIFO_getAvailableSize(const ByteLIFO lifo) {
	return lifo->size - (lifo->next - lifo->data);
}

/**
 * Vide la LIFO
 * @param lifo  LIFO à vider
 * @warning		La fonction ne libère pas la mémoire associée. Pour ça, il faut utiliser ByteLIFO_free
 */
inline void ByteLIFO_clear(ByteLIFO lifo) {
	lifo->next = lifo->data;
}

/**
 * Libère la mémoire de la LIFO
 * @param lifo  LIFO à supprimer
 * @warning		La fonction libère la mémoire associée. Il faut donc l'utiliser comme un free : ne pas l'éxécuter sur une LIFO non initialisée, et ne pas essayer d'utiliser la LIFO aprè-s en avoir libéré la mémoire
 */
inline void ByteLIFO_free(ByteLIFO lifo) {
	free(lifo);
}

/**
 * Renvoie la valeur du premier octet de la LIFO. Contrairement à ByteLIFO_pop, la donnée n'est pas retirée de la LIFO.
 * @param lifo  LIFO à lire
 * @return      Octet lu
 * @warning		La valeur renvoyer ne permet pas de savoir si la LIFO était vide. Il faut le tester avant d'exécuter cette fonction. Dans le cas où on l'exécute alors que la LIFO est vide, la fonction renvoie 0.
 */
inline U8 ByteLIFO_get(const ByteLIFO lifo) {
	if(!ByteLIFO_isEmpty(lifo)) {
		return *(lifo->next-1);
	}
	return 0;
}

/**
 * Renvoie la valeur du premier octet de la LIFO. Contrairement à ByteLIFO_get, la donnée est retirée de la LIFO.
 * @param lifo  LIFO à lire
 * @return      Octet lu
 * @warning		La valeur renvoyer ne permet pas de savoir si la LIFO était vide. Il faut le tester avant d'exécuter cette fonction. Dans le cas où on l'exécute alors que la LIFO est vide, la fonction renvoie 0. Par contre un test est fait afin de ne pas "supprimer" une donnée inexistante. On ne risque donc pas de corrompre la LIFO.
 */
inline U8 ByteLIFO_pop(ByteLIFO lifo) {
	if(!ByteLIFO_isEmpty(lifo)) {
		return *(--lifo->next);
	}
	return 0;
}

/**
 * Ecrit un octet dans la LIFO.
 * @param lifo  LIFO dans laquelle écrire
 * @param data	Octet a àjouter
 * @return      ByteLIFO_ok si l'écriture s'est déroulée comme prévu, ByteLIFO_full si elle était pleine.
 */
inline ByteLIFO_Error ByteLIFO_push(ByteLIFO lifo, const U8 data) {
	if(!ByteLIFO_isFull(lifo)) {
		*lifo->next = data;
		lifo->next++;
		return ByteLIFO_ok;
	} else {
		return ByteLIFO_full;
	}
}

/**
 * Ecrit plusieurs octets dans la LIFO. Les octets sont placés dans la LIFO dans l'ordre dans lequel ils sont donnés.
 * @param lifo  LIFO dans laquelle écrire
 * @param size	Nombre d'octets à écrire
 * @param data	pointeur vers les données à copier
 * @return      ByteLIFO_ok si l'écriture s'est déroulée comme prévu, ByteLIFO_full si la place disponible n'était pas suffisante. Dans ce cas, aucun octet n'est copié.
 */
inline ByteLIFO_Error ByteLIFO_pushBlock(ByteLIFO lifo, const U16 size, const void* data) {
	if(ByteLIFO_getAvailableSize(lifo) < size) {
		return ByteLIFO_full;
	}
	memcpy(lifo->next, data, size);
	lifo-> next += size;
	return ByteLIFO_ok;
}

/**
 * Ecrit plusieurs octets dans la LIFO. L'ordre des octets est inversé avent de les placer dans la LIFO
 * @param lifo  LIFO dans laquelle écrire
 * @param size	Nombre d'octets à écrire
 * @param data	pointeur vers les données à copier
 * @return      ByteLIFO_ok si l'écriture s'est déroulée comme prévu, ByteLIFO_full si la place disponible n'était pas suffisante. Dans ce cas, aucun octet n'est copié.
 */
inline ByteLIFO_Error ByteLIFO_rpushBlock(ByteLIFO lifo, const U16 size, const void* data) {
	if(ByteLIFO_getAvailableSize(lifo) < size) {
		return ByteLIFO_full;
	}
	U8* data_ = (U8*) data;
	U8* rp = data_+(size-1), *wp = lifo->next;
	for(;rp>=data_;) {
		*(wp++) = *(rp--);
	}
	lifo->next = wp;
	return ByteLIFO_ok;
}

/**
 * Lit plusieurs octets de la LIFO. Les octets sont placés dans le buffer dans l'ordre dans lequel ils sont lus.
 * @param lifo  LIFO à lire
 * @param size	Nombre d'octets à lire
 * @param data	pointeur vers le buffer dans lequel les données lues sont copiées
 * @return      ByteLIFO_ok si la lecture s'est déroulée comme prévu, ByteLIFO_notEnoughtData si on a essayé de lire plus de données qu'il y en avait disponibles. Dans ce cas, aucun octet n'est lu.
 */
inline ByteLIFO_Error ByteLIFO_popBlock(ByteLIFO lifo, const U16 size, void* data) {
	if(ByteLIFO_getDataSize(lifo) < size) {
		return ByteLIFO_notEnoughtData;
	}
	U8* data_ = (U8*) data;
	U8* wp = data_+size, *rp = lifo->next-size;
	for(;wp>=data_;) {
		*(--wp) = *(rp++);
	}
	lifo->next -= size;
	return ByteLIFO_ok;
}

/**
 * Lit plusieurs octets de la LIFO. Les octets sont placés dans le buffer dans l'ordre inverse à celui dans lequel ils sont lus (et donc dans l'ordre dans lequel ils ont été ajoutés à la LIFO)
 * @param[in,out] lifo  LIFO à lire
 * @param[in] size	Nombre d'octets à lire
 * @param[out] data	pointeur vers le buffer dans lequel les données lues sont copiées
 * @return      ByteLIFO_ok si la lecture s'est déroulée comme prévu, ByteLIFO_notEnoughtData si on a essayé de lire plus de données qu'il y en avait disponibles. Dans ce cas, aucun octet n'est lu.
 */
inline ByteLIFO_Error ByteLIFO_rpopBlock(ByteLIFO lifo, const U16 size, void* data) {
	if(ByteLIFO_getDataSize(lifo) < size) {
		return ByteLIFO_notEnoughtData;
	}
	lifo-> next -= size;
	memcpy(data, lifo->next, size);
	return ByteLIFO_ok;
}
