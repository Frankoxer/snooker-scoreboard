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
private:
    Match match;
    Frame currentFrame;
    bool isPlayer1 = true;
    bool isFoul = false;
    unsigned int player1_break = 0;
    unsigned int player2_break = 0;
signals:
    void initializeMatch(Match match, Frame frame, bool isPlayer1);
    void updateFrame(Frame frame, bool isPlayer1, unsigned int player1_break, unsigned int player2_break);
    void foulRecolor(bool isFoul);
    void showNewFrame(Match match, Frame frame);
public slots:
    void switchPlayer();
    void addScore(int score);
    void foul();
    void endOfFrame();
};



#endif //MATCHTHREAD_H
