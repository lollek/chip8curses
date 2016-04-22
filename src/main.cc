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

  bool loop = true;
  while (loop) {
    chip8core.tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    for (unsigned i = 0; i < Emulator::num_keys; ++i) {
      chip8core.setKeyState(i, false);
    }

    switch (curses::get_char()) {
      case KEY_ESCAPE:
        loop = false;
        break;

      case '1': chip8core.setKeyState( 0, true); break;
      case '2': chip8core.setKeyState( 1, true); break;
      case '3': chip8core.setKeyState( 2, true); break;
      case '4': chip8core.setKeyState( 3, true); break;
      case 'q': chip8core.setKeyState( 4, true); break;
      case 'w': chip8core.setKeyState( 5, true); break;
      case 'e': chip8core.setKeyState( 6, true); break;
      case 'r': chip8core.setKeyState( 7, true); break;
      case 'a': chip8core.setKeyState( 8, true); break;
      case 's': chip8core.setKeyState( 0, true); break;
      case 'd': chip8core.setKeyState(10, true); break;
      case 'f': chip8core.setKeyState(11, true); break;
      case 'z': chip8core.setKeyState(12, true); break;
      case 'x': chip8core.setKeyState(13, true); break;
      case 'c': chip8core.setKeyState(14, true); break;
      case 'v': chip8core.setKeyState(15, true); break;
    }
  }

  curses::stop();
  return 0;
}
