
/**
 * CSC232 - Data Structures
 * Missouri State University, Fall 2025
 *
 * @file      test_task1.cpp
 * @authors   Jim Daehn <jdaehn@missouristate.edu>
 * @brief     Google Test implementation for task 1 activities.
 */

#include "csc232.h"
#include "testing/base_test_fixture.h"
#include <gtest/gtest.h>

/**
 * @brief Namespace to encapsulate course specific macros, declarations and definitions.
 */
namespace csc232
{
#if TEST_TASK1
    /**
     * Text fixture for task 1.
     */
    class Task1TestFixture : public CSC232BaseTestFixture
    {
    };

    TEST_F( Task1TestFixture, RewriteThisTest )
    {
        std::cout << "Task 1 is ready for evaluation, but this isn't going to validate anything.\n";
        SUCCEED( );
    }
#else
    TEST( Task1TestSuite, ItIsNotReady )
    {
        std::cerr << "Task 1 is not ready for evaluation; please toggle the TEST_TASK1 macro to TRUE\n";
        SUCCEED( );
    }
#endif // TEST_TASK1

} // end namespace
