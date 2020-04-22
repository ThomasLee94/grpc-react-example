// RandomGenerator methods for uniform random ints, doubles, and strings

#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>

class RandomGenerator {
  public:
    RandomGenerator();
    // Generate a random number in the specified range [minValue, maxValue]
    int RandomInt(int minValue=std::numeric_limits<int>::min(),
                  int maxValue=std::numeric_limits<int>::max());
    double RandomDouble(double minValue=std::numeric_limits<double>::min(),
                        double maxValue=std::numeric_limits<double>::max());
    // Generate a random string of the specified length
    std::string RandomString(size_t length);
  private:
    // Engine for random generation (for example, Mersenne-Twister)
    std::default_random_engine generator;
    // Uniform distribution to apply to the generator
    std::uniform_real_distribution<> distribution;
};

#endif  // RANDOM_H_
