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
#include "gtest/gtest.h"  // google test (friend test)

using namespace std;


// ----------------------------
// Creature (Class Declaration)
// ----------------------------
class Creature
{
    public:
        // -----------
        // has_species
        // -----------

        /**
         * Returns a boolean value whether or not this Creature has a Species.
         */
        bool has_species() const
        {
            return false;
        }
};

// ---------------------------
// Species (Class Declaration)
// ---------------------------
class Species
{

};

// --------------------------
// Darwin (Class Declaration)
// --------------------------
template<int height, int width>
class Darwin
{
    private:
        Creature grid[height][width]; // the grid of Creatures
        int num_turns;                // total number of turns for a Darwin run
        int current_turn;             // the current turn of the Darwin run
        Creature* _b;                 // "beginning" of the board (left corner)
        Creature* _e;                 // "end" of the board (right corner)

    public:
        // --------------------
        // Darwin (constructor)
        // --------------------

        /**
         * Initializes a Darwin object, consisting of an empty grid of Creatures
         * and the current_turn set to 0 (no turns have passed). Also sets the
         * beginning (_b) and end (_e) pointers.
         * @param s, a string of space-delimited integers
         */
        Darwin();

        // -----
        // begin
        // -----

        /**
         * Returns an iterator (pointer) to the beginning (left corner) of
         * the grid.
         */
        Creature* begin() const;

        // ---
        // end
        // ---

        /**
         * Returns an iterator (pointer) to one PAST the end (right corner) of
         * the grid.
         */
        Creature* end() const;

        // --
        // at
        // --

        /**
         * Returns a pointer to the Creature on the grid at the row and column
         * given to this function.
         */
        const Creature* at(int row, int col) const;

        // --------
        // get_grid
        // --------

        /**
         * Returns a string representation of the Darwin object (the grid and 
         * the current turn at the time this function is called.
         */
        const string get_grid() const;
};

#endif // Darwin_h

#include "Darwin.c++" // http://stackoverflow.com/questions/495021/why-
                      // can-templates-only-be-implemented-in-the-header-file