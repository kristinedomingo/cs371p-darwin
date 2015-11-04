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

        ss.str("");
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
    stringstream ss;

    // Add Creature 'k' to the 0, 0 spot on the grid
    Species s('k');
    Creature c(s);
    d.add_creature(c, 0, 0);

    ss << d;
    string k_grid = ss.str();
    ss.str("");

    // Replace the 0, 0 spot using an iterator
    Species s2('j');
    Creature c2(s2);

    Darwin_Iterator b = d.begin();
    Creature* begin = *b;
    *begin = c2;

    ss << d;
    string k_replaced_by_j_grid = ss.str();
    ss.str("");

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
 * Tests the Darwin_Iterator::ahead()
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
 * Tests the Darwin_Iterator::ahead()
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
 * Tests the Darwin_Iterator::ahead()
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

/**
 * Tests the Darwin_Iterator::ahead()
 * @param DarwinIteratorAhead a fixture
 * @param darwin_iterator_ahead_4 test name
 */
TEST(DarwinIteratorAhead, darwin_iterator_ahead_4)
{
    Darwin d(10, 10);
    Species s('k');
    Creature c(s, WEST);
    d.add_creature(c, 0, 0);

    Darwin_Iterator b = d.begin();
    Darwin_Iterator space_ahead = b.ahead(b, NORTH);
    Creature* creature_ahead = *space_ahead;

    ASSERT_EQ(creature_ahead, nullptr);
}

/**
 * Tests the Darwin_Iterator::ahead()
 * @param DarwinIteratorAhead a fixture
 * @param darwin_iterator_ahead_5 test name
 */
TEST(DarwinIteratorAhead, darwin_iterator_ahead_5)
{
    Darwin d(10, 10);
    Species s('k');
    Creature c(s, EAST);
    d.add_creature(c, 0, 9);

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
    stringstream ss;
    ss << s;
    ASSERT_EQ(ss.str(), ".");
}

/**
 * Tests the Species constructor (one parameter)
 * @param SpeciesConstructor a fixture
 * @param species_constructor_2 test name
 */
TEST(SpeciesConstructor, species_constructor_2)
{
    Species s('k');
    stringstream ss;
    ss << s;
    ASSERT_EQ(ss.str(), "k");
}

// --------------------------
// Species::operator << tests
// --------------------------

/**
 * Tests the Species operator << overload
 * @param SpeciesOperatorOverload a fixture
 * @param species_operator_1 test name
 */
TEST(SpeciesOperatorOverload, species_operator_1)
{
    Species s;
    stringstream ss;
    ss << s;

    ASSERT_EQ(ss.str(), ".");
}

/**
 * Tests the Species operator << overload
 * @param SpeciesOperatorOverload a fixture
 * @param species_operator_2 test name
 */
TEST(SpeciesOperatorOverload, species_operator_2)
{
    Species s('k');
    stringstream ss;
    ss << s;

    ASSERT_EQ(ss.str(), "k");
}

/**
 * Tests the Species operator << overload
 * @param SpeciesOperatorOverload a fixture
 * @param species_operator_3 test name
 */
