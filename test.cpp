#include "PrimitiveMap.hpp"
#include <iostream>
#include <string>

int main(int argc, char ** argv) {

  int mapSize = 11;
  PrimitiveMap<int> m(mapSize);
  cout << "Created PrimitiveMap with size " << mapSize << endl;

  string strArr[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" };
  int numArr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
  int arrLength = 12;

  for (int i = 0; i < arrLength; i++) {
    if (m.set(strArr[i], numArr[i]) == true) {
      cout << "Successfully stored key/value: " << strArr[i] << "/" <<  numArr[i] << endl;
    }
    else {
      cout << "Unable to store key/value: " << strArr[i] << "/" << numArr[i] << endl;
    }
  }

  m.printTable();

  return 1;

}


