/**
 * @brief   Box interface specification.
 * @file    box.h
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 *
 * @remarks CSC232 - Data Structures
 *          Missouri State University, Spring 2026
 */

#ifndef BOX_H
#define BOX_H

/**
 * Namespace to encapsulate course work in CSC232 - Data Structures.
 */
namespace csc232
{
    /**
     * A simple interface for boxes that store one item.
     * @tparam object the type of the item placed in this box
     */
    template < typename object >
    class box
    {
    public:
        /**
         * Place an item in this box.
         * @param item the item to place in this box.
         */
        virtual auto set_item( const object &item ) -> void = 0;

        /**
         * Obtain a copy of the item stored in this box.
         * @return the item stored in this box.
         */
        virtual auto get_item( ) const -> object = 0;

        /**
         * Default virtual destructor.
         */
        virtual ~box( ) = default;
    };
}

#endif // BOX_H
