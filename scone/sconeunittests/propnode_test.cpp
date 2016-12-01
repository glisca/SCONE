#include "common.h"

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

BOOST_AUTO_TEST_CASE( propnode_stream_test )
{
	path rootpath = scone::GetFolder( "root" ).str();
	path p1path = rootpath / "config/f1022_gait_GH.xml";
	auto p1 = scone::load_xml( p1path.string() );

	auto p2path = temp_directory_path() / p1path.filename();
	save_xml( p1, p2path.string() );
	
	auto p2 = scone::load_xml( p2path.string() );

	BOOST_CHECK( p1 == p2 );
}
