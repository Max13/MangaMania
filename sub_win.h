///////////////////////////////////////////////////////////////////////
//                            Sub_Win.h                              //
///////////////////////////////////////////////////////////////////////
//       Auteur: Adnan RIHAN (Max13) <Max13@virtual-info.info>       //
///////////////////////////////////////////////////////////////////////

#ifndef SUB_WIN_H
#define SUB_WIN_H

#include "conf.h"

class MangaSubW : public QWidget
{
	Q_OBJECT

	private:
		QWidget * SubWidget;
		QGridLayout * SubGridLayout;
		QVBoxLayout * SubVBoxLayout;
		QListWidget * SubList;
		QListWidgetItem * currentItem;
		QList<QListWidgetItem *> selectedItems;
		QList<QString> * volumeList;
		QButtonGroup * buttonGroup;
		QRadioButton * availableRadio;
		QRadioButton * borrowedRadio;
		QRadioButton * missingRadio;
		QString titre;
		QStringList stateList;


	signals:

	public slots:
		void volumeSelectionChanged(void);
		void radioClicked(QAbstractButton*);

	public:
		MangaSubW(QWidget *, QString, QList<QString> *);
		QWidget * widget(void);
};

#endif // SUB_WIN_H
