#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
void gotoxy(int ,int );
void menu();
void add();
void view();
void search();
void modify();
void deleterec();
struct student
{
    char name[20];
    char project[20];
    char status[20];
};
int main()
{
    gotoxy(15,8);
    printf("<--:Sistem de management proiecte studenti:-->");
    gotoxy(19,15);
    printf("Apasati orice tasta sa continuati.");
    getch();
    menu();
    return 0;
}
void menu()
{
    int choice;
    system("cls");
    gotoxy(10,3);
    printf("<--:MENIU:-->");
    gotoxy(10,5);
    printf("Introduceti cifra corespunzatoare actiunii.");
    gotoxy(10,7);
    printf("1 : Adauga.");
    gotoxy(10,8);
    printf("2 : Vizualizeaza.");
    gotoxy(10,9);
    printf("3 : Cauta.");
    gotoxy(10,10);
    printf("4 : Modifica.");
    gotoxy(10,11);
    printf("5 : Sterge.");
    gotoxy(10,12);
    printf("6 : Iesire.");
    gotoxy(10,15);
    printf("Introdu alegere.");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        add();
        break;

    case 2:
        view();
        break;

    case 3:
        search();
        break;

    case 4:
        modify();
        break;

    case 5:
        deleterec();
        break;

    case 6:
        exit(1);
        break;

    default:
        gotoxy(10,17);
        printf("Alegere invalida.");
    }
}
void add()
{
    FILE *fp;
    struct student std;
    char another ='y';
    system("cls");

    fp = fopen("record.txt","ab+");
    if(fp == NULL){
        gotoxy(10,5);
        printf("Eroare");
        exit(1);
    }
    fflush(stdin);
    while(another == 'y')
    {
        gotoxy(10,3);
        printf("<--:Adauga:-->");
        gotoxy(10,5);
        printf("Introduceti detalile studentului.");
        gotoxy(10,7);
        printf("Nume : ");
        gets(std.name);
        gotoxy(10,8);
        printf("Proiect : ");
        gets(std.project);
        gotoxy(10,9);
        printf("Status : ");
        gets(std.status);
        fwrite(&std,sizeof(std),1,fp);
        gotoxy(10,15);
        printf("Doriti sa mai adaugati? Apasa 'y' daca da sau 'n' daca nu.");
        fflush(stdin);
        another = getch();
        system("cls");
        fflush(stdin);
    }
    fclose(fp);
    gotoxy(10,18);
    printf("Apasati orice tasta ca sa continuati.");
    getch();
    menu();
}
void view()
{
    FILE *fp;
    int i=1,j;
    struct student std;
    system("cls");
    gotoxy(10,3);
    printf("<--:VIZUALIZARE:-->");
    gotoxy(10,5);
    printf("S.No   Nume        Proiectul        Status");
    gotoxy(10,6);
    printf("--------------------------------------------------------------------");
    fp = fopen("record.txt","rb+");
    if(fp == NULL){
        gotoxy(10,8);
        printf("Eroare.");
        exit(1);
    }
    j=8;
    while(fread(&std,sizeof(std),1,fp) == 1){
        gotoxy(10,j);
        printf("%-7d%-7s%-7s%-7s",i,std.name,std.project,std.status);
        i++;
        j++;
    }
    fclose(fp);
    gotoxy(10,j+3);
    printf("Apasati orice tasta ca sa continuati.");
    getch();
    menu();
}
void search()
{
    FILE *fp;
    struct student std;
    char stname[20];
    system("cls");
    gotoxy(10,3);
    printf("<--:Cautare:-->");
    gotoxy(10,5);
    printf("Introduceti numele studentului : ");
    fflush(stdin);
    gets(stname);
    fp = fopen("record.txt","rb+");
    if(fp == NULL){
        gotoxy(10,6);
        printf("Eroare");
        exit(1);
    }
    while(fread(&std,sizeof(std),1,fp ) == 1){
        if(strcmp(stname,std.name) == 0){
            gotoxy(10,8);
            printf("Nume : %s",std.name);
            gotoxy(10,9);
            printf("Proiect : %s",std.project);
            gotoxy(10,10);
            printf("Status : %d",std.status);
        }
    }
    fclose(fp);
    gotoxy(10,16);
    printf("Apasati orice tasta ca sa continuati.");
    getch();
    menu();
}
void modify()
{
    char stname[20];
    FILE *fp;
    struct student std;
    system("cls");
    gotoxy(10,3);
    printf("<--:MODIFICATI:-->");
    gotoxy(10,5);
    printf("Numele studentului: ");
    fflush(stdin);
    gets(stname);
    fp = fopen("record.txt","rb+");
    if(fp == NULL){
        gotoxy(10,6);
        printf("Eroare");
        exit(1);
    }
    rewind(fp);
    fflush(stdin);
    while(fread(&std,sizeof(std),1,fp) == 1)
    {
        if(strcmp(stname,std.name) == 0){
            gotoxy(10,7);
            printf("Nume: ");
            gets(std.name);
            gotoxy(10,8);
            printf("Proiect : ");
            gets(std.project);
            gotoxy(10,9);
            printf("Status : ");
            gets(std.status);
            fseek(fp ,-sizeof(std),SEEK_CUR);
            fwrite(&std,sizeof(std),1,fp);
            break;
        }
    }
    fclose(fp);
    gotoxy(10,16);
    printf("Apasati orice tasta ca sa continuati.");
    getch();
    menu();
}
void deleterec()
{
    char stname[20];
    FILE *fp,*ft;
    struct student std;
    system("cls");
    gotoxy(10,3);
    printf("<--:STERGE:-->");
    gotoxy(10,5);
    printf("Introduceti nume : ");
    fflush(stdin);
    gets(stname);
    fp = fopen("record.txt","rb+");
    if(fp == NULL){
        gotoxy(10,6);
        printf("Eroare");
        exit(1);
    }
    ft = fopen("temp.txt","wb+");
    if(ft == NULL){
        gotoxy(10,6);
        printf("Eroare");
        exit(1);
    }
    while(fread(&std,sizeof(std),1,fp) == 1){
        if(strcmp(stname,std.name)!=0)
            fwrite(&std,sizeof(std),1,ft);
    }
    fclose(fp);
    fclose(ft);
    remove("record.txt");
    rename("temp.txt","record.txt");
    gotoxy(10,10);
    printf("Apasati orice tasta ca sa continuati.");
    getch();
    menu();
}
void gotoxy(int x,int y)
{
        COORD c;
        c.X=x;
        c.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
