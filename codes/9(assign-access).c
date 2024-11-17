#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_USERS 50
#define MAX_NAME_LEN 50

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    float price;
    int stock;
} Product;

typedef struct {
    int userId;
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];
    int isAdmin; // 0 for regular user, 1 for admin
} User;

Product products[MAX_PRODUCTS];
User users[MAX_USERS];
int productCount = 0;
int userCount = 0;

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

int main() {
    // Sample admin user
    signUp("admin", "adminpass", 1);

    int choice, userId, productId, stock, isAdmin;
    char keyword[MAX_NAME_LEN], username[MAX_NAME_LEN], password[MAX_NAME_LEN];
    float price;

    while (1) {
        printf("\nSuper Shop Management System\n");
        printf("1. Sign Up\n");
        printf("2. Add Product (Admin Only)\n");
        printf("3. Search Products\n");
        printf("4. Exit\n");
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
                scanf("%d", &stock);
                addProduct(userId, productId, keyword, price, stock);
                break;
            case 3:
                printf("Enter keyword to search: ");
                scanf("%s", keyword);
                searchProducts(keyword);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
