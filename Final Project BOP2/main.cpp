#include <time.h>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include "Cars.h"
#include "Customer.h"
#include "Rental.h"
#include <ctime>
#include <sstream>
using namespace std;


// function to load car data from text file
// using dynamic store
// file handling
vector<Car*> loadCarData(const string& filename) {
    vector<Car*> cars;
    ifstream file(filename);
    if (file.is_open()) {
        int ID, Year, daily_price;
        string Model, Make;
        bool avl;
        while (file >> ID >> Year >> Model >> Make >> daily_price >> avl) {
            Car* car = new Car(ID, Year, Model, Make, daily_price, avl);
            cars.push_back(car);
        }
        cout << "Number of cars added: " << cars.size() << endl;
        file.close();
    } else {
        throw runtime_error("Failed to open text file: " + filename);
    }
    return cars;
}

//take valid integer put from user
//the loop will not ternimate until user enter valid input
int getValidIntegerInput(const string& msg) {
    int number;
    while (true) {
        cout << msg;
        if (cin >> number) {
            // Input is a valid integer
            break;
        } else {
            // Input is not a valid integer
            cout << "Invalid input. Please enter a valid integer" << endl;
            cin.clear();  // clear error flags
            // discarding the input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return number;
}

// function to convert a string date in the format "DD:MM:YYYY" to a timestamp in seconds
// to store in text file as our load rental data function read in timestamp from file
time_t convertStringToTimestamp(const std::string& dateString) {
    std::tm tm = {};
    std::istringstream iss(dateString);
    char delimiter;
    iss >> tm.tm_mday >> delimiter >> tm.tm_mon >> delimiter >> tm.tm_year;
    tm.tm_mon -= 1;  // adjust month to zero-based (0-11)
    tm.tm_year -= 1900;  // adjust year to be years since 1900
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    return std::mktime(&tm);
}

// Function to load rental data from file
//using dymain storage
vector<Rental*> loadRentalData(const string& filename) {
    vector<Rental*> rentals;
    ifstream file(filename);
    if (file.is_open()) {
        time_t start_date, end_date;
        int ID, Year, daily_price, Age, phone_number;
        string name, email, Model, Make;
        bool avl;
        while (file >> start_date >> end_date >> name >> Age >> email >> phone_number >> ID >>
        Year >> Model >> Make >> daily_price >> avl) {
            Rental* rental = new Rental(start_date, end_date, name, Age, email, phone_number, ID, Year, Model, Make, daily_price, avl);
            rentals.push_back(rental);
        }
        cout << "Number of rentals added: " << rentals.size() << endl;
        file.close();
    } else {
        throw runtime_error("\nFailed to open rental data file\n");
    }
    return rentals;
}
// function to save car data to file
void saveCarData(const string& filename,vector<Car*>& cars) {
    ofstream file(filename);
    if (file.is_open()) {
        for (Car* car : cars)  {
            file << car->get_ID() << " " << car->get_year() << " " << car->get_Model() << " " << car->get_Make()
            << " " << car->get_daily_price()<< " " << 1 << endl;
        }
        file.close();
        cout<<"\nCars database text file updated success"<<endl;
    } else {
        throw runtime_error("Failed to open car data file for writing");
    }
}

// Function to save rental data to file
void saveRentalData(const string& filename,vector<Rental*>& rentals) {
    ofstream file(filename);
    if (file.is_open()) {
        for (Rental* rental : rentals) {
            file << rental->getStartDate() << " " << rental->getEndDate() << " " << rental->getCustomer()->get_name() << " "
                 << rental->getCustomer()->get_Age() << " " << rental->getCustomer()->get_email() << " "
                 << rental->getCustomer()->get_phone_number() << " " << rental->getCar()->get_ID() << " "
                 << rental->getCar()->get_year() << " " << rental->getCar()->get_Model() << " "
                 << rental->getCar()->get_Make() << " " << rental->getCar()->get_daily_price()
                 << " " << rental->getCar()->get_IsAvailable() << endl;
        }
        file.close();
        cout<<"\nRental database text file updated success\n"<<endl;
    } else {
        throw runtime_error("\nFailed to open rental data file for writing\n");
    }
}

int main() {
    vector<Car*> cars;
    vector<Rental*> rentals;

    // load data from files
    // try catch for exception handling
    try {
        cars = loadCarData("car_data.txt");
        rentals = loadRentalData("rental_data.txt");
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    int choice;
    bool exit = false;
    bool found = false;
    Car* selectedCar = nullptr;

    while(!exit){
        // display menu to user
        cout << "\n******************** Car Rental Management System ********************\n";
        cout << "1. Add a new car" << endl;
        cout << "2. Rent a car (also show all cars to select car for rent)" << endl;
        cout << "3. Show all cars" << endl;
        cout << "4. Display rental details" << endl;
        cout << "5. Remove a Car" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Add a new car
                int ID, Year, daily_price;
                string Model, Make;
                cout << "Enter car details:" << endl;
                //call the validate input method to get a valid input
                ID =  getValidIntegerInput("Enter ID :");
                Year = getValidIntegerInput("Enter Year :");
                cout << "Company Make: ";
                cin>> Model;
                cout << "Model : ";
                cin>> Make;
                daily_price = getValidIntegerInput("Daily Price: ");

                //dynamic memory allocation using new
                Car* newCar = new Car(ID, Year, Model, Make, daily_price, true);
                cars.push_back(newCar);
                // save car data to file
                try {
                    saveCarData("car_data.txt", cars);
                } catch (const exception& e) {
                    cerr << "Error: " << e.what() << endl;
                }

                cout << "New car added successfully" << endl;
                break;
            }
            case 2: {
                // rent a car
                // display all cars' information
                cout << "\n******************** Available Cars ********************\n";
                for (int i = 0; i < cars.size(); ++i) {
                    cout << "\n-------------\n";
                    cars[i]->printCarDetails();
                }

                // Get a valid car ID input from the user
                int carID;
                carID = getValidIntegerInput("Enter the car ID to rent: ");

                // find the car with the given ID
                for (Car* car : cars) {
                if (car->get_ID() == carID) {
                    selectedCar = car;
                    break;
                }
                }

            // if car is found with given id
            if (selectedCar != nullptr) {
                // Check if the selected car is available
                if (selectedCar->get_IsAvailable()) {
                     // Get rental details from the user
                    time_t start_date, end_date;
                    string name, email, dateString, dateString1;
                    int Age, phone_number;
                    cout << "Enter rental details:" << endl;
                    cout << "Enter the start date DD:MM:YYYY: ";
                    cin >> dateString;
                    start_date = convertStringToTimestamp(dateString);
                    cout << "Enter the end date DD:MM:YYYY: ";
                    cin >> dateString1;
                    end_date = convertStringToTimestamp(dateString1);
                    cout << "Customer Name: ";
                    cin >> name;
                    Age = getValidIntegerInput("Age: ");
                    cout << "Email: ";
                    cin >> email;
                    phone_number = getValidIntegerInput("Phone Number: ");

                    // Create a new rental
                    Rental* rental = new Rental(start_date, end_date, name, Age, email, phone_number, selectedCar->get_ID(), selectedCar->get_year(),
                    selectedCar->get_Model(), selectedCar->get_Make(), selectedCar->get_daily_price(), false);
                    rentals.push_back(rental);
                    // Save rental data to file
                    try {
                            saveRentalData("rental_data.txt", rentals);
                    } catch (const exception& e) {
                        cerr << "Error: " << e.what() << endl;
                    }
                    cout << "Car rented successfully" << endl;
                    selectedCar->set_IsAvailable(false);
                    } else {
                        cout << "Sorry! Car is unavailable" << endl;
                    }
                }
                else {
                cout << "\nInvalid car ID!\n";
                }
                break;
            }
                case 3:
                    //display all cars information
                    cout << "\n******************** All Cars ********************\n";
                    for (Car* car : cars) {
                        cout<<"\n-------------\n";
                        car->printCarDetails();
                    }
                    break;
                case 4:
                    //display all rental data
                    cout << "\n******************** All Rental History ********************\n";
                    for (Rental* rental : rentals) {
                        cout<<"\n-------------\n";
                        rental->printRentalDetails();
                    }
                    break;
                case 5:
                    //remmove a car
                    int id;
                    id = getValidIntegerInput("Eneter Car ID to remove: ");
                    //search all cars with given id and remove if any car id match
                    for (auto it = cars.begin(); it != cars.end(); ++it) {
                    if ((*it)->get_ID() == id) {
                        delete *it; // free the memory allocated for the car object
                        cars.erase(it);
                        found = true;
                        cout << "Car removed successfully" << endl;
                        break;
                    }
                    }
                    //upadte cars database text file if car removed
                    if(found)
                    {
                        // save car data to file
                        try {
                                saveCarData("car_data.txt", cars);
                        } catch (const exception& e) {
                            cerr << "Error: " << e.what() << endl;
                        }
                    }
                    else if(!found)
                    {
                        cout << "Failed! No car found with id: "<<id << endl;
                    }
                    break;
                case 6:
                    //terminate while loop
                    exit=true;
                    cout << "Exit success.....";
                    break;
                break;

                default:
                    cout << "Invalid choice!" << endl;

            }
        }
    }
