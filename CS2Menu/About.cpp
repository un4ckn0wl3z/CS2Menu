#include "About.h"
#include <QMediaPlayer>
#include <QAudioOutput>

About::About(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::AboutClass())
{
	ui->setupUi(this);
	QMediaPlayer* player = new QMediaPlayer(this);
	QAudioOutput* audioOutput = new QAudioOutput(this);
	player->setAudioOutput(audioOutput);
	player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/chipi_chipi.mp3"));
	audioOutput->setVolume(0.2);
	player->play();
}

About::~About()
{
	delete ui;
}
