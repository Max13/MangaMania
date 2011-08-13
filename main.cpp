///////////////////////////////////////////////////////////////////////
//                             Main.cpp                              //
///////////////////////////////////////////////////////////////////////
//       Auteur: Adnan RIHAN (Max13) <Max13@virtual-info.info>       //
///////////////////////////////////////////////////////////////////////

#include "conf.h"

int main(int argc, char *argv[])
{
	// Création de l'application
	Q_INIT_RESOURCE(res);
	QApplication app(argc, argv);
	app.setApplicationName(APPNAME);
	app.setApplicationVersion("2.6");
	app.setOrganizationName("Max13");
	app.setWindowIcon(QIcon(":/img/png"));
	// ---

	// Création du répertoire de sauvegarde
	QDir * dir = new QDir;
	dir->mkpath(SAVEDIR);
	dir->setCurrent(SAVEDIR);
	// ---

	// Recherche des options
	if (argc > 1)
	{
		QList<QString> ArgList;
		for (int i=0;i<argc;i++)
			ArgList << argv[i];

		if (ArgList.contains("-reset"))
			dir->remove(SAVENAME);
		if (ArgList.contains("-dir"))
		{
			QString newpath(ArgList[ArgList.indexOf("-dir")+1]);
			if (!dir->mkpath(newpath) || !dir->setCurrent(newpath))
				return EXIT_FAILURE;
		}
		if (ArgList.contains("-noexec"))
			return EXIT_SUCCESS;
	}
	// ---

	// Implémentation du système de traduction
	QString locale = QLocale::system().name().section('_', 0, 0);
	QTranslator translator;
	translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	app.installTranslator(&translator);
	// ---

	// Convertisseur
	QFile::copy(QString(":/app/")+CONVERTER, CONVERTER);
	QFile::setPermissions(CONVERTER, QFile::ReadOther|QFile::WriteOther|QFile::ExeOther);

	QProcess * proc = new QProcess;
	proc->start(CONVERTER);
	proc->waitForFinished(10000);

	delete proc;
	QFile::remove(CONVERTER);
	// ---

	// Lecture de la musique de fond
	Music * sound = new Music(":/music/ambi");
	sound->play();
	// ---

	// Démarrage
	QMessageBox::information(0, "Bienvenue", "Bienvenue sur MangaMania+,\nun gestionnaire de bibliothèque,\npar Max13 ;)");

	MangaW * MainWidget = new MangaW;
	MainWidget->LookingForDB();
	// ---

  return app.exec();
}
