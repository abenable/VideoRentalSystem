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

void rentVideo(DataHandler &dataHandler)
{
    int customerID, videoID, duration;
    const vector<Customer> &customers = dataHandler.getAllCustomers();
    const vector<Video> &videos = dataHandler.getAllVideos();

    cout << "Renting a Video." << endl;
    cout << "\nEnter customer ID: ";
    cin >> customerID;
    cout << "Enter video ID: ";
    cin >> videoID;
    cout << "Enter rental duration (days): ";
    cin >> duration;

    // Find customer by ID
    const Customer *selectedCustomer = nullptr;
    for (const auto &customer : customers)
    {
        if (customer.getCustomerID() == customerID)
        {
            selectedCustomer = &customer;
            break;
        }
    }

    // Find video by ID
    const Video *selectedVideo = nullptr;
    for (const auto &video : videos)
    {
        if (video.getVideoID() == videoID)
        {
            selectedVideo = &video;
            break;
        }
    }

    // Check if both customer and video are found
    if (selectedCustomer && selectedVideo)
    {
        int rentalID = rand() % 9000 + 1000;

        Rental rental(rentalID, selectedCustomer, selectedVideo, duration, false);
        // Optionally, add to dataHandler if there's a method for it
        if (dataHandler.addRental(rental))
        {
            cout << "Rental added successfully.\n";
        }
        else
        {
            cout << "Failed to add rental.\n";
        }
    }
    else
    {
        cout << "Customer or video not found.\n";
    }
}
void returnRental(DataHandler &dataHandler)
{
    int rentalID;

    cout << "Returning a Video." << endl;
    cout << "\nEnter Rental ID: ";
    cin >> rentalID;

    if (dataHandler.returnRental(rentalID))
    {
        cout << "Rental returned successfully.\n";
    }
    else
    {
        cout << "Failed to return rental.\n";
    }
}

