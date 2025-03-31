#include <iostream>
#include <conio.h>
#include <ctime>
#include <locale>
using namespace std;

// Enumeration
enum IN {
    // 13 is ASCII for carriage return
    IN_BACK = 8, // BACKSPACE
    IN_RET = 13  // ENTER
};

// assigned comma and period in a thousand number
struct comma_facet : public numpunct<char> {
protected:
    string do_grouping() const { return "\003"; }
};

// Hàm l?y password t? ngu?i dùng
string takePasswdFromUser() {
    string passwd;
    cout << "Enter your password (max 4 characters): ";
    cin >> passwd;
    if (passwd.length() > 4) {
        cout << "Password too long! Truncating to 4 characters." << endl;
        passwd = passwd.substr(0, 4);
    }
    return passwd;
}

string brute_force(string password, long long &num_of_attempt, clock_t &start_t, clock_t &end_t) {
    int num_ascii = 256; // number of possible ascii characters
    start_t = clock();
    for (int char1 = 0; char1 < num_ascii; char1++) {
        for (int char2 = 0; char2 < num_ascii; char2++) {
            for (int char3 = 0; char3 < num_ascii; char3++) {
                for (int char4 = 0; char4 < num_ascii; char4++) {
                    // convert each digit to char and concatenate into string
                    string convert_attempt = string(1, static_cast<char>(char1))
                                          + static_cast<char>(char2)
                                          + static_cast<char>(char3)
                                          + static_cast<char>(char4);
                    num_of_attempt++;
                    if (convert_attempt == password) {
                        end_t = clock();
                        return convert_attempt;
                    }
                }
            }
        }
    }
    throw "not found";
}

int main() {
    string input;
    long long num_of_attempt = 0;
    clock_t start_t, end_t;
    cout << "Input your password: ";
    // read password from user
    input = takePasswdFromUser();

    // Trying to crack password with Brute force
    cout << "Wait a minute - CRACKING your password..." << endl;
    try {
        cout << "Your password is: " << brute_force(input, num_of_attempt, start_t, end_t) << endl;
        cout.imbue(locale(cout.getloc(), new comma_facet()));
        cout << "Number of attempts: " << num_of_attempt << endl;
        cout << "Elapsed Time: " << (double)(end_t - start_t) / 1000 << " seconds" << endl;
    } catch (const char* msg) {
        cout << msg << endl;
    }
    return 0;
}
#include <iostream>
#include <cstring> // Thêm thu vi?n cho strlen
using namespace std;

void search2(char *text, char *pat) {
    int n = strlen(text);
    int m = strlen(pat);
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && pat[j] == text[i + j])
            j++;
        if (j == m) cout << "Pattern found at : " << i << endl;
    }
}

int main() {
    char a[500], b[500];
    cout << "enter the string" << endl;
    gets(a);
    cout << "enter the sub-string you wish to search for" << endl;
    gets(b);
    search2(a, b);
    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

long long combDP(int n, int k) {
    if (k > n || k < 0) return 0;
    if (k == 0 || k == n) return 1;

    vector<long long> c(k + 1, 0);
    c[0] = 1; // C(i, 0) = 1

    for (int i = 1; i <= n; i++) {
        for (int j = min(i, k); j > 0; j--) {
            c[j] = c[j] + c[j-1];
        }
    }

    return c[k];
}

int main() {
    int n, k;
    cout << "Enter n and k (n >= k >= 0): ";
    cin >> n >> k;

    if (n < 0 || k < 0 || k > n) {
        cout << "Invalid input! n must be >= 0 and k must be <= n." << endl;
        return 1;
    }

    long long result = combDP(n, k);
    cout << "C(" << n << "," << k << ") = " << result << endl;

    return 0;
}
