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

bool DataHandler::addCustomer(Customer &customer)
{
    ofstream file(customerFile, ios::app);
    if (!file)
        return false;

    file << customer.getCustomerID() << "," << customer.getName() << "," << customer.getAddress() << "," << customer.getPhone() << endl;
    return true;
}

bool DataHandler::editCustomer(Customer &customer)
{
    removeLineFromFile(customerFile, to_string(customer.getCustomerID()));
    return addCustomer(customer);
}

bool DataHandler::deleteCustomer(int customerID)
{
    removeLineFromFile(customerFile, to_string(customerID));
    return true;
}
Customer *DataHandler::getCustomerByID(int customerID) const
{
    ifstream file(customerFile);
    string line;

    while (getline(file, line))
    {
        auto data = splitCSVLine(line, ',');
        if (data.size() >= 4)
        {
            int id = stoi(data[0]);
            if (id == customerID)
            {
                string name = data[1];
                string address = data[2];
                string phone = data[3];
                return new Customer(id, name, address, phone);
            }
        }
    }
    return nullptr;
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

bool DataHandler::addVideo(Video &video)
{
    ofstream file(videoFile, ios::app);
    if (!file)
        return false;

    file << video.getVideoID() << "," << video.getTitle() << "," << video.getPrice() << "," << video.getAvailability() << endl;
    return true;
}

bool DataHandler::editVideo(Video &video)
{
    removeLineFromFile(videoFile, to_string(video.getVideoID()));
    return addVideo(video);
}

bool DataHandler::deleteVideo(int videoID)
{
    removeLineFromFile(videoFile, to_string(videoID));
    return true;
}
Video *DataHandler::getVideoByID(int videoID) const
{
    ifstream file(videoFile);
    string line;

    while (getline(file, line))
    {
        auto data = splitCSVLine(line, ',');
        if (data.size() >= 4)
        {
            int id = stoi(data[0]);
            if (id == videoID)
            {
                string title = data[1];
                double price = stod(data[2]);
                bool available = (data[3] == "true" || data[3] == "1");
                return new Video(id, title, price, available);
            }
        }
    }
    return nullptr;
}

vector<Video> DataHandler::getAllVideos() const
{
    vector<Video> videos;
    ifstream file(videoFile);
    string line;

    while (getline(file, line))
    {
        auto data = splitCSVLine(line, ',');
        if (data.size() >= 4)
        {
            int id = stoi(data[0]);
            string title = data[1];
            double price = stod(data[2]);
            bool available = (data[3] == "true" || data[3] == "1");

            videos.emplace_back(id, title, price, available);
        }
    }
    return videos;
}

// Rentals functions
bool DataHandler::addRental(Rental &rental)
{
    ofstream file(rentalFile, ios::app);
    if (!file)
        return false;

    // Construct the CSV entry
    int rentalID = rand() % 1000 + 1; // Simple random ID generator
    file << rentalID << "," << rental.getCustomerID() << "," << rental.getVideoID() << ","
         << rental.getRentalDate() << "," << rental.getDueDate() << "," << rental.getDuration() << ",0" << endl;
    return true;
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

vector<Rental> DataHandler::getActiveRentals() const
{
    vector<Rental> activeRentals;
    ifstream file(rentalFile);
    string line;

    while (getline(file, line))
    {
        auto data = splitCSVLine(line, ',');
        if (data.size() >= 7 && data[6] == "0") // Check if the rental is not returned
        {
            int rentalID = stoi(data[0]);
            int customerID = stoi(data[1]);
            int videoID = stoi(data[2]);
            int duration = stoi(data[5]);
            string rentalDate = data[3];
            string dueDate = data[4];
            bool returned = false;

            // Assuming you have a way to get Customer* and Video* from their IDs
            const Customer *customer = getCustomerByID(customerID);
            const Video *video = getVideoByID(videoID);
            if (customer != nullptr && video != nullptr)
            {
                activeRentals.emplace_back(rentalID, customer, video, duration, returned);
            }
        }
    }
    return activeRentals;
}
vector<Rental> DataHandler::getOverdueRentals() const
{
    vector<Rental> overdueRentals;
    ifstream file(rentalFile);
    string line;

    // Get the current date as time_t for comparison
    time_t now = time(0);

    while (getline(file, line))
    {
        auto data = splitCSVLine(line, ',');
        if (data.size() >= 6 && data[5] == "0") // Check if the rental is not returned
        {
            // Create a Rental object using data from the CSV
            Rental rental(stoi(data[0]), getCustomerByID(stoi(data[1])), getVideoByID(stoi(data[2])),
                          stoi(data[4]), false);

            // Convert rental's due date to time_t for comparison
            std::tm dueDate = {};
            std::istringstream ss(rental.getDueDate());
            ss >> std::get_time(&dueDate, "%Y-%m-%d");
            time_t dueDateTime = mktime(&dueDate);

            // Check if the due date has passed
            if (dueDateTime < now)
            {
                overdueRentals.push_back(rental);
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
            // Fetch Customer and Video pointers using their IDs
            const Customer *customer = getCustomerByID(stoi(data[1]));
            const Video *video = getVideoByID(stoi(data[2]));
            int duration = stoi(data[4]);

            // Create Rental object and add it to the returnedRentals vector
            returnedRentals.emplace_back(stoi(data[0]), customer, video, duration, true);
        }
    }
    return returnedRentals;
}

vector<Customer> DataHandler::customersWithOverdueRentals() const
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