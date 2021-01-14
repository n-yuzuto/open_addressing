#include <stdio.h>
#include <stdlib.h>
#include "open_addressing.h"

DictOpenAddr *create_dict(int len) {
    DictOpenAddr *another_dict = (DictOpenAddr*)malloc(sizeof(DictOpenAddr)); 
    if (another_dict != NULL) {
        another_dict -> H = (DictData*)malloc(sizeof(DictData));
        if (another_dict -> H == NULL) {
            printf("failed to secure the area.\n");
            free(another_dict);
            return NULL;
        }
        another_dict -> B = len;
        int i = 0;
        while (i < len)
        {
            another_dict -> H[i].state = EMPTY;
            i ++;
        }
    }
    printf("Dictionary created!\n");
    return another_dict;
}

int h(DictOpenAddr *dict, int d, int count) {
    return (d + count) % dict -> B;
}

int search_hash(DictOpenAddr *dict, int d) {
    int count = 0;
    int b = h(dict, d, count);
    int init_b = b;
    do {
        if (dict -> H[b].state == OCCUPIED) {
            if (dict -> H[b].name == d){
                return b;
            } 
        }
        else if (dict -> H[b].state == EMPTY) {
            return -1;
        }
        count += 1;
        b = h(dict, d, count);
    } while (b != init_b);
    return -1;
}

void insert_hash(DictOpenAddr *dict, int d) {
    if (search_hash(dict, d) != -1){
        return ;
    } 
    int count = 0;
    int b = h(dict, d, count);
    int init_b = b;
    do {
        if (dict -> H[b].state == EMPTY || dict->H[b].state == DELETED) {
            dict -> H[b].name = d;
            dict -> H[b].state = OCCUPIED;
            return;
        }
        count += 1;
        b = h(dict, d, count);
    } while (b != init_b);
    printf("hash is full\n");
    return;
}

void delete_hash(DictOpenAddr *dict, int d) {
    int b = search_hash(dict, d);
    if (b == -1){
        printf("data d is nowhere in the array.\n");
        return;
    } 
    dict -> H[b].state = DELETED;

    return;
}

void display(DictOpenAddr *dict) {
    int index = 0;
    for (int index = 0; index < dict -> B; index++){
         if (dict->H[index].state == EMPTY) {
            printf("e ");
        }
        else if (dict -> H[index].state == DELETED) {
            printf("d ");
        }
        else {
            printf("%d ", dict -> H[index].name);
        }
    }
    printf("\n");
}

void delete_dict(DictOpenAddr *dict) {
    free(dict);
    printf("Dictionary deleted!\n");
}