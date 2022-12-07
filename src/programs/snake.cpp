//#include "snake.hpp"
//#include "../drivers/video/txt3.hpp"
//#include "../drivers/system/timer.hpp"
//#include "../util/types.h"
//#include "../util/types/list.hpp"
//
//#define SEGMENT_BODY '#'
//#define SEGMENT_HEAD_UP 0x1E
//#define SEGMENT_HEAD_DOWN 0x1F
//#define SEGMENT_HEAD_RIGHT '>'
//#define SEGMENT_HEAD_LEFT '<'
//#define SEGMENT_TAIL 0x09
//
//namespace bac::programs::snake {
//
//    using namespace drivers::video;
//
//    struct Pos {
//        u8 x, y;
//
//        Pos(u8 x, u8 y): x(x), y(y) {}
//
//        bool operator==(Pos &other) {
//            return x == other.x && y == other.y;
//        }
//    };
//
//    types::List<Pos> *segments;
//
//    u8 tick = 0;
//
//    u8 direction = 0; // Directions- 0: UP, 1: RIGHT, 2: DOQN, 3: LEFT
//
//
//    void onTimerTick() {
//
//        if (tick == 100) {
//
//            tick = 0;
//
////            txt3::print("STEP. ");
//        }
//
//        tick++;
//    }
//
//    int main() {
//
//        segments = new types::List<Pos>;
//
//        drivers::system::timer::onTimerTick = onTimerTick;
//
//        *segments += Pos(10, 10);
//
//        txt3::setcolor(0x00);
//        txt3::clear();
//
//        txt3::setcolor(0x0A);
//        txt3::clear();
//
//        txt3::setcolor(0x20);
//        for (u8 x = 19; x < 61; x++)
//            for (u8 y = 1; y < 23; y++)
//                txt3::plot(x, y, x == 19 || x == 60 || y == 1 || y == 22 ? '#' : ' ');
//
//        txt3::setcolor(0x21);
//        txt3::plot(30, 10, '(');
//        txt3::plot(31, 10, ')');
//        txt3::plot(30, 11, '(');
//        txt3::plot(31, 11, ')');
//        txt3::plot(30, 12, '(');
//        txt3::plot(31, 12, ')');
//        txt3::plot(30, 13, '$');
//        txt3::plot(31, 13, '$');
//
//        txt3::plot(31, 15, 'o');
//        txt3::plot(32, 15, 'o');
//        txt3::plot(33, 15, 'o');
//        txt3::plot(34, 15, '$');
//
//        txt3::setcolor(0x2C);
//        txt3::plot(45, 7, '@');
//        txt3::plot(46, 7, '@');
//
//        char str[5] = {SEGMENT_TAIL, SEGMENT_BODY, SEGMENT_BODY, SEGMENT_HEAD_RIGHT, 0};
//        char str2[4] = {SEGMENT_TAIL, SEGMENT_BODY, SEGMENT_BODY, SEGMENT_HEAD_DOWN};
//
//        for (size_t y = 0; y < 4; y++)
//            txt3::plot(10, y + 10, str2[y]);
//
//        txt3::print(str);
//
//
//    }
//
//}