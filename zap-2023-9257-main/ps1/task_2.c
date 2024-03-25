#include <superkarel.h>
void travel_inside();
void travel_outside();
void turn_right();


int main() {
    turn_on("task_2.kw");
    
    set_step_delay(100);
    
    while ( beepers_in_bag() == false ) {
        if ( beepers_present() ) {
            pick_beeper();
            break;
        }
        travel_inside();
    }
    
    while ( beepers_in_bag() ) {
        if ( front_is_blocked() && right_is_blocked() && left_is_blocked() && facing_west() ) {
            turn_right();
            if ( left_is_blocked() && right_is_clear() && facing_north() ) {
                turn_right();
                while ( front_is_clear() ) {
                    if ( front_is_blocked() && right_is_clear() ) {
                        turn_right();
                    }
                    step();
                }
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
            }
        } 
        travel_outside();
    }
    turn_right();
    turn_off();
} 

void travel_inside() {
    while ( front_is_clear() ) {
        if ( front_is_blocked() || beepers_present() ) {
            break;
        }
        step();
    }

    while ( front_is_blocked() ) {
        turn_left();
        break;
    }
}

void travel_outside() {
    while ( front_is_clear() ) {
        if ( front_is_blocked() ) {
            break;
        }
        step();
    }

    while ( front_is_blocked() ) {
        if ( front_is_blocked() && right_is_blocked() && left_is_blocked() && facing_west() ) {
           break;
        }
        turn_right();
        break;
    }
}


void turn_right() {
    turn_left();
    turn_left();
    turn_left();
}
