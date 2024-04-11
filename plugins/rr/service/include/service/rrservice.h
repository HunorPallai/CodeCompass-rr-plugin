#ifndef CC_SERVICE_RRSERVICE_H
#define CC_SERVICE_RRSERVICE_H

#include <string>

#include <odb/database.hxx>
#include <webserver/servercontext.h>

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

		void getMessage(std::string&, const std::string&) override;
	
	private:
		std::shared_ptr<odb::database> _db;
		std::shared_ptr<std::string> _datadir;
};

} //rr
} //service
} //cc

#endif //CC_SERVICE_RRSERVICE_H
