#include <BloomFilter.hpp>
#include <MurmurHash3.h>

BloomFilter::BloomFilter(size_t size, uint8_t numHashes) :
    _numHashes(numHashes), _bits(size) {}

std::array<uint64_t, 2> BloomFilter::hash(const char *data, size_t len) const {
    std::array<uint64_t, 2> hashValue;
    MurmurHash3_x64_128(data, len, 0, hashValue.data());
    return hashValue;
}

void BloomFilter::add(const char *data, size_t len) {
    auto hashValues = hash(data, len);

    for (uint8_t i = 0; i < _numHashes; i++) {
        _bits[nthHash(i, hashValues[0], hashValues[1])] = true;
    }
}

bool BloomFilter::possiblyContains(const char *data, size_t len) const {
    auto hashValues = hash(data, len);

    for (uint8_t i = 0; i < _numHashes; i++) {
        if (!_bits[nthHash(i, hashValues[0], hashValues[1])]) {
            return false;
        }
    }

    return true;
}
