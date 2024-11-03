#include "../include/dataHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

DataHandler::DataHandler(const string &customerFile, const string &videoFile, const string &rentalFile)
    : customerFile(customerFile), videoFile(videoFile), rentalFile(rentalFile) {}

// Helper function to split a CSV line
vector<string> DataHandler::splitCSVLine(const string &line, char delimiter) const
{
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

// Helper function to remove a line with a specific ID from a file
void DataHandler::removeLineFromFile(const string &filename, const string &lineID) const
{
    ifstream infile(filename);
    ofstream tempFile("temp.csv");
    string line;

    while (getline(infile, line))
    {
        if (line.find(lineID + ",") != 0)
        {
            tempFile << line << endl;
        }
    }
    infile.close();
    tempFile.close();
    remove(filename.c_str());
    rename("temp.csv", filename.c_str());
}

// Customer functions

bool DataHandler::addCustomer(const string &name, const string &address, const string &phone)
{
    ofstream file(customerFile, ios::app);
    if (!file)
        return false;

    int customerID = rand() % 1000 + 1; // Simple random ID generator
    file << customerID << "," << name << "," << address << "," << phone << endl;
    return true;
}

bool DataHandler::editCustomer(int customerID, const string &name, const string &address, const string &phone)
{
    removeLineFromFile(customerFile, to_string(customerID));
    return addCustomer(name, address, phone);
}

bool DataHandler::deleteCustomer(int customerID)
{
    removeLineFromFile(customerFile, to_string(customerID));
    return true;
}

vector<Customer> DataHandler::getAllCustomers() const
{
    vector<Customer> customers;
    ifstream file(customerFile);
    string line;

    while (getline(file, line))
    {
        auto data = splitCSVLine(line, ',');
        if (data.size() >= 4)
        {
            customers.emplace_back(stoi(data[0]), data[1], data[2], data[3]);
        }
    }
    return customers;
}

// Video functions

bool DataHandler::addVideo(const string &title, const string &genre, int releaseYear, double rentalPrice, bool isAvailable)
{
    ofstream file(videoFile, ios::app);
    if (!file)
        return false;

    int videoID = rand() % 1000 + 1; // Simple random ID generator
    file << videoID << "," << title << "," << genre << "," << releaseYear << ","
         << rentalPrice << "," << (isAvailable ? "1" : "0") << endl;
    return true;
}

bool DataHandler::editVideo(int videoID, const string &title, const string &genre, int releaseYear, double rentalPrice, bool isAvailable)
{
    removeLineFromFile(videoFile, to_string(videoID));
    ofstream file(videoFile, ios::app);
    if (!file)
        return false;

    file << videoID << "," << title << "," << genre << "," << releaseYear << ","
         << rentalPrice << "," << (isAvailable ? "1" : "0") << endl;
    return true;
}

bool DataHandler::deleteVideo(int videoID)
{
    removeLineFromFile(videoFile, to_string(videoID));
    return true;
}

// Rental functions

bool DataHandler::addRental(int customerID, int videoID, int duration)
{
    ofstream file(rentalFile, ios::app);
    if (!file)
        return false;

    // Get the current date
    time_t now = time(0);
    tm *rentalDate = localtime(&now);

    // Format the current date as YYYY-MM-DD for the rental date
    stringstream rentalDateStream;
    rentalDateStream << 1900 + rentalDate->tm_year << "-"
                     << setw(2) << setfill('0') << 1 + rentalDate->tm_mon << "-"
                     << setw(2) << setfill('0') << rentalDate->tm_mday;

    // Calculate the due date by adding the duration to the rental date
    rentalDate->tm_mday += duration;
    mktime(rentalDate); // Normalize the date structure if month/day overflows

    // Format the due date as YYYY-MM-DD
    stringstream dueDateStream;
    dueDateStream << 1900 + rentalDate->tm_year << "-"
                  << setw(2) << setfill('0') << 1 + rentalDate->tm_mon << "-"
                  << setw(2) << setfill('0') << rentalDate->tm_mday;

    // Construct the CSV entry
    int rentalID = rand() % 1000 + 1; // Simple random ID generator
    file << rentalID << "," << customerID << "," << videoID << ","
         << rentalDateStream.str() << "," << dueDateStream.str() << ",0" << endl;
    return true;
}
vector<Rental> DataHandler::getActiveRentals() const
{
    vector<Rental> activeRentals;
    ifstream file(rentalFile);
    string line;

    while (getline(file, line))
    {
        auto data = splitCSVLine(line, ',');
        if (data.size() >= 6 && data[5] == "0") // Check if the rental is not returned
        {
            activeRentals.emplace_back(stoi(data[0]), stoi(data[1]), stoi(data[2]), data[3], data[4], false);
        }
    }
    return activeRentals;
}
vector<Rental> DataHandler::getOverdueRentals() const
{
    vector<Rental> overdueRentals;
    ifstream file(rentalFile);
    string line;

    // Get the current date
    time_t now = time(0);
    tm *currentDate = localtime(&now);

    while (getline(file, line))
    {
        auto data = splitCSVLine(line, ',');
        if (data.size() >= 6 && data[5] == "0") // Check if the rental is not returned
        {
            // Parse the due date from the file
            tm dueDate = {};
            stringstream ss(data[4]);
            ss >> get_time(&dueDate, "%Y-%m-%d");

            // Compare the due date with the current date
            if (mktime(&dueDate) < now)
            {
                overdueRentals.emplace_back(stoi(data[0]), stoi(data[1]), stoi(data[2]), data[3], data[4], false);
            }
        }
    }
    return overdueRentals;
}
vector<Rental> DataHandler::getReturnedRentals() const
{
    vector<Rental> returnedRentals;
    ifstream file(rentalFile);
    string line;

    while (getline(file, line))
    {
        auto data = splitCSVLine(line, ',');
        if (data.size() >= 6 && data[5] == "1") // Check if the rental is returned
        {
            returnedRentals.emplace_back(stoi(data[0]), stoi(data[1]), stoi(data[2]), data[3], data[4], true);
        }
    }
    return returnedRentals;
}

bool DataHandler::returnRental(int rentalID)
{
    // Assuming we mark the rental as returned in the file
    ifstream infile(rentalFile);
    ofstream tempFile("temp.csv");
    string line;

    while (getline(infile, line))
    {
        auto data = splitCSVLine(line, ',');
        if (data.size() >= 6 && stoi(data[0]) == rentalID)
        {
            data[5] = "1"; // Mark as returned
            tempFile << data[0] << "," << data[1] << "," << data[2] << ","
                     << data[3] << "," << data[4] << "," << data[5] << endl;
        }
        else
        {
            tempFile << line << endl;
        }
    }
    infile.close();
    tempFile.close();
    remove(rentalFile.c_str());
    rename("temp.csv", rentalFile.c_str());

    return true;
}

vector<Customer> DataHandler::getCustomersWithOverdueRentals() const
{
    vector<Customer> customersWithOverdueRentals;
    auto overdueRentals = getOverdueRentals();
    auto allCustomers = getAllCustomers();

    for (const auto &rental : overdueRentals)
    {
        for (const auto &customer : allCustomers)
        {
            if (customer.getCustomerID() == rental.getCustomerID())
            {
                customersWithOverdueRentals.push_back(customer);
                break;
            }
        }
    }

    return customersWithOverdueRentals;
}
