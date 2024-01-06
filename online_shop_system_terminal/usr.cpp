#include "usr.h"
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <chrono>
#include <ctime>

User::User( const string& username, const string& password, const string& nickname,
           const string& phone, const string& birthday, const string& gender)
    : username(username), password(password), nickname(nickname),
      phone(phone), birthday(birthday), gender(gender) {}

// 修改密码
void User::modifyPassword() {
    // 读取数据库
    std::ifstream userFile("user.txt");

    if (!userFile.is_open()) {
        std::cerr << "Failed to open user file for reading.\n";
        return;
    }

    std::map<string, vector<string>> userMap;

    // 跳过表头
    std::string header;
    std::getline(userFile, header);

    string nameID, pass, nick, ph, bir, gen;

    while (userFile >> nameID >> pass >> nick >> ph >> bir >> gen) {
        vector<string> info_vec = {pass, nick, ph, bir, gen};
        userMap[nameID] = info_vec;
    }

    userFile.close(); // 关闭文件

    // 修改密码，要求提供原密码
    string newPassword, oldPassword;
    int cnt = 3;
    bool flag = false;
    std::cout << "\nPlease input original password:";

    do {
        std::cin >> oldPassword;

        if (oldPassword == userMap[username][0]) {
            std::cout << "\nPlease input new password：";
            std::cin >> newPassword;
            userMap[username][0] = newPassword;
            flag = true;
            break;
        } else {
            std::cout << "\nThe original password is wrong, please re-enter (you still have" << --cnt << " chances): ";
        }
    } while (cnt);

    // 写入数据库
    std::ofstream outFile("user.txt");

    if (!outFile.is_open()) {
        std::cerr << "Failed to open user file for writing.\n";
        return;
    }

    outFile << "username password nickname phone birthday gender\n";
    for (const auto& entry : userMap) {
        outFile << entry.first;
        for (const auto& value : entry.second) {
            outFile << " " << value;
        }
        outFile << std::endl;
    }

    outFile.close(); // 关闭文件

    if (flag) {
         std::cout << "\nPassword changed successfully!\n";
     } else {
         std::cout << "\nPassword change failed!\n";
     }
}

// 欢迎菜单
void User::welcomeMenu() {
    int choice = -1;
    loadCartFromFile(); //load Cart
    
    std::cout << "欢迎用户 " << username << " !\n";
    giveRandomCoupon(); // 发放优惠券
    setDiscount(0.95); // 活动折扣
    std::cout << "How lucky! There is a discount on 12-12 today! You got a " << getDiscount()*10 << " off discount! What a discount!\n";
    do {
        std::cout << "============================\n";
        std::cout << "1. Change password\n";
        std::cout << "2. Exact product search\n";
        std::cout << "3. Search for products by keyword\n";
        std::cout << "4. Add items to shopping cart\n";
        std::cout << "5. Query the shopping cart\n";
        std::cout << "6. Remove an item from the shopping cart\n";
        std::cout << "7. Modify the purchase quantity of a certain product\n";
        std::cout << "8. Display product list\n";
        std::cout << "9. Calculate the total price of the shopping cart items\n";
        std::cout << "10. Select the items in the shopping cart for checkout\n";
        std::cout << "11. Use coupons to checkout\n";
        std::cout << "12. Analyze Purchase Data\n";
        std::cout << "0. Exit\n";
        std::cout << "============================\n";
        std::cout << "Please input your operation: ";
        std::cin >> choice;

        if (choice == 1) {
            modifyPassword();
        } else if (choice == 8) {
            showGoods();
        } else if (choice == 2) {
            string name;
            std::cout << "Please input the name: ";
            std::cin >> name;
            searchGood(name);
        } else if (choice == 3) {
            string name;
            std::cout << "Please input the keywords: ";
            std::cin >> name;
            findGood(name);
        } else if (choice == 0) {
            saveCartToFile();
            std::cout << "Exiting......\n";
            break;
        } else if (choice == 4) {
            string goodID;
            int quantity;
            std::cout << "Please input the goodID: ";
            std::cin >> goodID;
            std::cout << "\nPlease input the quantity: ";
            std::cin >> quantity;
            addToCart(goodID, quantity);
        } else if (choice == 5) {
            viewCart();
        } else if (choice == 6) {
            string goodID;
            std::cout << "Please input the goodID to be deleted: ";
            std::cin >> goodID;
            removeFromCart(goodID);
        } else if (choice == 7) {
            string goodID;
            int newQuantity;
            std::cout << "Please input the goodID to be modified: ";
            std::cin >> goodID;
            std::cout << "Please input the new quantity: ";
            std::cin >> newQuantity;
            modifyCartItem(goodID, newQuantity);
        } else if (choice == 9) {
            double oPrice = calculatePrice();
            double price = calFinalPrice(oPrice);
            std:: cout << "The total price is " << price << " .\n";
        } else if (choice == 10) {
            double oPrice = selectAndCalculate();
            double price = calFinalPrice(oPrice);
            std::cout << "Succeed! The total price of selected goods is: " << price << ".\n";
        } else if (choice == 11) {
            double oPrice = selectAndCalculate();
            double price = calculateFinalPrice(oPrice);
            std:: cout << "Succeed! The total price is " << price << " .\n";
        } else if (choice == 12) {
            string start, end;
            std::cout << "Enter start time (yyyy-mm-dd): ";
            std::cin >> start; 
            start +=  + "-00:00:00";
            std::cout << "Enter end time (yyyy-mm-dd): "; 
            std::cin >> end;
            end +=  + "-00:00:00";
            // 分析结果
            analyzePurchase(start, end); 
        } else std::cout << "Invalid selection, please re-enter\n";
    } while (choice != 0);
}

