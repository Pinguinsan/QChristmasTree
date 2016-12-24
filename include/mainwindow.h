#ifndef QCHRISTMASTREE_MAINWINDOW_H
#define QCHRISTMASTREE_MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>

#include <memory>
#include <future>
#include <list>
#include <thread>
#include <generalutilities.h>
#include <udpclient.h>

#include "custompushbutton.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateFutureHandles();
    void onTieredButtonClicked(CustomPushButton *button);
    void onAllOnButtonClicked(bool checked);
    void onAllOffButtonClicked(bool checked);

private:
    std::unique_ptr<Ui::MainWindow> m_uiPtr;
    std::vector<CustomPushButton *> m_numberedButtons;
    std::unique_ptr<QTimer> m_eventTimer;
    std::list<std::future<void>> m_futureHandles;

    static const unsigned long EVENT_INTERVAL;
    static const uint16_t CLIENT_PORT_NUMBER;
    static const std::vector<uint16_t> CLIENT_PORT_NUMBERS;
    static const char *CLIENT_HOST_NAME;
    static const char *PTCHANGE_BASE_STRING;
    static const char *DWRITE_BASE_STRING;
    static const char *DWRITEALL_BASE_STRING;
    static const char *DOUT_STRING;
    static const char *CHECKED_STYLESHEET;
    static const char *UNCHECKED_STYLESHEET;
    void uncheckAllOtherNumberedPushButtons(CustomPushButton *other);

    void sendUDPDatagramHandoff(const std::string &hostName, uint16_t portNumber, const std::string &str);
    void sendUDPDatagramsHandoff(const std::string &hostName, std::vector<uint16_t> portNumbers, const std::string &str);

    void sendUDPDatagram(const std::string &hostName, uint16_t portNumber, const std::string &str);
    void sendUDPDatagrams(const std::string &hostName, std::vector<uint16_t> portNumbers, const std::string &str);

    void staticSendUDPDatagram(MainWindow *mainWindow, const std::string *hostName, const uint16_t *portNumber, const std::string *str);
    void staticSendUDPDatagrams(MainWindow *mainWindow, const std::string *hostName, const std::vector<uint16_t> *portNumbers, const std::string *str);


    template<typename R>
    bool isReady(std::future<R> const& f)
    {
        return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
    }

};

#endif //QCHRISTMASTREE_MAINWINDOW_H
