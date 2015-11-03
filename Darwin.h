/** @file Darwin.h
 *  @brief This file contains the interfaces to the functions and methods
 *         in Darwin.c++
 * \mainpage Darwin
 * "Darwin" is project #4 of CS 371P, Object-Oriented Programming.
 */

#ifndef Darwin_h
#define Darwin_h

// --------
// includes
// --------

#include <string>         // string
#include <vector>         // vector
#include <sstream>        // stringstream
#include "gtest/gtest.h"  // friend tests

using namespace std;

// ----------------
// Direction (enum)
// ----------------
enum Direction {NORTH, EAST, SOUTH, WEST};

// ------------------
// Instruction (enum)
// ------------------
enum Instruction {HOP, LEFT, RIGHT, INFECT,
                  IF_EMPTY, IF_WALL, IF_RANDOM, IF_ENEMY, GO};

// Forward declarations
class Darwin;
class Creature;

// -----------------------------------
// Darwin_Iterator (Class Declaration)
// -----------------------------------
class Darwin_Iterator
{
    private:
        int row;        // row this iterator is at
        int col;        // column this iterator is at
        Darwin& darwin;  // reference to outer class

    public:
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
        Darwin_Iterator(Darwin& d, int row = 0, int col = 0);

        // --------------------
        // operator == (equals)
        // --------------------

        /**
         * The equals operator, returns true if the rhs Darwin_Iterator
         * points to the same space as this one.
         * @param rhs the Darwin_Iterator to compare to
         */
        bool operator == (const Darwin_Iterator& rhs) const;

        // -----------------------
        // operator != (not equal)
        // -----------------------

        /**
         * The not equals operator, returns true if the rhs
         * Darwin_Iterator does not point to the same space as this one.
         * @param rhs the Darwin_Iterator to compare to
         */
        bool operator != (const Darwin_Iterator& rhs) const;

        // ----------
        // operator *
        // ----------

        /**
         * The dereference operator, returns a pointer to the Creature
         * at this iterator's row and column.
         */
        Creature* operator * () const;

        // ---------------------------
        // operator ++ (pre-increment)
        // ---------------------------

        /**
         * The pre-increment operator, moves this iterator to the next
         * space in the grid.
         */
        Darwin_Iterator& operator ++ ();

        // -----
        // ahead
        // -----

        /**
         * Returns an iterator to the space "ahead" of this one (ahead has
         * different meanings depending on what "direction" is).
         * @param it the Darwin_Iterator to get the space ahead from
         * @param dir a Direction
         */
        Darwin_Iterator ahead(Darwin_Iterator& it, Direction dir) const;
};

// ---------------------------
// Species (Class Declaration)
// ---------------------------
class Species
{
    private:
        char display;                    // render of this Species on the grid
        vector<pair<Instruction, int>>   // this Species' instructions
                         instructions;

        FRIEND_TEST(AddInstruction, add_instruction_1);
        FRIEND_TEST(AddInstruction, add_instruction_2);
        FRIEND_TEST(AddInstruction, add_instruction_3);
        FRIEND_TEST(AddInstruction, add_instruction_4);

    public:
        // -----------------------------
        // Species (default constructor)
        // -----------------------------

        /**
         * Initializes a Species object. The "default" Species is represented
         * by a '.', meaning, when the Darwin board is initially constructed,
         * it creates a grid of Creatures that all have the default Species.
         * @param representation a char used to display this Species
         */
        Species(char representation = '.');

        // --------------------
        // operator == (equals)
        // --------------------

        /**
         * Returns true if the rhs Species is of the same species.
         * @param rhs the Species to compare to
         */
        bool operator == (const Species& rhs) const;

        // ------------------------
        // operator != (not equals)
        // ------------------------

        /**
         * Returns true if the rhs Species is NOT of the same species.
         * @param rhs the Species to compare to
         */
        bool operator != (const Species& rhs) const;

        // ------
        // render
        // ------

        /**
         * Returns this Species' rendering on the Darwin grid.
         */
        char render() const;

        // ---------------
        // add_instruction
        // ---------------

        /**
         * Adds an instruction to this Species.
         * @param instr the instruction
         * @param n the "n" associated with control instructions, defaulted
         *        to -1 for action instructions
         */
        void add_instruction(Instruction instr, int n = -1);

        // -------------------
        // execute_instruction
        // -------------------

