#include <iostream>

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
	std::cout << "RRServiceHandler object created!" << std::endl;
}

void RRServiceHandler::getMessage(std::string& return_,
				  const std::string& message_)
{
	std::cout << message_ << std::endl;
	return_ =  "Server: Hello World!\n";
}

} //rr
} //service
} //cc
