#include "../include/rental.h"
#include <iostream>

// Constructor implementation
Rental::Rental(int rentalID, int customerID, int videoID, const std::string &rentalDate,
               const std::string &dueDate, bool isReturned)
    : rentalID(rentalID), customerID(customerID), videoID(videoID), rentalDate(rentalDate),
      dueDate(dueDate), isReturned(isReturned) {}

// Getters
int Rental::getRentalID() const { return rentalID; }
int Rental::getCustomerID() const { return customerID; }
int Rental::getVideoID() const { return videoID; }
std::string Rental::getRentalDate() const { return rentalDate; }
std::string Rental::getDueDate() const { return dueDate; }
bool Rental::getIsReturned() const { return isReturned; }

// Setter
void Rental::setReturnStatus(bool status) { isReturned = status; }

// Display rental information
void Rental::displayRentalInfo() const
{
    std::cout << "Rental ID: " << rentalID << "\n"
              << "Customer ID: " << customerID << "\n"
              << "Video ID: " << videoID << "\n"
              << "Rental Date: " << rentalDate << "\n"
              << "Due Date: " << dueDate << "\n"
              << "Returned: " << (isReturned ? "Yes" : "No") << std::endl;
}