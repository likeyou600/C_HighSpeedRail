#include "main.h"

void Booking()
{
    char *userID = malloc(0);
    int station_from;
    int station_to;
    int int_carriage;
    char *char_carriage = malloc(0);
    int int_seat;
    char *char_seat = malloc(0);
    char *date = malloc(0);
    char *time = malloc(0);
    char *type = malloc(0);
    char *outtype = malloc(300 * sizeof(char));
    memset(outtype, 0x00, 300);

    char defaultcheck = 'Y';
    char check = 'Y';

    printf("Please enter your ID: ");
    fscanf(input_file, "%s", userID);
    printf("%s\r\n", userID);

    printf("\r\n");
    printf("Please enter the starting and ending stations according to the county and city numbers\r\n");
    displayallcity(citylist);
    printf("\r\n");
    printf("Departure Station/Arrival Station >> ");

    fscanf(input_file, "%d   %d", &station_from, &station_to);
    printf("%d %d\r\n", station_from, station_to);

    printf("\r\n");
    printf("Please enter the type of car 1. Standard class 2. Business class >> ");
    fscanf(input_file, "%d", &int_carriage);
    printf("%d\r\n", int_carriage);
    switch (int_carriage)
    {
    case 1:
        char_carriage = "Standard class";
        break;
    case 2:
        char_carriage = "Business class";
        break;

    default:
        break;
    }
    printf("\r\n");

    printf("Seat preference 1. None 2. Window priority 3. Aisle priority >> ");
    fscanf(input_file, "%d", &int_seat);
    printf("%d\r\n", int_seat);
    switch (int_seat)
    {
    case 1:
        char_seat = "None";
        break;
    case 2:
        char_seat = "Window priority";
        break;
    case 3:
        char_seat = "Aisle priority";
        break;
    default:
        break;
    }
    printf("\r\n");

    printf("Date (Year/Month/Day) >> ");
    fscanf(input_file, "%s", date);
    printf("%s\r\n", date);
    printf("\r\n");

    printf("Time (hour:minute) >> ");
    fscanf(input_file, "%s", time);
    printf("%s\r\n", time);
    printf("\r\n");

    double price = calticketprice(station_from, station_to);
    int cost = 0;
    while (check == defaultcheck)
    {
        printf("Please enter the type and number of tickets according to the following numbers (ex: Please enter 1/2 for two full tickets)\r\n");
        printf("1. Full ticket (original price) 2. Child ticket (6-11 years old) (40%% off) 3. Love ticket (50%% off) 4. Senior ticket (over 65 years old) (40%% off) 5. College student discount ticket (20%% off)\r\n");
        printf("Please enter >> ");
        fscanf(input_file, "%s", type);
        printf("%s\r\n", type);

        strcat(outtype, &type[2]);
        int count = atoi(&type[2]);

        switch (type[0] - '0')
        {
        case 1:
            strcat(outtype, " full tickets,");
            cost += price * count;
            break;
        case 2:
            strcat(outtype, " child ticket (6-11 years old),");
            cost += ceil((price * 0.6) * count);

            break;
        case 3:
            strcat(outtype, " love ticket,");
            cost += ceil((price * 0.5) * count);

            break;
        case 4:
            strcat(outtype, " senior ticket (over 65 years old),");
            cost += ceil((price * 0.6) * count);

            break;
        case 5:
            strcat(outtype, " college student discount ticket,");
            cost += ceil((price * 0.8) * count);

            break;

        default:
            break;
        }
        printf("\r\n");
        printf("Do you want to enter other ticket types (Y/N) >> ");
        fscanf(input_file, " %c", &check);
        printf("%c\r\n", check);
        printf("\r\n");
    }

    printf("Your booking information is as follows:\r\n");

    char *station_from_name = findcity(station_from);
    char *station_to_name = findcity(station_to);

    printf("Departure station: %s to %s\r\n", station_from_name, station_to_name);
    printf("Type of carriage: %s\r\n", char_carriage);
    printf("Seat preference: %s\r\n", char_seat);
    printf("Date/Time: %s %s\r\n", date, time);
    printf("Number of tickets: %s\r\n", outtype);
    printf("Cost: TW %d\r\n", cost);
    printf("Are you sure you want to book a ticket (Y/N) >> ");
    fscanf(input_file, " %c", &check);
    printf("%c ", check);
    printf("//If you press N, the ticket will be booked from the beginning\r\n");
    printf("\r\n");

    if (check == 'N' || check == 'n')
        return;
    else if (check == 'Y' || check == 'y')
    {
        char *code = addpassenger(userID,
                                  station_from, station_to, char_carriage,
                                  char_seat, date, time, outtype, cost);

        printf("Booking is successful! Your booking code is %s \r\n", code);
    }
    else
    {
        printf("noinput \r\n");
    }
    printf("-------\r\n");
    printf("\r\n");
}