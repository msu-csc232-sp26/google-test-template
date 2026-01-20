/**
 * @brief   Entry-point for demo target.
 * @file    demo.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 *
 * @remarks CSC232 - Data Structures
 *          Missouri State University, Spring 2026
 */

#include "csc232.h"

auto main( ) -> int
{
    cout << "Demo: simulating an error..." << endl;
#if TEST_TASK_2
    csc232::stream_file_writer file_writer;
    csc232::log_error( "error.log", file_writer, "Can not open data file." );
#endif

    cout << "Demo: simulating another error..." << endl;
#if TEST_TASK_2
    csc232::log_error( "error.log", file_writer, "Network connection timed out during API call." );
#endif

    return EXIT_SUCCESS;
}
