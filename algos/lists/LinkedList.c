#include <stdlib.h>
#include "typedef.h"
#include "LinkedList.h"

void getMeOutOfThisList(volatile LinkedList list, LinkedList_item * curr) {
    if(curr == list->first) {	// premier de la liste
        list->first = curr->next;
        if(curr->next != null) {	// cas ou il n'y avait qu'un élément dans la liste (premier et dernier)
            curr->next->prev = null;
        } else {
            list->last = null;
        }
    } else if(curr == list->last) { // dernier de la liste
        list->last = curr->prev;
        curr->prev->next = null; // le cas d'un seul élément dans la liste est passé en tant que 1° élément de la liste
    } else {	// élément au milieu
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }
}//


LinkedList LinkedList_new() {
    LinkedList ret = malloc(sizeof(*ret));
    if(ret != null) {
        ret->first = null;
        ret->last = null;
    }
    return ret;
}//

U16 LinkedList_size(volatile LinkedList list) {
    U16 size=0;
    LinkedList_item * curr = list->first;
    for(;curr!=null;curr=curr->next) {
        size++;
    }
    return size;
}//

U8 LinkedList_isEmpty(volatile LinkedList list) {
    return list->first==null;
}//


LinkedList_error LinkedList_addFirst(volatile LinkedList list, void* data) {
    LinkedList_item * new = malloc(sizeof(LinkedList_item));
    if(new == null) {
        return LINKEDLIST_OUT_OF_MEMORY;
    }

    new->prev = null;
    new->next = list->first;
    new->data = data;

    list->first->prev = new;
    list->first = new;
    if(new->next == null) {
        list->last = new;
    }

    return LINKEDLIST_SUCCESS;
}//

LinkedList_error LinkedList_addMiddle(volatile LinkedList list, void* data, U16 num) { // num correspond à la pos finale, comptée à partir de 0
    if(num == 0) {	// cas particulier pénible
        return LinkedList_addFirst(list, data);
    }

    if(LinkedList_isEmpty(list)) { // ce cas passe à travers du filtre ci-dessous
        return LINKEDLIST_OUT_OF_RANGE;
    }

    LinkedList_item * curr = list->first;
    U16 i;
    for(i=1;i<num;i++) {
        if(curr == null) {
            return LINKEDLIST_OUT_OF_RANGE;
        }
        curr = curr->next;
    }

    if(curr == list->last) {	// cas particulier pénible
        return LinkedList_addLast(list, data);
    }

    LinkedList_item * new = malloc(sizeof(LinkedList_item));
    if(new == null) {
        return LINKEDLIST_OUT_OF_MEMORY;
    }

    new->prev = curr;
    new->next = curr->next;
    new->data = data;

    curr->next = new;
    new->next->prev = new;

    return LINKEDLIST_SUCCESS;
}//

LinkedList_error LinkedList_addLast(volatile LinkedList list, void* data) {
    LinkedList_item * new = malloc(sizeof(LinkedList_item));
    if(new == null) {
        return LINKEDLIST_OUT_OF_MEMORY;
    }

    new->prev = list->last;
    new->next = null;
    new->data = data;

    list->last->next = new;
    list->last = new;
    if(new->prev == null) {
        list->first = new;
    }

    return LINKEDLIST_SUCCESS;
}//

LinkedList_error LinkedList_addSorted(volatile LinkedList list, void* data, U8 (*isSmaller)(void*, void*)) { // suppose implicitement que toute la liste est triée
    if(LinkedList_isEmpty(list) || isSmaller(data, list->first->data)) {	// liste vide ou placer au début
        return LinkedList_addFirst(list, data);	// isSmaller doit revoyer vrai si =
    } else if(isSmaller(list->last->data, data)) {	// on place à la fin
        return LinkedList_addLast(list, data);
    } else {	// cas général, sauf premier et dernier élément
        LinkedList_item * new = malloc(sizeof(LinkedList_item));
        if(new == null) {
            return LINKEDLIST_OUT_OF_MEMORY;
        }

        LinkedList_item * curr = list->first;
        while(!isSmaller(data, curr->next->data)) {
            curr = curr->next;
        }

        new->prev = curr;
        new->next = curr->next;
        new->data = data;

        curr->next = new;
        new->next->prev = new;

        return LINKEDLIST_SUCCESS;
    }
}//


void* LinkedList_getFirst(volatile LinkedList list) {
    if(LinkedList_isEmpty(list)) {
        return null;
    } else {
        return list->first->data;
    }
}//

void* LinkedList_getMiddle(volatile LinkedList list, U16 num) {
    LinkedList_item * curr = list->first;
    U16 i;
    for(i=0;i<num;i++) {
        if(curr == null) {
            return null;
        }
        curr = curr->next;
    }

    return curr->data;
}//

void* LinkedList_getLast(volatile LinkedList list) {
    if(LinkedList_isEmpty(list)) {
        return null;
    } else {
        return list->last->data;
    }
}//

