#include "CS2Menu.h"
#include <QtWidgets/QApplication>

#include <QtConcurrent>

#include <Windows.h>
#include "Memory.h"
#include "ExWindow.h"
#include "AimBot.h"
#include "TriggerBot.h"

Config config;

void Init()
{
    mem.Setup();
    mem.GetModules();
}


QString R("");


int main(int argc, char *argv[])
{
    QtConcurrent::run(Init);

    QApplication a(argc, argv);
    CS2Menu w;

    HMENU menu = ::GetSystemMenu((HWND)w.winId(), FALSE);
    ::DeleteMenu(menu, SC_CLOSE, MF_BYCOMMAND);
    ::EnableMenuItem(menu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);

    a.setStyle("Fusion");
    // Set the QSS theme
    w.setWindowFlag(Qt::WindowStaysOnTopHint);

    a.setStyleSheet("QCheckBox:checked { background-color: #00FF00; }");
    a.setWindowIcon(QIcon(":/CS2Menu/assets/counter_strike_2_game_icon_by_ceronemo_dgaf20k-fullview.png"));
    w.show();
    return a.exec();
}
