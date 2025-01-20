//
// Created by Frankoxer on 25-1-19.
//

#include "MatchThread.h"
#include <fstream>
#include <iostream>

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

    for (const auto& frame : j["FrameList"]) {
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
    currentFrame.player1_max_break = player1_break > currentFrame.player1_max_break ? player1_break : currentFrame.player1_max_break;
    player1_break = 0;
    currentFrame.player2_max_break = player2_break > currentFrame.player2_max_break ? player2_break : currentFrame.player2_max_break;
    player2_break = 0;
    emit updateFrame(currentFrame, isPlayer1, player1_break, player2_break);
}

void MatchThread::addScore(int score) {
    if (isPlayer1) {
        if(!isFoul) {
            currentFrame.player1_points += score;
            player1_break += score;
        } else {
            currentFrame.player2_points += score;
            player1_break = 0;
            isPlayer1 = !isPlayer1;
            isFoul = false;
        }
        currentFrame.player1_max_break = player1_break > currentFrame.player1_max_break ? player1_break : currentFrame.player1_max_break;
    } else {
        if(!isFoul) {
            currentFrame.player2_points += score;
            player2_break += score;
        } else {
            currentFrame.player1_points += score;
            player2_break = 0;
            isPlayer1 = !isPlayer1;
            isFoul = false;
        }
        currentFrame.player2_max_break = player2_break > currentFrame.player2_max_break ? player2_break : currentFrame.player2_max_break;
    }
    emit updateFrame(currentFrame, isPlayer1, player1_break, player2_break);
}

void MatchThread::foul() {
    isFoul = !isFoul;
    emit foulRecolor(isFoul);
}

void MatchThread::endOfFrame() {
    match.frame_list.push_back(currentFrame);
    unsigned int winner = currentFrame.player1_points > currentFrame.player2_points ? 1 : 2;

    std::cout << "End of frame, winner is player " << winner << std::endl;

    // 将数据写回 json 文件，只用更新 match 中的 frames 和 FrameList 即可
    // Read the existing JSON data
    std::ifstream i("../Data/demo.json");
    nlohmann::json j;
    i >> j;


    // Update the FrameList information
    j["FrameList"] = nlohmann::json::array();
    for (const auto& frame : match.frame_list) {
        nlohmann::json f;
        f["player1Points"] = frame.player1_points;
        f["player1MaxBreak"] = frame.player1_max_break;
        f["player2Points"] = frame.player2_points;
        f["player2MaxBreak"] = frame.player2_max_break;
        j["FrameList"].push_back(f);
    }

    // Write the updated JSON data back to the file
    std::ofstream o("../Data/demo.json");
    o << j.dump(4) << std::endl;

    unsigned int player1_frames = 0;
    unsigned int player2_frames = 0;

    for(auto it = match.frame_list.begin(); it != match.frame_list.end(); it++) {
        if(it->player1_points > it->player2_points) {
            player1_frames++;
        } else {
            player2_frames++;
        }
    }

    if(player1_frames == match.frames/2 + 1 || player2_frames == match.frames/2 + 1) {
        // End of match
    } else {
        // Start a new frame
        currentFrame = Frame();
        isPlayer1 = true;
        isFoul = false;
        player1_break = 0;
        player2_break = 0;
        emit showNewFrame(match, currentFrame);
    }
}
