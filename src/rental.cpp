#include <ctime>
#include "../include/rental.h"
#include <iostream>
#include <string>

using namespace std;

// Helper function to generate date strings
string getCurrentDate()
{
  time_t now = time(0);
  tm *ltm = localtime(&now);
  char date[20];
  strftime(date, sizeof(date), "%Y-%m-%d", ltm);
  return string(date);
}

// Constructor implementation
Rental::Rental(int rentalID, const Customer *customer, const Video *video, int duration, bool isReturned)
    : rentalID(rentalID), customer(*customer), video(*video), duration(duration),
      isReturned(isReturned), rentalDate(getCurrentDate()), dueDate(getDueDate()) {}

// Getters
int Rental::getRentalID() const { return rentalID; }
int Rental::getCustomerID() const { return customer.getCustomerID(); } // Get customer ID from Customer object
int Rental::getVideoID() const { return video.getVideoID(); }          // Get video ID from Video object
int Rental::getDuration() const { return duration; }
string Rental::getRentalDate() const { return rentalDate; }
string Rental::getDueDate() const
{
  time_t now = time(0);
  now += Rental::getDuration() * 24 * 60 * 60; // Add duration days in seconds
  tm *ltm = localtime(&now);
  char date[20];
  strftime(date, sizeof(date), "%Y-%m-%d", ltm);
  return string(date);
}
bool Rental::getIsReturned() const { return isReturned; }

// Setter
void Rental::setReturnStatus(bool status) { isReturned = status; }

// Display rental information
void Rental::displayRentalInfo() const
{
  cout << "Rental ID: " << rentalID << "\n"
       << "Customer ID: " << customer.getCustomerID() << "\n"
       << "Video ID: " << video.getVideoID() << "\n"
       << "Rental Date: " << rentalDate << "\n"
       << "Due Date: " << dueDate << "\n"
       << "Returned: " << (isReturned ? "Yes" : "No") << endl;
}
