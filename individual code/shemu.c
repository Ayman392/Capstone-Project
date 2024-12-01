#include <stdio.h>
#include <string.h>

struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
};

void logIn();
void addProduct(struct Product products[], int *count);
void editProduct(struct Product products[], int count);
void reorderProduct(struct Product products[], int count);
void manageStock(struct Product products[], int count);

int main() {
    struct Product products[80];
    int productCount = 0;
    int choice;

    printf("WELCOME to the Super Shop Management System\n");
    logIn();

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Product\n");
        printf("2. Edit Product\n");
        printf("3. Reorder Product\n");
        printf("4. Manage Stock\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct(products, &productCount);
                break;
            case 2:
                editProduct(products, productCount);
                break;
            case 3:
                reorderProduct(products, productCount);
                break;
            case 4:
                manageStock(products, productCount);
                break;
            case 5:
                printf("Exit\n");
                return 0;
            default:
                printf("Invalid choice. Please try again later: ");
        }
    }
    return 0;
}

void logIn() {
    char username[50], password[30];
    printf("Log In:\n");
    printf("Username:\n");
    scanf("%s", username);
    printf("Password:\n");
    scanf("%s", password);
    printf("Login successful:\n");
}

void addProduct(struct Product products[], int *count) {
    struct Product newProduct;
    printf("Enter product details:\n");
    printf("ID: \n");
    scanf("%d", &newProduct.id);
    printf("Name: \n");
    scanf("%s", newProduct.name); 
    printf("Price: \n");
    scanf("%f", &newProduct.price);
    printf("Quantity: \n");
    scanf("%d", &newProduct.quantity);
    products[*count] = newProduct;
    (*count)++;
    printf("Product added successfully: \n");
}

void editProduct(struct Product products[], int count) {
    int id, i;
    printf("Enter the product ID to edit: \n");
    scanf("%d", &id);

    for (i = 0; i < count; i++) {
        if (products[i].id == id) {
            printf("Editing product %d:\n", id);
            printf("New Name: \n");
            scanf("%s", products[i].name); // Corrected string input
            printf("New Price: \n");
            scanf("%f", &products[i].price);
            printf("New Quantity:\n");
            scanf("%d", &products[i].quantity);
            printf("Product details updated successfully: \n");
            return;
        }
    }
    printf("Product ID not found: \n");
}

void reorderProduct(struct Product products[], int count) {
    int id, i, reorderQuantity;
    printf("Enter the product ID to reorder: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++) {
        if (products[i].id == id) {
            printf("Enter reorder quantity for product %d: ", id);
            scanf("%d", &reorderQuantity);
            products[i].quantity += reorderQuantity;
            printf("Product reordered successfully! New quantity: %d\n", products[i].quantity);
            return;
        }
    }
    printf("Product ID not found\n");
}

void manageStock(struct Product products[], int count) {
    printf("Stock Management:\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Name: %s, Quantity: %d\n", products[i].id, products[i].name, products[i].quantity);
    }
}
