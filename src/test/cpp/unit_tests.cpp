/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2026
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
#include "mock_file_writer.h"
#include "safe_deposit_box.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <iomanip>
#include <iostream>
#include <string>

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

TEST_F( Task1, ItCanGenerateTimestamps )
{
    // const std::regex timeStampRegex(R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})");
    // const std::string timestamp = get_current_date_time();
    // EXPECT_TRUE(std::regex_match(timestamp, timeStampRegex));

    const std::string timestamp = csc232::get_current_date_time( );

    // Parse the timestamp string
    std::stringstream timestampStringStream( timestamp );
    std::tm tm_struct = { }; // Initialize struct tm

    // Use std::get_time to parse the string into the tm structure
    timestampStringStream >> std::get_time( &tm_struct, "%Y-%m-%d %H:%M:%S" );

    // Check if parsing failed
    EXPECT_FALSE( timestampStringStream.fail( ) ) << "Failed to parse timestamp string: " << timestamp;

    // Validate the date and time values using mktime
    // mktime normalizes the date and time values.  If the input values were invalid,
    // mktime will adjust them to the nearest valid date/time.
    const time_t mktime_result = mktime( &tm_struct );

    // Check if mktime failed (returns -1 if it fails)
    EXPECT_NE( mktime_result, static_cast< time_t >( -1 ) ) << "Invalid date/time values in timestamp: " << timestamp;
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
TEST_F( Task2, ItCreatesLogErrorFile )
{
    csc232::mock_file_writer mock_log_file;
    const std::string log_file_name = "test_error.log";
    const std::string error_message = "This is a test error message.";

    // Set expectations:
    // It is expected that open will be called with the correct filename and append mode.
    EXPECT_CALL( mock_log_file, open( testing::Eq( log_file_name ), std::ios_base::app ) );

    // It is expected that write will be called with a string containing the error message.
    EXPECT_CALL( mock_log_file, write( ::testing::HasSubstr( error_message ) ) );

    // It is expected that close will be called.
    EXPECT_CALL( mock_log_file, close( ) );

    // It is expected that is_open will be called, and it returns true
    // to simulate a successful file opening.
    EXPECT_CALL( mock_log_file, is_open( ) ).WillOnce( ::testing::Return( true ) );

    // Call the function under test, injecting the mock object.
    csc232::log_error( log_file_name, mock_log_file, error_message );
}

TEST_F( Task2, ItWritesErrorMessageWhenFailsToCreateLogFile )
{
    csc232::mock_file_writer mock_log_file;
    const std::string log_file_name = "test_error.log";
    const std::string error_message = "This is a test error message that will not get logged!";

    // Set expectations:
    // It is expected that open will be called with the correct filename and append mode.
    EXPECT_CALL( mock_log_file, open( testing::Eq( log_file_name ), std::ios_base::app ) );
    // It is expected that is_open will be called, and it returns false
    // to simulate an unsuccessful file opening.
    EXPECT_CALL( mock_log_file, is_open( ) ).WillOnce( ::testing::Return( false ) );

    // Call the function under test, injecting the mock object.
    csc232::log_error( log_file_name, mock_log_file, error_message );
}
#else
TEST( Task2, ItIsNotReady )
{
    std::cerr << "Task 2 is not ready for evaluation; please toggle the TEST_TASK2 macro to TRUE\n";
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

// Helper alias for a concrete instantiation
using box_t = csc232::safe_deposit_box< int >;

// --- Positive (valid) cases ---

TEST_F( Task3, Constructor_AllRequirementsMet_MinBoundary_NoThrow )
{
    // Exactly length 3 with letter+digit+special
    EXPECT_NO_THROW( box_t{ std::string{ "a1!" } } );
}

TEST_F( Task3, Constructor_AllRequirementsMet_Typical_NoThrow )
{
    EXPECT_NO_THROW( box_t{ std::string{ "Password123!" } } );
    EXPECT_NO_THROW( box_t{ std::string{ "A0#" } } );
    EXPECT_NO_THROW( box_t{ std::string{ "x9@Something" } } );
    EXPECT_NO_THROW( box_t{ std::string{ "Hello2$" } } );
}

// --- Negative (invalid) cases ---

TEST_F( Task3, Constructor_Empty_ThrowsInvalidArgument )
{
    EXPECT_THROW( box_t{ "" }, std::invalid_argument );
}

TEST_F( Task3, Constructor_TooShort_ThrowsInvalidArgument )
{
    EXPECT_THROW( box_t{ "a" }, std::invalid_argument );
    EXPECT_THROW( box_t{ "a!" }, std::invalid_argument ); // length 2, even if categories present
}

TEST_F( Task3, Constructor_MissingLetter_ThrowsInvalidArgument )
{
    // Has digit + special but no letter
    EXPECT_THROW( box_t{ "123!" }, std::invalid_argument );
    EXPECT_THROW( box_t{ "9@#" }, std::invalid_argument );
}

TEST_F( Task3, Constructor_MissingDigit_ThrowsInvalidArgument )
{
    // Has letter + special but no digit
    EXPECT_THROW( box_t{ "abc!" }, std::invalid_argument );
    EXPECT_THROW( box_t{ "Z$%" }, std::invalid_argument );
}

TEST_F( Task3, Constructor_MissingSpecial_ThrowsInvalidArgument )
{
    // Has letter + digit but no special
    EXPECT_THROW( box_t{ "abc1" }, std::invalid_argument );
    EXPECT_THROW( box_t{ "A0b0" }, std::invalid_argument );
}

// --- Optional: If you want to verify *which* rule triggered (by message) ---
// Only include this if your implementation throws distinct messages.
// Adjust expected substrings to match your implementation exactly.

TEST_F( Task3, Constructor_Message_Checks_Empty )
{
    try
    {
        box_t{ "" };
        FAIL( ) << "Expected std::invalid_argument";
    }
    catch ( const std::invalid_argument &ex )
    {
        // Change substring to match your actual message
        EXPECT_NE( std::string{ ex.what( ) }.find( "must not be empty" ), std::string::npos );
    }
    catch ( ... )
    {
        FAIL( ) << "Expected std::invalid_argument";
    }
}

TEST_F( Task3, Constructor_Message_Checks_TooShort )
{
    try
    {
        box_t{ "ab" };
        FAIL( ) << "Expected std::invalid_argument";
    }
    catch ( const std::invalid_argument &ex )
    {
        EXPECT_NE( std::string{ ex.what( ) }.find( "at least 3" ), std::string::npos );
    }
    catch ( ... )
    {
        FAIL( ) << "Expected std::invalid_argument";
    }
}

TEST_F( Task3, Constructor_Message_Checks_MissingCategories )
{
    // Missing digit
    try
    {
        box_t{ "a!a" };
        FAIL( ) << "Expected std::invalid_argument";
    }
    catch ( const std::invalid_argument &ex )
    {
        EXPECT_NE( std::string{ ex.what( ) }.find( "digit" ), std::string::npos );
    }
    catch ( ... )
    {
        FAIL( ) << "Expected std::invalid_argument";
    }

    // Missing letter
    try
    {
        box_t{ "1!1" };
        FAIL( ) << "Expected std::invalid_argument";
    }
    catch ( const std::invalid_argument &ex )
    {
        EXPECT_NE( std::string{ ex.what( ) }.find( "letter" ), std::string::npos );
    }
    catch ( ... )
    {
        FAIL( ) << "Expected std::invalid_argument";
    }

    // Missing special
    try
    {
        box_t{ "a1a" };
        FAIL( ) << "Expected std::invalid_argument";
    }
    catch ( const std::invalid_argument &ex )
    {
        EXPECT_NE( std::string{ ex.what( ) }.find( "special" ), std::string::npos );
    }
    catch ( ... )
    {
        FAIL( ) << "Expected std::invalid_argument";
    }
}

#else
TEST( Task3, ItIsNotReady )
{
    std::cerr << "Task 3 is not ready for evaluation; please toggle the TEST_TASK3 macro to TRUE\n";
    SUCCEED( );
}
#endif // TEST_TASK_3

// -----------------------------------------------------------------------------
// Task 4 Fixture and Tests
// -----------------------------------------------------------------------------
#if TEST_TASK_4
class Task4 : public ::testing::Test
{
protected:
    void SetUp( ) override { }
    void TearDown( ) override { }
};

// --- Replace these with your real Task 3 unit tests ---
TEST_F( Task4, ItCanUnlockAnItem )
{
    auto *const box_ptr = new csc232::safe_deposit_box< std::string >( std::string{ "csc232!" } );
    auto const result = box_ptr->unlock( std::string{ "csc232!" } );
    EXPECT_TRUE( result );
}

#else
TEST( Task4, ItIsNotReady )
{
    std::cerr << "Task 4 is not ready for evaluation; please toggle the TEST_TASK4 macro to TRUE\n";
    SUCCEED( );
}
#endif // TEST_TASK_4

// -----------------------------------------------------------------------------
// Task 5 Fixture and Tests
// -----------------------------------------------------------------------------
#if TEST_TASK_5
class Task5 : public ::testing::Test
{
protected:
    void SetUp( ) override { }
    void TearDown( ) override { }
};

// --- Replace these with your real Task 3 unit tests ---

TEST_F( Task5, ItCanStoreAnItemTest )
{
    EXPECT_NO_FATAL_FAILURE( {
        const std::string expected{ "Task 4" };
        csc232::box< std::string > *box_ptr = new csc232::safe_deposit_box< std::string >( std::string{ "csc232!" } );
        const auto result = dynamic_cast< csc232::safe_deposit_box< std::string > * >( box_ptr )->unlock( std::string{ "csc232!" } );
        EXPECT_TRUE( result );
        box_ptr->set_item( expected );
        const std::string actual{ box_ptr->get_item( ) };
        EXPECT_STREQ( expected.c_str( ), actual.c_str( ) );
    } );
}
#else
TEST( Task5, ItIsNotReady )
{
    std::cerr << "Task 5 is not ready for evaluation; please toggle the TEST_TASK5 macro to TRUE\n";
    SUCCEED( );
}
#endif // TEST_TASK_5

// -----------------------------------------------------------------------------
// Helper: Print task-by-task summary and compute score
// -----------------------------------------------------------------------------
struct SuiteSummary
{
    std::string name; // e.g., "Task3"
    int passed = 0;
    int failed = 0;
    int disabled = 0;     // compiled but disabled (DISABLED_*)
    int skipped = 0;      // skipped at runtime (e.g., using GTEST_SKIP())
    int total = 0;        // total compiled tests for this suite bucket
    double percent = 0.0; // among executed (pass+fail)
};

static auto normalize_suite_name( std::string_view suite_name ) -> std::string
{
    // Parameterized/type-parameterized suites often look like:
    //   "Task3_InvalidPassword/Invalids"
    //   "Task3_TypeParam/0"
    // Death tests can append "/DeathTest" as well.
    // We strip everything after the first '/' for bucketing.
    const size_t slash = suite_name.find( '/' );
    std::string base = std::string{ suite_name.substr( 0, slash ) };

    // Optional: If your suite names are "Task3_Something", map to "Task3".
    // This makes all Task3_* fixtures appear under "Task3".
    if ( base.rfind( "Task", 0 ) == 0 )
    { // starts with "Task"
        // Extract the TaskN prefix (letters "Task" + digits)
        size_t pos = 4;
        while ( pos < base.size( ) && ( std::isdigit( static_cast< unsigned char >( base[ pos ] ) ) != 0 ) )
        {
            ++pos;
        }
        // If there were digits after "Task", trim the rest to just "Task<digits>"
        if ( pos > 4 )
        {
            base = base.substr( 0, pos );
        }
    }

    return base;
}

static auto starts_with_disabled( std::string_view s ) -> bool
{
    return s.rfind( "DISABLED_", 0 ) == 0; // prefix check
}

static void PrintPerTaskSummaryAndScore( )
{
    using testing::TestInfo;
    using testing::TestResult;
    using testing::TestSuite;
    using testing::UnitTest;

    const UnitTest *unit = UnitTest::GetInstance( );

    // Aggregate across all suites into task buckets (Task1..Task5)
    std::map< std::string, SuiteSummary > taskBuckets;

    // We’ll also accumulate a true global total
    int overall_passed = 0;
    int overall_failed = 0;
    int overall_skipped = 0;
    int overall_disabled = 0;
    int overall_total = 0;

    const int suite_count = unit->total_test_suite_count( );
    for ( int s = 0; s < suite_count; ++s )
    {
        const TestSuite *suite = unit->GetTestSuite( s );
        if ( suite == nullptr )
        {
            continue;
        }

        const std::string normalized = normalize_suite_name( suite->name( ) );

        // Only bucket those that look like your task suites, or include all if you prefer
        // Here we include Task1..Task5 explicitly; change as needed
        // if ( !( normalized == "Task1" || normalized == "Task2" || normalized == "Task3" ||
        //         normalized == "Task4" || normalized == "Task5" ) )
        // {
        //     continue; // ignore non-task suites, or remove this to include everything
        // }

        // Ensure bucket exists
        auto &bucket = taskBuckets[ normalized ];
        bucket.name = normalized;

        // Iterate individual tests (this includes parameterized instances)

        const int test_count = suite->total_test_count( );
        for ( int t = 0; t < test_count; ++t )
        {
            const testing::TestInfo *info = suite->GetTestInfo( t );
            if ( !info )
                continue;

            // Count as compiled for the bucket
            bucket.total++;
            overall_total++;

            // Detect disabled-by-name
            const bool name_says_disabled =
                starts_with_disabled( suite->name( ) ) || starts_with_disabled( info->name( ) );

            // If disabled-by-name and it didn't run, classify as disabled
            if ( name_says_disabled && !info->should_run( ) )
            {
                bucket.disabled++;
                overall_disabled++;
                continue;
            }

            // If filtered out by --gtest_filter (but not disabled), exclude from executed stats
            if ( !info->should_run( ) )
            {
                continue;
            }

            // From here on, the test ran; use its result
            const testing::TestResult *result = info->result( );
            if ( !result )
                continue; // defensive

            if ( result->Skipped( ) )
            {
                bucket.skipped++;
                overall_skipped++;
                continue;
            }

            if ( result->Passed( ) )
            {
                bucket.passed++;
                overall_passed++;
            }
            else if ( result->Failed( ) )
            {
                bucket.failed++;
                overall_failed++;
            }
            else
            {
                // Treat any other terminal state conservatively as failure
                bucket.failed++;
                overall_failed++;
            }
        }

        // const int test_count = suite->total_test_count( );
        // for ( int t = 0; t < test_count; ++t )
        // {
        //     const TestInfo *info = suite->GetTestInfo( t );
        //     if ( info == nullptr )
        //     {
        //         continue;
        //     }
        //
        //     // Count as total compiled for the bucket
        //     bucket.total++;
        //     overall_total++;
        //
        //     // Disabled tests are known at discovery time
        //     if ( info->is_disabled( ) )
        //     {
        //         bucket.disabled++;
        //         overall_disabled++;
        //         continue; // disabled tests are not executed
        //     }
        //
        //     // If the test was filtered out (should_run == false), skip it from executed stats
        //     if ( !info->should_run( ) )
        //     {
        //         // Not disabled, but filtered out by --gtest_filter; do not count in executed
        //         continue;
        //     }
        //
        //     const TestResult *result = info->result( );
        //     if ( !result )
        //     {
        //         // Defensive: should not happen, but don't crash
        //         continue;
        //     }
        //
        //     if ( result->Skipped( ) )
        //     {
        //         bucket.skipped++;
        //         overall_skipped++;
        //         continue;
        //     }
        //
        //     if ( result->Passed( ) )
        //     {
        //         bucket.passed++;
        //         overall_passed++;
        //     }
        //     else if ( result->Failed( ) )
        //     {
        //         bucket.failed++;
        //         overall_failed++;
        //     }
        //     else
        //     {
        //         // Neither passed nor failed nor skipped—can happen for aborted?
        //         // Treat as failed in conservative scoring, or ignore.
        //         bucket.failed++;
        //         overall_failed++;
        //     }
        // }
    }

    // Compute per-bucket percentages (executed = pass + fail)
    for ( auto &kv : taskBuckets )
    {
        auto &b = kv.second;
        const int executed = b.passed + b.failed;
        b.percent = ( executed > 0 ) ? ( 100.0 * static_cast< double >( b.passed ) / executed ) : 0.0;
    }

    const int overall_executed = overall_passed + overall_failed;
    const double overall_percent =
        ( overall_executed > 0 ) ? ( 100.0 * static_cast< double >( overall_passed ) / overall_executed ) : 0.0;

    // Pretty print
    std::cout << "\n========== Assignment Task Results ==========\n";
    for ( const auto &kv : taskBuckets )
    {
        const auto &s = kv.second;
        std::cout << "Task: " << s.name << "\n"
                  << "  Passing:  " << s.passed << "\n"
                  << "  Failing:  " << s.failed << "\n"
                  << "  Skipped:  " << s.skipped << "\n"
                  << "  Disabled: " << s.disabled << "\n"
                  << "  Total (compiled): " << s.total << "\n"
                  << "  Score (% passing among executed): "
                  << std::fixed << std::setprecision( 1 ) << s.percent << "%\n\n";
    }

    std::cout << "-------------- Overall Summary --------------\n"
              << "Passing:  " << overall_passed << "\n"
              << "Failing:  " << overall_failed << "\n"
              << "Skipped:  " << overall_skipped << "\n"
              << "Disabled: " << overall_disabled << "\n"
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
