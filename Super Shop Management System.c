#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// File paths for storing data
#define PRODUCTS_FILE "products.txt"
#define USERS_FILE "users.txt"
#define ORDERS_FILE "orders.txt"

// Structure Definitions
struct Product {
    int id;
    char name[50];
    float price;
    int stock;
};

struct User {
    char username[50];
    char password[50];
};

struct CartItem {
    int productId;
    int quantity;
};

// Global cart for the user
struct CartItem cart[100];
int cartSize = 0;
int isRegistered = 0; // Track registration status
int isAdmin = 0;  // Declare globally


// Function Prototypes
void adminMenu();
void userMenu();
void clrscr();
void addProduct();
void editProduct();
void reorderProduct();
void viewProducts();
void registerUser();
void searchProducts();
void manageCart();
void addToCart();
void removeFromCart();
void viewCart();
void completePurchase();
void saveProduct(struct Product p);
void updateProduct(struct Product p);

// Main Function
int main() {
    int choice;

    while (1) {
        clrscr();
        printf("Welcome to Super Shop Management System\n\n");
        printf("1. Admin menu\n");
        printf("2. User menu\n");
        printf("3. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminMenu();
                break;
            case 2:
                userMenu();
                break;
            case 3:
                printf("Thank you for using the system!\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

void clrscr() {
    // Clear screen for Windows
    system("cls");
}

// Admin Functions
void adminMenu() {
    int choice;
    isAdmin = 1;  // Set the flag to true when admin logs in
    while (1) {
        clrscr();
        printf("-------------Admin Menu-------------\n\n");
        printf("1. Add Product\n");
        printf("2. Edit Product\n");
        printf("3. Reorder Product\n");
        printf("4. View Products\n");
        printf("5. Logout\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                editProduct();
                break;
            case 3:
                reorderProduct();
                break;
            case 4:
                viewProducts();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void addProduct() {
    clrscr();
    struct Product p;
    int addMore;

    do {
        printf("-------------Add Product-------------\n\n");
        printf("Enter Product ID: ");
        scanf("%d", &p.id);
        printf("Enter Product Name: ");
        scanf("%s", p.name);
        printf("Enter Product Price: ");
        scanf("%f", &p.price);
        printf("Enter Product Stock: ");
        scanf("%d", &p.stock);

        saveProduct(p);
        printf("Product added successfully!\n");

        printf("\nDo you want to add more products?\n\n1.Yes, 2.No\nPress 1 or 2 : ");
        scanf("%d", &addMore);
        clrscr();

    } while (addMore == 1);

    printf("\nReturning to Admin Menu...\n");
    system("pause");
}
void editProduct() {
    int continueEditing = 1; // Variable to control the loop

    do {
        clrscr();
        int productId;
        printf("-------------Edit Product-------------\n\n");
        printf("Enter Product ID to edit: ");
        scanf("%d", &productId);

        FILE *file = fopen(PRODUCTS_FILE, "r");
        FILE *tempFile = fopen("temp.txt", "w");

        if (file == NULL || tempFile == NULL) {
            printf("Error opening files!\n");
            if (file) fclose(file);
            if (tempFile) fclose(tempFile);
            system("pause");
            return;
        }

        struct Product p;
        int found = 0;

        while (fscanf(file, "%d %s %f %d", &p.id, p.name, &p.price, &p.stock) != EOF) {
            if (p.id == productId) {
                printf("Enter New Product Name: ");
                scanf("%s", p.name);
                printf("Enter New Product Price: ");
                scanf("%f", &p.price);
                printf("Enter New Product Stock: ");
                scanf("%d", &p.stock);
                found = 1;
            }
            // Write updated or original product to temp file
            fprintf(tempFile, "%d %s %.2f %d\n", p.id, p.name, p.price, p.stock);
        }

        fclose(file);
        fclose(tempFile);

        if (found) {
            remove(PRODUCTS_FILE);
            rename("temp.txt", PRODUCTS_FILE);
            printf("Product updated successfully!\n");
        } else {
            remove("temp.txt"); // Clean up temp file if product not found
            printf("Product not found!\n");
        }

        // Ask if the user wants to edit more products
        printf("\nDo you want to edit more products?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("Press 1 or 2: ");
        scanf("%d", &continueEditing);

    } while (continueEditing == 1);

    // Redirect to admin menu
    printf("\nReturning to Admin Menu...\n");
    system("pause");
    adminMenu(); // Call the admin menu function (replace with your function's name if different)
}


void reorderProduct() {
    int continueReordering = 1; // Variable to control the loop

    do {
        clrscr();
        int productId, additionalStock;
        printf("-------------Reorder Product-------------\n\n");
        printf("Enter Product ID: ");
        scanf("%d", &productId);
        printf("Enter Stock to Add: ");
        scanf("%d", &additionalStock);

        FILE *file = fopen(PRODUCTS_FILE, "r");
        FILE *tempFile = fopen("temp.txt", "w");
        if (file == NULL || tempFile == NULL) {
            printf("Error opening file!\n");
            if (file) fclose(file);
            if (tempFile) fclose(tempFile);
            system("pause");
            return;
        }

        struct Product p;
        int found = 0;

        while (fscanf(file, "%d %s %f %d", &p.id, p.name, &p.price, &p.stock) != EOF) {
            if (p.id == productId) {
                p.stock += additionalStock; // Update stock
                found = 1;
            }
            fprintf(tempFile, "%d %s %.2f %d\n", p.id, p.name, p.price, p.stock);
        }

        fclose(file);
        fclose(tempFile);

        if (found) {
            remove(PRODUCTS_FILE);
            rename("temp.txt", PRODUCTS_FILE);
            printf("Stock updated successfully!\n");
        } else {
            remove("temp.txt");
            printf("Product not found!\n");
        }

        // Ask if the user wants to reorder more products
        printf("\nDo you want to reorder more products?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("Press 1 or 2: ");
        scanf("%d", &continueReordering);

    } while (continueReordering == 1);

    // Redirect to admin menu
    printf("\nReturning to Admin Menu...\n");
    system("pause");
    adminMenu(); // Call the admin menu function (replace with your function's name if different)
}
// -----------------------------------------------ANAS-----------------------------------------------
void saveProduct(struct Product p) {
    FILE *file = fopen(PRODUCTS_FILE, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%d %s %.2f %d\n", p.id, p.name, p.price, p.stock);
    fclose(file);
}

void updateProduct(struct Product p) {
    FILE *file = fopen(PRODUCTS_FILE, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening files!\n");
        return;
    }

    struct Product temp;
    while (fscanf(file, "%d %s %f %d", &temp.id, temp.name, &temp.price, &temp.stock) != EOF) {
        if (temp.id == p.id) {
            fprintf(tempFile, "%d %s %.2f %d\n", p.id, p.name, p.price, p.stock);
        } else {
            fprintf(tempFile, "%d %s %.2f %d\n", temp.id, temp.name, temp.price, temp.stock);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(PRODUCTS_FILE);
    rename("temp.txt", PRODUCTS_FILE);
}

void viewProducts() {
    clrscr();

    // Check registration only for the end-user, not the admin
    if (!isRegistered && !isAdmin) {
        printf("Without registering, you can't see products.\n");
        system("pause");
        return;
    }

    printf("-------------Product List-------------\n");
    FILE *file = fopen(PRODUCTS_FILE, "r");
    if (file == NULL) {
        printf("No products found!\n");
        system("pause");
        return;
    }

    struct Product p;
    // Header with aligned columns
    printf("%-8s %-20s %-10s %-10s\n", "ID", "Name", "Price", "Stock");
    printf("--------------------------------------------------------\n");
    
    // Print each product with formatted alignment
    while (fscanf(file, "%d %s %f %d", &p.id, p.name, &p.price, &p.stock) != EOF) {
        printf("%-8d %-20s %-10.2f %-10d\n", p.id, p.name, p.price, p.stock);
    }
    printf("--------------------------------------------------------\n");

    fclose(file);
    system("pause");
}


// User Functions
void userMenu() {
    int choice;
    while (1) {
        clrscr();
        printf("User Menu\n");
        printf("1. Register\n");
        printf("2. View Products\n");
        printf("3. Search Products\n");
        printf("4. Manage Cart\n");
        printf("5. Complete Purchase\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                viewProducts();
                break;
            case 3:
                searchProducts();
                break;
            case 4:
                manageCart();
                break;
            case 5:
                completePurchase();
                break;
            case 6:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void registerUser() {
    clrscr();
    char username[50], password[50];
    printf("Register\n");
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        system("pause");
        return;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);

    isRegistered = 1; // Set registration status
    printf("\nRegistration successful!\n");
    system("pause");
}

void searchProducts() {
    clrscr();
    char keyword[50];

       // Check if the user is registered
    if (!isRegistered) {
        printf("You must register before adding items to the cart.\n");
        system("pause");
        return;
    }

    printf("Search Products\n");
    printf("Enter product name keyword: ");
    scanf("%s", keyword);

    FILE *file = fopen(PRODUCTS_FILE, "r");
    if (file == NULL) {
        printf("No products found!\n");
        system("pause");
        return;
    }

    struct Product p;
    int found = 0;
    while (fscanf(file, "%d %s %f %d", &p.id, p.name, &p.price, &p.stock) != EOF) {
        if (strstr(p.name, keyword) != NULL) {
            printf("ID: %d, Name: %s, Price: %.2f, Stock: %d\n", p.id, p.name, p.price, p.stock);
            found = 1;
        }
    }

    if (!found) {
        printf("No products match your search!\n");
    }

    fclose(file);
    system("pause");
}

// -----------------------------------------------SHEMU-----------------------------------------------

void manageCart() {
    int choice;
    while (1) {
        clrscr();
        printf("Manage Cart\n");
        printf("1. Add to Cart\n");
        printf("2. Remove from Cart\n");
        printf("3. View Cart\n");
        printf("4. Back to User Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addToCart();
                break;
            case 2:
                removeFromCart();
                break;
            case 3:
                viewCart();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void addToCart() {
    int continueAdding = 1; // Variable to control the loop

    do {
        clrscr();

        // Check if the user is registered
        if (!isRegistered) {
            printf("You must register before adding items to the cart.\n");
            system("pause");
            return;
        }

        // Display the current product list
        viewProducts();

        int productId, quantity;
        printf("-------------Add to Cart-------------\n\n");
        printf("Enter Product ID: ");
        scanf("%d", &productId);
        printf("Enter Quantity: ");
        scanf("%d", &quantity);

        FILE *file = fopen(PRODUCTS_FILE, "r");
        if (file == NULL) {
            printf("Error opening file!\n");
            system("pause");
            return;
        }

        struct Product p;
        int found = 0;

        while (fscanf(file, "%d %s %f %d", &p.id, p.name, &p.price, &p.stock) != EOF) {
            if (p.id == productId && p.stock >= quantity) {
                cart[cartSize].productId = productId;
                cart[cartSize].quantity = quantity;
                cartSize++;
                p.stock -= quantity;
                updateProduct(p); // Update the product in the inventory
                found = 1;
                break;
            }
        }

        fclose(file);

        if (found) {
            printf("\nProduct added to cart successfully!\n");
        } else {
            printf("\nProduct not found or insufficient stock!\n");
        }

        // Ask if the user wants to add more products
        printf("\nDo you want to add more products to the cart?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("Press 1 or 2: ");
        scanf("%d", &continueAdding);

    } while (continueAdding == 1);

    // Redirect based on user type
    if (isAdmin) {
        printf("\nReturning to Admin Menu...\n");
        system("pause");
        adminMenu(); // Redirect to admin menu
    } else {
        printf("\nReturning to User Menu...\n");
        system("pause");
        userMenu(); // Redirect to user menu (replace with your function's name if different)
    }
}

void removeFromCart() {
    clrscr();
    int productId;

     // Check if the user is registered
    if (!isRegistered) {
        printf("You must register before adding items to the cart.\n");
        system("pause");
        return;
    }

    // Display the current product list
    viewProducts();

    printf("Remove from Cart\n");
    printf("Enter Product ID to remove: ");
    scanf("%d", &productId);

    int found = 0;
    for (int i = 0; i < cartSize; i++) {
        if (cart[i].productId == productId) {
            for (int j = i; j < cartSize - 1; j++) {
                cart[j] = cart[j + 1];
            }
            cartSize--;
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Product removed from cart!\n");
    } else {
        printf("Product not found in cart!\n");
    }

    system("pause");
}

void viewCart() {
    clrscr();
    printf("-------------Your Cart-------------\n\n");

    if (cartSize == 0) {
        printf("Cart is empty!\n");
    } else {
        FILE *file = fopen(PRODUCTS_FILE, "r");
        if (file == NULL) {
            printf("Error opening product file!\n");
            system("pause");
            return;
        }

        struct Product p;

        for (int i = 0; i < cartSize; i++) {
            // Reset the file pointer to the beginning for each cart item
            rewind(file);
            int found = 0;

            // Search for the product in the inventory file
            while (fscanf(file, "%d %s %f %d", &p.id, p.name, &p.price, &p.stock) != EOF) {
                if (p.id == cart[i].productId) {
                    printf("Product ID: %d, Name: %s, Quantity: %d\n", p.id, p.name, cart[i].quantity);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("Product ID: %d (Product details not found!)\n", cart[i].productId);
            }
        }

        fclose(file);
    }

    printf("\n-----------------------------------\n");
    system("pause");
}

void completePurchase() {
    clrscr();
    if (cartSize == 0) {
        printf("Cart is empty! Cannot complete purchase.\n");
    } else {
        FILE *file = fopen(PRODUCTS_FILE, "r");
        FILE *tempFile = fopen("temp.txt", "w");
        if (file == NULL || tempFile == NULL) {
            printf("Error opening file!\n");
            system("pause");
            return;
        }

        printf("Your Purchase Summary:\n");
        printf("--------------------------------------------------\n");
        printf("ID\tName\t\tPrice\tQuantity\tTotal\n");
        printf("--------------------------------------------------\n");

        struct Product p;
        float grandTotal = 0.0;

        for (int i = 0; i < cartSize; i++) {
            rewind(file); // Reset file pointer to the beginning
            while (fscanf(file, "%d %s %f %d", &p.id, p.name, &p.price, &p.stock) != EOF) {
                if (p.id == cart[i].productId) {
                    // Calculate total price for the item
                    float total = p.price * cart[i].quantity;
                    printf("%d\t%s\t\t%.2f\t%d\t\t%.2f\n", p.id, p.name, p.price, cart[i].quantity, total);
                    grandTotal += total;

                    // Reduce stock after purchase
                    p.stock -= cart[i].quantity;

                    // Write updated product back to the temp file
                    fprintf(tempFile, "%d %s %.2f %d\n", p.id, p.name, p.price, p.stock);
                    break;
                }
            }
        }

        printf("--------------------------------------------------\n");
        printf("Grand Total: %.2f\n", grandTotal);
        printf("--------------------------------------------------\n");

        fclose(file);
        fclose(tempFile);

        // Replace the original product file with the updated file
        remove(PRODUCTS_FILE);
        rename("temp.txt", PRODUCTS_FILE);

        // Clear the cart after purchase
        cartSize = 0;
        printf("Purchase completed successfully!\n");
    }
    system("pause");
}
