#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
using namespace std;

class Customer
{
private:
    int customerID;
    string name;
    string address;
    string phone;

public:
    // Constructor
    Customer(int id, const string &name, const string &address,
             const string &phone);

    // Getters
    int getCustomerID() const;
    string getName() const;
    string getAddress() const;
    string getPhone() const;

    // Setters
    void setName(const string &name);
    void setAddress(const string &address);
    void setPhone(const string &phone);

    // Display customer info
    void displayCustomerInfo() const;
};

#endif // CUSTOMER_H
