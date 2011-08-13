///////////////////////////////////////////////////////////////////////
//                             Titres.h                              //
///////////////////////////////////////////////////////////////////////
//       Auteur: Adnan RIHAN (Max13) <Max13@virtual-info.info>       //
///////////////////////////////////////////////////////////////////////

#ifndef TITRES_H
#define TITRES_H

#include "conf.h"

class Titres
{
	private:
		QString filename;
		QMap<QString, QList<QString> > T_List;
		QMap<QString, QList<QString> >::iterator T_It;

	public:
		static bool DB_Existe(void);
		bool DB_Sauver(void);
		bool DB_Charger(void);

		bool Existe(QString);
		bool Creer(QString, int = 0);
		bool Modifier(QString, QString, int = 0);
		bool Supprimer(QString);

		int nb_titre(void);
		int nb_volume(QString);

		QMap<QString, QList<QString> > get_map(void);
		QStringList list_toQStringList(void);
		QList<QTreeWidgetItem *> list_toQList(void);
		QList<QString> * vlist(QString);
};

#endif