// 精确搜索
void User::searchGood(string name) {
    std::ifstream goodsFile("goods.txt");

    if (!goodsFile) {
        std::cerr << "Failed to open goods file for searching\n";
        return;
    }

    string id, goodName, info;
    double price;
    int total;
    bool found = false;

    // Skip the header line
    std::getline(goodsFile, id);

    while (goodsFile >> id >> goodName >> price >> info >> total) {
        if (goodName == name) {
            found = true;
            std::cout << "good info：\n id: " << id << " name: " << goodName << " price: " << price << " info: " << info << " total: " << total << "\n";
            break;  // Stop searching after the first match
        }
    }

    goodsFile.close();

    if (!found) {
        std::cout << "Couldn't find the product：" << name << "\n";
    }
}

// 模糊搜索
void User::findGood(string keywords) {
    std::ifstream goodsFile("goods.txt");

    if (!goodsFile) {
        std::cerr << "Failed to open goods file for searching\n";
        return;
    }

    string id, goodName, info;
    double price;
    int total;
    bool found = false;

    // Skip the header line
    std::getline(goodsFile, id);

    while (goodsFile >> id >> goodName >> price >> info >> total) {
        // Check if any field contains the keywords
        if (goodName.find(keywords) != string::npos ||
            info.find(keywords) != string::npos) {
            found = true;
            std::cout << "good info：\n  id: " << id << " goodName: " << goodName << " price: " << price << " info: " << info << " total: " << total << "\n";
        }
    }

    goodsFile.close();

    if (!found) {
        std::cout << "Failed to find good including the keywords-：" << keywords << "-you provided.\n";
    }
}

// 添加商品到购物车
void User::addToCart(const string& goodId, int quantity) {
    // 在这里需要检查商品是否存在，以及购买数量是否合理
    // 这里简化为直接添加到购物车
    shoppingCart[goodId] += quantity;
    std::cout << "Successfully added items to the shopping cart\n";
}

// 查询购物车中的商品信息
void User::viewCart() {
    if (shoppingCart.empty()) {
        std::cout << "The shopping cart is empty!\n";
        return;
    }

    std::cout << "Shopping cart contents：\n";
    for (const auto& item : shoppingCart) {
        std::cout << "goodID: " << item.first << ", quantity: " << item.second << "\n";
    }
}

