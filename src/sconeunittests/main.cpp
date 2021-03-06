/*
** main.cpp
**
** Copyright (C) 2013-2019 Thomas Geijtenbeek and contributors. All rights reserved.
**
** This file is part of SCONE. For more information, see http://scone.software.
*/

#include "scone/sconelib_config.h"
#include "xo/serialization/serialize.h"
#include "xo/system/log_sink.h"
#include "xo/system/test_case.h"
#include "xo/serialization/prop_node_serializer_zml.h"
#include "scenario_test.h"
#include "xo/utility/arg_parser.h"
#ifdef SCONE_HYFYDY
#	include "proxy_string_test.h"
#endif

int main( int argc, const char* argv[] )
{
	xo::log::console_sink sink( xo::log::level::info );
	scone::Initialize();

	auto args = xo::arg_parser( argc, argv );
	if ( !args.has_flag( "skip-tutorials" ) )
		scone::add_scenario_tests( "scenarios/Tutorials" );
	if ( !args.has_flag( "skip-opensim3" ) )
		scone::add_scenario_tests( "scenarios/UnitTests/OpenSim3" );
#ifdef SCONE_HYFYDY
	if ( !args.has_flag( "skip-hyfydy" ) ) {
		scone::add_scenario_tests( "scenarios/UnitTests/Hyfydy" );
		xo::test::add_test_case( "proxy_string", &scone::proxy_string_test );
	}
#endif

	return xo::test::run_tests_async();
}
