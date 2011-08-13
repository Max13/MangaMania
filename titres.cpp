///////////////////////////////////////////////////////////////////////
//                            Titres.cpp                             //
///////////////////////////////////////////////////////////////////////
//       Auteur: Adnan RIHAN (Max13) <Max13@virtual-info.info>       //
///////////////////////////////////////////////////////////////////////

#include "conf.h"

bool Titres::DB_Existe(void)
{
	QFile file(SAVENAME);

	if (file.exists() && file.size() != 0)
		return true;
	else
		return false;
}

bool Titres::DB_Sauver(void)
{
	QFile file(SAVENAME);
	QDataStream in;

	if ( file.open(QIODevice::WriteOnly) )
	{
		in.setDevice(&file);
		in << T_List;

		file.close();
		return true;
	}
	else
		return false;
}

bool Titres::DB_Charger(void)
{
	QFile file(SAVENAME);
	QDataStream out;

	if ( file.open(QIODevice::ReadOnly) )
	{
		out.setDevice(&file);
		out >> T_List;

		file.close();
		return true;
	}
	else
		return false;
}

bool Titres::Existe(QString nom)
{
	T_It = this->T_List.find(nom);

	if ( T_It == this->T_List.end() )
		return false;
	else
		return true;
}

bool Titres::Creer(QString nom, int nb)
{
	QList<QString> V_List;
	for (int i=0;i<nb;i++)
		V_List.append(QString::number(DISPO));

	this->T_List.insert(nom, V_List);
	this->DB_Sauver();

	return true;
}

bool Titres::Modifier(QString nom, QString NouvNom, int NouvNb)
{
	if (!this->Existe(nom))
		return false;

	QList<QString> O_List = T_List.take(nom), N_List;

	for (int i=0;i<NouvNb;i++)
	{
		if (i < O_List.size())
			N_List << O_List[i];
		else
			N_List.append(QString::number(DISPO));
	}

	this->T_List.insert(NouvNom, N_List);
	this->DB_Sauver();

	return true;
}

bool Titres::Supprimer(QString nom)
{
	if ( !this->Existe(nom) )
		return false;

	this->T_List.remove(nom);
	this->DB_Sauver();

	return true;
}

int Titres::nb_titre(void)
{
	return T_List.size();
}

int Titres::nb_volume(QString titre)
{
	return T_List.value(titre).size();
}

QMap<QString, QList<QString> > Titres::get_map(void)
{
	return T_List;
}

QStringList Titres::list_toQStringList(void)
{
	QStringList liste;
	for (T_It=T_List.begin();T_It != T_List.end();T_It++)
		liste.append( T_It.key() );
	return liste;
}

QList<QTreeWidgetItem *> Titres::list_toQList(void)
{
	QStringList SListe;
	QList<QTreeWidgetItem *> TListe;
	for (T_It=T_List.begin();T_It != T_List.end();T_It++)
	{
		SListe.clear();
		SListe << T_It.key() << QString::number(this->nb_volume(T_It.key()));
		TListe.append(new QTreeWidgetItem(SListe, QTreeWidgetItem::Type));
	}
	return TListe;
}

QList<QString> * Titres::vlist(QString nom)
{
	QList<QString> * Liste;
	T_It = T_List.find(nom);
	//Liste = &*T_It;
	Liste = T_It.operator ->();
	return Liste;
}
