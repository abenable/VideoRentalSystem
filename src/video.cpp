#include "video.h"
#include <iostream>

using namespace std; // Add this line

// Constructor implementation
Video::Video(int id, const std::string &title, const std::string &genre, int year, double price, bool available)
    : videoID(id), title(title), genre(genre), releaseYear(year), rentalPrice(price), isAvailable(available) {}

// Getters
int Video::getVideoID() const { return videoID; }
string Video::getTitle() const { return title; }
string Video::getGenre() const { return genre; }
int Video::getReleaseYear() const { return releaseYear; }
double Video::getRentalPrice() const { return rentalPrice; }
bool Video::getAvailability() const { return isAvailable; }

// Setters
void Video::setTitle(const string &title) { this->title = title; }
void Video::setGenre(const string &genre) { this->genre = genre; }
void Video::setReleaseYear(int year) { releaseYear = year; }
void Video::setRentalPrice(double price) { rentalPrice = price; }
void Video::setAvailability(bool available) { isAvailable = available; }

// Display video information
void Video::displayVideoInfo() const
{
    cout << "Video ID: " << videoID << "\n"
         << "Title: " << title << "\n"
         << "Genre: " << genre << "\n"
         << "Release Year: " << releaseYear << "\n"
         << "Rental Price: $" << rentalPrice << "\n"
         << "Availability: " << (isAvailable ? "Available" : "Rented") << endl;
}
