#include <stdio.h>

// Define the structure for each item
struct ITEM {
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
};

// Function to perform simple Bubble Sort on items based on profit/weight ratio
void bubbleSort(struct ITEM items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (items[j].profit_weight_ratio < items[j + 1].profit_weight_ratio) {
                // Swap the items
                struct ITEM temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}

// Fractional knapsack algorithm
float fractionalKnapsack(struct ITEM items[], int n, float capacity) {
    float total_profit = 0.0;

    for (int i = 0; i < n; i++) {
        if (capacity == 0)
            break;

        if (items[i].item_weight <= capacity) {
            // Take the full item
            printf("%d\t%.6f\t%.6f\t%.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, 1.0);
            total_profit += items[i].item_profit;
            capacity -= items[i].item_weight;
        } else {
            // Take a fraction of the item
            float fraction = capacity / items[i].item_weight;
            printf("%d\t%.6f\t%.6f\t%.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, fraction);
            total_profit += items[i].item_profit * fraction;
            capacity = 0;
        }
    }

    return total_profit;
}

int main() {
    int n;
    float capacity;

    // Input: number of items
    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct ITEM items[n];

    // Input: profit and weight of each item
    for (int i = 0; i < n; i++) {
        items[i].item_id = i + 1;
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        // Calculate profit/weight ratio
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    // Input: capacity of knapsack
    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);

    // Sort items based on profit/weight ratio in non-increasing order using Bubble Sort
    bubbleSort(items, n);

    // Display table header
    printf("\nItem No\tProfit\t\tWeight\t\tAmount to be taken\n");

    // Apply fractional knapsack algorithm and calculate maximum profit
    float max_profit = fractionalKnapsack(items, n, capacity);

    // Output: Maximum profit
    printf("Maximum profit: %.6f\n", max_profit);

    return 0;
}