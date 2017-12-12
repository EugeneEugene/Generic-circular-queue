#include "queue.h" 
#include <stdlib.h>
#include <string.h> 

/* creates a new queue with a given size */
queue_t* create_queue(int capacity) {  
    queue_t *queue; 
    queue = malloc(sizeof(queue_t));
    queue->arrray = malloc(capacity * sizeof(void *)); 
    queue->head = -1; 
    queue->tail = -1; 
    queue->maxSize = capacity; 
    queue->size = 0; 
    return queue;
}

/* deletes the queue and all allocated memory */
void delete_queue(queue_t *queue) { 
    free(queue->arrray);
    free(queue); 
}

/*
 * inserts a reference to the element into the queue
 * returns: true on success; false otherwise
 */
bool push_to_queue(queue_t *queue, void *data) {  
    if(queue->size >= queue->maxSize) { 
        return false;
    }  
    if(queue -> size == 0) { 
        queue->tail = 0; 
        queue -> head = 0; 
        queue->arrray[queue->tail] = data;  
        queue -> size ++;
        return true;
    }
    queue->tail = (queue->tail + 1) % queue->maxSize; 
    queue->arrray[queue->tail] = data; 
    queue->size++; 
    return true;
}

/*
 * gets the first element from the queue and removes it from the queue
 * returns: the first element on success; NULL otherwise
 */
void* pop_from_queue(queue_t *queue) { 
    if(queue->size == 0) { 
        return NULL;
    }
    void* firstElement = queue->arrray[queue->head]; 
    queue->arrray[queue->head] = NULL; 
    queue->size--;
    queue->head = (queue->head + 1) % queue->maxSize; 
    return firstElement;
}

/*
 * gets idx-th element from the queue
 * returns the element that will be popped after idx calls of the pop_from_queue()
 * returns: the idx-th element on success; NULL otherwise
 */
void* get_from_queue(queue_t *queue, int idx) { 
    if(idx <0 || idx >= queue->size) { 
        return NULL;
    }
    if((queue->arrray + ((queue->head + idx) % queue->maxSize)) == NULL) { 
        return NULL;
    } 
    return *(queue->arrray + ((queue->head + idx) % queue->maxSize));
}

/* gets number of stored elements */
int get_queue_size(queue_t *queue) {
    return queue->size;
}
