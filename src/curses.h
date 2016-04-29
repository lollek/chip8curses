#pragma once

#include "chip8core/Emulator.h"

namespace chip8curses {
namespace curses {

/**
 * Start curses and assert that there are at least x min lines and columns
 * If wide is true, tiles are twice as wide
 * return true on success
 * returns false on error (also cleans up, and prints an error message to stdout)
 */
bool start(int min_lines, int min_columns, bool wide);

/*
 * Stop curses.
 */
void stop();

/**
 * Attack to emulator, and handle all graphics from it.
 */
void attach(Emulator* emulator);

/**
 * Returns being pressed, it any
 */
int get_char();

} // curses
} // chip8curses
