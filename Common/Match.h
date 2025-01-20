//
// Created by Frankoxer on 25-1-19.
// describe the match between two snooker players
//

#ifndef MATCH_H
#define MATCH_H

#include <string>
#include <vector>
#include "Frame.h"

enum class MatchType {
    LAST_128,
    LAST_64,
    LAST_32,
    LAST_16,
    QUARTER_FINAL,
    SEMI_FINAL,
    FINAL
};

struct name {
    std::string first_name;
    std::string last_name;
};

class Match {
public:
    name player1_name;
    name player2_name;
    MatchType round;
    unsigned int frames;
    unsigned int player1_frames;
    unsigned int player2_frames;
    std::vector<Frame> frame_list;

    Match() {
        player1_name = {"Alex", "Higgins"};
        player2_name = {"Steve", "Davis"};
        round = MatchType::LAST_128;
        frames = 9;
        player1_frames = 0;
        player2_frames = 0;
        frame_list = std::vector<Frame>();
    }
};



#endif //MATCH_H
