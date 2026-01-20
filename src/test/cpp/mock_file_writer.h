/**
 * @brief   Google Mock of the FileWriter interface.
 * @file    mock_file_writer.h
 * @authors Jim Daehn <jdaehn@missouristate.edu>
 * @remarks CSC232 - Data Structures
 *          Missouri State University, Spring 2026
 */

#ifndef MOCK_FILE_WRITER_H
#define MOCK_FILE_WRITER_H

#include "file_writer.h"
#include "gmock/gmock.h"

/**
 * Namespace to encapsulate course work in CSC232 - Data Structures.
 */
namespace csc232
{
    /**
     * Google Mock of the file_writer interface.
     */
    class mock_file_writer final : public file_writer
    {
    public:
        /**
         * Mock declaration of the open method inherited from the file_writer interface.
         */
        MOCK_METHOD( void, open, ( const std::string &filename, const std::ios_base::openmode &mode ), ( override ) ); // NOLINT

        /**
         * Mock declaration of the write method inherited from the file_writer interface.
         */
        MOCK_METHOD( void, write, ( const std::string &data ), ( override ) ); // NOLINT

        /**
         * Mock declaration of the close method inherited from the file_writer interface.
         */
        MOCK_METHOD( void, close, ( ), ( override ) ); // NOLINT

        /**
         * Mock declaration of the is_open method inherited from the file_writer interface.
         */
        MOCK_METHOD( bool, is_open, ( ), ( const, override ) ); // NOLINT
    };
}

#endif // MOCK_FILE_WRITER_H
