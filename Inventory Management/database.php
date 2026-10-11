<?php
$host = '127.0.0.1';
$db   = 'inventory_db';
$user = 'root';
$pass = '';
$charset = 'utf8mb4';

$dsn = "mysql:host=$host;dbname=$db;charset=$charset";
$options = [
    PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
    PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
    PDO::ATTR_EMULATE_PREPARES   => false,
];

try {
    $pdo = new PDO($dsn, $user, $pass, $options);

    if ($argc >= 2) {
        $productData = json_decode($argv[1], true);

        if (!$productData) {
            echo json_encode(["status" => "error", "message" => "Invalid JSON formatting passed to PHP."]);
            exit(1);
        }

        if (isset($productData['action'])) {
               
          //View all products
            if ($productData['action'] === 'view_all') {
                $stmt = $pdo->query('SELECT id, name, sku, quantity, price FROM products');
                echo json_encode($stmt->fetchAll());
                exit(0);
            }
            
          //flag low stock items
            if ($productData['action'] === 'low_stock') {
                $threshold = isset($productData['threshold']) ? (int)$productData['threshold'] : 5;
                $stmt = $pdo->prepare('SELECT id, name, sku, quantity, price FROM products WHERE quantity <= :threshold');
                $stmt->execute([':threshold' => $threshold]);
                echo json_encode($stmt->fetchAll());
                exit(0);
            }
        }

        $stmt = $pdo->prepare('INSERT INTO products (name, sku, quantity, price) VALUES (:name, :sku, :quantity, :price)');
        $stmt->execute([
            ':name'     => $productData['name'],
            ':sku'     => $productData['sku'],
            ':quantity' => $productData['stock'],
            ':price'    => $productData['price']
        ]);

        echo json_encode(["status" => "success", "message" => "Product added successfully."]);
        exit(0);
    } 
    
    $stmt = $pdo->query('SELECT id, name, sku, quantity, price FROM products');
    echo json_encode($stmt->fetchAll());

} catch (\PDOException $e) {
    echo json_encode(["status" => "error", "message" => $e->getMessage()]);
}
?>
