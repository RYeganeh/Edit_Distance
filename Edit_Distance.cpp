#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Compute Levenshtein distance AND keep the DP table
int levenshtein(const std::string& s1,
                const std::string& s2,
                std::vector<std::vector<int>>& table)
{
    int len1 = s1.size();
    int len2 = s2.size();

    table.assign(len1 + 1, std::vector<int>(len2 + 1, 0));

    for (int i = 0; i <= len1; ++i)
        table[i][0] = i;

    for (int j = 0; j <= len2; ++j)
        table[0][j] = j;

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;

            table[i][j] = std::min({
                table[i - 1][j] + 1,       // deletion
                table[i][j - 1] + 1,       // insertion
                table[i - 1][j - 1] + cost // substitution
            });
        }
    }

    return table[len1][len2];
}

// Print the DP matrix in a readable format
void printMatrix(const std::vector<std::vector<int>>& table,
                 const std::string& s1,
                 const std::string& s2)
{
    std::cout << "\nDP Matrix:\n    ";

    for (char c : s2)
        std::cout << c << "  ";
    std::cout << "\n";

    for (int i = 0; i < table.size(); ++i) {
        if (i == 0)
            std::cout << "  ";
        else
            std::cout << s1[i - 1] << " ";

        for (int j = 0; j < table[i].size(); ++j) {
            std::cout << table[i][j] << "  ";
        }
        std::cout << "\n";
    }
}

int main()
{
    std::vector<std::string> words = {
        "cat", "bat", "rat", "hat",
        "book", "cook", "look",
        "code", "cope", "core", "cure",
        "apple", "apply", "ample",
        "plane", "plant", "plans",
        "data", "date", "mate", "made",

        "test",
        "tost", "tent", "text", "best",
        "tests", "teest", "tsets",
        "tes", "tet", "est",
        "bost", "tint",
        "teast", "twest",
        "tst",
        "teests",
        "ts",

        "abcd", "wxyz", "zzzzz", "aaa", "bbbbb"
    };

    std::string userWord;
    std::cout << "Enter a 4-letter word with typos: ";
    std::cin >> userWord;

    bool anyMatches = false;
    std::cout << "\nMatches (edit distance <= 2):\n";

    for (const auto& w : words) {
        std::vector<std::vector<int>> dp;
        int d = levenshtein(userWord, w, dp);

        if (d <= 2) {
            std::cout << "\nWord: " << w << " (distance = " << d << ")\n";
            printMatrix(dp, userWord, w);
            anyMatches = true;
        }
    }

    if (!anyMatches) {
        std::cout << "No close matches found.\n";
    }

    return 0;
}