TEST(SpeciesOperatorOverload, species_operator_3)
{
    Species s('.');
    stringstream ss;
    ss << s;

    ASSERT_EQ(ss.str(), ".");
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

/**
 * Tests the Species operator ==
 * @param SpeciesEquals a fixture
 * @param species_equals_4 test name
 */
TEST(SpeciesEquals, species_equals_4)
{
    Species s('k');
    Species s2;
    ASSERT_NE(s, s2);
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

/**
 * Tests the Species add_instruction() function
 * @param AddInstruction a fixture
 * @param add_instruction_5 test name
 */
TEST(AddInstruction, add_instruction_5)
{
    Species s;
    s.add_instruction(IF_EMPTY, 3);
    s.add_instruction(IF_WALL, 2);
    s.add_instruction(IF_ENEMY, 1);
    s.add_instruction(IF_RANDOM, 0);
    s.add_instruction(GO, 5);

    ASSERT_FALSE(s.instructions.empty());
    ASSERT_EQ(s.instructions[0].first, IF_EMPTY);
    ASSERT_EQ(s.instructions[0].second, 3);
    ASSERT_EQ(s.instructions[1].first, IF_WALL);
    ASSERT_EQ(s.instructions[1].second, 2);
    ASSERT_EQ(s.instructions[2].first, IF_ENEMY);
    ASSERT_EQ(s.instructions[2].second, 1);
    ASSERT_EQ(s.instructions[3].first, IF_RANDOM);
    ASSERT_EQ(s.instructions[3].second, 0);
    ASSERT_EQ(s.instructions[4].first, GO);
    ASSERT_EQ(s.instructions[4].second, 5);
}

/**
 * Tests the Species add_instruction() function
 * @param AddInstruction a fixture
 * @param add_instruction_6 test name
 */
TEST(AddInstruction, add_instruction_6)
{
    Species s;
    s.add_instruction(HOP);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    s.add_instruction(INFECT);

    ASSERT_FALSE(s.instructions.empty());
    ASSERT_EQ(s.instructions[0].first, HOP);
    ASSERT_EQ(s.instructions[0].second, -1);
    ASSERT_EQ(s.instructions[1].first, LEFT);
    ASSERT_EQ(s.instructions[1].second, -1);
    ASSERT_EQ(s.instructions[2].first, RIGHT);
    ASSERT_EQ(s.instructions[2].second, -1);
    ASSERT_EQ(s.instructions[3].first, INFECT);
    ASSERT_EQ(s.instructions[3].second, -1);
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

// ---------------------------
// Creature::operator << tests
// ---------------------------

/**
 * Tests the Creature operator << overload
 * @param CreatureOperatorOverload a fixture
 * @param creature_operator_1 test name
 */
TEST(CreatureOperatorOverload, creature_operator_1)
{
    Creature c;
    stringstream ss;
    ss << c;

    ASSERT_EQ(ss.str(), ".");
}

/**
 * Tests the Creature operator << overload
 * @param CreatureOperatorOverload a fixture
 * @param creature_operator_2 test name
 */
TEST(CreatureOperatorOverload, creature_operator_2)
{
    Species s;
    Creature c(s);
    stringstream ss;
    ss << c;

    ASSERT_EQ(ss.str(), ".");
}

/**
 * Tests the Creature operator << overload
 * @param CreatureOperatorOverload a fixture
 * @param creature_operator_3 test name
 */
TEST(CreatureOperatorOverload, creature_operator_3)
{
    Species s('k');
    Creature c(s);
    stringstream ss;
    ss << c;

    ASSERT_EQ(ss.str(), "k");
}

/**
 * Tests the Creature operator << overload
 * @param CreatureOperatorOverload a fixture
 * @param creature_operator_4 test name
 */
TEST(CreatureOperatorOverload, creature_operator_4)
{
    Species s('k');
    Creature c(s);

    Species s2('j');
    Creature c2(s2);
    c2.infect(c);

    stringstream ss;
    ss << c;

    ASSERT_EQ(ss.str(), "j");
}

// --------------------------
// Creature::is_enemy() tests
// --------------------------

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

// --------------------------
// Creature::is_empty() tests
// --------------------------

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

// ---------------------------
// Creature::turn_left() tests
// ---------------------------

/**
 * Tests the turn_left() function
 * @param TurnLeft a fixture
 * @param turn_left_1 test name
 */
TEST(TurnLeft, turn_left_1)
{
    Species s;
    Creature c(s);
    c.turn_left();

    ASSERT_EQ(c.dir, WEST);
}

/**
 * Tests the turn_left() function
 * @param TurnLeft a fixture
 * @param turn_left_2 test name
 */
TEST(TurnLeft, turn_left_2)
{
    Species s;
    Creature c(s, EAST);
    c.turn_left();

    ASSERT_EQ(c.dir, NORTH);
}

/**
 * Tests the turn_left() function
 * @param TurnLeft a fixture
 * @param turn_left_3 test name
 */
TEST(TurnLeft, turn_left_3)
{
    Species s;
    Creature c(s, SOUTH);
    c.turn_left();

    ASSERT_EQ(c.dir, EAST);
}

/**
 * Tests the turn_left() function
 * @param TurnLeft a fixture
 * @param turn_left_4 test name
 */
TEST(TurnLeft, turn_left_4)
{
    Species s;
    Creature c(s, WEST);
    c.turn_left();

    ASSERT_EQ(c.dir, SOUTH);
}

// ---------------------------
// Creature::turn_right() tests
// ---------------------------

/**
 * Tests the turn_right() function
 * @param TurnReft a fixture
 * @param turn_right_1 test name
 */
TEST(TurnLeft, turn_right_1)
{
    Species s;
    Creature c(s, NORTH);
    c.turn_right();

    ASSERT_EQ(c.dir, EAST);
}

/**
 * Tests the turn_right() function
 * @param TurnReft a fixture
 * @param turn_right_2 test name
 */
TEST(TurnLeft, turn_right_2)
{
    Species s;
    Creature c(s, WEST);
    c.turn_right();

    ASSERT_EQ(c.dir, NORTH);
}

/**
 * Tests the turn_right() function
 * @param TurnReft a fixture
 * @param turn_right_3 test name
 */
TEST(TurnLeft, turn_right_3)
{
    Species s;
    Creature c(s, SOUTH);
    c.turn_right();

    ASSERT_EQ(c.dir, WEST);
}

/**
 * Tests the turn_right() function
 * @param TurnReft a fixture
 * @param turn_right_4 test name
 */
TEST(TurnLeft, turn_right_4)
{
    Species s;
    Creature c(s, EAST);
    c.turn_right();

    ASSERT_EQ(c.dir, SOUTH);
}

// ------------------------
// Creature::infect() tests
// ------------------------

/**
 * Tests the infect() function
 * @param Infect a fixture
 * @param infect_1 test name
 */
TEST(Infect, infect_1)
{
    Species s('k');
    Creature c(s);

    Species s2('j');
    Creature c2(s2);

    c.infect(c2);

    ASSERT_FALSE(c.is_enemy(c2));
}

/**
 * Tests the infect() function
 * @param Infect a fixture
 * @param infect_2 test name
 */
TEST(Infect, infect_2)
{
    Species s('k');
    Creature c(s);
    Creature c2(s);

    ASSERT_FALSE(c.is_enemy(c2));

    c.infect(c2);

    ASSERT_FALSE(c.is_enemy(c2));
}

/**
 * Tests the infect() function
 * @param Infect a fixture
 * @param infect_3 test name
 */
TEST(Infect, infect_3)
{
    Species s('k');
    Creature c(s);

    Creature c2;

    ASSERT_FALSE(c.is_enemy(c2));
    ASSERT_TRUE(c2.is_empty());

    c.infect(c2);

    ASSERT_FALSE(c.is_enemy(c2));
    ASSERT_TRUE(c2.is_empty());
}

/**
 * Tests the infect() function
 * @param Infect a fixture
 * @param infect_4 test name
 */
TEST(Infect, infect_4)
{
    Species s('k');
    Creature c(s);

    Species s2('j');
    Creature c2(s2);

    Species s3('l');
    Creature c3(s3);

    c.infect(c2);
    c2.infect(c3);

    ASSERT_FALSE(c.is_enemy(c2));
    ASSERT_FALSE(c2.is_enemy(c3));
}

/**
 * Tests the infect() function
 * @param Infect a fixture
 * @param infect_5 test name
 */
TEST(Infect, infect_5)
{
    Species s('k');
    Creature c(s);

    Species s2('j');
    Creature c2(s2);

    Species s3('l');
    Creature c3(s3);

    c2.infect(c3);
    c.infect(c2);
    c2.infect(c3);

    ASSERT_FALSE(c.is_enemy(c2));
    ASSERT_FALSE(c2.is_enemy(c3));
}

// ------------------
// Darwin::at() tests
// ------------------

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
    ASSERT_EQ(d.at(7, 9), nullptr);
}

/**
 * Tests the at() function
 * @param At a fixture
 * @param at_3 test name
 */
TEST(At, at_3)
{
    Darwin d(8, 8);
    ASSERT_EQ(d.at(23, 34), nullptr);
}

/**
 * Tests the at() function
 * @param At a fixture
 * @param at_4 test name
 */
TEST(At, at_4)
{
    Darwin d(8, 8);
    ASSERT_EQ(d.at(-1, -1), nullptr);
}

/**
 * Tests the at() function
 * @param At a fixture
 * @param at_5 test name
 */
TEST(At, at_5)
{
    Darwin d(8, 8);
    ASSERT_EQ(d.at(5, -1), nullptr);
}

/**
 * Tests the at() function
 * @param At a fixture
 * @param at_6 test name
 */
TEST(At, at_6)
{
    Darwin d(8, 8);
    ASSERT_EQ(d.at(-1, 5), nullptr);
}

// -------------------------
// Darwin::operator << tests
// -------------------------

/**
 * Tests the Darwin operator << function
 * @param DarwinOperatorOverload a fixture
 * @param darwin_operator_1 test name
 */
TEST(DarwinOperatorOverload, darwin_operator_1)
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
                  "7 ........\n\n";

    stringstream ss;
    ss << d;

    ASSERT_EQ(ss.str(), grid);
}

/**
 * Tests the Darwin operator << function
 * @param DarwinOperatorOverload a fixture
 * @param darwin_operator_2 test name
 */
TEST(DarwinOperatorOverload, darwin_operator_2)
{
    Darwin d(1, 1);
    string grid = "Turn = 0.\n"
                  "  0\n"
                  "0 .\n\n";

    stringstream ss;
    ss << d;

    ASSERT_EQ(ss.str(), grid);
}

/**
 * Tests the Darwin operator << function
 * @param DarwinOperatorOverload a fixture
 * @param darwin_operator_3 test name
 */
TEST(DarwinOperatorOverload, darwin_operator_3)
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
                  "7 ........\n\n";

    stringstream ss;
    ss << d;
    ASSERT_EQ(ss.str(), grid);
}

