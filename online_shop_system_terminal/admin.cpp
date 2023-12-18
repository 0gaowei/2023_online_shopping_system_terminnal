#include "admin.h"
#include <iostream>
#include <fstream>
#include <sstream>

Admin::Admin(const string& nickname, const string& username) : nickname(nickname), username(username) {}
    

void Admin::welcomeMenu() {
    int choice;

    do {
        std::cout << "\n****Welcome admin " << username << " ****\n";
        std::cout << "╔═══════════════════════════╗" << std::endl;
		std::cout << "║       1.Add good.         ║" << std::endl;
		std::cout << "║       2.Delete good.      ║" << std::endl;
		std::cout << "║       3.Modify good       ║" << std::endl;
		std::cout << "║       0.Exit              ║" << std::endl;
		std::cout << "╚═══════════════════════════╝" << std::endl;
        std::cout << "Please select an action:";
        std::cin >> choice;
        
        if (choice == 1) {
            string id, name, info;
            double price; int total;
            std::cout << "Please input the ID: "; 
            std::cin >> id;
            std::cout << "\nPlease input the name: ";
            std::cin >> name;
            std::cout << "\nPlease input the price: ";
            std::cin >> price;
            std::cout << "\nPlease input the infomation: ";
            std::cin >> info;
            std::cout << "\nPlease input the total: ";
            std::cin >> total;
            if (addGood(id, name, price, info, total)) {
                std::cout << "Success added!\n";
            } else std::cerr << "Failed to open the goodFile.txt!\n";
        } else if (choice == 2) {
            string id;
            std::cout << "Please input the ID: ";
            std::cin >> id;
            if (deleteGood(id)) {
                std::cout << "Success deleted!\n";
            } else std::cerr << "Failed to delete the good!\n";
        } else if (choice == 3) {
            string id;
            std::cout << "Please input the ID: ";
            std::cin >> id;
            if (modifyGood(id)) {
                std::cout << "Success modified!\n";
            } else std::cerr << "Failed to modify the good!\n";
        } else if (choice == 0) {
            std::cout << "\nExiting......\n";
            break;
        } else {
            std::cout << "Invalid selection, please re-enter.\n";
        }
    } while (choice != 0);
}

bool Admin::addGood(string id, string name, double price,
                    string info, int total) {
    std::fstream goodFile;
    goodFile.open("goods.txt", std::ios::app);
    if (goodFile) {
        goodFile << id << " " << name << " " << price << " " << info << " " << total << "\n";
        goodFile.close();
        return true;
    } else return false;
}

bool Admin::deleteGood(string id) {
    std::ifstream inputFile("goods.txt");
    std::ofstream tempFile("temp.txt");
    
    if (!inputFile || !tempFile) {
        std::cerr << "Failed to open files for delete operation\n";
        return false;
    }

    bool deleted = false;
    string line;
    
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        string currentId;
        iss >> currentId;

        if (currentId != id) {
            // If the current ID is not the one to be deleted, write it to temp file
            tempFile << line << "\n";
        } else {
            // If the current ID matches the one to be deleted, set deleted to true
            deleted = true;
        }
    }

    inputFile.close();
    tempFile.close();

    // Remove the original file and rename the temp file
    if (deleted) {
        if (remove("goods.txt") != 0) {
            std::cerr << "Error deleting the original file\n";
            return false;
        }

        if (rename("temp.txt", "goods.txt") != 0) {
            std::cerr << "Error renaming the temp file\n";
            return false;
        }

        std::cout << "Successfully deleted the product with ID " << id << "\n";
        return true;
    } else {
        std::cout << "Product with ID " << id << " not found\n";
        // Remove the temp file since no changes were made
        remove("temp.txt");
        return false;
    }
}


bool Admin::modifyGood(string id) {
    std::ifstream inputFile("goods.txt");
    std::ofstream tempFile("temp.txt");

    if (!inputFile || !tempFile) {
        std::cerr << "Failed to open files for modify operation\n";
        return false;
    }

    bool modified = false;
    string line;
    // Skip the header line
    std::getline(inputFile, line);
    tempFile << line << "\n";
    
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        string currentId, name, info;
        double price;
        int total;

        iss >> currentId >> name >> price >> info >> total;

        if (currentId == id) {
            // If the current ID matches the one to be modified, prompt for new information
            std::cout << "Enter new information for the product with ID " << id << ":\n";
            std::cout << "New Name: ";
            std::cin >> name;
            std::cout << "New Price: ";
            std::cin >> price;
            std::cout << "New Info: ";
            std::cin >> info;
            std::cout << "New Total: ";
            std::cin >> total;

            // Write the modified information to the temp file
            tempFile << id << " " << name << " " << price << " " << info << " " << total << "\n";
            modified = true;
        } else {
            // If the current ID is not the one to be modified, write it to temp file
            tempFile << line << "\n";
        }
    }

    inputFile.close();
    tempFile.close();

    // Remove the original file and rename the temp file
    if (modified) {
        if (remove("goods.txt") != 0) {
            std::cerr << "Error deleting the original file\n";
            return false;
        }

        if (rename("temp.txt", "goods.txt") != 0) {
            std::cerr << "Error renaming the temp file\n";
            return false;
        }

        std::cout << "Successfully modified the product with ID " << id << "\n";
        return true;
    } else {
        std::cout << "Product with ID " << id << " not found\n";
        // Remove the temp file since no changes were made
        remove("temp.txt");
        return false;
    }
}
