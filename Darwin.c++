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
 * @param dir the direction this Creature will face
 */
Creature::Creature(char representation, Species s, Direction dir)
{
    this->s = s;
    this->dir = dir;
    display = representation;
    counter = 0;
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
 * @param num_turns the total number of turns for a run
 */
Darwin::Darwin(int height, int width, int num_turns) : di(*this)
{
    // Resize empty grid (which was initialized with size 0, 0)
    grid.resize(width, vector<Creature>(height));

    this->height = height;
    this->width = width;
    this->num_turns = num_turns;
    current_turn = 0;
    _b = &grid[0][0];
    _e = _b + (height * width);
}

// -----
// begin
// -----

/**
 * Returns a Darwin_Iterator to the FIRST, NON-EMPTY, Creature in the
 * grid. If all of the Creatures in the grid are empty, returns an
 * iterator to the end.
 */
Darwin::Darwin_Iterator Darwin::begin()
{
    int row = 0;
    int col = 0;

    // Set row and column to the first (left-to-right, top-down)
    // non-empty Creature found on the board
    while(grid[row][col].get_display() == '.' && row != height)
    {
        // If the end of the column is reached, goto next row
        if(col == width - 1)
        {
            col = 0;
            ++row;
        }
        else
        {
            ++col;
        }
    }

    // If reaches one row past the end, return the end iterator
    if(row == height)
    {
        return end();
    }

    // Set the iterator's row and col to the first non-empty creature
    di.row = row;
    di.col = col;
    return di;
}

// ---
// end
// ---

/**
 * Returns a Darwin_Iterator to the LAST, NON-EMPTY, Creature in the
 * grid. If all of the Creatures in the grid are empty, returns an
 * iterator to the end (one past the end of the vector).
 */
Darwin::Darwin_Iterator Darwin::end()
{
    int row = height - 1;
    int col = width - 1;

    // Set row and column to the first (left-to-right, top-down)
    // non-empty Creature found on the board
    while(grid[row][col].get_display() == '.' && row != -1)
    {
        // If the end of the column is reached, goto next row
        if(col == 0)
        {
            col = width - 1;
            --row;
        }
        else
        {
            --col;
        }
    }

    // If reaches one row past the end, set row and column to one past the
    // right corner of the grid
    if(row == -1)
    {
        di.row = height;
        di.col = 0;
    }
    // Else, set the iterator's row and col to the last non-empty creature
    else
    {
        di.row = row;
        di.col = col;
    }

    return di;
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