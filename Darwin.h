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
#include <sstream>   // stringstream

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
        char display;     // the representation of this Species on the grid

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
};

// ----------------------------
// Creature (Class Declaration)
// ----------------------------
class Creature
{
    public:
        Species s;        // the Species of this Creature (if any)
        Direction dir;    // the direction this Creature is facing
        int counter;      // the program counter

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
        };

    private:
        vector<vector<Creature>> grid; // the grid of Creatures
        int height;                    // the number of rows in the grid
        int width;                     // the number of columns in the grid
        int current_turn;              // the current turn of the Darwin run
        Darwin_Iterator di;            // an iterator over spaces in the grid

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
};

#endif // Darwin_h