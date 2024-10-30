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

bool DatabaseHandler::addCustomer(const std::string &name, const std::string &address,
                                  const std::string &phone, const std::string &email, bool isPremiumMember)
{
    std::stringstream query;
    query << "INSERT INTO Customers (name, address, phone, email, isPremiumMember) VALUES ('"
          << name << "', '" << address << "', '" << phone << "', '" << email << "', "
          << (isPremiumMember ? 1 : 0) << ");";
    return executeQuery(query.str());
}

bool DatabaseHandler::editCustomer(int customerID, const std::string &name, const std::string &address,
                                   const std::string &phone, const std::string &email, bool isPremiumMember)
{
    std::stringstream query;
    query << "UPDATE Customers SET name='" << name << "', address='" << address
          << "', phone='" << phone << "', email='" << email << "', isPremiumMember="
          << (isPremiumMember ? 1 : 0) << " WHERE customerID=" << customerID << ";";
    return executeQuery(query.str());
}

bool DatabaseHandler::deleteCustomer(int customerID)
{
    std::stringstream query;
    query << "DELETE FROM Customers WHERE customerID=" << customerID << ";";
    return executeQuery(query.str());
}

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
        cout << "Customer ID: " << sqlite3_column_int(stmt, 0) << "\n"
             << "Name: " << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)) << "\n"
             << "Address: " << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)) << "\n"
             << "Phone: " << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)) << "\n"
             << "Email: " << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)) << "\n"
             << "Premium Member: " << (sqlite3_column_int(stmt, 5) == 1 ? "Yes" : "No") << "\n";
    }
    else
    {
        cout << "Customer not found.\n";
    }

    sqlite3_finalize(stmt);
}

vector<Customer> DatabaseHandler::getAllCustomers() const
{
    vector<Customer> customers;
    sqlite3_stmt *stmt;

    const char *sql = "SELECT customerID, name, email, phone FROM Customers"; // Ensure table name is capitalized to match the creation
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return customers;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int customerID = sqlite3_column_int(stmt, 0);
        const char *name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        const char *email = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        const char *phone = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

        // Create a Customer object and add it to the vector
        customers.emplace_back(customerID, name, email, phone);
    }

    sqlite3_finalize(stmt);
    return customers;
}

bool DatabaseHandler::addVideo(const std::string &title, const std::string &genre, int releaseYear,
                               double rentalPrice, bool isAvailable)
{
    std::stringstream query;
    query << "INSERT INTO Videos (title, genre, releaseYear, rentalPrice, availabilityStatus) VALUES ('"
          << title << "', '" << genre << "', " << releaseYear << ", " << rentalPrice << ", "
          << (isAvailable ? 1 : 0) << ");";
    return executeQuery(query.str());
}

bool DatabaseHandler::editVideo(int videoID, const std::string &title, const std::string &genre,
                                int releaseYear, double rentalPrice, bool isAvailable)
{
    std::stringstream query;
    query << "UPDATE Videos SET title='" << title << "', genre='" << genre
          << "', releaseYear=" << releaseYear << ", rentalPrice=" << rentalPrice
          << ", availabilityStatus=" << (isAvailable ? 1 : 0) << " WHERE videoID=" << videoID << ";";
    return executeQuery(query.str());
}

bool DatabaseHandler::deleteVideo(int videoID)
{
    std::stringstream query;
    query << "DELETE FROM Videos WHERE videoID=" << videoID << ";";
    return executeQuery(query.str());
}

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
        cout << "Video ID: " << sqlite3_column_int(stmt, 0) << "\n"
             << "Title: " << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)) << "\n"
             << "Genre: " << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)) << "\n"
             << "Release Year: " << sqlite3_column_int(stmt, 3) << "\n"
             << "Rental Price: $" << sqlite3_column_double(stmt, 4) << "\n"
             << "Availability: " << (sqlite3_column_int(stmt, 5) == 1 ? "Available" : "Rented") << "\n";
    }
    else
    {
        cout << "Video not found.\n";
    }

    sqlite3_finalize(stmt);
}

bool DatabaseHandler::addRental(int customerID, int videoID, const std::string &rentalDate, const std::string &dueDate)
{
    std::stringstream query;
    query << "INSERT INTO Rentals (customerID, videoID, rentalDate, dueDate, returnStatus) VALUES ("
          << customerID << ", " << videoID << ", '" << rentalDate << "', '" << dueDate << "', 0);";
    return executeQuery(query.str());
}

bool DatabaseHandler::returnRental(int rentalID)
{
    std::stringstream query;
    query << "UPDATE Rentals SET returnStatus=1 WHERE rentalID=" << rentalID << ";";
    return executeQuery(query.str());
}

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
        cout << "Rental ID: " << sqlite3_column_int(stmt, 0) << "\n"
             << "Customer ID: " << sqlite3_column_int(stmt, 1) << "\n"
             << "Video ID: " << sqlite3_column_int(stmt, 2) << "\n"
             << "Rental Date: " << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)) << "\n"
             << "Due Date: " << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)) << "\n"
             << "Returned: " << (sqlite3_column_int(stmt, 5) == 1 ? "Yes" : "No") << "\n";
    }
    else
    {
        cout << "Rental not found.\n";
    }

    sqlite3_finalize(stmt);
}
