///////////////////////////////////////////////////////////////////////
//                             music.h                               //
///////////////////////////////////////////////////////////////////////
//       Auteur: Adnan RIHAN (Max13) <Max13@virtual-info.info>       //
///////////////////////////////////////////////////////////////////////

#ifndef MUSIC_H
#define MUSIC_H

#include <QApplication>
#include <Phonon/AudioOutput>
#include <Phonon/MediaObject>
#include <QFile>
#include <QMessageBox>
#include <QString>

#ifdef __WIN32__
#define ARCH getenv("PROCESSOR_ARCHITECTURE")
#endif

class Music : public QObject
{
	Q_OBJECT

	private:
		Phonon::MediaObject * player;
		QFile * file;

	public:
		Music(QString);
		void play(void);

	public slots:
		void error(Phonon::State);
};

#endif // MUSIC_H
