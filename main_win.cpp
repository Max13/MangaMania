///////////////////////////////////////////////////////////////////////
//                           Main_Win.cpp                            //
///////////////////////////////////////////////////////////////////////
//       Auteur: Adnan RIHAN (Max13) <Max13@virtual-info.info>       //
///////////////////////////////////////////////////////////////////////

#include "conf.h"

MangaW::MangaW(void) : QWidget()
{
	// Création du Widget + Elements
	HeadLabels << "Titre" << "Nb Volume";
}

void MangaW::LookingForDB(void)
{
	QWidget * loadingWidget = new QWidget;
	QVBoxLayout * loadingLayout = new QVBoxLayout; // Layout Vertical Box
	QLabel * loadingTexte = new QLabel("Restauration des sauvegardes"); // Label = Texte
	QProgressBar * loadingProgressBar = new QProgressBar; // Barre de progression
	
	loadingProgressBar->setRange(0, 0); // ProgressBar en "chargement indéfini"
	
	loadingLayout->addWidget(loadingTexte);
	loadingLayout->addWidget(loadingProgressBar);
	
	loadingWidget->setLayout(loadingLayout); // On ajoute le layout au Widget
	loadingWidget->show(); // On affiche le widget

	// On vérifie l'existance de la sauvegarde
	if ( T.DB_Existe() && T.DB_Charger() )
	{
		loadingWidget->close();
		this->ClassicStart();
	}
	else
	{
		loadingWidget->close();
		this->FirstStart();
	}
	// ---
}

void MangaW::FirstStart(void)
{
	bool ok;
	int FirstSerie_nb;
	QString FirstSerie;

	FirstSerie = QInputDialog::getText(this, "Première série", "Quel est le nom de la première série?", QLineEdit::Normal, "", &ok);

	if (!ok || FirstSerie.isEmpty())
		exit(0);
	
	FirstSerie_nb = QInputDialog::getInt(this, "Première série", "Combien de volumes avez-vous?", 1, 0, 100, 1, &ok);

	if (!ok)
		exit(0);

	T.Creer(FirstSerie, FirstSerie_nb);
	this->ClassicStart();
}

void MangaW::ClassicStart(void)
{
	MainLayout = new QGridLayout;
	VBoxLayout = new QVBoxLayout;
	MainItemList = new QTreeWidget;
	ListButton = new QPushButton("Liste des volumes");
	AddButton = new QPushButton("Ajouter une série");
	ModifyButton = new QPushButton("Modifier une série");
	DeleteButton = new QPushButton("Supprimer une série");

	this->setWindowIcon(qApp->windowIcon());
	this->setWindowTitle(qApp->applicationName());
	this->setMinimumSize(500, 250);

	ItemList = T.list_toQList();
	ListButton->setEnabled(false);
	ModifyButton->setEnabled(false);
	DeleteButton->setEnabled(false);

	MainItemList->setColumnCount(2);
	MainItemList->setHeaderLabels(HeadLabels);
	MainItemList->addTopLevelItems(ItemList);
	MainItemList->resizeColumnToContents(0);
    MainItemList->resizeColumnToContents(1);
    MainItemList->setSelectionBehavior(QAbstractItemView::SelectRows);

	VBoxLayout->addWidget(ListButton);
	VBoxLayout->addWidget(AddButton);
	VBoxLayout->addWidget(ModifyButton);
	VBoxLayout->addWidget(DeleteButton);
	MainLayout->addWidget(MainItemList, 0, 0);
	MainLayout->addLayout(VBoxLayout, 0, 1);

	this->setLayout(MainLayout);
	this->show();

	connect(MainItemList, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(itemClicked(QTreeWidgetItem *)));
	connect(MainItemList, SIGNAL(itemActivated(QTreeWidgetItem*,int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem*)));
	//connect(MainItemList, SIGNAL(itemSelectionChanged()));
	connect(ListButton, SIGNAL(clicked()), this, SLOT(itemList()));
	connect(AddButton, SIGNAL(clicked()), this, SLOT(addItem()));
	connect(ModifyButton, SIGNAL(clicked()), this, SLOT(modifyItem()));
	connect(DeleteButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
}

void MangaW::Update_ItemList(void)
{
	MainItemList->sortItems(0, Qt::AscendingOrder);
	MainItemList->resizeColumnToContents(0);
	MainItemList->resizeColumnToContents(1);
}
