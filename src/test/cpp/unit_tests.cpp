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
#include "cell.h"
#include "csc232.h"
#include "memory_cell.h"

#include "gtest/gtest.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>

// -----------------------------------------------------------------------------
// Task 1 Fixture and Tests
// -----------------------------------------------------------------------------
#if TEST_TASK1
/**
 * Text fixture for task 1.
 */
class Task1TestFixture : public csc232::CSC232BaseTestFixture
{
};

TEST_F( Task1TestFixture, ItDeclaresReadMethod )
{
    // Using static_assert means that if student hasn't declared the read method properly,
    // this test target won't even compile.
    static_assert( csc232::HasReadMethod< int, csc232::cell< int > >,
                   "csc232::cell<T> must declare a method: T read() const" );
}

TEST_F( Task1TestFixture, ItDeclaresVirtualReadMethod )
{
    struct Derived : csc232::cell< int >
    {
        auto write( const int &value ) -> void override
        {
            // intentionally empty
        }
        [[nodiscard]] auto read( ) const -> int override
        {
            return 0;
        }
    };
    std::unique_ptr< csc232::cell< int > > base = std::make_unique< Derived >( );
    EXPECT_NO_THROW( {
        base->read( ); // If not virtual, this would not dispatch correctly
    } );
}

TEST_F( Task1TestFixture, ItDeclaresWriteMethod )
{
    // Using static_assert means that if student hasn't declared the read method properly,
    // this test target won't even compile.
    static_assert(csc232::HasWriteMethod< int, csc232::cell< int > >,
        "csc232::cell< T > must declare a method: void write( const T& )"
    );
}

TEST_F( Task1TestFixture, ItDeclaresVirtualWriteMethod )
{
    struct Derived : csc232::cell< int >
    {
        void write( const int &value ) override
        {
            // intentionally empty
        }
        [[nodiscard]] auto read( ) const -> int override
        {
            return 0;
        }
    };

    std::unique_ptr< csc232::cell< int > > base = std::make_unique< Derived >( );
    EXPECT_NO_THROW( {
        base->write( 42 ); // If not virtual, this would not dispatch correctly
    } );
}

#else
TEST( Task1TestFixture, ItIsNotReady )
{
    std::cerr << "Task 1 is not ready for evaluation; please toggle the TEST_TASK1 macro to TRUE\n";
    SUCCEED( );
}
#endif // TEST_TASK1

// -----------------------------------------------------------------------------
// Task 2 Fixture and Tests
// -----------------------------------------------------------------------------
#if TEST_TASK2
// NOLINTBEGIN(bugprone-easily-swappable-parameters)
auto contains_destructor( const std::string &fileContent, const std::string &className ) -> bool
{
    std::regex pattern( "~\\s*" + className + R"(\s*\(\s*\)\s*.*;)" );
    return std::regex_search( fileContent, pattern );
}

auto contains_method( const std::string &fileContent, const std::string &methodName ) -> bool
{
    // This regex matches a method declaration with optional return type, parameters, and qualifiers
    // std::regex pattern( R"(([\w:<>\s*&]+)?\s+)" + methodName + R"(\s*\([^;{)]*\)\s*(const)?\s*(override)?\s*(=\s*default)?\s*;)" );
    const std::string method_name = "write"; // or any method name (escape if necessary)

    // build pattern: optional leading return type OR optional trailing return type
    std::regex pattern(
        std::string(R"((?:([\w:<>\s*&]+)\s+)?)")    // optional leading return type
      + method_name
      + R"(\s*\([^;{)]*\)\s*)"                     // parameter list
        R"((?:->\s*([\w:<>\s*&:<>\s]+)\s*)?)"      // optional trailing return type
      + R"((?:const\b)?\s*(?:noexcept\b(?:\([^)]*\))?\s*)?(?:&{1,2})?\s*(?:override\b)?\s*(?:=\s*(?:default|0))?\s*;)"
    );
    return std::regex_search( fileContent, pattern );
}

