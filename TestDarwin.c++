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

    Darwin_Iterator di = d.begin();

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

    Darwin_Iterator di_b = d.begin();
    Darwin_Iterator di_e = d.end();

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

    Darwin_Iterator di_b = d.begin();
    Darwin_Iterator di_e = d.end();

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

    Darwin_Iterator di_b = d.begin();
    Darwin_Iterator di_e = d.end();

    while(di_b != di_e)
    {
        stringstream ss;
        ss << *(*di_b);

        ASSERT_EQ(ss.str(), ".");

        ss.clear();
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

    Darwin_Iterator di_b = d.begin();
    Darwin_Iterator di_e = d.end();

    for(int i = 0; i < (30 * 30); ++i)
    {
      ++di_b;
    }

    ASSERT_EQ(di_b, di_e);
}

/**
 * Tests the Darwin_Iterator
 * @param DarwinIterator a fixture
 * @param iterators_6 test name
 */
TEST(DarwinIterator, iterators_6)
{
    Darwin d(30, 30);

    // Add Creature 'k' to the 0, 0 spot on the grid
    Species s('k');
    Creature c(s);
    d.add_creature(c, 0, 0);

    string k_grid = d.get_grid();

    // Replace the 0, 0 spot using an iterator
    Species s2('j');
    Creature c2(s2);

    Darwin_Iterator b = d.begin();
    Creature* begin = *b;
    *begin = c2;

    string k_replaced_by_j_grid = d.get_grid();

    ASSERT_TRUE(begin->is_enemy(c));
    ASSERT_NE(k_grid, k_replaced_by_j_grid);
}

// ---------------------------------
// Darwin_Iterator::operator * tests
// ---------------------------------

/**
 * Tests the Darwin_Iterator dereference operator
 * @param DarwinIteratorDereference a fixture
 * @param darwin_iterator_dereference_1 test name
 */
TEST(DarwinIteratorDereference, darwin_iterator_dereference_1)
{
    Darwin d(10, 10);
    Darwin_Iterator b = d.begin();
    Creature* c = *b;

    ASSERT_TRUE(c->is_empty());
}

/**
 * Tests the Darwin_Iterator dereference operator
 * @param DarwinIteratorDereference a fixture
 * @param darwin_iterator_dereference_2 test name
 */
TEST(DarwinIteratorDereference, darwin_iterator_dereference_2)
{
    Darwin d(10, 10);
    Species s('k');
    Creature c(s);
    d.add_creature(c, 0, 0);

    Darwin_Iterator b = d.begin();
    Creature* cp = *b;

    ASSERT_FALSE(cp->is_empty());
}

/**
 * Tests the Darwin_Iterator dereference operator
 * @param DarwinIteratorDereference a fixture
 * @param darwin_iterator_dereference_3 test name
 */
TEST(DarwinIteratorDereference, darwin_iterator_dereference_3)
{
    Darwin d(10, 10);
    Darwin_Iterator wall(d, 10, 0);
    Creature* cp = *wall;

    ASSERT_EQ(cp, nullptr);
}

/**
 * Tests the Darwin_Iterator dereference operator
 * @param DarwinIteratorDereference a fixture
 * @param darwin_iterator_dereference_4 test name
 */
TEST(DarwinIteratorDereference, darwin_iterator_dereference_4)
{
    Darwin d(10, 10);
    Darwin_Iterator out_of_bounds(d, 20, 20);
    Creature* cp = *out_of_bounds;

    ASSERT_EQ(cp, nullptr);
}

// ------------------------------
// Darwin_Iterator::ahead() tests
// ------------------------------

/**
 * Tests the Darwin_Iterator dereference operator
 * @param DarwinIteratorAhead a fixture
 * @param darwin_iterator_ahead_1 test name
 */
TEST(DarwinIteratorAhead, darwin_iterator_ahead_1)
{
    Darwin d(10, 10);
    Species s('k');
    Creature c(s, SOUTH);
    d.add_creature(c, 0, 0);

    Darwin_Iterator b = d.begin();
    Darwin_Iterator space_ahead = b.ahead(b, SOUTH);
    Creature* creature_ahead = *space_ahead;

    ASSERT_TRUE(creature_ahead->is_empty());
}

/**
 * Tests the Darwin_Iterator dereference operator
 * @param DarwinIteratorAhead a fixture
 * @param darwin_iterator_ahead_2 test name
 */
