
/**
 * CSC232 - Data Structures
 * Missouri State University, Fall 2025
 *
 * @file      test_task5.cpp
 * @authors   Jim Daehn <jdaehn@missouristate.edu>
 * @brief     Google Test implementation for task 5 activities.
 */

#include "csc232.h"
#include "testing/base_test_fixture.h"
#include <gtest/gtest.h>

/**
 * @brief Namespace to encapsulate course specific macros, declarations and definitions.
 */
namespace csc232
{
#if TEST_TASK4
    /**
     * Text fixture for task 5.
     */
    class Task5TestFixture : public CSC232BaseTestFixture
    {
    };

    TEST_F( Task5TestFixture, RewriteThisTest )
    {
        std::cout << "Task 5 is ready for evaluation, but this isn't going to validate anything.\n";
        SUCCEED( );
    }
#else
    TEST( Task5TestSuite, ItIsNotReady )
    {
        std::cerr << "Task 5 is not ready for evaluation; please toggle the TEST_TASK5 macro to TRUE\n";
        SUCCEED( );
    }
#endif // TEST_TASK5

} // end namespace
