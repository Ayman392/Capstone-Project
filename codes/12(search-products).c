#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_NAME_LEN 50

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
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

void searchProducts(char keyword[]) {
    printf("Search results for '%s':\n", keyword);
    for (int i = 0; i < productCount; i++) {
        if (strstr(products[i].name, keyword) != NULL) {
            printf("ID: %d, Name: %s, Price: %.2f, Quantity: %d\n",
                   products[i].id, products[i].name, products[i].price, products[i].quantity);
        }
    }
}

int main() {
    int choice;
    char keyword[MAX_NAME_LEN];

    while (1) {
        printf("\nSuper Shop Management System\n");
        printf("1. Add Product Details\n");
        printf("2. Search Products\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProductDetails();
                break;
            case 2:
                printf("Enter keyword to search: ");
                scanf("%s", keyword);
                searchProducts(keyword);
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}


// ### Explanation:

// 1. **Structure Definition**: The `Product` structure stores the product ID, name, price, and quantity.
// 2. **Product Array and Counter**:
//    - `products` array stores the list of products.
//    - `productCount` keeps track of the number of products.
// 3. **Add Product Details Function**:
//    - Prompts the user to enter product details (name, price, quantity).
//    - Adds the new product to the `products` array and increments `productCount`.
// 4. **Search Products Function**:
//    - Prompts the user to enter a keyword.
//    - Searches for products whose names contain the keyword and displays their details.
// 5. **Main Function**:
//    - Provides a menu to add product details, search for products, or exit the program.
//    - Executes the selected option based on user input.

// This basic program allows you to add products to a super shop management system and search for them using keywords. Feel free to expand it with more features as needed!