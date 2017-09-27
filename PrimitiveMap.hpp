
/* Author: Christopher Converse
 *         cconversee@gmail.com
 * 
 * Header file for a fixed-size hash map associating string 
 * keys with arbitrary data object references, including method definitions
 *
 */

#ifndef PRIMITIVEMAP_H
#define PRIMITIVEMAP_H

#include <string>

using namespace std;

#include <iostream>

#define EMPTY_STRING ""

template <class T>
class PrimitiveMap {
  public:

    /* 
     * Function name: Constructor
     * Description: Constructor method for a PrimitiveMap object
     * Parameters: size - The maximum size of the container
     *
     */
    PrimitiveMap(int size);

    /* 
     * Function name: Destructor 
     * Description: Destructor method for a PrimitiveMap object
     *
     */
    ~PrimitiveMap(void);

    /*
     * Function Name: set
     * Description: Store given key/value pair into the hash map. 
     * Parameters: key - Key to be associated with a T value
     *             value - What to store associated with key
     * Return: Boolean indicating success/failure of insertion.
     * Failures only happen in the result of a full hashmap
     *
     */
    const bool set(string &key, T &value);

    /*
     * Function Name: get
     * Description: Get a T value associated with a key in the hashmap
     * Parameters: key - What to find the associated value with
     * Return: T value associated, or NULL if not in the hashmap
     *
     */
    T get(string &key);

    /* 
     * Function Name: deleteKey (delete method renamed)
     * Description: Delete an associated value with a key
     * Parameters: key - Value to be associated with to search for
     * Return: T value deleted, or NULL if not inside hash map
     *
     */
    T deleteKey(string &key);

    /*
     * Function Name: load
     * Description: Get the load factor of the hash map
     * Return: Load factor of hashmap
     *
     */
    const float load();

    void printTable();

  private:
    typedef pair <string, T> TPair; // Define pair that holds key & T value
    TPair * map; // Array to store TPairs which holds they key & T value
    bool spaceDeleted[]; // Keep track of which elements in map are deleted
    unsigned int capacity; // Size of the hash map
    unsigned int itemsStored; // Number of items stored currently

    /*
     * Function Name: hash
     * Description: Get the hash value of a string 
     *
     * A hashing function taken from 
     * www.eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx
     * I DID NOT MAKE IT
     *
     * Parameters: key - String to hash
     * Return: Hashing value
     *
     */
    const int hash(string &key);
};

template <class T> 
PrimitiveMap<T>::PrimitiveMap(int size) : itemsStored(0), capacity(0) {

  /* Error check of a negative or zero size  */
  if (size <= 0) {
    size = 1;
  }

  capacity = size;
  map = new TPair[capacity];

  for (int i = 0; i < capacity; i++) {
    spaceDeleted[i] = false;
  }
  capacity = size;
}

template <class T>
PrimitiveMap<T>::~PrimitiveMap(void) { 
  delete []map;
}

template <class T>
const bool PrimitiveMap<T>::set(string &key, T &value) {

  /* Check if hashmap is full */ 
  if (itemsStored > capacity) {
    return false;
  }

  int hashVal = hash(key);

  /* Look for a space to place new key & value.
   * If key is found to be already be inside the hashmap,
   * the old value will be replaced with the new one. */
  while (map[hashVal].first != EMPTY_STRING) {

    if (map[hashVal].first == key) { 
      break; 
    }
    else if (hashVal == capacity - 1) { 
      hashVal = 0; 
    }
    else { 
      hashVal++; 
    }
  }

  map[hashVal].first = key;
  map[hashVal].second = value;
  itemsStored = itemsStored + 1;
  //cout << "itemsStored is " << itemsStored << endl;
  spaceDeleted[hashVal] = false;
  return true;
}

template <class T>
T PrimitiveMap<T>::get(string &key) { 

  int counter = 0; /* Keep track of whether entire table is searched */
  int hashVal = hash(key); /* Get hash value of key */
  T returnVal = NULL;

  /* Key not found */
  if (map[hashVal].first == EMPTY_STRING && spaceDeleted[hashVal] == false) {
    return returnVal;
  }

  while ( (map[hashVal].first != EMPTY_STRING) || spaceDeleted[hashVal] == true) {

    /* Match found */
    if (map[hashVal].first == key) {
      returnVal = map[hashVal].second;
      break;
    }

    /* Increment hashVal to next available spot */
    if (hashVal == capacity - 1) {
      hashVal = 0;
    }
    else {
      hashVal++;
    }

    /* Keep track if entire table searched; if yes, key not found */
    if (counter == capacity) {
      break;
    }
    else {
      counter++;
    }
  }

  return returnVal;
}

template <class T>
T PrimitiveMap<T>::deleteKey(string &key){ 

  int counter = 0; /* Keep track of whether entire table is searched */
  int hashVal = hash(key); /* Get hash value of key */
  T returnVal = NULL; /* Return value; either T if key present or NULL */

  /* Key not found */
  if (map[hashVal].first == EMPTY_STRING && spaceDeleted[hashVal] == false) { 
    return returnVal; 
  }

  /* Continue searching for the key while a match is not found. Also checks 
   * for previously deleted items since search is done through linear probing.
   */
  while ((map[hashVal].first != EMPTY_STRING) || spaceDeleted[hashVal] == true) {

    /* Match found */
    if (map[hashVal].first == key) {
      returnVal = map[hashVal].second;
      map[hashVal].first = EMPTY_STRING;
      spaceDeleted[hashVal] = true;
      itemsStored--;
      break;
    }

    /* Increment hashVal to the next available spot */
    if (hashVal == capacity - 1) { 
      hashVal = 0; 
    }
    else { 
      hashVal++; 
    }

    /* Keep track if entire table searched; if yes, key not found */
    if (counter == capacity) { 
      break; 
    }
    else { 
      counter++; 
    }
  }

  return returnVal;
}

template <class T>
const float PrimitiveMap<T>::load() { 
  return itemsStored / capacity;
}

template <class T>
const int PrimitiveMap<T>::hash(string &key) {

  string p = key;
  unsigned h = 0;
  int i;

  for (i = 0; i < key.length(); i++) {
    h += p[i];
    h ^= (h << 10);
    h += (h >> 6);
  }

  h += (h << 3);
  h ^= (h >> 11);
  h += (h << 15);

  return h % capacity;

}

template <class T>
void PrimitiveMap<T>::printTable() {
  for (int i = 0; i < capacity; i++) {
    cout << "HERE" << endl;
    cout << "Key/Value stored at " << i << ": " << map[i].first << "/" << map[i].second << endl;
  }
}

#endif // PRIMITIVEMAP_H
