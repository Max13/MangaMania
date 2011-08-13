///////////////////////////////////////////////////////////////////////
//                            Main_Win.h                             //
///////////////////////////////////////////////////////////////////////
//       Auteur: Adnan RIHAN (Max13) <Max13@virtual-info.info>       //
///////////////////////////////////////////////////////////////////////

#ifndef MAIN_WIN_H
#define MAIN_WIN_H

#include "conf.h"
#include "titres.h"

class MangaSubW;

class MangaW : public QWidget // L'Objet sert lui-même de widget
{
	Q_OBJECT

	private:
		QGridLayout * MainLayout;
		QVBoxLayout * VBoxLayout;
		QTreeWidget * MainItemList;
		QList<QTreeWidgetItem *> ItemList;
		QTreeWidgetItem * CurrentItem;
		QPushButton * ListButton;
		QPushButton * AddButton;
		QPushButton * ModifyButton;
		QPushButton * DeleteButton;
		QStringList HeadLabels;
		Titres T;
		MangaSubW * SubWin;

	signals:

	public slots:
		void itemClicked(QTreeWidgetItem *);
		void itemDoubleClicked(QTreeWidgetItem *);
		void itemList(void);
		void addItem(void);
		void modifyItem(void);
		void deleteItem(void);
		void saveItem(void);
	
	public:
		MangaW(void);
		void LookingForDB(void);
		void FirstStart(void);
		void ClassicStart(void);
		void Update_ItemList(void);
};

#endif // MAIN_WIN_H