// Display active rentals
void displayActiveRentals(DataHandler &dataHandler)
{
    vector<Rental> activeRentals = dataHandler.getActiveRentals();
    if (activeRentals.empty())
    {
        cout << "No active rentals found.\n";
    }
    else
    {
        cout << "Active Rentals:\n\n";
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
void displayReturnedRentals(DataHandler &dataHandler)
{
    vector<Rental> ReturnedRentals = dataHandler.getReturnedRentals();
    if (ReturnedRentals.empty())
    {
        cout << "No returned rentals found.\n";
    }
    else
    {
        cout << "Returned Rentals:\n\n";
        for (const auto &rental : ReturnedRentals)
        {
            cout << "Rental ID: " << rental.getRentalID() << "\n"
                 << "Customer ID: " << rental.getCustomerID() << "\n"
                 << "Video ID: " << rental.getVideoID() << "\n"
                 << "Rental Date: " << rental.getRentalDate() << "\n"
                 << "Due Date: " << rental.getDueDate() << "\n\n";
        }
    }
}
void displayOverDueRentals(DataHandler &dataHandler)
{
    vector<Rental> overDueRentals = dataHandler.getOverdueRentals();
    if (overDueRentals.empty())
    {
        cout << "No overdue rentals found.\n";
    }
    else
    {
        cout << "Overdue Rentals:\n\n";
        for (const auto &rental : overDueRentals)
        {
            cout << "Rental ID: " << rental.getRentalID() << "\n"
                 << "Customer ID: " << rental.getCustomerID() << "\n"
                 << "Video ID: " << rental.getVideoID() << "\n"
                 << "Rental Date: " << rental.getRentalDate() << "\n"
                 << "Due Date: " << rental.getDueDate() << "\n\n";
        }
    }
}
void displayCustomersWithOverdueRentals(DataHandler &dataHandler)
{
    vector<Customer> customersWithOverdueRentals = dataHandler.customersWithOverdueRentals();
    if (customersWithOverdueRentals.empty())
    {
        cout << "No customers with overdue rentals found.\n";
    }
    else
    {
        cout << "Customers with overdue rentals:\n\n";
        for (const auto &customer : customersWithOverdueRentals)
        {
            cout << "Customer ID: " << customer.getCustomerID() << "\n"
                 << "Address: " << customer.getAddress() << "\n"
                 << "Tel: " << customer.getPhone() << "\n";
        }
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
    int customerID = rand() % 9000 + 1000;
    Customer customer(customerID, name, address, phone);

    if (dataHandler.addCustomer(customer))
    {
        cout << "Customer added successfully.\n";
    }
    else
    {
        cout << "Failed to add customer.\n";
    }
}
void editCustomer(DataHandler &dataHandler)
{
    string name, address, phone;
    int id;

    cout << "\nEnter customer ID: ";
    cin >> id;
    cout << "\nEnter customer name: ";
    cin.ignore(); // Clear newline from input buffer
    getline(cin, name);
    cout << "Enter address: ";
    getline(cin, address);
    cout << "Enter phone: ";
    getline(cin, phone);
    Customer customer(id, name, address, phone);

    if (dataHandler.editCustomer(customer))
    {
        cout << "\nCustomer info updated successfully.\n";
    }
    else
    {
        cout << "Failed to add customer.\n";
    }
}
void deleteCustomer(DataHandler &dataHandler)
{
    int id;

    cout << "\nEnter customer ID: ";
    cin >> id;

    if (dataHandler.deleteCustomer(id))
    {
        cout << "\nCustomer with id: " << id << " deleted successfully.\n";
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
        case 3:
            editCustomer(dataHandler);
            break;
        case 4:
            deleteCustomer(dataHandler);
            break;
        // Implement update and delete functionality as needed
        case 6:
            return; // Exit to the main menu
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}
void addVideo(DataHandler &dataHandler)
{
    string title;
    double price;

    cout << "\nEnter video title: ";
    cin.ignore(); // Clear newline from input buffer
    getline(cin, title);
    cout << "Enter price: ";
    cin >> price;
    int videoID = rand() % 9000 + 1000;

    Video video(videoID, title, price, true);

    if (dataHandler.addVideo(video))
    {
        cout << "video added successfully.\n";
    }
    else
    {
        cout << "Failed to add video.\n";
    }
}
void editVideo(DataHandler &dataHandler)
{
    string title;
    double price;
    int id;

    cout << "Enter VideoID: ";
    cin >> id;
    cout << "\nEnter video title: ";
    cin.ignore(); // Clear newline from input buffer
    getline(cin, title);
    cout << "Enter price: ";
    cin >> price;

    Video video(id, title, price, true);

    if (dataHandler.editVideo(video))
    {
        cout << "\nVideo info updated successfully.\n";
    }
    else
    {
        cout << "Failed to update video.\n";
    }
}
void deleteVideo(DataHandler &dataHandler)
{
    int id;

    cout << "\nEnter VideoID: ";
    cin >> id;

    if (dataHandler.deleteVideo(id))
    {
        cout << "\nVideo with id: " << id << " deleted successfully.\n";
    }
    else
    {
        cout << "Failed to delete video.\n";
    }
}

// View all videos
void viewAllVideos(DataHandler &dataHandler)
{
    vector<Video> videos = dataHandler.getAllVideos();
    if (videos.empty())
    {
        cout << "No registered videos found.\n";
    }
    else
    {
        cout << "All Videos:\n\n";
        for (const auto &video : videos)
        {
            cout << "VideoID: " << video.getVideoID() << "\n"
                 << "Title: " << video.getTitle() << "\n"
                 << "Price: " << video.getPrice() << "\n"
                 << "Available: " << (video.getAvailability() ? "Yes" : "No") << "\n\n";
        }
    }
}

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
            viewAllVideos(dataHandler);
            break;
        case 2:
            addVideo(dataHandler);
            break;
        case 3:
            editVideo(dataHandler);
            break;
        case 4:
            deleteVideo(dataHandler);
            break;
        case 5:
            return; // Exit to the main menu
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

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
            displayActiveRentals(dataHandler);
            break;
        case 2:
            displayOverDueRentals(dataHandler);
            break;
        case 3:
            displayReturnedRentals(dataHandler);
            break;
        case 4:
            displayCustomersWithOverdueRentals(dataHandler);
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
    DataHandler dataHandler("data/customers.csv", "data/videos.csv", "data/rentals.csv");

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
            returnRental(dataHandler);
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