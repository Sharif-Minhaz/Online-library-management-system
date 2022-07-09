#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

void login();
void signup();
void b_add();
void b_delete();
void b_show();
void b_search();
void b_borrow();
void r_books();

struct user_info{
	char password[30];
	char rePassword[30];
	char user[30];
	char name[30];
}add, check;
struct user {
    char bookName[30];
    char writer[30];
    char year[10];
}add_book, check_book;
struct user_book {
    char username[30];
    char book[30];
    char day[10];
}borrow_info;

int logged_in=0, log_msg=0;
char borrow_book[30], borrow_user[30], ret_user[30];
int main() {
    int choice;
    int option=1;
    while (option) {
        system("color 9");
        printf("==========================================================\n");
        printf("||\t\t\t\t\t\t\t||\n");
        printf("||\t\tWELCOME TO THE ONLINE LIBRARY\t\t||\n");
        printf("||\t\t\t\t\t\t\t||\n");
        printf("==========================================================\n");
        //Available options
        printf("\n\t>> ALL AVAILABLE OPTIONS:\n");
        printf("\n\t1: Login\n");
        printf("\n\t2: Signup\n");
        printf("\n\t3: Add books (Admin V code required)\n");
        printf("\n\t4: Delete all books (Admin V code required)\n");
        printf("\n\t5: Show all books and history\n");
        printf("\n\t6: Search books\n");
        printf("\n\t7: Borrow books (User's login required)\n");
        printf("\n\t8: Return books (User's login required)\n");
        printf("\n\t9: Exit\n");
        printf("\n\t>> Please choose your option: ");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                logged_in=0;
                log_msg=0;
                login();
                break;
            case 2:
                signup();
                break;
            case 3:
                b_add();
                break;
            case 4:
                b_delete();
                break;
            case 5:
                b_show();
                break;
            case 6:
                b_search();
                break;
            case 7:
                b_borrow();
                break;
            case 8:
                r_books();
                break;
            case 9:
                goto ending;
            default:
                printf("Please choose from the above options\n");
        }
        printf("\nDo you want to continue(Type 0(No) or 1(Yes))?\n");
        scanf("%d", &option);
        if(option==1) {
            system("cls");
        }
    }
    ending:
    return 0;
}
//login (reading data)
void login() {
    system("cls");
    system("color 3");
    if(log_msg==1) {
        printf("<------Log in first----->\n");
    }
    FILE *fp;
    fp = fopen("stored_data.txt","r");
    printf("\nEnter your username: ");
    scanf("%s", check.name);
    printf("Enter your password: ");
    scanf("%s", check.password);
    while (fscanf(fp, "%s %s %s %s\n", add.password, add.rePassword, add.user, add.name) != EOF){
        if (strcmp(check.name, add.name) == 0 && strcmp(check.password, add.password) == 0){
            fclose(fp);
            system("cls");
            system("color 2");
            printf("Login Successful! welcome %s.\n",check.name);
            strcpy(borrow_user,check.name);
            logged_in=1;
            if(log_msg==1) {
                b_borrow();
            }
        }
        else{
            system("cls");
            system("color 4");
            printf("Wrong username or password.\n");
        }
	}
	fclose(fp);
    fp = fopen("borrowed_books_info.txt","r");
    while (fscanf(fp,"\n%s %s %s",borrow_info.username,borrow_info.book,borrow_info.day) != EOF){
        if(strcmp(check.name,borrow_info.username)==0) {
            printf("\nUser %s borrowed %s Book for %s days\n",check.name,borrow_info.book,borrow_info.day);
        }
    }
	fclose(fp);
}
//Sign up (store data)
void signup() {
    int checkPassword=0;
    system("cls");
    system("color 3");
    FILE *fp;
    fp = fopen("stored_data.txt","a+");
    printf("<-----Register New Account----->\n");
    printf("Enter your name: ");
    scanf("%s", add.user);
    while (checkPassword == 0){
	password:
		printf("Enter the password: ");
		scanf("%s", add.password);
		printf("Re-enter the password: ");
		scanf("%s", add.rePassword);
		if (strcmp(add.password, add.rePassword) == 0){
			checkPassword = 1;
			printf("Password matched!\n");
		}
		else
		{
			printf("Password don't match!\n");
			goto password;
		}
	}
    printf("Now add your username: ");
	scanf("%s", add.name);
	fprintf(fp, "%s %s %s %s\n", add.password, add.rePassword, add.user, add.name);
	fclose(fp);
	system("cls");
	system("color 2");
	printf("\nNew user's information added successfully!\n");
}
//Add new books (store data)
void b_add() {
    system("cls");
    system("color 3");
    int nOfBooks, year, vCode, admin=201353001;
    printf("Admin verification code: ");
    scanf("%d",&vCode);
    if(admin==vCode) {
        printf("Welcome!\n");
        FILE *fp;
        fp = fopen("all_books_info.txt","a+");
        printf("How many books you want to add?\n");
        scanf("%d",&nOfBooks);
        for(int i=0;i<nOfBooks;i++) {
            printf("\nEnter book name: ");
            scanf("%s",add_book.bookName);
            printf("Enter writer name: ");
            scanf("%s",add_book.writer);
            printf("Enter published year: ");
            scanf("%s",&add_book.year);
            fprintf(fp,"\n%s\t\t%s (%s)",add_book.bookName,add_book.writer,add_book.year);
        }
        if(nOfBooks>0) {
            system("cls");
            system("color 2");
            printf("\nBooks added successfully.\n");
        }
        fclose(fp);
    }
    else {
        system("cls");
        system("color 4");
        printf("Wrong verification code.\n");
    }
}
//Deleting any book
void b_delete() {
    system("cls");
    system("color 3");
    int vCode,admin=201353001,confirmation=0;
    printf("Admin verification code: ");
    scanf("%d",&vCode);
    if(admin==vCode) {
        printf("Welcome!\n");
        printf("Are you sure you want to delete all the books?\n");
        printf("Type 1(yes) or 0(no)\n");
        printf("Confirmation: ");
        scanf("%d",&confirmation);
        if(confirmation==1) {
            system("cls");
            system("color 2");
            FILE *fp;
            fp = fopen("all_books_info.txt","w");
            fclose(fp);
            printf("All books information deleted successfully.\n");
        }
        else if(confirmation==0) {
            system("cls");
            system("color 5");
            printf("Books information will be retained.\n");
        }
        else {
            system("cls");
            system("color 4");
            printf("Type correctly.\n");
        }
    }
    else {
        system("cls");
        system("color 4");
        printf("Wrong verification code.\n");
    }

}
//Displaying all books
void b_show() {
    system("cls");
    system("color 3");
    char available[100];
    FILE *fp;
    fp = fopen("all_books_info.txt","r");
    printf("All available books are: \n");
    printf("\nBooks name\t\tWriter names and published year");
    printf("\n------------------\t--------------------------------");
    while(!feof(fp)) {
        fgets(available,100,fp);
        printf("%s",available);
    }
    fp = fopen("borrowed_books_info.txt","r");
    printf("\n<-------Recent History------>\n");
    while (fscanf(fp,"\n%s %s %s",borrow_info.username,borrow_info.book,borrow_info.day) != EOF){
        if(strcmp(check.name,borrow_info.username)==0) {
            printf("\nUser %s borrowed %s Book for %s days\n",check.name,borrow_info.book,borrow_info.day);
        }
    }
    fclose(fp);
}
//Searching==========================>
void b_search() {
    system("cls");
    system("color 3");
    FILE *fp;
    fp = fopen("all_books_info.txt","r");
    printf("\nEnter the book name: ");
    scanf("%s", check_book.bookName);
    while (fscanf(fp,"%s%s%s",add_book.bookName,add_book.writer,add_book.year) != EOF){
        if (strcmp(add_book.bookName,check_book.bookName) == 0){
            system("cls");
            system("color 2");
            printf("\n%s  --> by %s %s book found.\n",check_book.bookName,add_book.writer,add_book.year);
            break;
        }
        else{
            system("cls");
            system("color 4");
            printf("'%s' book don't available right now.\n",check_book.bookName);
        }
	}
	fclose(fp);
}
//comparing two string
void b_borrow() {
    system("cls");
    system("color 3");
    FILE *fp;
    fp = fopen("all_books_info.txt","r");
    if(logged_in==1){
        b_show();
        printf("\n\nNote: Write the books name correctly.");
        printf("\nWhich book you want to borrow: ");
        scanf("%s",borrow_book);
        printf("For how many days: ");
        scanf("%s",borrow_info.day);
        while (fscanf(fp,"%s%s%s",add_book.bookName,add_book.writer,add_book.year) != EOF){
            if (strcmp(add_book.bookName,borrow_book) == 0) {
                system("cls");
                system("color 2");
                printf("\nBorrowed %s book successfully for %s days.\n",add_book.bookName,borrow_info.day);
                printf("Borrowed by %s.\n",borrow_user);
                printf("<-----------Current status--------->\n");
                strcpy(borrow_info.username,borrow_user);
                strcpy(borrow_info.book,borrow_book);
                FILE *fp;
                fp = fopen("borrowed_books_info.txt","a+");
                fprintf(fp,"\n%s %s %s",borrow_info.username,borrow_info.book,borrow_info.day);
                fclose(fp);
                break;
            }
            else {
                system("cls");
                system("color 4");
                printf("\nThe book doesn't exist or already borrowed maximum books.\n");
            }
        }
    }
    else {
        log_msg=1;
        login();
    }
    fclose(fp);
}
//returning bookd
void r_books() {
    system("cls");
    system("color 3");
    int choices;
    printf("Enter your username for returning your book: ");
    scanf("%s",ret_user);
    FILE *fp;
    fp = fopen("borrowed_books_info.txt","r");
    while (fscanf(fp,"\n%s %s %s",borrow_info.username,borrow_info.book,borrow_info.day) != EOF){
        if(strcmp(ret_user,borrow_info.username)==0) {
            printf("\nUser %s borrowed %s Book for %s days\n",ret_user,borrow_info.book,borrow_info.day);
        }
    }
    printf("\nDo you want to return those books?\n");
    printf("Type 0 for no 1 for yes: ");
    scanf("%d",&choices);
    fp = fopen("borrowed_books_info.txt","a+");
    if(choices==1){
        while (fscanf(fp,"\n%s %s %s",borrow_info.username,borrow_info.book,borrow_info.day) != EOF){
            if(strcmp(ret_user,borrow_info.username)==0) {
                fprintf("\n%s %s %s\n",NULL,NULL,NULL);
            }
        }
    }
    else {
        printf("\nBooks retained.\n");
    }
	fclose(fp);
}
