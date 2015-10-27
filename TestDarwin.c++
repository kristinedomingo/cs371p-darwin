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
    Darwin d(10, 10);
    Creature* begin = d.begin();
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
    Darwin d(1, 1);
    Creature* begin = d.begin();
    int count = 0;

    while(begin != d.end())
    {
        ++count;
        ++begin;
    }

    ASSERT_EQ(count, 1);
}

// TODO: add stronger iterator tests


// ----------------
// get_grid() tests
// ----------------

/**
 * Tests the get_grid() function
 * @param GetGrid a fixture
 * @param get_grid_1 test name
 */
TEST(GetGrid, get_grid_1)
{
    Darwin d(8, 8);
    string grid = "Turn = 0.\n"
                  "  01234567\n"
                  "0 ........\n"
                  "1 ........\n"
                  "2 ........\n"
                  "3 ........\n"
                  "4 ........\n"
                  "5 ........\n"
                  "6 ........\n"
                  "7 ........\n";

    ASSERT_EQ(d.get_grid(), grid);
}

/**
 * Tests the get_grid() function
 * @param GetGrid a fixture
 * @param get_grid_2 test name
 */
TEST(GetGrid, get_grid_2)
{
    Darwin d(1, 1);
    string grid = "Turn = 0.\n"
                  "  0\n"
                  "0 .\n";

    ASSERT_EQ(d.get_grid(), grid);
}

/**
 * Tests the get_grid() function
 * @param GetGrid a fixture
 * @param get_grid_3 test name
 */
TEST(GetGrid, get_grid_3)
{
    Darwin d(8, 8);

    Creature trap('t');
    Creature rover('r');

    Creature* const c = d.at(1, 1);
    *c = trap;

    Creature* const c2 = d.at(5, 6);
    *c2 = rover;

    const string grid = "Turn = 0.\n"
                  "  01234567\n"
                  "0 ........\n"
                  "1 .t......\n"
                  "2 ........\n"
                  "3 ........\n"
                  "4 ........\n"
                  "5 ......r.\n"
                  "6 ........\n"
                  "7 ........\n";

    ASSERT_EQ(d.get_grid(), grid);
}

/**
 * Tests the get_grid() function
 * @param GetGrid a fixture
 * @param get_grid_4 test name
 */
TEST(GetGrid, get_grid_4)
{
    Darwin d(8, 8);

    Creature trap('t');
    Creature* const c = d.at(0, 0);
    *c = trap;

    const string grid = "Turn = 0.\n"
                  "  01234567\n"
                  "0 t.......\n"
                  "1 ........\n"
                  "2 ........\n"
                  "3 ........\n"
                  "4 ........\n"
                  "5 ........\n"
                  "6 ........\n"
                  "7 ........\n";

    ASSERT_EQ(d.get_grid(), grid);
}