//
// Created by Frankoxer on 25-1-19.
//

#ifndef MATCHTHREAD_H
#define MATCHTHREAD_H

#include <Match.h>
#include <QtCore/qobject.h>

#include "json.hpp"

class MatchThread : public QObject {
    Q_OBJECT
public:
    void initialize();
    void run();
private:
    Match match;
    Frame currentFrame;
    bool isPlayer1 = true;
    bool isFoul = false;
signals:
    void initializeMatch(Match match, Frame frame, bool isPlayer1);
    void updateFrame(Frame frame, bool isPlayer1);
    void foulRecolor(bool isFoul);
public slots:
    void switchPlayer();
    void addScore(int score);
    void foul();
    void endOfFrame();
};



#endif //MATCHTHREAD_H
