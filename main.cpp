#include <iostream>
#include "Vector.h"
using namespace std;



void printVector(Vector& other){
	  for (size_t i = 0; i < other.size(); i++) {
		    cout << other[i] << " ";
	  }
	  cout << "\n\n";
}

int main() {
    double* vec = new double[2];
    vec[0] = 5;
    vec[1] = 81;
  
    Vector vec1;
    vec1.pushBack(7);
    vec1.pushFront(10);
    printVector(vec1);
    
    vec1.insert(12, 1);
    printVector(vec1);
  
    vec1.insert(vec, 2, 3);
    printVector(vec1);
    
    for (int i = 0; i < 10; i++) {
        vec1.pushBack(i + 1231);
    }
    printVector(vec1);
    
    vec1.popBack();
    printVector(vec1);
  
    vec1.popFront();
    printVector(vec1);
     
    cout << "Capasity: " << vec1.capacity() << "\n";
    cout << "Size: " << vec1.size() << "\n";
    cout << "LoadFactor: " << vec1.loadFactor() << "\n";
    cout << (vec1.find(1234) == -1 ? "Index 123 not found" : "Index 123 found") << "\n";
    cout << (vec1.find(-12) == -1 ? "Index -12 not found" : "Index -12 found") << "\n";
   
    delete[] vec;

	  return 0;
}
