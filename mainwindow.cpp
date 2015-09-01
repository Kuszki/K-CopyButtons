#include "mainwindow.hpp"
#include "ui_mainwindow.h"

const QString MainWindow::defSetPath = QDir::homePath() + QDir::separator() + ".kcopybuttons/settings.ini";
const QString MainWindow::defLstPath = QDir::homePath() + QDir::separator() + ".kcopybuttons/records.ini";

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow)
{
	Widgetsfile = QSettings(defSetPath, QSettings::IniFormat).value("list", defLstPath).toString();

	info = new DialogInfo(this);
	dialog = new DialogOptions(this);

	ui->setupUi(this);

	connect(dialog, &DialogOptions::onDialogAccept, this, &MainWindow::insertWidget);

	loadWidgets();
}

MainWindow::~MainWindow()
{
	if (Changed && QMessageBox::question(
		    this, tr("Config changed"),
		    tr("Do you want to save config file?"),
		    QMessageBox::Yes | QMessageBox::No
		    ) == QMessageBox::Yes) saveWidgets();

	delete ui;
}

void MainWindow::saveWidgets(void) const
{
	QFile::remove(Widgetsfile); QSettings INI(Widgetsfile, QSettings::IniFormat);

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
		createWidget(INI.value("data", "...").toString(), group.toUInt());
		INI.endGroup();
	}
}

bool MainWindow::setPath(bool Action)
{
	QString tmp = QString();

	if (Action) tmp = QFileDialog::getOpenFileName(
					   this, tr("Open file"),
					   QDir::homePath(),
					   tr("Config files (*.ini)"));
	else tmp = QFileDialog::getSaveFileName(
				 this, tr("Open file"),
				 QDir::homePath(),
				 tr("Config files (*.ini)"));

	if (tmp.isEmpty()) return false;
	else Widgetsfile = tmp;

	QSettings(defSetPath, QSettings::IniFormat).setValue("list", Widgetsfile);

	return true;
}

void MainWindow::createWidget(const QString& Text, unsigned UUID)
{
	ButtonWidget* b = new ButtonWidget(this, UUID);

	b->updateText(Text);

	connect(b, &ButtonWidget::onDelete, this, &MainWindow::removeWidget);
	connect(b, &ButtonWidget::onChange, this, &MainWindow::enableSave);

	ui->layoutButtons->addWidget(b);
}

void MainWindow::insertWidget(const QString& Text)
{
	createWidget(Text, time(nullptr));

	Changed = true;
}

void MainWindow::showTopmost(bool Topmost)
{
	if (Topmost) setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	else setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);

	show();
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
	if (setPath(true)) loadWidgets();
}

void MainWindow::saveToFile(void)
{
	if (setPath(false)) saveWidgets();
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
