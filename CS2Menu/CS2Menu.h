#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CS2Menu.h"
#include <Windows.h>
#include <QDebug>
#include <qtimer.h>

#include "Structures.h"
#include "Memory.h"
#include "ExWindow.h"
#include "AimBot.h"
#include "TriggerBot.h"
#include <QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class CS2MenuClass; };
QT_END_NAMESPACE

class CS2Menu : public QMainWindow
{
    Q_OBJECT


public:
    CS2Menu(QWidget *parent = nullptr);
    ~CS2Menu();

private:
    Ui::CS2MenuClass *ui;
    QTimer* m_handle_hotkey = new QTimer(this);
    bool m_hide_window = false;

    QTimer* m_aimbot = new QTimer(this);
    QTimer* m_triggerbot = new QTimer(this);
    QTimer* m_exwin = new QTimer(this);
    QMediaPlayer* player;

private slots:
    void eps_box_cheat(int toggle);
    void health_bar_cheat(int toggle);
    void health_status_cheat(int toggle);
    void lines_cheat(int toggle);
    void team_cheat(int toggle);
    void distance_cheat(int toggle);
    void aimbot_cheat(int toggle);
    void triggerbot_cheat(int toggle);
    void crosshair_cheat(int toggle);
   
};
