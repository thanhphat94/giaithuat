#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
typedef struct {
    int key;
    double otherfield;
} Recordtype;
void generateArray(Recordtype a[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        a[i].key = rand() % 10000;
        a[i].otherfield = 0.87 * a[i].key;
    }
}
void merge(Recordtype A[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    Recordtype L[n1 + 1], R[n2 + 1];

    for (int i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[q + 1 + j];

    L[n1].key = R[n2].key = INT_MAX; 

    int i = 0, j = 0;
    for (int k = p; k <= r; k++) {
        if (L[i].key <= R[j].key) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}
void mergeSort(Recordtype A[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}
void printArray(Recordtype a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Key: %d, Otherfield: %.2f\n", a[i].key, a[i].otherfield);
    }
}

int main() {
    int n;
    printf("Nhap so phan tu cua mang: ");
    scanf("%d", &n);

    Recordtype a[n], hold[n];
    generateArray(a, n);

    printf("Mang ban dau:\n");
    printArray(a, n);

    struct timeval begin, end;
    long seconds, microseconds;
    double elapsed;

    memcpy(hold, a, n * sizeof(Recordtype));
    gettimeofday(&begin, 0);
    mergeSort(hold, 0, n - 1);
    gettimeofday(&end, 0);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds * 1e-6;
    printf("Merge Sort - Wall-Time measured: %.6f seconds.\n", elapsed);

    printf("Mang sau khi sap xep (theo key):\n");
    printArray(hold, n);

    return 0;
}
bai toan ATM
#include <stdio.h>

int main() {
    int denominations[] = {5000, 2000, 1000, 500, 200, 100}; // Các m?nh giá ti?n
    int numDenominations = 6; // S? lu?ng m?nh giá
    int M; // S? ti?n c?n rút

    // Nh?p s? ti?n c?n rút
    printf("Nhap so tien can rut (M): ");
    scanf("%d", &M);

    if (M <= 0) {
        printf("So tien khong hop le!\n");
        return 1;
    }

    int remaining = M; // S? ti?n còn l?i
    int count[6] = {0}; // M?ng d?m s? t? ti?n cho m?i m?nh giá

    // Áp d?ng thu?t toán háu an
    for (int i = 0; i < numDenominations; i++) {
        if (denominations[i] <= remaining) {
            count[i] = remaining / denominations[i]; // S? t? t?i da có th? l?y
            remaining = remaining % denominations[i]; // C?p nh?t s? ti?n còn l?i
        }
    }

    // Hi?n th? k?t qu?
    printf("So luong to tien can su dung de rut %d:\n", M);
    for (int i = 0; i < numDenominations; i++) {
        if (count[i] > 0) {
            printf("%d to %d\n", count[i], denominations[i]);
        }
    }

    // Ki?m tra n?u không rút du?c d? ti?n
    if (remaining > 0) {
        printf("Khong the rut du %d voi cac menh gia da cho!\n", remaining);
    }

    return 0;
}
bai toan cai balo
#include <stdio.h>
#include <stdlib.h>

// C?u trúc luu thông tin d? v?t
typedef struct {
    char name;        // Tên d? v?t
    int weight;       // Tr?ng lu?ng
    int value;        // Giá tr?
    double valuePerWeight; // T? l? giá tr?/tr?ng lu?ng
} Item;

// Hàm so sánh d? s?p x?p theo t? l? giá tr?/tr?ng lu?ng gi?m d?n
int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    if (itemB->valuePerWeight > itemA->valuePerWeight) return 1;
    if (itemB->valuePerWeight < itemA->valuePerWeight) return -1;
    return 0;
}

int main() {
    int W, N;
    printf("Nhap trong luong toi da cua ba lo (W): ");
    scanf("%d", &W);
    printf("Nhap so loai do vat (N): ");
    scanf("%d", &N);

    Item items[N];
    printf("Nhap thong tin do vat (ten, trong luong, gia tri):\n");
    for (int i = 0; i < N; i++) {
        scanf(" %c %d %d", &items[i].name, &items[i].weight, &items[i].value);
        items[i].valuePerWeight = (double)items[i].value / items[i].weight;
    }

    // S?p x?p theo t? l? giá tr?/tr?ng lu?ng gi?m d?n
    qsort(items, N, sizeof(Item), compare);

    int remainingWeight = W;
    int count[N]; // S? lu?ng m?i lo?i d? v?t
    int totalValue = 0;

    for (int i = 0; i < N; i++) {
        count[i] = 0;
        while (items[i].weight <= remainingWeight) {
            count[i]++;
            remainingWeight -= items[i].weight;
            totalValue += items[i].value;
        }
    }

    // Hi?n th? k?t qu?
    printf("Cach chon do vat:\n");
    for (int i = 0; i < N; i++) {
        if (count[i] > 0) {
            printf("%d do vat %c\n", count[i], items[i].name);
        }
    }
    printf("Tong gia tri: %d\n", totalValue);

    return 0;
}

th1
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name;
    int weight;
    int value;
    double valuePerWeight;
    int quantity; // S? lu?ng t?i da c?a d? v?t
} Item;

int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    if (itemB->valuePerWeight > itemA->valuePerWeight) return 1;
    if (itemB->valuePerWeight < itemA->valuePerWeight) return -1;
    return 0;
}

