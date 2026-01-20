/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2026
 *
 * @file    main.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Entry-point for main target.
 * @version 1.0.0
 * @date    01/01/2025
 *
 * @copyright Copyright (c) 2026 James R. Daehn
 */

#include <cstdlib>
#include <iostream>

auto main( ) -> int
{
#if TEST_TASK3
    auto cell = std::make_unique< csc232::memory_cell< int > >( );
    std::cout << "Initially, cell contains:" << std::endl;
    std::cout << cell->read( ) << std::endl;
    auto constexpr NUM_STUDENTS{ 10 };
    std::cout << "Writing " << NUM_STUDENTS << " students in memory." << std::endl;
    cell->write( NUM_STUDENTS );
    std::cout << "Cell now contains: ";
    std::cout << cell->read( ) << std::endl;
#endif

    return EXIT_SUCCESS;
}
