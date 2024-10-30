#ifndef VIDEO_H
#define VIDEO_H

#include <string>
using namespace std;

class Video
{
private:
    int videoID;
    string title;
    string genre;
    int releaseYear;
    double rentalPrice;
    bool isAvailable;

public:
    // Constructor
    Video(int id, const string &title, const string &genre, int year, double price, bool available = true);

    // Getters
    int getVideoID() const;
    string getTitle() const;
    string getGenre() const;
    int getReleaseYear() const;
    double getRentalPrice() const;
    bool getAvailability() const;

    // Setters
    void setTitle(const string &title);
    void setGenre(const string &genre);
    void setReleaseYear(int year);
    void setRentalPrice(double price);
    void setAvailability(bool available);

    // Display video info
    void displayVideoInfo() const;
};

#endif // VIDEO_H
