#include "guest.h"
#include <iostream>
#include <fstream>
#include <string>
using std::string;

void Guest::browse() {
    int choice;
    do {
        std::cout << "============================\n";
         std::cout << "Visitors are welcome\n";
         std::cout << "1. View product list\n";
         std::cout << "0. Return to main menu\n";
         std::cout << "============================\n";

        std::cout << "Please select: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                showGoods();
                break;
            case 0:
                std::cout << "Return to main menu......\n";
                break;
            default:
                std::cout << "Invalid selection, please re-enter.\n";
                break;
        }
    } while (choice);
}

// 展示商品列表
void Guest::showGoods() {
    std::ifstream goodsFile("goods.txt");
    
    if(!goodsFile) {
        std::cerr << "Failed to open goods file for showing\n"; 
        return;
    }
    
    string id, name, price, info, total;
    
    // 跳过表头
    std::getline(goodsFile, id); 
    
    std::cout << "\ngoods list:\n";
    std::cout << "-------------------------------------" << std::endl;
    while(goodsFile >> id >> name >> price >> info >> total) {
        std::cout << "good-ID: " << id << std::endl; 
        std::cout << "good-name: " << name << std::endl;
        std::cout << "good-price: " << price << std::endl;
        std::cout << "good-info: " << info << std::endl; 
        std::cout << "good-total: " << total << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    
    goodsFile.close();
}
