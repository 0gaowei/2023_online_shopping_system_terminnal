#pragma once

#include <map>
#include <string>
#include <vector>
using std::vector;
using std::string;
using std::map;

class User {
public:
    // 构造函数
    User(const string& nickname, const string& username, const string& password,
         const string& phone, const string& birthday, const string& gender);
    
    // 1.修改密码，提供用户名
    void modifyPassword();
    
    // 欢迎、选择菜单
    void welcomeMenu();
    
    //2.查找商品
    void searchGood(string name);
    
    //3.模糊搜索商品
    void findGood(string keywords);

    // 4.添加商品到购物车
    void addToCart(const string& goodId, int quantity);

    // 5.查询购物车中的商品信息
    void viewCart();

    // 6.从购物车中删除商品
    void removeFromCart(const string& goodId);

    // 7.修改购物车中某个商品的购买数量
    void modifyCartItem(const string& goodId, int newQuantity);

    // 8.展示商品列表
    void showGoods();

    // 9. 计算购物车商品总价
    double calculatePrice();

    // 10.选择商品结算，并删除已经结算的商品
    double selectAndCalculate();
    double calculateOne(string goodId, int quantity);
    
    // 发放随机优惠券
    void giveRandomCoupon();
    // 使用优惠券计算金额
    double useCoupon(string code);
    double calculateFinalPrice(double price); 

    // 设置全局折扣活动
    void setDiscount(double discount);
    double getDiscount(); // 获取全局折扣  
    double calFinalPrice(double originalPrice); // 计算最终价格

    // 保存购买历史记录
    void recordPurchaseHistory(string goodId, int quantity, string time);

    // 购物历史数据分析
    void analyzePurchase(string startTime, string endTime); 

private:
    struct PurchaseItem {
    string goodId;
    string name; 
    double price;
    string info;
    int quantity;
    };

    string username;
    string password;
    string nickname;
    string phone;
    string birthday;
    string gender;

    // 保存购物历史
    map<string, vector<PurchaseItem>> purchaseHistory;  

    // 用户拥有的优惠券  
    map<string, double> coupons; 
    
    // 购物车数据结构，商品ID映射到购买数量
    map<string, int> shoppingCart;

    // 全局折扣比例
    double globalDiscount;

    // 将购物车数据保存到文件夹中
    void saveCartToFile();

    // 从文件夹加载购物车数据
    void loadCartFromFile();

    // 保存加载购买历史记录
    void savePurchaseHistory();
    void loadPurchaseHistory(); 

    // 购物的商品分类
    map<string, double> purchaseByCategory(string begin, string end);
    
};
