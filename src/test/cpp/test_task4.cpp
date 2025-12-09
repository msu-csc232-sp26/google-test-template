
/**
 * CSC232 - Data Structures
 * Missouri State University, Fall 2025
 *
 * @file      test_task4.cpp
 * @authors   Jim Daehn <jdaehn@missouristate.edu>
 * @brief     Google Test implementation for task 4 activities.
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
     * Text fixture for task 4.
     */
    class Task4TestFixture : public CSC232BaseTestFixture
    {
    };

    TEST_F( Task4TestFixture, RewriteThisTest )
    {
        std::cout << "Task 4 is ready for evaluation, but this isn't going to validate anything.\n";
        SUCCEED( );
    }
#else
    TEST( Task4TestSuite, ItIsNotReady )
    {
        std::cerr << "Task 4 is not ready for evaluation; please toggle the TEST_TASK4 macro to TRUE\n";
        SUCCEED( );
    }
#endif // TEST_TASK4

} // end namespace
