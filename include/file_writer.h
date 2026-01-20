/**
 * @brief     An interface for working with files.
 * @file      file_writer.h
 * @authors   Jim Daehn <jdaehn@missouristate.edu>
 *
 * @remarks CSC232 - Data Structures
 *          Missouri State University, Spring 2026
 */

#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include <ios>
#include <string>

/**
 * Namespace to encapsulate course work in CSC232 - Data Structures.
 */
namespace csc232
{
    /**
     * An interface for working with files.
     */
    class file_writer
    {
    public:
        /**
         * Default destructor.
         */
        virtual ~file_writer( ) = default;

        /**
         * Opens a file with the given file name with the given mode, e.g., append.
         * @param filename the name of the file to open
         * @param mode the mode by which to open the file
         */
        virtual void open( const std::string &filename, const std::ios_base::openmode &mode ) = 0;

        /**
         * Write the given data to a file.
         * @param data the data to be written to a file
         */
        virtual void write( const std::string &data ) = 0;

        /**
         * Close a file.
         */
        virtual void close( ) = 0;

        /**
         * Assess whether a file is open.
         * @return true if a file is open, false otherwise.
         */
        [[nodiscard]] virtual auto is_open( ) const -> bool = 0;
    };
}

#endif // FILE_WRITER_H
