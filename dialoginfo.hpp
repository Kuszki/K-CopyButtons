#ifndef DIALOGINFO_HPP
#define DIALOGINFO_HPP

#include <QDialog>

namespace Ui {
	class DialogInfo;
}

class DialogInfo : public QDialog
{
		Q_OBJECT

	public:
		explicit DialogInfo(QWidget *parent = 0);
		~DialogInfo();

	private:
		Ui::DialogInfo *ui;
};

#endif // DIALOGINFO_HPP
