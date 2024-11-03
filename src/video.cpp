#include "../include/video.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor implementation
Video::Video(int id, const string &title, double price, bool available)
    : videoID(id), title(title), rentalPrice(price), isAvailable(available) {}

// Getters
int Video::getVideoID() const { return videoID; }
string Video::getTitle() const { return title; }
double Video::getRentalPrice() const { return rentalPrice; }
bool Video::getAvailability() const { return isAvailable; }

// Setters
void Video::setTitle(const string &title) { this->title = title; }
void Video::setRentalPrice(double price) { rentalPrice = price; }
void Video::setAvailability(bool available) { isAvailable = available; }

// Display video information
void Video::displayVideoInfo() const
{
    cout << "Video ID: " << videoID << "\n"
         << "Title: " << title << "\n"
         << "Rental Price: $" << rentalPrice << "\n"
         << "Availability: " << (isAvailable ? "Available" : "Rented") << endl;
}
