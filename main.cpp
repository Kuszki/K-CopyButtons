#include "mainwindow.hpp"

#include <QLibraryInfo>
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTranslator qtTranslator;
	qtTranslator.load("qt_" + QLocale::system().name(),
				   QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	a.installTranslator(&qtTranslator);

	QTranslator baseTranslator;
	baseTranslator.load("qtbase_" + QLocale::system().name(),
				   QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	a.installTranslator(&baseTranslator);

	QTranslator appTranslator;
	appTranslator.load("kcopybuttons_" + QLocale::system().name());
	a.installTranslator(&appTranslator);

	MainWindow w; w.show();

	return a.exec();
}
