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

// -------------------------------
// operator << (Species overload)
// -------------------------------

/**
 * Overloads the << operator for the Species class. Outputs this Species'
 * character representation on the Darwin board to an ostream.
 * @param os an ostream to output the Species' render character
 * @param s the Species
 * @return an ostream with this Species' output
 */
ostream& operator << (ostream& os, const Species &s)
{
    return os << s.display;
}

// -------------------------------
// operator << (Creature overload)
// -------------------------------

/**
 * Overloads the << operator for the Creature class. Outputs this Creature's
 * Species' character representation on the Darwin board to an ostream.
 * @param os an ostream to output the Creature's Species' render
 * @param c the Creature
 * @return an ostream with this Creature's output
 */
ostream& operator << (ostream& os, const Creature &c)
{
    return os << c.s;
}

// -------------------------------
// operator << (Darwin overload)
// -------------------------------

/**
 * Overloads the << operator for the Darwin class. Outputs the state of the
 * Darwin board (Creatures and current turn) to an ostream.
 * @param os an ostream to output the Darwin grid and current turn
 * @param d the Darwin object
 * @return an ostream with this Darwin's output
 */
ostream& operator << (ostream& os, Darwin &d)
{
    // Add current turn
    os << "Turn = " << to_string(d.current_turn) << ".\n";

    // Add column identifiers
    os << "  ";
    for(int c = 0; c < d.width; ++c)
    {
        os << to_string(c % 10);
    }
    os << '\n';

    // Add row displays
    for(int r = 0; r < d.height; ++r)
    {
        // Add row identifier
        os << to_string(r % 10) << " ";

        // Add contents of this row
        for(int c = 0; c < d.width; ++c)
        {
            os << *(d.at(r, c));
        }

        os << '\n';
    }

    os << '\n';
    return os;
}

// -----------------------------
// Darwin_Iterator (constructor)
// -----------------------------

/**
 * Initializes a Darwin_Iterator object, default row and column
 * set to 0.
 * @param d the reference to a Darwin object to iterate over
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
 * @return true if rhs points to the same space as this iterator
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
 * @return true if rhs does not point to the same space as this iterator
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
 * @param a pointer to a Creature object
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
 * @return this iterator, moved to the next space in the grid
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
 * @param it the Darwin_Iterator to get the space ahead from
 * @param dir a Direction
 * @return another Darwin_Iterator at the space ahead of this one
 */