TEST(DarwinIteratorAhead, darwin_iterator_ahead_2)
{
    Darwin d(10, 10);
    Species s('k');
    Creature c(s, SOUTH);
    d.add_creature(c, 0, 0);

    Species s2('j');
    Creature c2(s2);
    d.add_creature(c2, 1, 0);

    Darwin_Iterator b = d.begin();
    Darwin_Iterator space_ahead = b.ahead(b, SOUTH);
    Creature* creature_ahead = *space_ahead;

    stringstream ss;
    ss << c2;
    ASSERT_FALSE(creature_ahead->is_empty());
    ASSERT_EQ(ss.str(), "j");
}

/**
 * Tests the Darwin_Iterator dereference operator
 * @param DarwinIteratorAhead a fixture
 * @param darwin_iterator_ahead_3 test name
 */
TEST(DarwinIteratorAhead, darwin_iterator_ahead_3)
{
    Darwin d(10, 10);
    Species s('k');
    Creature c(s, NORTH);
    d.add_creature(c, 0, 0);

    Darwin_Iterator b = d.begin();
    Darwin_Iterator space_ahead = b.ahead(b, NORTH);
    Creature* creature_ahead = *space_ahead;

    ASSERT_EQ(creature_ahead, nullptr);
}

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

// ------------------------------
// Species operator ==, !=, tests
// ------------------------------

/**
 * Tests the Species operator ==
 * @param SpeciesEquals a fixture
 * @param species_equals_1 test name
 */
TEST(SpeciesEquals, species_equals_1)
{
    Species s;
    Species s2;
    ASSERT_EQ(s, s2);
}

/**
 * Tests the Species operator ==
 * @param SpeciesEquals a fixture
 * @param species_equals_2 test name
 */
TEST(SpeciesEquals, species_equals_2)
{
    Species s;
    Species s2('k');
    ASSERT_NE(s, s2);
}

/**
 * Tests the Species operator ==
 * @param SpeciesEquals a fixture
 * @param species_equals_3 test name
 */
TEST(SpeciesEquals, species_equals_3)
{
    Species s('k');
    Species s2('k');
    ASSERT_EQ(s, s2);
}

// --------------
// render() tests
// --------------

/**
 * Tests the Species render() function
 * @param SpeciesRender a fixture
 * @param species_render_1 test name
 */
TEST(SpeciesRender, species_render_1)
{
    Species s;
    ASSERT_EQ(s.render(), '.');
}

/**
 * Tests the Species render() function
 * @param SpeciesRender a fixture
 * @param species_render_2 test name
 */
TEST(SpeciesRender, species_render_2)
{
    Species s('k');
    ASSERT_EQ(s.render(), 'k');
}

// -----------------------
// add_instruction() tests
// -----------------------

/**
 * Tests the Species add_instruction() function
 * @param AddInstruction a fixture
 * @param add_instruction_1 test name
 */
TEST(AddInstruction, add_instruction_1)
{
    Species s;
    ASSERT_TRUE(s.instructions.empty());
}

/**
 * Tests the Species add_instruction() function
 * @param AddInstruction a fixture
 * @param add_instruction_2 test name
 */
TEST(AddInstruction, add_instruction_2)
{
    Species s;
    s.add_instruction(HOP);

    ASSERT_FALSE(s.instructions.empty());
    ASSERT_EQ(s.instructions[0].first, HOP);
    ASSERT_EQ(s.instructions[0].second, -1);
}

/**
 * Tests the Species add_instruction() function
 * @param AddInstruction a fixture
 * @param add_instruction_3 test name
 */
TEST(AddInstruction, add_instruction_3)
{
    Species s;
    s.add_instruction(IF_EMPTY, 3);

    ASSERT_FALSE(s.instructions.empty());
    ASSERT_EQ(s.instructions[0].first, IF_EMPTY);
    ASSERT_EQ(s.instructions[0].second, 3);
}

/**
 * Tests the Species add_instruction() function
 * @param AddInstruction a fixture
 * @param add_instruction_4 test name
 */
TEST(AddInstruction, add_instruction_4)
{
    Species s;
    s.add_instruction(IF_EMPTY, 3);
    s.add_instruction(LEFT);

    ASSERT_FALSE(s.instructions.empty());
    ASSERT_EQ(s.instructions[0].first, IF_EMPTY);
    ASSERT_EQ(s.instructions[0].second, 3);
    ASSERT_EQ(s.instructions[1].first, LEFT);
    ASSERT_EQ(s.instructions[1].second, -1);
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