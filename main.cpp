#include <iostream>
#include <unistd.h>
#include <vector>
#include <array>

const size_t ITERATIONS = 10000;
const size_t LENGTH = 1000;
const char * const CHARS = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

char sample(size_t length, size_t offset) {
    return CHARS[(random() % length) + offset];
}

void pass_gen(std::vector<char> &password) {
    assert(LENGTH >= 4);
    for (auto i = 0; i < LENGTH; ++i) {
        password[i] = sample(94, 0);
    }
    password[LENGTH] = 0;
    std::vector<size_t> random_indices;
    auto j = LENGTH - 4;
    for (int i = 0; i < 4; i++, j++) {
        auto random_index = random() % (j + 1);
        auto pos = std::find(random_indices.begin(), random_indices.end(), random_index);
        auto value = pos == random_indices.end() ? random_index : j;
        random_indices.insert(pos, value);
    }
    password[random_indices[0]] = sample(10, 0);// NUMBERS
    password[random_indices[1]] = sample(26, 10);// LOWERS
    password[random_indices[2]] = sample(26, 36);// UPPERS
    password[random_indices[3]] = sample(32, 62);// SPECIALS
}

uint32_t mix(uint32_t a, uint32_t b, uint32_t c) {
    a = a - b;
    a = a - c;
    a = a ^ (c >> 13);
    b = b - c;
    b = b - a;
    b = b ^ (a << 8);
    c = c - a;
    c = c - b;
    c = c ^ (b >> 13);
    a = a - b;
    a = a - c;
    a = a ^ (c >> 12);
    b = b - c;
    b = b - a;
    b = b ^ (a << 16);
    c = c - a;
    c = c - b;
    c = c ^ (b >> 5);
    a = a - b;
    a = a - c;
    a = a ^ (c >> 3);
    b = b - c;
    b = b - a;
    b = b ^ (a << 10);
    c = c - a;
    c = c - b;
    c = c ^ (b >> 15);
    return c;
}

int main() {
    auto seed = mix(clock(), time(nullptr), getpid());
//    printf("Seed: %ud\n", seed);
    srandom(seed);
    std::vector<char> password(LENGTH + 1);
    for (size_t i = 0; i < ITERATIONS; i++) {
        pass_gen(password);
        std::cout << password.data() << "\n";
    }
}
