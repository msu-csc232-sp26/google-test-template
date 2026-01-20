/**
 * @brief   Plain box specification.
 * @file    plain_box.h
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 *
 * @remarks CSC232 - Data Structures
 *          Missouri State University, Spring 2026
 */

#ifndef PLAIN_BOX_H
#define PLAIN_BOX_H

#include "box.h"

/**
 * Namespace to encapsulate course work in CSC232 - Data Structures.
 */
namespace csc232
{
    /**
     * A basic implementation of the box interface.
     * @tparam object the type of item stored in this PlainBox.
     */
    template < typename object >
    class plain_box : public box< object >
    {
    public:
        /**
         * Initializing constructor.
         * @param initial_item an initial item to store in this PlainBox
         */
        explicit plain_box( const object &initial_item = object{ } );

        /**
         * Default destructor.
         */
        ~plain_box( ) noexcept override = default;

        /**
         * Item mutator method.
         * @param an_item an item to place in this PlainBox, replacing any existing item
         */
        auto set_item( const object &an_item ) -> void override;

        /**
         * Item accessor method.
         * @return a copy of the item currently stored in this PlainBox.
         */
        auto get_item( ) const -> object override;

    private:
        object item;
    };

} // csc232

#endif // PLAIN_BOX_H
