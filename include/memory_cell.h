/**
 * CSC232 - Data Structures
 * Missouri State University, Fall 2025
 *
 * @file    memory_cell.h
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Memory Cell template specification.
 * @version 1.0.0
 * @date    05/19/2025
 *
 * @copyright Copyright (c) 2025 James R. Daehn
 */

#ifndef MEMORY_CELL_H_
#define MEMORY_CELL_H_

#include "cell.h"

/**
 * A namespace to encapsulate work developed for CSC232 - Data Structures.
 */
namespace csc232
{
    /**
     * A general memory cell capable of storing a single object.
     * @tparam Object the type of object stored in this memory cell.
     */
    template < typename Object >
    class memory_cell : public cell< Object >
    {
    public:
        // TODO: Task 2 - Step 2: Declare default constructor.

        // TODO: Task 2 - Step 3: Override the default destructor.

        // TODO: Task 2 - Step 4: Declare/override the read() method

        // TODO: Task 2 - Step 5: Declare/override the write() method

    private:
        // TODO: Task 2 - Step 6: Declare data member

    };

} // csc232

#endif // MEMORY_CELL_H_
