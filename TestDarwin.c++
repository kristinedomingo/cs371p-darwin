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

// ----------------------------
// Creature (constructor) tests
// ----------------------------

/**
 * Tests the Creature constructor (no parameters)
 * @param CreatureConstructor a fixture
 * @param creature_constructor_1 test name
 */
TEST(CreatureConstructor, creature_constructor_1)
{
    Creature c;
    ASSERT_EQ(c.get_display(), '.');
}

/**
 * Tests the Creature constructor (one parameter)
 * @param CreatureConstructor a fixture
 * @param creature_constructor_2 test name
 */
TEST(CreatureConstructor, creature_constructor_2)
{
    Creature c('b');
    ASSERT_EQ(c.get_display(), 'b');
}

/**
 * Tests the Creature constructor (two parameters)
 * @param CreatureConstructor a fixture
 * @param creature_constructor_3 test name
 */
TEST(CreatureConstructor, creature_constructor_3)
{
    Species s;
    Creature c('k', s);
    ASSERT_EQ(c.get_display(), 'k');
}

/**
 * Tests the Creature constructor (three parameters)
 * @param CreatureConstructor a fixture
 * @param creature_constructor_4 test name
 */
TEST(CreatureConstructor, creature_constructor_4)
{
    Species s;
    Creature c('d', s, SOUTH);
    ASSERT_EQ(c.get_display(), 'd');
}

// ---------------------
// Darwin_Iterator tests
// ---------------------

/**
 * Tests the Darwin_Iterator
 * @param DarwinIterator a fixture
 * @param iterators_1 test name
 */
TEST(DarwinIterator, iterators_1)
{
    Darwin d(10, 10, 0);
    Creature trap('t');

    Creature* const c = d.at(0, 0);
    *c = trap;

    Darwin::Darwin_Iterator di = d.begin();

    ASSERT_EQ(*di, c);
}

/**
 * Tests the Darwin_Iterator
 * @param DarwinIterator a fixture
 * @param iterators_2 test name
 */
TEST(DarwinIterator, iterators_2)
{
    Darwin d(1, 1, 0);

    Darwin::Darwin_Iterator di_b = d.begin();
    Darwin::Darwin_Iterator di_e = d.end();

    ++di_b;

    ASSERT_EQ(di_b, di_e);
}

/**
 * Tests the Darwin_Iterator
 * @param DarwinIterator a fixture
 * @param iterators_3 test name
 */
TEST(DarwinIterator, iterators_3)
{
    Darwin d(4, 4, 0);

    Darwin::Darwin_Iterator di_b = d.begin();
    Darwin::Darwin_Iterator di_e = d.end();

    for(int i = 0; i < 16; ++i)
    {
      ++di_b;
    }

    ASSERT_EQ(di_b, di_e);
}

/**
 * Tests the Darwin_Iterator
 * @param DarwinIterator a fixture
 * @param iterators_4 test name
 */
TEST(DarwinIterator, iterators_4)
{
    Darwin d(5, 5, 0);

    Darwin::Darwin_Iterator di_b = d.begin();
    Darwin::Darwin_Iterator di_e = d.end();

    while(di_b != di_e)
    {
        ASSERT_EQ((*di_b)->get_display(), '.');
        ++di_b;
    }
}

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
    Darwin d(8, 8, 0);
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
    Darwin d(1, 1, 0);
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
    Darwin d(8, 8, 0);

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
    Darwin d(8, 8, 0);

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

/**
 * Tests the get_grid() function
 * @param GetGrid a fixture
 * @param get_grid_5 test name
 */
TEST(GetGrid, get_grid_5)
{
    Darwin d(11, 11, 0);
    string grid = "Turn = 0.\n"
                  "  01234567890\n"
                  "0 ...........\n"
                  "1 ...........\n"
                  "2 ...........\n"
                  "3 ...........\n"
                  "4 ...........\n"
                  "5 ...........\n"
                  "6 ...........\n"
                  "7 ...........\n"
                  "8 ...........\n"
                  "9 ...........\n"
                  "0 ...........\n";

    ASSERT_EQ(d.get_grid(), grid);
}

/**
 * Tests the get_grid() function
 * @param GetGrid a fixture
 * @param get_grid_6 test name
 */
TEST(GetGrid, get_grid_6)
{
    Darwin d(11, 11, 0);

    Creature trap('t');
    Creature* const c = d.at(10, 10);
    *c = trap;

    string grid = "Turn = 0.\n"
                  "  01234567890\n"
                  "0 ...........\n"
                  "1 ...........\n"
                  "2 ...........\n"
                  "3 ...........\n"
                  "4 ...........\n"
                  "5 ...........\n"
                  "6 ...........\n"
                  "7 ...........\n"
                  "8 ...........\n"
                  "9 ...........\n"
                  "0 ..........t\n";

    ASSERT_EQ(d.get_grid(), grid);
}