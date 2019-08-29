#ifndef ALLOCATE_OBJECTS_H
#define ALLOCATE_OBJECTS_H

#include <stdlib.h>     // for exit()
#include <iostream>
#include "lion.h"
#include "mice.h"
using namespace std;


/*
This function template is for dynamically allocating (with verification)
an array of objects T.

The template aspect will help later on, for allocating an array of
subclass objects, polymorphically.  (Huh??  ;-) )

Note: cannot remove second argument, and have this /return/ the pointer
value, since the template argument T /must/ be in the argument list.

E.g.:

unsigned int number_of_objects = 10;
long long *objects = 0;

allocate_objects(number_of_objects, objects);

*/

// number_of_objects is a const reference, for speed.
// objects is a /references/ to a pointer, as its value
// is changed here in the function, and must be reflected in the
// invoking function as well.
template <class T>
inline void allocate_objects(const unsigned int &number_of_objects,
	T *&objects) {
	delete[] objects;

	objects = 0;

	objects = new T[number_of_objects];

	if (!objects) {
		cerr << "Free store allocation for object array failed.";
		exit(-1);
	}
	else    // if okay, let's zero out the array
		for (int unsigned object = 0; object < number_of_objects; object++)
			objects[object] = (T)0;    // note the typecast

	return;
}




// this function copy array to another array
template <class T>
inline void change_size_of_objects(T *&objects, unsigned const int new_size, unsigned const int old_size) {

	int unsigned object, copy;

	// check if need to add or subtract from the array
	if (new_size > old_size) copy = old_size; else copy = new_size;

	// new dynamic array 
	T* temp_objects = new T[copy];
	if (!temp_objects) {											// check if the dynamic array worked well
		cerr << "Free store allocation for object array failed.";
		exit(-1);
	}
	else															// if the allocate worked well, copy the old array to the temp array
		for (object = 0; object < copy; object++)
			temp_objects[object] = objects[object];   

	// making our array to a new dynamic array, bigger or smaller
	delete[] objects;
	objects = 0;

	objects = new T[new_size];
	if (!objects) {
		cerr << "Free store allocation for object array failed.";
		exit(-1);
	}
	else if (new_size == 0)
		objects = 0;
	else
		for (object = 0; object < copy; object++)					// copy the temp array to our new array
		objects[object] = temp_objects[object];
	return;
}

#endif
