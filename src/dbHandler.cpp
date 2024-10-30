#include "../include/dbHandler.h"
#include <iostream>
#include <sstream> // For converting data types

using namespace std;

DatabaseHandler::DatabaseHandler(const std::string &dbName)
{
    if (sqlite3_open(dbName.c_str(), &db) == SQLITE_OK)
    {
        cout << "Database opened successfully.\n";
    }
    else
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << "\n";
        db = nullptr;
    }
}

DatabaseHandler::~DatabaseHandler()
{
    if (db)
    {
        sqlite3_close(db);
        cout << "Database connection closed.\n";
    }
}

bool DatabaseHandler::executeQuery(const std::string &query)
{
    char *errorMessage = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK)
    {
        cerr << "SQL Error: " << errorMessage << "\n";
        sqlite3_free(errorMessage);
        return false;
    }
    return true;
}

bool DatabaseHandler::createTables()
{
    const std::string customerTable = R"(CREATE TABLE IF NOT EXISTS Customers (
                                         customerID INTEGER PRIMARY KEY AUTOINCREMENT,
                                         name TEXT NOT NULL,
                                         address TEXT,
                                         phone TEXT,
                                         email TEXT,
                                         isPremiumMember INTEGER
                                      );)";

    const std::string videoTable = R"(CREATE TABLE IF NOT EXISTS Videos (
                                         videoID INTEGER PRIMARY KEY AUTOINCREMENT,
                                         title TEXT NOT NULL,
                                         genre TEXT,
                                         releaseYear INTEGER,
                                         rentalPrice REAL,
                                         availabilityStatus INTEGER
                                      );)";

    return executeQuery(customerTable) && executeQuery(videoTable);
}

bool DatabaseHandler::isConnected() const
{
    return db != nullptr;
}

// Add a new customer to the database
bool DatabaseHandler::addCustomer(const std::string &name, const std::string &address,
                                  const std::string &phone, const std::string &email, bool isPremiumMember)
{
    std::stringstream query;
    query << "INSERT INTO Customers (name, address, phone, email, isPremiumMember) VALUES ('"
          << name << "', '" << address << "', '" << phone << "', '" << email << "', "
          << (isPremiumMember ? 1 : 0) << ");";
    return executeQuery(query.str());
}

// Edit an existing customer's information
bool DatabaseHandler::editCustomer(int customerID, const std::string &name, const std::string &address,
                                   const std::string &phone, const std::string &email, bool isPremiumMember)
{
    std::stringstream query;
    query << "UPDATE Customers SET name='" << name << "', address='" << address
          << "', phone='" << phone << "', email='" << email << "', isPremiumMember="
          << (isPremiumMember ? 1 : 0) << " WHERE customerID=" << customerID << ";";
    return executeQuery(query.str());
}

// Delete a customer by ID
bool DatabaseHandler::deleteCustomer(int customerID)
{
    std::stringstream query;
    query << "DELETE FROM Customers WHERE customerID=" << customerID << ";";
    return executeQuery(query.str());
}

// Retrieve and display customer info by ID
void DatabaseHandler::getCustomerByID(int customerID) const
{
    std::stringstream query;
    query << "SELECT * FROM Customers WHERE customerID=" << customerID << ";";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to retrieve customer: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        const unsigned char *address = sqlite3_column_text(stmt, 2);
        const unsigned char *phone = sqlite3_column_text(stmt, 3);
        const unsigned char *email = sqlite3_column_text(stmt, 4);
        bool isPremium = sqlite3_column_int(stmt, 5) == 1;

        cout << "Customer ID: " << id << "\n"
             << "Name: " << name << "\n"
             << "Address: " << address << "\n"
             << "Phone: " << phone << "\n"
             << "Email: " << email << "\n"
             << "Premium Member: " << (isPremium ? "Yes" : "No") << "\n";
    }
    else
    {
        cout << "Customer not found.\n";
    }

    sqlite3_finalize(stmt);
}

