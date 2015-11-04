/** @file RunDarwin.c++
 *  @brief This file follows the template of "RunDarwin.c++" in the public test
 *         repo (github.com/gpdowning/cs371pdw/blob/master/RunDarwin.c++). It
 *         creates species called "food", "hopper", "rover", and "trap", and
 *         runs various Darwin boards with these creatures. The output of this
 *         file should match RunDarwin.out. At the end, a user-defined "best"
 *         creature is created, that should outnumber the creatures mentioned
 *         above at the end of a 1000-turn game.
 */

// --------
// includes
// --------

#include <iostream>  // cin, cout
#include <map>       // map
#include "Darwin.h"  // Darwin interfaces

using namespace std;

// ----------------
// random_direction
// ----------------

/**
 * Helper function for below, returns a random direction.
 */
Direction random_direction()
{
    int n = rand();
    if(n % 4 == 0)
    {
        return WEST;
    }
    else if(n % 4 == 1)
    {
        return NORTH;
    }
    else if (n % 4 == 2)
    {
        return EAST;
    }
    else
    {
        return SOUTH;
    }
}

// ----
// main
// ----

/**
 * The main function. Follows the template of "RunDarwin.c++" in the public test
 * repo.
 */
int main ()
{
    // ----
    // food
    // ----

    Species food('f');
    food.add_instruction(LEFT);
    food.add_instruction(GO, 0);

    // ------
    // hopper
    // ------

    Species hopper('h');
    hopper.add_instruction(HOP);
    hopper.add_instruction(GO, 0);

    // -----
    // rover
    // -----

    Species rover('r');
    rover.add_instruction(IF_ENEMY, 9);
    rover.add_instruction(IF_EMPTY, 7);
    rover.add_instruction(IF_RANDOM, 5);
    rover.add_instruction(LEFT);
    rover.add_instruction(GO, 0);
    rover.add_instruction(RIGHT);
    rover.add_instruction(GO, 0);
    rover.add_instruction(HOP);
    rover.add_instruction(GO, 0);
    rover.add_instruction(INFECT);
    rover.add_instruction(GO, 0);

    // ----
    // trap
    // ----

    Species trap('t');
    trap.add_instruction(IF_ENEMY, 3);
    trap.add_instruction(LEFT);
    trap.add_instruction(GO, 0);
    trap.add_instruction(INFECT);
    trap.add_instruction(GO, 0);

    // ----
    // best
    // ----

    Species best('b');
    best.add_instruction(IF_ENEMY, 10);
    best.add_instruction(IF_WALL, 8);
    best.add_instruction(IF_EMPTY, 6);
    best.add_instruction(IF_RANDOM, 8);
    best.add_instruction(LEFT);
    best.add_instruction(GO, 0);
    best.add_instruction(HOP);
    best.add_instruction(GO, 0);
    best.add_instruction(RIGHT);
    best.add_instruction(GO, 0);
    best.add_instruction(INFECT);
    best.add_instruction(GO, 0);

    // ----------
    // darwin 8x8
    // ----------

    cout << "*** Darwin 8x8 ***" << endl;
    Darwin d(8, 8);

    Creature food_c(food, EAST);
    d.add_creature(food_c, 0, 0);

    Creature hopper_c(hopper, NORTH);
    d.add_creature(hopper_c, 3, 3);

    Creature hopper_c2(hopper, EAST);
    d.add_creature(hopper_c2, 3, 4);

    Creature hopper_c3(hopper, SOUTH);
    d.add_creature(hopper_c3, 4, 4);

    Creature hopper_c4(hopper, WEST);
    d.add_creature(hopper_c4, 4, 3);

    Creature food_c2(food, NORTH);
    d.add_creature(food_c2, 7, 7);

    for(int i = 0; i <= 5; ++i)
    {
        cout << d;
        d.do_turn();
    }

    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);

    Darwin d2(7, 9);

    Creature trap_c(trap, SOUTH);
    d2.add_creature(trap_c, 0, 0);

    Creature hopper_c5(hopper, EAST);
    d2.add_creature(hopper_c5, 3, 2);

    Creature rover_c(rover, NORTH);
    d2.add_creature(rover_c, 5, 4);

    Creature trap_c2(trap, WEST);
    d2.add_creature(trap_c2, 6, 8);

    for(int i = 0; i <= 5; ++i)
    {
        cout << d2;
        d2.do_turn();
    }

    // ------------
    // darwin 72x72
    // without best
    // ------------

    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);

    Darwin d3(72, 72);

    // Place 10 foods
    vector<Creature> foods;
    vector<int> positions;
    for(int i = 0; i < 10; ++i)
    {
        positions.push_back(rand() % 5184);
        Creature food_creature(food, random_direction());
        foods.push_back(food_creature);
    }

    for(int i = 0; i < 10; ++i)
    {
        d3.add_creature(foods[i], positions[i] / 72, positions[i] % 72);
    }

    // Place 10 Hoppers
    vector<Creature> hoppers;
    positions.clear();
    for(int i = 0; i < 10; ++i)
    {
        positions.push_back(rand() % 5184);
        Creature hopper_creature(hopper, random_direction());
        hoppers.push_back(hopper_creature);
    }

    for(int i = 0; i < 10; ++i)
    {
        d3.add_creature(hoppers[i], positions[i] / 72, positions[i] % 72);
    }

    // Place 10 Rovers
    vector<Creature> rovers;
    positions.clear();
    for(int i = 0; i < 10; ++i)
    {
        positions.push_back(rand() % 5184);
        Creature rover_creature(rover, random_direction());
        rovers.push_back(rover_creature);
    }

    for(int i = 0; i < 10; ++i)
    {
        d3.add_creature(rovers[i], positions[i] / 72, positions[i] % 72);
    }

    // Place 10 Traps
    vector<Creature> traps;
    positions.clear();
    for(int i = 0; i < 10; ++i)
    {
        positions.push_back(rand() % 5184);
        Creature trap_creature(trap, random_direction());
        traps.push_back(trap_creature);
    }

    for(int i = 0; i < 10; ++i)
    {
        d3.add_creature(traps[i], positions[i] / 72, positions[i] % 72);
    }

    // Print first 10 grids
    for(int i = 0; i < 10; ++i)
    {
        cout << d3;
        d3.do_turn();
    }

    // Print every 100th grid after
    for(int i = 10; i <= 1000; ++i)
    {
        if(i % 100 == 0)
        {
            cout << d3;
        }
        d3.do_turn();
    }

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);

    Darwin d4(72, 72);

    // Place 10 foods
    foods.clear();
    positions.clear();
    for(int i = 0; i < 10; ++i)
    {
        positions.push_back(rand() % 5184);
        Creature food_creature(food, random_direction());
        foods.push_back(food_creature);
    }

    for(int i = 0; i < 10; ++i)
    {
        d4.add_creature(foods[i], positions[i] / 72, positions[i] % 72);
    }

    // Place 10 Hoppers
    hoppers.clear();
    positions.clear();
    for(int i = 0; i < 10; ++i)
    {
        positions.push_back(rand() % 5184);
        Creature hopper_creature(hopper, random_direction());
        hoppers.push_back(hopper_creature);
    }

    for(int i = 0; i < 10; ++i)
    {
        d4.add_creature(hoppers[i], positions[i] / 72, positions[i] % 72);
    }

    // Place 10 Rovers
    rovers.clear();
    positions.clear();
    for(int i = 0; i < 10; ++i)
    {
        positions.push_back(rand() % 5184);
        Creature rover_creature(rover, random_direction());
        rovers.push_back(rover_creature);
    }

    for(int i = 0; i < 10; ++i)
    {
        d4.add_creature(rovers[i], positions[i] / 72, positions[i] % 72);
    }

    // Place 10 Traps
    traps.clear();
    positions.clear();
    for(int i = 0; i < 10; ++i)
    {
        positions.push_back(rand() % 5184);
        Creature trap_creature(trap, random_direction());
        traps.push_back(trap_creature);
    }

    for(int i = 0; i < 10; ++i)
    {
        d4.add_creature(traps[i], positions[i] / 72, positions[i] % 72);
    }

    // Place 10 Bests
    vector<Creature> bests;
    positions.clear();
    for(int i = 0; i < 10; ++i)
    {
        positions.push_back(rand() % 5184);
        Creature best_creature(best, random_direction());
        bests.push_back(best_creature);
    }

    for(int i = 0; i < 10; ++i)
    {
        d4.add_creature(bests[i], positions[i] / 72, positions[i] % 72);
    }

    // Print first 10 grids
    for(int i = 0; i < 10; ++i)
    {
        cout << d4;
        d4.do_turn();
    }

    // Print every 100th grid after
    for(int i = 10; i <= 1000; ++i)
    {
        if(i % 100 == 0)
        {
            cout << d4;
        }
        d4.do_turn();
    }

    // Print number of each Creature
    Darwin_Iterator begin = d4.begin();
    Darwin_Iterator end = d4.end();
    map<string, int> counts;
    cout << "Creature count:" << endl;

    while(begin != end)
    {
        // Get the character of the Creature
        stringstream ss;
        ss << *(*begin);
        string creature_character = ss.str();
        ss.str("");

        // If it doesn't already exist in the map, add it
        if(counts.count(creature_character) == 0)
        {
            counts.insert(pair<string, int>(creature_character, 0));
        }

        // Else, increment the Creature's counter
        else
        {
            ++counts.at(creature_character);
        }

        ++begin;
    }

    // Now, loop through the map and print counts
    for(auto const& count : counts)
    {
        // Ignore empty Creatures
        if(count.first != ".")
        {
            cout << "Creature " << count.first << " has " << count.second << endl;
        }
    }

    return 0;
}