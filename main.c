/*
 * author: Yanling Wang
 * email: yuw17@psu.edu
 * main.c for CMPSC 311 Fall 2019
 * last updated: 10/15/2019
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dict.h"
void testCount() {
  // dict1
  const char *keys1[] = {"a", "b", "c", "e", "f"};
  int values1[] = {1, 2, 3, 4, 5};
  dictNode *dict = NULL;
  assert(countKeys(dict) == 0);
  dict = makeDict(keys1, values1, 5);
  assert(countKeys(dict) == 5);
  destroyDict(&dict);
  printf("passed testCount\n");
}

void testLookup() {
  // dict1
  const char *keys1[] = {"a", "b", "c", "e", "f"};
  int values1[] = {1, 2, 3, 4, 5};
  // dict2: an out of order dict to test for proper
  // early termination of search.
  const char *keys2[] = {"happy", "angry"};
  int values2[] = {10, 20};
  // testing lookup in empty dict
  dictNode *dict = NULL;
  assert(lookupKey(dict, "a") == -1);
  // testing lookup in dict1
  dict = makeDict(keys1, values1, 5);
  assert(lookupKey(dict, "a") == 1);
  assert(lookupKey(dict, "b") == 2);
  assert(lookupKey(dict, "f") == 5);
  assert(lookupKey(dict, "d") == -1);
  assert(lookupKey(dict, "c") == 3);
  assert(lookupKey(dict, "e") == 4);
  destroyDict(&dict);

  // testing lookup in dict2
  dict = makeDict(keys2, values2, 2);
  assert(lookupKey(dict, "happy") == 10);
  // angry key is stored out of order, your
  // search should have ended when it sees
  // that happy>angry instead of searching 
  // till the end.
  assert(lookupKey(dict, "angry") == -1);
  assert(lookupKey(dict, "other") == -1);
  destroyDict(&dict);
  printf("passed testLookup\n");
}

void testDelete() {
  dictNode *dict = NULL;
  // checking delete from empty dict
  deleteKey(&dict, "abc");
  assert(dict == NULL);
  // dict1
  const char *keys1[] = {"a", "b", "c", "e", "f"};
  int values1[] = {1, 2, 3, 4, 5};
  dict = makeDict(keys1, values1, 5);
  // checking delete from the head
  deleteKey(&dict, "a");
  assertEqualDict(dict, keys1+1, values1+1, 4);
  // checking delete from the tail
  deleteKey(&dict, "f");
  assertEqualDict(dict, keys1+1, values1+1, 3);
  
  // checking delete from the middle
  const char *keys2[] = {"b", "e"};
  int values2[] = {2,4};
  deleteKey(&dict, "c");
  assertEqualDict(dict, keys2, values2, 2);
  destroyDict(&dict);

  // checking that delete stops after search key is smaller than current key
  const char *keys3[] = {"a","c", "b", "f"};
  int values3[] = {1, 2, 3, 5};
  dict = makeDict(keys3, values3, 4);
  deleteKey(&dict, "b");
  assertEqualDict(dict, keys3, values3, 4);
  destroyDict(&dict); 
  printf("passed testDelete\n");
}

void testAdd() {
  dictNode *dict = NULL;
  char local[128] = "b";
  // dict1
  const char *keys1[] = {"a", "b", "c", "e", "f"};
  int values1[] = {1, 2, 3, 4, 5};
  // checking adding b:2 to empty dict
  addKey(&dict, local, 2); 
  assertEqualDict(dict, keys1+1, values1+1, 1); 
  const char *keys2[] = {"a", "b"};
  int values2[] = {0, 2};
  // checking adding a:0 to the head of the dict
  strcpy(local, "a");
  addKey(&dict, local, 0);
  assertEqualDict(dict, keys2, values2, 2); 

  // checking updating a:1 at the head of the dict
  addKey(&dict, "a", 1);
  assertEqualDict(dict, keys1, values1, 2);

  // checking adding f:5 to the end of the dict
  const char *keys3[] = {"a", "b", "f"};
  int values3[] = {1, 2, 5};
  addKey(&dict, "f", 5);
  assertEqualDict(dict, keys3, values3, 3);

  // checking adding e:4, c:30 and c:3
  strcpy(local, "e");
  addKey(&dict, local, 4);
  strcpy(local, "c");
  addKey(&dict, local, 30);
  addKey(&dict, local, 3);
  assertEqualDict(dict, keys1, values1, 5);

  destroyDict(&dict);
  printf("passed testAdd\n");
}
int main() {
  testCount();
  testLookup();
  testDelete();
  testAdd();
  return 0;
} 
