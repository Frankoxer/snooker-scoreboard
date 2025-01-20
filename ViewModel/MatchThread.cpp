//
// Created by Frankoxer on 25-1-19.
//

#include "MatchThread.h"
#include <fstream>

void MatchThread::initialize() {
    // 使用 json.hpp 解析库解析 Data/demo.json 文件
    std::ifstream i("../Data/demo.json");
    nlohmann::json j;
    i >> j;

    // 填充 Match 实体
    match.player1_name.first_name = j["player1"]["firstName"];
    match.player1_name.last_name = j["player1"]["lastName"];
    match.player2_name.first_name = j["player2"]["firstName"];
    match.player2_name.last_name = j["player2"]["lastName"];

    std::string round = j["Match"]["round"];
    if (round == "LAST_128") match.round = MatchType::LAST_128;
    else if (round == "LAST_64") match.round = MatchType::LAST_64;
    else if (round == "LAST_32") match.round = MatchType::LAST_32;
    else if (round == "LAST_16") match.round = MatchType::LAST_16;
    else if (round == "QUARTER_FINAL") match.round = MatchType::QUARTER_FINAL;
    else if (round == "SEMI_FINAL") match.round = MatchType::SEMI_FINAL;
    else if (round == "FINAL") match.round = MatchType::FINAL;

    match.frames = j["Match"]["frames"];
    match.player1_frames = j["Match"]["player1frames"];
    match.player2_frames = j["Match"]["player2frames"];

    for (const auto& frame : j["frames"]) {
        Frame f;
        f.player1_points = frame["player1Points"];
        f.player1_max_break = frame["player1MaxBreak"];
        f.player2_points = frame["player2Points"];
        f.player2_max_break = frame["player2MaxBreak"];
        match.frame_list.push_back(f);
    }

    currentFrame = Frame();

    emit initializeMatch(match, currentFrame, isPlayer1);
}

void MatchThread::run() {
    // Initialize the frame
    unsigned int frame_number = match.frame_list.size() + 1;
}

void MatchThread::switchPlayer() {
    isPlayer1 = !isPlayer1;
    emit updateFrame(currentFrame, isPlayer1);
}

void MatchThread::addScore(int score) {
    if (isPlayer1) {
        if(!isFoul) {
            currentFrame.player1_points += score;
        } else {
            currentFrame.player2_points += score;
            isPlayer1 = !isPlayer1;
            isFoul = false;
        }
    } else {
        if(!isFoul) {
            currentFrame.player2_points += score;
        } else {
            currentFrame.player1_points += score;
            isPlayer1 = !isPlayer1;
            isFoul = false;
        }
    }
    emit updateFrame(currentFrame, isPlayer1);
}

void MatchThread::foul() {
    isFoul = !isFoul;
    emit foulRecolor(isFoul);
}

void MatchThread::endOfFrame() {
    match.frame_list.push_back(currentFrame);
    unsigned int winner = currentFrame.player1_points > currentFrame.player2_points ? 1 : 2;
    if(winner == 1) {
        match.player1_frames++;
    } else {
        match.player2_frames++;
    }
    if(match.player1_frames == match.frames/2 + 1 || match.player2_frames == match.frames/2 + 1) {
        // End of match
    } else {
        // Start a new frame
        currentFrame = Frame();
    }
}
