#ifndef LION_H
#define LION_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include "my-input-simple.h"
using namespace std;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Lion status}
	enum lion_state{
		SLEEPING,
		HUNTING,
		SATIATED,
	};

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Lion status strings}
	const char* const lion_status_strings[]{
		"Sleeping",
			"Hunting",
			"Satiated",
	};

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Random Names for lions}
	const char* const names_of_lions[]{
		"Simba", "Scar", "Mofasa", "Frasier", "Samson", "Ryan", "Richard", "Leo", "Alex", "Lambert",
			"Aslan", "John", "Fahri", "Zuri", "Baruti", "Lusaka", "Arthur",
	};
	int sum_of_lions_names = 17;

	const char* rand_lion_name(){
		int random;
		random = rand() % sum_of_lions_names;
		return names_of_lions[random];
	}

	const string def_lion_name = "";


	/*
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    Class    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	*/
class lion{

protected:


	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Lion field}
	string _name;
	lion_state _status;
	int _taste;					// how much mice the lion ate
	int _captured_mice;			// how much mice the lion captured and didnt ate yet
	bool _ate_last_turn;		// to check if the lion ate last turn



public:

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Default constructor} the lion's status is "satiated" in start
	lion(const string& in_name = def_lion_name){
		_status = HUNTING;
		_taste = 0;
		_captured_mice = 0;
		_ate_last_turn = false;

		if (in_name == "")
			_name = rand_lion_name();
		else
			_name = in_name;
	}


	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Copy constructor}
	lion(const lion& rhs){
		_name = rhs._name;
		_status = rhs._status;	
		_taste = rhs._taste;
		_captured_mice = rhs._captured_mice;
		_ate_last_turn = rhs._ate_last_turn;
	}


	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {View member function}
	const string&	   name		    (void) const{ return _name; }
	const lion_state&  status	    (void) const{ return _status; }
	const int&		   taste		(void) const{ return _taste; }
	const int&		   captured_mice(void) const{ return _captured_mice; }
	const bool&		   ate_last_turn(void) const{ return _ate_last_turn; }

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Modify member function}
	string& name	   (void)  { return _name; }
	lion_state& status (void)  { return _status; }
	int& taste		   (void)  { return _taste; }
	int& captured_mice (void)  { return _captured_mice; }
	bool& ate_last_turn(void)  { return _ate_last_turn; }

	void name		  (const string& in_name)			   { _name = in_name;					return; }
	void status		  (const lion_state& in_status)		   { _status = in_status;			    return; }
	void taste		  (const int& in_taste)				   { _taste = in_taste;				    return; }
	void captured_mice(const int& in_captured_mice)		   { _captured_mice = in_captured_mice; return; }
	void ate_last_turn(const bool& in_a_l_t)				   { _ate_last_turn = in_a_l_t;			return; }

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Destructor}
	~lion(void) {}


	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Changing status}
	void hungry()   { status() = HUNTING; }
	void sleeping() { status() = SLEEPING; }
	void satiated() { status() = SATIATED; }


	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {operator =}
	lion& operator = (const lion& rhs){
		status()		= rhs.status();
		name()			= rhs.name();
		taste()			= rhs.taste();
		captured_mice() = rhs.captured_mice();
		ate_last_turn() = rhs.ate_last_turn();
		return *this;
	}

};
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {operator <<} with grammatical spelling
inline ostream& operator<< (ostream& output, const lion& rhs){
	if (rhs.taste() > 1){
		(output << rhs.name() << " is: " << lion_status_strings[rhs.status()]
			    << " and already succeed to eat " << rhs.taste() << " mice");
		if (rhs.captured_mice() == 1)													// if the lion have POW
			return (cout << " and captured " << rhs.captured_mice() << " mouse");
		else if (rhs.captured_mice() > 1)
			return (cout << " and captured " << rhs.captured_mice() << " mice");
		else return (cout << "!");
	}
	else if (rhs.taste() == 1)
		return (output << rhs.name() << " is: " << lion_status_strings[rhs.status()]
					   << " and already succeed to eat " << rhs.taste() << " mouse!");
	else
		return (output << rhs.name() << " is: " << lion_status_strings[rhs.status()]
					   << " and didn't succeed to eat mice at all");
}

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {operator >>} just from user
inline istream& operator >> (istream& input, lion& rhs){
	string temp_name;
	input >> temp_name;

	rhs.name(temp_name);
	return input;
}


#endif