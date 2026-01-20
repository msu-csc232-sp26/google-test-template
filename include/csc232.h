/**
 * @brief   Macros, libraries and definitions for use in csc232 assignments.
 * @file    csc232.h
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 *
 * @remarks CSC232 - Data Structures
 *          Missouri State University, Spring 2026
 */

#ifndef MSU_CSC232_H
#define MSU_CSC232_H

#define FALSE 0
#define TRUE 1

#define EXECUTE_PREAMBLE TRUE

#define TEST_TASK_1 FALSE // TODO:  Task 1 - Step 1: Toggle TEST_TASK_1 TO TRUE
#define TEST_TASK_2 FALSE // TODO:  Task 2 - Step 1: Toggle TEST_TASK_2 TO TRUE
#define TEST_TASK_3 FALSE // TODO:  Task 3 - Step 1: Toggle TEST_TASK_3 TO TRUE
#define TEST_TASK_4 FALSE // TODO:  Task 4 - Step 1: Toggle TEST_TASK_4 TO TRUE
#define TEST_TASK_5 FALSE // TODO:  Task 5 - Step 1: Toggle TEST_TASK_5 TO TRUE

#include "file_writer.h"
#include "stream_file_writer.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <utility>
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
 * Namespace to encapsulate course work in CSC232 - Data Structures.
 */
namespace csc232
{
    // Add any user-defined functions prescribed in your assignment below
    // TODO: Task 1
    inline auto get_current_date_time( ) -> std::string
    {
        // Erase this comment and implement me accordingly
        return std::string{ };
    }

    // TODO: Task 2
    inline auto log_error( const std::string &log_file_name, file_writer &log_file, const std::string &error_message ) -> void
    {
        // Erase this comment and implement me accordingly
    }
    // DO NOT Modify anything below this line
} // namespace csc232

#endif // MSU_CSC232_H
