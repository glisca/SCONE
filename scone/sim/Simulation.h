#pragma once

#include "sim.h"
#include "Model.h"
#include <memory>
#include "..\core\PropNode.h"

namespace scone
{
	namespace sim
	{
		class SCONE_SIM_API Simulation : public Propertyable
		{
		public:
			Simulation();
			virtual ~Simulation();
			virtual Model& AddModel( const String& filename );
			virtual Model& GetModel( size_t idx = 0 );
			virtual void ProcessProperties( const PropNode& props );

			virtual void AdvanceSimulationTo( double time ) = 0;

			double max_simulation_time;

		protected:
			virtual ModelUP CreateModel( const String& filename ) = 0;

		private:
			std::vector< ModelUP > m_Models;
			Simulation( const Simulation& );
			Simulation& operator=( const Simulation& );
		};
	}
}
