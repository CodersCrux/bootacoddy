//#include "basicoddy.hpp"
//
//namespace bac::programs::basicoddy {
//
//    using namespace types;
//    using namespace drivers::video;
//
//    SortedDictionary<size_t, String> *lines;
//
//
//    void run_line() {
//
//
//
//    }
//
//
//    int main() {
//
//        lines = new SortedDictionary<size_t, String>;
//
//        txt3::setcolor(0x0D);
//        txt3::setcursor(0, 0);
//        txt3::clear();
//
//
//        lines->set(10, "Hello there");
//
//
//        for (auto line : *lines) {
//
//            txt3::print("%s\n", line.value.str());
//        }
//
//
//
//
//        while (1);
//
//    }
//
//
//
////    using namespace drivers::input;
////    using namespace drivers::video;
////    using namespace types;
////
//////    SortedDictionary<int, String> *lines;
////
//////    String lines[64001]; // There are 64,000 available line slots. line index 64,000 is reserved for prompt commands.
////    SortedDictionary<u32, String> lines;
////
////
////    bool running = true;
////    bool accept_input = false;
////    u8 prompt_row;
////    u16 highest_line = 0;
////
////    u16 num_chars = 0;
////
////    size_t current_line;
////
////    void prompt() {
////
////        txt3::newline();
////        auto pos = txt3::getcursor();
////        prompt_row = pos.y;
////
////        txt3::setcursor(0, prompt_row);
////        txt3::prints("] ");
////        accept_input = true;
////    }
////
////    /**
////     * @brief Internal function for interpreting and running commands.\n
////     * return codes:\n
////     * * -1: goto\n
////     * * 0: success\n
////     * * 1: Line index out of range\n
////     * * 2: Empty string\n
////     * * 3: Invalid arguments\n
////     *
////     * @param str
////     * @return
////     */
////    int interpret_cmd(String str) {
////
////        if (str.isEmpty())
////            return 2; // empty string
////
////        txt3::print("(%i) %s\n", current_line, str.str());
////
//////        List<char *> args;
//////        u8 last = 0;
//////        for (size_t i = 0; i < str.length(); i++) {
//////
//////            if (str[i] == ' ' || str[i] == 0) {
//////
//////                str[i] = 0;
//////                args += &str[last];
//////                last = i + 1;
//////            }
//////        }
//////        args += &str[last];
//////
//////        txt3::print("Split: ");
//////        for (auto arg : args) {
//////            txt3::print("%s ", arg);
//////        }
//////        txt3::newline();
////
////        List<char *> args;
////        char *ptr = (char *)str.str(), *last = ptr;
////        while (*ptr) {
////            if (*ptr == ' ') {
////                args += last;
////                last = ptr + 1;
////                txt3::print("Found argument.\n");
////                *ptr = 0;
////            }
////            ptr++;
////        }
////        args += last;
////
////        String cmd = args[0];//args[0];
////
////
////        if (cmd.isDecimal()) { // Set command
////
////            int line_idx = cmd.toInt();
////            if (line_idx < 0 || line_idx >= 64000)
////                return 1; // Line index out of range
////
////            lines.set(line_idx, &str[cmd.length() + 1]);
////
////        } else if (cmd == "#") {} // Comment
//////        else if (cmd == "goto") { // Go to line
//////
//////            String num;
//////
//////            if (args.length() < 2 || !(num = args[1]).isDecimal())
//////                return 3; // Invalid arguments
//////
//////            int line_idx = num.toInt();
//////            txt3::print("Going to %i\n", line_idx);
//////
//////            if (line_idx < 0 || line_idx >= 64000)
//////                return 1; // Line index out of range
//////
//////            current_line = line_idx;
//////            return -1; // Goto code, makes sure we reach the correct line
////        else if (cmd == "print") { // Print without new space
////
////            size_t i = 1;
////            for (auto iter = ++args.begin(); iter != args.end(); ++iter, ++i) {
////
////                txt3::prints(*iter);
////                if (i < args.length() - 1)
////                    txt3::printc(' ');
////            }
////        } else if (cmd == "printn") { // Print with new line
////
////            size_t i = 1;
////            for (auto iter = ++args.begin(); iter != args.end(); ++iter, ++i) {
////
////                txt3::prints(*iter);
////                if (i < args.length() - 1)
////                    txt3::printc(' ');
////            }
////            txt3::newline();
////        } else if (cmd == "help") {
////            txt3::prints("Helping you. *pat pat*\n");
////
////        } else {//if (str == "list") { // List all comments ascending
////
////
////
////            for (u16 i = 0; i < 64000; i++) {
////
////
////
////                if (lines[i] == 0 || lines[i].isEmpty())
////                    continue;
////                txt3::print("%i   %s\n", i, lines[i].str());
////            }
////        }
//////        } else {
//////            txt3::print("Unknown command '%s'\n", cmd.str());
//////        }
////
//////        for (auto iter = ++args.begin(); iter != args.end(); ++iter)
//////            *(*iter - 1) = ' ';
////
////        return 0;
////    }
////
////    void run(u16 line_idx) {
////
////        current_line = line_idx;
////
////        do {
////
////            if (lines[current_line].isEmpty()) {
////
////                txt3::print("Skipping %i\n", current_line);
////                current_line++;
////                continue;
////            }
////
////
////            int code = interpret_cmd(lines[current_line]);
////
////            // TODO: Error checks, exceptions
////
////            if (code > 0) { // Error happened
////
////                txt3::setcolor(0x0C);
////                txt3::print("\nERROR: ");
////                switch (code) {
////                    case 1: // line index out of range
////                        txt3::print("Line index out of range");
////                        break;
////                    case 2:
////                        txt3::print("Empty string");
////                        break;
////                    case 3:
////                        txt3::print("Invalid arguments");
////                        break;
////                }
////                txt3::print(" (%i)\n", current_line);
////
////            }
////
////            // Unless the cmd was goto, increment line
////            if (code != -1)
////                current_line++;
////
////        } while (current_line < 64000);
////    }
////
////    void keyHandler(keyboard::Keycode key) {
////
////        if (accept_input) {
////
////            if (keyboard::text::isSymbol(key)) {
////
////                txt3::printc(keyboard::text::toAscii(key));
////
////                // Make sure they don't somehow, majestically, write SO many characters that they breach the video memory.
////                if (num_chars < 80 * 25 - 1)
////                    num_chars++;
////            }
////
////            else if (key == keyboard::Keycode::Backspace) {
////
////                if (num_chars > 0) {
////
////                    num_chars--;
////                    txt3::setcursor(txt3::getcursorIdx() - 1);
////                    txt3::plot(' ');
////                }
////            }
////
////            if (key == keyboard::Keycode::Enter) {
////
////                accept_input = false;
////
////                u16 idx = txt3::getcursorIdx();
////                char str[num_chars];
////                for (u16 i = 0; i < num_chars; i++)
////                    str[i] = txt3::get(idx - num_chars + i) & 0xFF;
////
////                txt3::print("chars: %i", num_chars);
////
//////                txt3::newline();
//////                txt3::prints(str, num_chars);
////
////                num_chars = 0;
////
////                kernel::paging::malloc(3000);
////
////                lines[64000] = String(str, num_chars);
////                run(64000);
////
////
////                prompt();
////                accept_input = true;
////
////            }
////        }
////
////    }
////
////    int main() {
////
////        txt3::setcolor(0x0d);
////        txt3::clear();
////        txt3::setcursor(0, 0);
////        txt3::showcursor(7, 9);
////        txt3::print(
////                "BasiCoddy language v1, inspired by Apple Basic.\n"
////                "A very awful manual is available 'basicoddy.md'.\n"
////                "Run 'help' to get started.\n\n"
////        );
////
////        keyboard::onKeyPressed = keyHandler;
////
//////        prompt();
//////        accept_input = true;
////
//////        lines[0] = "# Hello there, I'm a comment";
//////        lines[1] = "# the line above me is a comment";
//////        lines[2] = "# the line above me is a comment";
//////        lines[3] = "# the line above me is a comment";
//////        lines[4] = "# the line above me really loves line #3";
//////        lines[5] = "# the line below #6 is gay";
//////        lines[6] = "# redemption";
//////        lines[7] = "# line #5 is a liar";
//////        lines[8] = "# the line below me is two lines away from redemption";
//////        lines[9] = "# a sinner";
//////
//////        lines[10] = "printn hello there!";
////
////        lines.set(10, "list");
//////        lines[20] = "printn Hi";
////
//////        lines[63999] = "goto 0";
////        run(10);
////
////        run(10);
//////        run(10);
////
//////        run(64000);
////
////
////        while (true);
////
////        return 0;
////    }
//}
