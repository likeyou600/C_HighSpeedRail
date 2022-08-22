#include "main.h"

struct passenger
{
    char *code;
    char *userID;
    int station_from;
    int station_to;
    char *carriage;
    char *seat;
    char *date;
    char *time;
    char *type;
    int cost;
    struct passenger *next;
};
struct passengerlist
{
    Passenger *head;
};
Passenger *createpassenger(char *code, char *userID,
                           int station_from, int station_to, char *carriage,
                           char *seat, char *date, char *time, char *type, int cost)
{
    Passenger *newPassenger = malloc(sizeof(Passenger));
    if (!newPassenger)
    {
        return NULL;
    }
    newPassenger->code = code;
    newPassenger->userID = userID;
    newPassenger->station_from = station_from;
    newPassenger->station_to = station_to;
    newPassenger->carriage = carriage;
    newPassenger->seat = seat;
    newPassenger->date = date;
    newPassenger->time = time;
    newPassenger->type = type;
    newPassenger->cost = cost;

    newPassenger->next = NULL;
    return newPassenger;
}
Passengerlist *makepassengerlist()
{
    Passengerlist *passengerlist = malloc(sizeof(Passengerlist));
    if (!passengerlist)
    {
        return NULL;
    }
    passengerlist->head = NULL;
    return passengerlist;
}

char *addpassenger(char *userID,
                   int station_from, int station_to, char *carriage,
                   char *seat, char *date, char *time, char *type, int cost)
{
    char *code;
    code = "9527";
    gen_code(&code); //自動更新流水號

    Passenger *current = NULL;
    if (passengerlist->head == NULL)
    {
        passengerlist->head = createpassenger(code, userID,
                                              station_from, station_to, carriage,
                                              seat, date, time, type, cost);
    }
    else
    {
        current = passengerlist->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = createpassenger(code, userID,
                                        station_from, station_to, carriage,
                                        seat, date, time, type, cost);
    }
    return code;
}

//產生流水號
void gen_code(char **code)
{
    char v[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    static char buf[6] = {0};
    srand(time(NULL));

    for (int i = 0; i < 6; ++i)
    {
        buf[i] = v[rand() % 16];
    }
    buf[6] = '\0';
    newcode = buf;
    *code = buf;
}
void print_passenger_data(char *code)
{
    Passenger *current = passengerlist->head;
    if (passengerlist->head == NULL)
    {
        printf("couldn't find data\r\n");
        return;
    }
    bool check = false;
    for (; current != NULL; current = current->next)
    {
        char *current_code = current->code;

        if (!strcmp(current_code, code))
        {
            printf("Your booking information is as follows:\r\n");

            char *station_from_name = findcity(current->station_from);
            char *station_to_name = findcity(current->station_to);

            printf("Departure station: %s to %s\r\n", station_from_name, station_to_name);
            printf("Type of carriage: %s\r\n", current->carriage);
            printf("Seat preference: %s\r\n", current->seat);
            printf("Date/Time: %s %s\r\n", current->date, current->time);
            printf("Number of tickets: %s\r\n", current->type);
            printf("Cost: TW %d\r\n", current->cost);

            check = true;
        }
    }
    if (check == false)
    {
        printf("couldn't find data\r\n");
    }
}

void deletepassenger(char *code)
{
    Passenger *current = passengerlist->head;
    Passenger *previous = current;
    while (current != NULL)
    {
        char *current_code = current->code;

        if (!strcmp(current_code, code))
        {
            previous->next = current->next;
            if (current == passengerlist->head)
                passengerlist->head = current->next;
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}
void getbookingcode(char *userID)
{
    Passenger *current = passengerlist->head;
    if (passengerlist->head == NULL)
    {
        printf("couldn't find data\r\n");
        return;
    }
    bool check = false;
    char code_s[200] = "";

    for (; current != NULL; current = current->next)
    {
        char *current_userID = current->userID;

        if (!strcmp(current_userID, userID))
        {
            strcat(code_s, current->code);
            strcat(code_s, " , ");

            check = true;
        }
    }
    if (check == false)
    {
        printf("couldn't find data\r\n");
    }
    else
    {
        printf("Your booking code: %s\r\n", code_s);
    }
}
void change_passenger_datetime(char *code, char *date, char *time)
{
    Passenger *current = passengerlist->head;
    if (passengerlist->head == NULL)
    {
        return;
    }
    bool check = false;
    for (; current != NULL; current = current->next)
    {
        char *current_code = current->code;

        if (!strcmp(current_code, code))
        {
            current->date = date;
            current->time = time;
        }
    }
}
void change_passenger_typeprice(char *code, char *type, int cost)
{
    Passenger *current = passengerlist->head;
    if (passengerlist->head == NULL)
    {
        return;
    }
    bool check = false;
    for (; current != NULL; current = current->next)
    {
        char *current_code = current->code;

        if (!strcmp(current_code, code))
        {
            current->type = type;
            current->cost = cost;
        }
    }
}

bool check_passenger_exist(char *code)
{
    bool check = false;
    Passenger *current = passengerlist->head;
    if (passengerlist->head == NULL)
    {
        return false;
    }
    for (; current != NULL; current = current->next)
    {
        char *current_code = current->code;

        if (!strcmp(current_code, code))
        {
            check = true;
        }
    }
    if (check == false)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int get_station_from(char *code)
{
    Passenger *current = passengerlist->head;
    if (passengerlist->head == NULL)
        return 0;

    for (; current != NULL; current = current->next)
    {
        char *current_code = current->code;

        if (!strcmp(current_code, code))
        {
            return current->station_from;
        }
    }
}

int get_station_to(char *code)
{
    Passenger *current = passengerlist->head;
    if (passengerlist->head == NULL)
        return 0;

    for (; current != NULL; current = current->next)
    {
        char *current_code = current->code;

        if (!strcmp(current_code, code))
        {
            return current->station_to;
        }
    }
}
