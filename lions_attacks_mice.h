#ifndef LIONS_ATTACKS_MICE_H
#define LIONS_ATTACKS_MICE_H

#include <iostream>
#include <stdlib.h>
#include "mice.h"
#include "lion.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ this function give me random number between 0-100
bool precents(const int in_precent){	
	int success;
	if (in_precent >= 0 && in_precent <= 100){							// check if the input is between 0-100
		success = (rand() % 100);										// precents 0 to 99
		if (success < in_precent)										// checking if the random number is in the range of the precents
			return true;
		else
			return false;			
	}
	else
		cerr << "Error! try again" << endl;
	exit(0);
}


/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    Lions    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  Dynmically @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    Array    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/

int number_of_lions = 0;				// global argument for count the number of lions in lion's pride
int number_of_mice = 0;					// global argument for count the number of mice in mice's colonoy

//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Add lion to the original array
void add_lion(lion*& lions){			// Array of lions in lion's pride
	number_of_lions++;					// Count the lions in lion's pride
	change_size_of_objects(lions, number_of_lions, number_of_lions - 1);
}

//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Subtruct lion from the original array
void sub_lion(lion*& lions){			// Array of lions in lion's pride
	number_of_lions--;					// Count the lions in lion's pride
	change_size_of_objects(lions, number_of_lions, number_of_lions + 1);
}

//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Add mouse to the original array
void add_mouse(mouse*& mice){			// Array of mice in mice's colonoy
	number_of_mice++;					// Count the mice in mice's colonoy
	change_size_of_objects(mice, number_of_mice, number_of_mice - 1);
}

