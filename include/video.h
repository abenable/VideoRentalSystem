#ifndef VIDEO_H
#define VIDEO_H

#include <string>
using namespace std;

class Video
{
private:
    int videoID;
    string title;
    double price;
    bool isAvailable;

public:
    // Constructor
    Video(int id, string &title, double price, bool available = true);

    // Getters
    int getVideoID() const;
    string getTitle() const;
    double getPrice() const;
    bool getAvailability() const;

    // Setters
    void setTitle(const string &title);
    void setPrice(double price);
    void setAvailability(bool available);

    // Display video info
    void displayVideoInfo() const;
};

#endif // VIDEO_H
