#include <iostream>
#include <vector>
using namespace std;

/*
========================================================
PROGRAM: Vehicle Rental System (OOP Based)
--------------------------------------------------------
This program simulates a simple vehicle rental system.

WHAT THE CODE DOES:
- Stores different types of vehicles (Car, Bike, Truck)
- Displays available vehicles to the user
- Allows the user to rent a vehicle by entering plate number
- Calculates total rental cost based on vehicle type and days
- Updates vehicle availability after renting

OOP CONCEPTS USED:
- Inheritance (Car, Bike, Truck inherit Vehicle)
- Polymorphism (calculateFare() works differently)
- Abstraction (base class Vehicle)
========================================================
*/

// ===== Base Class =====
class Vehicle {
protected:
    string brand;     // vehicle brand name
    string plate;     // unique plate number
    double rate;      // rent per day
    bool available;   // availability status

public:
    // Constructor to initialize vehicle data
    Vehicle(string b, string p, double r) {
        brand = b;
        plate = p;
        rate = r;
        available = true; // all vehicles start as available
    }

    // Pure virtual function (forces derived classes to implement their own fare logic)
    virtual double calculateFare(int days) = 0;

    // Display vehicle details
    void show() {
        cout << brand << " | " << plate
             << " | Rs." << rate
             << " | " << (available ? "Available" : "Rented") << endl;
    }

    // Getter for plate number
    string getPlate() { return plate; }

    // Check if vehicle is available
    bool isAvailable() { return available; }

    // Update availability
    void setAvailable(bool a) { available = a; }
};

// ===== Derived Class: Car =====
class Car : public Vehicle {
public:
    Car(string b, string p, double r) : Vehicle(b,p,r) {}

    // Car fare = normal rate × days
    double calculateFare(int days) {
        return rate * days;
    }
};

// ===== Derived Class: Bike =====
class Bike : public Vehicle {
public:
    Bike(string b, string p, double r) : Vehicle(b,p,r) {}

    // Bike gets 20% discount
    double calculateFare(int days) {
        return rate * days * 0.8;
    }
};

// ===== Derived Class: Truck =====
class Truck : public Vehicle {
public:
    Truck(string b, string p, double r) : Vehicle(b,p,r) {}

    // Truck has 50% extra charge
    double calculateFare(int days) {
        return rate * days * 1.5;
    }
};

// ===== Main Function =====
int main() {
    vector<Vehicle*> vehicles; // stores different vehicle types using base class pointer

    // Adding sample vehicles to system
    vehicles.push_back(new Car("Toyota", "BA123", 50));
    vehicles.push_back(new Bike("Yamaha", "BA456", 20));
    vehicles.push_back(new Truck("Volvo", "BA789", 100));

    int choice;

    // Loop runs until user exits
    while (true) {
        cout << "\n=== Car Rental System ===\n";
        cout << "1. View Vehicles\n";
        cout << "2. Rent Vehicle\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        // Option 1: Display all vehicles
        if (choice == 1) {
            for (auto v : vehicles)
                v->show();
        }

        // Option 2: Rent a vehicle
        else if (choice == 2) {
            string plate;
            int days;

            // Take user input
            cout << "Enter plate: ";
            cin >> plate;
            cout << "Enter days: ";
            cin >> days;

            bool found = false;

            // Search for the requested vehicle
            for (auto v : vehicles) {
                // If plate matches and vehicle is available
                if (v->getPlate() == plate && v->isAvailable()) {

                    // Polymorphism: calls correct calculateFare()
                    double cost = v->calculateFare(days);

                    // Mark vehicle as rented
                    v->setAvailable(false);

                    cout << "Total Cost: Rs." << cost << endl;
                    found = true;
                    break;
                }
            }

            // If vehicle not found or already rented
            if (!found)
                cout << "Vehicle not available\n";
        }

        // Option 3: Exit program
        else if (choice == 3) {
            break;
        }
    }

    return 0;
}