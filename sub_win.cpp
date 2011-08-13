///////////////////////////////////////////////////////////////////////
//                            Sub_Win.cpp                            //
///////////////////////////////////////////////////////////////////////
//       Auteur: Adnan RIHAN (Max13) <Max13@virtual-info.info>       //
///////////////////////////////////////////////////////////////////////

#include "conf.h"

MangaSubW::MangaSubW(QWidget * parent, QString titre, QList<QString> * volumeList) : QWidget(parent)
{
	this->titre = titre;
	this->volumeList = volumeList;

	SubWidget = new QWidget(parent);
	SubGridLayout = new QGridLayout(SubWidget);
	SubVBoxLayout = new QVBoxLayout(SubWidget);
	SubList = new QListWidget(SubWidget);
	buttonGroup = new QButtonGroup(SubWidget);
	availableRadio = new QRadioButton(ETAT[0], SubWidget);
	borrowedRadio = new QRadioButton(ETAT[1], SubWidget);
	missingRadio = new QRadioButton(ETAT[2], SubWidget);

	int num;
	bool ok;
	QString str;

	SubWidget->setAttribute(Qt::WA_DeleteOnClose, true);
	SubWidget->setWindowIcon(qApp->windowIcon());
	SubWidget->setWindowTitle(titre);
	SubWidget->setWindowModality(Qt::ApplicationModal);
	SubWidget->setMinimumSize(400, 200);

	SubList->setSelectionBehavior(QAbstractItemView::SelectRows);
	SubList->setSelectionMode(QAbstractItemView::ExtendedSelection);
	for (int i=0;i<volumeList->size();i++)
	{
		str = volumeList->value(i);
		num = str.toInt(&ok);
		if (ok)
			str = ETAT[num];

		stateList << "Vol "+QString::number(i+1)+": "+str;
	}
	SubList->addItems(stateList);

	availableRadio->setEnabled(false);
	borrowedRadio->setEnabled(false);
	missingRadio->setEnabled(false);

	buttonGroup->addButton(availableRadio, 0);
	buttonGroup->addButton(borrowedRadio, 1);
	buttonGroup->addButton(missingRadio, 2);

	SubVBoxLayout->addWidget(availableRadio);
	SubVBoxLayout->addWidget(borrowedRadio);
	SubVBoxLayout->addWidget(missingRadio);

	SubGridLayout->addWidget(SubList, 0, 0);
	SubGridLayout->addLayout(SubVBoxLayout, 0, 1);

	SubWidget->setLayout(SubGridLayout);
	SubWidget->show();

	connect(SubList, SIGNAL(itemSelectionChanged()), this, SLOT(volumeSelectionChanged()));
	connect(buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(radioClicked(QAbstractButton*)));
}

void MangaSubW::volumeSelectionChanged(void)
{
	selectedItems = SubList->selectedItems();

	if (selectedItems.size() == 1)
	{
		int currentRow = SubList->row(selectedItems[0]);

		availableRadio->setEnabled(true);
		borrowedRadio->setEnabled(true);
		missingRadio->setEnabled(true);

		if (volumeList->value(currentRow) == QString::number(0))
			availableRadio->setChecked(true);
		else if (volumeList->value(currentRow) == QString::number(1))
			borrowedRadio->setChecked(true);
		else if (volumeList->value(currentRow) == QString::number(2))
			missingRadio->setChecked(true);
		else
			borrowedRadio->setChecked(true);
	}
	else
	{
		availableRadio->setChecked(false);
		borrowedRadio->setChecked(false);
		missingRadio->setChecked(false);
	}
}

void MangaSubW::radioClicked(QAbstractButton * button)
{
	int currentRow;
	QListWidgetItem * currentItem;

	if (button->text() == ETAT[0]) // Dispo
	{
		for (int i=0;i<selectedItems.size();i++)
		{
			currentItem = selectedItems[i];
			currentRow = SubList->row(currentItem);
			currentItem->setText("Vol "+QString::number(currentRow+1)+": "+ETAT[0]);
			volumeList->replace(currentRow, QString::number(0));
		}

	}
	else if (button->text() == ETAT[1]) // Prêt
	{
		bool ok;
		QString borrowedTo = QInputDialog::getText(this, "Prêté ?", "A qui avez-vous prêté ce(s) volume(s) ?", QLineEdit::Normal, "", &ok);

		if (!ok)
			return;
		else if (borrowedTo.isEmpty())
			borrowedTo = ETAT[1];

		for (int i=0;i<selectedItems.size();i++)
		{
			currentItem = selectedItems[i];
			currentRow = SubList->row(currentItem);
			currentItem->setText("Vol "+QString::number(currentRow+1)+": "+borrowedTo);
			volumeList->replace(currentRow, borrowedTo);
		}
	}
	else if (button->text() == ETAT[2]) // Manquant
	{
		for (int i=0;i<selectedItems.size();i++)
		{
			currentItem = selectedItems[i];
			currentRow = SubList->row(currentItem);
			currentItem->setText("Vol "+QString::number(currentRow+1)+": "+ETAT[2]);
			volumeList->replace(currentRow, QString::number(2));
		}
	}
}

QWidget * MangaSubW::widget(void)
{
	return SubWidget;
}
