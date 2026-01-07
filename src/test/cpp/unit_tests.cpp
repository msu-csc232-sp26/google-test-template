/**
 * CSC232 - Data Structures
 * Missouri State University, Fall 2025
 *
 * @file    unit_tests.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Assignment unit testing for evaluation.
 * @version 1.0.0
 * @date    12/13/25
 *
 * @copyright Copyright (c) 2025 James R. Daehn
 */

// unit_tests.cpp
#include "base_test_fixture.h"
#include "csc232.h"
#if TEST_TASK_1
#include "lock_box.h"
#endif
#include "gtest/gtest.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>

// -----------------------------------------------------------------------------
// Task 1 Fixture and Tests
// -----------------------------------------------------------------------------
#if TEST_TASK_1
class Task1 : public csc232::CSC232BaseTestFixture
{
protected:
    void SetUp( ) override
    {
        // Initialize any shared state/resources for Task 1 tests.
    }

    void TearDown( ) override
    {
        // Cleanup for Task 1.
    }
};

TEST_F( Task1TestFixture, RewriteThisTest )
    {
        std::cout << "Task 1 is ready for evaluation, but this isn't going to validate anything.\n";
        SUCCEED( );
    }

#else
TEST( Task1, ItIsNotReady )
{
    std::cerr << "Task 1 is not ready for evaluation; please toggle the TEST_TASK1 macro to TRUE\n";
    SUCCEED( );
}
#endif // TEST_TASK_1

// -----------------------------------------------------------------------------
// Task 2 Fixture and Tests
// -----------------------------------------------------------------------------
#if TEST_TASK_2
class Task2 : public ::testing::Test
{
protected:
    void SetUp( ) override { }
    void TearDown( ) override { }
};

// --- Replace these with your real Task 2 unit tests ---
TEST_F( Task2, ItGetsDefaultItemWithValidPassword )
{
    const auto box = csc232::lock_box< int >( "password" );
    auto item = box.get_item( );
    EXPECT_EQ( item, int{ } );
}

TEST_F( Task2, ItThrowsExceptionWhenTryingToRetrieveLockedItem )
{
    auto box = csc232::lock_box< int >( "password" );
    box.lock( );
    EXPECT_THROW( const auto item = box.get_item( ), std::logic_error );
}

TEST_F( Task2, ItCanUpdateItemWhenNotLocked )
{
    auto box = csc232::lock_box< int >( "password" );
    constexpr auto expected{ 1 };

    box.set_item( expected );
    const auto actual = box.get_item( );
    EXPECT_EQ( expected, actual );
}

TEST_F( Task2, ItCannotUpdateItemWhenLocked )
{
    auto box = csc232::lock_box< int >( "password" );
    constexpr auto expected{ 1 };
    auto actual = int{ };
    box.lock( );
    try
    {
        box.set_item( expected );
        actual = box.get_item( );
    }
    catch ( std::logic_error )
    {
        EXPECT_NE( expected, actual );
        EXPECT_EQ( int{ }, actual );
    }
}

TEST_F( Task2, ItWritesErrorMessagesToStandardErrorOutputStream )
{
    std::ostringstream capture;
    {
        csc232::ScopedCerrRedirect guard( capture );
        auto box = csc232::lock_box< int >( "password" );
        box.lock( );
        constexpr auto item{ 1 };
        box.set_item( item );
    }
    EXPECT_EQ( capture.str( ), "Attempt to add item to locked box.\n" );
}

#else
TEST( Task2, ItIsNotReady )
{
    std::cerr << "Task 2 is not ready for evaluation; please toggle the TEST_TASK1 macro to TRUE\n";
    SUCCEED( );
}
#endif // TEST_TASK_2

// -----------------------------------------------------------------------------
// Task 3 Fixture and Tests
// -----------------------------------------------------------------------------
#if TEST_TASK_3
class Task3 : public ::testing::Test
{
protected:
    void SetUp( ) override { }
    void TearDown( ) override { }
};

// --- Replace these with your real Task 3 unit tests ---
TEST_F( Task3, ItUnlocksWithTheCorrectPassword )
{
    auto box = csc232::lock_box< int >( "password" );
    auto constexpr expected{ 1 };
    auto actual = int{ };
    box.set_item( expected );
    box.lock( );
    const auto is_unlocked = box.unlock( "password" );
    try
    {
        actual = box.get_item( );
    }
    catch ( std::logic_error error )
    {
        FAIL( );
    }
    EXPECT_TRUE( is_unlocked );
    EXPECT_FALSE( box.is_locked( ) );
    EXPECT_FALSE( box.is_locked_out( ) );
    EXPECT_EQ( expected, actual );
}

