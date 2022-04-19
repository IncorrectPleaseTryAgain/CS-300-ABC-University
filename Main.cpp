/*
* Name: Michael Steenkamp
* Prof: Amy Burns
* Project Two
* 9/04/2022
* 
* Main.cpp
* 
* This program reads courses and their respected prerequisites
* from a file. The user can then print the courses in alphabetical order
* according to their ID, or the user can print information of a specific
* course.
*/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <thread>

#include "BinarySearchTree.h"

using namespace std;

//number of seconds to sleep
#define NUM_SECONDS_PAUSE 1

/* Method Decleration */

/*
* Display menu.
*
* @return N/A
* Parameters: N/A
*/
void displayMenu();

/*
* Get menu selection from user input.
*
* @return N/A
* Parameters: int&
*/
void getUserInput(int& userChoice);

/*
* Get the input file name from user input.
* 
* @return N/A
* Parameters: string&
*/
void getInputFile(string& fileName);

/*
* Load the file data into the data structure.
*
* @return N/A
* Parameters: const string&
*/
void loadData(BinarySearchTree& BST);

/*
* Check If prerequisite is defined course in file.
*
* @return Boolean
* Parameters: const string&
*             const string&
*/
bool validPrerequisite(const string& fileName, const string& prerequisite);

/*
* Get course ID from user input.
*
* @return N/A
* Parameters: BinarySearchTree&
*			  string&
*/
void getCourse(BinarySearchTree& BST, string& id);

/*
* Format user input for course ID - Capitalize.
*
* @return N/A
* Parameters: string&
*/
void formatId(string& id);

/*
* Pause until user press enter.
*
* @return N/A
* Parameters: N/A
*/
void pressEnterToContinue();

/* Main Method */

int main()
{
	/* Declare variables */
	int userChoice = 99999;
	string courseId = "";

	// Declare BST Object
	BinarySearchTree BST;

	/* Logic */
	while (userChoice != 9)
	{
		displayMenu();
		getUserInput(userChoice);

		switch (userChoice)
		{
			
		case 1: // Load Data
			loadData(BST);
			pressEnterToContinue();
			break;

			
		case 2: // Print Course List
			BST.printCourseList();
			pressEnterToContinue();
			break;

			
		case 3: // Print Course
			getCourse(BST, courseId);
			
			// If user exit function before entering valid id
			if (courseId == "back")
			{
				// Clear terminal
				system("CLS");
				break;
			}

			BST.printCourse(courseId);
			pressEnterToContinue();
			break;

			
		default: // Exit
			userChoice = 9;
			break;
		}
	}

	// Clear Terminal
	system("CLS");

	// Exit Message
	cout << "Program Exit Successful";

	return 0;
}

/* Method Initialization */

void displayMenu()
{
	// Clear Terminal
	system("CLS");

	// Welcome Message
	cout << setw(26) << "The Course Planner" << endl;
	cout << setw(20) << "Welcome!" << endl;

	// Display Options
	cout << "---------------------------------" << endl;
	cout << "| Option 1: Load Data           |" << endl;
	cout << "|                               |" << endl;
	cout << "| Option 2: Print Course List   |" << endl;
	cout << "|                               |" << endl;
	cout << "| Option 3: Print Course        |" << endl;
	cout << "|                               |" << endl;
	cout << "| Option 9: EXIT                |" << endl;
	cout << "---------------------------------" << endl;
}

void getUserInput(int& userChoice)
{
    cout << "Please Enter Option: ";
    cin >> userChoice;

	// While input is invalid
    while (cin.fail() || userChoice < 0)
    {
        //error message
        cout << "Error: Invalid Input" << endl;

        //clear buffer
        cin.clear();
        cin.ignore(256, '\n');

        //get new input
        cout << "Please Enter Option: ";
        cin >> userChoice;
    }

}

void getInputFile(string& fileName)
{
	// Text file extention
	const string TEXT_FILE_EXTENTION = ".txt";

	// File type
	string fileExtention = "";

	cout << "Please Enter Text File: ";
	cin >> fileName;

	// If file has at least 4 characters to satisfy extention - .txt
	if (fileName.length() >= 4)
	{
		// Store file extention
		// Example: .txt
		// 4 -> length of extention
		for (int i = 4; i > 0; i--)
		{
			fileExtention.push_back(fileName[fileName.length() - i]);
		}
	}

	// While input is invalid
	while (cin.fail() || fileName.length() < 4 || fileExtention != TEXT_FILE_EXTENTION)
	{
		//error message
		cout << "Error: Invalid Input" << endl;

		//clear buffer
		cin.clear();
		cin.ignore(256, '\n');

		//get new input
		cout << "Please Enter File: ";
		cin >> fileName;

		// If file has at least 4 characters to satisfy extention - .txt
		if (fileName.length() >= 4)
		{
			// Store file extention - .txt
			for (int i = 4; i > 0; i--)
			{
				fileExtention.push_back(fileName[fileName.length() - i]);
			}
		}
	}
}

