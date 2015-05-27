#include "stdafx.h"

#include "MuscleReflex.h"
#include "../sim/Muscle.h"

namespace scone
{
	namespace cs
	{
		MuscleReflex::MuscleReflex( const PropNode& props, opt::ParamSet& par, sim::Model& model, sim::Actuator& target, sim::Sensor& source ) :
		Reflex( props, par, model, target, source )
		{
			INIT_FROM_PROP_PAR( props, par, length_gain, 0.0 );
			INIT_FROM_PROP_PAR( props, par, length_ofs, 1.0 );
			INIT_FROM_PROP_PAR( props, par, velocity_gain, 0.0 );
			INIT_FROM_PROP_PAR( props, par, force_gain, 0.0 );
		}

		MuscleReflex::~MuscleReflex()
		{
		}

		void MuscleReflex::ComputeControls( double timestamp )
		{
			// add stretch reflex
			Real u_l = length_gain * std::max( 0.0, m_DelayedSource.GetSensorValue( sim::Muscle::MuscleLengthSensor, delay ) - length_ofs );

			// add velocity reflex
			// TODO: should velocity gain be positive only?
			Real u_v = velocity_gain * std::max( 0.0, m_DelayedSource.GetSensorValue( sim::Muscle::MuscleVelocitySensor, delay ) );

			// add force reflex
			Real u_f = force_gain * m_DelayedSource.GetSensorValue( sim::Muscle::MuscleForceSensor, delay );

			m_Target.AddControlValue( u_l + u_v + u_f );
		}
	}
}