/**
 * Tests the Darwin operator << function
 * @param DarwinOperatorOverload a fixture
 * @param darwin_operator_4 test name
 */
TEST(DarwinOperatorOverload, darwin_operator_4)
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
                  "7 ........\n\n";

    stringstream ss;
    ss << d;
    ASSERT_EQ(ss.str(), grid);
}

/**
 * Tests the Darwin operator << function
 * @param DarwinOperatorOverload a fixture
 * @param darwin_operator_5 test name
 */
TEST(DarwinOperatorOverload, darwin_operator_5)
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
                  "0 ...........\n\n";

    stringstream ss;
    ss << d;
    ASSERT_EQ(ss.str(), grid);
}

/**
 * Tests the Darwin operator << function
 * @param DarwinOperatorOverload a fixture
 * @param darwin_operator_6 test name
 */
TEST(DarwinOperatorOverload, darwin_operator_6)
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
                  "0 ..........t\n\n";

    stringstream ss;
    ss << d;
    ASSERT_EQ(ss.str(), grid);}

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
    stringstream ss;

    ss << d;
    string empty_board = ss.str();
    ss.str("");

    Creature kristine('k');
    Creature downing('d');

    // Placing a Creature in an invalid spot should leave the grid unchanged
    d.add_creature(kristine, 9, 9);

    ss << d;
    string new_board = ss.str();
    ss.str("");

    ASSERT_EQ(empty_board, new_board);

    d.add_creature(downing, 5, 5);

    ss << d;
    new_board = ss.str();
    ss.str("");

    ASSERT_NE(empty_board, new_board);
    ASSERT_FALSE(d.at(5, 5)->is_enemy(downing));
}

