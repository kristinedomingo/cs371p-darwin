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


// --------------------
// Darwin (constructor)
// --------------------

/**
 * Initializes a Darwin object, consisting of an empty grid of Species
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
Species* Darwin<height, width>::begin() const
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
Species* Darwin<height, width>::end() const
{
    return _e;
}

#endif // Darwin_c