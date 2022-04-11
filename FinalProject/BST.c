#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct _product
{
    int code;
    char name[50];
    float price;
    int qt_stock;
    struct _product *left,*rigth;
};
typedef struct _product Product;

typedef struct
{
    Product *root;
} LProduct;

struct _cart
{
    int codeprod;
    int qt_buy;
    struct _product *next;
};
typedef struct _cart Cart;



void printProducts(Product *root)
{
    Product *aux = products.first;

    for (; aux != NULL; aux = aux->next)
    {
        printf("Code: %d Name: %s, Price:%.2f, Quantity in stock: %d\n", aux->code, aux->name, aux->price, aux->qt_stock);
    }
}
Product* addProduct(Product* root, Product p)
{
    Product *aux = root;
    Product *product = (Product *)malloc(sizeof(Product));
    *product = p;

    if (root == NULL)
    {
        return product;
    }

    else{
        if(root->code >= product->code){
            root->left = addProduct(root->left, p);
        }
        else{
            root->rigth = addProduct(root->rigth, p);
        }
    }
   
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
    fprintf(fp,"\n%d,%s,%.2f,%d",product.code, product.name, product.price, product.qt_stock);
    fclose(fp);
    

}


LProduct createNewProduct(LProduct products)
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
    products = addProduct(products, product);
    writeProductInFile(product);
}



LProduct init_productList()
{
    LProduct products;
    products.root = NULL;
    return products;
}

int main()
{
    LProduct products = init_productList();
    products = readFile(products);
    products = createNewProduct(products);
    printProducts(products);
    return 0;
}