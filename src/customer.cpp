#include "../include/customer.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor implementation
Customer::Customer(int id, const string &name, const string &address,
                   const string &phone)
    : customerID(id), name(name), address(address), phone(phone) {}

// Getters
int Customer::getCustomerID() const { return customerID; }
string Customer::getName() const { return name; }
string Customer::getAddress() const { return address; }
string Customer::getPhone() const { return phone; }

// Setters
void Customer::setName(const string &name) { this->name = name; }
void Customer::setAddress(const string &address) { this->address = address; }
void Customer::setPhone(const string &phone) { this->phone = phone; }

// Display customer info
void Customer::displayCustomerInfo() const
{
    cout << "Customer ID: " << customerID << "\n"
         << "Name: " << name << "\n"
         << "Address: " << address << "\n"
         << "Phone: " << phone << endl;
}
