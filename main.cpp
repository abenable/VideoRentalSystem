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
void rentVideo(DataHandler &dataHandler)
{
    int customerID, videoID, duration;

    cout << "Renting a Video." << endl;
    cout << "\nEnter customer ID: ";
    cin >> customerID;
    cout << "Enter video ID: ";
    cin >> videoID;
    cout << "Enter rental duration (days): ";
    cin >> duration;

    if (dataHandler.addRental(customerID, videoID, duration))
    {
        cout << "Rental added successfully.\n";
    }
    else
    {
        cout << "Failed to add rental.\n";
    }
}

// Return a video
void returnVideo(DataHandler &dataHandler)
{
    int rentalID;
    cout << "\nEnter rental ID to return: ";
    cin >> rentalID;

    if (dataHandler.returnRental(rentalID))
    {
        cout << "Rental marked as returned.\n";
    }
    else
    {
        cout << "Failed to update return status.\n";
    }
}

// Add a customer
void addCustomer(DataHandler &dataHandler)
{
    string name, address, phone;
    cout << "\nEnter customer name: ";
    cin.ignore(); // Clear newline from input buffer
    getline(cin, name);
    cout << "Enter address: ";
    getline(cin, address);
    cout << "Enter phone: ";
    getline(cin, phone);

    if (dataHandler.addCustomer(name, address, phone))
    {
        cout << "Customer added successfully.\n";
    }
    else
    {
        cout << "Failed to add customer.\n";
    }
}

// View all customers
void viewAllCustomers(DataHandler &dataHandler)
{
    vector<Customer> customers = dataHandler.getAllCustomers();
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

void displayActiveRentals(DataHandler &dataHandler)
{
    vector<Rental> activeRentals = dataHandler.getActiveRentals();
    if (activeRentals.empty())
    {
        cout << "No active rentals found.\n";
    }
    else
    {
        cout << "Active Rentals:\n";
        for (const auto &rental : activeRentals)
        {
            cout << "Rental ID: " << rental.getRentalID() << "\n"
                 << "Customer ID: " << rental.getCustomerID() << "\n"
                 << "Video ID: " << rental.getVideoID() << "\n"
                 << "Rental Date: " << rental.getRentalDate() << "\n"
                 << "Due Date: " << rental.getDueDate() << "\n\n";
        }
    }
}
// Display overdue rentals
void displayOverdueRentals(DataHandler &dataHandler)
{
    vector<Rental> overdueRentals = dataHandler.getOverdueRentals();
    if (overdueRentals.empty())
    {
        cout << "No overdue rentals found.\n";
    }
    else
    {
        cout << "Overdue Rentals:\n";
        for (const auto &rental : overdueRentals)
        {
            cout << "Rental ID: " << rental.getRentalID() << "\n"
                 << "Customer ID: " << rental.getCustomerID() << "\n"
                 << "Video ID: " << rental.getVideoID() << "\n"
                 << "Rental Date: " << rental.getRentalDate() << "\n"
                 << "Due Date: " << rental.getDueDate() << "\n\n";
        }
    }
}

// Display returned rentals
void displayReturnedRentals(DataHandler &dataHandler)
{
    vector<Rental> returnedRentals = dataHandler.getReturnedRentals();
    if (returnedRentals.empty())
    {
        cout << "No returned rentals found.\n";
    }
    else
    {
        cout << "Returned Rentals:\n";
        for (const auto &rental : returnedRentals)
        {
            cout << "Rental ID: " << rental.getRentalID() << "\n"
                 << "Customer ID: " << rental.getCustomerID() << "\n"
                 << "Video ID: " << rental.getVideoID() << "\n"
                 << "Rental Date: " << rental.getRentalDate() << "\n"
                 << "Return Date: " << rental.getDueDate() << "\n\n";
        }
    }
}
// Display customers with overdue rentals
void displayCustomersWithOverdueRentals(DataHandler &dataHandler)
{
    vector<Customer> customers = dataHandler.getCustomersWithOverdueRentals();
    if (customers.empty())
    {
        cout << "No customers with overdue rentals found.\n";
    }
    else
    {
        cout << "Customers with Overdue Rentals:\n";
        for (const auto &customer : customers)
        {
            cout << "Customer ID: " << customer.getCustomerID() << "\n"
                 << "Name: " << customer.getName() << "\n"
                 << "Phone: " << customer.getPhone() << "\n\n";
        }
    }
}
// Manage customers submenu
void manageCustomers(DataHandler &dataHandler)
{
    int customerChoice;

    while (true)
    {
        displayCustomerMenu();
        cin >> customerChoice;

        switch (customerChoice)
        {
        case 1:
            viewAllCustomers(dataHandler);
            break;
        case 2:
            addCustomer(dataHandler);
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
void addVideo(DataHandler &dataHandler)
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

    if (dataHandler.addVideo(title, genre, releaseYear, rentalPrice, true))
    {
        cout << "Video added successfully.\n";
    }
    else
    {
        cout << "Failed to add video.\n";
    }
}

// Manage videos submenu
void manageVideos(DataHandler &dataHandler)
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
            addVideo(dataHandler);
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
void viewRecords(DataHandler &dataHandler)
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
            // Inside the viewRecords function
            displayActiveRentals(dataHandler);
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
    DataHandler dataHandler("customers.csv", "videos.csv", "rentals.csv");

    int choice;

    while (true)
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            rentVideo(dataHandler);
            break;
        case 2:
            returnVideo(dataHandler);
            break;
        case 3:
            manageCustomers(dataHandler);
            break;
        case 4:
            manageVideos(dataHandler);
            break;
        case 5:
            viewRecords(dataHandler);
            break;
        case 6:
            cout << "Exiting program. Thank you!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}
