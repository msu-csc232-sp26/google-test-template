/**
 * @brief   Entry-point for main target.
 * @file    main.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 *
 * @remarks CSC232 - Data Structures
 *          Missouri State University, Spring 2026
 */

#include "csc232.h"
#include "plain_box.h"
#include "safe_deposit_box.h"

using csc232::box;
using csc232::plain_box;
using csc232::safe_deposit_box;

auto main( ) -> int
{
    box< std::string > *box_ptr = new plain_box< std::string >{ };
    box_ptr->set_item( "CSC232 - Data Structures!" );
    cout << "Current item stored in box: " << box_ptr->get_item( ) << endl;
    delete box_ptr;
    box_ptr = nullptr;
#if TEST_TASK_3
    const auto password{ std::string{ "csc232!" } };
    box_ptr = new safe_deposit_box< std::string >{ password };
    try
    {
        box_ptr->set_item( "Safe deposit item" );
    }
    catch ( const std::exception &e )
    {
        std::cerr << e.what( ) << std::endl;
    }

    try
    {
        const auto item = box_ptr->get_item( );
        cout << "Current item stored in safe deposit box: " << item << endl;
    }
    catch ( const std::exception &e )
    {
        std::cerr << e.what( ) << std::endl;
    }

    if ( dynamic_cast< safe_deposit_box< std::string > * >( box_ptr )->unlock( "csc232!" ) )
    {
        box_ptr->set_item( "Safe deposit item" );
        cout << "Current item stored in safe deposit box: " << box_ptr->get_item( ) << endl;
    }
    delete box_ptr;
    box_ptr = nullptr;
#endif

    return EXIT_SUCCESS;
}
