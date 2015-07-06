#include "mainwindow.hpp"
#include "ui_mainwindow.h"

DialogInfo* MainWindow::info = nullptr;

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow)
{
	QSettings INI("ustawienia.ini", QSettings::IniFormat);

	if (info) qFatal("Ta klasa ma być singletonem!");
	else info = new DialogInfo(this);

	ui->setupUi(this);

	INI.beginGroup("Program");

	Widgetsfile = INI.value("list", QDir::homePath() + QDir::separator() + "wpisy.ini").toString();

	INI.endGroup();

	connect(dialog = new DialogOptions(this),
		   SIGNAL(onDialogAccept(const QString&)),
		   SLOT(insertWidget(const QString&)));

	loadWidgets();
}

MainWindow::~MainWindow()
{
	if (Changed && QMessageBox::question(
		    this, "Zapis pliku",
		    "Czy chcesz zapisać zmiany w konfiguracji?",
		    QMessageBox::Yes | QMessageBox::No
		    ) == QMessageBox::Yes) saveWidgets();

	delete ui;
}

void MainWindow::saveWidgets(void) const
{
	QFile::remove(Widgetsfile);

	QSettings INI(Widgetsfile, QSettings::IniFormat);

	for (int i = 0; i < ui->layoutButtons->count(); i++)
	{
		const ButtonWidget* button = qobject_cast<const ButtonWidget*>(ui->layoutButtons->itemAt(i)->widget());

		if (button)
		{
			INI.beginGroup(QString::number(button->getID()));

			INI.setValue("data", button->getText());

			INI.endGroup();
		}
	}
}

void MainWindow::loadWidgets(void)
{
	QSettings INI(Widgetsfile, QSettings::IniFormat);

	for (auto* widget: ui->layoutButtons->children()) delete qobject_cast<ButtonWidget*>(widget);

	for (const auto& group: INI.childGroups())
	{
		INI.beginGroup(group);

		createWidget(INI.value("data", "Tekst...").toString(), group.toUInt());

		INI.endGroup();


	}
}

bool MainWindow::setPath(void)
{
	const QString tmp = QFileDialog::getOpenFileName(
						this, "Otwórz plik",
						QDir::homePath(),
						"Pliki konfiguracyjne (*.ini)");

	if (tmp.isEmpty()) return false;
	else Widgetsfile = tmp;

	QSettings INI("ustawienia.ini", QSettings::IniFormat);

	INI.beginGroup("Program");

	INI.setValue("list", Widgetsfile);

	INI.endGroup();

	return true;
}

void MainWindow::createWidget(const QString& Text, unsigned UUID)
{
	ButtonWidget* b = new ButtonWidget(this, UUID);

	b->updateText(Text);

	connect(b,
		   SIGNAL(onDelete(unsigned)),
		   SLOT(removeWidget(unsigned)));

	connect(b,
		   SIGNAL(onChange(const QString&)),
		   SLOT(enableSave(const QString&)));

	ui->layoutButtons->addWidget(b);
}

void MainWindow::insertWidget(const QString& Text)
{
	createWidget(Text, time(nullptr));

	Changed = true;
}

void MainWindow::removeWidget(unsigned UUID)
{
	QSettings INI(Widgetsfile, QSettings::IniFormat);

	INI.remove(QString::number(UUID));

	Changed = true;
}

void MainWindow::addWidget(void)
{
	dialog->open();
	dialog->setFocus();
}

void MainWindow::loadFromFile(void)
{
	if (setPath()) loadWidgets();
}

void MainWindow::saveToFile(void)
{
	if (setPath()) saveWidgets();
}

void MainWindow::showAbout(void)
{
	info->show();
	info->setFocus();
}

void MainWindow::enableSave(const QString&)
{
	Changed = true;
}
