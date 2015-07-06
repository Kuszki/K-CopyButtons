#include "buttonwidget.hpp"
#include "ui_buttonwidget.h"

ButtonWidget::ButtonWidget(QWidget *parent, unsigned uuid)
: QWidget(parent), ID(uuid), ui(new Ui::ButtonWidget)
{
	ui->setupUi(this);

	connect(dialog = new DialogOptions(this),
		   SIGNAL(onDialogAccept(const QString&)),
		   SLOT(updateText(const QString&)));
}

ButtonWidget::~ButtonWidget()
{
	delete ui;
}

QString ButtonWidget::getText(void) const
{
	return ui->labelText->text();
}

unsigned ButtonWidget::getID(void) const
{
	return ID;
}

void ButtonWidget::updateText(const QString& Text)
{
	ui->labelText->setText(Text);

	emit onChange(Text);
}

void ButtonWidget::saveClipboard(void) const
{
	QApplication::clipboard()->setText(ui->labelText->text());
}

void ButtonWidget::deleteWidget(void)
{
	deleteLater();

	emit onDelete(ID);
}

void ButtonWidget::editText(void)
{
	dialog->open();
	dialog->setFocus();
}
