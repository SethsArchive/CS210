#include <iostream>
#include <iomanip>
using namespace std;

#include "Animal.h"

//Constructor
Animal::Animal(string animalName, int trackingNum, string animalType, string animalSubType, int numOfEggs, int nursing){
	name = animalName;
	this->trackingNum = trackingNum;
	this->animalType = animalType;
	this->animalSubType = animalSubType;
	this->numOfEggs = numOfEggs;
	this->nursing = nursing;
}

//Retrieves name
string Animal::GetName(){
	return name;
}

//Retrieves tracking number
int Animal::GetTrackingNumber(){
	return trackingNum;
}

//Retrieves animal type
string Animal::GetAnimalType(){
	return animalType;
}

//Retrieves animal sub type
string Animal::GetAnimalSubType(){
	return animalSubType;
}

//Retrieves egg number
int Animal::GetNumOfEggs(){
	return numOfEggs;
}

//Retrieves nursing value
int Animal::GetNursing(){
	return nursing;
}

//Prints formatted info
void Animal::PrintInfo(){
	cout << "| " << setw(6) << setfill('0') << right << trackingNum << " || ";
	cout << setw(15) << setfill(' ') << left << name << " || ";
	cout << setw(15) << left << animalType << " || ";
	cout << setw(15) << left << animalSubType << " || ";
	cout << setw(4) << left  << numOfEggs << " || ";
	cout << setw(7) << left << nursing << " |" << endl;
}
