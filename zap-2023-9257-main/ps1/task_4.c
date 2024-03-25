#include <superkarel.h>
void turn_right();
void travel();
void fix_pillar();
void fix_firstpillar();

int main() {
    turn_on("task_4.kw");
    set_step_delay(100);

    fix_firstpillar();
    travel();
    fix_pillar();
    travel();
    fix_pillar();
    travel();
    fix_pillar();

    if ( front_is_blocked() && facing_north() && right_is_clear() ) {
                    turn_left();
                    turn_left();
                    while ( front_is_clear() ) {
                       if ( front_is_blocked() ) {
                         turn_left();
                         break;
                       }
                       step();
                    }
    }

    turn_left();
    turn_off();
} 

void fix_firstpillar() {
    turn_left();
    while ( front_is_clear() ) {
        if ( front_is_blocked() ) {
            break;
        }
        if ( !beepers_present() ) {
            put_beeper();
        }
        step();
    }
    if ( front_is_blocked() ) {
        turn_right();
        step();
    }
}

void fix_pillar() { 
    if ( left_is_blocked() && front_is_blocked() && facing_east() ) {
            turn_right();
            step();
            turn_left();
            step();
    }

    while ( !facing_south() ) {
        if ( facing_south() && front_is_blocked() ) {
            break;
        }
        if ( facing_south() && front_is_clear() ) {
            break;
        }
        turn_left();
    }

    while ( front_is_clear() ) {
        if ( !beepers_present() ) {
            put_beeper();
        }
        if ( front_is_blocked() && facing_south() ) {
            if ( !beepers_present() ) {
                put_beeper();
            }
            break;
        }
        step();
    }
   
    if ( front_is_blocked() && facing_south() ) {
            if ( !beepers_present() ) {
                put_beeper();
            }
            turn_left();
            turn_left();
            while ( front_is_clear() ) {
                if ( front_is_blocked() && facing_north() ) {
                    break;
                }
                if ( front_is_blocked() && right_is_blocked() ) {
                    break;
                }
                step();
            }
    }

    if ( facing_north() && front_is_blocked() && !right_is_blocked() ) {
        turn_right();
        step();
        if ( front_is_blocked() ) {
            turn_left();
            turn_left();
            step();
            turn_left();
            while ( front_is_clear() ) {
                  if ( front_is_blocked() ) {
                         return;
                  }
                  step();
            }
    }
   }
   if ( front_is_blocked() && right_is_blocked() ) {
                    if ( !beepers_present() ) {
                        put_beeper();
                    }
                    turn_left();
                    turn_left();
                    while ( front_is_clear() ) {
                       if ( front_is_blocked() ) {
                         turn_left();
                         return;
                       }
                       step();
                    }
    }
}

void travel() {
    while ( left_is_clear() ) {
        if ( left_is_blocked() || front_is_blocked() ) {
            break;
        }
        step();
    }
}

void turn_right() {
    turn_left();
    turn_left();
    turn_left();
}

