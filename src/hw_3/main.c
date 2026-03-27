#include "func.h"
int main()
{
    InputData* data = readFromFile("example2.txt");
    if (data == NULL) {
        printf("Ошибка чтения файла\n");
        return 1;
    }
    algorithm(data);
    printResults(data);
    freeInputData(data);
    return 0;
}