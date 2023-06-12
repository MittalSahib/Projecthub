#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
    char name[30], email[30], password[15];
    struct node *next;
};
int signup(char a[30], char b[30], char c[15]) // function for signing up
{
    FILE *f = NULL;
    struct node *first = (struct node *)malloc(sizeof(struct node));
    strcpy(first->name, a);
    strcpy(first->email, b); 
    strcpy(first->password, c);
    f = fopen("C:\\Users\\assu\\OneDrive\\Desktop\\folders\\Projects\\projecthub\\Files\\sign.txt", "a+");         // opens the file sign.txt
    if (f == NULL)
    {
        free(first);
        return 1;                  //  if file does not open returns 1
    }
    fprintf(f, "%s %s %s\n", first->email, first->password, first->name);        // data entry in the file
    fclose(f);
    free(first);     
    return 0;     // successfull termination of program
}
int login(char a[30], char b[15])       // function for login 
{
    FILE *f = NULL;
    struct node *first = (struct node *)malloc(sizeof(struct node));
    f = fopen("C:\\Users\\assu\\OneDrive\\Desktop\\folders\\Projects\\projecthub\\Files\\sign.txt", "r");       // opens the sign.txt file in read form 
    if(f == NULL) return 1;  // return 1 if file does not open 
    while(fscanf(f,"%s%s%s",first->email, first->password, first->name) != EOF)
    {
        if(strcmp(first->email,a) == 0)
        {
            if(strcmp(first->password,b) == 0)
            {
                fclose(f);
                free(first);
                return 0;    // successfully return
            }
            else 
            {
                fclose(f);
                free(first);
                return 1; // Password Incorrect return 1
            }
        }
    }
    fclose(f);
    free(first);
    return 2;  // not found any email return 2
}
/*int main()
{
    int a,i;
    char c[30] = "Rishabh gupta";
    for(i=0;i<strlen(c);++i) // necessary for the name which has gap in between
    {
        if(c[i] == ' ') 
        {
            c[i] = '_';
        }
    } w
    a = signup(c,"rishabhsingh","27378232");
    printf("%d",a);
    a = login("24mittal","12345")
    return 0;
}    */