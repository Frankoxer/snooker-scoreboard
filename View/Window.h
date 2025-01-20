//
// Created by Frankoxer on 25-1-19.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "Match.h"
#include <string>
#include <QKeyEvent>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QWidget {
Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window() override;

private:
    Ui::Window *ui;
    Match match;
    Frame currentFrame;
    QLabel *player1CircleLabel = nullptr;
    QLabel *player2CircleLabel = nullptr;
    QLabel *player1CurrentScoreLabel = nullptr;
    QLabel *player2CurrentScoreLabel = nullptr;
    bool isPlayer1;
    QString matchTypeToString(MatchType type);
    void keyPressEvent(QKeyEvent *event) override;
    void updateIsPlayer1();
    void updateScoreLabels();

public slots:
    void initializeMatch(Match match, Frame frame, bool isPlayer1);
    void updateFrame(Frame frame, bool isPlayer1);
    void foulRecolor(bool isFoul);

signals:
    void keyScorePressed(int score);
    void keyFPressed();
    void keyBackSpacePressed();
    void keyEnterPressed();
    void keySpacePressed();
};


#endif //WINDOW_H
