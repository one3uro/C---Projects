#This cOde was generated via Gemini Pro On thinking mode i used the layout of python as im familiar with it and bit by bit re-constructed the code to translate to its c++ equivalent. I also used the python code as a reference to ensure that the logic and structure of the C++ code matched the Python implementation.
# import mysql.connector
# from mysql.connector import Error
# 
# # 1. DATABASE CONNECTION LAYER
# def get_db_connection():
#     """Establishes and returns a connection to the MySQL database."""
#     try:
#         return mysql.connector.connect(
#             host='localhost',
#             user='root', # Replace with your MySQL username
#             password='password', # Replace with your MySQL password
#             database='inventory_db'
#         )
#     except Error as e:
#         print(f"Error connecting to MySQL: {e}")
#         return None
# 
# # 2. OBJECT-ORIENTED MODEL (OOP)
# class Product:
#     def __init__(self, name, sku, quantity, price, description="", product_id=None):
#         self.id = product_id
#         self.name = name
#         self.sku = sku
#         self.quantity = int(quantity)
#         self.price = float(price)
#         self.description = description
# 
#     def __str__(self):
#         return f"[SKU: {self.sku:7}] {self.name:20} | Qty: {self.quantity:4} | Price: ${self.price:7.2f}"
# 
# # 3. INVENTORY MANAGEMENT SYSTEM (SQL / DATA LOGIC)
# class InventoryManager:
#     @staticmethod
#     def initialize_database():
#         """Ensures the table exists before attempting operations."""
#         connection = get_db_connection()
#         if not connection:
#             return
#         try:
#             cursor = connection.cursor()
#             cursor.execute("""
#                 CREATE TABLE IF NOT EXISTS products (
#                     id INT AUTO_INCREMENT PRIMARY KEY,
#                     name VARCHAR(255) NOT NULL,
#                     sku VARCHAR(50) UNIQUE NOT NULL,
#                     quantity INT NOT NULL,
#                     price DECIMAL(10, 2) NOT NULL,
#                     description TEXT
#                 );
#             """)
#             connection.commit()
#         except Error as e:
#             print(f"Database initialization failed: {e}")
#         finally:
#             cursor.close()
#             connection.close()
# 
#     @staticmethod
#     def add_product(product):
#         """Inserts a new product into the database using parameterized queries."""
#         connection = get_db_connection()
#         if not connection:
#             return False
#         try:
#             cursor = connection.cursor()
#             query = """INSERT INTO products (name, sku, quantity, price, description) VALUES (%s, %s, %s, %s, %s) ON DUPLICATE KEY UPDATE quantity = quantity + VALUES(quantity)"""
#             values = (product.name, product.sku, product.quantity, product.price, product.description)
#             cursor.execute(query, values)
#             connection.commit()
#             return True
#         except Error as e:
#             print(f"Failed to add product {product.sku}: {e}")
#             return False
#         finally:
#             cursor.close()
#             connection.close()
# 
#     @staticmethod
#     def view_all_products():
#         """Retrieves SQL records and maps them to instances of the Product class."""
#         connection = get_db_connection()
#         if not connection:
#             return []
#         products = []
#         try:
#             cursor = connection.cursor()
#             cursor.execute("SELECT name, sku, quantity, price, description, id FROM products")
#             for row in cursor.fetchall():
#                 prod = Product(row[0], row[1], row[2], row[3], row[4], row[5])
#                 products.append(prod)
#             return products
#         except Error as e:
#             print(f"Query error: {e}")
#             return []
#         finally:
#             cursor.close()
#             connection.close()
# 
#     @staticmethod
#     def get_low_stock_alerts(threshold=5):
#         """Finds items whose stock falls below a custom numerical baseline."""
#         connection = get_db_connection()
#         if not connection:
#             return []
#         low_stock_items = []
#         try:
#             cursor = connection.cursor()
#             query = "SELECT name, sku, quantity, price, description, id FROM products WHERE quantity <= %s"
#             cursor.execute(query, (threshold,))
#             for row in cursor.fetchall():
#                 prod = Product(row[0], row[1], row[2], row[3], row[4], row[5])
#                 low_stock_items.append(prod)
#             return low_stock_items
#         except Error as e:
#             print(f"Alert query failed: {e}")
#             return []
#         finally:
#             cursor.close()
#             connection.close()
# 
# # 4. RUN AUTOMATED TEST DEMO
# if __name__ == "__main__":
#     print("--- Initializing Database Structure ---")
#     InventoryManager.initialize_database()
# 
#     print("\n--- Injecting Dummy Production Data ---")
#     dummy_items = [
#         Product("Logitech Mouse", "MS-102", 45, 29.99, "Wireless optical mouse"),
#         Product("4K Monitor", "MN-4K2", 3, 349.50, "Ultra HD 32-inch monitor"), # Low Stock
#         Product("Mechanical Keyboard", "KB-MECH", 12, 89.00, "RGB Blue-switch board"),
#         Product("USB-C Cable 6ft", "CB-USBC", 2, 9.99, "Braided fast charging cable") # Low Stock
#     ]
#     for item in dummy_items:
#         if InventoryManager.add_product(item):
#             print(f"Imported: {item.name}")
# 
#     print("\n--- Active Database Inventory Inventory ---")
#     all_items = InventoryManager.view_all_products()
#     for item in all_items:
#         print(item)
# 
#     print("\n⚠️ SYSTEM ALERTS: LOW STOCK REPORT (Threshold <= 5) ⚠️")
#     alerts = InventoryManager.get_low_stock_alerts(threshold=5)
#     if alerts:
#         for low_item in alerts:
#             print(f"ALERT: {low_item.name} is critically low! Only {low_item.quantity} left.")
#     else:
#         print("All stock levels are clear and stable.")
