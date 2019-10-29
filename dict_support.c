/*
 * author: Yanling Wang
 * email: yuw17@psu.edu
 * dict_support.c for CMPSC 311 Fall 2019
 * last updated: 10/15/2019
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dict.h"


void displayDict(const dictNode *dict) {
  while(dict != NULL) {
    printf("\"%s\":%d ", dict->key, dict->value);
    dict = dict->next;
  }
  printf("\n");
  return;
}

/* free a node's memory (including key/value) */
void freeNode(dictNode *current) {
  free(current->key);
  free(current);
}

/* delete all nodes in a dict */
void destroyDict(dictNode **dictPtr) {
  dictNode *current = *dictPtr;
  while(current != NULL) {
    *dictPtr = current -> next;
    freeNode(current);
    current = *dictPtr;
  }
  return;
}

// create a dict based on arrays of keys and values of length elements.
dictNode *makeDict(const char *keys[], int values[], int length) {
  dictNode *dict = NULL;
  dictNode *newNode = NULL;
  int i;
  for (i = length - 1; i >= 0; i--) {
    newNode = malloc(sizeof(dictNode));
    newNode->key = strdup(keys[i]);
    newNode->value = values[i];
    newNode->next = dict;
    dict = newNode;
  }
  return dict;
}

void assertEqualDict(const dictNode *dict, const char *keys[], int values[], int length) {
  int i = 0;
  while (dict && i < length) {
    assert(!strcmp(dict->key, keys[i]));
    assert(dict->value == values[i]);
    dict = dict->next;
    i++;
  }
  assert(i == length);
  assert(dict == NULL);
}
