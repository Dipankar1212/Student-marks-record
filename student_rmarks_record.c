#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>

COORD coord = {0,0};

void gotoxy(int x,int y)
{
    coord.X= x;
    coord.Y= y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);

}
struct student

 {
    char name[40];
    int reg;
    float marks;

 };


int main(){
    FILE *fp, *ft;
    struct student s;

    char studentname[40];
    long int recsize;
    char choice,another;

    fp=fopen("STUDENT.DAT","rb+");
    if(fp==NULL){
        fp=fopen("STUDENT.DAT","wb+");
        if(fp=NULL){
           printf("Cannot open the file\n");
           exit(1);
        } 

    }
    recsize = sizeof(s);


    while(1)
    {

        system("cls");
        gotoxy(30,10);
        printf("1. ive record");
        gotoxy(30,12);
        printf("2. Show record");
        gotoxy(30,14);
        printf("3. Modify record");
        gotoxy(30,16);
        printf("4. Delete record");
        gotoxy(30,18);
        printf("5. Exit");
        gotoxy(30,20);
        printf("Your choice: ");
        fflush(stdin);
        choice=getche();
        
        switch (choice)
        {
        case '1':
                system("cls");
                fseek(fp,0,SEEK_END);

                another='y';
                while(another=='y'){
                    printf("\nEntre name: ");
                    scanf("%s",s.name);
                    printf("\nEntre reg ");
                    scanf("%d",&s.reg);
                    printf("\nEntre marks ");
                    scanf("%f",&s.marks);

                    fwrite(&s,recsize,1,fp);
                    printf("Add another record y/n");
                    fflush(stdin);
                    another=getche();

                }
            break;

        case '2':
                system("cls");
                rewind(fp);
                while(fread(&s,recsize,1,fp)==1){
                    printf("\n %s %d %.2f",s.name,s.reg,s.marks);
                }
                getche();
                break;
        case '3':
                system("cls");
                another='y';
                while(another=='y'){
                    printf("Entre the student name to modify");
                    scanf("%s",studentname);
                    rewind(fp);
                    while(fread(&s,recsize,1,fp)==1){
                        if(strcmp(s.name,studentname)==0){
                            printf("\nEntre new name, reg and marks: ");
                            scanf("%s%d%f",s.name,&s.reg,&s.marks);
                            fwrite(&s,recsize,1,fp);
                            break;
                        }
                    }
                    printf("\n Modify another record y/n");
                    fflush(stdin);
                    another=getche();

                }   
                break;

            case'4':
            system("cls");
            another='y';
            while (another=='y'){
                printf("\n Entre name of student to delete: ");
                scanf("%s",studentname);
                ft=fopen("Temp.dat","wb");
                rewind(fp);
                while(fread(&s,recsize,1,fp)==1){
                    if(strcmp(s.name,studentname)!=0){
                        fwrite(&s,recsize,1,ft);

                    }
                }
                fclose(fp);
                fclose(ft);
                remove("STUDENT.DAT");
                rename("Temp.dat","STUDENT.DAT");
                fp=fopen("STUDENT.DAT","rb+");
                printf("Delete another record y/n ");
                fflush(stdin);
                another=getche();

            }    
            case'5':
            fclose(fp);
            exit(0);    


        
        default:
            break;
        }
    }


    return 0;
}