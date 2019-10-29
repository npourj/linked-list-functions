/*
 * author: Yanling Wang
 * email: yuw17@psu.edu
 * dict.h for CMPSC 311 Fall 2019
 * last updated: 10/15/2019
 */
#ifndef DICT_H
#define DICT_H
// dictionary node contains string key and int value
// valid value is a non-negative value since we use -1
// to indicate the key is not in the dictionary.
// A dictionary is a linked list of these nodes
// where the nodes are sorted by its key in alphabetical
// order
typedef struct dictNode {
  char *key;
  int value;
  struct dictNode *next;
} dictNode;

// print out the key/value pairs in a dictionary
void displayDict(const dictNode *dict); 

// delete all memory allocated for dictionary, which
// not only includes each nodes, but also the memory
// allocated to store each key. So when you are creating
// a node, you must make sure that the key points to
// newly allocated memory just for the use of this node.
void destroyDict(dictNode **dictPtr);


// use free to clean up memory pointed to by current,
// including freeing the memory for key.
void freeNode(dictNode *current);

// create a dict based on two arrays of keys and values.
dictNode *makeDict(const char *keys[], int values[], int length);

// assert a dict has nodes exactly the same as a dict represented by
// two arrays (keys, values) of given length
void assertEqualDict(const dictNode *dict, const char *keys[],
    int values[], int length);

// given a key, look up its corresponding value in the
// dictionary, returns -1 if the value is not in the dictionary.
// your search for key should end when the key in the next node
// is bigger than the lookup key or you reached the end of the
// list.
int lookupKey(const dictNode *dict, const char *key);

// given a key/value pair, first lookup the key in the dictionary,
// if it is already there, update the dictionary with the new
// value; if it is not in the dictionary, insert a new node into
// the dictionary, still make sure that the key is in alphabetical
// order.
// IMPORTANT: When creating a new node, make sure you dynamically
// allocate memory to store a copy of the key in the memory. You
// may use strdup function. DO NOT STORE the input key from the 
// argument directly into the node. There is no guarantee that key
// pointer's value will stay the same. 
// YOU MUST KEEP THE ALPHABETICAL ORDER OF THE KEY in the dictionary.
void addKey(dictNode **dictPtr, const char *key, int value);

// count number of keys in a dict.
int countKeys(const dictNode *dict);

// delete the node in a dict with given key, return the value of
// the deleted node if it was found, return -1 if it wasn't found.
int deleteKey(dictNode **dictPtr, const char *key);
#endif //DICT_H