auto contains_const_method( const std::string &fileContent, const std::string &methodName ) -> bool
{

    // This regex matches const-qualified member functions, including those with trailing return types
    std::regex pattern( R"((?:[\w:<>\s*&]+)?\s+)" + methodName +  // optional return type + method name
                        R"(\s*\([^;{)]*\)\s+const\s*)"            // parameter list and const
                        R"((?:->\s*[\w:<>\s*&]+)?\s*)"            // optional trailing return type
                        R"((?:override)?\s*(?:=\s*default)?\s*;)" // optional override and = default
    );
    return std::regex_search( fileContent, pattern );
}
// NOLINTEND(bugprone-easily-swappable-parameters)

auto readFile( const std::string &filePath ) -> std::string
{
    std::ifstream file( filePath );
    std::stringstream buffer;
    buffer << file.rdbuf( );
    return buffer.str( );
}

/**
 * Text fixture for task 2.
 */
class Task2TestFixture : public csc232::CSC232BaseTestFixture
{
};

TEST_F( Task2TestFixture, ItDeclaresDefaultConstructor )
{
    ASSERT_TRUE( is_method_declared_in_class( "memory_cell.h", "csc232", "memory_cell", "memory_cell" ) );
}

TEST_F( Task2TestFixture, ItDeclaresDestructor )
{
    std::string fileContent = readFile( "memory_cell.h" );
    ASSERT_TRUE( contains_destructor( fileContent, "memory_cell" ) ) << "Destructor not declared for class memory_cell";
}

TEST_F( Task2TestFixture, ItDeclaresReadMethod )
{
    std::string fileContent = readFile( "memory_cell.h" );
    ASSERT_TRUE( contains_const_method( fileContent, "read" ) );
}

TEST_F( Task2TestFixture, ItDeclaresWriteMethod )
{
    std::string fileContent = readFile( "memory_cell.h" );
    ASSERT_TRUE( contains_method( fileContent, "write" ) );
}

#else
TEST( Task2TestFixture, ItIsNotReady )
{
    std::cerr << "Task 2 is not ready for evaluation; please toggle the TEST_TASK2 macro to TRUE\n";
    SUCCEED( );
}
#endif // TEST_TASK2

// -----------------------------------------------------------------------------
// Task 3 Fixture and Tests
// -----------------------------------------------------------------------------
#if TEST_TASK3
/**
 * Text fixture for task 3.
 */
class Task3TestFixture : public csc232::CSC232BaseTestFixture
{
};

TEST_F( Task3TestFixture, ItCanCreateDefaultIntCell )
{
    auto cell = std::make_unique< csc232::memory_cell< int > >( );
    EXPECT_TRUE( cell->read( ) == int{ } );
}

TEST_F( Task3TestFixture, ItCanCreateDefaultDoubleCell )
{
    auto cell = std::make_unique< csc232::memory_cell< double > >( );
    EXPECT_TRUE( cell->read( ) == double{ } );
}

TEST_F( Task3TestFixture, ItCanReadAnUpdatedValue )
{
    auto const VALUE{ 42 };
    auto cell = std::make_unique< csc232::memory_cell< int > >( );
    cell->write( VALUE );
    EXPECT_TRUE( cell->read( ) == VALUE );
}
#else
TEST( Task3TestFixture, ItIsNotReady )
{
    std::cerr << "Task 3 is not ready for evaluation; please toggle the TEST_TASK3 macro to TRUE\n";
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
        // Recommend naming fixtures exactly "Task1TestFixture", "Task2TestFixture", "Task3TestFixture"
        if ( suiteSummary.name == "Task1TestFixture" || suiteSummary.name == "Task2TestFixture" || suiteSummary.name == "Task3TestFixture" || suiteSummary.name == "Task4TestFixture" || suiteSummary.name == "Task5TestFixture" )
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
