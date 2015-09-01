#include "buttonwidget.hpp"
#include "ui_buttonwidget.h"

ButtonWidget::ButtonWidget(QWidget *parent, unsigned uuid)
: QWidget(parent), ID(uuid), ui(new Ui::ButtonWidget)
{
	dialog = new DialogOptions(this);

	ui->setupUi(this);

	connect(dialog, &DialogOptions::onDialogAccept, this, &ButtonWidget::updateText);
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

void ButtonWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton
	    && ui->labelText->geometry().contains(event->pos()))
	{
		QDrag *drag = new QDrag(this);
		QMimeData *mimeData = new QMimeData;

		mimeData->setText(ui->labelText->text());

		drag->setMimeData(mimeData);
		drag->exec();
	}
}
