#include "mainwindow.h"
#include "ui_mainwindow.h"

const uint16_t MainWindow::CLIENT_PORT_NUMBER{62001};
const std::vector<uint16_t> MainWindow::CLIENT_PORT_NUMBERS{62000, 62001, 62002, 62003, 62004, 62005, 62006};
const char *MainWindow::CLIENT_HOST_NAME{"pinguinsan1224.asuscomm.com"};
const char *MainWindow::PTCHANGE_BASE_STRING{"{ptchange:"};
const char *MainWindow::DWRITE_BASE_STRING{"{dwrite:"};
const char *MainWindow::DWRITEALL_BASE_STRING{"{dwriteall:"};
const char *MainWindow::DOUT_STRING{"dout"};
const unsigned long MainWindow::EVENT_INTERVAL{100};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    m_uiPtr{std::make_unique<Ui::MainWindow>()},
    m_eventTimer{std::make_unique<QTimer>()}
{
    this->m_uiPtr->setupUi(this);

    connect(this->m_uiPtr->firstTierPushButton, SIGNAL(leftClicked(CustomPushButton *)), this, SLOT(onTieredButtonClicked(CustomPushButton *)));
    connect(this->m_uiPtr->secondTierPushButton, SIGNAL(leftClicked(CustomPushButton *)), this, SLOT(onTieredButtonClicked(CustomPushButton *)));
    connect(this->m_uiPtr->thirdTierPushButton, SIGNAL(leftClicked(CustomPushButton *)), this, SLOT(onTieredButtonClicked(CustomPushButton *)));
    connect(this->m_uiPtr->fourthTierPushButton, SIGNAL(leftClicked(CustomPushButton *)), this, SLOT(onTieredButtonClicked(CustomPushButton *)));
    connect(this->m_uiPtr->fifthTierPushButton, SIGNAL(leftClicked(CustomPushButton *)), this, SLOT(onTieredButtonClicked(CustomPushButton *)));
    connect(this->m_uiPtr->allOnPushButton, SIGNAL(clicked(bool)), this, SLOT(onAllOnButtonClicked(bool)));
    connect(this->m_uiPtr->allOffPushButton, SIGNAL(clicked(bool)), this, SLOT(onAllOffButtonClicked(bool)));

    this->m_uiPtr->firstTierPushButton->setNumber(2);
    this->m_uiPtr->secondTierPushButton->setNumber(3);
    this->m_uiPtr->thirdTierPushButton->setNumber(4);
    this->m_uiPtr->fourthTierPushButton->setNumber(5);
    this->m_uiPtr->fifthTierPushButton->setNumber(6);

    this->m_numberedButtons.push_back(this->m_uiPtr->firstTierPushButton);
    this->m_numberedButtons.push_back(this->m_uiPtr->secondTierPushButton);
    this->m_numberedButtons.push_back(this->m_uiPtr->thirdTierPushButton);
    this->m_numberedButtons.push_back(this->m_uiPtr->fourthTierPushButton);
    this->m_numberedButtons.push_back(this->m_uiPtr->fifthTierPushButton);

    for (int i = 0; i < 1; i++) {
        std::string stringToSend{static_cast<std::string>(MainWindow::DWRITEALL_BASE_STRING) + "0}"};
        this->sendUDPDatagramsHandoff(static_cast<std::string>(MainWindow::CLIENT_HOST_NAME),
                              MainWindow::CLIENT_PORT_NUMBERS,
                              stringToSend);
    }

    for (int i = 0; i < 1; i++) {
        for (auto &it : this->m_numberedButtons) {
            std::string stringToSend{static_cast<std::string>(MainWindow::DWRITE_BASE_STRING)
                                     + std::to_string(it->number())
                                     + ":0}"};
            this->sendUDPDatagramsHandoff(static_cast<std::string>(MainWindow::CLIENT_HOST_NAME),
                                  MainWindow::CLIENT_PORT_NUMBERS,
                                  stringToSend);
        }
    }

    connect(this->m_eventTimer.get(), SIGNAL(timeout()), this, SLOT(updateFutureHandles()));
    this->m_eventTimer->setInterval(MainWindow::EVENT_INTERVAL);
    this->m_eventTimer->start();
}

void MainWindow::updateFutureHandles()
{
    if (this->m_futureHandles.empty()) {
        return;
    }
    auto it = this->m_futureHandles.begin();
    for (; it != this->m_futureHandles.end(); it++) {
        if (this->isReady(*it)) {
            this->m_futureHandles.erase(it);
            it = this->m_futureHandles.begin();
        }
    }
}

void MainWindow::onTieredButtonClicked(CustomPushButton *button)
{
    button->flipState();
    for (int i = 0; i < 1; i++) {
        std::string stringToSend{static_cast<std::string>(MainWindow::DWRITE_BASE_STRING)
                                 + std::to_string(button->number())
                                 + ":"
                                 + std::to_string(button->state())
                                 + "}"};
        this->sendUDPDatagramsHandoff(static_cast<std::string>(MainWindow::CLIENT_HOST_NAME),
                              MainWindow::CLIENT_PORT_NUMBERS,
                              stringToSend);

    }
}

