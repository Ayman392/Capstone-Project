#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100

typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;

void addProductDetails() {
    if (productCount >= MAX_PRODUCTS) {
        printf("Product list is full. Cannot add more products.\n");
        return;
    }

    Product newProduct;
    newProduct.id = productCount + 1;

    printf("Enter product name: ");
    scanf("%s", newProduct.name);

    printf("Enter product price: ");
    scanf("%f", &newProduct.price);

    printf("Enter product quantity: ");
    scanf("%d", &newProduct.quantity);

    products[productCount] = newProduct;
    productCount++;

    printf("Product added successfully!\n");
}

void displayProducts() {
    printf("Product List:\n");
    for (int i = 0; i < productCount; i++) {
        printf("ID: %d, Name: %s, Price: %.2f, Quantity: %d\n",
               products[i].id, products[i].name, products[i].price, products[i].quantity);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nSuper Shop Management System\n");
        printf("1. Add Product Details\n");
        printf("2. Display Products\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProductDetails();
                break;
            case 2:
                displayProducts();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

/*
### Explanation:

1. **Structure Definition**: The `Product` structure stores the product ID, name, price, and quantity.
2. **Product Array and Counter**: 
   - `products` array stores the list of products.
   - `productCount` keeps track of the number of products.
3. **Add Product Details Function**:
   - Prompts the user to enter product details (name, price, quantity).
   - Adds the new product to the `products` array and increments `productCount`.
4. **Display Products Function**:
   - Prints the list of all products, showing their ID, name, price, and quantity.
5. **Main Function**:
   - Provides a menu to add product details, display products, or exit the program.
   - Executes the selected option based on user input.
*/

