/**
 * @brief   A file writer that writes to the standard output file stream.
 * @file    stream_file_writer.h
 * @authors Jim Daehn <jdaehn@missouristate.edu>
 *
 * @remarks CSC232 - Data Structures
 *          Missouri State University, Spring 2026
 */

#ifndef OF_STREAM_FILE_WRITER_H
#define OF_STREAM_FILE_WRITER_H

#include "file_writer.h"
#include <fstream>
#include <string>

/**
 * Namespace to encapsulate course work in CSC232 - Data Structures.
 */
namespace csc232
{
    /**
     * A file writer that facilitates writing to standard output file streams.
     */
    class stream_file_writer final : public file_writer
    {
    public:
        /**
         * @copydoc file_writer::open
         */
        void open( const std::string &file_name, const std::ios_base::openmode &mode ) override;

        /**
         * @copydoc file_writer::write
         */
        void write( const std::string &data ) override;

        /**
         * @copydoc file_writer::close
         */
        void close( ) override;

        /**
         * @copydoc file_writer::is_open
         */
        [[nodiscard]] auto is_open( ) const -> bool override;

    private:
        std::ofstream file_stream_;
    };
}

#endif // OF_STREAM_FILE_WRITER_H