TEST_F( Task3, ItRemainsLockedWhenUsingWrongPassword )
{
    auto box = csc232::lock_box< int >( "password" );
    auto constexpr expected{ 1 };
    auto actual = int{ };
    box.set_item( expected );
    box.lock( );
    const auto is_unlocked = box.unlock( "this ain't it" );
    try
    {
        actual = box.get_item( );
    }
    catch ( std::logic_error error )
    {
        EXPECT_NE( expected, actual );
        EXPECT_TRUE( box.is_locked( ) );
        EXPECT_FALSE( box.is_locked_out( ) );
        EXPECT_FALSE( is_unlocked );
    }
}

TEST_F( Task3, ItReportsLockedStatusWhenLocked )
{
    auto box = csc232::lock_box< int >( "password" );
    box.lock( );
    EXPECT_TRUE( box.is_locked( ) );
}

#else
TEST( Task3, ItIsNotReady )
{
    std::cerr << "Task 3 is not ready for evaluation; please toggle the TEST_TASK1 macro to TRUE\n";
    SUCCEED( );
}
#endif // TEST_TASK_3

// -----------------------------------------------------------------------------
// Helper: Print task-by-task summary and compute score
// -----------------------------------------------------------------------------
struct SuiteSummary
{
    std::string name;
    int passed = 0;
    int failed = 0;
    int disabled = 0;
    int total = 0;
    double percent = 0.0; // passing percentage among executed tests (pass+fail)
};

static void PrintPerTaskSummaryAndScore( )
{
    using testing::TestSuite;
    using testing::UnitTest;

    const UnitTest *unitTest = UnitTest::GetInstance( );

    // Aggregate per suite (fixture) results
    std::vector< SuiteSummary > summaries;
    int overall_passed = 0;
    int overall_failed = 0;

    for ( int i = 0; i < unitTest->total_test_suite_count( ); ++i )
    {
        const TestSuite *suite = unitTest->GetTestSuite( i );
        // Only include suites that correspond to our tasks.
        // (Optional) You can filter by name prefix "Task" if needed.
        SuiteSummary suiteSummary;
        suiteSummary.name = suite->name( );
        suiteSummary.passed = suite->successful_test_count( );
        suiteSummary.failed = suite->failed_test_count( );
        suiteSummary.disabled = suite->disabled_test_count( );
        suiteSummary.total = suite->total_test_count( );
        const int executed = suiteSummary.passed + suiteSummary.failed;
        suiteSummary.percent = ( executed > 0 ) ? ( 100.0 * suiteSummary.passed / executed ) : 0.0;

        summaries.push_back( suiteSummary );
        overall_passed += suiteSummary.passed;
        overall_failed += suiteSummary.failed;
    }

    const int overall_executed = overall_passed + overall_failed;
    const double overall_percent = ( overall_executed > 0 )
                                       ? ( 100.0 * static_cast< double >( overall_passed ) / overall_executed )
                                       : 0.0;

    // Pretty print
    std::cout << "\n========== Assignment Task Results ==========\n";
    for ( const auto &suiteSummary : summaries )
    {
        // Recommend naming fixtures exactly "Task1", "Task2", "Task3"
        if ( suiteSummary.name == "Task1" || suiteSummary.name == "Task2" || suiteSummary.name == "Task3" )
        {
            std::cout << "Task: " << suiteSummary.name << "\n"
                      << "  Passing: " << suiteSummary.passed << "\n"
                      << "  Failing: " << suiteSummary.failed << "\n"
                      << "  Disabled: " << suiteSummary.disabled << "\n"
                      << "  Total (compiled): " << suiteSummary.total << "\n"
                      << "  Score (% passing among executed): "
                      << std::fixed << std::setprecision( 1 ) << suiteSummary.percent << "%\n\n";
        }
    }

    std::cout << "-------------- Overall Summary --------------\n"
              << "Passing: " << overall_passed << "\n"
              << "Failing: " << overall_failed << "\n"
              << "Executed: " << overall_executed << "\n"
              << "Overall Score: " << std::fixed << std::setprecision( 1 )
              << overall_percent << "%\n"
              << "=============================================\n\n";
}

// -----------------------------------------------------------------------------
// Custom main (do NOT link gtest_main)
// -----------------------------------------------------------------------------
auto main( int argc, char **argv ) -> int
{
    ::testing::InitGoogleTest( &argc, argv );
    const int gtest_return = RUN_ALL_TESTS( );

    // After tests run, compute/print summaries & score
    PrintPerTaskSummaryAndScore( );

    // Return gtest's status (0 means all tests passed)
    return gtest_return;
}
