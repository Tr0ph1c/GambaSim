#include <random>
#include <chrono>
#include "Generators.h"

auto seed = static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count());
std::default_random_engine rng(seed);

std::uniform_real_distribution<float> rando(0.0f, 1.0f);

float gen::random () {
    return rando(rng);
}

int gen::random (int start, int end) {
    std::uniform_int_distribution<int> irando(start, end);

    return irando(rng);
}