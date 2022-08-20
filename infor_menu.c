#include "main.h"

void menu(int select)
{

    printf("(1) Booking\r\n");
    printf("(2) Cancellation of booked tickets\r\n");
    printf("(3) Booking record query\r\n");
    printf("(4) Check the booking code\r\n");
    printf("(5) Amendment of reservation record\r\n");
    printf("(6) Check the fare\r\n");
    printf("(7) End the booking system\r\n");
    printf("Please enter function >> ");

    printf("%d\r\n", select);
    printf("\r\n");
    switch (select)
    {
    case 1:
        Booking();
        break;
    case 2:
        Cancellation();
        break;
    case 3:
        Record();
        break;
    case 4:
        Checkcode();
        break;
    case 5:
        Amendment();
        break;
    case 6:
        Checkfare();
        break;
    case 7:
        break;
    default:
        break;
    }

}
void Cancellation()
{
    printf("Please enter the booking code: ");
    char *code = malloc(0);
    fscanf(input_file, "%s", code);
    printf("%s\r\n", code);
    printf("\r\n");
    if (!check_passenger_exist(code))
    {
        printf("%s not exists,the last generate code is %s , will use the last code\r\n", code, newcode);
        code = strdup(newcode);
    }

    getpassenger(code);
    printf("Are you sure you want to cancel the reservation (Y/N) >> ");

    char check = ' ';
    fscanf(input_file, " %c", &check);
    printf("%c ", check);
    printf("\r\n");

    if (check == 'N' || check == 'n')
        return;
    else if (check == 'Y' || check == 'y')
    {
        // deletepassenger(code);
        printf("\r\n");
        printf("The reservation record has been cancelled!\r\n");
        printf("\r\n");
    }
    else
    {
        printf("noinput \r\n");
    }
}
void Record()
{
    printf("Please enter the booking code: ");
    char *code = malloc(0);
    fscanf(input_file, "%s", code);
    printf("%s\r\n", code);
    printf("\r\n");
    if (!check_passenger_exist(code))
    {
        printf("%s not exists,the last generate code is %s , will use the last code\r\n", code, newcode);
        code = strdup(newcode);
    }
    getpassenger(code);
    printf("\r\n");
    printf("Press any key to continue...\r\n");
    printf("\r\n");
    printf("------\r\n");
}
void Checkcode()
{
    printf("Please enter your ID: ");
    char *userID = malloc(0);
    fscanf(input_file, "%s", userID);
    printf("%s\r\n", userID);
    printf("\r\n");
    getbookingcode(userID);
    printf("\r\n");
    printf("Press any key to continue...\r\n");
    printf("\r\n");
    printf("------\r\n");
}
void Amendment()
{
    printf("Please enter the booking code: ");
    char *code = malloc(0);
    fscanf(input_file, "%s", code);
    printf("%s\r\n", code);
    if (!check_passenger_exist(code))
    {
        printf("%s not exists,the last generate code is %s , will use the last code \r\n", code, newcode);
        printf("\r\n");

        code = strdup(newcode);
    }
    printf("Which do you want to modify ? 1. Ticket (type and number) 2. Date >> ");

    int modify = 0;
    fscanf(input_file, "%d", &modify);
    printf("%d\r\n", modify);
    char *date = malloc(0);
    char *time = malloc(0);
    char defaultcheck = 'Y';
    char check = 'Y';
    char *outtype = malloc(300 * sizeof(char));
    memset(outtype, 0x00, 300);
    char *type = malloc(0);
    double price = calticketprice(get_station_from(code), get_station_to(code));
    int cost = 0;
    switch (modify)
    {
    case 1:

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
        printf("Confirm (Y/N) >> ");
        char check;
        fscanf(input_file, " %c", &check);
        printf("%c ", check);
        printf("\r\n");
        if (check == 'N' || check == 'n')
            return;
        else if (check == 'Y' || check == 'y')
        {
            change_passenger_typeprice(code, outtype, cost);

            getpassenger(code);
            printf("\r\n");
            printf("Press any key to continue...\r\n");
            printf("\r\n");
            printf("------\r\n");
        }
        else
        {
            printf("noinput \r\n");
        }

        break;
    case 2:
        printf("New Date (Year/Month/Day) >> ");
        fscanf(input_file, "%s", date);
        printf("%s\r\n", date);
        printf("\r\n");

        printf("New Time (hour:minute) >> ");
        fscanf(input_file, "%s", time);
        printf("%s\r\n", time);
        printf("\r\n");
        printf("Confirm (Y/N) >> ");

        fscanf(input_file, " %c", &check);
        printf("%c ", check);
        printf("\r\n");
        if (check == 'N' || check == 'n')
            return;
        else if (check == 'Y' || check == 'y')
        {
            change_passenger_datetime(code, date, time);

            getpassenger(code);
            printf("\r\n");
            printf("Press any key to continue...\r\n");
            printf("\r\n");
            printf("------\r\n");
        }
        else
        {
            printf("noinput \r\n");
        }
        break;
    default:
        break;
    }
}

void Checkfare()
{
    int station_from;
    int station_to;

    int type = 0;
    char *text_type = malloc(0);
    int sum = 0;
    printf("Please enter the starting and ending stations according to the county and city numbers\r\n");
    displayallcity(citylist);
    printf("\r\n");
    printf("Departure Station/Arrival Station >> ");

    fscanf(input_file, "%d   %d", &station_from, &station_to);
    printf("%d %d\r\n", station_from, station_to);
    printf("\r\n");

    printf("Please enter the type of tickets according to the following numbers\r\n");
    printf("1. Full ticket (original price) 2. Child ticket (6-11 years old) (40%% off) 3. Love ticket (50%% off) 4. Senior ticket (over 65 years old) (40%% off) 5. College student discount ticket (20%% off)\r\n");
    printf("Please enter >> ");
    fscanf(input_file, "%d", &type);
    printf("%d\r\n", type);

    double price = calticketprice(station_from, station_to);

    switch (type)
    {
    case 1:
        sum = price;
        text_type = "Full ticket";
        break;
    case 2:
        sum = ceil(price * 0.6);
        text_type = "Child ticket";
        break;
    case 3:
        sum = ceil(price * 0.5);
        text_type = "Love ticket";
        break;
    case 4:
        sum = ceil(price * 0.6);
        text_type = "Senior ticket";
        break;
    case 5:
        sum = ceil(price * 0.8);
        text_type = "College student discount ticket";
        break;

    default:
        break;
    }
    char *station_from_name = findcity(station_from);
    char *station_to_name = findcity(station_to);
    printf("The %s from %s to %s is TW %d \r\n", text_type, station_from_name, station_to_name, sum);
    printf("\r\n");
    printf("Press any key to continue...\r\n");
    printf("\r\n");
    printf("------\r\n");
}