# Inventory Management System (C++ & PHP)

A hybrid C++ and PHP command-line application designed to manage an active inventory database. The system utilizes a C++ frontend for core logic execution and manages data by piping JSON arguments directly to a background PHP script connected to a MySQL server running via XAMPP.

## 🚀 Features
* **Database State Verification**: Validates connection and initializes table state upon startup.
* **Product Insertion**: Bundles and injects new item metrics (Name, SKU, Price, Stock) into the database.
* **Live Inventory View**: Pulls full inventory tables directly into a clean console matrix string.
* **Low-Stock Alert Engine**: Scans product quantities individually to flag entries that fall beneath a specified threshold (e.g., fewer than 5 units).

## 🛠️ Project Structure
* `main.cpp` - Core C++ application managing operations, control flow, and process piping.
* `database.php` - Backend interface file handling MySQL PDO parameters, data sanitization, and SQL statements.

---

## 📋 Prerequisites & Setup

### 1. Environment & Services Setup
Because this setup relies on a local background server stack, you must ensure your database services are running before launching the application.

#### A. Starting the Services
Depending on your operating system and installation environment, run the appropriate command or interface tool to start Apache and MySQL/MariaDB:

* **Linux (XAMPP Bundled):**
  ```bash
  sudo /opt/lampp/lampp start
  ```
* **Linux (Standard Native Stack):**
  ```bash
  sudo systemctl start apache2 mysql
  ```
* **macOS:**
  * If using **XAMPP Application Wrapper**: Open the XAMPP application from your Applications folder, navigate to the "Manage Servers" tab, and click **Start All**.
  * If using **Homebrew native packages**: 
    ```bash
    brew services start httpd
    brew services start mysql
    ```
* **Windows:**
  * Open the **XAMPP Control Panel** (`xampp-control.exe`) as an Administrator and click **Start** next to both Apache and MySQL.

#### B. Connection Parameters
Open your `database.php` file and verify that your SQL connection parameters match your database environment's administrative user profile. For default XAMPP setups across all platforms, use:
```php
$username = 'root';
$password = ''; // Leave blank
```

#### C. Executable Engine Note
This application utilizes process piping within `main.cpp` to execute the PHP backend. You must ensure the execution path matches your environment's PHP binary:
* **Linux (XAMPP):** Points explicitly to `/opt/lampp/bin/php` to avoid driver mismatches.
* **Linux (Native) / macOS / Windows:** Update the piping call inside `main.cpp` to target your global environment binary (`php` or `php.exe`), ensuring PHP is added to your system's `PATH` variable.

---

## ⚙️ Compilation & Execution

1. Compile the C++ program utilizing a standard C++ compiler:
   * **Linux / macOS (g++/clang++):**
     ```bash
     g++ main.cpp -o inventory_system
     ```
   * **Windows (MinGW/g++):**
     ```cmd
     g++ main.cpp -o inventory_system.exe
     ```

2. Run the compiled executable binary:
   * **Linux / macOS:**
     ```bash
     ./inventory_system
     ```
   * **Windows:**
     ```cmd
     inventory_system.exe
     ```

---

## 📊 Expected Terminal Output Trace
Screenshots of the database will be included to verify the output.

```text
Starting Inventory Management system...
inventoryManager is Requesting database state..
InventoryManager has recieved the required Data.[]
System Initialized Successfully

--- Injecting Dummy Production Data ---
Imported: Logitech Mouse
Imported: 4K Monitor
Imported: Mechanical Keyboard
Imported: USB-C Cable 6ft

--- Active Database Inventory ---
[{"id":1,"name":"Logitech Mouse","sku":"MS-102","quantity":45,"price":"29.99"},{"id":2,"name":"4K Monitor","sku":"MN-4K2","quantity":3,"price":"349.50"},{"id":3,"name":"Mechanical Keyboard","sku":"KB-MECH","quantity":12,"price":"89.00"},{"id":4,"name":"USB-C Cable 6ft","sku":"CB-USBC","quantity":2,"price":"9.99"}]

 Low stock Detected (Item is below threshold. (Less than 5) )
[{"id":2,"name":"4K Monitor","sku":"MN-4K2","quantity":3,"price":"349.50"},{"id":4,"name":"USB-C Cable 6ft","sku":"CB-USBC","quantity":2,"price":"9.99"}]
```
