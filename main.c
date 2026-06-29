#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include <windows.h>
#include<conio.h>
#include <time.h>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void showCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void showSplashScreen() {
    system("cls");
    hideCursor();

    const char* I[] = {
        "#########",
        "   #     ",
        "   #     ",
        "   #     ",
        "   #     ",
        "   #     ",
        "   #     ",
        "   #     ",
        "   #     ",
        "   #     ",
        "   #     ",
        "#########"
    };

    const char* V[] = {
        "#       #",
        "#       #",
        "#       #",
        "#       #",
        "#       #",
        "#       #",
        "#       #",
        " #     # ",
        "  #   #  ",
        "   # #   ",
        "    #    ",
        "    #    "
    };

    const char* T[] = {
        "#########",
        "    #    ",
        "    #    ",
        "    #    ",
        "    #    ",
        "    #    ",
        "    #    ",
        "    #    ",
        "    #    ",
        "    #    ",
        "    #    ",
        "    #    "
    };

    const char* D2[] = {
        " ####### ",
        "#       #",
        "       #",
        "      #",
        "     # ",
        "    # ",
        "   # ",
        "  # ",
        " # ",
        " # ",
        " ######### "
    };

    const char* D5[] = {
        " ####### ",
        "#       ",
        "#       ",
        "#       ",
        " ####### ",
        "       # ",
        "       # ",
        " ####### ",
        "       ",
        "       ",
        " "
    };

    const char* D3[] = {
        " ",
        "      ",
        "       ",
        "       ",
        " ####### ",
        "       # ",
        "       # ",
        " ####### ",
        "       # ",
        "       # ",
        " ####### "
    };

    int colors[] = { 12, 13, 14, 10, 11, 9, 13, 12, 14, 10 };
    int numColors = 10;

    for (int cycle = 0; cycle < 100; cycle++) {

        for (int i = 0; i < 12; i++) {
            int colorIndex = (cycle + i) % numColors;
            setColor(colors[colorIndex]);
            gotoxy(8, 5 + i);
            printf("%s", I[i]);
        }

        for (int i = 0; i < 12; i++) {
            int colorIndex = (cycle + i + 3) % numColors;
            setColor(colors[colorIndex]);
            gotoxy(20, 5 + i);
            printf("%s", V[i]);
        }

        for (int i = 0; i < 12; i++) {
            int colorIndex = (cycle + i + 6) % numColors;
            setColor(colors[colorIndex]);
            gotoxy(32, 5 + i);
            printf("%s", T[i]);
        }

        setColor(14);
        for (int i = 0; i < 9; i++) {
            gotoxy(44 + i, 11);
            printf("-");
        }

        for (int i = 0; i < 11; i++) {
            int colorIndex = (cycle + i + 9) % numColors;
            setColor(colors[colorIndex]);
            gotoxy(55, 5 + i);
            printf("%s", D2[i]);
        }

        for (int i = 0; i < 11; i++) {
            int colorIndex = (cycle + i + 12) % numColors;
            setColor(colors[colorIndex]);
            gotoxy(66, 5 + i);
            printf("%s", D5[i]);
        }

        for (int i = 0; i < 11; i++) {
            int colorIndex = (cycle + i + 15) % numColors;
            setColor(colors[colorIndex]);
            gotoxy(77, 5 + i);
            printf("%s", D3[i]);
        }

        setColor(8);
        for (int i = 0; i < 100; i++) {
            gotoxy(i, 0); printf("#");
            gotoxy(i, 23); printf("#");
        }
        for (int i = 1; i < 23; i++) {
            gotoxy(0, i); printf("#");
            gotoxy(99, i); printf("#");
        }

        setColor(11);
        gotoxy(28, 21);
        printf(">>> НАЖМИТЕ ЛЮБУЮ КЛАВИШУ <<<");

        Sleep(80);

        if (_kbhit()) {
            _getch();
            break;
        }
    }

    setColor(7);
    system("cls");
    showCursor();
}

