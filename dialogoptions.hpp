#ifndef DIALOGOPTIONS_HPP
#define DIALOGOPTIONS_HPP

#include "buttonwidget.hpp"

#include <QMessageBox>
#include <QDialog>

namespace Ui
{
	class DialogOptions;
}

class DialogOptions : public QDialog
{

		Q_OBJECT

	public:

		explicit DialogOptions(QWidget* parent = nullptr);
		virtual ~DialogOptions(void) override;

		virtual void open(void) override;
		virtual void accept(void) override;

	private:

		Ui::DialogOptions* ui;

	signals:

		void onDialogAccept(const QString& Text);

};

#endif // DIALOGOPTIONS_HPP
