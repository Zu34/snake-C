
#include "game.h"
#include "input.h"
#include <stdlib.h>
#include <ncurses.h>

int main() {
    enable_raw_mode();
    init_game();
    run_game_loop();
    disable_raw_mode();
    return 0;
}
