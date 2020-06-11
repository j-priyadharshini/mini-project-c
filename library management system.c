#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX_BOOK 50
#define MAX_STUDENT 50
#define USRNAME_LEN 15
#define PASSWD_LEN 15
#define NAME_LEN 15
#define AUTHOR_LEN 15

const char DEFAULT_USRNAME[] ="user";
const char DEFAULT_PASSWRD[] ="password";

int stud_no;//the position of student info in structure
char user[15];//whether user is student or librarian
int user_no=0;//total students
int book_no=0;//total books

//date structure
typedef struct
{
    int dd,mm,yy;
}Date;

//credentials structure
typedef struct
{
    char username[USRNAME_LEN];
    char password[PASSWD_LEN];
}Check;

typedef struct
{
    int id;
    char status[15];
    char name[NAME_LEN];
    char author[AUTHOR_LEN];
    Date date;
}book;

book b[MAX_BOOK];//initialize books

typedef struct
{
    int id;
    char name[15];
    char dept[15];
    int borrowed_book_no;
    char borrowed_books[5][15];
    Date dob;
    Check check;
}User;

User librarian;
User student[MAX_STUDENT];

int main()
{
    first_page();
    return 0;
}

void first_page()
{
    system("cls");
    printf("\n\n\n");
    printf("\t\t\t----------------------------------------------------------------------\n\n");
    printf("\t\t\t|                   LIBRARY MANAGEMENT SYSTEM                        |\n\n");
    printf("\t\t\t----------------------------------------------------------------------\n\n\n\n\n");
    printf("Press any key to continue...");
    getch();
    enter_page();
}



//display text as heading
void head_text(char text[])
{
    int len =0;
    int pos = 0;
    //how many space need to print
    len = (78 - strlen(text))/2;

    printf("\n\t\t\t----------------------------------------------------------------------------\n");
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++){
        printf(" ");
    }
    printf("%s",text);
    printf("\n\t\t\t----------------------------------------------------------------------------\n\n\n");
}

//Login or Sign up
void enter_page()
{
    system("cls");
    fflush(stdin);
    int choice;
    head_text("ENTER PAGE");
    printf("1.Login\n2.User Signup\n\n\nEnter your choice => ");
    scanf("%d",&choice);
    if(choice==1)
        login();
    else if(choice==2)
        sign_up();
    else{
        printf("\n\nINCORRECT CHOICE!!!\nTRY AGAIN!\nPress any key...");
        fflush(stdin);
        getch();
        enter_page();
    }
}

void student_menu()
{
    system("cls");
    int choice;

    head_text("STUDENT MENU PAGE");

    printf("1.View Books\n");
    printf("2.Search Books\n");
    printf("3.Borrow Book\n");
    printf("4.Return Book\n");
    printf("5.User Info\n");
    printf("6.Edit User Info\n");
    printf("7.Add preference\n");
    printf("8.Log Out\n");
    printf("0.Exit\n");
    printf("\n\n\nEnter choice => ");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            view_books();
            break;
        case 2:
            search_book();
            break;
        case 3:
            borrow_book();
            break;
        case 4:
            return_book();
            break;
        case 5:
            display_info();
            break;
        case 6:
            edit_info();
            break;
        case 7:
            add_preference();
            break;
        case 8:
            enter_page();
            break;
        case 0:
            {
               printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
               exit(1);
            }
            break;
        default:
            {
                printf("\n\n\n\t\t\tINVALID INPUT!!! Try again.Press any key...");
                fflush(stdin);
                getch();
                student_menu();
            }
    }
}

void librarian_menu()
{
    system("cls");
    int choice;

    head_text("LIBRARIAN MENU PAGE");

    printf("1.Add Books\n");
    printf("2.Search Books\n");
    printf("3.View Books\n");
    printf("4.View Students\n");
    printf("5.Delete Book\n");
    printf("6.Edit User Info\n");
    printf("7.View preference\n");
    printf("8.Log Out\n");
    printf("0.Exit");
    printf("\n\n\nEnter choice => ");
    scanf("%d",&choice);

    switch(choice)
        {
        case 1:
            add_book();
            break;
        case 2:
            search_book();
            break;
        case 3:
            view_books();
            break;
        case 4:
            view_students();
            break;
        case 5:
            delete_book();
            break;
        case 6:
            edit_info();
            break;
        case 7:
            view_preference();
            break;
        case 8:
            enter_page();
            break;
        case 0:
            {
                printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
                exit(1);
            }
            break;
        default:
            {
                printf("\n\n\n\t\t\tINVALID INPUT!!! Try again.Press any key...");
                fflush(stdin);
                getch();
                librarian_menu();
            }
    }
}

