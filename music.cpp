///////////////////////////////////////////////////////////////////////
//                             Music.cpp                             //
///////////////////////////////////////////////////////////////////////
//       Auteur: Adnan RIHAN (Max13) <Max13@virtual-info.info>       //
///////////////////////////////////////////////////////////////////////

#include "music.h"

Music::Music(QString filename) : QObject()
{
	#ifdef __WIN32__
	QString libs;
	if (ARCH == QString("AMD64").toStdString().c_str())
		libs = QString(getenv("WINDIR"))+"/SysWOW64/QtPlugins";
	else
		libs = QString(getenv("WINDIR"))+"/system32/QtPlugins";
	qApp->addLibraryPath(libs);
	#endif

	file = new QFile(filename);
	player = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(file));

	connect(player, SIGNAL(stateChanged(Phonon::State, Phonon::State)), this, SLOT(error(Phonon::State)));
}

void Music::play(void)
{
	player->play();
}

void Music::error(Phonon::State newState)
{
	if (newState == Phonon::ErrorState)
		QMessageBox::warning(0, "Titre", player->errorString());
}
