/*
 *
 *  Copyright (c) 2012-2015
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

#ifndef KEYDIALOG_H
#define KEYDIALOG_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QMenu>
#include <QLabel>

class QCloseEvent ;
class QAction ;
class QTableWidgetItem ;
class QTableWidget ;

#include "sirikali.h"
#include "volumeinfo.h"
#include "utility.h"
#include "siritask.h"
#include "can_build_pwquality.h"
#include "secrets.h"
#include "engines.h"
#include "walletconfig.h"

#include "favorites.h"

#include <functional>
#include <memory>
#include <vector>

class cryfsWarning : public QObject
{
	Q_OBJECT
public:
	cryfsWarning()
	{
		connect( &m_timer,&QTimer::timeout,[ this ](){

			this->update() ;
		} ) ;
	}
	void setWarningLabel( QLabel * l )
	{
		m_label = l ;
		m_label->setVisible( false ) ;
	}
	void showCreate( const QString& engine )
	{
		m_warning = tr( "Please be patient because creating a CryFS volume may take a very long time.\n\n" ) ;
		this->show( engine ) ;
	}
	void showUnlock( const QString& engine )
	{
		m_warning = tr( "Please be patient because unlocking a CryFS volume may take a very long time.\n\n" ) ;
		this->show( engine ) ;
	}
	void hide()
	{
		m_timer.stop() ;
		m_time = 0 ;
		m_label->setVisible( false ) ;
		m_label->setText( m_warning + tr( "Elapsed time: 0 seconds" ) ) ;
	}
private:
	void show( const QString& engine )
	{
		if( engine == "cryfs" ){

			static bool displayWarning = utility::backendIsGreaterOrEqualTo( engine,"0.10.0" ).await().value() ;

			if( displayWarning ){

				m_label->setVisible( true ) ;
				m_timer.start( 1000 * 1 ) ;
				this->update() ;
			}
		}
	}
	void update()
	{
		QString e ;
		if( m_time >= 60 ){

			e = tr( "Elapsed time: %0 minutes" ).arg( QString::number( m_time / 60,'f',2 ) ) ;
		}else{
			e = tr( "Elapsed time: %0 seconds" ).arg( QString::number( m_time ) ) ;
		}

		m_time++ ;

		m_label->setText( m_warning + e ) ;
	}
private:
	QLabel * m_label ;
	QTimer m_timer ;
	double m_time = 0 ;
	QString m_warning ;
};

#if BUILD_PWQUALITY
class keystrength
{
public:
	keystrength() : m_handle( pwquality_default_settings() )
	{
	}
	~keystrength()
	{
		pwquality_free_settings( m_handle ) ;
	}
	int quality( const QString& e )
	{
		return pwquality_check( m_handle,e.toLatin1().constData(),
					nullptr,nullptr,nullptr ) ;
	}
	operator bool()
	{
		return true ;
	}
private:
	pwquality_settings_t * m_handle ;
};
#else
class keystrength
{
public:
	keystrength()
	{
	}
	~keystrength()
	{
	}
	int quality( const QString& e )
	{
		Q_UNUSED( e ) ;
		return 0 ;
	}
	operator bool()
	{
		return false ;
	}
private:
};
#endif

namespace Ui {
class keyDialog;
}

class keyDialog : public QDialog
{
	Q_OBJECT
public:
	static QString keyFileError() ;

	static void instance( QWidget * parent,
			      secrets& s,
			      const volumeInfo& v,
			      std::function< void() > cancel,
			      bool o,
			      const QString& m,
			      const QString& exe = QString(),
			      const QByteArray& key = QByteArray() )
	{
		new keyDialog( parent,s,v,std::move( cancel ),o,m,exe,key ) ;
	}
	static void instance( QWidget * parent,
			      secrets& s,
			      bool o,
			      const QString& m,
			      favorites::volumeList e,
			      std::function< void() > function )
	{
		new keyDialog( parent,s,o,m,std::move( e ),std::move( function ) ) ;
	}
	keyDialog( QWidget * parent,
		   secrets&,
		   bool,
		   const QString&,
		   favorites::volumeList,
		   std::function< void() > ) ;
	keyDialog( QWidget * parent,
		   secrets&,
		   const volumeInfo&,
		   std::function< void() >,
		   bool,
		   const QString&,
		   const QString&,
		   const QByteArray& ) ;
	~keyDialog() ;
signals:
	void mounted( QString ) ;
	void cryptoOpen( QString ) ;
private slots:
	void cbVisibleKeyStateChanged( int ) ;
	void textChanged( QString ) ;
	void passWordTextChanged( QString ) ;
	void cbActicated( QString ) ;
	void pbOptions( void ) ;
	void pbkeyOption( void ) ;
	void pbMountPointPath( void ) ;
	void pbFolderPath( void ) ;
	void pbOK( void ) ;
	void plugIn( void ) ;
	void key( void ) ;
	void keyFile( void ) ;
	void HMACKeyFile( void ) ;
	void pbOpen( void ) ;
	void pbCancel( void ) ;
	void KeyFile( void ) ;
	void cbMountReadOnlyStateChanged( int ) ;
	void encryptedFolderMount( void ) ;
	void encryptedFolderCreate( void ) ;
	void pbSetKeyKeyFile( void ) ;
	void pbSetKey( void ) ;
	void pbSetKeyCancel( void ) ;
private :	
	void unlockVolume( void ) ;
	void setVolumeToUnlock() ;
	void setUpVolumeProperties( const volumeInfo& e,const QByteArray& ) ;
	void setUpInitUI() ;
	void setKeyEnabled( bool ) ;
	void setDefaultUI( void ) ;
	void SetUISetKey( bool ) ;
	void ShowUI( void ) ;
	void HideUI( void ) ;
	void setKeyInWallet() ;
	void setKeyInWallet( const QString& volumeType,const QString& title ) ;
	void showErrorMessage( const engines::engine::cmdStatus& ) ;
	void showErrorMessage( const QString& ) ;
	void reportErrorMessage( const engines::engine::cmdStatus& ) ;
	void openMountPoint( const QString& ) ;

	void setUIVisible( bool ) ;
	void keyAndKeyFile( void ) ;
	void openVolume( void ) ;
	void enableAll( void ) ;
	void disableAll( void ) ;
	void windowSetTitle( const QString& = QString() ) ;
	void closeEvent( QCloseEvent * ) ;

	bool upgradingFileSystem( void ) ;
	bool mountedAll() ;
	bool completed( const engines::engine::cmdStatus&,const QString& m ) ;
	bool eventFilter( QObject * watched,QEvent * event ) ;

	bool keySelected( int ) ;

	Ui::keyDialog * m_ui ;

	QByteArray m_key ;

	QString m_walletType ;
	QString m_checkBoxOriginalText ;
	QString m_path ;
	QString m_deviceOffSet ;
	QString m_idleTimeOut ;
	QString m_configFile ;
	QString m_exe ;
	QString m_engineName ;
	QString m_mountOptions ;
	QString m_createOptions ;
	QString m_fileManagerOpen ;
	QStringList m_keyFiles ;

	bool m_autoOpenMountPoint ;
	bool m_working ;
	bool m_create ;
	bool m_reUseMountPoint ;
	bool m_checked = false ;
	bool m_hmac ;
	bool m_closeGUI = false ;
	bool m_reverseMode = false ;

	favorites::triState m_favoriteReadOnly ;
	secrets& m_secrets ;

	keystrength m_keyStrength ;

	typedef enum{ Key = 0,keyfile = 1,hmacKeyFile = 2,keyKeyFile = 3,Plugin = 4,yubikey = 5 } keyType ;

	keyType m_keyType ;

	QWidget * m_parentWidget ;

	std::function< void() > m_cancel = [](){} ;
	std::function< void() > m_done = [](){} ;

	favorites::volumeList m_volumes ;

	cryfsWarning m_cryfsWarning ;

	decltype( m_volumes.size() ) m_counter = 0 ;

	struct walletKey
	{
		walletKey( secrets& s ) : secret( s )
		{
		}
		secrets& secret ;
		QString id ;
		QString walletName ;
		QString appName ;
		LXQt::Wallet::BackEnd bk ;
		bool set = false ;

		void deleteKey()
		{
			if( set ){

				set = false ;

				auto s = secret.walletBk( bk ) ;

				s->setImage( QIcon( ":/sirikali" ) ) ;

				if( s->opened() ){

					walletconfig::deleteKey( s,id ) ;
				}else {
					if( s->open( walletName,appName ) ){

						walletconfig::deleteKey( s,id ) ;
					}
				}
			}
		}
	} m_walletKey;
};

#endif // KEYDIALOG_H
