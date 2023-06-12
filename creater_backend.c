#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
struct subnode      // node for the idea details
{
    char title[100],description[1000000],time[30],email[30];
    struct subnode *next;
    int count;
};
struct ideas       // node for delivering the ideas details to the dashboard of creater
{
    char time[30],title[100],description[1000000];
    int p;
    struct ideas *next;
};
struct ideaselect2
{
    char cemail[30],pemail[30],time[30],acc[10];
    int patentno;
    struct ideaselect2 *next;
};
struct dash   // node for delivering all the details to the dashboard of creater
{
    int patent;
    struct ideas *head;
    struct ideaselect2 *head2;
};
int accept_reject(char cemail[30],char pemail[30], int patentno,char acc[10])
{
    FILE *sp = NULL,*temp = NULL;
    int count = 0,line = -1;
    struct ideaselect2 *first = (struct ideaselect2 *)malloc(sizeof(struct ideaselect2));
    sp = fopen("C:\\Users\\assu\\OneDrive\\Desktop\\folders\\Projects\\projecthub\\Files\\selectedideas.txt","r");
    temp = fopen("C:\\Users\\assu\\OneDrive\\Desktop\\folders\\Projects\\projecthub\\Files\\temp_selectedideas.txt","w");
    if(sp == NULL || temp == NULL) 
    {
        free(first);
        return 1;   // file error]
    }
    while(fscanf(sp,"%d %s %s %s %s",&first->patentno,&first->cemail,&first->pemail,&first->time,&first->acc) != EOF)
    {
        if(strcmp(cemail,first->cemail) == 0)
        {
            if(strcmp(pemail,first->pemail) == 0)
            {
                if(patentno == first->patentno)
                {
                    line = count;
                    break;
                }
            }
        }
        count += 1;
    }
    if(line == -1) 
    {
        free(first);
        return 2; // didn't find any request with these details
    }
    fseek(sp,0,SEEK_SET);
    count = 0;
    while(fscanf(sp,"%d %s %s %s %s",&first->patentno,&first->cemail,&first->pemail,&first->time,&first->acc) != EOF)
    {
        if(line == count)
        {
            strcpy(first->acc,acc);
            fprintf(temp,"%d %s %s %s %s\n",first->patentno,first->cemail,first->pemail,first->time,first->acc);
        }
        else fprintf(temp,"%d %s %s %s %s\n",first->patentno,first->cemail,first->pemail,first->time,first->acc);
        count += 1;
    }
    fclose(sp);
    fclose(temp);
    remove("C:\\Users\\assu\\OneDrive\\Desktop\\folders\\Projects\\projecthub\\Files\\selectedideas.txt");
    rename("C:\\Users\\assu\\OneDrive\\Desktop\\folders\\Projects\\projecthub\\Files\\temp_selectedideas.txt","C:\\Users\\assu\\OneDrive\\Desktop\\folders\\Projects\\projecthub\\Files\\selectedideas.txt");
    free(first);
    return 0;
}
int ideasubmit(char a[30],char b[100],char c[1000000],int pcount)     // function for the idea submittion   it needs email, title, description, patents
{
    time_t t;
    struct subnode *first = (struct subnode *)malloc(sizeof(struct subnode));
    FILE *f = NULL;
    int i;
    strcpy(first->email,a);          // copy email in storage                                              
    strcpy(first->title,b);      // copy title in storage
    strcpy(first->description,c);    // copy description in storage
    first->count = pcount+1;        // copy number of patents 
    time(&t);  
    strcpy(first->time,ctime(&t));
    for(i=0;i<strlen(first->time);++i)
    {
        if(first->time[i] == '\n') first->time[i] = '\0';
        if(first->time[i] == ' ') first->time[i] = '_';
    }
    for(i=0;i<(strlen(first->title) < strlen(first->description)? strlen(first->description) : strlen(first->title));++i) // necessary for the name which has gap in between
    {
        if(first->title[i] == ' ') 
        {
            first->title[i] = '_';
        }
        if(first->title[i] == '\n') first->title[i] = '\0';
        if(first->description[i] == ' ')
        {
            first->description[i] = '_';
        }
        if(first->description[i] == '\n') first->description[i] = '\0';
    }
    f = fopen("C:\\Users\\assu\\OneDrive\\Desktop\\folders\\Projects\\projecthub\\Files\\patent.txt","a+");
    if(f == NULL)
    {
        free(first);
        return 1; // file does not open
    }
    fprintf(f,"%d %s %s %s %s\n",first->count,first->time,first->email,first->title,first->description);
    fclose(f);
    free(first);
    return 0;
}
int updation_of_idea(char a[30], int n_o_p, char b, char d[1000000])     //updation of the ideas title or description. 
{
    FILE *f,*temp;       // two files one for patent file and one for temprary file to save data
    int i,count1 = 0,line;
    struct subnode *first = (struct subnode *)malloc(sizeof(struct subnode));       
    f = fopen("C:\\Users\\assu\\OneDrive\\Desktop\\folders\\Projects\\projecthub\\Files\\patent.txt","r");   // opening of file patent.txt for updation
    temp = fopen("C:\\Users\\assu\\OneDrive\\Desktop\\folders\\Projects\\projecthub\\Files\\temp_patent.txt","w"); // opening of file temp_patent for temprarily store data
    if(f == NULL || temp == NULL)     // if either of the file does not open then it will return 1;
    {
        free(first);
        return 1;
    }
    while(fscanf(f,"%d %s %s %s %s",&first->count,&first->time,&first->email,&first->title,&first->description) != EOF)  // reading every line in loop to find the line for updation
    {
        if(strcmp(first->email,a) == 0 ) 
        {
            if(first->count == n_o_p )
            {
                line = count1;
                break;
            }
        }
        count1 += 1;
    }
    fseek(f,0,SEEK_SET);
    count1 = 0;
    while(fscanf(f,"%d %s %s %s %s",&first->count,&first->time,&first->email,&first->title,&first->description) != EOF) // transfering every line in temprary file with updated data
    {
        if(line == count1)    
        {
            if(b == 't')
            {
                strcpy(first->title,d);
                fprintf(temp,"%d %s %s %s %s\n",first->count,first->time,first->email,first->title,first->description);
            }
            else 
            {
                strcpy(first->description,d);
                fprintf(temp,"%d %s %s %s %s\n",first->count,first->time,first->email,first->title,first->description);
            }
        }
        else fprintf(temp,"%d %s %s %s %s\n",first->count,first->time,first->email,first->title,first->description);
        count1 += 1;
    }
    fclose(f);
    fclose(temp);
    remove("C:\\Users\\assu\\OneDrive\\Desktop\\folders\\Projects\\projecthub\\Files\\patent.txt");  // removing patent.txt file from the location
    rename("C:\\Users\\assu\\OneDrive\\Desktop\\folders\\Projects\\projecthub\\Files\\temp_patent.txt","C:\\Users\\assu\\OneDrive\\Desktop\\folders\\Projects\\projecthub\\Files\\patent.txt");
    free(first);
    return 0;  // indication of successful termination
}
struct dash cdashboard(char a[30]) // function for creater dashboard takes email as input
{
    FILE *p;
    struct ideaselect2 *second,*third;
    struct dash b;           
    struct ideas *h,*s;
    int count = 0,i,c = 0;
    struct subnode *first = (struct subnode *)malloc(sizeof(struct subnode));
    p = fopen("C:\\Users\\assu\\OneDrive\\Desktop\\folders\\Projects\\projecthub\\Files\\patent.txt","r"); // opening of file 
    while(fscanf(p,"%d %s %s %s %s",&first->count,&first->time,&first->email,&first->title,&first->description) != EOF)   // reading the patent file 
    {
        if(strcmp(first->email,a) == 0)     // if email matches from the email given
        {
            h = (struct ideas *)malloc(sizeof(struct ideas));     // making a linked list for ideas
            if(count != 0) s->next = h;
            if(count == 0) b.head = h;
            for(i=0;i<(strlen(first->title) < strlen(first->description)? strlen(first->description) : strlen(first->title));++i) // making it great for display purposes
            {
                if(first->title[i] == '_') 
                {
                    first->title[i] = ' ';
                }
                if(first->description[i] == '_')
                {
                    first->description[i] = ' ';
                }
            }
            for(i=0;i<strlen(first->time);++i)
            {
                if(first->time[i] == '_') first->time[i] = ' ';
            }
            strcpy(h->title,first->title);
            strcpy(h->description,first->description);
            strcpy(h->time,first->time);
            h->p = first->count;
            s = h;
            count += 1; // counting number of patents
        }
    }
    if(count != 0) s->next = NULL;
    else 
    {
        free(h);
        h = NULL;
    }
    b.patent = count;
    fclose(p);
    p = fopen("C:\\Users\\assu\\OneDrive\\Desktop\\folders\\Projects\\projecthub\\Files\\selectedideas.txt","r");
    while(1) 
    {  
        second = (struct ideaselect2 *)malloc(sizeof(struct ideaselect2));
        if(fscanf(p,"%d %s %s %s %s",&second->patentno,&second->cemail,&second->pemail,&second->time,&second->acc) == EOF) break;
        if(c == 0) b.head2 = second;
        if(c != 0) third->next = second;
        third = second;
        c += 1;
    }
    if(c == 0) 
    {
        free(second);
        b.head2 = NULL;
    }
    else 
    {
        free(second);
        third->next = NULL;
    }
    fclose(p);
    return b;
}
/*
int main()
{         
    struct dash dashboard;
    char a[30] = "divyeshkoli35@gmail.com",b[100] = "Title of idea",c[1000000] = "desciption of idea";
    int i;
 // i = ideasubmit("24mittal.parth@gmail.com","hat be bhen ke lode","gand mara",1);    
 // i = updation_of_idea("24mittal.parth@gmail.com",1,'t',"jail_ho");
  //  printf("%d",i);
    dashboard = cdashboard("24mittal.parth@gmail.com");
    printf("patents : %d\n",dashboard.patent);
    while(dashboard.head != NULL)
    {
        printf("%d %s %s %s\n",dashboard.head->p,dashboard.head->time,dashboard.head->title,dashboard.head->description);
        dashboard.head = dashboard.head->next;
    }
    while(dashboard.head2 != NULL)
    {
        printf("%d %s %s %s\n",dashboard.head2->patentno,dashboard.head2->time,dashboard.head2->cemail,dashboard.head2->pemail);
        dashboard.head2 = dashboard.head2->next;
    }
    i = accept_reject("24mitt.parth@gmail.com","krishna.com",2,"accepted");
    printf("%d",i);
    return 0;
} */