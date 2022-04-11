#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct _product
{
    int code;
    char name[50];
    float price;
    int qt_stock;
    struct _product *next, *prev;
};
typedef struct _product Product;

typedef struct
{
    Product *first, *last;
} LProduct;

struct _cartItem
{
    Product *product;
    int qt_buy;
    struct _cartItem *next;
    struct _cartItem *prev;
};
typedef struct _cartItem CartItem;

struct _cart
{
    CartItem *first, *last;
};
typedef struct _cart Cart;

void printSingleProduct(Product *aux)
{
    printf("Code: %d Name: %s, Price:%.2f, Quantity in stock: %d\n", aux->code, aux->name, aux->price, aux->qt_stock);
}

void freeMemory(Product *p, CartItem *c)
{
    Product *aux = p;

    while (aux != NULL)
    {
        p = aux->next;
        free(aux);
        aux = p;
    }
    CartItem *auxC = c;
    while (auxC != NULL)
    {
        c = auxC->next;
        free(auxC);
        auxC = c;
    }
    exit(1);
}

void printProducts(LProduct products)
{
    Product *aux = products.first;
    if (aux == NULL)
    {
        printf("No products found\n");
    }
    for (; aux != NULL; aux = aux->next)
    {
        printSingleProduct(aux);
    }
}

LProduct addProduct(LProduct products, Product p)
{
    Product *aux = products.first;
    Product *product = (Product *)malloc(sizeof(Product));
    *product = p;
    product->next = NULL;
    product->prev = NULL;

    if (products.first == NULL)
    {
        products.first = product;
        products.last = product;
        return products;
    }
    products.last->next = product;
    product->prev = products.last;
    products.last = product;
    return products;
}

Product *codeExists(LProduct products, int key)
{
    // try to implement BST
    Product *aux = products.first;
    for (; aux != NULL; aux = aux->next)
    {
        if (aux->code == key)
        {
            return aux;
        }
    }
    return NULL;
}

LProduct readFile(LProduct products)
{
    FILE *fp;
    fp = fopen("products.csv", "r");
    Product product;

    if (fp == NULL)
    {
        printf("Error reading file\n");
        return products;
    }
    while (fscanf(fp, "%d,%[^,],%f,%d", &product.code, product.name, &product.price, &product.qt_stock) != EOF)
    {
        products = addProduct(products, product);
    }
    fclose(fp);
    return products;
}

void writeProductInFile(Product product)
{
    FILE *fp;
    fp = fopen("products.csv", "a");
    fprintf(fp, "%d,%s,%.2f,%d\n", product.code, product.name, product.price, product.qt_stock);

    fclose(fp);
}

void rewriteInFile(LProduct products)
{
    Product *aux = products.first;
    FILE *fp = fopen("products.csv", "w");
    for (; aux != NULL; aux = aux->next)
    {
        fprintf(fp, "%d,%s,%.2f,%d\n", aux->code, aux->name, aux->price, aux->qt_stock);
    }
    fprintf(fp, "\n");

    fclose(fp);
}

LProduct insertNewProduct(LProduct products)
{
    Product product;
    printf("Enter product data:\n");
    printf("Code: ");
    scanf(" %d", &product.code);
    printf("Name: ");
    scanf(" %s", product.name);
    printf("Price: ");
    scanf(" %f", &product.price);
    printf("Quantity in stock: ");
    scanf(" %d", &product.qt_stock);
    if (codeExists(products, product.code) == NULL)
    {
        products = addProduct(products, product);
        writeProductInFile(product);

        return products;
    }

    printf("Product not added: Code %d already exists\n", product.code);
    return products;
}

void searchProduct(LProduct products)
{
    int key;
    printf("Enter code: ");
    scanf(" %d", &key);
    Product *productFound = codeExists(products, key);
    if (productFound == NULL)
    {
        printf("Code : %d not found.\n", key);
        return;
    }
    printSingleProduct(productFound);
}

LProduct init_productList()
{
    LProduct products;
    products.first = NULL;
    return products;
}

LProduct deleteProduct(LProduct products)
{
    int key;
    printf("Enter product code: ");
    scanf(" %d", &key);
    printf("Looking for id %d ...\n", key);

    if (codeExists(products, key) != NULL)
    {

        Product *product = codeExists(products, key);
        if (product == products.first)
        {

            products.first = product->next;
            products.first->prev = NULL;
        }
        else if (product == products.last)
        {
            products.last = product->prev;
            products.last->next = NULL;
        }
        else
        {
            printf("Last %d ...\n", key);

            product->prev->next = product->next;
            product->next->prev = product->prev;
        }
        rewriteInFile(products);
        printf("Deleted!\n");
        return products;
    }
    printf("Code %d not found\n", key);
    return products;
}
Cart addItemToCart(Cart cart, Product *product, int quantity)
{
    CartItem *cartItem = (CartItem *)malloc(sizeof(CartItem));
    CartItem *aux = cart.first;
    cartItem->product = product;
    cartItem->qt_buy = quantity;
    cartItem->next = NULL;
    if (cart.first == NULL)
    {
        cart.first = cartItem;
        cart.last = cartItem;
        return cart;
    }
    cart.last->next = cartItem;
    cartItem->prev = cart.last;
    cart.last = cartItem;

    return cart;
}

