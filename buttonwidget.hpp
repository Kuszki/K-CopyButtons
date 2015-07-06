#ifndef BUTTONWIDGET_HPP
#define BUTTONWIDGET_HPP

class DialogOptions;

#include "dialogoptions.hpp"

#include <QApplication>
#include <QClipboard>
#include <QWidget>

namespace Ui
{
	class ButtonWidget;
}

class ButtonWidget : public QWidget
{

		Q_OBJECT

	public:

		explicit ButtonWidget(QWidget* parent,
						  unsigned uuid);
		virtual ~ButtonWidget(void) override;

		QString getText(void) const;

		unsigned getID(void) const;

	public slots:

		void updateText(const QString& Text);

		void saveClipboard(void) const;

		void deleteWidget(void);

		void editText(void);

	private:

		const unsigned ID;

		Ui::ButtonWidget* ui;

		DialogOptions* dialog;

	signals:

		void onDelete(unsigned);

		void onChange(const QString&);

};

#endif // BUTTONWIDGET_HPP
