#include "logicForOther.h"


double timeFile(char letter, vector<string>& words) { 
    auto start = std::chrono::high_resolution_clock::now();
    countFile(letter, words);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}
double countFile(char letter, vector<string>& words) {  
    int count = 0;
    for (string word : words) {
        if (letter == word[0]) {
            count++;
        }
    }
    return count;
}
