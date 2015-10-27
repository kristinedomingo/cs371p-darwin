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

using namespace std;


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
         */
        Creature(char representation = '.', Species s = Species());

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
         * @param num_turns the total number of turns for a run
         */
        Darwin(int height, int width, int num_turns);

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