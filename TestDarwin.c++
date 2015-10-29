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

// ---------------------------
// Species (constructor) tests
// ---------------------------

/**
 * Tests the Species constructor (no parameters)
 * @param SpeciesConstructor a fixture
 * @param species_constructor_1 test name
 */
TEST(SpeciesConstructor, species_constructor_1)
{
    Species s;
    ASSERT_EQ(s.render(), '.');
}


/**
 * Tests the Species constructor (one parameter)
 * @param SpeciesConstructor a fixture
 * @param species_constructor_2 test name
 */
TEST(SpeciesConstructor, species_constructor_2)
{
    Species s('k');
    ASSERT_EQ(s.render(), 'k');
}

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

    ASSERT_TRUE(c.is_empty());

    stringstream ss;
    ss << c;
    ASSERT_EQ(ss.str(), ".");
}

/**
 * Tests the Creature constructor (one parameter)
 * @param CreatureConstructor a fixture
 * @param creature_constructor_2 test name
 */
TEST(CreatureConstructor, creature_constructor_2)
{
    Species s;
    Creature c(s);

    ASSERT_TRUE(c.is_empty());

    stringstream ss;
    ss << c;
    ASSERT_EQ(ss.str(), ".");
}

/**
 * Tests the Creature constructor (two parameters)
 * @param CreatureConstructor a fixture
 * @param creature_constructor_4 test name
 */
TEST(CreatureConstructor, creature_constructor_4)
{
    Species s;
    Creature c(s, SOUTH);

    ASSERT_TRUE(c.is_empty());

    stringstream ss;
    ss << c;
    ASSERT_EQ(ss.str(), ".");
}

/**
 * Tests the Creature constructor (non-default Species)
 * @param CreatureConstructor a fixture
 * @param creature_constructor_5 test name
 */
TEST(CreatureConstructor, creature_constructor_5)
{
    Species s('r');
    Creature c(s, SOUTH);

    ASSERT_FALSE(c.is_empty());

    stringstream ss;
    ss << c;
    ASSERT_EQ(ss.str(), "r");
}

// ----------------
// is_empty() tests
// ----------------

/**
 * Tests the is_empty() function
 * @param IsEmpty a fixture
 * @param is_empty_1 test name
 */
TEST(IsEmpty, is_empty_1)
{
    Creature c;
    ASSERT_TRUE(c.is_empty());
}

/**
 * Tests the is_empty() function
 * @param IsEmpty a fixture
 * @param is_empty_2 test name
 */
TEST(IsEmpty, is_empty_2)
{
    Species s;
    Creature c(s);

    ASSERT_TRUE(c.is_empty());
}

/**
 * Tests the is_empty() function
 * @param IsEmpty a fixture
 * @param is_empty_3 test name
 */
TEST(IsEmpty, is_empty_3)
{
    Species s('k');
    Creature c(s);

    ASSERT_FALSE(c.is_empty());
}

// ----------------
// is_enemy() tests
// ----------------

/**
 * Tests the is_enemy() function
 * @param IsEnemy a fixture
 * @param is_enemy_1 test name
 */
TEST(IsEnemy, is_enemy_1)
{
    Creature c;
    Creature c2;

    ASSERT_FALSE(c.is_enemy(c2));
}

/**
 * Tests the is_enemy() function
 * @param IsEnemy a fixture
 * @param is_enemy_2 test name
 */
TEST(IsEnemy, is_enemy_2)
{
    Species s;
    Creature c(s);
    Creature c2;

    ASSERT_FALSE(c.is_enemy(c2));
}

/**
 * Tests the is_enemy() function
 * @param IsEnemy a fixture
 * @param is_enemy_3 test name
 */
TEST(IsEnemy, is_enemy_3)
{
    Species s('k');
    Creature c(s);

    Species s2('l');
    Creature c2(s2);

    ASSERT_TRUE(c.is_enemy(c2));
}

/**
 * Tests the is_enemy() function
 * @param IsEnemy a fixture
 * @param is_enemy_4 test name
 */
TEST(IsEnemy, is_enemy_4)
{
    Species s('k');
    Creature c(s);

    Species s2;
    Creature c2(s2);

    ASSERT_FALSE(c.is_enemy(c2));
}

