#include "../include/rental.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor implementation
Rental::Rental(int rentalID, const Customer &customer, const Video &video, int duration,
               const string &rentalDate, const string &dueDate, bool isReturned)
    : rentalID(rentalID), customer(customer), video(video), duration(duration),
      rentalDate(rentalDate), dueDate(dueDate), isReturned(isReturned) {}

// Getters
int Rental::getRentalID() const { return rentalID; }
int Rental::getCustomerID() const { return customer.getCustomerID(); } // Get customer ID from Customer object
int Rental::getVideoID() const { return video.getVideoID(); }          // Get video ID from Video object
string Rental::getRentalDate() const { return rentalDate; }
string Rental::getDueDate() const { return dueDate; }
bool Rental::getIsReturned() const { return isReturned; }

// Setter
void Rental::setReturnStatus(bool status) { isReturned = status; }

// Display rental information
void Rental::displayRentalInfo() const
{
  cout << "Rental ID: " << rentalID << "\n"
       << "Customer ID: " << customer.getCustomerID() << "\n" // Display customer ID
       << "Video ID: " << video.getVideoID() << "\n"          // Display video ID
       << "Rental Date: " << rentalDate << "\n"
       << "Due Date: " << dueDate << "\n"
       << "Returned: " << (isReturned ? "Yes" : "No") << endl;
}