void loadData(BinarySearchTree& BST)
{
	ifstream myFile;
	string fileName = "";
	
	// Store current file line string
	string currLine = "";

	// Store current file line number
	unsigned int currFileLine = 1;

	// Get file name
	getInputFile(fileName);

	cout << "\nAttempt Open \"" << fileName << "\"..." << endl;

	// Open file to read
	myFile.open(fileName);

	// Unsuccessful open	
	if (!myFile.is_open())
	{
		while (!myFile.is_open())
		{
			// Error Message
			cout << "Error: Cannot Open \"" << fileName << "\"" << endl;

			// Get file name
			getInputFile(fileName);

			cout << "Attempt Open \"" << fileName << "\"..." << endl;

			// Open file to read
			myFile.open(fileName);
		}

	}

	// Pause 1 second
	this_thread::sleep_for(chrono::seconds(NUM_SECONDS_PAUSE));

	cout << "Attempt Read \"" << fileName <<  "\"..." << endl;

	// Pause 1 second
	this_thread::sleep_for(chrono::seconds(NUM_SECONDS_PAUSE));

	try
	{
		// While you can read a line from file
		while (getline(myFile, currLine))
		{
			const string EMPTY_STRING = "";

			// Store subject id and name
			string id;
			string name;

			stringstream ss(currLine);

			// Read ID
			getline(ss, id, ',');

			// Read Name
			getline(ss, name, ',');

			// If there is less than two parameters
			if (id == EMPTY_STRING || name == EMPTY_STRING)
			{
				cout << "(" << currFileLine << ") Error: Could Not Read" << endl;
			}
			else
			{
				// Store subject prerequisites
				vector<string> prereq;

				// While there are still some parameters
				while (true)
				{
					string currPrereq = "";

					// Read prerequisite
					getline(ss, currPrereq, ',');

					// If no more prerequisites to read
					if (currPrereq == EMPTY_STRING)
					{
						// Go to next line
						break;
					}
					else
					{
						// If prerequisite is defined as course in file
						if (validPrerequisite(fileName, currPrereq))
						{
							// Add prerequisite to list
							prereq.push_back(currPrereq);
						}
						else
						{
							cout << "(" << currFileLine << ") Error: Prerequisite \"" << currPrereq << "\" Invalid." << endl;
						}
					}
				}

				// Store subject into binary search tree
				BST.insertCourse(id, name, prereq);
			}

			currFileLine++;
		}
	}
	catch (...)
	{
		cout << "Error: Reading File" << endl;
	}

	cout << "Attempt Close \"" << fileName << "\"..." << endl;

	// Pause 1 second
	this_thread::sleep_for(chrono::seconds(NUM_SECONDS_PAUSE));

	try
	{
		// Close file
		myFile.close();
	}
	catch (...)
	{
		// Keep track of amount of times attempting to close file
		unsigned int count = 0;

		// While file is open
		while (myFile.is_open())
		{
			// If attempted to close file 10 times
			if (count == 10)
			{
				cout << "FAILED" << endl;
				return;
			}

			cout << "Could Not Close File..." << endl;
			cout << "Re-Attempting Closing File..." << endl;

			// Close file
			myFile.close();

			count++;
		}
	}

	cout << "Successful..."  << endl;
}

bool validPrerequisite(const string& fileName, const string& prerequisite)
{
	ifstream myFile;

	// Store current file line string
	string currLine = "";

	// Open file to read
	myFile.open(fileName);

	// While you can read a line from file
	while (!myFile.eof())
	{
		// Store current subject id
		string id = "";

		// Read Line
		getline(myFile, currLine, '\n');

		// Get Course ID from line
		// 0 -> first character
		// currLine.find(',') -> character before first comma
		id = currLine.substr(0, currLine.find(','));

		// If there is less than two parameters
		if (id == prerequisite)
		{
			// Close file
			myFile.close();

			// Found
			return true;
		}
	}

	// Close file
	myFile.close();

	// Not Found
	return false;
}

void getCourse(BinarySearchTree& BST, string& id)
{
	displayMenu();

	cout << "\nNote: To Go Back, Enter \"back\"\n" << endl;
	cout << "Please Enter Course ID: ";
	cin >> id;

	if (id == "back")
	{
		return;
	}

	formatId(id);

	// While input is invalid
	while (cin.fail())
	{
		//error message
		cout << "Error: Invalid Input" << endl;

		//clear buffer
		cin.clear();
		cin.ignore(256, '\n');

		//get new input
		cout << "Please Enter Course ID: ";
		cin >> id;
	}
}

void formatId(string& id)
{
	const int LENGTH_ID = id.length();

	// Capitalize each character
	for (int i = 0; i < LENGTH_ID - 1; i++)
	{
		id[i] = toupper(id[i]);
	}
}

void pressEnterToContinue()
{
	// Pause Until user press enter
	cout << endl;
	cout << "Press Enter To Continue...";
	cin.ignore();
	cin.get();
}
