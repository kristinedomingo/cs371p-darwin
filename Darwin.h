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
        Species grid[height][width]; // the grid of species
        int num_turns;               // total number of turns for a Darwin run
        int current_turn;            // the current turn of the Darwin run
        Species* _b;                 // "beginning" of the board (left corner)
        Species* _e;                 // "end" of the board (right corner)

    public:
        // --------------------
        // Darwin (constructor)
        // --------------------

        /**
         * Initializes a Darwin object, consisting of an empty grid of Species
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
        Species* begin() const;

        // ---
        // end
        // ---

        /**
         * Returns an iterator (pointer) to the end (right corner) of the grid.
         */
        Species* end() const;
};

#include "Darwin.c++" // http://stackoverflow.com/questions/495021/why-
                      // can-templates-only-be-implemented-in-the-header-file

#endif // Darwin_h