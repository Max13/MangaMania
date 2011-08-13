///////////////////////////////////////////////////////////////////////
//                              conf.h                               //
///////////////////////////////////////////////////////////////////////
//       Auteur: Adnan RIHAN (Max13) <Max13@virtual-info.info>       //
///////////////////////////////////////////////////////////////////////

#ifndef CONF_H
#define CONF_H

// Inclusions
//#include <cstdlib>
//#include <cstdio>
//#include <iostream>

#include <QtGui>

#include "main_win.h"
#include "music.h"
#include "sub_win.h"
#include "titres.h"
//---

// Constantes Char[]
#define APPNAME "MangaMania"
#define SAVENAME "MangaMania2.db"
#ifdef __WIN32__
	#define SAVEDIR QString(QString(getenv("APPDATA"))+"/"+APPNAME).toStdString().c_str()
	#define TMP getenv("TMP")
	#define CONVERTER "converter2.0_win.exe"
#elif defined(__MACH__)
	#define SAVEDIR QString(QDir::homePath()+"Library/Application Support"+"/"+APPNAME).toStdString().c_str()
	#define TMP "/tmp"
	#define CONVERTER "converter2.0_mac"
#elif defined(__linux__)
	#define SAVEDIR QString(QDir::homePath()+"/"+APPNAME).toStdString().c_str()
	#define TMP "/tmp"
	#define CONVERTER "converter2.0_linux"
#else
	#error "What is you OS ? =/"
#endif
const char ETAT[][11] = {"Disponible", "Emprunté", "Manquant"};
//---

// Constantes Int
#define DISPO 0
#define EMPR 1
#define MANQ 2
//---

#endif
