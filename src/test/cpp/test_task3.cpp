
/**
 * CSC232 - Data Structures
 * Missouri State University, Fall 2025
 *
 * @file      test_task3.cpp
 * @authors   Jim Daehn <jdaehn@missouristate.edu>
 * @brief     Google Test implementation for task 3 activities.
 */

#include "csc232.h"
#include "testing/base_test_fixture.h"
#include <gtest/gtest.h>

/**
 * @brief Namespace to encapsulate course specific macros, declarations and definitions.
 */
namespace csc232
{
#if TEST_TASK3
    /**
     * Text fixture for task 3.
     */
    class Task3TestFixture : public CSC232BaseTestFixture
    {
    };

    TEST_F( Task3TestFixture, RewriteThisTest )
    {
        std::cout << "Task 3 is ready for evaluation, but this isn't going to validate anything.\n";
        SUCCEED( );
    }
#else
    TEST( Task3TestSuite, ItIsNotReady )
    {
        std::cerr << "Task 3 is not ready for evaluation; please toggle the TEST_TASK3 macro to TRUE\n";
        SUCCEED( );
    }
#endif // TEST_TASK3

} // end namespace
