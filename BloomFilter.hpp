#pragma once
/*
 * Based on the Bloom Filter implementation by Michael Schmatz
 * http://blog.michaelschmatz.com/2016/04/11/how-to-write-a-bloom-filter-cpp/
 */
#include <vector>
#include <array>
#include <cstdint>

class BloomFilter {
    public:
        BloomFilter(size_t size, uint8_t numHashes);

        void add(const char *data, size_t len);
        bool possiblyContains(const char *data, size_t len) const;

    private:
        uint8_t _numHashes;
        std::vector<bool> _bits;

        std::array<uint64_t, 2> hash(const char *data, size_t len) const;
        inline uint64_t nthHash(uint8_t n, uint64_t hashA, uint64_t hashB) const {
            return (hashA + n * hashB) % _bits.size();
        }
};
