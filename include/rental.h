#ifndef RENTAL_H
#define RENTAL_H

#include <string>
#include "video.h"
#include "customer.h"

using namespace std;

class Rental
{
private:
    int rentalID;
    Customer customer;
    Video video;
    int duration;
    string rentalDate;
    string dueDate;
    bool isReturned;

public:
    // Constructor
    Rental(int rentalID, const Customer *customer, const Video *video, int duration, bool isReturned);
    int getRentalID() const;
    int getCustomerID() const;
    int getVideoID() const;
    int getDuration() const;
    string getRentalDate() const;
    string getDueDate() const;
    bool getIsReturned() const;

    // Setters
    void setReturnStatus(bool status);
    string setRentalDate() const;
    string setDueDate() const;

    // Display rental info
    void
    displayRentalInfo() const;
};

#endif // RENTAL_H
