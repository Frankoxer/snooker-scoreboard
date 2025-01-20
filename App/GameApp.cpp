//
// Created by Frankoxer on 25-1-19.
//

#include "GameApp.h"

void GameApp::init() {

    Window *window = new Window();
    MatchThread *matchThread = new MatchThread();

    // Connect the signals and slots
    connect(matchThread, &MatchThread::initializeMatch, window, &Window::initializeMatch);
    connect(matchThread, &MatchThread::updateFrame, window, &Window::updateFrame);
    connect(matchThread, &MatchThread::foulRecolor, window, &Window::foulRecolor);
    connect(matchThread, &MatchThread::showNewFrame, window, &Window::showNewFrame);
    connect(window, &Window::keyScorePressed, matchThread, &MatchThread::addScore);
    connect(window, &Window::keyFPressed, matchThread, &MatchThread::foul);
    connect(window, &Window::keyEnterPressed, matchThread, &MatchThread::endOfFrame);
    connect(window, &Window::keySpacePressed, matchThread, &MatchThread::switchPlayer);

    // Initialize the match
    matchThread->initialize();
    window->show();
}