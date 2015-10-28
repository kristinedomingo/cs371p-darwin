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

// -----------------------------
// Darwin_Iterator (constructor)
// -----------------------------

/**
 * Initializes a Darwin_Iterator object, default row and column
 * set to 0.
 * @param d the reference to the outer class (darwin)
 * @param row the row this iterator is at
 * @param col the col this iterator is at
 */
Darwin::Darwin_Iterator::Darwin_Iterator(Darwin& d, int row, int col) : darwin(d)
{
    this->row = row;
    this->col = col;
}

// --------------------
// operator == (equals)
// --------------------

/**
 * The equals operator, returns true if the rhs Darwin_Iterator
 * points to the same space as this one.
 */
bool Darwin::Darwin_Iterator::operator == (const Darwin::Darwin_Iterator& rhs) const
{
    return (this->row == rhs.row) && (this->col == rhs.col);
}

// -----------------------
// operator != (not equal)
// -----------------------

/**
 * The not equals operator, returns true if the rhs 
 * Darwin_Iterator does not point to the same space as this one.
 */
bool Darwin::Darwin_Iterator::operator != (const Darwin::Darwin_Iterator& rhs) const
{
    return !(*this == rhs);
}

// ----------
// operator *
// ----------

/**
 * The dereference operator, returns a pointer to the Creature
 * at this iterator's row and column.
 */
Creature* Darwin::Darwin_Iterator::operator * () const
{
    return darwin.at(row, col);
}

// ---------------------------
// operator ++ (pre-increment)
// ---------------------------

/**
 * The pre-increment operator, moves this iterator to the next
 * space in the grid.
 */
Darwin::Darwin_Iterator& Darwin::Darwin_Iterator::operator ++ ()
{
    ++col;

    // Move to next row if reached end of column
    if(col == darwin.width)
    {
        col = 0;
        ++row;
    }

    return *this;
}

// --------------------
// Darwin (constructor)
// --------------------

/**
 * Initializes a Darwin object, consisting of an empty grid of Creatures
 * and the current_turn set to 0 (no turns have passed).
 * @param height the number of rows in the grid
 * @param width the number of columns in the grid
 */
Darwin::Darwin(int height, int width) : di(*this)
{
    // Resize empty grid (which was initialized with size 0, 0)
    grid.resize(width, vector<Creature>(height));

    this->height = height;
    this->width = width;
    current_turn = 0;
}

// -----
// begin
// -----

/**
 * Returns a Darwin_Iterator first space (left corner) the grid.
 */
Darwin::Darwin_Iterator Darwin::begin()
{
    Darwin_Iterator di(*this);
    return di;
}

// ---
// end
// ---

/**
 * Returns a Darwin_Iterator to the last spaces (one past the right
 * corner) of the grid.
 */
Darwin::Darwin_Iterator Darwin::end()
{
    // One past the right corner (one row below, leftmost column)
    Darwin_Iterator di(*this, height, 0);
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