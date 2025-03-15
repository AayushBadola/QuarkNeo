#include "quark.h"
#include <stdio.h>

int main(void)
{
    print_blue("Welcome to the Quark Library Example Program!\n\n");
    
    // Demonstrate input functions
    string name = get_string("What is your name? ");
    print_green("Hello, %s!\n", name);
    
    int age = get_int("How old are you? ");
    if (age < 0)
    {
        error("Age cannot be negative");
    }
    
    print_yellow("You are %d years old.\n", age);
    
    double height = get_double("Enter your height in meters: ");
    print_green("Your height is %.2f meters.\n", height);
    
    // Cleanup
    free(name);
    
    return 0;
}
