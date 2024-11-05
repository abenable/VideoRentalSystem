#include "../include/video.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor implementation
Video::Video(int id, string &title, double price, bool available)
    : videoID(id), title(title), price(price), isAvailable(available) {}

// Getters
int Video::getVideoID() const { return videoID; }
string Video::getTitle() const { return title; }
double Video::getPrice() const { return price; }

bool Video::getAvailability() const { return isAvailable; }

// Setters
void Video::setTitle(const string &title) { this->title = title; }
void Video::setPrice(double price) { price = price; }
void Video::setAvailability(bool available) { isAvailable = available; }

// Display video information
void Video::displayVideoInfo() const
{
    cout << "Video ID: " << videoID << "\n"
         << "Title: " << title << "\n"
         << "Rental Price: $" << price << "\n"
         << "Availability: " << (isAvailable ? "Available" : "Rented") << endl;
}
