//
// Created by Frankoxer on 25-1-19.
//

#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "../View/Window.h"
#include "../ViewModel/MatchThread.h"

class GameApp : public QObject{
    Q_OBJECT
public:
    Window gameWindow;
    MatchThread matchThread;
    void init();
};



#endif //GAMEAPP_H