Darwin_Iterator Darwin_Iterator::ahead(Darwin_Iterator& it, Direction dir) const
{
    Darwin_Iterator space_ahead(this->darwin, it.row, it.col);

    if(dir == NORTH)
    {
        --space_ahead.row;
    }
    else if(dir == EAST)
    {
        ++space_ahead.col;
    }
    else if(dir == SOUTH)
    {
        ++space_ahead.row;
    }
    else if(dir == WEST)
    {
        --space_ahead.col;
    }
    return space_ahead;
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
 * @return true if rhs is of the same Species
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
 * @return true if rhs is NOT of the same Species
 */
bool Species::operator != (const Species& rhs) const
{
    return !(*this == rhs);
}

// ---------------
// add_instruction
// ---------------

/**
 * Adds an instruction to this Species.
 * @param instr the instruction
 * @param n the "n" associated with control instructions, defaulted
 *        to -1 for action instructions
 */
void Species::add_instruction(Instruction instr, int n)
{
    instructions.emplace_back(instr, n);
}

// -------------------
// execute_instruction
// -------------------

/**
 * Executes this Species counterth instruction.
 * @param this_space a Darwin_Iterator located at THIS Species' Creature
 * @param space_ahead a Darwin_Iterator located at the space ahead
 * @param counter the instruction to execute
 * @return the instruction that this Species executed
 */
int Species::execute_instruction(Darwin_Iterator& this_space,
                                 Darwin_Iterator& space_ahead,
                                 int counter) const
{
    // Get the instruction at counter
    pair<Instruction, int> instr = instructions[counter];
    Instruction i = instr.first;

    Creature* const creature_ahead = *space_ahead;
    Creature* const this_creature = *this_space;

    // If the counterth instruction is NOT an action instruction, follow the
    // "flow" of instructions until an action instruction is reached
    while(i != HOP && i != LEFT && i != RIGHT && i != INFECT)
    {
        // If the instruction matches the control condition, go to line "n"
        if((i == GO)                                                                                
           || (i == IF_RANDOM && rand() % 2 == 1)                                                      
           || (i == IF_WALL   && creature_ahead == nullptr)                                            
           || (i == IF_ENEMY  && creature_ahead != nullptr && creature_ahead->is_enemy(*this_creature))
           || (i == IF_EMPTY  && creature_ahead != nullptr && creature_ahead->is_empty()))
        {
            counter = instr.second;
        }

        // Else, go to next line
        else
        {
            ++counter;
        }

        // Update instruction
        instr = instructions[counter];
        i = instr.first;
    }

    // Now, the instruction SHOULD be at an action instruction
    assert(i == HOP || i == LEFT || i == RIGHT || i == INFECT);

    // If the space ahead is empty (and not a wall), move forward
    if(i == HOP && creature_ahead != nullptr && creature_ahead->is_empty())
    {
        *creature_ahead = Creature(*this_creature);
        *this_creature = Creature();
    }

    // Turn the Creature left
    else if(i == LEFT)
    {
        this_creature->turn_left();
    }

    // Turn the Creature right
    else if(i == RIGHT)
    {
        this_creature->turn_right();
    }

    // If the space ahead is an enemy, change that to be THIS Species
    else if(i == INFECT && creature_ahead->is_enemy(*this_creature))
    {
        this_creature->infect(*creature_ahead);
    }

    return counter;
}

// ----------------------
// Creature (constructor)
// ----------------------

/**
 * Initializes a Creature object. Sets the passed in Species as this
 * Creature's associated Species (or uses the default Species). The
 * default Species is an "empty" Species, represented by a "." on the
 * Darwin grid.
 * @param s a Species object
 * @param dir the direction this Creature will face
 */
Creature::Creature(Species s, Direction dir)
{
    this->s = s;
    this->dir = dir;
    counter = 0;
    flag = 0;
}

// --------
// is_enemy
// --------

/**
 * Returns true if rhs is not of the same species, AND either side isn't empty.
 * @param rhs another Creature object
 * @return true is rhs is an enemy Creature
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
 * @return true if this Creature is an empty spot on the grid
 */
bool Creature::is_empty() const
{
    stringstream ss;
    ss << s;
    return ss.str() == ".";
}

// --------
// execute
// --------

/**
 * Executes this Creature's Species' "counterth" instruction. Also
 * modifies the counter, depending on what instruction the Species
 * ended up taking.
 * @param d a Darwin object this Creature is on
 * @param it a Darwin_Iterator
 */
void Creature::execute(Darwin& d, Darwin_Iterator& it)
{
    if(!d.creature_has_gone(flag))
    {
        ++flag;

        Darwin_Iterator space_ahead = it.ahead(it, dir);

        // Species::execute_instruction returns the number of control
        // instructions that the function had to go through to reach an "action"
        // instruction, so have to increment "counter" accordingly
        counter = s.execute_instruction(it, space_ahead, counter);

        // Set counter to next instruction
        ++counter;
    }
}

// ---------
// turn_left
// ---------

/**
 * Turns this Creature left.
 */
void Creature::turn_left()
{
    if(dir == NORTH)
    {
        dir = WEST;
    }
    else if(dir == EAST)
    {
        dir = NORTH;
    }
    else if(dir == SOUTH)
    {
        dir = EAST;
    }
    else if(dir == WEST)
    {
        dir = SOUTH;
    }
}

// ---------
// turn_right
// ---------

/**
 * Turns this Creature right.
 */
void Creature::turn_right()
{
    if(dir == NORTH)
    {
        dir = EAST;
    }
    else if(dir == EAST)
    {
        dir = SOUTH;
    }
    else if(dir == SOUTH)
    {
        dir = WEST;
    }
    else if(dir == WEST)
    {
        dir = NORTH;
    }
}

// ------
// infect
// ------

/**
 * "Infects" another Creature (replaces the other Creature's Species
 * with this one, and resets the program counter).
 * @param victum another Creature
 */
void Creature::infect(Creature& victim)
{
    // Victim cannot be an empty space, and victim has to be an enemy
    if(victim.is_enemy(*this) && !victim.is_empty())
    {
        victim.s = this->s;
        victim.counter = 0;
    }
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
Darwin::Darwin(int height, int width)
{
    // Resize empty grid (which was initialized with size 0, 0)
    grid.resize(height, vector<Creature>(width));

    this->height = height;
    this->width = width;
    current_turn = 0;
}

// -----
// begin
// -----

/**
 * Returns a Darwin_Iterator first space (left corner) the grid.
 * @return a Darwin_Iterator
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
 * @return a Darwin_Iterator
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
 * @return a pointer to a Creature object
 */
Creature* const Darwin::at(int row, int col)
{
    if(row >= height || col >= width || row < 0 || col < 0)
    {
        return nullptr;
    }
    return &grid[row][col];
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

    // Make sure the row and col is a valid point to place a Creature
    if(creature_pointer != nullptr)
    {
        *creature_pointer = c;
    }
}

// -----------------
// creature_has_gone
// -----------------

/**
 * Checks to see if a Creature has gone by comparing the Creature's
 * "flag" against the current turn. Each Creature has an integer "flag",
 * that begins at 0 and is incremented after it has done a turn. This
 * way, the current turn and each Creature's "flag" (turn) can be
 * compared by this function, which will determine whether or not this
 * Creature has already gone during a Darwin turn.
 * @param flag the Creature's flag
 * @return true if the Creature has already executed an instr this turn
 */
const bool Darwin::creature_has_gone(int flag) const
{
    return flag % 2 != current_turn % 2;
}

// -------
// do_turn
// -------

/**
 * Simulates a turn on a Darwin grid.
 */
void Darwin::do_turn()
{
    Darwin_Iterator b = begin();
    Darwin_Iterator e = end();

    // Iterate through every SPACE on the Darwin grid
    while(b != e)
    {
        Creature* c = *b;

        // If the space contains a NON-EMPTY creature, give the Creature a turn
        if(!c->is_empty())
        {
            c->execute(*this, b);
        }

        // Go to next space
        ++b;
    }

    ++current_turn;
}