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


// ---------------------------
// Species (Class Declaration)
// ---------------------------
class Species
{
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
        bool has_species; // whether or not this Creature has a Species

    public:
        // ------------------------------
        // Creature (default constructor)
        // ------------------------------

        /**
         * Initializes a Creature object. Default constructor, does NOT define
         * a species and sets has_species to false.
         */
        Creature();

        // ------------------------------
        // Creature (species constructor)
        // ------------------------------

        /**
         * Initializes a Creature object. Sets the passed in Species as this
         * Creature's associated Species, and sets has_species to true.
         * @param s a Species object
         */
        Creature(Species& s);

        // --------
        // is_empty
        // --------

        /**
         * Returns a boolean value whether or not this Creature has a Species.
         */
        bool is_empty() const;
};

// --------------------------
// Darwin (Class Declaration)
// --------------------------
class Darwin
{
    private:
        vector<vector<Creature>> grid; // the grid of Creatures
        int height;                    // the number of rows in the grid
        int width;                     // the number of columns in the grid
        int num_turns;                 // total number of turns for a Darwin run
        int current_turn;              // the current turn of the Darwin run
        Creature* _b;                  // "beginning" of the board (left corner)
        Creature* _e;                  // "end" of the board (right corner)

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
         */
        Darwin(int height, int width);

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