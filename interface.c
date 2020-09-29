
#include "interface.h"

#include "book_management.h"
#include "user.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//static struct User *current_user = NULL;


//return a newly allocated string
static char *ask_question(const char *question) {

	printf("%s",question);

	const int size_step = 2;
	char *answer = malloc(size_step);
	answer[0] = 0; //now it's a string of length 0.

	//read until a new line in blocks of size_step  bytes at at time
	char *next_chunk = answer;
	int iteration = 0;
	do {
		answer = realloc(answer, size_step + iteration*size_step);
		next_chunk = answer + strlen(answer); //answer may have moved.
		fgets(next_chunk, size_step, stdin);

		next_chunk = answer + strlen(answer); //take the new read into account
		++iteration;
	} while (* (next_chunk-1) != '\n');

	*(next_chunk-1) = 0; //truncate the string eliminating the new line.

	return answer;
}


static void register_interface(){
    int err;
    		
    char * username = ask_question("Username: ");
    char * password = ask_question("Password: ");

    struct User user = create_User(username, password, NULL);

    err = register_User(user);

    free(username);
    free(password);

    if(err == -2){

        puts("\nUsername already exists. Registration Failed");
    }

    return;
}


static void login_menu_interface(){

	int choice = 7; //exit
    char* title;
    char* authors;
    char* year_str;
    char* copies_str;
    char* borrowed_str;
    int year, copies, borrowed, err;
    struct Book book;

	do {

		char * answer = ask_question("\nPlease enter next action:\n1) Search book by title\n2) Search book by author\n3) Borrow book\n4) Return book\n5) Add book(Librarian)\n6) Remove book(Librarian)\n7) Logout\nchoice: ");
		choice = atoi(answer);
		free(answer);

		switch (choice) {
			case 1:
    
                title = ask_question("Title: ");
                err = find_book_by_title_User(title);
                if(err == -2){

                    printf("\nNo book found with title: %s\n", title);

                }
                free(title);
				break;

			case 2:

                authors = ask_question("Authors: ");
                err = find_book_by_authors_User(authors);
                if(err == -2){

                    printf("\nNo book found with author(s): %s\n", authors);
                    
                }

                free(authors);
				break;

			case 3:

                title = ask_question("Title: ");
                authors = ask_question("Authors: ");

                err = borrow_Book_User(title, authors);
                if(err ==0){

                    puts("\nBook borrowed");
                }
                if(err == -1){

                    puts("\nPlease login first");                  
                }
                if(err == -2){

                    puts("\nYou can onky borrow one book at the time. Return the one you have first");
                }
                if(err == -3){

                    puts("\nNo copies to borrow for the specified book");
                }
                if(err == -4){

                    puts("\nBook not found");
                }                

                free(title);
                free(authors);


				break;

			case 4:
        
                err = return_Book_User();
                if(err ==0){

                    puts("\nBook returned");
                }
                if(err == -1){

                    puts("\nPlease login first");                  
                }
                if(err == -2){

                    puts("\nNo book to return");
                }
                if(err == -3){

                    puts("\nno registred borrowed copies for the specific book");
                }
                if(err == -4){

                    puts("\nBook not found");
                }     
				break;

			case 5:
                title = ask_question("Title: ");
                authors = ask_question("Authors: ");
                year_str = ask_question("Year: ");
                year = atoi(year_str);
                copies_str = ask_question("Number of copies available in the library: ");
                copies = atoi(copies_str);
                borrowed_str = ask_question("Number of copies borrowed (not in the library): ");
                borrowed = atoi(borrowed_str);

                book = create_Book(title, authors, year, copies, borrowed);
                free(title);
                free(authors);
                free(year_str);
                free(copies_str);
                free(borrowed_str);
                err = add_Book_Librarian(book);//this book is the one being added to the Database
                if(err ==0){

                    puts("\nBook added to the library");
                }
                if(err == -1){

                    puts("\nPlease login first");                  
                }
                if(err == -2){

                    puts("\nBook already exists in the library");
                }
                if(err == -3){

                    puts("\nOnly the librarian has permission to add books to the library");
                }
				break;

			case 6:

                title = ask_question("Title: ");
                authors = ask_question("Authors: ");
                year_str = ask_question("Year: ");
                year = atoi(year_str);
                copies_str = ask_question("Number of copies available in the library: ");
                copies = atoi(copies_str);
                borrowed_str = ask_question("Number of copies borrowed (not in the library): ");
                borrowed = atoi(borrowed_str);

                book = create_Book(title, authors, year, copies, borrowed);
                free(title);
                free(authors);
                free(year_str);
                free(copies_str);
                free(borrowed_str);
                err = remove_Book_Librarian(book);  
                free_Book(book);//remove_Book_Librarian only uses this book for comparison  
                if(err ==0){

                    puts("\nBook removed from the library");
                }
                if(err == -1){

                    puts("\nPlease login first");                  
                }
                if(err == -2){

                    puts("\nBook does not exist in the library");
                }
                if(err == -3){

                    puts("\nOnly the librarian has permission to remove books from the library");
                }
				break;
            case 7:
                err = logout_User();
                if(err ==0){

                    puts("\nLogged out");
                }
                if(err == -1){

                    puts("\nYou're already logged out");                  
                }
				break;
			default:
				printf("\nSorry, that doesn't seem to be an option\n");
		}

	} while (choice != 7);
    return;
}


