
/**
 * CSC232 - Data Structures
 * Missouri State University, Fall 2025
 *
 * @file      test_task2.cpp
 * @authors   Jim Daehn <jdaehn@missouristate.edu>
 * @brief     Google Test implementation for task 2 activities.
 */

#include "csc232.h"
#include "testing/base_test_fixture.h"
#include <gtest/gtest.h>

/**
 * @brief Namespace to encapsulate course specific macros, declarations and definitions.
 */
namespace csc232
{
#if TEST_TASK2
    /**
     * Text fixture for task 2.
     */
    class Task2TestFixture : public CSC232BaseTestFixture
    {
    };

    TEST_F( Task2TestFixture, RewriteThisTest )
    {
        std::cout << "Task 2 is ready for evaluation, but this isn't going to validate anything.\n";
        SUCCEED( );
    }
#else
    TEST( Task2TestSuite, ItIsNotReady )
    {
        std::cerr << "Task 2 is not ready for evaluation; please toggle the TEST_TASK2 macro to TRUE\n";
        SUCCEED( );
    }
#endif // TEST_TASK2

} // end namespace
