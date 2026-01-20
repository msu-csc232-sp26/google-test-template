/**
 * @brief   PlainBox implementation.
 * @file    plain_box.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 *
 * @remarks CSC232 - Data Structures
 *          Missouri State University, Spring 2026
 */

#include "plain_box.h"

/**
 * Namespace to encapsulate course work in CSC232 - Data Structures.
 */
namespace csc232
{
    template < typename object >
    plain_box< object >::plain_box( const object &initial_item ) : item{ initial_item }
    {
        // intentionally empty
    }

    template < typename object >
    auto plain_box< object >::set_item( const object &an_item ) -> void
    {
        item = an_item;
    }

    template < typename object >
    auto plain_box< object >::get_item( ) const -> object
    {
        return item;
    }
} // csc232
