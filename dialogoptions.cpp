#include "dialogoptions.hpp"
#include "ui_dialogoptions.h"

DialogOptions::DialogOptions(QWidget* parent)
: QDialog(parent), ui(new Ui::DialogOptions)
{
	ui->setupUi(this);
}

DialogOptions::~DialogOptions(void)
{
	delete ui;
}

void DialogOptions::open(void)
{
	ButtonWidget* owner = qobject_cast<ButtonWidget*>(parent());

	if (owner) ui->editText->document()->setPlainText(owner->getText());
	else ui->editText->document()->setPlainText(QString());

	QDialog::open();
}

void DialogOptions::accept(void)
{
	if (ui->editText->document()->toPlainText().isEmpty())
	{
		QMessageBox::warning(this, "Błąd",
						 "Tekst nie może być pusty");
	}
	else
	{
		emit onDialogAccept(ui->editText->document()->toPlainText());

		QDialog::accept();
	}
}
