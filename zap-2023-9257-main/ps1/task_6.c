#include <superkarel.h>

void turn_right();

int main() {
   turn_on("task_6.kw");
    
   set_step_delay(100);

   while ( !front_is_blocked())  {
   while ( !beepers_present() ) {
        if ( beepers_present() ) {
            break;
        }
        step();
   }

   while ( beepers_present() ) {
        if ( !beepers_present() ) {
            break;
        }
        while ( beepers_present() ) {
        if ( beepers_present() ) {
            pick_beeper();
            while ( !facing_north() ) {
                if ( facing_north() ) {
                    break;
                }
                turn_left();
            }
            if ( beepers_present() ) {
                pick_beeper();
                while ( !facing_west() ) {
                    if ( facing_west() ) {
                        break;
                    }
                    turn_left();
                }
                if ( beepers_present() ) {
                    pick_beeper();
                    while ( !facing_south() ) {
                        if ( facing_south() ) {
                           break;
                        }
                        turn_left();
                    }
                    if ( beepers_present() ) {
                        pick_beeper();
                        while ( !facing_east() ) {
                            if ( facing_east() ) {
                                break;
                            }
                            turn_left();
                        }
                        if ( beepers_present() ) {
                            pick_beeper();
                            turn_off();
                        }
                    }
                }
            }
        }

        break;
    }

   }
   }

}

void turn_right() {
	turn_left();
	turn_left();
	turn_left();
}

