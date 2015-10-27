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

// ------------------------------
// Creature (default constructor)
// ------------------------------

/**
 * Initializes a Creature object. Default constructor, does NOT define
 * a species and sets has_species to false.
 */
Creature::Creature()
{
    has_species = false;
}

// ------------------------------
// Creature (species constructor)
// ------------------------------

/**
 * Initializes a Creature object. Sets the passed in Species as this
 * Creature's associated Species, and sets has_species to true.
 * @param s a Species object
 */
Creature::Creature(Species& s)
{
    this->s = s;
    has_species = true;
}


// --------
// is_empty
// --------

/**
 * Returns a boolean value whether or not this Creature has a Species.
 */
bool Creature::is_empty() const
{
    return has_species;
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
const Creature* Darwin::at(int row, int col) const
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
const string Darwin::get_grid() const
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
            if(at(r, c) -> is_empty())
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