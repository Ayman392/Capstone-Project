#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_USERS 50
#define MAX_CART_ITEMS 20
#define MAX_ORDERS 100
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
} User;

typedef struct {
    Product product;
    int quantity;
} CartItem;

typedef struct {
    int orderId;
    int userId;
    CartItem items[MAX_CART_ITEMS];
    int itemCount;
    float total;
} Order;

Product products[MAX_PRODUCTS];
User users[MAX_USERS];
Order orders[MAX_ORDERS];
CartItem cart[MAX_CART_ITEMS];
int productCount = 0;
int userCount = 0;
int orderCount = 0;
int cartItemCount = 0;

void signUp(const char *username, const char *password) {
    if (userCount < MAX_USERS) {
        users[userCount].userId = userCount + 1;
        strncpy(users[userCount].username, username, MAX_NAME_LEN);
        strncpy(users[userCount].password, password, MAX_NAME_LEN);
        userCount++;
        printf("User registered successfully!\n");
    } else {
        printf("User limit reached!\n");
    }
}

int logIn(const char *username, const char *password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful!\n");
            return users[i].userId;
        }
    }
    printf("Invalid username or password.\n");
    return -1;
}

void addProduct(int id, const char *name, float price, int stock) {
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
}

void viewProducts() {
    printf("Product List:\n");
    for (int i = 0; i < productCount; i++) {
        printf("ID: %d, Name: %s, Price: %.2f, Stock: %d\n", products[i].id, products[i].name, products[i].price, products[i].stock);
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

void addToCart(int productId, int quantity) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == productId) {
            if (products[i].stock >= quantity) {
                products[i].stock -= quantity;
                cart[cartItemCount].product = products[i];
                cart[cartItemCount].quantity = quantity;
                cartItemCount++;
                printf("Added %d of %s to cart.\n", quantity, products[i].name);
                return;
            } else {
                printf("Insufficient stock for %s\n", products[i].name);
                return;
            }
        }
    }
    printf("Product ID %d not found\n", productId);
}

void removeFromCart(int productId) {
    for (int i = 0; i < cartItemCount; i++) {
        if (cart[i].product.id == productId) {
            products[i].stock += cart[i].quantity;
            for (int j = i; j < cartItemCount - 1; j++) {
                cart[j] = cart[j + 1];
            }
            cartItemCount--;
            printf("Removed product ID %d from cart.\n", productId);
            return;
        }
    }
    printf("Product ID %d not found in cart\n", productId);
}

void completePurchase(int userId) {
    if (cartItemCount == 0) {
        printf("Your cart is empty!\n");
        return;
    }

    Order newOrder;
    newOrder.orderId = orderCount + 1;
    newOrder.userId = userId;
    newOrder.itemCount = cartItemCount;
    newOrder.total = 0;

    for (int i = 0; i < cartItemCount; i++) {
        newOrder.items[i] = cart[i];
        newOrder.total += cart[i].product.price * cart[i].quantity;
    }

    orders[orderCount] = newOrder;
    orderCount++;
    cartItemCount = 0; // Empty the cart

    printf("Purchase completed! Order ID: %d, Total: %.2f\n", newOrder.orderId, newOrder.total);
}

void trackOrders(int userId) {
    printf("Orders for User ID %d:\n", userId);
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].userId == userId) {
            printf("Order ID: %d, Total: %.2f\n", orders[i].orderId, orders[i].total);
            for (int j = 0; j < orders[i].itemCount; j++) {
                printf("  Product: %s, Quantity: %d, Price: %.2f\n",
                       orders[i].items[j].product.name,
                       orders[i].items[j].quantity,
                       orders[i].items[j].product.price);
            }
        }
    }
}

int main() {
    int choice, userId = -1, productId, quantity;
    char username[MAX_NAME_LEN], password[MAX_NAME_LEN], keyword[MAX_NAME_LEN];

    // Adding some sample products
    addProduct(1, "Apple", 0.5, 100);
    addProduct(2, "Banana", 0.3, 150);
    addProduct(3, "Orange", 0.7, 80);

    while (1) {
        printf("\nSuper Shop Management System\n");
        printf("1. Sign Up\n");
        printf("2. Log In\n");
        printf("3. View Products\n");
        printf("4. Search Products\n");
        printf("5. Add to Cart\n");
        printf("6. Remove from Cart\n");
        printf("7. Complete Purchase\n");
        printf("8. Track Orders\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                signUp(username, password);
                break;
            case 2:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                userId = logIn(username, password);
                break;
            case 3:
                viewProducts();
                break;
            case 4:
                printf("Enter keyword to search: ");
                scanf("%s", keyword);
                searchProducts(keyword);
                break;
            case 5:
                if (userId == -1) {
                    printf("Please log in first.\n");
                    break;
                }
                printf("Enter product ID to add to cart: ");
                scanf("%d", &productId);
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                addToCart(productId, quantity);
                break;
            case 6:
                if (userId == -1) {
                    printf("Please log in first.\n");
                    break;
                }
                printf("Enter product ID to remove from cart: ");
                scanf("%d", &productId);
                removeFromCart(productId);
                break;
            case 7:
                if (userId == -1) {
                    printf("Please log in first.\n");
                    break;
                }
                completePurchase(userId);
                break;
            case 8:
                if (userId == -1) {
                    printf("Please log in first.\n");
                    break;
                }
                trackOrders(userId);
                break;
            case 9:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
