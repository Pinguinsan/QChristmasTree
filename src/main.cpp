#include <QApplication>
#include <memory>
#include <generalutilities.h>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    std::unique_ptr<QApplication> qApplication{std::make_unique<QApplication>(argc, argv)};
    std::unique_ptr<MainWindow> mainWindow{std::make_unique<MainWindow>()};
    mainWindow->showMaximized();

    return qApplication->exec();
}
