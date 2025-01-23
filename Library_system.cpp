#include <iostream>
#include <algorithm>
#include <assert.h>

using namespace std;

// Maximum number of books and users the library system can handle
const int MAX_BOOKS = 100;
const int MAX_USERS = 100;

// structure representing a book in the library
struct book
{
    string name;                     // name of the book
    int id;                          // unique identifier (id) for the book
    int quantity;                    // number of copies available of the book
    int total_borrowed;              // number of persons borrowed this book
    int user_borrowed_id[MAX_USERS]; // the unique identifiers ids of persons that has borrowed the book

    // Default book constructor
    book()
    {
        name = "";
        id = -1;
        quantity = 0;
        total_borrowed = 0;
    }

    // Book constructor with parameters
    book(string name_, int id_, int quantity_)
    {
        name = name_;
        id = id_;
        quantity = quantity_;
        total_borrowed = 0;
    }

    // function to read the data for the book from the admin
    void read()
    {
        cout << "Enter the book id: ";
        cin >> id;
        cout << "Enter book's name: ";
        cin >> name;
        cout << "Enter quantity: ";
        cin >> quantity;
        total_borrowed = 0; // set the total number of persons that has borrowed this book to 0
    }

    // function to print book details
    void print()
    {
        cout << "id: " << id << "\t\tname: " << name << "\tquantity: " << quantity << "\ttotalborrowed: " << total_borrowed << "\n";
    }

    // function to add users borrowed this book
    void borrow(int &u)
    {
        user_borrowed_id[total_borrowed++] = u; // record the user id who borrowed the book
        quantity--;                             // decrement the number of books available in the library by 1
    }

    // function that help me in returning the book to the library and remove the user from the list of users borrowed this book
    // i used recursion function here for practice i think in big applications iterative would be better
    void shift_left_user(int arr[], int start, int len)
    {
        if (start == len)
            return;
        arr[start] = arr[start + 1];
        shift_left_user(arr, start + 1, len);
    }

    // function to return the book to the library and remove the user from list of users borrowed the book
    void return_book(int &s)
    {
        int index = -1;
        for (int i = 0; i < total_borrowed; i++)
        {
            if (user_borrowed_id[i] == s)
            {
                index = i;
                break;
            }
        }
        // check if the number of users more than 1 to shift
        if (total_borrowed > 1)
            shift_left_user(user_borrowed_id, index, total_borrowed);
        user_borrowed_id[total_borrowed] = 0;
        quantity++;       // increment the quantity of copies available for the book by 1
        total_borrowed--; // decrement the number of users borrowed the book by 1
    }
};

// global compare function to help me sorting the library by name
bool cmp_book_by_name(book &a, book &b)
{
    return a.name < b.name;
}

// global compare function to help me sorting the library by id
bool cmp_book_by_id(book &a, book &b)
{
    return a.id < b.id;
}

// structure representing a user in the library
struct user
{
    string name;                      // name of the user
    int id;                           // unique identifier (id) for the user
    int borrowed_books_id[MAX_BOOKS]; // ids for the books the user has borrowed
    int cnt;                          // number of books the user has borrowed

    // Default constructor for the user
    user()
    {
        name = "";
        id = -1;
    }

    // User constructor with parameters
    user(string name_, int id_)
    {
        name = name_;
        id = id_;
    }

    // function to read the data for the user
    void read()
    {
        cout << "The user name: ";
        cin >> name;
        cout << "The user id: ";
        cin >> id;
    }

    // function to print the user data
    void print()
    {
        cout << "User name: " << name << "\t\tUser id: " << id << "\t\tborrowed books ids: ";
        for (int i = 0; i < cnt; i++)
            cout << borrowed_books_id[i] << " ";
        cout << "\n";
    }

    // function to set the books ids that the user have borrowed
    void user_borrowing(int &b)
    {
        borrowed_books_id[cnt++] = b;
    }

    // check if the user has a book by id
    bool user_has_book(int &b)
    {
        bool here = false;
        for (int i = 0; i < cnt; i++)
        {
            if (borrowed_books_id[i] == b)
            {
                here = true;
                break;
            }
        }
        return here;
    }

    // function help me to remove a book from the list of borrowed books when the user returns a book
    // i used recursion here also but i think iterative way might be better in bigger scale
    void shift_left_book(int arr[], int start, int len)
    {
        if (start == len)
            return;
        arr[start] = arr[start + 1];
        shift_left_book(arr, start + 1, len);
    }

