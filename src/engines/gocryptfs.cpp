/*
 *
 *  Copyright (c) 2018
 *  name : Francis Banyikwa
 *  email: mhogomchungu@gmail.com
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gocryptfs.h"
#include "commandOptions.h"

#include "gocryptfscreateoptions.h"

static engines::engine::BaseOptions _setOptions()
{
	engines::engine::BaseOptions s ;

	s.autoMountsOnCreate  = false ;
	s.hasGUICreateOptions = true ;
	s.setsCipherPath      = true ;

	s.configFileArgument  = "--config" ;

	s.configFileNames = QStringList{ "gocryptfs.conf",
					 ".gocryptfs.conf",
					 ".gocryptfs.reverse.conf",
					 "gocryptfs.reverse.conf" } ;

	s.fuseNames = QStringList{ "fuse.gocryptfs","fuse.gocryptfs-reverse" } ;

	s.names = QStringList{ "gocryptfs","gocryptfs.reverse" } ;

	s.notFoundCode = engines::engine::status::gocryptfsNotFound ;

	return s ;
}

gocryptfs::gocryptfs() : engines::engine( _setOptions() )
{
}

QString gocryptfs::command( const engines::engine::cmdArgsList& args ) const
{
	commandOptions m( args,this->name() ) ;

	auto exeOptions = m.exeOptions() ;

	exeOptions.add( "-q" ) ;

	if( args.opt.reverseMode ){

		exeOptions.add( "-reverse" ) ;
	}

	if( !args.opt.idleTimeout.isEmpty() ){

		exeOptions.addPair( "-idle",args.opt.idleTimeout ) ;
	}

	if( !args.configFilePath.isEmpty() ){

		exeOptions.add( args.configFilePath ) ;
	}

	if( args.create ){

		exeOptions.add( "--init",args.opt.createOptions ) ;

		QString e = "%1 %2 %3" ;

		return e.arg( args.exe,exeOptions.get(),args.cipherFolder ) ;
	}else{
		QString e = "%1 %2 %3 %4 %5" ;

		return e.arg( args.exe,
			      exeOptions.get(),
			      args.cipherFolder,
			      args.mountPoint,
			      m.fuseOpts().get() ) ;
	}
}

engines::engine::status gocryptfs::errorCode( const QString& e,int s ) const
{
	/*
	 * This error code was added in gocryptfs 1.2.1
	 */
	if( s == 12 ){

		return engines::engine::status::gocryptfsBadPassword ;

	}else if( e.contains( "password" ) ){

		return engines::engine::status::gocryptfsBadPassword ;
	}else{
		return engines::engine::status::backendFail ;
	}
}

QString gocryptfs::setPassword( const QString& e ) const
{
	return e ;
}

void gocryptfs::GUICreateOptionsinstance( QWidget * parent,engines::engine::function function ) const
{
	gocryptfscreateoptions::instance( parent,std::move( function ) ) ;
}