        /**
         * Executes this Species counterth instruction.
         * @param this_space a Darwin_Iterator located at THIS Species' Creature
         * @param space_ahead a Darwin_Iterator located at the space ahead
         * @param counter the instruction to execute
         * @return the number of control instructions this function had to do
         */
        int execute_instruction(Darwin_Iterator& this_space,
                                Darwin_Iterator & space_ahead,
                                int counter) const;
};

// ----------------------------
// Creature (Class Declaration)
// ----------------------------
class Creature
{
    private:
        Species s;      // the Species of this Creature (if any)
        Direction dir;  // the direction this Creature is facing
        int counter;    // the program counter
        int flag;       // used to check if this Creature has gone during a turn

        // Overload of the << operator to allow use with Creature
        friend ostream& operator << (ostream&, const Creature&);

    public:
        // ----------------------
        // Creature (constructor)
        // ----------------------

        /**
         * Initializes a Creature object. Sets the passed in Species as this
         * Creature's associated Species (or uses the default Species).
         * @param s a Species object
         * @param dir the direction this Creature will face
         */
        Creature(Species s = Species(), Direction dir = NORTH);

        // --------
        // is_enemy
        // --------

        /**
         * Returns true if the rhs Creature is not of the same species, AND 
         * either side isn't empty.
         * @param rhs another Creature object
         */
        bool is_enemy(const Creature& rhs) const;

        // --------
        // is_empty
        // --------

        /**
         * Returns true if this Creature's Species is the default Species,
         * in other words, this Creature is an "empty" space on the grid.
         */
        bool is_empty() const;

        // --------
        // execute
        // --------

        /**
         * Executes this Creature's Species' "counterth" instruction.
         * @param d a Darwin object this Creature is on
         * @param it a Darwin_Iterator
         */
        void execute(Darwin& d, Darwin_Iterator& it);

        // ---------
        // turn_left
        // ---------

        /**
         * Turns this Creature left.
         */
        void turn_left();

        // ---------
        // turn_right
        // ---------

        /**
         * Turns this Creature right.
         */
        void turn_right();

        // ------------
        // get_infected
        // ------------

        /**
         * Causes this Creature to become "infected" by another Species, also
         * resetting the program counter to 0.
         * @param infector another Species
         */
        void get_infected(const Species& infector);
};

// -------------------------------
// operator << (Creature overload)
// -------------------------------

/**
 * Overloads the << operator for the Creature class.
 * @param os an ostream to output the Creature's Species' render
 * @param c the Creature
 */
ostream& operator << (ostream& os, const Creature &c);

// --------------------------
// Darwin (Class Declaration)
// --------------------------
class Darwin
{
    private:
        vector<vector<Creature>> grid; // the grid of Creatures
        int height;                    // the number of rows in the grid
        int width;                     // the number of columns in the grid
        int current_turn;              // the current turn of the Darwin run

        friend class Darwin_Iterator;

    public:
        // --------------------
        // Darwin (constructor)
        // --------------------

        /**
         * Initializes a Darwin object, consisting of an empty grid of Creatures
         * and the current_turn set to 0 (no turns have passed).
         * @param height the number of rows in the grid
         * @param width the number of columns in the grid
         */
        Darwin(int height, int width);

        // -----
        // begin
        // -----

        /**
         * Returns a Darwin_Iterator first space (left corner) the grid.
         */
        Darwin_Iterator begin();

        // ---
        // end
        // ---

        /**
         * Returns a Darwin_Iterator to the last space (one past the right
         * corner) of the grid.
         */
        Darwin_Iterator end();

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
        Creature* const at(int row, int col);

        // --------
        // get_grid
        // --------

        /**
         * Returns a string representation of the Darwin object (the grid and 
         * the current turn) at the time this function is called.
         */
        const string get_grid();

        // ------------
        // add_creature
        // ------------

        /**
         * Places a creature on the grid at a specified point.
         * @param c a Creature to place on the grid
         * @param row the row to place this creature in
         * @param col the col to place this creature in
         */
        void add_creature(Creature& c, int row, int col);

        // -----------------
        // creature_has_gone
        // -----------------

        /**
         * Checks to see if a Creature has gone by comparing the Creature's
         * "flag" against the current turn.
         * @param flag the Creature's flag
         */
        const bool creature_has_gone(int flag) const;

        // -------
        // do_turn
        // -------

        /**
         * Simulates a turn on a Darwin grid.
         */
        void do_turn();
};

#endif // Darwin_h