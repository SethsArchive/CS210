//Author: Seth Daniel
//Date: 2/21/2021
//Description: Takes in file data that was created using Java.
//			   Displays info regarding to the animals and allows for adding and removing of animal data

#include <iostream>
#include <jni.h>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

#include "Animal.h"

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

//Adds a new animal to vector
void AddAnimal(vector<Animal*>& animals)
{
	int trackNum; //Tracking Number
	string name; //Animal Name
	string animalType; //Animal Type (Mammal or Oviparous)
	string animalSubType; //Animal Sub Type (Bat, Goose, Elephant)
	int numOfEggs; //Number of eggs
	int nurses; //1 or 0 if nursing baby

	//Assigns tracking number for new animal
	cout << "Track Number:" << endl;
	cin >> trackNum;

	//Assigns name for new animal
	cout << "Enter Animal Name:" << endl;
	cin >> name;

	//Assigns animal type for new animal
	cout << "Enter Animal Type:" << endl;
	cin >> animalType;

	//Assigns animal sub type for new animal
	cout << "Enter Animal Sub-Type:" << endl;
	cin >> animalSubType;

	//Assigns number of eggs for new animal
	cout << "Enter Number of Eggs:" << endl;
	cin >> numOfEggs;

	//Assigns whether animal is currently nursing a baby
	cout << "Enter 1 if Nursing, 0 if not:" << endl;
	cin >> nurses;

	//Creates new animal object and puts it in vector
	Animal* newAnimal = new Animal(name, trackNum, animalType, animalSubType, numOfEggs, nurses);
	animals.push_back(newAnimal);
}

//Removes animal from vector
void RemoveAnimal(vector<Animal*>& animals)
{
	int animalToRemove; //Position of animal in the vector to remove

	//Assigns position of the animal
    cout << "Enter number of animal you wish to remove:" << endl;
    cin >> animalToRemove;

    //Erases vector data at specified spot
    animals.erase(animals.begin() + (animalToRemove - 1));
}

//Loads data from the "zoodata.txt" file
void LoadDataFromFile(vector<Animal*>& animals)
{
	string name; //Animal name
	int trackingNum; //Tracking Number
	string animalType; //Animal Type (Mammal or Oviparous)
	string animalSubType; //Animal Sub Type (Bat, Goose, Elephant)
	int numOfEggs; //Number of eggs
	int nursing; //1 or 0 for nursing a baby

	ifstream inFS; //File in stream
	inFS.open("zoodata.txt"); //Opens "zoodata.txt" to read data from file

	//Loops for all lines in the file, assigns the corresponding data, and puts data into a vector
	while(inFS >> trackingNum >> name >> animalType >> animalSubType >> numOfEggs >> nursing){

		//Creates new Animal object and adds to vector
		Animal* newAnimal = new Animal(name, trackingNum, animalType, animalSubType, numOfEggs, nursing);
		animals.push_back(newAnimal);
	}

	inFS.close(); //Closes file
}

//Writes vector data to file
void SaveDataToFile(const vector<Animal*>& animals)
{
	string name; //Animal Name
	int trackingNum; //Tracking Number
	string animalType; //Animal Type (Mammal or Oviparous)
	string animalSubType; //Animal SubType (Bat, Goose, Elephant)
	int numOfEggs; //Number of eggs
	int nursing; //1 or 0 if nursing baby
	unsigned int i; //Loop index

	ofstream outFS; //File out stream
	outFS.open("zoodata.txt"); //Opens "zoodata.txt" to write data to file

	//Loops through vector assigning corresponding data and writes to file
	for(i = 0; i < animals.size(); ++i){
		name = animals.at(i)->GetName();
		trackingNum = animals.at(i)->GetTrackingNumber();
		animalType = animals.at(i)->GetAnimalType();
		animalSubType = animals.at(i)->GetAnimalSubType();
		numOfEggs = animals.at(i)->GetNumOfEggs();
		nursing = animals.at(i)->GetNursing();


		outFS << setw(6) << setfill('0') << trackingNum << " ";
		outFS << setw(15) << setfill(' ') << name << " ";
		outFS << setw(15) << animalType << " ";
		outFS << setw(15) << animalSubType << " ";
		outFS << numOfEggs << " " << nursing << endl;
	}

	outFS.close(); //Closes file
}

//Display menu
void DisplayMenu()
{
	cout << "1) Load Animal Data\t\t\t2) Generate Data" << endl << endl;
	cout << "3) Display Animal Data\t\t\t4) Add Record" << endl << endl;
	cout << "5) Delete Record\t\t\t6) Save Animal Data" << endl << endl;
}

//Displays formatted animal data
void DisplayAnimalData(const vector<Animal*>& animals){
	unsigned int i; //Loop index

	cout << "| " << setw(6) << "Track#" << " || ";
	cout << setw(15) << "  Animal Name  " << " || ";
	cout << setw(15) << "  Animal Type  " << " || ";
	cout << setw(15) << "Animal Sub Type" << " || ";
	cout << setw(4) << "Eggs" << " || ";
	cout << setw(7) << "Nursing" << " |" << endl;

	//Prints animal info
	for(i = 0; i < animals.size(); ++i){
		animals.at(i)->PrintInfo();
	}
}

int main()
{
	int userChoice; //Users choice for menu
	char keepGoing; //Checks if the user would like to keep going
	vector<Animal*> animals; //Animal vector

	do{
		DisplayMenu();
		cin >> userChoice;

		switch(userChoice){
		case 1:
			LoadDataFromFile(animals);
			break;
		case 2:
			GenerateData();
			break;
		case 3:
			DisplayAnimalData(animals);
			break;
		case 4:
			AddAnimal(animals);
			break;
		case 5:
			RemoveAnimal(animals);
			break;
		case 6:
			SaveDataToFile(animals);
			break;
		default:
			cout << "Invalid input. Exiting Program...";
			exit(0);
		}

		cout << "Do you wish to continue?(\'Y\' or \'y\' for yes)" << endl;
		cin >> keepGoing;

	}while(keepGoing == 'Y' || keepGoing == 'y');

	return 1;
}
