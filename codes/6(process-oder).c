#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_NAME_LEN 50

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    float price;
    int stock;
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;

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
                printf("Order processed: %d x %s\n", quantity, products[i].name);
            } else {
                printf("Insufficient stock for %s\n", products[i].name);
            }
            return;
        }
    }
    printf("Product ID %d not found\n", productId);
}

int main() {
    addProduct(1, "Apple", 0.5, 100);
    addProduct(2, "Banana", 0.3, 150);
    addProduct(3, "Orange", 0.7, 80);

    char keyword[MAX_NAME_LEN];
    printf("Enter keyword to search products: ");
    scanf("%s", keyword);
    searchProducts(keyword);

    int productId, quantity;
    printf("Enter product ID to order: ");
    scanf("%d", &productId);
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    processOrder(productId, quantity);

    return 0;
}
