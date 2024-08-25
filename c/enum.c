#include <stdio.h>

// Defining an enum to represent days of the week
enum Day {
    SUNDAY,    // 0
    MONDAY,    // 1
    TUESDAY,   // 2
    WEDNESDAY, // 3
    THURSDAY,  // 4
    FRIDAY,    // 5
    SATURDAY   // 6
};

int main() {
    // Declaring a variable of enum type
    enum Day today;

    // Assigning a value to the enum variable
    today = WEDNESDAY;

    // Checking the value of the enum variable
    if (today == WEDNESDAY) {
        printf("It's Wednesday!\n");
    }

    // Print the numeric value of the enum
    printf("Numeric value of today: %d\n", today);

    return 0;
}