    // function to remove book from the list of books user borrowed
    void remove_book(int &b)
    {
        int index = -1;
        for (int i = 0; i < cnt; i++)
        {
            if (borrowed_books_id[i] == b)
            {
                index = i;
                break;
            }
        }
        // check if the number of books more than 1 to shift
        if (cnt > 1)
            shift_left_book(borrowed_books_id, index, cnt);
        borrowed_books_id[cnt] = 0; // reseting the last element in the array
        cnt--;                      // decrement the number of books user borrowed
    }
};

// structure for the main library system
struct library_system
{
    book books[MAX_BOOKS]; // books in the library
    user users[MAX_USERS]; // users in the library
    int total_books;       // total books in the library
    int total_users;       // total users in the library

    // Default constructor for the library_system
    library_system()
    {
        total_books = 0;
        total_users = 0;
    }

    // library_system constructor with parameters
    library_system(int total_books_, int total_users_)
    {
        total_books = total_books_;
        total_users = total_users_;
    }

    // menu of options that showed to admin to choose the request hewant from the program
    int menu()
    {
        while (true)
        {
            int n;
            cout << "\nPlease choose your request from the menu\n";
            cout << "Library menu:\n";
            cout << "1) Add book\n";
            cout << "2) Search books by prefix\n";
            cout << "3) Print who borrowed book by name\n";
            cout << "4) Print library by id\n";
            cout << "5) Print library by name\n";
            cout << "6) Add user\n";
            cout << "7) User borrow book\n";
            cout << "8) User return book\n";
            cout << "9) Print users\n";
            cout << "10) Exit\n";
            cin >> n; // choice entered by admin
            return n;
        }
    }

    // the run function that runs the application
    // the funciton takes the choice from the menu function and call corresponding fucntion to execute the request
    void run()
    {
        while (true)
        {
            int choice = menu();
            if (choice == 1)
                add_book();
            if (choice == 2)
                search_books_by_prefix();
            if (choice == 3)
                print_who_borrowed_book_by_name();
            if (choice == 4)
                print_library_by_id();
            if (choice == 5)
                print_library_by_name();
            if (choice == 6)
                add_user();
            if (choice == 7)
                user_borrow_book();
            if (choice == 8)
                user_return_book();
            if (choice == 9)
                print_users();
            if (choice == 10)
                break;
        }
    }

    // function to add book to the library
    void add_book()
    {
        books[total_books++].read();
        cout << "\nBook added successfully\n\n";
    }

    // function to search for a book by prefix in the library
    void search_books_by_prefix()
    {
        book suf[total_books]; // the books that match the prefix
        int cnt = 0;           // number of books match the prefix
        string query;          // the prefix to be entered by the admin
        cout << "Enter query: ";
        cin >> query;
        int k = 0;
        for (int i = 0; i < total_books; i++)
        {
            // make sure the query length smaller than book length
            if (query.length() > books[i].name.length())
                continue;
            if (prfx_name(books[i].name, query)) // check if the query is a prefix of the book
            {
                cnt++;               // increment the number of books
                suf[k++] = books[i]; // add this to the list of books that match the prefix
            }
        }
        cout << "\n";
        // if no books match the prefix
        if (cnt == 0)
        {
            cout << "NO books with such prefix\n\n";
            return;
        }
        cout << cnt << " books matching\n\n"; // number of books matched the prefix
        // printing the books matching the prefix
        for (int i = 0; i < cnt; i++)
            suf[i].print();
        cout << "\n\n\n";
    }

    // function to check if the queryis a string for the book name or not
    bool prfx_name(string name, string query, int start = 0)
    {
        if (start == query.length()) // base case
            return true;
        if (name[start] != query[start])
            return false;
        return prfx_name(name, query, start + 1);
    }

    // function to print who borrowed a book by book's name
    void print_who_borrowed_book_by_name()
    {
        int cnt = 0;                // number of users borrowed the book
        int users_has[total_users]; // list to save users that have borrowed the book
        int index = -1;
        string name; // name of the book to be entered by admin
        cout << "Enter the name of the book:\n";
        cin >> name;
        // search for the requested book
        for (int i = 0; i < total_books; i++)
        {
            if (books[i].name == name)
            {
                index = i;
                break;
            }
        }
        // if there is no book in library with that name
        if (index == -1)
        {
            cout << "\nThere is no book with this name\n";
            return;
        }
        // search in the list of users about users that has borrowed the book
        for (int i = 0; i < total_users; i++)
        {
            for (int j = 0; j < books[index].total_borrowed; j++)
            {
                if (books[index].user_borrowed_id[j] == users[i].id)
                {
                    cnt++;
                    cout << "User name: " << users[i].name << "\t\tUser id: " << users[i].id << "\n";
                }
            }
        }
        // if there are no users has borrowed the book
        if (cnt == 0)
            cout << "\nNo users borrowed that book\n\n";
    }

