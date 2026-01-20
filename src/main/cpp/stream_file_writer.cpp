/**
 * @brief   An implementation of a file writer that writes to the standard output file stream.
 * @file    stream_file_writer.cpp
 * @authors Jim Daehn <jdaehn@missouristate.edu>
 * @brief   An implementation of a file writer that writes to the standard output file stream.
 *
 * @remarks CSC232 - Data Structures
 *          Missouri State University, Spring 2026
 */

#include "stream_file_writer.h"

namespace csc232
{
    void stream_file_writer::open( const std::string &file_name, const std::ios_base::openmode &mode )
    {
        file_stream_.open( file_name, mode );
    }

    void stream_file_writer::write( const std::string &data )
    {
        if ( file_stream_.is_open( ) )
        {
            file_stream_ << data;
        }
    }

    void stream_file_writer::close( )
    {
        if ( file_stream_.is_open( ) )
        {
            file_stream_.close( );
        }
    }

    auto stream_file_writer::is_open( ) const -> bool
    {
        return file_stream_.is_open( );
    }

}
