#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add_task();
void view_task();
void cmplt_task();
void delete_task();

int main()
{
    system("chcp 65001 > nul"); //Forces emojies to show in terminal
    while(1)
    {
        int ch;
        printf("\n======= MENU - TO DO LIST =======\n");
        printf("Press [1] : Add Task\n");
        printf("Press [2] : View Task(s)\n");
        printf("Press [3] : Complete Task\n");
        printf("Press [4] : Delete Task\n");
        printf("Press [0] : Exit program\n");

        printf("YOUR INPUT - ");
        scanf("%d", &ch);

        if (ch < 0 || ch > 4)
            printf("\nEnter number from limited choice only! [1-2-3-4-0]\n");

        if (ch == 0)
        {
            printf("\nExiting Program!\n");
            break;
        }

        switch (ch)
        {
            case 1:
                add_task();
                break;
            
            case 2:
                view_task();
                break;

            case 3:
                cmplt_task();
                break;

            case 4:
                delete_task();
                break;

            default:
                break;
        }
    } return 0;
}

void add_task()
{
    char str[100];
    FILE *fp = fopen("ToDoList.txt", "a");

    if (fp == NULL) {
        printf("\nFile could not be opened!\n");
        return;
    }

    printf("\nEnter task: ");
    getchar();
    fgets(str, 100, stdin);
    str[strcspn(str, "\n")] = '\0';

    fputs(str, fp);
    fputs(" [ ]", fp);
    fputs("\n", fp);
    printf("\nTask successfully added!\n");

    fclose(fp);
}

void view_task()
{
    char line[100];
    int count = 1;

    FILE *fp = fopen("ToDoList.txt", "r");
    if (fp == NULL) {
        printf("File does not exist!\n");
        return;
    }

    printf("\n");
    printf("============\n");
    printf("TASKS TO DO\n");
    printf("============\n");
    printf("Tip! - [ ] : Task not completed yet || [✓] : Task completed\n");
    printf("-------------------------------------------------\n\n");

    while (fgets(line, 100, fp) != NULL) {
        printf("%d. %s", count, line);
        count++;
    }

    if (count == 1) {
        printf("No tasks found.\n");
    }

    printf("\n-------------------------------------------------\n\n");

    fclose(fp);
}

void cmplt_task()
{
    int task_no;
    char line[100];
    int counter = 1;

    printf("\nEnter task number you want to mark as completed: ");
    scanf("%d", &task_no);
    getchar();   // clear newline

    FILE *fp = fopen("ToDoList.txt", "r");
    FILE *fpt = fopen("tempFile.txt", "w");

    if (fp == NULL || fpt == NULL) {
        printf("\nFile error!\n");
        return;
    }

    while (fgets(line, 100, fp) != NULL)
    {
        if (counter == task_no)
        {
            // remove newline for safe editing
            line[strcspn(line, "\n")] = '\0';

            // replace [ ] with [✓]
            char *pos = strstr(line, "[ ]");
            if (pos != NULL)
                strcpy(pos, "[✓]");

            fputs(line, fpt);
            fputs("\n", fpt);
        }

        else
            fputs(line, fpt);

        counter++;
    }

    fclose(fp);
    fclose(fpt);

    remove("ToDoList.txt");
    rename("tempFile.txt", "ToDoList.txt");

    printf("\nTask marked as completed!\n");
}

void delete_task()
{
    int task_no, counter = 1;
    char line[100];

    printf("Enter which task you want to remove: ");
    scanf("%d", &task_no);

    FILE *fp = fopen("ToDoList.txt", "r");
    FILE *fpt = fopen("TEMP.txt", "w");

    if (fp == NULL || fpt == NULL) {
        printf("File error!\n");
        return;
    }

    while (fgets(line, 100, fp) != NULL) {
        if (counter != task_no) {
            fputs(line, fpt);
        }
        counter++;
    }

    fclose(fp);
    fclose(fpt);

    remove("ToDoList.txt");
    rename("TEMP.txt", "ToDoList.txt");

    printf("\nTask deleted successfully!\n");
}
