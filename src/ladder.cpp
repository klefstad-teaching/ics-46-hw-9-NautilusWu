#include "ladder.h"
// #include "timer_mine.h"

#include <vector>
#include <queue>
#include <set>
#include <string>
#include <cmath>
#include <algorithm>
#include <unordered_set>
// #include <iomanip>
#include <cmath>
// #include <unordered_map>

void error(string word1, string word2, string msg) {
    cerr << "Error between " << word1 << " and " << word2 << ": " << msg << endl;
    exit(1);
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int m = str1.length();
    int n = str2.length();
    if (abs(m - n) > d) return false;

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; ++i)
        dp[i][0] = i;
    for (int j = 0; j <= n; ++j)
        dp[0][j] = j;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }

    // cout << "dp: " << dp[m][n] << endl;
    return dp[m][n] <= d;
}

// Check if two strings are adjacent
bool is_adjacent(const string& word1, const string& word2) {
    int dd = word1.length() - word2.length();
    if (dd > 1 || dd < -1) return false;
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_edit_distance_one(const string& word) {
    vector<string> result;

    // Insert a character
    for (int i = 0; i <= word.size(); ++i) {
        for (char c = 'a'; c <= 'z'; ++c) {
            string new_word = word;
            new_word.insert(new_word.begin() + i, c);
            result.push_back(new_word);
        }
    }

    // Delete a character
    for (int i = 0; i < word.size(); ++i) {
        string new_word = word;
        new_word.erase(new_word.begin() + i);
        result.push_back(new_word);
    }

    // Replace a character
    for (int i = 0; i < word.size(); ++i) {
        char original_char = word[i];
        for (char c = 'a'; c <= 'z'; ++c) {
            if (c != original_char) {
                string new_word = word;
                new_word[i] = c;
                result.push_back(new_word);
            }
        }
    }

    result.push_back(word);
    return result;
}

vector<string> filter_by_ordered_vector(const vector<string>& edit_distance_one, const set<string>& ordered_set) {
    // set<string> ordered_set(ordered_set.begin(), ordered_set.end());
    vector<string> filtered_result;

    for (const string& word : edit_distance_one) {
        if (ordered_set.find(word) != ordered_set.end()) {
            filtered_result.push_back(word);
        }
    }
    // sort(filtered_result.begin(), filtered_result.end(), [&ordered_set](const string& a, const string& b) {
    //     auto pos_a = ordered_set.find(a);
    //     auto pos_b = ordered_set.find(b);
    //     return distance(ordered_set.begin(), pos_a) < distance(ordered_set.begin(), pos_b);
    // });
    sort(filtered_result.begin(), filtered_result.end());
    return filtered_result;
}


// Generate word ladder
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {};
    queue<vector<string>> ladder_queue;
    unordered_set<string> visited;
    set<string> word_list_copy(word_list.begin(), word_list.end());

    ladder_queue.push({begin_word});
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        vector<string> edit_distance_one = generate_edit_distance_one(last_word);
        vector<string> filtered_result = filter_by_ordered_vector(edit_distance_one, word_list_copy);
        for (auto it = filtered_result.begin(); it != filtered_result.end(); ) {
        // for (auto it = word_list_copy.begin(); it != word_list_copy.end(); ) {
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
                // it = word_list_copy.erase(it);
                it = filtered_result.erase(it);
            } else {
                ++it;
            }
        }
    }
    return {};

}

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
    cout << "verify_word: awake aware ware were wee see seep sleep" << endl;
    set<string> word_list;

    load_words(word_list, "../src/words.txt");

    // Timer t;
    // double eTime = 0.0;
    // eTime = 0.0;
    // t.start();
    // vector<string> test2 = generate_word_ladder("awake", "sleep", word_list);
    // t.elapsedUserTime(eTime);
    // std::cout << "Time = " << std::fixed << std::setprecision(6) << eTime << std::endl ;
    // print_word_ladder(test2);

    my_assert(generate_word_ladder("cat", "cat", word_list).size() == 0);
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}
