#include <iostream>
#include <stdlib.h>				// for exit
#include <iomanip>				// for setw
#include <time.h>				// for random
#include "allocate-objects.h"	// for dynamically array
#include "my-input-simple.h"	// for user's choices
#include "mice.h"
#include "lion.h"
#include "lions_attacks_mice.h"

int main()
{
	srand((unsigned int) time(NULL));
	lion *lions_pride = 0, new_lion;
	mouse *mice_colony = 0, new_mouse;
	int user_choice;
	cout << "Welcome to Lions VS Mice" << endl << endl;
	prompted_input(total_turn, "How much turns the battles will be?");

	do{
		user_choice = get_menu_option();

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Main menu option
		switch (user_choice){

			// Adding lion to the array lions pride
		case ADD_LION:
			prompted_input(new_lion, "Please enter Lion name");
			add_lion(lions_pride);
			lions_pride[number_of_lions - 1] = new_lion;
			break;

			// Adding mouse to the array mouse colony
		case ADD_MOUSE:
			prompted_input(new_mouse, "Please enter mouse name");
			add_mouse(mice_colony);
			mice_colony[number_of_mice - 1] = new_mouse;
			break;


			// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Battle option
		case BATTLE:
			if (lions_pride == 0 || mice_colony == 0)
				cout << "Please add lions and mice first" << endl;
			else{
				user_choice = get_battle_option();

				switch (user_choice){

					// Custome battle, group against group
				case CUSTOME_BATTLE:{

					int hunting_lion, hunted_mouse,											// argument to save the number of mouse/lion who's user chosen
						lions_counter = 0, mice_counter = 0;										// argument to count the number of mice and lions for battle function
					lion **lions_to_fight = 0;												// array who's point on the lion from the original array
					mouse **mice_to_fight = 0;												// array who's point on the mouse from the original array
					bool more = true;														// "more" - if the user want to add more lion/mouse

					for (int i = 1; i <= number_of_lions; i++){								// for loop, to add the lions who's go to hunt
						if (more == true){
							cout << "Choose the number of lion which go to hunt (0 - "
								<< number_of_lions << ")";
							prompted_input(hunting_lion, "");								// asking for lion to add to the array
							change_size_of_objects(lions_to_fight, i, (i - 1));
							lions_to_fight[(i - 1)] = &lions_pride[hunting_lion];
							more = prompted_yes_or_no("Do you want to add more lions?");	// asking if the user wants more lions
							lions_counter++;
						}
						else break;
					}

					more = true;															// default the argument more to true
					for (int i = 1; i < number_of_mice; i++){								// for loop, to add the mouse who's gonna to be hunted
						if (more == true){
							cout << "Choose the number of mouse which go to be hunted (0 - "
								<< number_of_mice << ")";
							prompted_input(hunted_mouse, "");								// asking for lion to add to the array

							change_size_of_objects(mice_to_fight, i, (i - 1));
							mice_to_fight[(i - 1)] = &mice_colony[hunted_mouse];
							more = prompted_yes_or_no("Do you want to add more mice?");		// asking if the user wants more lions
							mice_counter++;
						}
						else break;
					}
					battle(*lions_to_fight, lions_counter, *mice_to_fight, mice_counter);
				}
					turns(lions_pride, number_of_lions, mice_colony, number_of_mice);
					break;

					// Survival fight, all the lions against all the mice
				case SURVIVAL_FIGHT:
					battle(lions_pride, number_of_lions, mice_colony, number_of_mice);
					turns(lions_pride, number_of_lions, mice_colony, number_of_mice);
					break;

					// Fast forward overs (- running turns)
				case FAST_BATTLE:{
					int turns_forward;
					prompted_input(turns_forward, "enter the number of turns you want run forward");
					if (turns_forward > total_turn - turn){
						cerr << "Sorry, but " << turns_forward <<
							" is not a valid menu option." << endl;
						break;
					}
					for (int i = 0; i < turns_forward; i++){
						battle(lions_pride, number_of_lions, mice_colony, number_of_mice);
						turns(lions_pride, number_of_lions, mice_colony, number_of_mice);
					}
				}
					break;

					// return to main menu
				case BACK:
					break;

				default:
					cerr << "Sorry, but " << user_choice <<
						" is not a valid menu option." << endl;
					break;
				}
			}
				break;


				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Population menu
		case POPULATION:
			user_choice = get_population_option();
			if (turn / total_turn > 0.75)											// if 75% of the turns pass, block this option 
				cout << "The battle is about to end, the lion and mice tired to reproduce" << endl;
			else{
				switch (user_choice){

					// Add one more lion (random name) to lion pride
				case MORE_LION:
					add_lion(lions_pride);
					cout << "The lion " << lions_pride[number_of_lions - 1].name() << " join to lion pride" << endl;
					break;

					// Add 3-4 more mice (random names) to mice colony
				case MORE_MICE:
					int mouse_pups;
					mouse_pups = precents(50) ? 4 : 3;
					for (int i = 0; i < mouse_pups; i++){
						add_mouse(mice_colony);
						cout << "The mouse " << mice_colony[number_of_mice - 1].name() << " join to mice_colony" << endl;
					}
					break;

					// Subtraction the last lion in the array from lion pride
				case SUB_LION:
					if (number_of_lions == 0)
						cout << "You dont have a lions in the pride" << endl;
					else{
						cout << "The lion " << lions_pride[number_of_lions - 1].name() << " leave the lion pride" << endl;
						sub_lion(lions_pride);
					}

					break;

					// Subtraction mice from mice colony
				case SUB_MICE:{
					int plague = (int)((double)number_of_mice * 0.2), random_mouse;
					if (plague == 0)
						cout << "Mice colony is too much smallest to have a plague" << endl;
					else{
						for (int i = 0, j = 1; i < plague; i++){
							random_mouse = rand() % number_of_mice; 									// killing random mouse
							cout << "The mouse " << mice_colony[random_mouse].name()
								<< " become sick and died" << endl;
							mice_colony[random_mouse].eaten();											// change his status to dead

							for (j = 1; j < number_of_mice; j++)										// find the last mice in the array 					
								if (mice_colony[number_of_mice - j].status() == mouse_state::DEAD)		// who's still alive
									break;
								else if (!(j = number_of_mice))											// if not all the mice died
									change_order(mice_colony[random_mouse], mice_colony[number_of_mice - j]);	// put the dead mouse in the end of the array
						}
					}
				}
					break;

					// return to main menu
				case BACK1:
					break;

				default:
					cerr << "Sorry, but " << user_choice <<
						" is not a valid menu option." << endl;
					break;
				}
			}
			break;

			// Print all the lions and mice who's exist
		case EXIST:
			cout << "Lions in the pride: " << endl;
			for (int i = 0; i < number_of_lions; i++)
				cout << lions_pride[i] << ", " << endl;
			cout << endl;

			cout << "Mice in the colony: " << endl;
			for (int i = 0; i < number_of_mice; i++)
				cout << mice_colony[i] << endl;

			break;

			// exit from the game
		case EXIT:
			break;

		default:
			cerr << "Sorry, but " << user_choice <<
				" is not a valid menu option." << endl;
			break;
		}

		/* 3 condition to finish the fight:
			 1. user choose to exit
			 2. the turns finished
			 3. all the mice been dead
		*/
	} while (user_choice != EXIT && total_turn > turn && (mouse::death() != number_of_mice || number_of_mice == 0));

	cout << endl;
	if (mouse::death() <= 0.75 * number_of_mice)
		cout << "The mice succeed to survive the lions attack! YAY!!" << endl;
	else
		cout << "The lion succeed to obliterate all the mice in the area! YAY!" << endl;
	cout << endl;
	
	system ("pause");
	return 0;
}