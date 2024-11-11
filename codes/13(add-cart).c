#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_CART_ITEMS 50

typedef struct {
    int id;
    char name[50];
    float price;
} Product;

typedef struct {
    Product product;
    int quantity;
} CartItem;

Product products[MAX_PRODUCTS];
CartItem cart[MAX_CART_ITEMS];
int productCount = 0;
int cartItemCount = 0;

void addProduct(int id, char name[], float price) {
    products[productCount].id = id;
    strcpy(products[productCount].name, name);
    products[productCount].price = price;
    productCount++;
}

void searchProduct(char keyword[]) {
    printf("Search results for '%s':\n", keyword);
    for (int i = 0; i < productCount; i++) {
        if (strstr(products[i].name, keyword) != NULL) {
            printf("ID: %d, Name: %s, Price: %.2f\n", products[i].id, products[i].name, products[i].price);
        }
    }
}

void addToCart(int productId, int quantity) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == productId) {
            cart[cartItemCount].product = products[i];
            cart[cartItemCount].quantity = quantity;
            cartItemCount++;
            printf("Added %d of %s to cart.\n", quantity, products[i].name);
            return;
        }
    }
    printf("Product with ID %d not found.\n", productId);
}

void viewCart() {
    printf("Shopping Cart:\n");
    for (int i = 0; i < cartItemCount; i++) {
        printf("Product: %s, Quantity: %d, Total Price: %.2f\n", cart[i].product.name, cart[i].quantity, cart[i].product.price * cart[i].quantity);
    }
}

int main() {
    addProduct(1, "Apple", 0.5);
    addProduct(2, "Banana", 0.3);
    addProduct(3, "Orange", 0.8);

    char keyword[50];
    int productId, quantity, choice;

    while (1) {
        printf("\nSuper Shop Management System\n");
        printf("1. Add Product Details\n");
        printf("2. Search Products\n");
        printf("3. Add to Cart\n");
        printf("4. View Cart\n");
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
                addProduct(productId, keyword, products[productCount].price);
                break;
            case 2:
                printf("Enter keyword to search: ");
                scanf("%s", keyword);
                searchProduct(keyword);
                break;
            case 3:
                printf("Enter product ID to add to cart: ");
                scanf("%d", &productId);
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                addToCart(productId, quantity);
                break;
            case 4:
                viewCart();
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}


// ### Explanation:

// 1. **Structure Definitions**:
//    - `Product` structure stores product ID, name, and price.
//    - `CartItem` structure stores a product and its quantity.
// 2. **Product and Cart Arrays**:
//    - `products` array stores the list of products.
//    - `cart` array stores the items added to the cart.
// 3. **Counters**:
//    - `productCount` keeps track of the number of products.
//    - `cartItemCount` keeps track of the number of items in the cart.
// 4. **Add Product Function**:
//    - Adds a new product to the `products` array.
// 5. **Search Product Function**:
//    - Searches for products containing the keyword in their name and displays their details.
// 6. **Add to Cart Function**:
//    - Adds a product to the cart by product ID and specified quantity.
// 7. **View Cart Function**:
//    - Displays the items in the shopping cart along with their quantities and total prices.
// 8. **Main Function**:
//    - Provides a menu to add product details, search products, add to cart, view cart, or exit the program.
//    - Executes the selected option based on user input.
