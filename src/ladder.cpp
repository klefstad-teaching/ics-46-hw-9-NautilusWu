#include "ladder.h"

#include <vector>
#include <queue>
#include <set>
#include <string>
#include <cmath>
#include <algorithm>
#include <unordered_set>

void error(string word1, string word2, string msg) {
    cerr << "Error between " << word1 << " and " << word2 << ": " << msg << endl;
    exit(1);
}


bool edit_distance_within(const string& str1, const string& str2, int d) {
    int m = str1.size();
    int n = str2.size();
    if (abs(m - n) > d) return false;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int j = 0; j <= n; ++j) dp[0][j] = j;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }
    return dp[m][n] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {};
    queue<vector<string>> ladder_queue;
    unordered_set<string> visited;
    unordered_set<string> word_list_copy(word_list.begin(), word_list.end());
    ladder_queue.push({begin_word});
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (auto it = word_list_copy.begin(); it != word_list_copy.end(); ) {
            const string& word = *it;
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
                it = word_list_copy.erase(it);
            } else {
                ++it;
            }
        }
    }
    return {};
}


// bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
//     int m = str1.length();
//     int n = str2.length();
//     if (abs(m - n) > d) return false;

//     vector<vector<int>> dp(m + 1, vector<int>(n + 1));

//     for (int i = 0; i <= m; ++i)
//         dp[i][0] = i;
//     for (int j = 0; j <= n; ++j)
//         dp[0][j] = j;

//     for (int i = 1; i <= m; ++i) {
//         for (int j = 1; j <= n; ++j) {
//             if (str1[i - 1] == str2[j - 1]) {
//                 dp[i][j] = dp[i - 1][j - 1];
//             } else {
//                 dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
//             }
//         }
//     }

//     return dp[m][n] <= d;
// }




// // Check if two strings are adjacent
// bool is_adjacent(const string& word1, const string& word2) {
//     return edit_distance_within(word1, word2, 1);
// }

// // Generate word ladder
// vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
//     if (begin_word == end_word) return {};



//     queue<vector<string>> ladder_queue;
//     unordered_set<string> visited;
//     unordered_set<string> word_list_copy(word_list.begin(), word_list.end());
    

//     ladder_queue.push({begin_word});
//     visited.insert(begin_word);
//     while (!ladder_queue.empty()) {
//         vector<string> ladder = ladder_queue.front();
//         ladder_queue.pop();
//         string last_word = ladder.back();
//         for (auto it = word_list_copy.begin(); it != word_list_copy.end(); ) {
//             const string& word = *it;
//             if (is_adjacent(last_word, word)) {
//                 if (visited.find(word) == visited.end()) {
//                     visited.insert(word);
//                     vector<string> new_ladder = ladder;
//                     new_ladder.push_back(word);
//                     if (word == end_word) {
//                         return new_ladder;
//                     }
//                     ladder_queue.push(new_ladder);
//                 }
//                 it = word_list_copy.erase(it);
//             } else {
//                 ++it;
//             }
//         }
//     }
//     return {};

// }

// Load words from file
void load_words(set<string>& word_list, const string& file_name) {
    word_list.clear();


    ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "Cannot open file: " << file_name << endl;
        exit(1);
    }

    string word;
    while (file >> word) {
        word_list.insert(word);
    }

    file.close();
}

// Print word ladder
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }

    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i)
        cout << ladder[i] << " ";
    cout << endl;
}

// Verify word ladder
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    cout << "verify_word" << endl;
    set<string> word_list;
    load_words(word_list, "../src/words.txt");

    vector<string> test = generate_word_ladder("awake", "sleep", word_list);
    print_word_ladder(test);

    // my_assert(generate_word_ladder("cat", "cat", word_list).size() == 0);
    // my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    // my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    // my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    // my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    // my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    // my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}
