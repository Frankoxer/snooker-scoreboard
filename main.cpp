#include <QApplication>
#include "App/GameApp.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GameApp game;
    game.init();
    return QApplication::exec();
}
