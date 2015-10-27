/** @file Darwin.c++
 *  @brief This file contains all of the implementations of functions and
 *         methods in "Darwin.h".
 */

// --------
// includes
// --------

#include <cassert>   // assert
#include <string>    // string
#include "Darwin.h"  // Darwin interfaces

using namespace std;

// -----------------------------
// Species (default constructor)
// -----------------------------

/**
 * Initializes a Species object.
 */
Species::Species()
{

}

// ----------------------
// Creature (constructor)
// ----------------------

/**
 * Initializes a Creature object. Sets the passed in Species as this
 * Creature's associated Species (or uses the default Species).
 * @param s a Species object
 * @param representation a char used to display this Creature
 */
Creature::Creature(char representation, Species s)
{
    this->s = s;
    display = representation;

}

// -----------
// get_display
// -----------

/**
 * Returns the character representation of this Species.
 */
const char Creature::get_display() const
{
    return display;
}

// --------------------
// Darwin (constructor)
// --------------------

/**
 * Initializes a Darwin object, consisting of an empty grid of Creatures
 * and the current_turn set to 0 (no turns have passed). Also sets the
 * beginning (_b) and end (_e) pointers.
 * @param height the number of rows in the grid
 * @param width the number of columns in the grid
 */
Darwin::Darwin(int height, int width)
{
    // Resize empty grid (which was initialized with size 0, 0)
    grid.resize(width, vector<Creature>(height));

    this->height = height;
    this->width = width;
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
Creature* Darwin::begin() const
{
    return _b;
}

// ---
// end
// ---

/**
 * Returns an iterator (pointer) to the end (right corner) of the grid.
 */
Creature* Darwin::end() const
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
Creature* const Darwin::at(int row, int col)
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
const string Darwin::get_grid()
{
    // Add current turn
    string output = "Turn = " + to_string(current_turn) + ".\n";

    // Add column identifiers
    output += "  ";
    for(int c = 0; c < width; ++c)
    {
        output += to_string(c % 10);
    }
    output += '\n';

    // Add row displays
    for(int r = 0; r < height; ++r)
    {
        // Add row identifier
        output += to_string(r % 10) + " ";

        // Add contents of this row
        for(int c = 0; c < width; ++c)
        {
            output += at(r, c)->get_display();
        }

        output += '\n';
    }

    return output;
}