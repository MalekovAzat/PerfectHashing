#include <iostream>
#include "../lib/googletest/googletest/include/gtest/gtest.h"
#include "../tools/UniformDistributionGenerator.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    // init random generator
    UniformDistributionGenerator::getInstance();

    return RUN_ALL_TESTS();
}