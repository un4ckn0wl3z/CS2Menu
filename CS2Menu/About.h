#pragma once

#include <QDialog>
#include "ui_About.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AboutClass; };
QT_END_NAMESPACE

class About : public QDialog
{
	Q_OBJECT

public:
	About(QWidget *parent = nullptr);
	~About();

private:
	Ui::AboutClass *ui;
};
