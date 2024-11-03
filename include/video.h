#ifndef VIDEO_H
#define VIDEO_H

#include <string>
using namespace std;

class Video
{
private:
    int videoID;
    string title;
    double rentalPrice;
    bool isAvailable;

public:
    // Constructor
    Video(int id, const string &title, double price, bool available = true);

    // Getters
    int getVideoID() const;
    string getTitle() const;
    double getRentalPrice() const;
    bool getAvailability() const;

    // Setters
    void setTitle(const string &title);
    void setRentalPrice(double price);
    void setAvailability(bool available);

    // Display video info
    void displayVideoInfo() const;
};

#endif // VIDEO_H
