#ifndef MICE_H
#define MICE_H

#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Mice status} - dead, captrued or travling
enum mouse_state {
	DEAD,
	CAPTURED,
	TRAVELING,
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Mouse status strings}
const char* const mouse_status_strings[]{
	"Died",
		"Capture",
		"Free",
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Random Names for mice}
const char* const names_of_mice[]{
	"Jerry", "Mickey", "Minnie", "Speedy_Gonzales", "Nibbles", "Stuart_little", "Pinky", "Brain",
		"Jaq", "Bernard", "Gus", "Luke", "Sniffles", "Hubie", "Bertie", "Bert", "Mert", "Blabber",
		"Remi", "itchy", "Brisby", "Frisby", "Ages",
};
int sum_of_mice_names = 23;

const char* rand_mouse_name(){
	int random;
	random = rand() % sum_of_mice_names;
	return names_of_mice[random];
}
const string def_mouse_name = "";


/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    Class    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/
class mouse {

protected:

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Mouse's field}
	string _name;
	mouse_state _status;
	int _survive;					// hot much turns the mouse escape from eaten
	static int _death;				// static to count the number of the death mice

public:

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Default constructor} - all of the mice will be traveling in start
	mouse(const string in_name = def_mouse_name) {					
		_status = TRAVELING;
		_survive = 0;
		if (in_name == "")
			_name = rand_mouse_name();
		else
		_name = in_name;
	}


	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Copy constructor}
	mouse(const mouse& rhs){							 
		_name = rhs._name;
		_status = rhs._status;
		_survive = rhs._survive;
	}


	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {View member function}
	const string&	   name   (void) const { return _name; }			
	const mouse_state& status (void) const { return _status; }
	const int&		   survive(void) const { return _survive; }
	static const int&  death  (void)	   { return _death; }

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Modify member function}
	string&		 name   (void) { return _name; }
	mouse_state& status (void) { return _status; }
	int&		 survive(void) { return _survive; }
	static void  death  (const int in_death)		   { _death   = in_death; return; }
	void		 name   (const string in_name)		   { _name    = in_name; return; }
	void		 status (const mouse_state& in_status) { _status  = in_status; return; }
	void		 survive(const int in_survive)		   { _survive = in_survive; return; }


	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Destructor}
	~mouse(void){}


	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Changing status}
	void eaten()   { status() = DEAD; }
	void captured(){ status() = CAPTURED; }
	void release() { status() = TRAVELING; }


	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {operator =}
	mouse& operator = (const mouse& rhs){
		status() = rhs.status();
		name() = rhs.name();
		survive() = rhs.survive();

		return *this;
	}


};

int mouse::_death = 0;			// default static 

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {operator <<} with grammatical spelling
inline ostream& operator <<(ostream& cout, const mouse& rhs){
	if (rhs.survive() > 1)
	 cout << rhs.name() << " is: " << mouse_status_strings[rhs.status()] 
		<< " and succeed to escape from lions " << rhs.survive() << " times!";
	else if (rhs.survive() == 1)
		cout << rhs.name() << " is: " << mouse_status_strings[rhs.status()]
		<< " and succeed to escape from lions once";
	else
		cout << rhs.name() << " is: " << mouse_status_strings[rhs.status()]
		<< " and didn't succeed to escape from lions";

	if (rhs.status() == mouse_state::DEAD)
		return (cout << " before his death");
	else
		return (cout << " until now");
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {operator >>} just from user
inline istream& operator >> (istream& input, mouse& rhs){
	string temp_name;
	input >> temp_name;
	rhs.name(temp_name);
	return input;
}
#endif 