// 从购物车中删除商品
void User::removeFromCart(const string& goodId) {
    auto it = shoppingCart.find(goodId);
    if (it != shoppingCart.end()) {
        shoppingCart.erase(it);
        std::cout << "Product removed from shopping cart successfully!\n";
    } else {
        std::cout << "This product is not in the shopping cart!\n";
    }
}

// 修改购物车中某个商品的购买数量
void User::modifyCartItem(const string& goodId, int newQuantity) {
    auto it = shoppingCart.find(goodId);
    if (it != shoppingCart.end()) {
        it->second = newQuantity;
        std::cout << "Successfully modified product purchase quantity!\n";
    } else {
        std::cout << "This product is not in the shopping cart!\n";
    }
}

// 保存购物出信息
void User::saveCartToFile() {
    // 构建购物车文件路径
    string cartFilePath = "SHOPCAR/" + username + "_cart.txt";

    std::ofstream cartFile(cartFilePath);

    if (!cartFile) {
        std::cerr << "Failed to open cart file for writing\n";
        return;
    }

    // 写入购物车数据到文件
    for (const auto& item : shoppingCart) {
        cartFile << item.first << " " << item.second << "\n";
    }

    cartFile.close();
}

//读取购物车信息
void User::loadCartFromFile() {
    // 构建购物车文件路径
    string cartFilePath = "SHOPCAR/" + username + "_cart.txt";

    std::ifstream cartFile(cartFilePath);

    if (!cartFile) {
        std::cerr << "No cart file found for user " << username << "\n";
        return;
    }

    // 从文件加载购物车数据
    string goodId;
    int quantity;
    while (cartFile >> goodId >> quantity) {
        shoppingCart[goodId] = quantity;
    }

    cartFile.close();
}

