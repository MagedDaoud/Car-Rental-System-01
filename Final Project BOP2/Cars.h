#ifndef CARS_H
#define CARS_H

#include <string>
using namespace std;

class Car {

	int ID;
	int Year;
	string Model;
	string Make;
	int daily_price;
	bool isAvailable;

public:
	Car(int ID, int Year, string Make, string Model, int daily_price, bool isAvailable) {
		this->ID = ID;
		this->Year = Year;
		this->Model = Model;
		this->Make = Make;
		this->daily_price = daily_price;
		this->isAvailable = isAvailable;
	}
	// Getters
	int get_ID() {
		return this->ID;
	}
	int get_year() {
		return this->Year;
	}
	int get_daily_price() {
		return this->daily_price;
	}
	string get_Model() {
		return this->Model;
	}
	string get_Make() {
		return this->Make;
	}
	bool get_IsAvailable(){
		return this->isAvailable;
	}

	//Setters for daily price and availabity
	void set_daily_price(int daily_price) {
		this->daily_price = daily_price;
	}
	void set_IsAvailable(bool avl) {
		this->isAvailable = avl;
	}

	//method to print detals of car
	void printCarDetails() {
    cout << "Car ID: " << ID << endl;
    cout << "Year: " << Year << endl;
    cout << "Model: " << Model << endl;
    cout << "Make: " << Make << endl;
    cout << "Daily Price: " << daily_price << endl;
	if(isAvailable)
		cout << "Availabilty Status: Available(True)"<< endl;
	else
		cout << "Availabilty Status: Not-Available(False)"<< endl;
}
};


#endif
