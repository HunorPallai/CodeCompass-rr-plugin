#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <boost/regex.hpp>

#include <util/logutil.h>

#include <service/rrservice.h>

namespace cc
{
namespace service
{
namespace rr
{

RRServiceHandler::RRServiceHandler(
	std::shared_ptr<odb::database> db_,
	std::shared_ptr<std::string> datadir_,
	const cc::webserver::ServerContext& context_)
		:  _db(db_),
		   _datadir(datadir_) 
{
	ts.tv_sec = 0;
        ts.tv_nsec = 500 * 1000000;
}

RRServiceHandler::~RRServiceHandler() 
{
        close( r_pipe[1] );
        close( w_pipe[0] );
}

void RRServiceHandler::startDebugger( 
		std::string& return_)
{
        if ( pipe( r_pipe ) == -1 || pipe( w_pipe ) == -1 )
        {
                LOG(error) << "Failed to open pipes! Error: " << strerror( errno );
                return;
        }

        p_id = fork();

        if ( p_id == -1 )
        {
                LOG(error) << "Failed to start child process! Error: " << strerror( errno );
                return;
        }

        if ( p_id == 0 ) //Child process
        {
                close( r_pipe[ 1 ] );
                close( w_pipe[ 0 ] );

                if ( dup2( r_pipe[ 0 ], STDIN_FILENO ) == -1 || dup2( w_pipe[ 1 ], STDOUT_FILENO ) == -1 || dup2( w_pipe[ 1 ], STDERR_FILENO) == -1 )
                {
                        LOG(error) << "Failed to redirect file descriptors! Error: " << strerror( errno );
                        return;
                }

                int err = execlp( "rr", "rr", "replay", NULL );

                if ( err == -1 )
                {
                        LOG(error) << "Failed to execute rr replay! Error: " << strerror( errno );
                        return;
                }
        }
        else //Parent process
        {
                close( r_pipe[ 0 ] );
                close( w_pipe[ 1 ] );

                char message[ 4096 ];
                ssize_t read_count;
                                           
                sleep( 1 );

                read_count = read( w_pipe[ 0 ], message, sizeof( message ) );
        	if ( read_count == -1 )
       		{
        	        LOG(warning) << "Failed to read from pipe!";
	        }	
	 	
		boost::regex prompt_pattern( "\\(rr\\).*" );

		return_ = boost::regex_replace( std::string( message ), prompt_pattern, "" );
	}

}

void RRServiceHandler::getMessage(
		std::string& return_,
		const std::string& message_)
{
	char message[ 2048 ];
	ssize_t count;

	count = write( r_pipe[ 1 ], (message_ + "\n").c_str(), message_.length() + 1 );
	if ( count == -1 )
        {
                LOG(warning) << "Failed to write to pipe!";
        }

	nanosleep( &ts, &ts );
        
	count = read( w_pipe[ 0 ], message, sizeof( message ) );
	if ( count == -1 ) 
	{
		LOG(warning) << "Failed to read from pipe!";
	}
	
	boost::regex prompt_pattern( "\\(rr\\).*" );
	
	return_ = boost::regex_replace( std::string( message ), prompt_pattern, "" );
}

} //rr
} //service
} //cc
