#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_ORDERS 100
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
} Order;

Product products[MAX_PRODUCTS];
Order orders[MAX_ORDERS];
int productCount = 0;
int orderCount = 0;

void addProduct(int id, const char *name, float price, int stock) {
    if (productCount < MAX_PRODUCTS) {
        products[productCount].id = id;
        strncpy(products[productCount].name, name, MAX_NAME_LEN);
        products[productCount].price = price;
        products[productCount].stock = stock;
        productCount++;
    } else {
        printf("Product list is full!\n");
    }
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

int main() {
    addProduct(1, "Apple", 0.5, 100);
    addProduct(2, "Banana", 0.3, 150);
    addProduct(3, "Orange", 0.7, 80);

    char keyword[MAX_NAME_LEN];
    int productId, quantity, orderId;
    int choice;
    char status[20];

    while (1) {
        printf("\nSuper Shop Management System\n");
        printf("1. Add Product Details\n");
        printf("2. Search Products\n");
        printf("3. Process Order\n");
        printf("4. Update Order Status\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter product ID: ");
                scanf("%d", &productId);
                printf("Enter product name: ");
                scanf("%s", keyword);  // Using keyword as a temporary variable for product name
                printf("Enter product price: ");
                scanf("%f", &products[productCount].price);
                printf("Enter product stock: ");
                scanf("%d", &products[productCount].stock);
                addProduct(productId, keyword, products[productCount].price, products[productCount].stock);
                break;
            case 2:
                printf("Enter keyword to search: ");
                scanf("%s", keyword);
                searchProducts(keyword);
                break;
            case 3:
                printf("Enter product ID to order: ");
                scanf("%d", &productId);
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                processOrder(productId, quantity);
                break;
            case 4:
                printf("Enter order ID to update: ");
                scanf("%d", &orderId);
                printf("Enter new status: ");
                scanf("%s", status);
                updateOrderStatus(orderId, status);
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
