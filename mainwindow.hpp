#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialoginfo.hpp"
#include "buttonwidget.hpp"
#include "dialogoptions.hpp"

#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>
#include <QDir>

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{

		Q_OBJECT

	protected:

		void saveWidgets(void) const;
		void loadWidgets(void);

		bool setPath(bool Action);

		void createWidget(const QString& Text, unsigned UUID);

	protected slots:

		void insertWidget(const QString& Text);

		void showTopmost(bool Topmost);

	public:

		explicit MainWindow(QWidget *parent = 0);
		virtual ~MainWindow(void) override;

	public slots:

		void removeWidget(unsigned UUID);

		void addWidget(void);

		void loadFromFile(void);
		void saveToFile(void);

		void showAbout(void);

		void enableSave(const QString&);

	private:

		static const QString defSetPath;
		static const QString defLstPath;

		Ui::MainWindow* ui;

		DialogInfo* info;
		DialogOptions* dialog;

		QString Widgetsfile;

		bool Changed = false;

};

#endif // MAINWINDOW_H
