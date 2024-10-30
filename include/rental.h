#ifndef RENTAL_H
#define RENTAL_H

#include <string>
using namespace std;

class Rental
{
private:
    int rentalID;
    int customerID;
    int videoID;
    string rentalDate;
    string dueDate;
    bool isReturned;

public:
    // Constructor
    Rental(int rentalID, int customerID, int videoID, const string &rentalDate,
           const string &dueDate, bool isReturned = false);

    // Getters
    int getRentalID() const;
    int getCustomerID() const;
    int getVideoID() const;
    string getRentalDate() const;
    string getDueDate() const;
    bool getIsReturned() const;

    // Setters
    void setReturnStatus(bool status);

    // Display rental info
    void displayRentalInfo() const;
};

#endif // RENTAL_H
