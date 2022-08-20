#ifndef BOOKING_HEADER
#define BOOKING_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

FILE *input_file;
char *newcode;

void loadfile();
void addTaiwanCity();

void menu();
void Booking();
void Cancellation();
void Record();
void Checkcode();
void Amendment();
void Checkfare();

typedef struct city City;
typedef struct passenger Passenger;
typedef struct citylist Citylist;
typedef struct passengerlist Passengerlist;

Citylist *citylist;
Passengerlist *passengerlist;

City *createcity(int No, char *City, int fare);
Citylist *makecitylist();
void addcity(int No, char *City, int fare);
void displayallcity();
int calticketprice(int from, int to);
char *findcity(int findNo);

Passenger *createpassenger(char *code, char *userID,
                           int station_from, int station_to, char *carriage,
                           char *seat, char *date, char *time, char *type, int cost);
Passengerlist *makepassengerlist();
char *addpassenger(char *userID,
                   int station_from, int station_to, char *carriage,
                   char *seat, char *date, char *time, char *type, int cost);
void gen_code(char **code);
void displaypassenger();
void getpassenger(char *code);
void deletepassenger(char *code);
void getbookingcode(char *userID);
bool check_passenger_exist(char *code);
void change_passenger_datetime(char *code, char *date, char *time);
void change_passenger_typeprice(char *code, char *type, int cost);
void destroy_passenger_list();

int get_station_from(char *code);
int get_station_to(char *code);

#endif