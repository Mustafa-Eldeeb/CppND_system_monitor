#include "ncurses_display.h"
#include "system.h"

int main() {
  //int num_processes = 20; 
  System system;
  NCursesDisplay::Display(system,30);
}