/** @file Darwin.c++
 *  @brief This file contains all of the implementations of functions and
 *         methods in "Darwin.h".
 */

#ifndef Darwin_c
#define Darwin_c

// --------
// includes
// --------

#include <cassert>   // assert
#include <string>    // string
#include "Darwin.h"  // Darwin interfaces

using namespace std;


// -----------
// has_species
// -----------

/**
 * Returns a boolean value whether or not this Creature has a Species.
 */
// bool Creature::has_species()
// {
//     return false;
// }


// --------------------
// Darwin (constructor)
// --------------------

/**
 * Initializes a Darwin object, consisting of an empty grid of Creatures
 * and the current_turn set to 0 (no turns have passed). Also sets the
 * beginning (_b) and end (_e) pointers.
 * @param s, a string of space-delimited integers
 */
template<int height, int width>
Darwin<height, width>::Darwin()
{
    num_turns = 0;
    current_turn = 0;
    _b = &grid[0][0];
    _e = _b + (height * width);
}

// -----
// begin
// -----

/**
 * Returns an iterator (pointer) to the beginning (left corner) of
 * the grid.
 */
template<int height, int width>
Creature* Darwin<height, width>::begin() const
{
    return _b;
}

// ---
// end
// ---

/**
 * Returns an iterator (pointer) to the end (right corner) of the grid.
 */
template<int height, int width>
Creature* Darwin<height, width>::end() const
{
    return _e;
}

// --
// at
// --

/**
 * Returns a pointer to the Creature on the grid at the row and column
 * given to this function.
 */
template<int height, int width>
const Creature* Darwin<height, width>::at(int row, int col) const
{
    return &grid[row][col];
}

// --------
// get_grid
// --------

/**
 * Returns a string representation of the Darwin object (the grid and 
 * the current turn at the time this function is called.
 */
template<int height, int width>
const string Darwin<height, width>::get_grid() const
{
    // Add current turn
    string output = "Turn = " + to_string(current_turn) + ".\n";

    // Add column identifiers
    output += "  ";
    for(int c = 0; c < width; ++c)
    {
        output += to_string(c);
    }
    output += '\n';

    // Add row displays
    for(int r = 0; r < height; ++r)
    {
        // Add row identifier
        output += to_string(r) + " ";

        // Add contents of this row
        for(int c = 0; c < width; ++c)
        {
            if(at(r, c) -> has_species())
            {

            }
            else
            {
                output += ".";
            }
        }

        output += '\n';
    }

    return output;
}

#endif // Darwin_c