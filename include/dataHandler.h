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
    Customer *getCustomerByID(int customerID) const;
    vector<Customer> getAllCustomers() const;

    // Video Management
    bool addVideo(Video &video);
    bool editVideo(Video &video);
    bool deleteVideo(int videoID);
    Video *getVideoByID(int videoID) const;
    vector<Video> getAllVideos() const;

    // Rental management
    bool addRental(Rental &rental);
    bool returnRental(int rentalID);
    vector<Rental> getActiveRentals() const;
    vector<Rental> getOverdueRentals() const;
    vector<Rental> getReturnedRentals() const;
    vector<Customer> customersWithOverdueRentals() const;
};

#endif
