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

#include <string> // string
#include <vector> // vector
#include <iostream>

using namespace std;

// ----------------
// Direction (enum)
// ----------------
enum Direction {NORTH, EAST, SOUTH, WEST};

// ---------------------------
// Species (Class Declaration)
// ---------------------------
class Species
{
    private:

    public:
        // -----------------------------
        // Species (default constructor)
        // -----------------------------

        /**
         * Initializes a Species object.
         */
        Species();
};

// ----------------------------
// Creature (Class Declaration)
// ----------------------------
class Creature
{
    private:
        Species s;        // the Species of this Creature (if any)
        Direction dir;    // the direction this Creature is facing
        int counter;      // the program counter
        char display;     // the representation of this Creature on the grid

    public:
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
        Creature(char representation = '.', 
                 Species s = Species(),
                 Direction dir = NORTH);

        // -----------
        // get_display
        // -----------

        /**
         * Returns the character representation of this Species.
         */
        const char get_display() const;
};

// --------------------------
// Darwin (Class Declaration)
// --------------------------
class Darwin
{
    public:

        // -----------------------------------
        // Darwin_Iterator (Class Declaration)
        // -----------------------------------
        class Darwin_Iterator
        {
            friend class Darwin;

            private:
                int row;        // row this iterator is at
                int col;        // column this iterator is at
                Darwin& darwin; // reference to outer class

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
                Darwin_Iterator(Darwin& d, int row = 0, int col = 0) : darwin(d)
                {
                    this->row = row;
                    this->col = col;
                }

                // ----------
                // operator *
                // ----------

                /**
                 * The dereference operator, returns a pointer to the Creature
                 * at this iterator's row and column.
                 */
                Creature* operator * () const
                {
                    return darwin.at(row, col);
                }
        };

    private:
        vector<vector<Creature>> grid; // the grid of Creatures
        int height;                    // the number of rows in the grid
        int width;                     // the number of columns in the grid
        int num_turns;                 // total number of turns for a Darwin run
        int current_turn;              // the current turn of the Darwin run
        Creature* _b;                  // "beginning" of the board (left corner)
        Creature* _e;                  // "end" of the board (right corner)
        Darwin_Iterator di;            // an iterator over non-empty creatures

    public:
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
        Darwin(int height, int width, int num_turns);

        // -----
        // begin
        // -----

        /**
         * Returns a Darwin_Iterator to the FIRST, NON-EMPTY, Creature in the
         * grid. If all of the Creatures in the grid are empty, returns an
         * iterator to the end.
         */
        Darwin_Iterator begin();

        // ---
        // end
        // ---

        /**
         * Returns a Darwin_Iterator to the LAST, NON-EMPTY, Creature in the
         * grid. If all of the Creatures in the grid are empty, returns an
         * iterator to the end (one past the end of the vector).
         */
        Darwin_Iterator end();

        // --
        // at
        // --

        /**
         * Returns a pointer to the Creature on the grid at the row and column
         * given to this function.
         */
        Creature* const at(int row, int col);

        // --------
        // get_grid
        // --------

        /**
         * Returns a string representation of the Darwin object (the grid and 
         * the current turn at the time this function is called.
         */
        const string get_grid();
};

#endif // Darwin_h