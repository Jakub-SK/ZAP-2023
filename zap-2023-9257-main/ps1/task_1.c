#include <superkarel.h>

void turn_right();
void climb_over_right();
void climb_over_left();
void park_it();

int main() {
   turn_on("task_1.kw");
    
   set_step_delay(100);
   
   while ( front_is_clear() ) {
       if( front_is_blocked() ) {
            break;
       }
        step();
   }

   while ( front_is_blocked() ) {
        if ( beepers_present() ) {
            break;
        }
        climb_over_right();
   }

   while ( beepers_present() ) {
        pick_beeper();
        while ( front_is_clear() ) {
            if( front_is_blocked() ) {
                break;
            }
            step();
        }
        while ( front_is_blocked() )  {
            if ( facing_north() && left_is_blocked() ) {
                break;
            }
            climb_over_left();
        }
   }
   
   park_it();
   turn_right();
   turn_off();

} 

void park_it() {
            if ( left_is_blocked() && front_is_blocked() && facing_north() ) {
                turn_left();
                turn_left();
                while( front_is_clear() ) {
                    if ( front_is_blocked() ) {
                        break;
                    }
                    step();
                }
            }
}

void climb_over_right() {
    if ( beepers_present() ) {
                pick_beeper();
                return;
    }

    if ( facing_south() ) {
        turn_left();
        turn_left();
    }
    if ( facing_east() ) {
        turn_left();
    }

    while ( right_is_blocked() && !front_is_blocked() ) {
        if ( right_is_clear() || front_is_blocked() ) {
            turn_left();
            break;
        }
        step();
    }
    while ( facing_north() && right_is_clear() ) {
        turn_left();
        turn_left();
        turn_left();
        step();
        while ( right_is_blocked() ) {
            if ( front_is_blocked() ) {
                break;
            }
            step();
        }
        break;
    }
    while ( facing_east() && right_is_clear() ) {
        turn_left();
        turn_left();
        turn_left();
        step();
        while ( right_is_blocked() ) {
            if ( front_is_blocked() ) {
                return;
            }
            step();
        }
        break;
    }

    while ( facing_east() && front_is_clear() && right_is_blocked() ) {
        if ( front_is_blocked() ) {
            break;
        }
        step();
    }

}

void climb_over_left() {
    if ( left_is_blocked() && front_is_blocked() && facing_north() ) {
                park_it();
    }
    if ( left_is_blocked() && front_is_blocked() && right_is_blocked() && facing_south() ) {
        turn_left();
        turn_left();
        turn_left();
        while ( front_is_clear() ) {
            if ( front_is_blocked() && left_is_clear() ) {
                turn_left();
                turn_left();
                while ( front_is_clear() ) {
                    if ( front_is_blocked() ) {
                        break;
                    }
                    step();
                }
                break;
            }
            if ( front_is_blocked() && left_is_blocked() ) {
                park_it();
                break;
            }
            step();
        }
    }
    if ( facing_south() ) {
        turn_left();
        turn_left();
    }
    if ( facing_west() ) {
        turn_left();
        turn_left();
        turn_left();
    }
    
    if ( facing_east() ) {
        turn_left();
        turn_left();
    }

    while ( left_is_blocked() ) {
        if ( front_is_blocked() ) {
            break;
        }
        if ( left_is_clear() ) {
            break;
        }
        step();
    }
    while ( facing_north() && left_is_clear() ) {
        if ( left_is_blocked() && front_is_blocked() && facing_north() ) {
                break;
        }
        turn_left();
        step();
        while ( left_is_blocked() && front_is_clear() ) {
            step();
        }
        break;
    }
    while ( facing_west() && left_is_clear() ) {
        turn_left();
        step();
        while ( left_is_blocked() ) {
            if ( front_is_blocked() ) {
                break;
            }
            step();
        }
        break;
    }

}

void turn_right() {
	turn_left();
	turn_left();
	turn_left();
}
