#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float lift_a_car(const int stick_length, const int human_weight, const int car_weight) {

    float position;
    position = ( stick_length * human_weight ) / (float) ( human_weight + car_weight );

    position = position + .005;
    position = trunc(position * 100.0) / 100.0;
    return position;
}

float unit_price(const float pack_price, const int rolls_count, const int pieces_count) {

    int total_amount;
    total_amount = rolls_count * pieces_count;

    float single_price;
    single_price = (float)( pack_price / total_amount ) * 100;

    single_price = single_price + .005;
    single_price = trunc(single_price * 100.0) / 100.0;
    return single_price;
}

int bank_notes(const int price) {

    int notes_needed = 0;
    int cost = price;

    while ( cost >= 200 ) {
        if ( cost < 200) {
            break;
        }
        cost = cost - 200;
        notes_needed++;
    }

    while ( cost >= 100 ) {
        if ( cost < 100) {
            break;
        }
        cost = cost - 100;
        notes_needed++;
    }

    while ( cost >= 50 ) {
        if ( cost < 50) {
            break;
        }
        cost = cost - 50;
        notes_needed++;
    }

    while ( cost >= 20 ) {
        if ( cost < 20) {
            break;
        }
        cost = cost - 20;
        notes_needed++;
    }

    while ( cost >= 10 ) {
        if ( cost < 10) {
            break;
        }
        cost = cost - 10;
        notes_needed++;
    }

    if ( cost <= 10 && cost % 10 != 0 ) {
        return -1;
    }
    else {
        return notes_needed;
    }

}

int euler(const int n) {

    int result = n;
    int a = n; 

    for ( int i = 2; i * i <= a; i++ ) {
        if ( a % i == 0 ) {
            while ( a % i == 0 )
                a /= i;
            result -= result / i;
        }
    }

    if ( a > 1 ) {
        result -= result / a;
    }
    return result;

}

int find_missing_number(const int n, const int arr[]) {

    int sum = 0;
    int i; 
    int result;

    for( i = 0; i < n; i++ ) {
        sum = sum + arr[i];
    }
   
    result = (n * ( n+1 ) ) / 2 - sum;
    return result;

}

unsigned long sum_squared(const int line) {

    unsigned long result = 0; 
    unsigned long coef = 1;
    int i;

    for ( i = 0; i < line; i++) {
        result += coef * coef;
        coef = coef * ( line - i ) / ( i + 1 );
    }

    result += 1;
    return result;

}

int array_min(const int input_array[], const int array_size) {

    int min = 1;

    for ( int i = 0; i < array_size; i++) {
        if ( min > input_array[i] ) {
            min = input_array[i];
        }
        if ( array_size == input_array[i] ) {
            break;
        }
    }

    return min;

}

int array_max(const int input_array[], const int array_size) {

    int max = 1;

    if ( input_array == NULL  ) {
        return -1;
    }

    for ( int i = 0; i < array_size; i++) {
        if ( max < input_array[i] ) {
            max = input_array[i];
        }
        if ( array_size == input_array[i] ) {
            break;
        }
    }

    return max;

}

int factorize_count(const int n) {

    int amount = 1;
    int copy = n;

    for ( int i = 2; i < n; i++ ) {
        if ( copy % i == 0 ) {
            while ( copy % i == 0 ) {
                copy /= i;
                if ( copy == 1 ) {
                    break;
                }
            }
            if ( copy == 1 ) {
                break;
            }
            amount++;
        }
        if ( copy == 1 ) {
            break;
        }
    }

    return amount;

}

void podium(const int n, int arr[]) {

    int m = n;

    arr[0]=0;
    arr[1]=0;
    arr[2]=0;

    if ( n < 6 ) {
        return;
    }

    if ( m == 6 ) {
        
        arr[0]=2;
        arr[1]=3;
        arr[2]=1;
        return;

    }

    while ( m > 0 ) {
        arr[1]++;
        m--;
        if ( m > 0 ) {
            arr[0]++;
            m--;
            if ( m > 0 ) {
                arr[2]++;
                m--;
            }
        }
    }

    if ( n % 2 == 0 ) {
        arr[0] += 1;
        arr[1] += 1;
        arr[2] -= 2;
    }
    
    if ( n % 2 != 0 ) {
        arr[0] += 1;
        arr[1] += 2;
        arr[2] -= 3;
    }


}

int main() {



}