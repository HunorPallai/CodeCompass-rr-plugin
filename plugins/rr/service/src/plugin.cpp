#include <webserver/pluginhelper.h>

#include <service/rrservice.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"

extern "C"
{
	boost::program_options::options_description getOptions()
	{
		namespace po = boost::program_options;
		po::options_description description("RR Plugin");

		return description;
	}

	void registerPlugin(
		const cc::webserver::ServerContext& context_,
		cc::webserver::PluginHandler<cc::webserver::RequestHandler>* pluginHandler_)
	{
		cc::webserver::registerPluginSimple(
			context_,
			pluginHandler_,
			CODECOMPASS_SERVICE_FACTORY_WITH_CFG(RR, rr),
			"RRService");
	}
}
#pragma clang diagnostic pop