//read file with user info
void read_info()
{
    int loop,book;
    strcpy((librarian.check.username),DEFAULT_USRNAME);
    strcpy((librarian.check.password),DEFAULT_PASSWRD);

    FILE *fp;
    fp=fopen("input.txt","r");

    if(fp==NULL){
        return;
    }

    for(loop=0;!(feof(fp));loop++)
    {
        fscanf(fp,"\n%d %s %s %s %s %d %d/%d/%d ", &student[loop].id, student[loop].check.username, student[loop].check.password, student[loop].name, student[loop].dept, &student[loop].borrowed_book_no, &student[loop].dob.dd, &student[loop].dob.mm, &student[loop].dob.yy);

        if(student[loop].borrowed_book_no==0){
            fscanf(fp,"%s ",student[loop].borrowed_books[0]);
        }
        else{
            for(book=0;book<student[loop].borrowed_book_no;book++){
                fscanf(fp,"%s ",student[loop].borrowed_books[book]);
            }
        }
    }
    user_no=loop;
    fclose(fp);
}

//read books from file
void read_book()
{
    int loop;
    FILE *fp;
    fp=fopen("books.txt","r");

    if(fp==NULL){
        fclose(fp);
        return;
    }

    for(loop=0;!(feof(fp));loop++)
        fscanf(fp,"\n%d %s %s %s ", &b[loop].id, b[loop].name, b[loop].author, b[loop].status);
    book_no=loop;

    fclose(fp);
}

//update changes made in user info to file
void update_info()
{
    int loop,book;
    FILE *fp;

    fp=fopen("input.txt","w");

    for(loop=0;loop<user_no;loop++){
        fprintf(fp,"\n%d %s %s %s %s %d %d/%d/%d ", student[loop].id, student[loop].check.username, student[loop].check.password, student[loop].name, student[loop].dept, student[loop].borrowed_book_no, student[loop].dob.dd, student[loop].dob.mm, student[loop].dob.yy);
        fflush(stdin);

        if(student[loop].borrowed_book_no==0){
            fprintf(fp,"%s ","NONE");
            fflush(stdin);
        }
        else{
            for(book=0;book<student[loop].borrowed_book_no;book++){
                fprintf(fp,"%s ",student[loop].borrowed_books[book]);
                fflush(stdin);
            }
        }
    }
    fclose(fp);
}

//update changes made to book in file
void update_book()
{
    FILE *fp;
    fp=fopen("books.txt","w");

    int loop=0;

    for(loop=0;loop<book_no;loop++)
    {
        fprintf(fp,"\n%d %s %s %s ", b[loop].id, b[loop].name, b[loop].author, b[loop].status);
        fflush(stdin);
    }
    fclose(fp);
}

//create new student user
void sign_up()
{
    system("cls");
    head_text("SIGN UP PAGE");
    read_info();

    int choice,loop,flag=1,id;
    char username[USRNAME_LEN];
    char password[PASSWD_LEN];

    printf("ENTER ROLL NO:  ");
    scanf("%d",&id);
    //check if id is unique
    for(loop=0;loop<user_no;loop++){
        if(id==student[loop].id){
            printf("\n\nROLL NO ALREADY IN USE. Press any key to try again...\n\n");
            fflush(stdin);
            getch();
            sign_up();
        }
    }

    printf("\nUSERNAME: ");
    scanf("%s",&username);
    //check if username is unique
    for(loop=0;loop<user_no;loop++){
        if(!strcmp(username,student[loop].check.username)){
            printf("\n\nUSERNAME ALREADY IN USE. Press any key to try again...\n\n");
            fflush(stdin);
            getch();
            sign_up();
        }
    }

    user_no++;

    student[user_no].id=id;
    strcpy(student[user_no].check.username,username);

    printf("\nPASSWORD: ");
    scanf("%s",&student[user_no].check.password);

    printf("\nName: ");
    scanf("%s",&student[user_no].name);
    printf("\nDepartment: ");
    scanf("%s",&student[user_no].dept);

    printf("\nDate Of Birth (dd/mm/yy format): ");
    scanf("%d/%d/%d", &student[user_no].dob.dd, &student[user_no].dob.mm, &student[user_no].dob.yy);

    student[user_no].borrowed_book_no=0;
    strcpy(student[user_no].borrowed_books[0],"None\0");
    //write to file
    FILE *fp;
    fp=fopen("input.txt","a");

    fprintf(fp,"\n%d %s %s %s %s %d %d/%d/%d ", student[user_no].id, student[user_no].check.username, student[user_no].check.password, student[user_no].name, student[user_no].dept, student[user_no].borrowed_book_no, student[user_no].dob.dd, student[user_no].dob.mm, student[user_no].dob.yy);
    fflush(stdin);
    fprintf(fp,"%s ",student[user_no].borrowed_books[0]);
    fflush(stdin);

    fclose(fp);
    stud_no=user_no;
    strcpy(user,"student");
    student_menu();
}

