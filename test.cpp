/*
 * Author: Christopher Converse
 *         cconversee@gmail.com
 *
 * Tester method for PrimitiveMap.hpp. Methods tested include set, get, 
 * deleteKey, and load.
 *
 */

#include "PrimitiveMap.hpp"
#include <iostream>

/* 
 * Name: main
 * Description: Tests PrimitiveMap.hpp in several different ways.
 * Insertions, retrievals, and deletions are tested. Edge cases tested
 * also include reinsertion of the same key but with a different value,
 * retrieval of keys not inside the hashmap, and deletion of keys
 * not inside the hashmap.
 *
 */
int main(int argc, char ** argv) {

  int mapSize = 11; /* Size of map */
  PrimitiveMap<int> m(mapSize);
  cout << ">>>>> Created PrimitiveMap with size " << mapSize << "<<<<<" << endl;

  /* Key/value pairs */
  string strArr[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" };
  int numArr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
  int arrLength = 12;

  cout << ">>>>> Testing set method <<<<<" << endl;

  /* Insertion of key/values */
  for (int i = 0; i < arrLength; i++) {
    if (m.set(strArr[i], numArr[i]) == true) {
      cout << "Successfully stored key/value: " << strArr[i] << "/" <<  
        numArr[i] << endl;
    }
    else {
      cout << "Unable to store key/value: " << strArr[i] << "/" << numArr[i] << 
        ", hashmap full!" << endl;
    }
  }

  /* Load factor */
  cout << "Load factor is " << m.load() << endl;

  cout << ">>>>> Testing get method <<<<<" << endl;

  /* Call get method to confirm insertions */
  for (int i = 0; i < mapSize; i++) {
    cout << "Value with " << strArr[i] << " is: " << m.get( strArr[i] ) << endl;
  }

  cout << ">>>>> Testing deleteKey method <<<<< " << endl;

  /* Remove 2 keys */
  for (int i = 0; i < 3; i += 2) {
    int removedNum = m.deleteKey(strArr[i]);
    cout << "Removed key with " << strArr[i] << " is " << removedNum << endl;

    if (removedNum == numArr[i]) {
      cout << "Correct deletion" << endl;
    }
    else {
      cout << "Incorrect deletion" << endl;
    }
  }

  /* Recall get method to ensure linear probing is not broken from removal */
  for (int i = 0; i < mapSize; i++) {
    cout << "Value with " << strArr[i] << " is: " << m.get( strArr[i] ) << endl;
  }

  /* Load factor */
  cout << "Load factor is " << m.load() << endl;

  cout << ">>>> Testing deletion of values not present inside hashmap <<<<<" << endl;
  if (m.deleteKey(strArr[0]) == NULL) {
      cout << "Tried deleting " << strArr[0] << ", not found" << endl;
  }

  cout << ">>>>> Testing reinsertion of values already present <<<<<" << endl;
  m.set( strArr[1], numArr[11]);
  cout << strArr[1] << " should now be paired with " << numArr[11] << endl;

  for (int i = 0; i < mapSize; i++) {
    cout << "Value with " << strArr[i] << " is: " << m.get( strArr[i] ) << endl;
  }
  
  return 1;

}


