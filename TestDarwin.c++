/** @file TestDarwin.c++
 *  @brief This file contains unit tests to test the functions and methods
 *         contained in Darwin.c++.
 */

// --------
// includes
// --------

#include <string>         // string
#include "gtest/gtest.h"  // google test
#include "Darwin.h"       // Darwin interfaces

using namespace std;


// --------------------------
// Darwin (constructor) tests
// --------------------------

/**
 * Tests the Darwin constructor (iterators)
 * @param DarwinConstructor a fixture
 * @param iterators_1 test name
 */
TEST(DarwinConstructor, iterators_1)
{
    Darwin<10, 10> d;
    Species* begin = d.begin();
    int count = 0;

    while(begin != d.end())
    {
        ++count;
        ++begin;
    }

    ASSERT_EQ(count, 100);
}

/**
 * Tests the Darwin constructor (iterators)
 * @param DarwinConstructor a fixture
 * @param iterators_2 test name
 */
TEST(DarwinConstructor, iterators_2)
{
    Darwin<1, 1> d;
    Species* begin = d.begin();
    int count = 0;

    while(begin != d.end())
    {
        ++count;
        ++begin;
    }

    ASSERT_EQ(count, 1);
}