/**
 * Tests the add_creature() function
 * @param AddCreature a fixture
 * @param add_creature_3 test name
 */
TEST(AddCreature, add_creature_3)
{
    Darwin d(8, 8);

    Species s('k');
    Creature c(s);

    d.add_creature(c, 0, 0);

    ASSERT_FALSE(d.at(0, 0)->is_empty());
    ASSERT_TRUE(!d.at(0, 0)->is_enemy(c));
}

/**
 * Tests the add_creature() function
 * @param AddCreature a fixture
 * @param add_creature_4 test name
 */
TEST(AddCreature, add_creature_4)
{
    Darwin d(8, 8);

    Species s('k');
    Creature c(s);
    d.add_creature(c, 0, 0);

    Species s2('j');
    Creature c2(s2);
    d.add_creature(c2, 0, 0);

    ASSERT_FALSE(d.at(0, 0)->is_empty());
    ASSERT_TRUE(!d.at(0, 0)->is_enemy(c2));
}

/**
 * Tests the add_creature() function
 * @param AddCreature a fixture
 * @param add_creature_5 test name
 */
TEST(AddCreature, add_creature_5)
{
    Darwin d(8, 8);

    Species s('k');
    Creature c(s);
    d.add_creature(c, 0, 0);

    Creature c2;
    d.add_creature(c2, 0, 0);

    ASSERT_TRUE(d.at(0, 0)->is_empty());
}

