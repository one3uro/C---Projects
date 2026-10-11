#include <iostream>
#include <array>
#include <cstdio>
#include <memory>
#include <string>

//The code is designed to manage an inventory system, including database connection, product management, and low stock alerts.


//Connection Function
std::string connectToDatabase() {
    std::string command = "/opt/lampp/bin/php database.php";
    std::string result = "";
    std::array<char, 128> buffer;

    //gets database connection
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        std::cerr << "Process failed!" << std::endl;
        //return a string upon failure
        return "";
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result; //send the json string back
}

class InventoryManager {
    public:
    // ensures the table exists before attempting any operation
        bool initDatabase(){
        std::cout <<"inventoryManager is Requesting database state.." << std::endl;

        //call the connection function to capture the JSON string.
        std::string json_data = connectToDatabase();

        if (json_data.empty()) {
            std::cerr << "InventoryManager Error: Received no data from PHP script." << std::endl;
            return false;
        }

        std::cout <<"InventoryManager has recieved the required Data."<< json_data << std::endl;
        return true;

        }

         //Function for product insertion via php file communication
        bool AddProduct(const std::string& name, const std::string& sku, double price, int stock){

            // make the product into a string json arg
            std::string jsonProduct = "{\"name\":\"" + name + "\",\"sku\":\"" + sku + "\",\"price\":" + std::to_string(price) + ",\"stock\":" + std::to_string(stock) + "}";
            
            //append the json string arg
            std::string command = "/opt/lampp/bin/php database.php '" + jsonProduct + "'";
            std::string result = "";
            std::array<char, 128> buffer;

            //get database connection
            std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
            if (!pipe) return false;
            while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
                result += buffer.data();
            }

            //check if the php has carried out a successful database insertion
            //We treat the characters in the output as literal text
            return (result.find("\"status\":\"success\"") != std::string::npos);
        }


        //Function for product viewing
        std::string viewAllProducts(){
            // make the product into a string json arg
            std::string jsonPayload = "{\"action\":\"view_all\"}";
            
            //append the json string arg
            std::string command = "/opt/lampp/bin/php database.php '" + jsonPayload + "'";
            std::string result = "";
            std::array<char, 128> buffer;
            std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
            //exits and returns an empty string if the pipe fails to open
            if (!pipe) return "";
            while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
            {
                result += buffer.data();
            }
            //send the json string back
            return result;
        }

        std::string getLowStockAlerts(int threshold = 5) {
            std::string jsonPayload = "{\"action\":\"low_stock\",\"threshold\":" + std::to_string(threshold) + "}";
            std::string command = "/opt/lampp/bin/php database.php '" + jsonPayload + "'";
            std::string result = "";
            std::array<char, 128> buffer;
            std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
            //exits and returns an empty string if the pipe fails to open
            if (!pipe) return "";
            while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
            {
                result += buffer.data();
            }
            //send the json string back
            return result;
        }




};


int main() {
    std::cout << "Starting Inventory Management system..." << std::endl;

    // Call connection Function in main
    InventoryManager manager;
    if (manager.initDatabase()){
        std::cout <<"System Initialized Successfully"<<std::endl;

        std::cout << "\n--- Injecting Dummy Production Data ---" << std::endl;

        // Add some dummy products to the database
        if (manager.AddProduct("Logitech Mouse", "MS-102", 29.99, 45)) {
            std::cout << "Imported: Logitech Mouse" << std::endl;
        }
        if (manager.AddProduct("4K Monitor", "MN-4K2", 349.50, 3)) {
            std::cout << "Imported: 4K Monitor" << std::endl;
        }
        if (manager.AddProduct("Mechanical Keyboard", "KB-MECH", 89.00, 12)) {
            std::cout << "Imported: Mechanical Keyboard" << std::endl;
        }
        if (manager.AddProduct("USB-C Cable 6ft", "CB-USBC", 9.99, 2)) {
            std::cout << "Imported: USB-C Cable 6ft" << std::endl;
        }

        std::cout << "\n--- Active Database Inventory ---" << std::endl;
        // Fetch and print out all items from the database
        std::string allProducts = manager.viewAllProducts();
        std::cout << allProducts << std::endl;

        //low stock warning alert
        std::cout << "\n Low stock Detected (Item is below threshold. (Less than 5) )" << std::endl;
        std::string alerts = manager.getLowStockAlerts(5);
        
        // Evaluates if the returned database JSON array contains data records
        if (!alerts.empty() && alerts != "[]" && alerts.find("error") == std::string::npos) {
            std::cout << alerts << std::endl;
        } else {
            std::cout << "All stock levels are above threshold" << std::endl;
        }


    }else{
        std::cout <<"System Failed to Initialize"<<std::endl;

    }

    return 0;
}
