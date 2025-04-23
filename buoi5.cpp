#include <stdio.h>
#include <limits.h>
#include <string.h>

#define N 4

int final_path[N + 1];
int visited[N];
int final_res = INT_MAX;

// Sao chep duong di tam thoi vao ket qua cuoi
void copyToFinal(int curr_path[]) {
    for (int i = 0; i < N; i++)
        final_path[i] = curr_path[i];
    final_path[N] = curr_path[0];
}

// Tim canh ngan nhat tu dinh i
int firstMin(int adj[N][N], int i) {
    int min = INT_MAX;
    for (int k = 0; k < N; k++) {
        if (adj[i][k] < min && i != k)
            min = adj[i][k];
    }
    return min;
}

// Tim canh ngan thu hai tu dinh i
int secondMin(int adj[N][N], int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < N; j++) {
        if (i == j) continue;
        if (adj[i][j] <= first) {
            second = first;
            first = adj[i][j];
        } else if (adj[i][j] <= second && adj[i][j] != first) {
            second = adj[i][j];
        }
    }
    return second;
}

// Ham nhanh can de quy
void TSPRec(int adj[N][N], int curr_bound, int curr_weight, int level, int curr_path[]) {
    if (level == N) {
        if (adj[curr_path[level - 1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + adj[curr_path[level - 1]][curr_path[0]];
            if (curr_res < final_res) {
                copyToFinal(curr_path);
                final_res = curr_res;
            }
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (adj[curr_path[level - 1]][i] != 0 && visited[i] == 0) {
            int temp = curr_bound;
            curr_weight += adj[curr_path[level - 1]][i];

            if (level == 1)
                curr_bound -= (firstMin(adj, curr_path[level - 1]) + firstMin(adj, i)) / 2;
            else
                curr_bound -= (secondMin(adj, curr_path[level - 1]) + firstMin(adj, i)) / 2;

            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = 1;
                TSPRec(adj, curr_bound, curr_weight, level + 1, curr_path);
            }

            curr_weight -= adj[curr_path[level - 1]][i];
            curr_bound = temp;

            memset(visited, 0, sizeof(visited));
            for (int j = 0; j <= level - 1; j++)
                visited[curr_path[j]] = 1;
        }
    }
}

// Ham khoi tao va goi de quy chinh
void TSP(int adj[N][N]) {
    int curr_path[N + 1];
    int curr_bound = 0;

    memset(curr_path, -1, sizeof(curr_path));
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < N; i++)
        curr_bound += firstMin(adj, i) + secondMin(adj, i);

    curr_bound = (curr_bound & 1) ? (curr_bound / 2 + 1) : (curr_bound / 2);

    visited[0] = 1;
    curr_path[0] = 0;

    TSPRec(adj, curr_bound, 0, 1, curr_path);
}

// Ham main
int main() {
    int adj[N][N] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    TSP(adj);

    printf("Chi phi nho nhat: %d\n", final_res);
    printf("Duong di: ");
    for (int i = 0; i <= N; i++)
        printf("%d ", final_path[i]);
    printf("\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    float weight;
    int value;
} Item;

typedef struct {
    int level;
    int profit;
    int bound;
    float weight;
} Node;

int n = 5; // so luong vat pham
int W = 10; // trong luong toi da cua ba lo

Item arr[] = {
    {2, 40}, {3.14, 50}, {1.98, 100}, {5, 95}, {3, 30}
};

// Ham so sanh cho qsort: sap xep theo ty le value/weight giam dan
int cmp(const void *a, const void *b) {
    float r1 = ((Item*)a)->value / ((Item*)a)->weight;
    float r2 = ((Item*)b)->value / ((Item*)b)->weight;
    if (r1 < r2) return 1;
    if (r1 > r2) return -1;
    return 0;
}

// Tinh bound toi da loi nhuan co the dat tu node u
int bound(Node u, Item arr[]) {
    if (u.weight >= W)
        return 0;

    int profit_bound = u.profit;
    int j = u.level + 1;
    float totweight = u.weight;

    while (j < n && totweight + arr[j].weight <= W) {
        totweight += arr[j].weight;
        profit_bound += arr[j].value;
        j++;
    }

    if (j < n)
        profit_bound += (W - totweight) * arr[j].value / arr[j].weight;

    return profit_bound;
}

// Hang doi don gian cho Node
Node queue[MAX];
int front = 0, rear = 0;

void enqueue(Node x) {
    if (rear < MAX)
        queue[rear++] = x;
}

Node dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front == rear;
}

// Giai bai toan Knapsack bang nhanh can
int knapsack(Item arr[]) {
    qsort(arr, n, sizeof(Item), cmp);

    Node u, v;
    u.level = -1;
    u.profit = 0;
    u.weight = 0;

    int maxProfit = 0;

    enqueue(u);

    while (!isEmpty()) {
        u = dequeue();

        if (u.level == n - 1)
            continue;

        v.level = u.level + 1;

        // Nhanh lay vat pham
        v.weight = u.weight + arr[v.level].weight;
        v.profit = u.profit + arr[v.level].value;

        if (v.weight <= W && v.profit > maxProfit)
            maxProfit = v.profit;

        v.bound = bound(v, arr);
        if (v.bound > maxProfit)
            enqueue(v);

        // Nhanh khong lay vat pham
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, arr);
        if (v.bound > maxProfit)
            enqueue(v);
    }

    return maxProfit;
}

// Ham main
int main() {
    int result = knapsack(arr);
    printf("Gia tri toi uu: %d\n", result);
    return 0;
}