// -----------------------
// Darwin::do_turn() tests
// -----------------------

/**
 * Tests the Darwin::do_turn() function
 * @param DoTurn a fixture
 * @param do_turn_1 test name
 */
TEST(DoTurn, do_turn_1)
{
    Darwin d(8, 8);
    stringstream ss;

    Species s('k');
    s.add_instruction(HOP);

    Creature c(s, WEST);
    d.add_creature(c, 1, 1);

    ss << d;
    const string grid2 = "Turn = 0.\n"
                         "  01234567\n"
                         "0 ........\n"
                         "1 .k......\n"
                         "2 ........\n"
                         "3 ........\n"
                         "4 ........\n"
                         "5 ........\n"
                         "6 ........\n"
                         "7 ........\n\n";
    ASSERT_EQ(ss.str(), grid2);
    ss.str("");

    d.do_turn();
    ss << d;
    const string grid3 = "Turn = 1.\n"
                         "  01234567\n"
                         "0 ........\n"
                         "1 k.......\n"
                         "2 ........\n"
                         "3 ........\n"
                         "4 ........\n"
                         "5 ........\n"
                         "6 ........\n"
                         "7 ........\n\n";
    ASSERT_EQ(ss.str(), grid3);
}

/**
 * Tests the Darwin::do_turn() function
 * @param DoTurn a fixture
 * @param do_turn_2 test name
 */
TEST(DoTurn, do_turn_2)
{
    Darwin d(8, 8);
    stringstream ss;

    Species s('k');
    s.add_instruction(HOP);

    Creature c(s, SOUTH);
    d.add_creature(c, 1, 1);

    const string grid1 = "Turn = 0.\n"
                         "  01234567\n"
                         "0 ........\n"
                         "1 .k......\n"
                         "2 ........\n"
                         "3 ........\n"
                         "4 ........\n"
                         "5 ........\n"
                         "6 ........\n"
                         "7 ........\n\n";
    ss << d;
    ASSERT_EQ(ss.str(), grid1);
    ss.str("");

    d.do_turn();
    const string grid2 = "Turn = 1.\n"
                         "  01234567\n"
                         "0 ........\n"
                         "1 ........\n"
                         "2 .k......\n"
                         "3 ........\n"
                         "4 ........\n"
                         "5 ........\n"
                         "6 ........\n"
                         "7 ........\n\n";
    ss << d;
    ASSERT_EQ(ss.str(), grid2);
    ss.str("");
}

/**
 * Tests the Darwin::do_turn() function
 * @param DoTurn a fixture
 * @param do_turn_3 test name
 */
TEST(DoTurn, do_turn_3)
{
    Darwin d(8, 8);
    stringstream ss;

    Species s('k');
    s.add_instruction(HOP);
    s.add_instruction(GO, 0);

    Creature c(s, SOUTH);
    d.add_creature(c, 1, 1);

    const string grid1 = "Turn = 0.\n"
                        "  01234567\n"
                        "0 ........\n"
                        "1 .k......\n"
                        "2 ........\n"
                        "3 ........\n"
                        "4 ........\n"
                        "5 ........\n"
                        "6 ........\n"
                        "7 ........\n\n";
    ss << d;
    ASSERT_EQ(ss.str(), grid1);
    ss.str("");

    for(int i = 0; i < 20; ++i)
    {
        d.do_turn();
    }

    const string grid2 = "Turn = 20.\n"
                         "  01234567\n"
                         "0 ........\n"
                         "1 ........\n"
                         "2 ........\n"
                         "3 ........\n"
                         "4 ........\n"
                         "5 ........\n"
                         "6 ........\n"
                         "7 .k......\n\n";
    ss << d;
    ASSERT_EQ(ss.str(), grid2);
    ss.str("");}

/**
 * Tests the Darwin::do_turn() function
 * @param DoTurn a fixture
 * @param do_turn_4 test name
 */
