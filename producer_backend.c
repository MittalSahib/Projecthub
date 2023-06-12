#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct patentideas    // need for searching in the patent file
{
    char title[100],description[1000000],time[30],email[30];
    struct subnode *next;
    int count;
};
struct ideaselect
{
    char cemail[30],pemail[30],time[30],acc[10];
    int patentno;
    struct ideaselect *next;
};
struct search  // need for storing the searched data
{
    int p;
    char email[30],title[30],desciption[1000000];
    struct search *next;
};
struct search *searching()
{
    struct patentideas *first = (struct patentideas *)malloc(sizeof(struct patentideas));
    struct search *second,*third,*head;
    FILE *p;
    int count = 0;
    p = fopen("C:\\Files\\patent.txt","r");
    while(fscanf(p,"%d %s %s %s %s",&first->count,&first->time,&first->email,&first->title,&first->description) != EOF)
    {
        second = (struct search *)malloc(sizeof(struct search));
        if(count == 0) head = second;
        if(count != 0) third->next = second;
        second->p = first->count;
        strcpy(second->email,first->email);
        strcpy(second->title,first->title);
        strcpy(second->desciption,first->description);
        third = second;
        count += 1;
    }
    third->next = NULL;
    return head;
}
int ideaselection(char pemail[30],char cemail[30],int patentno)
{
    FILE *sp = NULL,*p = NULL;
    time_t t;
    int count = 0;
    int i;
    struct patentideas *first = (struct patentideas *)malloc(sizeof(struct patentideas));
    struct ideaselect *second = (struct ideaselect *)malloc(sizeof(struct ideaselect));
    p = fopen("C:\\Files\\patent.txt","r");
    sp = fopen("C:\\Files\\selectedideas.txt","a+");
    if(sp == NULL || p == NULL)
    {
        free(first);
        free(second);
        return 1;
    }
    while(fscanf(p,"%d %s %s %s %s",&first->count,&first->time,&first->email,&first->title,&first->description) != EOF)
    {
        if(strcmp(first->email,cemail) == 0)
        {
            if(first->count == patentno)
            {
                second->patentno = first->count;
                strcpy(second->cemail,cemail);
                strcpy(second->pemail,pemail);
                time(&t);  
                strcpy(second->time,ctime(&t));
                for(i=0;i<strlen(second->time);++i)
                {
                    if(second->time[i] == '\n') second->time[i] = '\0';
                    if(second->time[i] == ' ') second->time[i] = '_';
                }
                count = 1;
                break;
            }
        }
    }
    if(count == 0)
    {
        return 2;
    }
    strcpy(second->acc,"Pending");
    fprintf(sp,"%d %s %s %s %s\n",second->patentno,second->cemail,second->pemail,second->time,second->acc);
    fclose(p);
    fclose(sp);
    free(first);
    free(second);
    return 0;
}
struct ideaselect *ideastatus(char email[30])
{
    FILE *sp;
    int count = 0,i;
    struct ideaselect *first = (struct ideaselect *)malloc(sizeof(struct ideaselect)),*head,*second;
    sp = fopen("C:\\Files\\selectedideas.txt","r");
    while(fscanf(sp,"%d %s %s %s %s",&first->patentno,&first->cemail,&first->pemail,&first->time,&first->acc) != EOF)
    {
        if(strcmp(first->pemail,email) == 0)
        {
            if(count == 0) head = first;
            if(count != 0) second->next = first;
            second = first;
            for(i=0;i<strlen(second->time);++i)
            {
                if(second->time[i] == '_') second->time[i] = ' ';
            }
            count += 1;
        }
    }
    second->next = NULL;
    return head;
}
/*
int main()
{ 
 //   struct search *head;
    struct ideaselect *head;
   // head =  searching();
   head = ideastatus("krishna.com");
    while(head != NULL)
    {
        printf("%d %s %s %s %s\n",head->patentno,head->cemail,head->pemail,head->time,head->acc);
        head = head->next;
    }
 //   int a;
   // a = ideaselection("krishna.com","24mittal.parth@gmail.com",2);
    //printf("%d",a);
    return 0;
}*/
