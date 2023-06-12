#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "logindetails_backend.c"
#include "creater_backend.c"
#include "producer_backend.c"
char email[30];
int signup2()    // function for signup
{
    char name[30], password[15];
    int i;
    printf("Enter your name(max 30 characters use '_' instead of gaps) : ");
    scanf("%s", &name);
    printf("Enter your email (max 30 characters): ");
    scanf("%s", &email);
    printf("Enter your password (max 15 characters): ");
    scanf("%s", &password);
    i = signup(name, email, password);
    if (i == 0) 
    {
        printf("Succesfully signed up");
        return 0;
    }
    else
    {
        printf("Error in file");
        return 1;
    }
}

int login2()  // function for login
{
    int num_users = 0;
    char password[15];

    printf("Enter your email: ");
    scanf("%s", &email);

    printf("Enter your password: ");
    scanf("%s", &password);
    num_users = login(email, password);
    if (num_users == 0)
    {
        printf("Successfully logined");
        return 0;
    }
    else if (num_users == 1)
    {
        printf("Error in file opening");
        return 1;
    }
    else
    {
        printf("didn't find any email");
        return 2;
    }
}
int snp(int nop)   // function for submittion of ideas
{
    int i;
    char title[100],desc[1000000];
    printf("Enter your title : ");
    fgets(title, 100, stdin);
    fgets(title, 100, stdin);
    printf("Enter your description : ");
    fgets(desc, 1000000, stdin);
    i = ideasubmit(email,title,desc,nop);
    if(i == 0)
    {
        printf("Successfully Submitted");
        return 0;
    }
    else 
    {
        printf("File Opening Error");
        return 1;
    }
}
int up()  // function for updation of idea
{
    char ch,td[1000000];
    int a,i;
    printf("Enter the number of patent you want to update : ");
    scanf("%d",&a);
    printf("Enter t for title or d for description : ");
    scanf("%s",&ch);
    printf("Enter your updated text : ");
    fgets(td, 1000000, stdin);
    fgets(td, 1000000, stdin);
    for(i=0;i<strlen(td);++i)
    {
        if(td[i] == ' ') td[i] = '_';
        if(td[i] == '\n') td[i] = '\0';
    }
    i = updation_of_idea(email,a,ch,td);
    if(i == 0)
    {
        printf("Successfully Updated");
        return 0;
    }
    else 
    {
        printf("File error");
        return 1;
    }
}
int aor()
{
    char pe[30],ac[10];
    int p,i;
    printf("Enter the Producer email : ");
    scanf("%s",&pe);
    printf("Enter Patent Number : ");
    scanf("%d",&p);
    printf("You want to Accept or Reject : ");
    scanf("%s",&ac);
    i = accept_reject(email,pe,p,ac);
    if(i == 0)
    {
        printf("Successfully Status updated");
        return 0;
    }
    else if(i == 2)
    {
        printf("Didn't find any Patent request");
        return 2;
    }
    else 
    {
        printf("File opening error");
        return 1;
    }
}
int createrdashboard() // function for dashboard of creater
{
    struct dash a;
    int choice,re;
    while(1)
    {
        a = cdashboard(email);
        printf("\t\t****** Creater Dashboard ******\n\n");
        printf("Patents : %d",a.patent);
        printf("\n1. Submit New Project\n2. Update Project\n3. Submitted Ideas\n4. Idea Request\n5. Accept or reject idea request\n6. Exit\nEnter your choice: ");
        scanf("%d",&choice);
        switch (choice)
            {
            case 1:
                re = snp(a.patent);
                break;
            case 2:
                re = up();
                break;
            case 3:
                printf("Ideas Submitted :\n");
                while(a.head != NULL)
                {
                    printf("%d | %s | %s | %s\n",a.head->p,a.head->time,a.head->title,a.head->description);
                    a.head = a.head->next;
                }
                break;
            case 4:
                printf("Requested Ideas : \n");
                while(a.head2 != NULL)
                {
                    printf("%d | %s | %s | %s\n",a.head2->patentno,a.head2->time,a.head2->pemail,a.head2->acc);
                    a.head2 = a.head2->next;
                }
                break;
            case 5:
                re = aor();
                break;
            case 6:
                return 0;
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
    }
}
void si()
{
    struct search *head;
    int i;
    head = searching();
    for(i=0;i<(strlen(head->title) < strlen(head->desciption)? strlen(head->desciption) : strlen(head->title));++i) // making it great for display purposes
    {
        if(head->title[i] == '_') 
        {
            head->title[i] = ' ';
        }
        if(head->desciption[i] == '_')
        {
            head->desciption[i] = ' ';
        }
    }
    printf("Search results : \n");
    while(head != NULL)
    {
        printf("%d | %s | %s | %s\n",head->p,head->email,head->title,head->desciption);
        head = head->next;
    }
}
int sii()
{
    char ce[30];
    int p,i;
    printf("Enter the email id of patents creater : ");
    scanf("%s",&ce);
    printf("Enter the patent number : ");
    scanf("%d",&p);
    i = ideaselection(email,ce,p);
    if(i == 0)
    {
        printf("Successfully selected idea");
        return 0;
    }
    else if(i == 2)
    {
        printf("Didn't find any patent");
        return 2;
    }
    else 
    {
        printf("File error");
        return 1;
    }
}
void soi()
{
    struct ideaselect *head;
    head = ideastatus(email);
    printf("Status of idea : \n");
    while(head != NULL)
    {
        printf("%d | %s | %s | %s\n",head->patentno,head->time,head->cemail,head->acc);
        head = head->next;
    }
}
int producerdashboard()
{
    int ch;
    while(1)
    {
        printf("\t\t****** Producer Dashboard ******\n\n");
        printf("1. Search ideas\n2. Select idea\n3. Status of Idea \n4. exit\nEnter your choic : ");
        scanf("%d",&ch);
        switch (ch)
            {
            case 1:
                si();      
                break;
            case 2:
                sii();
                break;
            case 3:
                soi();
                break;
            case 4:
                return 0;
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
    }
}
int main()
{
    int choice;
    int re;
    while (1)
    {
        printf("\t\t******Welcome to Project Hub******\n");
        printf("\n1. Sign up\n2. Log in\n3. exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            re =  signup2();
            if(re == 0) choice = -1;
            break;
        case 2:
            re = login2();
            if(re == 0) choice = -1;
            break;
        case 3:
            printf("\t\t******Thankyu to visit Project Hub******\n");
            return 0;
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
        if (choice == -1)
            break;
    }
    while(1)
    {
        printf("\n1. Creater Dashboard\n2. Producer Dashboard\n3. exit\nEnter your choice: ");
        scanf("%d", &choice);
        if(choice == 1)
        {
            createrdashboard();
        }
        else if(choice == 2)
        {
            producerdashboard();
        }
        else if(choice == 3)
        {
            printf("\t\t******Thankyu to visit Project Hub******\n");
            break;
        }
        else continue;
    }
    return 0;
}
