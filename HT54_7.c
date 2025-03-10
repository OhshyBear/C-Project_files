#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100  // Maximum number of records in orders data file

/* Function prototypes */
int input_orders(int order_arr[], int product_arr[], int quantity_arr[], float price_arr[], int limit);
void print_orders(const int order_arr[], const int product_arr[], const int quantity_arr[], const float price_arr[], int size);
int print_order_report(const int order_arr[], const int product_arr[], const int quantity_arr[], const float price_arr[], int size);
int print_product_report(const int order_arr[], const int product_arr[], const int quantity_arr[], const float price_arr[], int size);  // ADD CODE #3-1

int main(void) {
    int orders[MAX];     // Store order IDs
    int products[MAX];   // Store product IDs
    int quantities[MAX]; // Store ordered quantities
    float prices[MAX];   // Store product prices
    int size = 0;

    size = input_orders(orders, products, quantities, prices, MAX);
    print_orders(orders, products, quantities, prices, size);

    print_order_report(orders, products, quantities, prices, size);  // ADD CODE #4
    print_product_report(orders, products, quantities, prices, size);  // ADD CODE #4

    return 0;
}

/* Revise input_orders() to read data from "orders.txt" */
int input_orders(int order_arr[], int product_arr[], int quantity_arr[], float price_arr[], int limit) {
    FILE *file = fopen("orders.txt", "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file 'orders.txt'.\n");
        return 0;
    }

    int size = 0;
    printf("Reading orders from 'orders.txt'...\n");
    while (size < limit && fscanf(file, "%d,%d,%d,%f", 
           &order_arr[size], &product_arr[size], 
           &quantity_arr[size], &price_arr[size]) == 4) {
        size++;
    }
    fclose(file);
    printf("Done loading data from file.\n");
    return size;
}

/* Prints "size" records of order ID, product ID, ordered quantity, and price */
void print_orders(const int order_arr[], const int product_arr[], const int quantity_arr[], const float price_arr[], int size) {
    if (size <= 0) {
        fprintf(stderr, "Error: Invalid size %d. Abort print.\n", size);
        return;
    }

    printf("\nOrderID | ProductID | Quantity | Price\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("%d | %d | %d | $%.2f\n", order_arr[i], product_arr[i], quantity_arr[i], price_arr[i]);
    }
    printf("----------------------------------------\n");
}

/* Prints subtotals per order */
int print_order_report(const int order_arr[], const int product_arr[], const int quantity_arr[], const float price_arr[], int size) {
    if (size <= 0) {
        fprintf(stderr, "Error: No orders to process.\n");
        return 0;
    }

    printf("\nOrder Report:\n");
    printf("----------------------------------------\n");

    int current_order = order_arr[0];
    float subtotal = 0;

    for (int i = 0; i < size; i++) {
        if (order_arr[i] != current_order) {
            printf("OrderID %d | Subtotal: $%.2f\n", current_order, subtotal);
            current_order = order_arr[i];
            subtotal = 0;
        }

        float item_total = quantity_arr[i] * price_arr[i];
        printf("Test - %d | %d | $%.2f\n", order_arr[i], product_arr[i], item_total);
        subtotal += item_total;
    }
    printf("OrderID %d | Subtotal: $%.2f\n", current_order, subtotal);
    printf("----------------------------------------\n");
    return 1;
}

/* Prints subtotals per product */
int print_product_report(const int order_arr[], const int product_arr[], const int quantity_arr[], const float price_arr[], int size) {
    if (size <= 0) {
        fprintf(stderr, "Error: No products to process.\n");
        return 0;
    }

    printf("\nReport - subtotals per product\n");
    printf("----------------------------------------\n");

    // Find unique product IDs
    int unique_products[MAX];
    int unique_count = 0;

    for (int i = 0; i < size; i++) {
        int product = product_arr[i];
        int found = 0;

        for (int j = 0; j < unique_count; j++) {
            if (unique_products[j] == product) {
                found = 1;
                break;
            }
        }

        if (!found) {
            unique_products[unique_count++] = product;
        }
    }

    // Calculate subtotals per product
    for (int i = 0; i < unique_count; i++) {
        int product_id = unique_products[i];
        float subtotal = 0;

        for (int j = 0; j < size; j++) {
            if (product_arr[j] == product_id) {
                float item_total = quantity_arr[j] * price_arr[j];
                printf("Test - %d | %d | $%.2f\n", order_arr[j], product_arr[j], item_total);
                subtotal += item_total;
            }
        }

        printf("ProductID %d | Subtotal: $%.2f\n", product_id, subtotal);
    }

    printf("----------------------------------------\n");
    return 1;
}