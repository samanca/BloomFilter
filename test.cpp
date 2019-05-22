#include <BloomFilter.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
using namespace std::chrono;

#define BLOOM_FILTER_SIZE   (size_t)4 << 20
#define BLOOM_FILTER_HASH   13
#define RANDOM_RECORDS      1E7
#define WORD_SIZE           64

std::string randomWord(size_t wordSize) {
    std::string str;
    for (size_t i = 0; i < wordSize; i++) {
        str += ('a' + rand() % 26);
    }
    return str;
}

int main() {
    BloomFilter filter(BLOOM_FILTER_SIZE, BLOOM_FILTER_HASH);
    std::vector<std::string> randomWords;
    high_resolution_clock::time_point t1, t2;

    t1 = high_resolution_clock::now();
    for (size_t i = 0; i < RANDOM_RECORDS; i++) {
        std::string word = randomWord(WORD_SIZE);
        filter.add(word.c_str(), WORD_SIZE);
        randomWords.push_back(word);
    }
    t2 = high_resolution_clock::now();
    std::cout << "Add latency:\t";
    auto d1 = duration_cast<milliseconds>(t2 - t1).count();
    std::cout << d1 << " ms (" << (d1 * 1E3 / RANDOM_RECORDS) << " us)";
    std::cout << std::endl;

    t1 = high_resolution_clock::now();
    for (size_t i = 0; i < RANDOM_RECORDS; i++) {
        if (!filter.possiblyContains(randomWords[i].c_str(), WORD_SIZE)) {
            std::cerr << "False Negative: " << i << "\n";
            break;
        }
    }
    t2 = high_resolution_clock::now();
    std::cout << "Lookup latency:\t";
    auto d2 = duration_cast<milliseconds>(t2 - t1).count();
    std::cout << d2 << " ms (" << (d2 * 1E3 / RANDOM_RECORDS) << " us)";
    std::cout << std::endl;

    randomWords.clear();
    return 0;
}