//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Subtruct mouse from the original array
void sub_mouse(mouse*& mice){			// Array of mice in mice's colonoy
	number_of_mice--;					// Count the mice in mice's colony
	change_size_of_objects(mice, number_of_mice, number_of_mice + 1);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Change the order in the array of lions pride or mice colony
template <class T>
void change_order(T& first, T& second){
	T temp;
	temp = first;
	first = second;
	second = first;
}

/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		       @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	 Battles   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		       @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/

int turn = 0, total_turn = 0;												// Global argument, to count our turn in the game

bool eat_supplies(lion& check_lion, mouse*& mice_colony, const int& i){		// Check if the lion captured mouse, and eat them
	if (check_lion.captured_mice() >= 1){
		check_lion.captured_mice()--;
		check_lion.taste()++;
		check_lion.ate_last_turn() = true;
		for (int j = 0; j < number_of_mice; j++)							// searching after a mouse who captured by a lion
			if (mice_colony[j].status() == CAPTURED){
			mice_colony[j].eaten();
			cout << "The mouse " << mice_colony[j].name()
				<< " have been eaten by " << check_lion.name() << endl;
			break;
			}
		return true;
	}
	return false;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ this function doing completion to every turn
void turns(lion* pride, int size_of_lions, mouse* colony, int size_of_mice){
	for (int i = 0; i < size_of_lions; i++){								// changing status of the lions
		if (pride[i].taste() < (float)(turn / 5) &&							// checking if the lion is hungry, and if he ate last turn
			!(pride[i].ate_last_turn()))
			pride[i].hungry();

		else if (pride[i].taste() >= (float)(turn / 5) &&					// checking if the lion is satiated, and if he ate last turn
			!(pride[i].ate_last_turn())){
			if (eat_supplies(pride[i], colony, size_of_mice))				// checking if the lion have captured mouse to eat
				pride[i].sleeping();
			else
				pride[i].satiated();
		}
		else pride[i].sleeping();											// set lion is sleeping
	}

	for (int i = 0; i < size_of_mice; i++)									// mice try to escape from lion
		if (colony[i].status() == mouse_state::CAPTURED){					// 10% precents to the mouse the escape from lion captivity
			bool try_to_escape = precents(10);
			if (try_to_escape == true){
				colony[i].release();										// release mouse
				colony[i].survive()++;										// raising his experience
				mouse::death(mouse::death() - 1);							// count the dead and captured mouse
				for (int j = 0; j < size_of_lions; j++)						// searching after a lion to release from him the mouse
					if (pride[j].captured_mice() >= 1){
					pride[j].captured_mice()--;
					cout << "The mouse " << colony[i].name()
						<< " success to escape from " << pride[j].name() << endl;
					break;
					}
			}
		}
	
	// printing summary of this turn
	cout << endl << "Status of the lions in the pride:" << endl;

	for (int i = 0; i < size_of_lions; i++){								// printing the information on the lions
		cout << pride[i].name() << " is " <<
			lion_status_strings[pride[i].status()] << " " << pride[i].name()
			<< " ate " << pride[i].taste() << " and capture " 
			<< pride[i].captured_mice() << endl;
	}
	cout << endl << "Status of the mice in the colony:" << endl;
	for (int i = 0; i < size_of_mice; i++){									// printing the information on the mice
		cout << colony[i].name() << " is " <<
			mouse_status_strings[colony[i].status()] << " and have succeed to escape from lions " <<
			colony[i].survive() << " times!" << endl;

	}
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ function to determind if the lion eat the mouse or capture him
void catch_mouse(lion& the_lion, mouse& the_mouse){
	mouse::death(mouse::death() + 1);									// count the dead and captured mouse
	if (the_lion.taste() <= (float)(turn / 5)){								// if the lion hungry (didnt eat mouse for five turn in average)
		the_mouse.eaten();													// change status of mice o eaten
		the_lion.taste()++;													// add to lion 1 more "kill"
		the_lion.ate_last_turn() = true;
		cout << "The lion " << the_lion.name()
			<< " tack his claws in " << the_mouse.name()
			<< " and it ate his fill" << endl;
	}
	else{																	// if the lion is satiated
		the_mouse.captured();
		the_lion.captured_mice()++;
		cout << "The lion " << the_lion.name()
			<< " shocked " << the_mouse.name()
			<< " and took him to captivity" << endl;
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ battle function - every lion try to eat 3 mice
void battle(lion* lions, const int& size_of_lions, 
			mouse* mice, const int& size_of_mice){
	int count = 0;																			// argument to prevent ifinite loop
	turn++;
	cout << endl << "Turn number: " << turn << endl << endl;
	int random_mouse;																		// argument for random mouse to be hunt
	bool success_to_hunt;																	// argument to set if the lion success to hunt the mouse
	for (int i = 0; i < size_of_lions; i++){												// 'for' loop, run on all the lions in the array
		if (lions[i].status() == lion_state(SLEEPING)){										// checking if the lion is sleeping
			lions[i].hungry();
			lions[i].ate_last_turn() = false;
		}
		else{
			for (int j = 0; j < 3; j++){													// 'for' loop, run on 3 random mice in the array
				random_mouse = rand() % size_of_mice;										// choose the number to be attacked
				if (mice[random_mouse].status() == mouse_state(TRAVELING)){					// checking if the mouse is dead or sleeping
					success_to_hunt = precents(40 - mice[random_mouse].survive());			// 50% to be caught reduction of his experience
					if (success_to_hunt)													// in case the lion catch the mouse
						catch_mouse(lions[i], mice[random_mouse]);
					else{																	// if the mouse succeed to escape
						mice[random_mouse].survive() += 1;									// adding +1 to his survival
						cout << "The mouse " << mice[random_mouse].name()
							<< " succeeded to escape from " << lions[i].name()
							<< " and his experience growth" << endl;
					}
				}
				else
					j--;
				count++;
				if (count > 10) break;
			}
		}		
	}
}

/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    Menus    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/

const int spaces = 10;							// for order the menus option

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Menu option}
enum menu_option{
	ADD_LION,									// 0) ADD LION TO THE LION PRIDE
	ADD_MOUSE,									// 1) ADD MOUSE OT THE MICE'S COLONY
	BATTLE,										// 2) SOME KIND OF OPTION OF BATTLE
	POPULATION,									// 3) SOME KIND OF OPTION OF ANNIHILATION AND CREATION OF MICE AND LIONS
	EXIST,										// 4) Show all the lions and mice who's exist
	EXIT,										// 6) EXIT FROM THE GAME

	FIRST_MENU_OPTION = ADD_LION,				// FIRST AND LAST OF MY MENU OPTION
	LAST_MENU_OPTION = EXIT,
};

const char* const menu_option_strings[]{
	"Add lion to the lion's pride",
		"Add mouse to the mice's colony",
		"Battle!!!",
		"Creation and Annihilation",
		"Show all",
		"Exit, ant let the lions to win",
};

menu_option get_menu_option(void){							// this function will run our menu option
	menu_option menu_option_chosen;
	menu_option_chosen = FIRST_MENU_OPTION;


	cout << endl << "Please note the following menu options:" << endl << endl;


	for (; menu_option_chosen <= LAST_MENU_OPTION;											// The user will see:
		menu_option_chosen = static_cast <menu_option> ((int)menu_option_chosen + 1))		//
		cout << setw(spaces) << " " << menu_option_chosen << " -- "							//           0 -- Add lion to the lion's pride
		<< menu_option_strings[menu_option_chosen] << endl;									//           1 -- Add mouse to the mice's colony
																							// etc.
	cout << endl;

	int menu_option_chosen_as_int;
	prompted_input(menu_option_chosen_as_int, "Please choose a menu option");				// taking user's choice			
	return static_cast<menu_option>(menu_option_chosen_as_int);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {Battle option}
enum battle_option{
	CUSTOME_BATTLE,								// 0) CUSTOME BATTLE FOR CHOICE OF USER
	SURVIVAL_FIGHT,								// 1) FIGHT ALL AGIANST ALL
	FAST_BATTLE,								// 2) RUNNING TURNS OF SURVIVAL FIGHT
	BACK,										// 3) RETURN TO MAIN MENU

	FIRST_BATTLE_OPTION = CUSTOME_BATTLE,		// FIRST AND LAST OF MY BATTLE OPTION
	LAST_BATTLE_OPTION = BACK,
};

const char* const battle_option_strings[]{
	"Custom battle",
		"Survival fight, all against all",
		"Fast forward overs",
		"Back",
};

battle_option get_battle_option(void){						// this function will run our battle's menu option

	battle_option battle_option_chosen = FIRST_BATTLE_OPTION;

	cout << endl << "Please note the following battle's menu options:" << endl << endl;


	for (; battle_option_chosen <= LAST_BATTLE_OPTION;											// The user will see:
		battle_option_chosen = static_cast <battle_option> ((int)battle_option_chosen + 1))		//
		cout << setw(spaces) << " " << battle_option_chosen << " -- "							//           0 -- Add lion to the lion's pride
		<< battle_option_strings[battle_option_chosen] << endl;									//           1 -- Add mouse to the mice's colony
	// etc.
	cout << endl;

	int battle_option_chosen_as_int;
	prompted_input(battle_option_chosen_as_int, "Please choose a battle's menu option");		// taking user's choice			
	return static_cast<battle_option>(battle_option_chosen_as_int);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {population option}
enum population_option{
	MORE_LION,									// 0) LIONESS GIVE BIRTH (ADD 1 MORE LION)
	MORE_MICE,									// 1) MOUSE GIVE BIRTH (ADD 3-4 MORE MICE)
	SUB_LION,									// 2) KILL A LION
	SUB_MICE,									// 3) TO KILL A MICE (RANDOM)
	BACK1,										// 4) BACK

	FIRST_POPULATION_OPTION = MORE_LION,		// FIRST AND LAST OF MY POPULATION OPTION
	LAST_POPULATION_OPTION = BACK1,
};

const char* const population_option_strings[]{
	"Lioness give brith",
		"Mouse give birth",
		"Mouse stuck in lion's throat (kill a lion)",
		"Plague among the mice (kill 20% mice)",
		"Back",
};

population_option get_population_option(void){				// this function will run our population's menu option

	population_option population_option_chosen = FIRST_POPULATION_OPTION;

	cout << endl << "Please note the following population's menu options:" << endl << endl;


	for (; population_option_chosen <= LAST_POPULATION_OPTION;													// The user will see:
		population_option_chosen = static_cast <population_option> ((int)population_option_chosen + 1))	//
		cout << setw(spaces) << " " << population_option_chosen << " -- "								//           0 -- Add lion to the lion's pride
		<< population_option_strings[population_option_chosen] << endl;									//           1 -- Add mouse to the mice's colony
	// etc.
	cout << endl;

	int population_option_chosen_as_int;
	prompted_input(population_option_chosen_as_int, "Please choose a population's menu option");		// taking user's choice			
	return static_cast<population_option>(population_option_chosen_as_int);
}

#endif