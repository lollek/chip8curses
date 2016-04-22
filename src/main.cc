#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "chip8core/Emulator.h"

#include "curses.h"

using namespace std;
using namespace chip8curses;

int constexpr KEY_ESCAPE{27};

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " FILENAME\n";
    return 1;
  }

  Emulator chip8core;
  if (!chip8core.loadFileToRam(argv[1])) {
    cerr << argv[0] << ": Error loading file: " << chip8core.getError() << "\n";
    return 1;
  }

  curses::start(Emulator::screen_rows, Emulator::screen_columns);
  curses::attach(&chip8core);
  vector<bool> keys(Emulator::num_keys);

  bool loop = true;
  while (loop) {
    chip8core.tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    switch (curses::get_char()) {
      case KEY_ESCAPE:
        loop = false;
        break;

      case '1': chip8core.setKeyState(0x0, (keys.at(0x0) = !keys.at(0x0))); break;
      case '2': chip8core.setKeyState(0x1, (keys.at(0x1) = !keys.at(0x1))); break;
      case '3': chip8core.setKeyState(0x2, (keys.at(0x2) = !keys.at(0x2))); break;
      case '4': chip8core.setKeyState(0x3, (keys.at(0x3) = !keys.at(0x3))); break;
      case 'q': chip8core.setKeyState(0x4, (keys.at(0x4) = !keys.at(0x4))); break;
      case 'w': chip8core.setKeyState(0x5, (keys.at(0x5) = !keys.at(0x5))); break;
      case 'e': chip8core.setKeyState(0x6, (keys.at(0x6) = !keys.at(0x6))); break;
      case 'r': chip8core.setKeyState(0x7, (keys.at(0x7) = !keys.at(0x7))); break;
      case 'a': chip8core.setKeyState(0x8, (keys.at(0x8) = !keys.at(0x8))); break;
      case 's': chip8core.setKeyState(0x9, (keys.at(0x9) = !keys.at(0x9))); break;
      case 'd': chip8core.setKeyState(0xA, (keys.at(0xA) = !keys.at(0xA))); break;
      case 'f': chip8core.setKeyState(0xB, (keys.at(0xB) = !keys.at(0xB))); break;
      case 'z': chip8core.setKeyState(0xC, (keys.at(0xC) = !keys.at(0xC))); break;
      case 'x': chip8core.setKeyState(0xD, (keys.at(0xD) = !keys.at(0xD))); break;
      case 'c': chip8core.setKeyState(0xE, (keys.at(0xE) = !keys.at(0xE))); break;
      case 'v': chip8core.setKeyState(0xF, (keys.at(0xF) = !keys.at(0xF))); break;
    }

  }

  curses::stop();
  return 0;
}