static void login_interface(){

    int err;
    		
    char * username = ask_question("Username: ");
    char * password = ask_question("Password: ");


    err = login_User(username, password);

    free(username);
    free(password);

    if(err == -2){

        puts("\nLogin Failed");
    }else{

        login_menu_interface();
    }

    return;

}


static void init_library_interface(const char* books_file,const char* users_file){

    int err;
    FILE *file1 = fopen(books_file, "r");
    err = load_books(file1);

    if(err == -2){
        puts("\nError loading books");
    }
    if(err == -1){
        puts("\nInvalid file");
    }

    FILE *file2 = fopen(users_file, "r");
    err = load_Users(file2);

    if(err == -2){
        puts("\nError loading users");
    }
    if(err == -1){
        puts("\nInvalid file");
    }

    fclose(file1);
    fclose(file2);

    print_BookArray_Database();
    print_UserArray_Database();
    //not a very good practise to show all passwords
    //but doing it to check how the program is working

    return;
}

static void exit_library_interface(const char* books_file,const char* users_file){

    int err;

    FILE *file2 = fopen(users_file, "w");
    err = store_Users(file2);

    if(err == -2){
        puts("\nError storing users");
    }
    if(err == -1){
        puts("\nInvalid file");
    }

    FILE *file1 = fopen(books_file, "w");
    err = store_books(file1);

    if(err == -2){
        puts("\nError storing books");
    }
    if(err == -1){
        puts("\nInvalid file");
    }



    fclose(file1);
    fclose(file2);

    cleanup_BookArray_Database(); //frees allBooks
    cleanup_UserArray_Database(); //frees allUsers

    return;
}


static void main_menu_interface() {


	int choice = 3; //exit

	do {

		char * answer = ask_question("\nPlease enter next action:\n1) Register\n2) Login\n3) Quit\nchoice: ");
		choice = atoi(answer);
		free(answer);

		switch (choice) {
			case 1:
				register_interface();
				break;
			case 2:
				login_interface();
				break;
			case 3:
				puts("\nGoodbye");
				break;
			default:
				printf("\nSorry, that doesn't seem to be an option\n");
		}

	} while (choice != 3);

    return;

}


void run_interface() {

    init_library_interface("books.txt", "users.txt");

	main_menu_interface();

    exit_library_interface("books.txt", "users.txt");



	return;
}
