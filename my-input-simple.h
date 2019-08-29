#ifndef MY_INPUT_SIMPLE_H    // This #ifndef envelope is to prevent this
#define MY_INPUT_SIMPLE_H    //     file from being included more than once.

#include <stdlib.h>     // for exit()
#include <string.h>     // for strlen()
#include <iostream>     // for cout, cin, cerr, etc.
#include "lion.h"
#include "mice.h"
using namespace std;


/*
The function prompts the user with a question, continually checks that
a valid (correct type) answer was input, and returns it to the
invoking function.  E.g.:

int age;
prompted_input(age, "Please input your age");
float weight;
prompted_input(weight, "Please input your weight");
*/

// The function template makes this type-free, so the type is only
//     determined when the function is invoked, e.g., in main().
// Making this inline for speed.
template <class T>
inline void prompted_input(T& thing_to_get, const char *user_prompt = 0) {
	bool okay_input = false;

	do {
		if (user_prompt)
			cout << user_prompt << ": ";
		cin >> thing_to_get;

		// Was there a problem with the input, e.g., an int was expected,
		//     but a char was input?
		if (cin.fail()) {
			// cerr is for unbuffered output, in order to output /now/
			cerr << endl << "You blew it--perhaps the wrong input type."
				<< endl;
			// Without this next line, no further input would occur.
			cin.clear();
		}
		else
			okay_input = true;

		// in case of erred input (or not), this will
		//     skip the rest of the line
		const int buffer_size = 80;
		cin.ignore(buffer_size, '\n');

		cout << endl;
	} while (!okay_input);

	return;
}

/*
The function prompts the user with a question, where the answer is a
string (without whitespace).  Then the correct amount of dynamic
allocation is requested and verified.  Finally the string is copied
into place.  E.g.:

char *name = 0;
prompted_input(name, "Please input your name");
char *favorite_color = 0;
prompted_input(favorite_color, "Please input your favorite color");
*/

// NOTE: no whitespace allowed in this string  :-(
inline void prompted_input(char *&string_to_get, const char *user_prompt) {
	// freeing up possible old pointed-to information (does nothing if
	//     string_to_get is already NULL)
	delete[] string_to_get;
	string_to_get = NULL;

	cout << user_prompt << ": ";

	// this should be enough space, and perhaps should be mentioned to
	//     the user
	const int buffer_size = 250;
	char buffer[buffer_size];
	cin >> buffer;

	// this will skip the rest of the line
	cin.ignore(buffer_size, '\n');

	cout << endl;

	const int string_length = strlen(buffer);

	// allocating (and then verifying) the exact, correct amount of
	//     memory)
	string_to_get = new char[string_length + 1];
	if (!string_to_get) {
		cerr << "Free store allocation for string failed.";
		exit(-1);
	}

	// copying the information into place, for the invoking function
	strcpy(string_to_get, buffer);

	return;
}

/*
The function prompts the user with a question, continually checks that
a valid boolean answer [ynYN01] was input, and returns it to the
invoking function.  E.g.:

bool go_on = prompted_yes_or_no("Do you want to continue?");
bool like_computers = prompted_yes_or_no("Is this your favorite class?");
*/

inline bool prompted_yes_or_no(const char *user_prompt) {
	char input_char;

	do {
		cout << "Please answer with: [ynYN01]." << endl << endl <<
			user_prompt << " ";
		cin >> input_char;

		// only interested in one char, so this will
		//     skip the rest of the line
		const int buffer_size = 80;
		cin.ignore(buffer_size, '\n');
	} while ((input_char != 'y') && (input_char != 'n') &&
		(input_char != 'Y') && (input_char != 'N') &&
		(input_char != '1') && (input_char != '0'));

	return (input_char == 'y') || (input_char == 'Y') || (input_char == '1');
}

#endif
