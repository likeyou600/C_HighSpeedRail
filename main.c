#include "main.h"

int main(void)
{
    citylist = makecitylist();
    passengerlist = makepassengerlist();

    addTaiwanCity();

    loadfile();
    int select = 0;
    while (1)
    {
        fscanf(input_file, "%d", &select);
        menu(select);
        if (select == 7)
            break;
    }

    system("pause");
    return 0;
}

void loadfile()
{
    const char *filename = "inputFile.txt";

    input_file = fopen(filename, "r");
    rewind(input_file);
}