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
    std::string tournament_name;
    name player1_name;
    name player2_name;
    MatchType round;
    unsigned int frames;
    std::vector<Frame> frame_list;

    Match() {
        tournament_name = "World Championship 1985";
        player1_name = {"Steve", "Davis"};
        player2_name = {"Dennis", "Taylor"};
        round = MatchType::FINAL;
        frames = 35;
        frame_list = std::vector<Frame>();
    }
};



#endif //MATCH_H