//login as student or librarian
void login()
{
    system("cls");
    head_text("LOGIN PAGE");

    int choice,loop,trys=0,flag=0;
    char username[USRNAME_LEN];
    char password[PASSWD_LEN];

    printf("Enter as \n\n1.STUDENT\n2.LIBRARIAN\n\nEnter choice => ");
    scanf("%d",&choice);
    read_info();

    if((choice!=1)&&(choice!=2)){
        printf("\n\nINCORRECT CHOICE!!!\nTRY AGAIN!\nPress any key...");
        fflush(stdin);
        getch();
        login();
    }

    else{
        do{
            strcpy(user,"student");
            printf("\nUSERNAME :  ");
            scanf("%s",&username);
            printf("PASSWORD :  ");
            scanf("%s",&password);
            //student login
            if(choice==1){
                for(loop=0;loop<user_no;loop++){
                    if((!strcmp(student[loop].check.username,username))&&(!strcmp(student[loop].check.password,password))){
                        stud_no=loop;
                        flag=1;
                        break;
                    }
                }
                if(flag==1){
                   student_menu();
                }
            }
            //librarian login
            else if(choice==2){
                strcpy(user,"librarian");
                if((!strcmp(librarian.check.username,username))&&(!strcmp(librarian.check.password,password))){
                    librarian_menu();
                    break;
                }
            }

            if(flag==0){
                printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
                trys++;
            }
        }while(trys<=3);

        if(trys>3){
            printf("\n\nLogin Failed. Too many trys\n");
            printf("\nSorry,Unknown User.");
            printf("\nPress any key....");
            getch();
            first_page();
        }
    }
}

//return as specified
void return_to()
{
    int choice;
    fflush(stdin);
    printf("\n\nEnter 1 to go to menu or 0 to exit.....");
    scanf("%d",&choice);
    if(choice==1){
        if(!strcmp(user,"student"))
            student_menu();
        else
            librarian_menu();
    }
    if(choice==0)
        exit(1);
    else{
        printf("\n\nINCORRECT CHOICE!!!\nTRY AGAIN!\nPress any key...");
        return_to();
    }
}

//view students
void view_students()
{
    system("cls");
    head_text("STUDENT DETAILS");
    read_info();
    int loop=0;
    if(user_no>0){
        printf("\nSTUDENT ID\t\tSTUDENT NAME\t\t\tDOBt\t\tDEPARTMENT\n");
        printf("-------------------------------------------------------------------------------------------------\n");
        for(loop=0;loop<user_no;loop++){
            printf("\n%d",student[loop].id);
            printf("\t\t\t%s",student[loop].name);
            printf("\t\t\t\t%d/%d/%d",student[loop].dob.dd,student[loop].dob.mm,student[loop].dob.yy);
            printf("\t\t\t\t\t%s",student[loop].dept);
        }
    }
    if(!user_no)
        printf("\n\t\t\tNo Record\n\n");
    return_to();
}

//list all books in the record
void view_books()
{
    system("cls");
    head_text("BOOK DETAILS");
    read_book();
    int loop=0;
    if(book_no>0){
        printf("\nBOOK ID\t\t\tBOOK NAME\t\t\tAUTHOR NAME\t\t\tBOOK STATUS\n");
        printf("-------------------------------------------------------------------------------------------------\n");
        for(loop=0;loop<book_no;loop++){
            printf("\n%d",b[loop].id);
            printf("\t\t\t%s",b[loop].name);
            printf("\t\t\t\t%s",b[loop].author);
            printf("\t\t\t\t\t%s",b[loop].status);
        }
    }
    if(!book_no)
        printf("\n\t\t\tNo Record\n\n");
    return_to();
}

