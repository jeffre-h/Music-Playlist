#include <iostream>
#include <string>
#include "PlayList.h"
#include "Song.h"

using std::cout;
using std::cin;
using std::endl;
using std::exception;
using std::out_of_range;

/*
	Time Complexity Analysis
	--------------
	***for methods 1,2,4-9 let n be the size of the playlist

	PlayList Methods:
	1. Default Constructor - O(1)
		-set head & length (constant time operations)
		-no worst case running time
	2. Destructor - O(n) 
		-has to loop through the entire playlist from start to end
		-no worst case running time
	3. Copy Constructor - O(n) 
		-n is the length of pl (parameter). Loops through pl to deep copy to the playlist.
		-no worst case running time
	4. Overload Assignment Operator - O(n)
		-let m be the length of pl (parameter). loops through playlist to deallocate and pl to deep copy O(n+m).
        -O(n+m) linear time
		-no worst case running time
	5. Insert - O(n)
		-let k be the # of positions after the insert position
		-loops through the playlist n-k times. O(n-k) ignoring constants -> O(n)
		-worst case running time O(n+1) -> O(n)
			-this occurs when the position is equal to the length of the playlist (iteration from idx 0 to length)
			-position is after the last node, signifiying an insert to the end of the playlist
	6. Remove - O(n)
		-let k be the # of position after the remove position
		-loops through the playlist n-k times. O(n-k) ignoring constants -> O(n)
		-worst case running time O(n)
			-this occurs when the position is eqaul to the legnth of the playlist - 1 (loops to last song in playlist)
	7. Get - O(n)
		-let k be the # of positions after the get position
		-loops through the playlist n-k times. O(n-k) ignoring constants -> O(n)
		-worst case running time O(n)
			-this occurs when the position is equal to the length of the playlist - 1 (loops to last song in playlist)
	8. Swap - O(n)
		-loops through the playlist once to search for pos1 and pos2
		-a lot of constant time operations, but are negligible when caluclation big-O
		-no worst case since the function loops through the entire playlist regardless if pos1 and pos2 are found earlier or later
	9. Size - O(1)
		-retrieve length from playlist (1 constant time operation)
		-no worst case running time

	Main Function Commands:
	let n be the size of the playlist created in the main

	1. Enter a song - O(n)
		-let k be the # of positions after the enter position
		-calls insert function -> loops through the playlist n-k times. O(n-k) ignoring constants -> O(n)
		-depends on user's input (while loops used to validate user input)
		-worst case running time O(n+1) -> O(n) (assuming user provides valid input)
			-this occurs when the position is equal to the length of the playlist (iterate from idx 0 to length)
			-position is after the last node, signifiying an insert to the end of the playlist
	2. Remove a song - O(n)
		-let k be the # of position after the remove position
		-calls remove function -> loops through the playlist n-k times. O(n-k) ignoring constants -> O(n)
        -depends on user's input (while loop used to validate user input)
		-worst case running time O(n) (assuming user provides valiod input)
			-this occurs when the position is eqaul to the legnth of the playlist - 1 (loops to last song in playlist)
	3. Swap 2 songs -  O(n)
        -calls the swap function
            -loops through the playlist once to search for pos1 and pos2
            -a lot of constant time operations, but are negligible when caluclation big-O
		-depends on user's input (while loops used to validate user input)
        -no worst case, as the swap function will always traverse the entire playlist

	4. Print all the songs - O(n^2)
		-loops through the playlist once and in each iteration calls the get (O(n)) function 3 times (nested for loop)

*/