struct Writer {
    char name[100];
    char bio[500];
    char years[50];
};

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand((unsigned int)time(NULL));

    struct Writer writers[100];
    int writerCount = 0;

    FILE* file;
    fopen_s(&file, "writers.txt", "r");

    if (file == NULL) {
        system("cls");
        printf("Файл не найден!\n");
        return 1;
    }

    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {

        line[strcspn(line, "\n")] = '\0';

        char* token = strtok(line, "|");

        char fullName[150] = "";

        if (token != NULL) {
            strcat(fullName, token);
            strcat(fullName, " ");
            token = strtok(NULL, "|");
        }

        if (token != NULL) {
            strcat(fullName, token);
            strcat(fullName, " ");
            token = strtok(NULL, "|");
        }

        if (token != NULL) {
            strcat(fullName, token);
            token = strtok(NULL, "|");
        }

        strcpy(writers[writerCount].name, fullName);

        if (token != NULL) {
            char yearsText[50];
            int birth = atoi(token);
            token = strtok(NULL, "|");
            if (token != NULL) {
                int death = atoi(token);
                sprintf_s(yearsText, sizeof(yearsText), "%d-%d", birth, death);
                strcpy(writers[writerCount].years, yearsText);
            }
            token = strtok(NULL, "|");
        }

        for (int i = 0; i < 2; i++) {
            if (token != NULL) token = strtok(NULL, "|");
        }

        if (token != NULL) {
            strcpy(writers[writerCount].bio, token);
        }

        writerCount++;
        if (writerCount >= 100) break;
    }

    fclose(file);

    int choice;

    do {
        system("cls");
        gotoxy(53, 4);
        printf("----------------\n");
        gotoxy(53, 5);
        printf("| ГЛАВНОЕ МЕНЮ:|\n");
        gotoxy(53, 6);
        printf("|              |\n");
        gotoxy(53, 7);
        printf("|  1. Заставка |\n");
        gotoxy(53, 8);
        printf("|  2. Задача   |\n");
        gotoxy(53, 9);
        printf("|  3. Об авторе|\n");
        gotoxy(53, 10);
        printf("|  4. Выход    |\n");
        gotoxy(53, 11);
        printf("----------------\n");
        gotoxy(55, 13);
        printf("Ваш выбор: ");
        scanf_s("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            showSplashScreen();
            break;

        case 2: {
            system("cls");
            int choice2;

            do {
                system("cls");
                gotoxy(53, 5);
                printf("ПОДМЕНЮ:\n");
                gotoxy(53, 7);
                printf("5. Поиск писателя\n");
                gotoxy(53, 8);
                printf("6. Список всех писателей\n");
                gotoxy(53, 9);
                printf("7. Добавить нового писателя\n");
                gotoxy(53, 10);
                printf("8. Выход\n");
                gotoxy(53, 12);
                printf("Ваш выбор: ");
                scanf_s("%d", &choice2);
                getchar();

                switch (choice2) {
                case 5: {
                    char search[100];
                    int found = 0;

                    system("cls");
                    gotoxy(45, 5);
                    printf("ПОИСК ПИСАТЕЛЯ");
                    gotoxy(45, 7);
                    printf("Введите фамилию или ФИО: ");

                    fgets(search, 100, stdin);
                    search[strlen(search) - 1] = '\0';

                    for (int i = 0; i < writerCount; i++) {
                        if (strstr(writers[i].name, search) != NULL) {
                            system("cls");
                            gotoxy(10, 5);
                            printf("РЕЗУЛЬТАТ ПОИСКА:");
                            gotoxy(10, 7);
                            printf("Писатель: %s", writers[i].name);
                            gotoxy(10, 8);
                            printf("Годы жизни: %s", writers[i].years);
                            gotoxy(10, 10);
                            printf("Биография:");
                            gotoxy(10, 11);
                            printf("%s", writers[i].bio);
                            found = 1;
                            break;
                        }
                    }

                    if (found == 0) {
                        gotoxy(45, 10);
                        printf("Писатель не найден!");
                    }

                    gotoxy(45, 20);
                    printf("Нажмите Enter...");
                    getchar();
                    getchar();
                    break;
                }
                case 6:
                    system("cls");
                    gotoxy(45, 5);
                    printf("СПИСОК ПИСАТЕЛЕЙ\n\n");
                    for (int i = 0; i < writerCount; i++) {
                        printf("%d. %s (%s)\n", i + 1, writers[i].name, writers[i].years);
                    }
                    printf("\nНажмите Enter...");
                    getchar();
                    getchar();
                    break;
                case 7:{
                    system("cls");
                    gotoxy(45, 5);
                    printf("ДОБАВЛЕНИЕ ПИСАТЕЛЯ");
                    if (writerCount >= 100) {
                        gotoxy(45, 7);
                        printf("Достигнут лимит писателей (100)!");
                        gotoxy(45, 20);
                        printf("Нажмите Enter...");
                        getchar();
                        getchar();
                        break;
                    }

                    char newName[100] = "";
                    char newYears[50] = "";
                    char newBio[500] = "";

                    gotoxy(45, 7);
                    printf("Введите ФИО писателя: ");
                    fgets(newName, sizeof(newName), stdin);
                    newName[strcspn(newName, "\n")] = '\0';

                    gotoxy(45, 8);
                    printf("Введите годы жизни (например, 1799-1837): ");
                    fgets(newYears, sizeof(newYears), stdin);
                    newYears[strcspn(newYears, "\n")] = '\0';

                    gotoxy(45, 9);
                    printf("Введите биографию писателя: ");
                    fgets(newBio, sizeof(newBio), stdin);
                    newBio[strcspn(newBio, "\n")] = '\0';
                    strcpy(writers[writerCount].name, newName);
                    strcpy(writers[writerCount].years, newYears);
                    strcpy(writers[writerCount].bio, newBio);
                    writerCount++;

                    FILE* fileAppend;
                    fopen_s(&fileAppend, "писатели-LINNaaa333.txt", "a");

                    if (fileAppend != NULL) {
                        char surname[50] = "", name[50] = "", patronymic[50] = "";

                        char tempName[100];
                        strcpy(tempName, newName);
                        char* token = strtok(tempName, " ");
                        if (token != NULL) {
                            strcpy(surname, token);
                            token = strtok(NULL, " ");
                            if (token != NULL) {
                                strcpy(name, token);
                                token = strtok(NULL, " ");
                                if (token != NULL) {
                                    strcpy(patronymic, token);
                                }
                            }
                        }

                        char birthYear[20] = "", deathYear[20] = "";
                        char tempYears[50];
                        strcpy(tempYears, newYears);
                        char* yearToken = strtok(tempYears, "-");
                        if (yearToken != NULL) {
                            strcpy(birthYear, yearToken);
                            yearToken = strtok(NULL, "-");
                            if (yearToken != NULL) {
                                strcpy(deathYear, yearToken);
                            }
                        }

                        fprintf(fileAppend, "%s|%s|%s|%s|%s|%s\n",
                            surname, name, patronymic, birthYear, deathYear, newBio);
                        fclose(fileAppend);

                        gotoxy(45, 11);
                        printf("Писатель успешно добавлен!");
                    }
                    else {
                        gotoxy(45, 11);
                        printf("Ошибка при сохранении в файл!");
                    }

                    gotoxy(45, 20);
                    printf("Нажмите Enter...");
                    getchar();
                    getchar();
                    break;
                }
                case 8:
                    break;
                default:
                    gotoxy(45, 15);
                    printf("Неверный выбор!");
                    getchar();
                    getchar();
                    break;
                }
            } while (choice2 != 8);

            break;
        }

        case 3:
            system("cls");
            gotoxy(55, 6);
            printf("ОБ АВТОРЕ:\n");
            gotoxy(45, 8);
            printf("ФИО студента: Макаркина Полина Ильинична\n");
            gotoxy(45, 9);
            printf("ВУЗ: ОмГТУ\n");
            gotoxy(45, 10);
            printf("Предмет: программирование\n");
            gotoxy(45, 11);
            printf("Год: 2026\n");
            gotoxy(45, 12);
            printf("Группа: ИВТ-253\n");
            getchar();
            getchar();
            break;

        case 4:
            system("cls");
            gotoxy(55, 10);
            printf("До новых встреч!\n\n");
            break;

        default:
            gotoxy(55, 15);
            printf("Неверный выбор!");
            getchar();
            getchar();
            break;
        }
    } while (choice != 4);

    return 0;
}