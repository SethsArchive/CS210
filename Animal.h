
#ifndef ANIMAL_H_
#define ANIMAL_H_

//Animal Class definition
class Animal{
public:
	Animal(string animalName, int trackingNum, string animalType, string animalSubType, int numOfEggs, int nursing);
	string GetName();
	int GetTrackingNumber();
	string GetAnimalType();
	string GetAnimalSubType();
	int GetNumOfEggs();
	int GetNursing();
    void PrintInfo();
private:
	string name;
	int trackingNum;
	string animalType;
	string animalSubType;
	int numOfEggs;
	int nursing;
};

#endif /* ANIMAL_H_ */
