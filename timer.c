#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

// In seconds
BYTE timer;

#define MAX_TIME 250

// Function Prototypes.
unsigned int minutesToSeconds(unsigned int min);
int minutesLeft(time_t start, time_t end);
int secondsLeft(time_t start, time_t end);
void displayTimer(struct timer t);

int main(int argc, char *argv[])
{
    if (argc != 2) // Incorrect number of arguments.
    {
        printf("Usage: %s [minutes]\n", argv[0]);
        return 1;
    }

    unsigned int interval = atoi(argv[1]);

    if (interval <= 0) // Check if argument [m] is a positive int.
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
    time_t currentTimestamp  = time(NULL);

    // Set end of timer.
    time_t end = currentTimestamp + interval; 

    // Set timer.
    struct timer pomodoro;
    pomodoro.minutes = minutesLeft(currentTimestamp, end);
    pomodoro.seconds = secondsLeft(currentTimestamp, end);

    while(currentTimestamp < end)
    {
        // Pause for 1 second.
        sleep(1);

        // Update timer
        pomodoro.minutes = minutesLeft(currentTimestamp, end);
        pomodoro.seconds = secondsLeft(currentTimestamp, end);

        // Display remaining minutes and seconds. 
        displayTimer(pomodoro);
 
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
int minutesLeft(time_t start, time_t end)
{
    // Get the difference between two timestamps in seconds.
    int  diff = (int) difftime(end, start);

    return diff / 60;
}

// Calculates the remaining seconds.
int secondsLeft(time_t start, time_t end)
{
    // Get the difference between two timestamps in seconds.
    int diff = (int) difftime(end, start);

    return diff % 60;
}

// Prints the timer on the console.
void displayTimer(struct timer t)
{
    // Tomato emoji unicode caracter.
    printf(" \U0001F345 ");

    // Print timer in mm:ss format. 
    printf("%02d:%02d\n", t.minutes, t.seconds);

    // Move cursor up one line.
    printf("\33[A");

    // Clear line.
    printf("\33[2K\r");
}
