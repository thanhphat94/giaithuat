#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_E 100
#define MAX_V 5

typedef struct {
    int u, v, cost;
    int active; // 1: xét, 0: loại bỏ
} Edge;

Edge edges[MAX_E];
int E = 0;
int best_cost = INT_MAX;

int parent[MAX_V];
int rank[MAX_V];

// Tìm đại diện
int find(int u) {
    if (parent[u] != u)
        parent[u] = find(parent[u]);
    return parent[u];
}

// Hợp nhất 2 tập
int union_set(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    if (pu == pv) return 0;
    if (rank[pu] < rank[pv]) parent[pu] = pv;
    else if (rank[pu] > rank[pv]) parent[pv] = pu;
    else {
        parent[pv] = pu;
        rank[pu]++;
    }
    return 1;
}

// Đếm bậc của mỗi đỉnh trong tập cạnh chọn
int degrees[MAX_V];

int is_valid_tour(Edge selected[], int count) {
    if (count != MAX_V) return 0;
    memset(degrees, 0, sizeof(degrees));
    for (int i = 0; i < MAX_V; i++) parent[i] = i, rank[i] = 0;
    for (int i = 0; i < count; i++) {
        degrees[selected[i].u]++;
        degrees[selected[i].v]++;
        if (!union_set(selected[i].u, selected[i].v))
            return 0; // tạo chu trình sớm
    }
    for (int i = 0; i < MAX_V; i++) {
        if (degrees[i] != 2) return 0;
    }
    return 1;
}

void solve(int idx, Edge selected[], int count, int curr_cost) {
    if (curr_cost >= best_cost) return;

    if (count == MAX_V) {
        if (is_valid_tour(selected, count)) {
            if (curr_cost < best_cost) {
                best_cost = curr_cost;
                printf("\n> Tour tốt hơn tìm được: Chi phí = %d\n", best_cost);
                for (int i = 0; i < count; i++)
                    printf("   %d-%d (%d)\n", selected[i].u, selected[i].v, selected[i].cost);
            }
        }
        return;
    }

    if (idx >= E) return;

    // Nhánh chọn cạnh idx
    selected[count] = edges[idx];
    solve(idx + 1, selected, count + 1, curr_cost + edges[idx].cost);

    // Nhánh bỏ qua cạnh idx
    solve(idx + 1, selected, count, curr_cost);
}

int main() {
    // Danh sách cạnh theo ví dụ hình 3-5
    int input[][3] = {
        {0, 1, 2}, {0, 2, 4}, {0, 3, 6}, {0, 4, 8},
        {1, 2, 6}, {1, 3, 10}, {1, 4, 5},
        {2, 3, 3}, {2, 4, 7}, {3, 4, 4}
    };

    int input_E = sizeof(input) / sizeof(input[0]);
    for (int i = 0; i < input_E; i++) {
        edges[E].u = input[i][0];
        edges[E].v = input[i][1];
        edges[E].cost = input[i][2];
        edges[E].active = 1;
        E++;
    }

    Edge selected[MAX_V];
    solve(0, selected, 0, 0);

    printf("\nChi phí nhỏ nhất tìm được: %d\n", best_cost);
    return 0;
}

// Mô phỏng thuật toán nhánh cận cho bài toán cái ba lô như Hình 3.13 trong sách
#include <stdio.h>
#include <stdlib.h>

#define N 4           // Số lượng vật
#define CAPACITY 37   // Trọng lượng tối đa

// Cấu trúc vật phẩm
typedef struct {
    char name;
    int weight;
    int value;
    float ratio; // Giá trị / Trọng lượng
} Item;

// Cấu trúc nút trạng thái trong cây tìm kiếm
typedef struct {
    int level;        // Cấp hiện tại (đang xét vật thứ mấy)
    int profit;       // Giá trị hiện tại (TGT)
    int weight;       // Trọng lượng hiện tại (W)
    float bound;      // Cận trên CT
} Node;

Item items[N] = {
    {'b', 10, 25, 0},
    {'a', 15, 30, 0},
    {'d', 4, 6, 0},
    {'c', 2, 2, 0}
};

// So sánh để sắp xếp theo tỉ lệ giá trị / trọng lượng giảm dần
int cmp(const void *a, const void *b) {
    float r1 = ((Item *)a)->ratio;
    float r2 = ((Item *)b)->ratio;
    return (r2 > r1) - (r2 < r1);
}

// Tính bound (cận trên) tại một node
float bound(Node u) {
    if (u.weight >= CAPACITY) return 0;
    float result = u.profit;
    int j = u.level + 1;
    int totalWeight = u.weight;
    while (j < N && totalWeight + items[j].weight <= CAPACITY) {
        totalWeight += items[j].weight;
        result += items[j].value;
        j++;
    }
    if (j < N)
        result += (CAPACITY - totalWeight) * items[j].ratio;
    return result;
}

// Hàm mô phỏng nhánh cận
void knapsack() {
    Node Q[100];
    int front = 0, rear = 0;
    Node u, v;

    Node best = { .profit = 0 };

    u.level = -1; u.profit = 0; u.weight = 0;
    u.bound = bound(u);
    Q[rear++] = u;

    while (front < rear) {
        u = Q[front++];

        if (u.bound <= best.profit) continue; // Cắt tỉa

        v.level = u.level + 1;

        // Nhánh chọn vật phẩm
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;
        v.bound = bound(v);

        if (v.weight <= CAPACITY && v.profit > best.profit) {
            best = v;
        }
        if (v.bound > best.profit)
            Q[rear++] = v;

        // Nhánh không chọn vật phẩm
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v);
        if (v.bound > best.profit)
            Q[rear++] = v;
    }

    printf("\n> Giá trị lớn nhất tìm được: %d\n", best.profit);
}

int main() {
    for (int i = 0; i < N; i++) {
        items[i].ratio = (float)items[i].value / items[i].weight;
    }
    qsort(items, N, sizeof(Item), cmp);

    knapsack();
    return 0;
}




