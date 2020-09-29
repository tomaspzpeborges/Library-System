
#include "unity.h"

#include "book_management.h"
#include <stdlib.h>



void test_store_books(){

    FILE *file = NULL;
    int count;

    //invalid file input
    //count = store_books(file);
    //TEST_ASSERT_EQUAL_MESSAGE(count, -1, "Should have returned -1 for invalid file");

    //normal file input
    file = fopen("books_tests.txt", "w");
    count = store_books(file);
    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "Books NOT stored properly");
    fclose(file);

    //valid but empty valid




}

void test_load_books(){

    FILE *file = NULL;
    int count;
    

    //invalid file input
    count = load_books(file);
    TEST_ASSERT_EQUAL_MESSAGE(count, -1, "Should have returned -1 for invalid file");


    //normal file input
    file = fopen("books_tests.txt", "r");
    count = load_books(file);
    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "Books NOT loaded properly");
    fclose(file);


}

void test_add_book(){

    int count; 
    
    //adding a book normally
    struct Book book = create_Book("Bold","Random Guy",2019,2,0);
    count = add_book(book);
    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "Book not added properly");


    //trying to add a book twice
    count = add_book(book);
    TEST_ASSERT_EQUAL_MESSAGE(count, -2, "Same book was added twice");


/*
    //Checking if memory allocation is working the right way
    struct Book book3 = create_Book("Quadrado","TZB",2020,1,0);

    count = add_book(book3);
    free_Book(book3);

    book3 = create_Book("Bola", "TZB", 2021,1,0);//previous "Quadrado" becomes "Bola" so this will be considered a repeated book
    count = add_book(book3);

    TEST_ASSERT_EQUAL_MESSAGE(count, -2, "Should have given error for repeated book (altered existing allocated memory");
    //remove_book(book3);
*/

}

void test_remove_book(){


    //removing a book normally
    struct Book book5 = create_Book("Bold","Random Guy",2019,2,0);
    int count = remove_book(book5);
    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "Book NOT removed properly");
    free_Book(book5);


    //trying to remove a book that does not exist
    struct Book book2 = create_Book("unkown", "unkown", 2020,1,0);
    count = remove_book(book2);
    TEST_ASSERT_EQUAL_MESSAGE(count, -2, "Book that did not exist not given as ignored");
    free_Book(book2);

    //print_database();

}

void test_find_book_by_title(){

    //looking for a non existing title
    struct BookArray books1 = find_book_by_title("unkown");
    TEST_ASSERT_NULL_MESSAGE(books1.array,"BookArray.array should be null when no book is found");

    //looking for a title that exists
    struct BookArray books2 = find_book_by_title("Forma"); //this book needs to exist
    TEST_ASSERT_EQUAL_MESSAGE(books2.books_number, 1, "Should have found 1 book when looking for title 'Forma'");
    //print_BookArray(books);
    free(books2.array);


}

void test_find_book_by_author(){


    //looking for a non existing title
    struct BookArray books1 = find_book_by_author("unkown");
    TEST_ASSERT_NULL_MESSAGE(books1.array,"BookArray.array should be null when no book is found");

    //looking for an author that exists
    struct BookArray books2 = find_book_by_author("TZB"); //this book needs to exist
    TEST_ASSERT_EQUAL_MESSAGE(books2.books_number, 2, "Should have found 2 books when looking for authors 'TZB'");
    //print_BookArray(books);
    free(books2.array);

}

void test_find_book_by_year(){


    //looking for a non existing title
    struct BookArray books1 = find_book_by_year(10);
    TEST_ASSERT_NULL_MESSAGE(books1.array,"BookArray.array should be null when no book is found");

    //looking for a year that exists
    struct BookArray books2 = find_book_by_year(2020); //this book needs to exist
    TEST_ASSERT_EQUAL_MESSAGE(books2.books_number, 1, "Should have found 2 books when looking for year 2020");
    //print_BookArray(books);
    free(books2.array);


}


void test_borrow_book(){

    int count;

    //trying to borrow an existing Book
    count = borrow_Book("Gema", "TZB");
    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "Book NOT lent properly");

    //trying to borrow an existing Book, but with no copies left
    count = borrow_Book("Gema", "TZB");
    TEST_ASSERT_EQUAL_MESSAGE(count, -3, "Book with no copies left was still borrowed");


    //trying to borrow a Book that it is not in the database
    count = borrow_Book("unkown", "unkown");
    TEST_ASSERT_EQUAL_MESSAGE(count, -4, "Book that was not in the library was given as borrowed");



}


void test_return_book(){

    int count;

    //trying to return a a book that was previously lent
    count = return_Book("Gema", "TZB");
    TEST_ASSERT_EQUAL_MESSAGE(count, 0, "Book NOT returned properly");

    //trying to return an existing Book, but with no registred borrowed copies
    count = return_Book("Gema", "TZB");
    TEST_ASSERT_EQUAL_MESSAGE(count, -3, "Book with no registred copies borrowed was returned");


    //trying to return a Book that it is not in the database
    count = return_Book("unkown", "unkown");
    TEST_ASSERT_EQUAL_MESSAGE(count, -4, "Book that was not in the library was given as returned");


}



void setUp() {
	 //this function is called before each test, it can be empty
}

void tearDown() {
	 //this function is called after each test, it can be empty
}

int main() {
	UNITY_BEGIN();//macro for startup jobs that unity needs to perform 


	RUN_TEST(test_load_books);
    RUN_TEST(test_add_book);
    //print_BookArray_Database();
    RUN_TEST(test_remove_book); 
    RUN_TEST(test_borrow_book);
    RUN_TEST(test_return_book);
    //print_BookArray_Database();
    RUN_TEST(test_store_books);


    RUN_TEST(test_find_book_by_title);
    RUN_TEST(test_find_book_by_author);
    RUN_TEST(test_find_book_by_year);

        
    cleanup_BookArray_Database();
    //print_BookArray_Database();

	return UNITY_END();// macro for cleanup jobs that unity needs to perform 
}