//display user info
void display_info()
{
    system("cls");
    int i;
    head_text("STUDENT INFO");
    read_info();

    printf("STUDENT ID:            %d\n",student[stud_no].id);
    printf("NAME :                 %s\n",student[stud_no].name);
    printf("DEPARTMENT :           %s\n",student[stud_no].dept);
    printf("DOB:                   %d/%d/%d\n", student[stud_no].dob.dd, student[stud_no].dob.mm, student[stud_no].dob.yy);
    printf("NO OF BOOKS BORROWED : %d\n",student[stud_no].borrowed_book_no);

    if(student[stud_no].borrowed_book_no>0){
        printf("BORROWED BOOKS : \n\n");

        for(i=0;i<student[stud_no].borrowed_book_no;i++){
            printf("%s\n",student[stud_no].borrowed_books[i]);
        }
    }
    return_to();
}

//edit student info
void edit_info()
{
    system("cls");
    head_text("EDIT INFO");
    read_info();

    int loop,id,flag=0;
    char username[15];
    if(!strcmp(user,"student"))
        strcpy(username,student[stud_no].check.username);
    else{
        printf("Enter username: ");
        scanf("%s",username);
        for(loop=0;loop<user_no;loop++){
            if(!(strcmp(username,student[loop].check.username))){
                flag=1;
                stud_no=loop;
                break;
            }
        }
        if(flag==0){
            printf("USERNAME not found. Try again. Press any key...");
            getch();
            fflush(stdin);
            edit_info();
        }
    }



    printf("\nCURRENT INFO\n\n");

    printf("STUDENT ID:     %d\n",student[stud_no].id);
    printf("USERNAME :      %s\n",student[stud_no].check.username);
    printf("NAME :          %s\n",student[stud_no].name);
    printf("DEPARTMENT :    %s\n",student[stud_no].dept);
    printf("DATE OF BIRTH:  %d/%d/%d\n", student[stud_no].dob.dd, student[stud_no].dob.mm, student[stud_no].dob.yy);

    printf("\n\nEnter modified Info\n\n");

    check_id:

    printf("STUDENT ID:     ");
    scanf("%d",&id);
    //check if unique
    for(loop=0;loop<user_no;loop++){
        if((student[loop].id==id)&&(stud_no!=loop)){
            printf("ID is not unique. TRY again.\n\n");
            fflush(stdin);
            goto check_id;
        }
    }

    check_username:

    printf("USERNAME :      ");
    scanf("%s",username);

    for(loop=0;loop<user_no;loop++){
        if((!(strcmp(username,student[loop].check.username))&&(stud_no!=loop))){
            printf("USERNAME is not unique. TRY again.\n\n");
            fflush(stdin);
            goto check_username;
        }
    }

    student[stud_no].id=id;
    strcpy(student[stud_no].check.username,username);

    printf("NAME :          ");
    scanf("%s",student[stud_no].name);
    printf("DEPARTMENT :    ");
    scanf("%s",student[stud_no].dept);
    printf("DATE OF BIRTH :  ");
    scanf("%d/%d/%d\n", &student[stud_no].dob.dd, &student[stud_no].dob.mm, &student[stud_no].dob.yy);
    update_info();
    return_to();
}

//add book to record
void add_book()
{
    system("cls");
    read_book();
    head_text("ADD BOOKS PAGE");
    int loop,id,count=0,flag=1;

    FILE *fp;
    fp=fopen("books.txt","a");

    printf("\nENTER YOUR DETAILS BELOW:\n\n");
    printf("\nBook id: ");
    scanf("%d",&id);
    for(loop=0;loop<book_no;loop++){
        if(id==b[loop].id){
            printf("\n\nBOOK ID not available. Try again. \n\n\nPress any key...");
            getch();
            flag=0;
            break;
        }
    }
    if(flag==0)
        add_book();

    book_no++;
    b[book_no].id=id;

    printf("Book name: ");
    scanf("%s",&b[book_no].name);

    printf("Author name: ");
    scanf("%s",&b[book_no].author);

    strcpy(b[book_no].status,"available");

    fprintf(fp,"%d %s %s %s\n", b[book_no].id, b[book_no].name, b[book_no].author, b[book_no].status);

    fclose(fp);
    printf("\n\nBOOK SUCCESSFULLY ADDED\n");
    return_to();

}