void showCart(Cart cart)
{
    float sum = 0;
    CartItem *aux = cart.first;
    if (aux == NULL)
    {
        printf("Shooping cart is empty\n");
        return;
    }
    printf("Cart: \n");
    for (aux = cart.first; aux != NULL; aux = aux->next)
    {
        printf("Product:\n Name: %s\n Price: %.2f\n Quantity: %d\n", aux->product->name, aux->product->price, aux->qt_buy);
        sum += (aux->qt_buy * aux->product->price);
    }
    printf("Total: %.2f\n\n", sum);
}

CartItem *isProductInCart(Cart cart, int key)
{
    CartItem *aux = cart.first;
    for (; aux != NULL; aux = aux->next)
    {
        if (key == aux->product->code)
        {
            return aux;
        }
    }
    return NULL;
}

Cart updateItemInCart(Cart cart, CartItem *item, Product *product)
{
    int quantity;
    printf("It looks like this product is already in your cart.\n");
    printf("Update the quantity (There's %d avaliable in stock): ", product->qt_stock);
    scanf(" %d", &quantity);

    if (quantity <= product->qt_stock)
    {
        item->qt_buy = quantity;
        return cart;
    }
    printf("We don't have that many in stock.\n");
    return cart;
}

Cart buyProduct(LProduct products, Cart cart)
{

    int key, quantity;
    printf("Enter code: ");
    scanf("%d", &key);
    Product *product = codeExists(products, key);
    if (product != NULL)
    {
        CartItem *item = isProductInCart(cart, key);
        if (item != NULL)
        {
            return updateItemInCart(cart, item, product);
        }
        printf("Enter quantity (There's %d avaliable in stock): ", product->qt_stock);
        scanf(" %d", &quantity);

        if (quantity <= product->qt_stock)
        {
            cart = addItemToCart(cart, product, quantity);
            return cart;
        }

        printf("Not enough items in stock. Let's try again\n");
        buyProduct(products, cart);

        return cart;
    }

    printf("Code %d not found\n", key);
}

LProduct updateProductsAfterPurchase(LProduct products, Cart cart)
{
    CartItem *aux = cart.first;
    for (; aux != NULL; aux = aux->next)
    {
        aux->product->qt_stock = aux->product->qt_stock - aux->qt_buy;
    }
    rewriteInFile(products);
}

Cart executeDeleteFromCart(Cart cart, CartItem *item)
{
    if (item == cart.first)
    {
        cart.first = item->next;
        if(cart.first!= NULL){
            cart.first->prev = NULL;
        }
    }
    else if (item == cart.last)
    {
        cart.last = item->prev;
        cart.last->next = NULL;
    }
    else{

        item->prev->next = item->next;
        item->next->prev = item->prev;
    }
    return cart;
    }


Cart removeItemFromCart(Cart cart)
{
    int key;
    printf("Enter product code: ");
    scanf(" %d", &key);
    CartItem *item = isProductInCart(cart, key);
    CartItem *aux = cart.first;
    CartItem *prev = cart.first;

    if (item != NULL)
    {
        cart = executeDeleteFromCart(cart, item);
        return cart;
    }
        printf("We couldn't find this product\n");

    return cart;
}

void shop(LProduct products, Cart cart)
{
    int option;
    printf("Shopping Menu:\n");
    printf("1- Buy product\n2- Show cart\n3- Remove item from cart\n4- Finish purchase\n");
    scanf(" %d", &option);
    switch (option)
    {
    case 1:
        cart = buyProduct(products, cart);
        showCart(cart);
        break;
    case 2:
        showCart(cart);
        break;
    case 3:
        cart = removeItemFromCart(cart);
        shop(products, cart);

    case 4:
        products = updateProductsAfterPurchase(products, cart);
        return;
    }
    shop(products, cart);
}

void menu(LProduct products, Cart cart)
{
    int option;
    printf("1- Add product\n2- Show all products\n3 -Search for product\n4 -Delete product\n5 -Shop\n6-Leave\n");
    scanf(" %d", &option);

    switch (option)
    {
    case 1:
        products = insertNewProduct(products);
        break;
    case 2:
        printProducts(products);
        break;
    case 3:
        searchProduct(products);
        break;
    case 4:
        products = deleteProduct(products);
        break;
    case 5:
        shop(products, cart);
        break;

    default:
        printf("Not a valid option. Choose again\n");
    }
    menu(products, cart);
}

int main()
{
    Cart cart;
    cart.first = NULL;
    LProduct products = init_productList();
    products = readFile(products);
    menu(products, cart);

    return 0;
}