#include "include/dbHandler.h"
#include <iostream>
#include <vector>

using namespace std; // Add this line

void displayMainMenu()
{
    cout << "\n--- Video Rental System ---\n";
    cout << "1. Add New Customer\n";
    cout << "2. Add New Video\n";
    cout << "3. View Customer\n";
    cout << "4. View Video\n";
    cout << "5. Add Rental\n";
    cout << "6. Return Rental\n";
    cout << "7. View Rental\n";
    cout << "8. View All Customers\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}
void viewAllCustomers(DatabaseHandler &dbHandler)
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
                 << "Email: " << customer.getEmail() << "\n"
                 << "Phone: " << customer.getPhone() << "\n\n";
        }
    }
}

void addCustomer(DatabaseHandler &dbHandler)
{
    string name, address, phone, email;
    cout << "\nEnter customer name: ";
    getline(cin, name);
    cout << "Enter address: ";
    getline(cin, address);
    cout << "Enter phone: ";
    getline(cin, phone);
    cout << "Enter email: ";
    getline(cin, email);

    if (dbHandler.addCustomer(name, address, phone, email, true))
    {
        cout << "Customer added successfully.\n";
    }
    else
    {
        cout << "Failed to add customer.\n";
    }
}

void addVideo(DatabaseHandler &dbHandler)
{
    string title, genre;
    int releaseYear;
    double rentalPrice;
    cout << "\nEnter video title: ";
    getline(cin, title);
    cout << "Enter genre: ";
    getline(cin, genre);
    cout << "Enter release year: ";
    cin >> releaseYear;
    cout << "Enter rental price: ";
    cin >> rentalPrice;
    cin.ignore(); // To clear newline from input buffer

    if (dbHandler.addVideo(title, genre, releaseYear, rentalPrice, true))
    {
        cout << "Video added successfully.\n";
    }
    else
    {
        cout << "Failed to add video.\n";
    }
}

void viewCustomer(DatabaseHandler &dbHandler)
{
    int customerID;
    cout << "\nEnter customer ID to view: ";
    cin >> customerID;
    cin.ignore(); // Clear newline
    dbHandler.getCustomerByID(customerID);
}

void viewVideo(DatabaseHandler &dbHandler)
{
    int videoID;
    cout << "\nEnter video ID to view: ";
    cin >> videoID;
    cin.ignore(); // Clear newline
    dbHandler.getVideoByID(videoID);
}

void addRental(DatabaseHandler &dbHandler)
{
    int customerID, videoID;
    string rentalDate, dueDate;
    cout << "\nEnter customer ID: ";
    cin >> customerID;
    cout << "Enter video ID: ";
    cin >> videoID;
    cout << "Enter rental date (YYYY-MM-DD): ";
    cin >> rentalDate;
    cout << "Enter due date (YYYY-MM-DD): ";
    cin >> dueDate;
    cin.ignore(); // Clear newline

    if (dbHandler.addRental(customerID, videoID, rentalDate, dueDate))
    {
        cout << "Rental added successfully.\n";
    }
    else
    {
        cout << "Failed to add rental.\n";
    }
}

void returnRental(DatabaseHandler &dbHandler)
{
    int rentalID;
    cout << "\nEnter rental ID to return: ";
    cin >> rentalID;
    cin.ignore(); // Clear newline

    if (dbHandler.returnRental(rentalID))
    {
        cout << "Rental marked as returned.\n";
    }
    else
    {
        cout << "Failed to update return status.\n";
    }
}

void viewRental(DatabaseHandler &dbHandler)
{
    int rentalID;
    cout << "\nEnter rental ID to view: ";
    cin >> rentalID;
    cin.ignore(); // Clear newline
    dbHandler.getRentalByID(rentalID);
}

int main()
{
    DatabaseHandler dbHandler("VideoRentalSystem.db");

    if (!dbHandler.isConnected())
    {
        cerr << "Failed to connect to the database.\n";
        return 1;
    }

    dbHandler.createTables(); // Ensures tables exist

    int choice;
    do
    {
        displayMainMenu();
        cin >> choice;
        cin.ignore(); // Clear newline

        switch (choice)
        {
        case 1:
            addCustomer(dbHandler);
            break;
        case 2:
            addVideo(dbHandler);
            break;
        case 3:
            viewCustomer(dbHandler);
            break;
        case 4:
            viewVideo(dbHandler);
            break;
        case 5:
            addRental(dbHandler);
            break;
        case 6:
            returnRental(dbHandler);
            break;
        case 7:
            viewRental(dbHandler);
            break;
        case 8:
            viewAllCustomers(dbHandler);
            break;
        case 0:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