//delete book from record
void delete_book()
{
    system("cls");
    head_text("DELETE BOOK PAGE");
    read_book();

    int loop,index,count=0;
    char name[NAME_LEN];

    printf("\n\nEnter book name to delete:  ");
    scanf("%s",&name);
    for(loop=0;loop<book_no;loop++){
        if(!(strcmp(name,b[loop].name))){
            count++;
            for(index=loop;index<book_no;index++){
                b[index].id=b[index+1].id;
                strcpy(b[index].author,b[index+1].author);
                strcpy(b[index].name,b[index+1].name);
                strcpy(b[index].status,b[index+1].status);

            }
            book_no--;
            --loop;
        }
    }
    if(count==0)
        printf("Book not available");
    else{
        printf("\n        Books available after deletion       ");
        printf("\n---------------------------------------------------------\n");
        printf("BOOK ID\t\tAUTHOR\t\t\tNAME\t\t\t\tSTATUS");
        for(loop=0;loop<book_no;loop++){
            printf("\n%d",b[loop].id);
            printf("\t\t%s",b[loop].author);
            printf("\t\t\t%s",b[loop].name);
            printf("\t\t\t\t%s",b[loop].status);
        }
        printf("\n\n\nTotal number of books available after deletion: %d",book_no);
        printf("\n\n\n\n");
    }
    update_book();
    return_to();
}

//return book
void return_book()
{
    system("cls");
    head_text("RETURN BOOK PAGE");
    read_book();

    int loop,flag=0,book,temp,num,pos;
    char name[NAME_LEN],status[15];

    printf("Enter book name: ");
    scanf("%s",&name);

    for(loop=0;loop<student[stud_no].borrowed_book_no;loop++)
    {
        if(!(strcmp(name,student[stud_no].borrowed_books[loop])))
        {
            //find position of book in structure
            for(book=0;book<book_no;book++){
                if(!(strcmp(b[book].name,name))){
                    pos=book;
                }
            }

            flag=1;
            printf("\nBook issued");
            printf("\n\n         Returned book details         ");
            printf("\n----------------------------------------------------------");
            printf("\nReturned Book id :         %d",b[pos].id);
            printf("\nReturned book author name: %s",b[pos].author);
            printf("\nReturned book name:        %s",b[pos].name);
            strcpy(b[loop].status,"available");
            printf("\nBook status:               %s",b[pos].status);

            num=student[stud_no].borrowed_book_no;
            //remove from borrowed books
            for(book=0;book<num;book++){
                if(!(strcmp(student[stud_no].borrowed_books[book],name))){
                   for(temp=book;temp<num;temp++){
                    strcpy(student[stud_no].borrowed_books[temp],student[stud_no].borrowed_books[temp+1]);
                   }
                   break;
                }
            }
            student[stud_no].borrowed_book_no--;
            update_info();
            update_book();
            break;
        }
        else
            continue;
    }
    if(flag==0)
        printf("\nBook not found to be borrowed! ");
    return_to();

}

