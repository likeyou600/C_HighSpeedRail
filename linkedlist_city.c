#include "main.h"

void addTaiwanCity()
{
    addcity(1, "Nangang", 0);
    addcity(2, "Taipei", 40);
    addcity(3, "Banqiao", 70);
    addcity(4, "Taoyuan", 200);
    addcity(5, "Hsinchu", 330);
    addcity(6, "Miaoli", 480);
    addcity(7, "Taichung", 750);
    addcity(8, "Changhua", 870);
    addcity(9, "Yunlin", 970);
    addcity(10, "Chiayi", 1120);
    addcity(11, "Tainan", 1390);
    addcity(12, "Kaohsiung", 1530);
}

struct city
{
    int No;
    char *cityname;
    int fare;
    struct city *next;
};
struct citylist
{
    City *head;
};

City *createcity(int No, char *cityname, int fare)
{
    City *newCity = malloc(sizeof(City));
    if (!newCity)
    {
        return NULL;
    }
    newCity->No = No;
    newCity->cityname = cityname;
    newCity->fare = fare;

    newCity->next = NULL;
    return newCity;
}
Citylist *makecitylist()
{
    Citylist *citylist = malloc(sizeof(Citylist));
    if (!citylist)
    {
        return NULL;
    }
    citylist->head = NULL;
    return citylist;
}

void addcity(int No, char *cityname, int fare)
{
    City *current = NULL;
    if (citylist->head == NULL)
    {
        citylist->head = createcity(No, cityname, fare);
    }
    else
    {
        current = citylist->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = createcity(No, cityname, fare);
    }
}
void print_allcity()
{
    City *current = citylist->head;
    if (citylist->head == NULL)
        return;

    for (; current != NULL; current = current->next)
    {
        int No = current->No;
        if (No == 7)
            printf("\r\n");
        printf("%d. %s ", current->No, current->cityname);
    }
}
int calticketprice(int from, int to)
{
    City *current = citylist->head;
    if (citylist->head == NULL)
        return 0;

    int sum = 0;
    for (; current != NULL; current = current->next)
    {
        int No = current->No;
        if (No == from)
            sum += current->fare;
        if (No == to)
            sum -= current->fare;
    }
    if (sum < 0)
        sum = -sum;
    return sum;
}
char *findcity(int findNo)
{
    City *current = citylist->head;
    if (citylist->head == NULL)
        return "";

    for (; current != NULL; current = current->next)
    {
        int No = current->No;
        if (No == findNo)
            return current->cityname;       
    }
}