void* LinkedList_getFilter(volatile LinkedList list, U8 (*match)(void*)) {
    LinkedList_item * curr = list->first;
    while(curr!=null) {
        if(match(curr->data)) {
            return curr->data;
        } else {
            curr = curr->next;
        }
    }
    return null;
}//


void* LinkedList_removeFirst(volatile LinkedList list) {
    if(LinkedList_isEmpty(list)) {
        return null;
    }
    LinkedList_item * first = list->first;

    void * ret = first->data;
    getMeOutOfThisList(list, first);
    free(first);
    return ret;
}//

void* LinkedList_removeMiddle(volatile LinkedList list, U16 num) {
    LinkedList_item * curr = list->first;
    U16 i;
    for(i=0;i<num;i++) {
        if(curr == null) {
            return null;
        }
        curr = curr->next;
    }

    void * ret = curr->data;
    getMeOutOfThisList(list, curr);
    free(curr);
    return ret;
}//

void* LinkedList_removeLast(volatile LinkedList list) {
    if(LinkedList_isEmpty(list)) {
        return null;
    }
    LinkedList_item * last = list->last;

    void * ret = last->data;
    getMeOutOfThisList(list, last);
    free(last);
    return ret;
}//

void* LinkedList_removePtr(volatile LinkedList list, void* data) {
    LinkedList_item * curr = list->first;
    while(curr!=null) {
        if(curr->data == data) {
            getMeOutOfThisList(list,curr);
            void * ret = curr->data;
            free(curr);
            return ret;
        } else {
            curr = curr->next;
        }
    }
    return null;
}//

void* LinkedList_removeFilter(volatile LinkedList list, U8 (*match)(void*)) {
    LinkedList_item * curr = list->first;
    while(curr!=null) {
        if(match(curr->data)) {
            getMeOutOfThisList(list,curr);
            void * ret = curr->data;
            free(curr);
            return ret;
        } else {
            curr = curr->next;
        }
    }
    return null;
}//

U16 LinkedList_removeAll(volatile LinkedList list) {
    LinkedList_item * curr = list->first;
    U16 ret=0;
    while(curr!=null) {
        getMeOutOfThisList(list,curr);
        LinkedList_item * tmp=curr;
        curr = curr->next;
        free(tmp);
        ret++;
    }
    return ret;
}//

U16 LinkedList_removeAllPtr(volatile LinkedList list, void* data) {
    LinkedList_item * curr = list->first;
    U16 ret=0;
    while(curr!=null) {
        LinkedList_item * next = curr->next;
        if(curr->data == data) {
            getMeOutOfThisList(list,curr);
            free(curr);
            ret++;
        }
        curr=next;
    }
    return ret;
}//

U16 LinkedList_removeIf(volatile LinkedList list, U8 (*match)(void*)) {
    LinkedList_item * curr = list->first;
    U16 ret=0;
    while(curr!=null) {
        LinkedList_item * next = curr->next;
        if(match(curr->data)) {
            getMeOutOfThisList(list,curr);
            free(curr);
            ret++;
        }
        curr=next;
    }
    return ret;
}//


void LinkedList_deleteFirst(volatile LinkedList list) {
    void * ret = LinkedList_removeFirst(list);
    if(ret != null) {
        free(ret);
    }
}//

void LinkedList_deleteMiddle(volatile LinkedList list, U16 num) {
    void * ret = LinkedList_removeMiddle(list, num);
    if(ret != null) {
        free(ret);
    }
}//

void LinkedList_deleteLast(volatile LinkedList list) {
    void * ret = LinkedList_removeLast(list);
    if(ret != null) {
        free(ret);
    }
}//

void LinkedList_deletePtr(volatile LinkedList list, void* data) {
    LinkedList_removePtr(list, data);
    free(data);
}//

void LinkedList_deleteFilter(volatile LinkedList list, U8 (*match)(void*)) {
    void * ret = LinkedList_removeFilter(list, match);
	if(ret != null) {
		free(ret);
	}
}//

U16 LinkedList_deleteAll(volatile LinkedList list) {
    LinkedList_item * curr = list->first;
    U16 ret=0;
    while(curr!=null) {
        LinkedList_item * next = curr->next;
        getMeOutOfThisList(list,curr);
        free(curr->data);
        free(curr);
        ret++;
        curr=next;
    }
    return ret;
}//

U16 LinkedList_deleteAllWithDuplicates(volatile LinkedList list){
    U16 ret=0;
    while(!LinkedList_isEmpty(list)) {
        ret += LinkedList_deleteAllPtr(list, list->first);
    }
    return ret;
}

U16 LinkedList_deleteAllPtr(volatile LinkedList list, void* data) {
    free(data);
    return LinkedList_removeAllPtr(list, data);
}

U16 LinkedList_deleteIf(volatile LinkedList list, U8 (*match)(void*)) {
    LinkedList_item * curr = list->first;
    U16 ret=0;
    while(curr!=null) {
        LinkedList_item * next = curr->next;
        if(match(curr->data)) {
            getMeOutOfThisList(list,curr);
            free(curr->data);
            free(curr);
            ret++;
        }
        curr = next;
    }
    return ret;
}//


