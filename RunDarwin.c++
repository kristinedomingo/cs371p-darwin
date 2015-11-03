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
#include "Darwin.h"  // Darwin interfaces

using namespace std;

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
        cout << d.get_grid();
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
        cout << d2.get_grid();
        d2.do_turn();
    }

    // ------------
    // darwin 72x72
    // without best
    // ------------

    //cout << "*** Darwin 72x72 without Best ***" << endl;
    //srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    // ------------
    // darwin 72x72
    // with best
    // ------------

    //cout << "*** Darwin 72x72 with Best ***" << endl;
    //srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    return 0;
}