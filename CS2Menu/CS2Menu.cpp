#include "CS2Menu.h"
#include "About.h"

#include <QtConcurrent>
// Config config;

void StartExternalWindows()
{
    CreateExternalWindows();
}

void Aimbots()
{
    while (true)
    {
        if (config.aimbot)
        {
            ExternalAimBot();
            // Sleep(50);
        }
    }
}

void TriggerBots()
{
    while (true)
    {
        if (config.triggerBot)
        {
            TriggerBot();
            // Sleep(50);
        }
    }
}

CS2Menu::CS2Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CS2MenuClass())
{
    ui->setupUi(this);

    connect(ui->actionAbout_CS2Menu, &QAction::triggered, [=]() {
        About about(this);
        about.exec();
    });

    connect(ui->actionExit, &QAction::triggered, [=]() {
        ExitProcess(0);
        });

    m_handle_hotkey->start(100);

    connect(m_handle_hotkey, &QTimer::timeout, [=]() {

        if (config.foundGameProcess)
        {
            ui->statusBar->showMessage("Found game process...", 0);

            if(config.runFeatures){
                Sleep(1000);
                QtConcurrent::run(Aimbots);
                QtConcurrent::run(TriggerBots);
                QtConcurrent::run(StartExternalWindows);
                config.runFeatures = 0;
            }

           
        }
        else {
            ui->statusBar->showMessage("Waiting for game process...", 0);
        }

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            if (!m_hide_window)
            {
                showMinimized();
            }
            else {
                showNormal();
            }
            m_hide_window = !m_hide_window;
        }
     });


    connect(ui->espBoxCheckBox, &QCheckBox::toggled, this, &CS2Menu::eps_box_cheat);
    connect(ui->healthBarCheckBox, &QCheckBox::toggled, this, &CS2Menu::health_bar_cheat);
    connect(ui->healthStatusCheckBox, &QCheckBox::toggled, this, &CS2Menu::health_status_cheat);
    connect(ui->linesCheckBox, &QCheckBox::toggled, this, &CS2Menu::lines_cheat);
    connect(ui->teamCheckBox, &QCheckBox::toggled, this, &CS2Menu::team_cheat);
    connect(ui->distanceCheckBox, &QCheckBox::toggled, this, &CS2Menu::distance_cheat);
    connect(ui->aimbotCheckBox, &QCheckBox::toggled, this, &CS2Menu::aimbot_cheat);
    connect(ui->TriggerBotCheckBox, &QCheckBox::toggled, this, &CS2Menu::triggerbot_cheat);
    connect(ui->crosshairCheckBox, &QCheckBox::toggled, this, &CS2Menu::crosshair_cheat);


    ui->espBoxCheckBox->setChecked(config.boxes);
    ui->healthBarCheckBox->setChecked(config.healthBar);
    ui->healthStatusCheckBox->setChecked(config.healthStatus);
    ui->linesCheckBox->setChecked(config.lines);
    ui->teamCheckBox->setChecked(config.team);
    ui->distanceCheckBox->setChecked(config.boxes);
    ui->aimbotCheckBox->setChecked(config.aimbot);
    ui->TriggerBotCheckBox->setChecked(config.triggerBot);
    ui->crosshairCheckBox->setChecked(config.crosshair);


    this->player = new QMediaPlayer(this);
    QAudioOutput* audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.4);



    // mem.Setup();
    // mem.GetModules();

}

void CS2Menu::eps_box_cheat(int toggle)
{
    config.boxes = toggle;
    if (toggle)
    {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/esp_box_activated.mp3"));
        player->play();
    }
    else {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/esp_box_deactivated.mp3"));
        player->play();
    }
}

void CS2Menu::health_bar_cheat(int toggle)
{
    config.healthBar = toggle;
    if (toggle)
    {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/health_bar_activated.mp3"));
        player->play();
    }
    else {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/health_bar_deactivated.mp3"));
        player->play();
    }
}

void CS2Menu::health_status_cheat(int toggle)
{
    config.healthStatus = toggle;
    if (toggle)
    {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/health_status_activated.mp3"));
        player->play();
    }
    else {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/health_status_deactivated.mp3"));
        player->play();
    }
}

void CS2Menu::lines_cheat(int toggle)
{
    config.lines = toggle;
    if (toggle)
    {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/lines_activated.mp3"));
        player->play();
    }
    else {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/lines_deactivated.mp3"));
        player->play();
    }
}

void CS2Menu::team_cheat(int toggle)
{
    config.team = toggle;
    if (toggle)
    {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/team_activated.mp3"));
        player->play();
    }
    else {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/team_deactivated.mp3"));
        player->play();
    }
}

void CS2Menu::distance_cheat(int toggle)
{
    config.distance = toggle;
    if (toggle)
    {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/distance_activated.mp3"));
        player->play();
    }
    else {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/distance_deactivated.mp3"));
        player->play();
    }
}

void CS2Menu::aimbot_cheat(int toggle)
{
    config.aimbot = toggle;
    if (toggle)
    {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/aimbot_activated.mp3"));
        player->play();
    }
    else {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/aimbot_deactivated.mp3"));
        player->play();
    }
}

void CS2Menu::triggerbot_cheat(int toggle)
{
    config.triggerBot = toggle;
    if (toggle)
    {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/trigger_bot_activated.mp3"));
        player->play();
    }
    else {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/trigger_bot_deactivated.mp3"));
        player->play();
    }
}

void CS2Menu::crosshair_cheat(int toggle)
{
    config.crosshair = toggle;
    if (toggle)
    {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/crosshair_activated.mp3"));
        player->play();
    }
    else {
        player->setSource(QUrl::fromLocalFile("qrc:/CS2Menu/assets/crosshair_deactivated.mp3"));
        player->play();
    }
}

CS2Menu::~CS2Menu()
{
    delete ui;
}