void LinkedList_executeAll(volatile LinkedList list, void (*todo)(void*)) {
    LinkedList_item * curr = list->first;
    while(curr!=null) {
        todo(curr->data);
        curr = curr->next;
    }
}//

U16 LinkedList_executeIf(volatile LinkedList list, U8 (*match)(void*), void (*todo)(void*)) {
    LinkedList_item * curr = list->first;
    U16 ret=0;
    while(curr!=null) {
        if(match(curr->data)) {
            todo(curr->data);
            ret++;
        }
        curr = curr->next;
    }
    return ret;
}//

void LinkedList_reverseExecuteAll(volatile LinkedList list, void (*todo)(void*)) {
    LinkedList_item * curr = list->last;
    while(curr!=null) {
        todo(curr->data);
        curr = curr->prev;
    }
}//

U16 LinkedList_reverseExecuteIf(volatile LinkedList list, U8 (*match)(void*), void (*todo)(void*)) {
    LinkedList_item * curr = list->last;
    U16 ret=0;
    while(curr!=null) {
        if(match(curr->data)) {
            todo(curr->data);
            ret++;
        }
        curr = curr->prev;
    }
    return ret;
}//

void LinkedList_reverse(LinkedList list) {
    if(!LinkedList_isEmpty(list)) {
        LinkedList_item * src = list->first->next;
        LinkedList_item * dest = list->first;
        list->last = dest;
        dest->next=null;
        while(src != null) {
            LinkedList_item * next = src->next;
            dest->prev = src;
            src->next = dest;
            dest = src;
            src = next;
        }
        list->first = dest;
        dest->prev=null;
    }
}

LinkedList_error LinkedList_addAllFirst(LinkedList dest, LinkedList src) {
    LinkedList_item * curr = src->last;
    while(curr!=null) {
        if(LinkedList_addFirst(dest, curr->data) == LINKEDLIST_OUT_OF_MEMORY) {
            return LINKEDLIST_OUT_OF_MEMORY;
        }
        curr = curr->prev;
    }
}

LinkedList_error LinkedList_addAllLast(LinkedList dest, LinkedList src) {
    LinkedList_item * curr = src->first;
    while(curr!=null) {
        if(LinkedList_addLast(dest, curr->data) == LINKEDLIST_OUT_OF_MEMORY) {
            return LINKEDLIST_OUT_OF_MEMORY;
        }
        curr = curr->next;
    }
}

LinkedList_error LinkedList_addAllMiddle(LinkedList dest, LinkedList src, int n) {
    LinkedList_item * curr = src->last;
    while(curr!=null) {
        if(LinkedList_addMiddle(dest, curr->data, n) == LINKEDLIST_OUT_OF_MEMORY) {
            return LINKEDLIST_OUT_OF_MEMORY;
        }
        curr = curr->prev;
    }
}

LinkedList_error LinkedList_addAllSorted(LinkedList dest, LinkedList src, U8 (*isSmaller)(void*, void*)) {
    LinkedList_item * curr = src->first;
    while(curr!=null) {
        if(LinkedList_addSorted(dest, curr->data, isSmaller) == LINKEDLIST_OUT_OF_MEMORY) {
            return LINKEDLIST_OUT_OF_MEMORY;
        }
        curr = curr->next;
    }
}

LinkedList LinkedList_merge(LinkedList list1, LinkedList list2) {
    if(LinkedList_isEmpty(list1)) {
        free(list1);
        return list2;
    } else if(LinkedList_isEmpty(list2)) {
        free(list2);
        return list1;
    } else {
        list1->last->next = list2->first;
        list2->first->prev = list1->last;
        list1->last = list2->last;
        free(list2);
        return list1;
    }
}

LinkedList LinkedList_mergeSorted(LinkedList list1, LinkedList list2, U8 (*isSmaller)(void*, void*)) {
    if(LinkedList_isEmpty(list1)) {
        free(list1);
        return list2;
    } else if(LinkedList_isEmpty(list2)) {
        free(list2);
        return list1;
    } else {
        LinkedList_item * curr1 = list1->first;
        LinkedList_item * curr2 = list2->first;
        LinkedList_item * currnew;

        if(isSmaller(curr2->data,curr1->data)) {
            currnew = curr2;
            curr2 = curr2->next;
        } else {
            currnew = curr1;
            curr1 = curr1->next;
        }
        list1->first = currnew;
        currnew->prev = null;

        while(curr1!=null && curr2!=null) {
            if(isSmaller(curr2->data,curr1->data)) {
                currnew->next = curr2;
                curr2 = curr2->next;
            } else {
                currnew->next = curr1;
                curr1 = curr1->next;
            }
            currnew->next->prev = currnew;
            currnew = currnew->next;
        }

        if(curr1==null) {
            currnew->next = curr2;
            curr2->prev = currnew;
            list1->last = list2->last;
        } else {
            currnew->next = curr1;
            curr1->prev = currnew;
        }

        free(list2);
        return list1;
    }
}

