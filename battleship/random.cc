// RandomGenerator methods for uniform random ints, doubles, and strings

#include "random.h"

RandomGenerator::RandomGenerator() {
    // Seed the generator from the system random device
    std::random_device randomDevice;
    generator.seed(randomDevice());
}

int RandomGenerator::RandomInt(int minValue, int maxValue) {
    // Generate a [0, 1] double and scale to range, then cast to int type
    double randomValue = distribution(generator);
    double range = (maxValue - minValue + 1);
    // Note: +1 is to give maxValue chance of getting selected within int range
    return static_cast<int>((randomValue * range) + minValue);
}

double RandomGenerator::RandomDouble(double minValue, double maxValue) {
    // Generate a [0, 1] double and scale to range, then cast to double type
    double randomValue = distribution(generator);
    double range = (maxValue - minValue);
    return static_cast<double>((randomValue * range) + minValue);
}

std::string RandomGenerator::RandomString(size_t length) {
    static const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int maxIndex = sizeof(charset) - 2;  // Skip last hidden character \0
    // Allocate a string of the given length
    std::string str(length, 0);
    for (auto& ch : str) {
    // The above `auto` type requires C++11: compile with `g++ -std=c++11`
    // The below `std::string::iterator` type is an equivalent loop in C++98
    // for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
        // Choose a random character from charset
        const size_t randomIndex = RandomInt(0, maxIndex);
        ch = charset[randomIndex];
    }
    return str;
}

void TestRandomInt(int count) {
    printf("\nTesting RandomInt(int minValue, int maxValue):\n");
    RandomGenerator randomGenerator;
    // Generate random integers between 10 and 20
    for (int i = 0; i < count; ++i) {
        int randomInt = randomGenerator.RandomInt(10, 20);
        printf("Generated random integer: %i\n", randomInt);
    }
}

void TestRandomDouble(int count) {
    printf("\nTesting RandomDouble(double minValue, double maxValue):\n");
    RandomGenerator randomGenerator;
    // Generate random doubles between 10 and 20
    for (int i = 0; i < count; ++i) {
        double randomDouble = randomGenerator.RandomDouble(10, 20);
        printf("Generated random double: %f\n", randomDouble);
    }
}

void TestRandomString(int count) {
    printf("\nTesting RandomString(size_t length):\n");
    RandomGenerator randomGenerator;
    // Generate random strings of length 10
    for (int i = 0; i < count; ++i) {
        std::string randomString = randomGenerator.RandomString(10);
        printf("Generated random string: %s\n", randomString.c_str());
        // Alternative way to print string using std::cout from <iostream>
        // std::cout << "Generated string: " << randomString << std::endl;
    }
}

// int main(int argc, const char * argv[]) {
// 	TestRandomInt(10);
// 	TestRandomDouble(10);
// 	TestRandomString(10);
// }
