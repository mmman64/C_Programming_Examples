#include <stdio.h>
#include <math.h>

// int toInt(float num);

int main(void)
{
    // declare variable for dollar amount
    float dollarAmount;
    // declare variable for converted dollar amount
    int centsAmount;

    // user must give a positive number
    do
    {
        printf("Please enter change owed in dollars: ");
        scanf("%f", &dollarAmount);
        centsAmount = (int)round(dollarAmount * 100.0);
    } while (dollarAmount <= 0);

    // declare and initialise coins used variable
    int coinsUsed = 0;

    // test change owed and deduct accordingly
    while (centsAmount >= 25)
    {
        coinsUsed++;
        centsAmount -= 25;
    }

    while (centsAmount >= 10)
    {
        coinsUsed++;
        centsAmount -= 10;
    }

    while (centsAmount >= 5)
    {
        coinsUsed++;
        centsAmount -= 5;
    }

    while (centsAmount > 0)
    {
        coinsUsed++;
        centsAmount -= 1;
    }

    // display coins used
    printf("%i\n", coinsUsed);

} // end
