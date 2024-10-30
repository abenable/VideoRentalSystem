#include "../include/customer.h"
#include <iostream>

using namespace std;

// Constructor implementation
Customer::Customer(int id, const string &name, const string &address,
                   const string &phone, const string &email, bool premium)
    : customerID(id), name(name), address(address), phone(phone), email(email), isPremiumMember(premium) {}

// Getters
int Customer::getCustomerID() const { return customerID; }
string Customer::getName() const { return name; }
string Customer::getAddress() const { return address; }
string Customer::getPhone() const { return phone; }
string Customer::getEmail() const { return email; }
bool Customer::getIsPremiumMember() const { return isPremiumMember; }

// Setters
void Customer::setName(const string &name) { this->name = name; }
void Customer::setAddress(const string &address) { this->address = address; }
void Customer::setPhone(const string &phone) { this->phone = phone; }
void Customer::setEmail(const string &email) { this->email = email; }
void Customer::setIsPremiumMember(bool premium) { isPremiumMember = premium; }

// Display customer info
void Customer::displayCustomerInfo() const
{
    cout << "Customer ID: " << customerID << "\n"
         << "Name: " << name << "\n"
         << "Address: " << address << "\n"
         << "Phone: " << phone << "\n"
         << "Email: " << email << "\n"
         << "Premium Member: " << (isPremiumMember ? "Yes" : "No") << endl;
}
