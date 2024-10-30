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
    string email;
    bool isPremiumMember;

public:
    // Constructor
    Customer(int id, const string &name, const string &address,
             const string &phone, const string &email, bool premium = false);

    // Getters
    int getCustomerID() const;
    string getName() const;
    string getAddress() const;
    string getPhone() const;
    string getEmail() const;
    bool getIsPremiumMember() const;

    // Setters
    void setName(const string &name);
    void setAddress(const string &address);
    void setPhone(const string &phone);
    void setEmail(const string &email);
    void setIsPremiumMember(bool premium);

    // Display customer info
    void displayCustomerInfo() const;
};

#endif // CUSTOMER_H