// 展示商品列表
void User::showGoods() {
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

// 计算购物车中某个商品的总价 
double User::calculateOne(string goodId, int quantity) {
    double price = 0;
    
    std::ifstream goodsFile("goods.txt");
    string id, name, info, singlePrice, total;
    while(goodsFile >> id >> name >> singlePrice >> info >> total) {
        // std::cout << id << ": " << singlePrice;
        if(id == goodId) {
            price = stod(singlePrice) * quantity;
            break; 
        }
    }
    goodsFile.close();
    
    return price;
}

// 计算购物车所有商品总价
double User::calculatePrice() {
    double totalPrice = 0;
    
    for (const auto& item : shoppingCart) {
        // 从商品列表中获取商品单价
        string goodId = item.first;  
        int quantity = item.second;
        // std::cout << goodId << " " << quantity << "\n";
        totalPrice += calculateOne(goodId, quantity);
    }
    
    return totalPrice;
}

// 选择结算购物车中商品
double User::selectAndCalculate() {
    double totalPrice = 0;
    string goodId;
    int quantity;
    
    // 显示购物车商品
    viewCart();  
    
    // 用户选择结算的商品
    std::cout << "Enter the product ID you want to settle, and enter '0' to stop selecting.";
    int cnt = 0;
    while(true) {
        std::cout<< std::endl << ++cnt << ": ";
        std::cin >> goodId;
        if(goodId == "0") break;
        
        auto it = shoppingCart.find(goodId);
        if(it != shoppingCart.end()) {
            quantity = it->second;
            totalPrice += calculateOne(goodId, quantity);
            // 删除前保存购物历史
            time_t t = time(nullptr);
            char timeStr[20]; 
            // time就是格式化后的时间 "2023-06-23-11:28:29"
            strftime(timeStr, sizeof(timeStr), "%Y-%m-%d-%H:%M:%S", localtime(&t));  
            string time(timeStr);
            recordPurchaseHistory(it->first, it->second, time);
            //删除
            shoppingCart.erase(it);
        } else {
            std::cout << "There is no product in the shopping cart." << std::endl; 
        }
    }
    
    return totalPrice;
}

// 发放随机优惠券
void User::giveRandomCoupon() {
    std::random_device rd; // 随机数生成器
    std::mt19937 gen(rd()); // 随机数引擎
    std::uniform_int_distribution<> dist(5000, 10000); // 均匀分布的整数随机数生成类

    // 线程安全地生成一个范围在5000-10000之间的随机整数优惠券码
    int code = dist(gen);
    double rawDiscount = (rand() % 50 + 50) / 10.0; // 0.5 - 1.0  
    double discount = rawDiscount / 10; // 舍去一位小数
    coupons[std::to_string(code)] = discount;

    std::cout << "How lucky! You have received a " << discount * 100 << " off discount coupon. The discount code: " << code << "\n"; 
}

// 使用优惠券
double User::useCoupon(string code) {
    auto it = coupons.find(code);
    if (it != coupons.end()) {
        return it->second;
    }
    return 1.0; // 没有该优惠券,不打折
}

// 打折
double User::calculateFinalPrice(double price) {
    string code;
    std::cout << "Please enter your coupon code (empty for no coupon): ";
    std::cin >> code;
  
    double discount = useCoupon(code);  
    return price * discount; 
}

// 设置全局折扣活动
void User::setDiscount(double discount) {
  globalDiscount = discount; 
}

// 获取全局折扣
double User::getDiscount() {
  return globalDiscount;
}

// 折扣价
double User::calFinalPrice(double originalPrice) {
    double discount = getDiscount();
    
    double price = originalPrice * discount; 
    
    // 使用优惠券后计算价格
    return price; 
}

// 保存购物历史
void User::recordPurchaseHistory(string goodId, int quantity, string time) {

    // 获取商品详细信息
    std::ifstream file("goods.txt");
    string id, name, price, info, total;
    while(file >> id >> name >> price >> info >> total) {
        if(id == goodId) {
        break; 
        }
    }

    // 创建记录
    PurchaseItem item {
        goodId, name, stod(price), info, quantity
    };

    // 添加到购物历史
    purchaseHistory[time].push_back(item); 

    // 保存
    savePurchaseHistory();

}

// 保存历史记录到DB
void User::savePurchaseHistory() {

  // 文件路径 
  string hisFilePath = "SHOPCAR/" + username + "_history.txt";

  std::ofstream file(hisFilePath);

  for(auto& h : purchaseHistory) {
     file << h.first << "\t";  
     
     for(auto& item : h.second) {
        file << item.goodId << " "  
            << item.name << " "
            << item.price << " "
            << item.info << " "
            << item.quantity << " ";
     }

     file << "\n";
  }

  file.close();
}

// 从DB读取历史记录
void User::loadPurchaseHistory() {
    string hisFilePath = "SHOPCAR/" + username + "_history.txt";
    std::ifstream file(hisFilePath);
    string time;

    while(getline(file, time)) {
        vector<PurchaseItem> items;

        while(true) {
            PurchaseItem item;
            // 检查文件结束 
            if(!file) break;
            file >> item.goodId >> item.name >> item.price >> item.info >> item.quantity;
            items.push_back(item);
        }

        purchaseHistory[time] = items;
    } 
    file.close();
}

// 分析购买数据
void User::analyzePurchase(string startTime, string endTime) {

    // 按商品类别统计购买金额
    auto result = purchaseByCategory(startTime, endTime);

    // 打印输出结果  
    for(auto& item : result) {
        std::cout << item.first << ": " << item.second << std::endl; 
    }
}

bool inRange(string time, string begin, string end) {
    return (begin <= time && time <= end);
}

map<string, double> User::purchaseByCategory(string begin, string end) {
    map<string, double> purchaseByInfo;
    
    // 遍历指定日期范围的购买记录
    for(auto& t : purchaseHistory) {
        if(inRange(t.first, begin, end)) { 
        for(auto& item : t.second) {
            purchaseByInfo[item.info] += item.price * item.quantity;  
        }
        }
    }

    return purchaseByInfo;
}
