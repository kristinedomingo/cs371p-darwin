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
// Darwin_Iterator (constructor)
// -----------------------------

/**
 * Initializes a Darwin_Iterator object, default row and column
 * set to 0.
 * @param d the reference to the outer class (darwin)
 * @param row the row this iterator is at
 * @param col the col this iterator is at
 */
Darwin_Iterator::Darwin_Iterator(Darwin& d, int row, int col) : darwin(d)
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
 * @param rhs the Darwin_Iterator to compare to
 */
bool Darwin_Iterator::operator == (const Darwin_Iterator& rhs) const
{
    return (this->row == rhs.row) && (this->col == rhs.col);
}

// -----------------------
// operator != (not equal)
// -----------------------

/**
 * The not equals operator, returns true if the rhs
 * Darwin_Iterator does not point to the same space as this one.
 * @param rhs the Darwin_Iterator to compare to
 */
bool Darwin_Iterator::operator != (const Darwin_Iterator& rhs) const
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
Creature* Darwin_Iterator::operator * () const
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
Darwin_Iterator& Darwin_Iterator::operator ++ ()
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

// -----
// ahead
// -----

/**
 * Returns an iterator to the space "ahead" of this one (ahead has
 * different meanings depending on what "direction" is).
 * @param dir a Direction
 */
Darwin_Iterator Darwin_Iterator::ahead(Direction dir) const
{
    return *this;
}

// -----------------------------
// Species (default constructor)
// -----------------------------

/**
 * Initializes a Species object. The "default" Species is represented
 * by a '.', meaning, when the Darwin board is initially constructed,
 * it creates a grid of Creatures that all have the default Species.
 * @param representation a char used to display this Species
 */
Species::Species(char representation)
{
    display = representation;
}

// --------------------
// operator == (equals)
// --------------------

/**
 * Returns true if the rhs Species is of the same species.
 * @param rhs the Species to compare to
 */
bool Species::operator == (const Species& rhs) const
{
    return this->display == rhs.display;
}

// ------------------------
// operator != (not equals)
// ------------------------

/**
 * Returns true if the rhs Species is NOT of the same species.
 * @param rhs the Species to compare to
 */
bool Species::operator != (const Species& rhs) const
{
    return !(*this == rhs);
}

// ------
// render
// ------

/**
 * Returns this Species' rendering on the Darwin grid.
 */
char Species::render() const
{
    return display;
}

// -------------------
// execute_instruction
// -------------------

/**
 * Executes this Species counterth instruction.
 * @param darwin the Darwin grid
 * @param it a Darwin_Iterator
 * @param dir the Direction the Creature is facing
 * @param counter the instruction to execute
 */
void Species::execute_instruction(Darwin& darwin, Darwin_Iterator& it, 
                                  Direction dir, int counter) const
{
    // Instruction instr = instructions[counter];
    // Darwin_Iterator space_ahead = it.ahead(dir);

    // if(instr == HOP)
    // {
    //     if(space_ahead != nullptr && !space_ahead->is_empty())
    //     {
    //         *space_ahead = Creature(*this);
    //     }
    // }
}

// ----------------------
// Creature (constructor)
// ----------------------

/**
 * Initializes a Creature object. Sets the passed in Species as this
 * Creature's associated Species (or uses the default Species).
 * @param s a Species object
 * @param dir the direction this Creature will face
 */
Creature::Creature(Species s, Direction dir)
{
    this->s = s;
    this->dir = dir;
    counter = 0;
}

// --------
// is_enemy
// --------

/**
 * Returns true if rhs is not of the same species, AND either side isn't empty.
 * @param rhs another Creature object
 */
bool Creature::is_enemy(const Creature& rhs) const
{
    return (this->s != rhs.s) && (!rhs.is_empty()) && (!this->is_empty());
}

// --------
// is_empty
// --------

/**
 * Returns true if this Creature's Species is the default Species,
 * in other words, this Creature is an "empty" space on the grid.
 */
bool Creature::is_empty() const
{
    return s.render() == '.';
}

// --------
// execute
// --------

/**
 * Executes this Creature's Species' "counterth" instruction.
 * @param darwin a Darwin object
 * @param it a Darwin_Iterator
 */
void Creature::execute(Darwin& darwin, Darwin_Iterator& it) const
{
    // TODO: add check to see if creature has gone already
    s.execute_instruction(darwin, it, dir, counter);
}

// -------------------------------
// operator << (Creature overload)
// -------------------------------

/**
 * Overloads the << operator for the Creature class.
 * @param os an ostream to output the Creature's Species' render
 * @param c the Creature
 */
ostream& operator << (ostream& os, const Creature &c)
{
    return os << c.s.render();
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
Darwin_Iterator Darwin::begin()
{
    Darwin_Iterator di(*this);
    return di;
}

// ---
// end
// ---

/**
 * Returns a Darwin_Iterator to the last space (one past the right
 * corner) of the grid.
 */
Darwin_Iterator Darwin::end()
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
 * given to this function. If the row or column is out of bounds,
 * returns a nullptr.
 * @param row the row to look at
 * @param the column to look at
 */
Creature* const Darwin::at(int row, int col)
{
    if(row >= height || col >= width)
    {
        return nullptr;
    }
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
    stringstream output;
    output << "Turn = " << to_string(current_turn) << ".\n";

    // Add column identifiers
    output << "  ";
    for(int c = 0; c < width; ++c)
    {
        output << to_string(c % 10);
    }
    output << '\n';

    // Add row displays
    for(int r = 0; r < height; ++r)
    {
        // Add row identifier
        output << to_string(r % 10) << " ";

        // Add contents of this row
        for(int c = 0; c < width; ++c)
        {
            output << *(at(r, c));
        }

        output << '\n';
    }

    return output.str();
}

// ------------
// add_creature
// ------------

/**
 * Places a creature on the grid at a specified point.
 * @param c a Creature to place on the grid
 * @param row the row to place this creature in
 * @param col the col to place this creature in
 */
void Darwin::add_creature(Creature& c, int row, int col)
{
    Creature* const creature_pointer = at(row, col);
    if(creature_pointer != nullptr)
    {
        *creature_pointer = c;
    }
}

// -------
// do_turn
// -------

/**
 * Simulates a turn on a Darwin grid.
 * @param d a Darwin object to simulate a turn on
 */
void do_turn(Darwin& d)
{
    Darwin_Iterator b = d.begin();
    Darwin_Iterator e = d.end();

    // Iterate through every SPACE on the Darwin grid
    while(b != e)
    {
        Creature* c = *b;

        // If the space contains a NON-EMPTY creature, give the Creature a turn.
        if(!c->is_empty())
        {
            c->execute(d, b);
        }

        ++b;
    }
}