//borrow book
void borrow_book()
{
    system("cls");
    head_text("BORROW BOOK PAGE");
    read_book();

    int loop,flag=0,num;
    char c,name[NAME_LEN],status[15];

    printf("Enter book name: ");
    scanf("%s",&name);

    for(loop=0;loop<book_no;loop++)
    {
        if((!(strcmp(name,b[loop].name)))&&(!(strcmp(b[loop].status,"available"))))
        {
            flag=1;
            printf("\n\nBook available");
            printf("\nDo you need the book (Y or N) :  ");
            fflush(stdin);
            scanf("%c",&c);
            if((c=='y')||(c=='Y')){

                if(student[stud_no].borrowed_book_no==5){
                    printf("\n\nA USER CANNOT BORROW MORE THAN 5 BOOKS\n\n");
                    return_to();
                }

                printf("\nBook issued\n");
                printf("\n          Issued book details         ");
                printf("\n----------------------------------------------------------");
                printf("\nIssued Book id :             %d",b[loop].id);
                printf("\nIssued book author name:     %s",b[loop].author);
                printf("\nIssued book name:            %s",b[loop].name);
                strcpy(b[loop].status,"borrowed");
                printf("\nBook status:               %s",b[loop].status);

                num=student[stud_no].borrowed_book_no;
                strcpy(student[stud_no].borrowed_books[num],b[loop].name);

                student[stud_no].borrowed_book_no++;

                update_info();
                update_book();
                printf("\nReturn the book within 15 days from today\n");
                break;
            }
        }
    }

    if(flag==0)
        printf("\nBook not available");
    return_to();

}
void search_book()
{
    system("cls");
    head_text("SEARCH BOOK");
    read_book();

    int choice,loop,flag=0,avail_book=0;
    char author[AUTHOR_LEN],name[NAME_LEN];

    printf("Search by : \n\n");
    printf("1.Title\n2.Author\n\n\nEnter choice => ");
    scanf("%d",&choice);

    if(choice==1){
        printf("\n\nEnter the Title of the book :  ");
        scanf("%s",&name);
        for(loop=0;loop<book_no;loop++){
            if(strcmp(name,b[loop].name)==0){
                avail_book++;
                if(avail_book==1){
                  printf("\nBOOK IS AVAILABLE\n\n\t\t\tBOOK DETAILS\n\n");
                }
                printf("BOOK NO %d :  \n",avail_book);
                printf("BOOK ID :\t%d\n",b[loop].id);
                printf("BOOK NAME :\t%s\n",b[loop].name);
                printf("AUTHOR NAME :\t%s\n",b[loop].author);
                printf("BOOK STATUS :\t%s\n",b[loop].status);
                printf("---------------------------------------------------\n\n");
                flag=1;
                continue;
            }
        }
    }

    else if(choice==2){
        printf("\n\nEnter Author name : ");
        scanf("%s",&author);
        for(loop=0;loop<book_no;loop++){
            if(strcmp(author,b[loop].author)==0){
                avail_book++;
                if(avail_book==1){
                   printf("\nBOOK IS AVAILABLE\n\n\t\t\tBOOK DETAILS\n\n");
                }
                printf("BOOK NO %d :  \n",avail_book);
                printf("BOOK ID :\t%d\n",b[loop].id);
                printf("BOOK NAME :\t%s\n",b[loop].name);
                printf("AUTHOR NAME :\t%s\n",b[loop].author);
                printf("BOOK STATUS :\t%s\n",b[loop].status);
                printf("PUBLISHED DATE :\t%d/%d/%d\n",b[loop].date.dd,b[loop].date.mm,b[loop].date.yy);
                printf("---------------------------------------------------\n\n");
                flag=1;
                continue;
            }
        }
    }
    else{
        printf("\n\n\nWRONG CHOICE!!\nTRY AGAIN.\n...");
        fflush(stdin);
        getch();
        search_book();
    }
    if(flag==0)
        printf("\n\n\nWE DON'T HAVE THE BOOK YOU REQUIRED\n");

    return_to();
}

void add_preference()
{
    system("cls");
    head_text("REQUEST TO ADD PREFERRED BOOKS IN THE LIBRARY");
    read_book();
    int loop,flag=0;
    char name[NAME_LEN],author[AUTHOR_LEN];

    printf("Enter the title of the book : ");
    scanf("%s",name);
    printf("Enter the author of the book : ");
    scanf("%s",author);

    for(loop=0;loop<book_no;loop++){
        if((!strcasecmp(b[loop].name,name))&&(!strcmp(b[loop].author,author))){
            flag=1;
            printf("\n\t\t\tTHE BOOK YOU PREFERED IS ALREADY AVAILABLE IN THE LIBRARY!! CHECK IN VIEW BOOKS!!\n\n");
            break;
        }
    }
    if(flag==0){
        FILE *fp;
        fp=fopen("prefer.txt","a");
        fprintf(fp,"%s %s\n",name,author);
        fflush(stdin);
        fclose(fp);
        printf("\n\t\tYOUR PREFERENCES ARE NOTED!! WE WILL TRY TO ADD THE BOOK AS SOON AS POSSIBLE!!\n\n");
    }
    return_to();
}



void view_preference()
{
    system("cls");
    head_text("VIEW PREFERENCES");
    FILE *fp;
    fp=fopen("prefer.txt","r");
    char author[AUTHOR_LEN],name[NAME_LEN];
    if(fp==NULL){
        printf("\t\tNo record of preferences!!\n\n");
    }
    else{
        printf("\t\t\tBOOK NAMES\t\tAUTHOR NAMES\n\n");
        while((fscanf(fp,"%s %s\n",name,author))!=EOF){
            printf("\t\t\t%s\t  -  \t%s\n",name,author);
        }
    }
    fclose(fp);
    return_to;
}

