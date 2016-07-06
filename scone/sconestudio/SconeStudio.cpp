#include "SconeStudio.h"
#include "scone/core/system_tools.h"
#include "scone/core/Log.h"

#include <osgDB/ReadFile>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    #include <QtWidgets/QFileSystemModel.h>
    #include <QtWidgets/QMessageBox.h>
#endif

using namespace scone;
using namespace std;

SconeStudio::SconeStudio(QWidget *parent, Qt::WindowFlags flags) :
QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

bool SconeStudio::init( osgViewer::ViewerBase::ThreadingModel threadingModel )
{
	// init file model and browser widget
	QString path = QString( scone::GetSconeFolder( "output" ).c_str() );
	m_pFileModel = new QFileSystemModel( this );
	QStringList filters( "*.par" );
	m_pFileModel->setNameFilters( filters );
	ui.browserView->setModel( m_pFileModel );
	ui.browserView->setRootIndex( m_pFileModel->setRootPath( path ) );
	ui.browserView->setColumnHidden( 1, true );
	ui.browserView->setColumnHidden( 2, true );
	ui.browserView->setColumnHidden( 3, true );
	ui.splitter->setSizes( QList< int >{ 100, 200 } );

	ui.osgViewer->setScene( manager.GetOsgRoot() );

	return true;
}

SconeStudio::~SconeStudio() {}

void SconeStudio::activateBrowserItem( QModelIndex idx )
{
	try
	{
		String filename = m_pFileModel->fileInfo( idx ).absoluteFilePath().toStdString();
		manager.CreateModel( filename );
		ui.horizontalScrollBar->setRange( 0, int( 1000 * manager.GetMaxTime() ) );
		ui.horizontalScrollBar->setValue( 0 );
	}
	catch ( std::exception& e )
	{
		QMessageBox::critical( this, "Exception", e.what() );
	}
}

void SconeStudio::updateScrollbar( int pos )
{
	TimeInSeconds t = double( pos ) / 1000;
	manager.Update( t );
	ui.lcdNumber->display( t );
}
