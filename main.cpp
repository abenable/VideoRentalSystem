#include <iostream>
#include <vector>
#include <string>

#include "include/dataHandler.h"

using namespace std;

// Main menu display function
void displayMenu()
{
    cout << "======================================" << endl;
    cout << "       Welcome to Video Rental        " << endl;
    cout << "======================================" << endl;
    cout << "Main Menu Options:" << endl;
    cout << "1. Rent a Video" << endl;
    cout << "2. Return a Video" << endl;
    cout << "3. Manage Customers" << endl;
    cout << "4. Manage Videos" << endl;
    cout << "5. View Records" << endl;
    cout << "6. Exit" << endl;
    cout << "======================================" << endl;
    cout << "Choose an option: ";
}

// Display Customer Management submenu
void displayCustomerMenu()
{
    cout << "======================================" << endl;
    cout << "       Customer Management Menu       " << endl;
    cout << "======================================" << endl;
    cout << "1. View All Customers" << endl;
    cout << "2. Add Customer" << endl;
    cout << "3. Update Customer" << endl;
    cout << "4. Delete Customer" << endl;
    cout << "5. Customer Rental History" << endl;
    cout << "6. Return to Main Menu" << endl;
    cout << "======================================" << endl;
    cout << "Enter your choice: ";
}

// Display Video Management submenu
void displayVideoMenu()
{
    cout << "======================================" << endl;
    cout << "         Video Management Menu        " << endl;
    cout << "======================================" << endl;
    cout << "1. View All Videos" << endl;
    cout << "2. Add New Video" << endl;
    cout << "3. Update Video Info" << endl;
    cout << "4. Delete Video" << endl;
    cout << "5. Return to Main Menu" << endl;
    cout << "======================================" << endl;
    cout << "Enter your choice: ";
}

// Display Records Management submenu
void displayRecordsMenu()
{
    cout << "======================================" << endl;
    cout << "             Records Menu             " << endl;
    cout << "======================================" << endl;
    cout << "1. Active Rentals" << endl;
    cout << "2. Overdue Rentals" << endl;
    cout << "3. Returned Rentals" << endl;
    cout << "4. Customers with Overdue Rentals" << endl;
    cout << "5. Return to Main Menu" << endl;
    cout << "======================================" << endl;
    cout << "Enter your choice: ";
}

// Rent a video
void rentVideo(DataHandler &dbHandler)
{
    int customerID, videoID, duration;

    cout << "Renting a Video." << endl;
    cout << "\nEnter customer ID: ";
    cin >> customerID;
    cout << "Enter video ID: ";
    cin >> videoID;
    cout << "Enter rental duration (days): ";
    cin >> duration;

    if (dbHandler.addRental(customerID, videoID, duration))
    {
        cout << "Rental added successfully.\n";
    }
    else
    {
        cout << "Failed to add rental.\n";
    }
}

// Return a video
void returnVideo(DataHandler &dbHandler)
{
    int rentalID;
    cout << "\nEnter rental ID to return: ";
    cin >> rentalID;

    if (dbHandler.returnRental(rentalID))
    {
        cout << "Rental marked as returned.\n";
    }
    else
    {
        cout << "Failed to update return status.\n";
    }
}

// Add a customer
void addCustomer(DataHandler &dbHandler)
{
    string name, address, phone;
    cout << "\nEnter customer name: ";
    cin.ignore(); // Clear newline from input buffer
    getline(cin, name);
    cout << "Enter address: ";
    getline(cin, address);
    cout << "Enter phone: ";
    getline(cin, phone);

    if (dbHandler.addCustomer(name, address, phone))
    {
        cout << "Customer added successfully.\n";
    }
    else
    {
        cout << "Failed to add customer.\n";
    }
}

// View all customers
void viewAllCustomers(DataHandler &dbHandler)
{
    vector<Customer> customers = dbHandler.getAllCustomers();
    if (customers.empty())
    {
        cout << "No registered customers found.\n";
    }
    else
    {
        cout << "Registered Customers:\n";
        for (const auto &customer : customers)
        {
            cout << "Customer ID: " << customer.getCustomerID() << "\n"
                 << "Name: " << customer.getName() << "\n"
                 << "Phone: " << customer.getPhone() << "\n\n";
        }
    }
}

// Manage customers submenu
void manageCustomers(DataHandler &dbHandler)
{
    int customerChoice;

    while (true)
    {
        displayCustomerMenu();
        cin >> customerChoice;

        switch (customerChoice)
        {
        case 1:
            viewAllCustomers(dbHandler);
            break;
        case 2:
            addCustomer(dbHandler);
            break;
        // Implement update and delete functionality as needed
        case 6:
            return; // Exit to the main menu
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

// Add a video
void addVideo(DataHandler &dbHandler)
{
    string title, genre;
    int releaseYear;
    double rentalPrice;
    cout << "\nEnter video title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter genre: ";
    getline(cin, genre);
    cout << "Enter release year: ";
    cin >> releaseYear;
    cout << "Enter rental price: ";
    cin >> rentalPrice;

    if (dbHandler.addVideo(title, genre, releaseYear, rentalPrice, true))
    {
        cout << "Video added successfully.\n";
    }
    else
    {
        cout << "Failed to add video.\n";
    }
}

// Manage videos submenu
void manageVideos(DataHandler &dbHandler)
{
    int videoChoice;

    while (true)
    {
        displayVideoMenu();
        cin >> videoChoice;

        switch (videoChoice)
        {
        case 1:
            // Implement video viewing logic here
            break;
        case 2:
            addVideo(dbHandler);
            break;
        // Implement update and delete functionality as needed
        case 5:
            return; // Exit to the main menu
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

// View records submenu
void viewRecords(DataHandler &dbHandler)
{
    int recordsChoice;
    while (true)
    {
        displayRecordsMenu();
        cin >> recordsChoice;

        switch (recordsChoice)
        {
        case 1:
            // Implement logic to display active rentals
            cout << "Displaying active rentals..." << endl;
            break;
        case 5:
            cout << "Returning to main menu..." << endl;
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main()
{
    DataHandler dbHandler("customers.csv", "videos.csv", "rentals.csv");

    int choice;

    while (true)
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            rentVideo(dbHandler);
            break;
        case 2:
            returnVideo(dbHandler);
            break;
        case 3:
            manageCustomers(dbHandler);
            break;
        case 4:
            manageVideos(dbHandler);
            break;
        case 5:
            viewRecords(dbHandler);
            break;
        case 6:
            cout << "Exiting program. Thank you!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}
