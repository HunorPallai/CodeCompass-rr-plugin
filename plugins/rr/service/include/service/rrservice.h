#ifndef CC_SERVICE_RRSERVICE_H
#define CC_SERVICE_RRSERVICE_H

#include <string>

#include <odb/database.hxx>
#include <webserver/servercontext.h>
#include "time.h"

#include <RRService.h>

namespace cc
{
namespace service
{
namespace rr 
{

class RRServiceHandler : virtual public RRServiceIf
{
	public:
		RRServiceHandler(
			std::shared_ptr<odb::database> db_,
			std::shared_ptr<std::string> datadir_,
			const cc::webserver::ServerContext& context_);

		~RRServiceHandler();

		void startDebugger(
				std::string& ) override;

		void getMessage(
				std::string&,
			       	const std::string& ) override;
	
	private:
		std::shared_ptr<odb::database> _db;
		std::shared_ptr<std::string> _datadir;
		int r_pipe[ 2 ], w_pipe[ 2 ];
		int p_id;
		struct timespec ts;	
};

} //rr
} //service
} //cc

#endif //CC_SERVICE_RRSERVICE_H