    // function to prin the library sorted by the id of the book
    void print_library_by_id()
    {
        // if the library is empty
        if (total_books == 0)
        {
            cout << "\nThere are no books to show\n\n";
            return;
        }
        sort(books, books + total_books, cmp_book_by_id); // sorting the library books by id

        cout << "Books sorted by id: \n\n";

        // printing library sorted by id
        for (int i = 0; i < total_books; i++)
            books[i].print();

        cout << "\n\n";
    }

    // funciton to print the library sorted by name
    void print_library_by_name()
    {
        // if the library is empty
        if (total_books == 0)
        {
            cout << "\nThere are no books to show\n\n";
            return;
        }
        sort(books, books + total_books, cmp_book_by_name); // sorting the library by name

        cout << "Books sorted by name:\n\n";

        // printing library sorted by name
        for (int i = 0; i < total_books; i++)
            books[i].print();

        cout << "\n\n";
    }

    // function to add users to the system
    void add_user()
    {
        users[total_users++].read();
        cout << "\nUser " << users[total_users - 1].name << " added successfully\n\n";
    }

    // function to allow user borrow books from the library
    void user_borrow_book()
    {
        string book_name;        // book_name to be entered by the admin
        string user_name;        // user_name wamt to to borrow the book entered by admin
        bool exist_user = false; // check if the user exists in the library system
        bool exist_book = false; // check if the book exists in the library system
        int index_book = -1;
        int index_user = -1;
        cout << "Enter the name of the user:\n";
        cin >> user_name;

        // search for user in the system
        for (int i = 0; i < total_users; i++)
        {
            if (users[i].name == user_name)
            {
                exist_user = true;
                index_user = i;
                break;
            }
        }

        // if user doesn't existin the system
        if (!exist_user)
        {
            cout << "\nUser not found\n\n";
            return;
        }
        cout << "Enter the name of the book " << user_name << " wants to borrow:\n";
        cin >> book_name;

        // search for the name of the book in the system
        for (int i = 0; i < total_books; i++)
        {
            if (books[i].name == book_name)
            {
                exist_book = true;
                index_book = i;
                break;
            }
        }

        // if the books doesn't exist in the system
        if (!exist_book)
        {
            cout << "\nBook not found!!\n\n";
            return;
        }

        // check if there is enough copies from the book user wants to borrow
        if (books[index_book].quantity == 0)
        {
            cout << "\nNot enough books right now\n\n";
            return;
        }

        // executing the process of borrowing
        users[index_user].user_borrowing(books[index_book].id);
        books[index_book].borrow(users[index_user].id);
        cout << "\nCongratulation. " << books[index_book].name << " Book borrowed successfully\n\n";
    }

    // function to return book to the library by user
    void user_return_book()
    {
        int book_idx;
        int user_idx;
        bool b = false;
        bool u = false;
        string user_name; // name of the user to be eneterd by admin
        cout << "Enter the user name\n";
        cin >> user_name;

        // search for user in the system
        for (int i = 0; i < total_users; i++)
        {
            if (users[i].name == user_name)
            {
                user_idx = i;
                u = true;
                break;
            }
        }

        // if the user doesn't exist in the system
        if (!u)
        {
            cout << "\nThis user doesn't exist\n\n";
            return;
        }
        string book_name;
        cout << "Enter the book name:\n";
        cin >> book_name;

        // search for the book in the system
        for (int i = 0; i < total_books; i++)
        {
            if (books[i].name == book_name)
            {
                book_idx = i;
                b = true;
                break;
            }
        }

        // if book doesn't exist
        if (!b)
        {
            cout << "\nThis book doesn't exist\n\n";
            return;
        }

        // check if this user has this book
        if (!(users[user_idx].user_has_book(books[book_idx].id)))
        {
            // if user don't have the book
            cout << users[user_idx].name << " don't have " << books[book_idx].name << "\n";
            return;
        }

        // executing the process of returning
        users[user_idx].remove_book(books[book_idx].id);
        books[book_idx].return_book(users[user_idx].id);
        cout << "\nCongratulations, " << books[book_idx].name << " book returned successfully\n\n";
    }

    // funciton to print all users in the system
    void print_users()
    {
        for (int i = 0; i < total_users; i++)
        {
            users[i].print();
        }
    }
};

int main()
{
    // running the library system
    library_system mylibrary;
    mylibrary.run();
    return 0;
}