TEST(DoTurn, do_turn_4)
{
    Darwin d(8, 8);
    stringstream ss;

    Species s('k');
    s.add_instruction(IF_WALL, 3);
    s.add_instruction(HOP);
    s.add_instruction(GO, 0);
    s.add_instruction(RIGHT);
    s.add_instruction(GO, 0);

    Creature c(s, EAST);
    d.add_creature(c, 0, 0);

    const string top_left = "Turn = 0.\n"
                            "  01234567\n"
                            "0 k.......\n"
                            "1 ........\n"
                            "2 ........\n"
                            "3 ........\n"
                            "4 ........\n"
                            "5 ........\n"
                            "6 ........\n"
                            "7 ........\n\n";
    const string top_right = "Turn = 8.\n"
                             "  01234567\n"
                             "0 .......k\n"
                             "1 ........\n"
                             "2 ........\n"
                             "3 ........\n"
                             "4 ........\n"
                             "5 ........\n"
                             "6 ........\n"
                             "7 ........\n\n";
    const string bottom_right = "Turn = 16.\n"
                                "  01234567\n"
                                "0 ........\n"
                                "1 ........\n"
                                "2 ........\n"
                                "3 ........\n"
                                "4 ........\n"
                                "5 ........\n"
                                "6 ........\n"
                                "7 .......k\n\n";
    const string bottom_left = "Turn = 24.\n"
                               "  01234567\n"
                               "0 ........\n"
                               "1 ........\n"
                               "2 ........\n"
                               "3 ........\n"
                               "4 ........\n"
                               "5 ........\n"
                               "6 ........\n"
                               "7 k.......\n\n";

    ss << d;
    ASSERT_EQ(ss.str(), top_left);
    ss.str("");

    for(int i = 0; i < 8; ++i) {d.do_turn();}
    ss << d;
    ASSERT_EQ(ss.str(), top_right);
    ss.str("");

    for(int i = 0; i < 8; ++i) {d.do_turn();}
    ss << d;
    ASSERT_EQ(ss.str(), bottom_right);
    ss.str("");

    for(int i = 0; i < 8; ++i) {d.do_turn();}
    ss << d;
    ASSERT_EQ(ss.str(), bottom_left);
    ss.str("");
}

/**
 * Tests the Darwin::do_turn() function
 * @param DoTurn a fixture
 * @param do_turn_5 test name
 */
TEST(DoTurn, do_turn_5)
{
    Darwin d(8, 8);
    stringstream ss;

    Species s('k');
    s.add_instruction(IF_ENEMY, 3);
    s.add_instruction(HOP);
    s.add_instruction(GO, 0);
    s.add_instruction(INFECT);
    s.add_instruction(GO, 0);

    Creature c(s, SOUTH);
    d.add_creature(c, 1, 1);

    Species s2('j');
    Creature c2(s2);
    d.add_creature(c2, 2, 1);

    const string grid1 = "Turn = 0.\n"
                         "  01234567\n"
                         "0 ........\n"
                         "1 .k......\n"
                         "2 .j......\n"
                         "3 ........\n"
                         "4 ........\n"
                         "5 ........\n"
                         "6 ........\n"
                         "7 ........\n\n";
    ss << d;
    ASSERT_EQ(ss.str(), grid1);
    ss.str("");

    d.do_turn();
    const string grid2 = "Turn = 1.\n"
                         "  01234567\n"
                         "0 ........\n"
                         "1 .k......\n"
                         "2 .k......\n"
                         "3 ........\n"
                         "4 ........\n"
                         "5 ........\n"
                         "6 ........\n"
                         "7 ........\n\n";
    ss << d;
    ASSERT_EQ(ss.str(), grid2);
    ss.str("");
}

/**
 * Tests the Darwin::do_turn() function
 * @param DoTurn a fixture
 * @param do_turn_6 test name
 */
TEST(DoTurn, do_turn_6)
{
    Darwin d(1, 1);

    Species s('k');
    s.add_instruction(HOP);
    s.add_instruction(GO, 0);

    Creature c(s);
    d.add_creature(c, 0, 0);

    for(int i = 0; i < 10; ++i) {d.do_turn();}

    ASSERT_FALSE(d.at(0, 0)->is_enemy(c));
    ASSERT_FALSE(d.at(0, 0)->is_empty());
}