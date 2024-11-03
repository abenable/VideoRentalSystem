#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <string>
#include <vector>

#include "customer.h"
#include "video.h"
#include "rental.h"

using namespace std;

class DataHandler
{
private:
    string customerFile;
    string videoFile;
    string rentalFile;

    vector<string> splitCSVLine(const string &line, char delimiter) const;
    void removeLineFromFile(const string &filename, const string &lineID) const;

public:
    DataHandler(const string &customerFile, const string &videoFile, const string &rentalFile);

    // Customer Management
    bool addCustomer(Customer &customer);
    bool editCustomer(Customer &customer);
    bool deleteCustomer(int customerID);
    vector<Customer> getAllCustomers() const;

    // Video Management
    bool addVideo(const string &title, const string &genre, int releaseYear, double rentalPrice, bool isAvailable);
    bool editVideo(int videoID, const string &title, const string &genre, int releaseYear, double rentalPrice, bool isAvailable);
    bool deleteVideo(int videoID);
    vector<Video> getAllVideos() const;

    // Rental Management
    vector<Rental> getActiveRentals() const;
    vector<Rental> getReturnedRentals() const;
    vector<Rental> getOverdueRentals() const;
    vector<Customer> getCustomersWithOverdueRentals() const;
    bool addRental(const Customer &customer, const Video &video, int duration);
    bool returnRental(int rentalID);
};

#endif