void MainWindow::onAllOnButtonClicked(bool checked)
{
    (void)checked;
    for (int i = 0; i < 1; i++) {
        for (auto &it : this->m_numberedButtons) {
            it->setChecked(true);
            it->setState(true);

        }
        std::string stringToSend{static_cast<std::string>(MainWindow::DWRITEALL_BASE_STRING) + "1}"};
        this->sendUDPDatagramsHandoff(static_cast<std::string>(MainWindow::CLIENT_HOST_NAME),
                              MainWindow::CLIENT_PORT_NUMBERS,
                              stringToSend);
    }
}

void MainWindow::onAllOffButtonClicked(bool checked)
{
    (void)checked;
    for (int i = 0; i < 1; i++) {
        for (auto &it : this->m_numberedButtons) {
            it->setChecked(false);
            it->setState(false);

        }
        std::string stringToSend{static_cast<std::string>(MainWindow::DWRITEALL_BASE_STRING) + "0}"};
        this->sendUDPDatagramsHandoff(static_cast<std::string>(MainWindow::CLIENT_HOST_NAME),
                              MainWindow::CLIENT_PORT_NUMBERS,
                              stringToSend);
    }
}

void MainWindow::sendUDPDatagramHandoff(const std::string &hostName, uint16_t portNumber, const std::string &str)
{
    this->m_futureHandles.emplace_back(std::async(std::launch::async,
                                                  &MainWindow::sendUDPDatagram,
                                                  this,
                                                  hostName,
                                                  portNumber,
                                                  str));
}

void MainWindow::sendUDPDatagramsHandoff(const std::string &hostName, std::vector<uint16_t> portNumbers, const std::string &str)
{
    this->m_futureHandles.push_back(std::async(std::launch::async,
                                                  &MainWindow::sendUDPDatagrams,
                                                  this,
                                                  hostName,
                                                  portNumbers,
                                                  str));
}

void MainWindow::sendUDPDatagram(const std::string &hostName, uint16_t portNumber, const std::string &str)
{
    try {
        std::unique_ptr<UDPClient> udpClient{std::make_unique<UDPClient>(hostName, portNumber)};
        udpClient->writeString(str);
        std::cout << "Send string " << str << " to " << hostName << " (port " << portNumber << ")" << std::endl;
    } catch (std::exception &e) {
        (void)e;
        std::unique_ptr<QMessageBox> warningBox{std::make_unique<QMessageBox>()};
        warningBox->setText("Failed to send message! (Is there an active internet connection?)");
        warningBox->exec();
    }
}

void MainWindow::sendUDPDatagrams(const std::string &hostName, std::vector<uint16_t> portNumbers, const std::string &str)
{
    for (auto &it : portNumbers) {
        try {
            std::unique_ptr<UDPClient> udpClient{std::make_unique<UDPClient>(hostName, it)};
            udpClient->writeString(str);
            std::cout << "Send string " << str << " to " << hostName << " (port " << it << ")" << std::endl;
        } catch (std::exception &e) {
            (void)e;
            std::unique_ptr<QMessageBox> warningBox{std::make_unique<QMessageBox>()};
            warningBox->setText("Failed to send message! (Is there an active internet connection?)");
            warningBox->exec();
        }
    }

}

void MainWindow::staticSendUDPDatagram(MainWindow *mainWindow, const std::string *hostName, const uint16_t *portNumber, const std::string *str)
{
    (void)mainWindow;
    try {
        std::unique_ptr<UDPClient> udpClient{std::make_unique<UDPClient>(*hostName, *portNumber)};
        udpClient->writeString(*str);
    } catch (std::exception &e) {
        (void)e;
        std::unique_ptr<QMessageBox> warningBox{std::make_unique<QMessageBox>()};
        warningBox->setText("Failed to send message! (Is there an active internet connection?)");
        warningBox->exec();
    }
}

void MainWindow::staticSendUDPDatagrams(MainWindow *mainWindow, const std::string *hostName, const std::vector<uint16_t> *portNumbers, const std::string *str)
{
    (void)mainWindow;
    for (auto &it : *portNumbers) {
        try {
            std::unique_ptr<UDPClient> udpClient{std::make_unique<UDPClient>(*hostName, it)};
            udpClient->writeString(*str);
        } catch (std::exception &e) {
            (void)e;
            std::unique_ptr<QMessageBox> warningBox{std::make_unique<QMessageBox>()};
            warningBox->setText("Failed to send message! (Is there an active internet connection?)");
            warningBox->exec();
        }
    }
}

void MainWindow::uncheckAllOtherNumberedPushButtons(CustomPushButton *other)
{
    if (other) {
        for (auto &it : this->m_numberedButtons) {
            if (it->number() != other->number()) {
                it->setChecked(false);
            }
        }
    } else {
        for (auto &it : this->m_numberedButtons) {
            it->setChecked(false);
        }
    }
}

MainWindow::~MainWindow()
{

}
