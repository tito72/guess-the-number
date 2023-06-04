#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOWER_LIMIT 1U
#define UPPER_LIMIT 100U
#define MAX_ATTEMPTS 10U
#define MAX_INPUT_LENGTH 11U
#define MAX_SECRET_LENGTH 4U  // Maximum number of digits in UPPER_LIMIT

void numberToString(unsigned int number, char* str)
{
    (void)sprintf(str, "%u", number);
}

int main(void)
{
    unsigned int secret_number = 0U;
    unsigned int user_guess = 0U;
    unsigned int attempt_count = 0U;
    char user_input[MAX_INPUT_LENGTH] = {0};
    char secret_str[MAX_SECRET_LENGTH] = {0};
    char* end_ptr;

    /* Initializes random number generator */
    (void)srand((unsigned int)time(NULL));

    /* Get a random number between LOWER_LIMIT and UPPER_LIMIT */
    secret_number = ((unsigned int)rand() % UPPER_LIMIT) + LOWER_LIMIT;

    (void)puts("Welcome to Guess the Number game!");

    for(attempt_count = 0U; attempt_count < MAX_ATTEMPTS; ++attempt_count)
    {
        (void)puts("Enter your guess: ");

        /* Read input as a string */
        if (fgets(user_input, sizeof(user_input), stdin) != NULL)
        {
            /* Convert string to number */
            user_guess = (unsigned int)strtoul(user_input, &end_ptr, 10);

            /* Check if conversion was successful */
            if (*end_ptr != '\n' && *end_ptr != '\0')
            {
                (void)puts("Invalid input! Please enter a number.");
            }
            else if(user_guess < secret_number)
            {
                (void)puts("Too low! Try again.");
            }
            else if(user_guess > secret_number)
            {
                (void)puts("Too high! Try again.");
            }
            else
            {
                (void)puts("Congratulations! You've found the secret number.");
                break;
            }
        }
        else
        {
            (void)puts("Error reading input! Try again.");
        }
    }

    if(attempt_count == MAX_ATTEMPTS)
    {
        (void)puts("Sorry, you didn't guess the number in 10 attempts. The number was:");
        numberToString(secret_number, secret_str);
        (void)puts(secret_str);
    }

    return 0;
}
