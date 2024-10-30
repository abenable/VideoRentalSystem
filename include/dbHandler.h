#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <sqlite3.h>
#include "customer.h"
#include <string>
#include <vector>

using namespace std;

class DatabaseHandler
{
private:
    sqlite3 *db;

public:
    // Constructor and Destructor
    DatabaseHandler(const string &dbName);
    ~DatabaseHandler();

    // Database operations
    bool executeQuery(const string &query);
    bool createTables();
    bool isConnected() const;

    // Customer management
    bool addCustomer(const string &name, const string &address, const string &phone,
                     const string &email, bool isPremiumMember);
    bool editCustomer(int customerID, const string &name, const string &address,
                      const string &phone, const string &email, bool isPremiumMember);
    bool deleteCustomer(int customerID);
    void getCustomerByID(int customerID) const;
    vector<Customer> getAllCustomers() const;

    // Video management
    bool addVideo(const string &title, const string &genre, int releaseYear,
                  double rentalPrice, bool isAvailable);
    bool editVideo(int videoID, const string &title, const string &genre,
                   int releaseYear, double rentalPrice, bool isAvailable);
    bool deleteVideo(int videoID);
    void getVideoByID(int videoID) const;

    // Rental management
    bool addRental(int customerID, int videoID, const string &rentalDate, const string &dueDate);
    bool returnRental(int rentalID);
    void getRentalByID(int rentalID) const;
};

#endif // DBHANDLER_H
