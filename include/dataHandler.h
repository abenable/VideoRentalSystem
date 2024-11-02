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
    bool addCustomer(const string &name, const string &address, const string &phone);
    bool editCustomer(int customerID, const string &name, const string &address, const string &phone);
    bool deleteCustomer(int customerID);
    vector<Customer> getAllCustomers() const;

    // Video Management
    bool addVideo(const string &title, const string &genre, int releaseYear, double rentalPrice, bool isAvailable);
    bool editVideo(int videoID, const string &title, const string &genre, int releaseYear, double rentalPrice, bool isAvailable);
    bool deleteVideo(int videoID);

    // Rental Management
    bool addRental(int customerID, int videoID, int duration);
    bool returnRental(int rentalID);
};

#endif
