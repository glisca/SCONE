#include "common.h"

#include "scone/opt/opt_tools.h"
#include "scone/cs/cs_tools.h"
#include "scone/sim/simbody/sim_simbody.h"

struct SconeGlobalFixture
{

    SconeGlobalFixture()
	{
		std::cout << "Initializing SCONE" << std::endl;

		scone::opt::RegisterFactoryTypes();
		scone::cs::RegisterFactoryTypes();
		scone::sim::RegisterSimbody();
	}

    ~SconeGlobalFixture()
	{
		std::cout << "Cleaning up SCONE" << std::endl;
	}
};

BOOST_GLOBAL_FIXTURE( SconeGlobalFixture );
