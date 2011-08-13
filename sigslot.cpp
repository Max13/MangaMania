///////////////////////////////////////////////////////////////////////
//                            SigSlot.cpp                            //
///////////////////////////////////////////////////////////////////////
//       Auteur: Adnan RIHAN (Max13) <Max13@virtual-info.info>       //
///////////////////////////////////////////////////////////////////////

#include "conf.h"

// Slots
void MangaW::itemClicked(QTreeWidgetItem * item)
{
	ListButton->setEnabled(true);
	ModifyButton->setEnabled(true);
	DeleteButton->setEnabled(true);
	
	CurrentItem = item;
}

void MangaW::itemDoubleClicked(QTreeWidgetItem * item)
{
	this->itemClicked(item);
	this->itemList();
}

void MangaW::itemList(void)
{
	SubWin = new MangaSubW(0, CurrentItem->text(0), T.vlist(CurrentItem->text(0)));
	QWidget * WidWid = SubWin->widget();
	connect(WidWid, SIGNAL(destroyed()), this, SLOT(saveItem()));
}

void MangaW::saveItem(void)
{
	T.DB_Sauver();
}
// /Slots

void MangaW::addItem(void)
{
	bool ok;
	int nb;
	QString titre;

	titre = QInputDialog::getText(this, "Nouvelle Série", "Quel est le titre de la nouvelle Série?", QLineEdit::Normal, "", &ok);

	if (!ok || titre.isEmpty())
		return;

	nb = QInputDialog::getInt(this, "Nouvelle Série", "Quel est le numéro du dernier volume?", 1, 0, 100, 1, &ok);

	if (!ok)
		return;

	if (T.Existe(titre.toLower()))
	{
		if (QMessageBox::question(0, "Ouups...", "<strong>"+titre+"</strong> existe déjà.\n\nRemplacer?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
			return;
	}

	T.Creer(titre, nb);

	QTreeWidgetItem * item = new QTreeWidgetItem;
	item->setText(0, titre);
	item->setText(1, QString::number(nb));
	MainItemList->addTopLevelItem(item);
	this->Update_ItemList();
}

void MangaW::modifyItem(void)
{
	bool ok;
	int nb = CurrentItem->text(1).toInt(&ok);
	QString titre = CurrentItem->text(0);

	titre = QInputDialog::getText(this, "Modification", "Quel est le nouveau titre de la Série?", QLineEdit::Normal, titre, &ok);

	if (!ok || titre.isEmpty())
		return;

	nb = QInputDialog::getInt(this, "Modification", "Quel est le numéro du dernier volume?", nb, 0, 100, 1, &ok);

	if (!ok)
		return;

	T.Modifier(CurrentItem->text(0), titre, nb);
	CurrentItem->setText(0, titre);
	CurrentItem->setText(1, QString::number(nb));
	this->Update_ItemList();
}

void MangaW::deleteItem(void)
{
	QString titre = CurrentItem->text(0);

	if (!T.Existe(titre))
		return;

	if (QMessageBox::question(0, "Attention", "Êtes-vous sûr de vouloir supprimer <strong>"+titre+"</strong> ?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
		return;

	T.Supprimer(titre);
	MainItemList->takeTopLevelItem(MainItemList->indexOfTopLevelItem(CurrentItem));
	this->Update_ItemList();
}
