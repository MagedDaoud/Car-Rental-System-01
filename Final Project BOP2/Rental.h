#ifndef RENTAL_H_INCLUDED
#define RENTAL_H_INCLUDED



#endif // RENTAL_H_INCLUDED
#ifndef RENTAL_H
#define RENTAL_H

#include <string>
#include <iostream>
#include <time.h>
#include "Cars.h"
#include "Customer.h"
using namespace std;

class Rental {
	time_t start_date;
	time_t end_date;
	Car* car;
	Customer* customer;

public:
	Rental(time_t start_date, time_t end_date, string name, int Age,
		string email, int phone_number, int ID, int Year,
		string Model, string Make, int daily_price,bool isAvailable) {

		this->start_date = start_date;
		this->end_date = end_date;
		car = new Car(ID, Year, Model, Make, daily_price, isAvailable);
		customer = new Customer(name, Age, email, phone_number);
	}

	// Getter and Setter for start_date
    time_t getStartDate() const {
        return start_date;
    }

    void setStartDate(time_t startDate) {
        start_date = startDate;
    }

    // Getter and Setter for end_date
    time_t getEndDate() const {
        return end_date;
    }

    void setEndDate(time_t endDate) {
        end_date = endDate;
    }

    // Getter and Setter for car
    Car* getCar() const {
        return car;
    }

    void setCar(Car* car) {
        this->car = car;
    }

    // Getter and Setter for customer
    Customer* getCustomer() const {
        return customer;
    }

    void setCustomer(Customer* customer) {
        this->customer = customer;
    }


    //print rental data details
    void printRentalDetails() const {
    cout << "Rental Details:" << endl;
    cout << "Start Date: " << ctime(&start_date);
    cout << "End Date: " << ctime(&end_date)<<endl;
    customer->printCustomerDetails();
    cout << "Car Details:" << endl;
    cout << car->get_Make()<< " " << car->get_Model()<<" "<<car->get_year();
    cout << endl;
}

};

#endif
