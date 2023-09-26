#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
using namespace std;

class Customer  {

	string name;
	int Age;
	string email;
	int phone_number;


public:
	Customer (string name, int Age, string email, int phone_number) {
		this->name = name;
		this->Age = Age;
		this->email = email;
		this->phone_number = phone_number;
	}

	// Getters

	string get_name() {
		return this->name;
	}

	int get_Age() {
		return this->Age;
	}

	int get_phone_number() {
		return this->phone_number;
	}

	string get_email() {
		return this->email;
	}

	void printCustomerDetails() const {
    cout << "Customer Details:" << endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << Age << endl;
    cout << "Email: " << email << endl;
    cout << "Phone Number: " << phone_number << endl;
    cout << endl;
}
};


#endif
