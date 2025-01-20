//
// Created by Frankoxer on 25-1-19.
// describe a snooker frame
//

#ifndef FRAME_H
#define FRAME_H

class Frame {
public:
    unsigned int player1_points;
    unsigned int player2_points;
    unsigned int player1_max_break;
    unsigned int player2_max_break;
    Frame() {
        player1_points = 0;
        player2_points = 0;
        player1_max_break = 0;
        player2_max_break = 0;
    }
};



#endif //FRAME_H
