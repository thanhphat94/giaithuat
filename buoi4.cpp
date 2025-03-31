#include <stdio.h>
#include <time.h>
#include <string.h>

enum IN {
    IN_BACK = 8, // BACKSPACE
    IN_RET = 13  // ENTER
};

// Function to get password from user (simplified, no length checking beyond buffer)
char* takePasswdFromUser(char* passwd, int maxLen) {
    printf("Enter your password (max 4 characters): ");
    fgets(passwd, maxLen, stdin);
    // Remove newline if present
    size_t len = strlen(passwd);
    if (len > 0 && passwd[len - 1] == '\n') {
        passwd[len - 1] = '\0';
    }
    if (strlen(passwd) > 4) {
        printf("Password too long! Truncating to 4 characters.\n");
        passwd[4] = '\0'; // Truncate
    }
    return passwd;
}

char* brute_force(const char* password, long long* num_of_attempt, clock_t* start_t, clock_t* end_t) {
    int num_ascii = 256;
    *start_t = clock();
    for (int char1 = 0; char1 < num_ascii; char1++) {
        for (int char2 = 0; char2 < num_ascii; char2++) {
            for (int char3 = 0; char3 < num_ascii; char3++) {
                for (int char4 = 0; char4 < num_ascii; char4++) {
                    char convert_attempt[5];
                    convert_attempt[0] = (char)char1;
                    convert_attempt[1] = (char)char2;
                    convert_attempt[2] = (char)char3;
                    convert_attempt[3] = (char)char4;
                    convert_attempt[4] = '\0';
                    (*num_of_attempt)++;
                    if (strcmp(convert_attempt, password) == 0) {
                        *end_t = clock();
                        return convert_attempt; // Return a static buffer (not ideal, but for simplicity)
                    }
                }
            }
        }
    }
    return NULL; // Not found
}

int main() {
    char input[5]; // Buffer for password + null terminator
    long long num_of_attempt = 0;
    clock_t start_t, end_t;

    takePasswdFromUser(input, sizeof(input));

    printf("Wait a minute - CRACKING your password...\n");
    char* result = brute_force(input, &num_of_attempt, &start_t, &end_t);
    if (result) {
        printf("Your password is: %s\n", result);
        printf("Number of attempts: %lld\n", num_of_attempt);
        printf("Elapsed Time: %.3f seconds\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    } else {
        printf("Password not found!\n");
    }

    return 0;
}#include <stdio.h>
#include <string.h>

void search2(char* text, char* pat) {
    int n = strlen(text);
    int m = strlen(pat);
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && pat[j] == text[i + j]) {
            j++;
        }
        if (j == m) {
            printf("Pattern found at: %d\n", i);
        }
    }
}

int main() {
    char a[500], b[500];
    printf("Enter the string:\n");
    fgets(a, sizeof(a), stdin);
    // Remove newline
    size_t len = strlen(a);
    if (len > 0 && a[len - 1] == '\n') {
        a[len - 1] = '\0';
    }

    printf("Enter the sub-string you wish to search for:\n");
    fgets(b, sizeof(b), stdin);
    len = strlen(b);
    if (len > 0 && b[len - 1] == '\n') {
        b[len - 1] = '\0';
    }

    search2(a, b);
    return 0;
}#include <stdio.h>

long long combDP(int n, int k) {
    if (k > n || k < 0) return 0;
    if (k == 0 || k == n) return 1;

    long long c[100][100]; // Static array, assume n, k < 100
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= min(i, k); j++) {
            if (j == 0 || j == i) {
                c[i][j] = 1;
            } else {
                c[i][j] = c[i-1][j-1] + c[i-1][j];
            }
        }
    }

    return c[n][k];
}

int main() {
    int n, k;
    printf("Enter n and k (n >= k >= 0): ");
    scanf("%d %d", &n, &k);

    if (n < 0 || k < 0 || k > n) {
        printf("Invalid input! n must be >= 0 and k must be <= n.\n");
        return 1;
    }

    long long result = combDP(n, k);
    printf("C(%d,%d) = %lld\n", n, k, result);

    return 0;
}#include <stdio.h>

long long fibo(int n) {
    if (n < 0) {
        printf("Invalid input! n must be >= 0.\n");
        return -1;
    }
    if (n == 0) return 0;
    if (n == 1) return 1;

    long long f[100]; // Static array, assume n < 100
    f[0] = 0;
    f[1] = 1;

    for (int i = 2; i <= n; i++) {
        f[i] = f[i-1] + f[i-2];
    }

    return f[n];
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    long long result = fibo(n);
    if (result != -1) {
        printf("Fibonacci(%d) = %lld\n", n, result);
    }

    return 0;
}#include <stdio.h>

typedef struct {
    long long revenue;
    int* cuts;
    int cuts_size;
} Result;

Result rodCutting(int n, long long* p) {
    long long r[100]; // Assume n < 100
    int s[100];       // Store cut lengths
    for (int i = 0; i <= n; i++) {
        r[i] = 0;
        s[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (r[i] < p[j] + r[i - j]) {
                r[i] = p[j] + r[i - j];
                s[i] = j;
            }
        }
    }

    // Collect cuts
    int cuts[100], cuts_size = 0;
    int remaining = n;
    while (remaining > 0) {
        cuts[cuts_size++] = s[remaining];
        remaining -= s[remaining];
    }

    Result result = {r[n], cuts, cuts_size};
    return result;
}

int main() {
    int n;
    printf("Enter the length of the steel rod (n): ");
    scanf("%d", &n);

    long long p[101]; // Prices, index 1 to n
    printf("Enter the price for each length (p[1] to p[%d]):\n", n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &p[i]);
    }

    Result result = rodCutting(n, p);

    printf("Maximum revenue: %lld USD\n", result.revenue);
    printf("Optimal cutting lengths: ");
    for (int i = 0; i < result.cuts_size; i++) {
        printf("%d ", result.cuts[i]);
    }
    printf("inches\n");

    return 0;
}