int main() {
	cout << "Menu:" << endl;
	cout << "1 - Enter a song in the play list at a given position" << endl;
	cout << "2 - Remove a song from the play list at a given position" << endl;
	cout << "3 - Swap two songs in the play list" << endl;
	cout << "4 - Print all the songs in the play list" << endl;
	cout << "5 - Quit" << endl;

	bool cont = true; // cont is set to false, when user wants to quit program
	int input; // user input from the menu
	PlayList* pl = new PlayList(); // allocate space for playlist, deallocated at end of program
	unsigned int size = pl->size(); //initialized as 0, keeps track of the size of the playlist throughout the program


	// user-interfaced does not use 0-based indices for readibility
	// before using functions, parameters will be adjusted to become 0-based
	while (cont == true) {
		cout << endl << "Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ";
		cin >> input;
		//valid
		if (input >= 1 && input <=5) { // valid input
			//insert
			if (input == 1) {
				string name;
				string artist;
				int length;
				unsigned int pos;

				// song name can't be ""
				cout << "Song name: ";
				cin.ignore(10000,'\n');
				getline(cin,name);
				while(name == "" || name == " ") {
					cout << "Invalid song name, input can't be empty. Please try again." << endl;
					cout << "Song name: ";
					getline(cin,name);
				}

				// artist can't be ""
				cout << "Artist: ";
				getline(cin,artist);
				while (artist == "" || artist == " ") {
					cout << "Invalid artist, input can't be empty. Please try again." << endl;
					cout << "Artist: ";
					getline(cin,artist);
				}
				
				// length must be > 1
				cout << "Length: ";
				cin >> length;
				while (length < 1) {
					if (cin.fail()) {
						cin.clear();
						cin.ignore(10000,'\n');
					}
 					cout << "Invalid length, length should be an integer > 0. Please try again." << endl;
					cout << "Length: ";
					cin >> length;
				}
				//validate_int(length<1, length, "Length: ");

				if (pl->size() == 0) {
					cout << "Position (1): ";
					cin >> pos;
					while (pos != 1) {
						if (cin.fail()) {
							cin.clear();
							cin.ignore(10000,'\n');
						}
						cout << "Invalid position, enter '1'." << endl;
						cout << "Position (1): ";
						cin >> pos;
					//validate_int(pos!=1, pos, "Position (1): ");
					}
				}
				else {
					cout << "Position (1 to " << (size+1) << "): ";
					cin >> pos;
					while (pos<1 || pos > size+1) {
						if (cin.fail()) {
							cin.clear();
							cin.ignore(10000,'\n');
						}
						cout << "Invalid position, enter an integer in the range." << endl;
						cout << "Position (1 to " << (size+1) << "): ";
						cin >> pos;
					}
				}

				Song sng = Song(name, artist, length);
				pl->insert(sng, pos-1);
				size++;
				cout << "You entered " << name << " at position " << pos << " in the play list" << endl;
			}
			//remove
			else if (input == 2) {
				unsigned int pos;
				if (pl->size() == 0) { // playlist is empty
					cout << "Play list is empty, nothing to remove." << endl;
				}
				else if (pl->size() == 1) { // playlist has one song
					cout << "Position (1): ";
					cin >> pos;
					while (pos != 1) { // if user inpuit invalid, continute asking for user input until valid
						if (cin.fail()) {
							cin.clear();
							cin.ignore(10000,'\n');
						}
						cout << "Invalid position, enter '1'." << endl;
						cout << "Position (1): ";
						cin >> pos;
					}
					pl->remove(pos-1); // remove song at given position 
					size--; // size decreased by 1 after removal
				}
				else { // playlist has more than one song
					cout << "Position (1 to " << size << "): ";
					cin >> pos;
					while (pos<1 || pos > size) { // if user input is invalid, continute asking for user input until valid
						if (cin.fail()) {
							cin.clear();
							cin.ignore(10000,'\n');
						}
						cout << "Invalid position, enter an integer in the range. " << endl;
						cout << "Position (1 to " << (size) << "): ";
						cin >> pos;
					}
					pl->remove(pos-1); // remove song at given position
					size--; // size decreased by 1 after removal
				}
			}
			//swap
			else if (input == 3) {
				if (size < 2) { // playlist must have at least 2 songs to be able to swap
					cout << "Not enough songs in the play list to swap." << endl;
				}
				else {
					unsigned int pos1, pos2;
					cout << "Swap song at position (1 to " << (size) << "): "; 
					cin >> pos1;
					while (pos1<1 || pos1>size) { // if user input is invalid, continute asking for user input until valid
						if (cin.fail()) {
							cin.clear();
							cin.ignore(10000,'\n');
						}
						cout << "Invalid position, enter an integer in the range. " << endl;
						cout << "Swap Song at position (1 to " << (size) << "): ";
						cin >> pos1;
					}
					cout << "with the song at position (1 to " << (size) << "): ";
					cin >> pos2;
					// pos1 != pos2
					while (pos2<1 || pos2>size) { // if user input is invalid, continute asking for user input until valid
						if (cin.fail()) {
							cin.clear();
							cin.ignore(10000,'\n');
						}
						cout << "Invalid position, enter an integer in the range. " << endl;
						cout << "with the song at position (1 to " << (size) << "): ";
						cin >> pos2;
					}
					pl->swap(pos1-1,pos2-1); // swap positions
					cout << "Your swapped the songs at positions " << pos1 << " and " << pos2 << endl;
				}
			}
			// print
			else if (input == 4) { 
				if (size == 0) { // size = 0, nothing to print
					cout << "The play list is empty, try adding a song!" << endl;
				}
				else { // size > 0
					for (unsigned int i =0; i<size; i++) { // loop through playlist and print
						cout << i+1 << " " << pl->get(i).getName() << " (" << pl->get(i).getArtist() << ") " << pl->get(i).getLength() << "s" <<endl;
					}
					if (size == 1) {
						cout << "There is 1 song in the play list." << endl;
					}
					else {
						cout << "There are " << size << " songs in the play list." << endl;
					}
				}
			}
			else {	// input == 5, exit program
				cout << "You have chosen to quit the program." << endl;
				cont = false;
			}
		}
		else {	// invalid input, force user to input again
			cin.clear();
			cin.ignore(10000,'\n');
			cout << "Invalid input, enter one of the following: [1,2,3,4,5]" << endl;
		}
	}

	delete pl; // deallocate space 
	return 0;
}