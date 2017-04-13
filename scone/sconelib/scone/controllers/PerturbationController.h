#pragma once

#include "scone/core/types.h"
#include "scone/model/Controller.h"
#include "scone/core/PropNode.h"
#include "scone/optimization/ParamSet.h"
#include "scone/core/Vec3.h"

namespace scone
{
	class SCONE_API PerturbationController : public Controller
	{
	public:
		PerturbationController( const PropNode& props, ParamSet& par, Model& model, const Area& target_area );
		virtual ~PerturbationController() {}

		String name;
		double force;
		TimeInSeconds interval;
		TimeInSeconds duration;
		TimeInSeconds start_time;

		virtual void StoreData( Storage<Real>::Frame& frame ) override;
		virtual UpdateResult UpdateControls( Model& model, double timestamp ) override;

	protected:
		virtual String GetClassSignature() const override;

	private:
		Vec3 current_force;
		Body& force_body;
	};
}