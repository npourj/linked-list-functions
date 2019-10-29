/*
 * author: Nick Pourjalilvand
 * email: nkp5157@psu.edu
 * dict.c for CMPSC 311 Fall 2019
 * last updated: 10/23/2019
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dict.h"

// count number of keys in a dict.
int countKeys(const dictNode *dict) {
  int num = 0;
  while (dict != NULL) {
    num += 1;
    dict = dict->next;
  }
  return num;
}

// given a key, look up its corresponding value in the
// dictionary, returns -1 if the value is not in the dictionary.
// your search for key should end when the key in the next node
// is bigger than the lookup key or you reached the end of the
// list.
int lookupKey(const dictNode *dict, const char *key) {
  int isCorrectKey = 0;
  bool keepSearching = true;
  //loop through list, stop when you find the right key
  //or when the next node is bigger
  while((dict != NULL) && keepSearching) {
    isCorrectKey = strcmp(dict->key, key);
    if (isCorrectKey == 0) {
      return dict->value;
    }
    else if (isCorrectKey > 0) {
      keepSearching = false;
    }
    dict = dict->next;
  }
  return -1;
}

// delete the node in a dict with given key, return the value of
// the deleted node if it was found, return -1 if it wasn't found.
int deleteKey(dictNode **dict, const char *key) {
  int isCorrectKey = 0;
  int nodeValue = 0;
  //Case: empty list
  dictNode *current = *dict;
  dictNode *prev = *dict;
  if (countKeys(*dict) == 0)
    return -1;
  //Case: key is not in list
  else if (lookupKey(*dict, key) == -1)
    return -1;
  //Case: only 1 node in list
  else if (countKeys(*dict) == 1) {
    if (strcmp(current->key, key) == 0) {
      nodeValue = current->value;
      freeNode(current);
      return nodeValue;
    }
  }
  else {
    isCorrectKey = strcmp(current->key, key);
    //Case: beginning of list
    if (isCorrectKey == 0) {
      nodeValue = current->value;
      *dict = current->next;
      current->next = NULL;
      freeNode(current);
      return nodeValue;
    }
    current = current->next;
    while ((current != NULL)) {
      isCorrectKey = strcmp(current->key, key);
      if (isCorrectKey == 0) {
        //Case: last node in list
        if (current->next == NULL) {
          nodeValue = current->value;
          prev->next = NULL;
          freeNode(current);
        }
        //Case: middle of list
        else {
          nodeValue = current->value;
          prev->next = current->next;
          current->next = NULL;
          freeNode(current);
          return nodeValue;
        }
      }
    prev = current;
    current = current->next;
    }
  }
  return -1;
}
// given a key/value pair, first lookup the key in the dictionary,
// if it is already there, update the dictionary with the new
// value; if it is not in the dictionary, insert a new node into
// the dictionary, still make sure that the key is in alphabetical
// order.
// IMPORTANT: When creating a new node, make sure you dynamically
// :allocate memory to store a copy of the key in the memory. You
// may use strdup function. DO NOT STORE the input key from the 
// argument directly into the node. There is no guarantee that key
// pointer's value will stay the same. 
// YOU MUST KEEP THE ALPHABETICAL ORDER OF THE KEY in the dictionary.
void addKey(dictNode **dict, const char *key, int value) {
  int isCorrectKey = 0;
  dictNode *current = *dict;
  dictNode *prev = NULL;
  //Case: dict is NULL
  if (*dict == NULL) {
    dictNode *newNode;
    newNode = (dictNode*)malloc(sizeof(dictNode));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = NULL;
    *dict = newNode;
    return;
  }
  while (current != NULL) {
    isCorrectKey = strcmp(current->key, key);
    //Case: key already in list
    if (isCorrectKey == 0) {
      current->value = value;
      return;
    }
    //Knows to insert here
    if (isCorrectKey > 0) {
      //Case: insert into first spot
      if (prev == NULL) {
        dictNode *newNode;
        newNode = (dictNode*)malloc(sizeof(dictNode));
        newNode->key = strdup(key);
        newNode->value = value;
        newNode->next = current;
        *dict = newNode;
        return;
      }
      //Case: insert into middle
      else {
        dictNode *newNode;
        newNode = (dictNode*)malloc(sizeof(dictNode));
        newNode->key = strdup(key);
        newNode->value = value;
        newNode->next = current;
        prev->next = newNode;
        return;
      }
    }
    if (prev == NULL) {
      prev = current;
      current = current->next;
    }
    else {
    prev = current;
    current = current->next;
    }
  }

  //Case: insert into last position
  current = NULL;
  dictNode *newNode;
  newNode = (dictNode*)malloc(sizeof(dictNode));
  newNode->key = strdup(key);
  newNode->value = value;
  newNode->next = NULL;
  prev->next = newNode;
  return;
}
