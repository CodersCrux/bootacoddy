#include "desktop.hpp"
#include "../drivers/video/txt3.hpp"

namespace bac::programs::desktop {

    using namespace drivers::video;

    int main() {

        txt3::setcolor(0x9F);
        txt3::clear();
        txt3::setcursor(0, 0);

        txt3::print("hello this is the desktop");







        while (1);


        return 0;
    }

}