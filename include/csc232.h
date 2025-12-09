/**
 * CSC232 - Data Structures
 * Missouri State University, Fall 2025
 *
 * @file    csc232.h
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Macros, libraries and definitions for use in csc232 assignments.
 * @version 1.0.0
 * @date    01/01/2025
 *
 * @copyright Copyright (c) 2025 James R. Daehn
 */

#ifndef MSU_CSC232_H
#define MSU_CSC232_H

#define FALSE 0
#define TRUE 1

#define EXECUTE_PREAMBLE TRUE

#define TEST_TASK1 FALSE // TODO:  Task 1 - Step 1: Toggle TEST_TASK1 TO TRUE
#define TEST_TASK2 FALSE // TODO:  Task 2 - Step 1: Toggle TEST_TASK2 TO TRUE
#define TEST_TASK3 FALSE // TODO:  Task 3 - Step 1: Toggle TEST_TASK3 TO TRUE
#define TEST_TASK4 FALSE // TODO:  Task 4 - Step 1: Toggle TEST_TASK4 TO TRUE
#define TEST_TASK5 FALSE // TODO:  Task 5 - Step 1: Toggle TEST_TASK5 TO TRUE

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

/** Common iostream objects */
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

/** Common iomanip objects */
using std::left;
using std::right;
using std::setprecision;
using std::setw;

/**
 * @brief Common namespace for CSC232 identifiers.
 */
namespace csc232
{
    // Add any user-defined functions prescribed in your assignment below

    // DO NOT Modify anything below this line

    /**
     * @brief Generate a quasi-random UUID.
     * @return A string representation of a quasi-random UUID.
     */
    inline auto generate_uuid( ) -> std::string
    {
        static constexpr auto DISTRIBUTION_RANGE{ 15 };
        static std::random_device random_device;
        static std::mt19937 random_number_generator( random_device( ) );

        std::uniform_int_distribution< int > dist( 0, DISTRIBUTION_RANGE );

        const auto dash = std::vector{ false, false, false, false, true, false, true, false,
                                       true, false, true, false, false, false, false, false };

        auto uuid = std::string{ };
        for ( bool dash_location : dash )
        {
            const std::vector uuid_alphabet = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

            if ( dash_location )
            {
                uuid += "-";
            }
            uuid += uuid_alphabet[ dist( random_number_generator ) ];
            uuid += uuid_alphabet[ dist( random_number_generator ) ];
        }
        return uuid;
    }
} // namespace csc232

#endif // MSU_CSC232_H
