#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_ORDERS 100
#define MAX_USERS 50
#define MAX_NAME_LEN 50

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    float price;
    int stock;
} Product;

typedef struct {
    int orderId;
    int productId;
    int quantity;
    char status[20];
    float total;
} Order;

typedef struct {
    int userId;
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];
    int isAdmin;
} User;

Product products[MAX_PRODUCTS];
Order orders[MAX_ORDERS];
User users[MAX_USERS];
int productCount = 0;
int orderCount = 0;
int userCount = 0;

void signUp(const char *username, const char *password, int isAdmin) {
    if (userCount < MAX_USERS) {
        users[userCount].userId = userCount + 1;
        strncpy(users[userCount].username, username, MAX_NAME_LEN);
        strncpy(users[userCount].password, password, MAX_NAME_LEN);
        users[userCount].isAdmin = isAdmin;
        userCount++;
        printf("User signed up successfully!\n");
    } else {
        printf("User limit reached!\n");
    }
}

void addProduct(int userId, int id, const char *name, float price, int stock) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].userId == userId && users[i].isAdmin) {
            if (productCount < MAX_PRODUCTS) {
                products[productCount].id = id;
                strncpy(products[productCount].name, name, MAX_NAME_LEN);
                products[productCount].price = price;
                products[productCount].stock = stock;
                productCount++;
                printf("Product added successfully!\n");
            } else {
                printf("Product list is full!\n");
            }
            return;
        }
    }
    printf("Access denied. Only admins can add products.\n");
}

void searchProducts(const char *keyword) {
    printf("Search results for '%s':\n", keyword);
    for (int i = 0; i < productCount; i++) {
        if (strstr(products[i].name, keyword) != NULL) {
            printf("ID: %d, Name: %s, Price: %.2f, Stock: %d\n", products[i].id, products[i].name, products[i].price, products[i].stock);
        }
    }
}

void processOrder(int productId, int quantity) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == productId) {
            if (products[i].stock >= quantity) {
                products[i].stock -= quantity;
                orders[orderCount].orderId = orderCount + 1;
                orders[orderCount].productId = productId;
                orders[orderCount].quantity = quantity;
                orders[orderCount].total = products[i].price * quantity;
                strcpy(orders[orderCount].status, "Processed");
                orderCount++;
                printf("Order processed: %d x %s\n", quantity, products[i].name);
            } else {
                printf("Insufficient stock for %s\n", products[i].name);
            }
            return;
        }
    }
    printf("Product ID %d not found\n", productId);
}

void updateOrderStatus(int orderId, const char *newStatus) {
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderId == orderId) {
            strncpy(orders[i].status, newStatus, 20);
            printf("Order ID %d status updated to %s\n", orderId, newStatus);
            return;
        }
    }
    printf("Order ID %d not found\n", orderId);
}

void generateSalesReport(const char *keyword) {
    printf("Sales Report for '%s':\n", keyword);
    for (int i = 0; i < orderCount; i++) {
        for (int j = 0; j < productCount; j++) {
            if (orders[i].productId == products[j].id && strstr(products[j].name, keyword) != NULL) {
                printf("Order ID: %d, Product: %s, Quantity: %d, Total: %.2f, Status: %s\n",
                       orders[i].orderId, products[j].name, orders[i].quantity, orders[i].total, orders[i].status);
            }
        }
    }
}

int main() {
    signUp("admin", "adminpass", 1);

    int choice, userId, productId, quantity, orderId, isAdmin;
    char keyword[MAX_NAME_LEN], username[MAX_NAME_LEN], password[MAX_NAME_LEN];
    float price;

    while (1) {
        printf("\nSuper Shop Management System\n");
        printf("1. Sign Up\n");
        printf("2. Add Product (Admin Only)\n");
        printf("3. Search Products\n");
        printf("4. Process Order\n");
        printf("5. Update Order Status\n");
        printf("6. Generate Sales Report\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                printf("Enter 1 for admin, 0 for regular user: ");
                scanf("%d", &isAdmin);
                signUp(username, password, isAdmin);
                break;
            case 2:
                printf("Enter your user ID: ");
                scanf("%d", &userId);
                printf("Enter product ID: ");
                scanf("%d", &productId);
                printf("Enter product name: ");
                scanf("%s", keyword);  
                printf("Enter product price: ");
                scanf("%f", &price);
                printf("Enter product stock: ");
                scanf("%d", &quantity);
                addProduct(userId, productId, keyword, price, quantity);
                break;
            case 3:
                printf("Enter keyword to search: ");
                scanf("%s", keyword);
                searchProducts(keyword);
                break;
            case 4:
                printf("Enter product ID to order: ");
                scanf("%d", &productId);
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                processOrder(productId, quantity);
                break;
            case 5:
                printf("Enter order ID to update: ");
                scanf("%d", &orderId);
                printf("Enter new status: ");
                scanf("%s", keyword);  
                updateOrderStatus(orderId, keyword);
                break;
            case 6:
                printf("Enter keyword for sales report: ");
                scanf("%s", keyword);
                generateSalesReport(keyword);
                break;
            case 7:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
