#include "mainwindow.hpp"

#include <QLibraryInfo>
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv); MainWindow w;

	QTranslator qtTranslator;
	qtTranslator.load("qt_" + QLocale::system().name(),
				   QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	a.installTranslator(&qtTranslator);

	w.show();

	return a.exec();
}
