
#include "unity.h"

#include "book_management.h"
#include "user.h"

#include <stdlib.h>





void test_register_user(){

    int count; 
    
    //adding a user normally
    struct User user = create_User("duarte_teixeira", "andebol",0);
    count = register_User(user);

    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "User not registred properly");

/*
    //trying to add a user twice
    count = register_User(user);
    TEST_ASSERT_EQUAL_MESSAGE(count, -2, "Same User was added twice");
*/

}

void test_remove_user(){

    //removing a user normally
    struct User user5 = create_User("duarte_teixeira", "password doesn´t need to be equal",0);
    int count = remove_User(user5);
    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "User NOT removed properly");

/*
    //trying to remove a user that does not exist
    struct User user3 = create_User("unkown", "unkown",0);
    count = remove_User(user3);
    TEST_ASSERT_EQUAL_MESSAGE(count, -2, "User that did not exist not given as ignored");


*/
}

void test_store_users(){

    FILE *file = NULL;
    int count;

    //invalid file input
    count = store_Users(file);
    TEST_ASSERT_EQUAL_MESSAGE(count, -1, "Should have returned -1 for invalid file");

    //normal file input
    file = fopen("users_tests.txt", "w");
    count = store_Users(file);
    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "Users NOT stored properly");

    fclose(file);
}

void test_load_users(){

    FILE *file = NULL;
    int count;
    
    //invalid file input
    count = load_Users(file);
    TEST_ASSERT_EQUAL_MESSAGE(count, -1, "Should have returned -1 for invalid file");


    //normal file input
    file = fopen("users_tests.txt", "r");
    count = load_Users(file);
    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "Users NOT loaded properly");
    fclose(file);

}


void test_login_User(){


    //valid login
    int count = login_User("kikiborges", "what");
    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "User should have logged in");


}


void test_find_book_by_title_User(){


    int count; 

    count = find_book_by_title_User("Meditations");
    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "1 book should have been found");



}

void test_find_book_by_authors_User(){

    int count;

    count = find_book_by_authors_User("TZB");
    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "2 books should have been found");
}

void test_add_book_librarian(){

    //adding a book bas a valid librarian
    int count;
    struct Book book = create_Book("Digital Minimalism", "Cal Newport", 2016,1,0);
    count = add_Book_Librarian(book);

    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "Book should have been added but wasn't");


}


void test_remove_book_librarian(){

    //adding a book bas a valid librarian
    int count;
    struct Book book = create_Book("Digital Minimalism", "Cal Newport", 2016,1,0);    
    count = remove_Book_Librarian(book);

    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "Book should have been removed but wasn't");


}

void test_borrow_Book_User(){


    int count;

    count = borrow_Book_User("Gema", "TZB");
    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "Book should have been borrowed to user but wasn't");

}


void test_return_Book_User(){


    int count;
    count = return_Book_User();
    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "Book should have been returned but wasn't");


}


    

void setUp() {
	 //this function is called before each test, it can be empty
}

void tearDown() {
	 //this function is called after each test, it can be empty
}

int main() {
	UNITY_BEGIN();//macro for startup jobs that unity needs to perform 


    RUN_TEST(test_load_users);
    FILE *file = fopen("books_tests.txt", "r");
    load_books(file);
    fclose(file);


    RUN_TEST(test_register_user);
    print_UserArray_Database();
    RUN_TEST(test_remove_user);
    print_UserArray_Database();


    RUN_TEST(test_login_User);
    RUN_TEST(test_borrow_Book_User);
    RUN_TEST(test_return_Book_User);


    RUN_TEST(test_find_book_by_title_User);
    RUN_TEST(test_find_book_by_authors_User);


    logout_User();
    login_User("librarian", "librarian");
    RUN_TEST(test_add_book_librarian);
    RUN_TEST(test_remove_book_librarian);
    logout_User();


    print_UserArray_Database();
    print_BookArray_Database();


    RUN_TEST(test_store_users);
    cleanup_UserArray_Database();
    cleanup_BookArray_Database();


	return UNITY_END();// macro for cleanup jobs that unity needs to perform 
}