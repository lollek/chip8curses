#include <curses.h>

#include <iostream>

#include "curses.h"

using namespace std;

namespace chip8curses {
namespace curses {
Emulator* emulator_ptr{nullptr};

namespace {

void write_pixel(int x, int y, bool black) {
  mvaddch(y, x, (black ? ' ' | A_STANDOUT : ' '));
}

void flush() {
  refresh();
}

void callback() {
  byte const* graphics_ptr{emulator_ptr->getGraphicsData()};

  for (unsigned line{0}; line < Emulator::screen_rows; ++line) {
    for (unsigned column{0}; column < Emulator::screen_columns; ++column) {
      byte data = graphics_ptr[line * 8 + column];
      write_pixel(column * 8 + 0, line, (data & 0x80) != 0 );
      write_pixel(column * 8 + 1, line, (data & 0x40) != 0 );
      write_pixel(column * 8 + 2, line, (data & 0x20) != 0 );
      write_pixel(column * 8 + 3, line, (data & 0x10) != 0 );
      write_pixel(column * 8 + 4, line, (data & 0x08) != 0 );
      write_pixel(column * 8 + 5, line, (data & 0x04) != 0 );
      write_pixel(column * 8 + 6, line, (data & 0x02) != 0 );
      write_pixel(column * 8 + 7, line, (data & 0x01) != 0 );
    }
  }
  flush();
}

} // anonymous namespace

bool start(int min_lines, int min_columns) {
  initscr();

  if (LINES < min_lines || COLS < min_columns) {
    cerr << "Screen was too small! Need at least " << min_lines
         << " lines and " << min_columns << " columns\n";
    stop();
    return false;
  }

  raw();
  noecho();
  timeout(0);
  return true;
}

void stop() {
  endwin();
  emulator_ptr = nullptr;
}

void attach(Emulator* emulator) {
  emulator_ptr = emulator;
  emulator->onGraphics = callback;
}

int get_char() {
  return getch();
}

} // curses
} // chip8curses