/**
 * Tests the is_enemy() function
 * @param IsEnemy a fixture
 * @param is_enemy_5 test name
 */
TEST(IsEnemy, is_enemy_5)
{
    Creature c;

    Species s('k');
    Creature c2(s);

    ASSERT_FALSE(c.is_enemy(c2));
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
    Darwin d(10, 10);
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
    Darwin d(1, 1);

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
    Darwin d(4, 4);

    Darwin::Darwin_Iterator di_b = d.begin();
    Darwin::Darwin_Iterator di_e = d.end();

    for(int i = 0; i < (4 * 4); ++i)
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
    Darwin d(5, 5);

    Darwin::Darwin_Iterator di_b = d.begin();
    Darwin::Darwin_Iterator di_e = d.end();

    while(di_b != di_e)
    {
        ASSERT_EQ((*di_b)->s.render(), '.');
        ++di_b;
    }
}

/**
 * Tests the Darwin_Iterator
 * @param DarwinIterator a fixture
 * @param iterators_5 test name
 */
TEST(DarwinIterator, iterators_5)
{
    Darwin d(30, 30);

    Darwin::Darwin_Iterator di_b = d.begin();
    Darwin::Darwin_Iterator di_e = d.end();

    for(int i = 0; i < (30 * 30); ++i)
    {
      ++di_b;
    }

    ASSERT_EQ(di_b, di_e);
}

// ----------
// at() tests
// ----------

/**
 * Tests the at() function
 * @param At a fixture
 * @param at_1 test name
 */
TEST(At, at_1)
{
    Darwin d(8, 8);

    Species s('k');
    Creature c(s);
    d.add_creature(c, 1, 1);

    ASSERT_FALSE(d.at(1, 1)->is_enemy(c));
}

/**
 * Tests the at() function
 * @param At a fixture
 * @param at_2 test name
 */
TEST(At, at_2)
{
    Darwin d(8, 8);
    ASSERT_EQ(d.at(9, 9), nullptr);
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

    d.add_creature(trap, 1, 1);
    d.add_creature(rover, 5, 6);

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
    d.add_creature(trap, 0, 0);

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
    Darwin d(11, 11);
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
    Darwin d(11, 11);

    Creature trap('t');
    d.add_creature(trap, 10, 10);

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

// --------------------
// add_creature() tests
// --------------------

/**
 * Tests the add_creature() function
 * @param AddCreature a fixture
 * @param add_creature_1 test name
 */
TEST(AddCreature, add_creature_1)
{
    Darwin d(8, 8);
    Creature kristine('k');
    Creature downing('d');

    d.add_creature(kristine, 0, 0);
    d.add_creature(kristine, 1, 1);
    d.add_creature(kristine, 2, 2);

    d.add_creature(downing, 3, 3);
    d.add_creature(downing, 4, 4);
    d.add_creature(downing, 5, 5);

    ASSERT_FALSE(d.at(0, 0)->is_enemy(kristine));
    ASSERT_FALSE(d.at(1, 1)->is_enemy(kristine));
    ASSERT_FALSE(d.at(2, 2)->is_enemy(kristine));

    ASSERT_FALSE(d.at(3, 3)->is_enemy(downing));
    ASSERT_FALSE(d.at(4, 4)->is_enemy(downing));
    ASSERT_FALSE(d.at(5, 5)->is_enemy(downing));
}

/**
 * Tests the add_creature() function
 * @param AddCreature a fixture
 * @param add_creature_2 test name
 */
TEST(AddCreature, add_creature_2)
{
    Darwin d(8, 8);
    string empty_board = d.get_grid();

    Creature kristine('k');
    Creature downing('d');

    // Placing a Creature in an invalid spot should leave the grid unchanged
    d.add_creature(kristine, 9, 9);
    string new_board = d.get_grid();
    ASSERT_EQ(empty_board, new_board);

    d.add_creature(downing, 5, 5);
    new_board = d.get_grid();
    ASSERT_NE(empty_board, new_board);
    ASSERT_FALSE(d.at(5, 5)->is_enemy(downing));
}