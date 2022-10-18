#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

// In secondas.
unsigned int timer = 0;

#define MAX_TIME 250

// Function Prototypes.
unsigned int minutesToSeconds(unsigned int min);
unsigned int minutesLeft(unsigned int seconds);
unsigned int secondsLeft(unsigned int seconds);
void displayTimer(unsigned int timer);

int main(int argc, char *argv[])
{
    // Incorect number of arguments.
    if (argc != 2) 
    {
        printf("Usage: %s [minutes]\n", argv[0]);
        return 1;
    }

    // Convert input string to int.
    unsigned int interval = atoi(argv[1]);

    if (interval <= 0) 
    {
        printf("Arg must be a positive integer > 0.\n");
        return 2;
    }
    else if (interval > MAX_TIME)
    {
        printf("Cannot exceed the value of %i.\n", MAX_TIME);
        return 3;
    }
    
    // Convert interval into seconds.
    interval = minutesToSeconds(interval);

    // Get current timestamp in seconds.
    time_t currentTimestamp = time(NULL);

    // Set end of timer.
    time_t end = currentTimestamp + interval; 

    // Set timer.
    timer = (unsigned int) difftime(end, currentTimestamp); 

    while(currentTimestamp < end)
    {
        // Pause for 1 second.
        sleep(1);

        // Update timer
        timer = (unsigned int) difftime(end, currentTimestamp),

        // Display remaining time. 
        displayTimer(timer);
 
        // Update current timestamp.
        currentTimestamp = time(NULL);
    }

    // Send a notification to signal the timer has ended. 
    system("notify-send \" Well done! The session is over.\"");
    return 0;
}

// Converts minutes to seconds.
unsigned int minutesToSeconds(unsigned int min)
{
    return min * 60;
}

// Calculates remaining minutes.
unsigned int minutesLeft(unsigned int seconds)
{
    return seconds / 60;
}

// Calculates the remaining seconds.
unsigned int secondsLeft(unsigned int seconds)
{
    return seconds % 60;
}

// Prints the timer on the console.
void displayTimer(unsigned int timer)
{
    unsigned int minutes = minutesLeft(timer);
    unsigned int seconds = secondsLeft(timer);

    // Tomato emoji unicode caracter.
    printf(" \U0001F345 ");

    // Print timer in mm:ss format. 
    printf("%02d:%02d\n", minutes, seconds);

    // Move cursor up one line.
    printf("\33[A");

    // Clear line.
    printf("\33[2K\r");
}
