#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

//BMH Algorithm Implementation
int boyerMooreSearch(const string& pattern, const string& text) {
    int m = pattern.length();
    int n = text.length();

    if (m == 0 || m > n) return -1;

    //bad character table
    vector<int> badCharSkip(256, m);
    for (int i = 0; i < m - 1; i++) {
        badCharSkip[static_cast<unsigned char>(pattern[i])] = m - 1 - i;
    }

    int i = 0; 
    while (i <= n - m) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }

        if (j < 0) {
            return i; 
        } else {
            char badChar = text[i + m - 1];
            i += badCharSkip[static_cast<unsigned char>(badChar)];
        }
    }

    return -1;
}

int main() {
    string filename = "pi-billion.txt";
    string piData;
    string targetSequence;

    cout << "================================================\n";
    cout << "TRANSCENDENTAL SEQUENCE FINDER \n";
    cout << "================================================\n\n";

    cout << "[*] Loading dataset (" << filename << ")...\n";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "[!] Error: Could not open " << filename << ".\n";
        cerr << "    Ensure it exists in the project directory.\n";
        return 1;
    }
    
    // Fast file reading into memory
    file.seekg(0, ios::end);
    piData.reserve(file.tellg());
    file.seekg(0, ios::beg);
    piData.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    
    cout << "[+] Successfully loaded " << piData.length() << " digits.\n\n";

    while (true) {
        cout << "Enter a sequence to search (or 'q' to quit): ";
        cin >> targetSequence;

        if (targetSequence == "q" || targetSequence == "Q") break;

        cout << "Searching using Boyer-Moore...\n";

        auto start = high_resolution_clock::now();
        int index = boyerMooreSearch(targetSequence, piData);
        auto end = high_resolution_clock::now();
        duration<double, milli> duration_ms = end - start;

        
        cout << "------------------------------------------------\n";
        if (index != -1) {
            cout << "[SUCCESS] Sequence '" << targetSequence << "' found!\n";
            cout << "          Index: " << index << "\n";
        } else {
            cout << "[RESULT]  Sequence '" << targetSequence << "' not found.\n";
        }
        cout << "[TIME]    Execution time: " << duration_ms.count() << " ms\n";
        cout << "------------------------------------------------\n\n";
    }

    return 0;
}