// Add a new video to the database
bool DatabaseHandler::addVideo(const std::string &title, const std::string &genre, int releaseYear,
                               double rentalPrice, bool isAvailable)
{
    std::stringstream query;
    query << "INSERT INTO Videos (title, genre, releaseYear, rentalPrice, availabilityStatus) VALUES ('"
          << title << "', '" << genre << "', " << releaseYear << ", " << rentalPrice << ", "
          << (isAvailable ? 1 : 0) << ");";
    return executeQuery(query.str());
}

// Edit an existing video's information
bool DatabaseHandler::editVideo(int videoID, const std::string &title, const std::string &genre,
                                int releaseYear, double rentalPrice, bool isAvailable)
{
    std::stringstream query;
    query << "UPDATE Videos SET title='" << title << "', genre='" << genre
          << "', releaseYear=" << releaseYear << ", rentalPrice=" << rentalPrice
          << ", availabilityStatus=" << (isAvailable ? 1 : 0) << " WHERE videoID=" << videoID << ";";
    return executeQuery(query.str());
}

// Delete a video by ID
bool DatabaseHandler::deleteVideo(int videoID)
{
    std::stringstream query;
    query << "DELETE FROM Videos WHERE videoID=" << videoID << ";";
    return executeQuery(query.str());
}

// Retrieve and display video info by ID
void DatabaseHandler::getVideoByID(int videoID) const
{
    std::stringstream query;
    query << "SELECT * FROM Videos WHERE videoID=" << videoID << ";";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to retrieve video: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *title = sqlite3_column_text(stmt, 1);
        const unsigned char *genre = sqlite3_column_text(stmt, 2);
        int releaseYear = sqlite3_column_int(stmt, 3);
        double rentalPrice = sqlite3_column_double(stmt, 4);
        bool isAvailable = sqlite3_column_int(stmt, 5) == 1;

        cout << "Video ID: " << id << "\n"
             << "Title: " << title << "\n"
             << "Genre: " << genre << "\n"
             << "Release Year: " << releaseYear << "\n"
             << "Rental Price: $" << rentalPrice << "\n"
             << "Availability: " << (isAvailable ? "Available" : "Rented") << "\n";
    }
    else
    {
        cout << "Video not found.\n";
    }

    sqlite3_finalize(stmt);
}

// Add a new rental to the database
bool DatabaseHandler::addRental(int customerID, int videoID, const std::string &rentalDate, const std::string &dueDate)
{
    std::stringstream query;
    query << "INSERT INTO Rentals (customerID, videoID, rentalDate, dueDate, returnStatus) VALUES ("
          << customerID << ", " << videoID << ", '" << rentalDate << "', '" << dueDate << "', 0);";
    return executeQuery(query.str());
}

// Mark a rental as returned
bool DatabaseHandler::returnRental(int rentalID)
{
    std::stringstream query;
    query << "UPDATE Rentals SET returnStatus=1 WHERE rentalID=" << rentalID << ";";
    return executeQuery(query.str());
}

// Retrieve and display rental info by ID
void DatabaseHandler::getRentalByID(int rentalID) const
{
    std::stringstream query;
    query << "SELECT * FROM Rentals WHERE rentalID=" << rentalID << ";";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to retrieve rental: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        int custID = sqlite3_column_int(stmt, 1);
        int vidID = sqlite3_column_int(stmt, 2);
        const unsigned char *rentalDate = sqlite3_column_text(stmt, 3);
        const unsigned char *dueDate = sqlite3_column_text(stmt, 4);
        bool returnStatus = sqlite3_column_int(stmt, 5) == 1;

        cout << "Rental ID: " << id << "\n"
             << "Customer ID: " << custID << "\n"
             << "Video ID: " << vidID << "\n"
             << "Rental Date: " << rentalDate << "\n"
             << "Due Date: " << dueDate << "\n"
             << "Return Status: " << (returnStatus ? "Returned" : "Not Returned") << "\n";
    }
    else
    {
        cout << "Rental not found.\n";
    }

    sqlite3_finalize(stmt);
}

// You can add more methods as needed...