int main() {
    int W, N;
    printf("Nhap trong luong toi da cua ba lo (W): ");
    scanf("%d", &W);
    printf("Nhap so loai do vat (N): ");
    scanf("%d", &N);

    Item items[N];
    printf("Nhap thong tin do vat (ten, trong luong, gia tri, so luong):\n");
    for (int i = 0; i < N; i++) {
        scanf(" %c %d %d %d", &items[i].name, &items[i].weight, &items[i].value, &items[i].quantity);
        items[i].valuePerWeight = (double)items[i].value / items[i].weight;
    }

    qsort(items, N, sizeof(Item), compare);

    int remainingWeight = W;
    int count[N];
    int totalValue = 0;

    for (int i = 0; i < N; i++) {
        count[i] = 0;
        while (items[i].weight <= remainingWeight && count[i] < items[i].quantity) {
            count[i]++;
            remainingWeight -= items[i].weight;
            totalValue += items[i].value;
        }
    }

    printf("Cach chon do vat:\n");
    for (int i = 0; i < N; i++) {
        if (count[i] > 0) {
            printf("%d do vat %c\n", count[i], items[i].name);
        }
    }
    printf("Tong gia tri: %d\n", totalValue);

    return 0;
}

th2
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name;
    int weight;
    int value;
    double valuePerWeight;
} Item;

int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    if (itemB->valuePerWeight > itemA->valuePerWeight) return 1;
    if (itemB->valuePerWeight < itemA->valuePerWeight) return -1;
    return 0;
}

int main() {
    int W, N;
    printf("Nhap trong luong toi da cua ba lo (W): ");
    scanf("%d", &W);
    printf("Nhap so loai do vat (N): ");
    scanf("%d", &N);

    Item items[N];
    printf("Nhap thong tin do vat (ten, trong luong, gia tri):\n");
    for (int i = 0; i < N; i++) {
        scanf(" %c %d %d", &items[i].name, &items[i].weight, &items[i].value);
        items[i].valuePerWeight = (double)items[i].value / items[i].weight;
    }

    qsort(items, N, sizeof(Item), compare);

    int remainingWeight = W;
    int count[N];
    int totalValue = 0;

    for (int i = 0; i < N; i++) {
        count[i] = 0;
        if (items[i].weight <= remainingWeight) {
            count[i] = 1; // Ch? l?y 1 l?n
            remainingWeight -= items[i].weight;
            totalValue += items[i].value;
        }
    }

    printf("Cach chon do vat:\n");
    for (int i = 0; i < N; i++) {
        if (count[i] > 0) {
            printf("%d do vat %c\n", count[i], items[i].name);
        }
    }
    printf("Tong gia tri: %d\n", totalValue);

    return 0;
}
