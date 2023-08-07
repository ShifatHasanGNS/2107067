#include "Library.hpp"

Library lib;
Librarian admin;

enum STATE
{
    MAIN_PAGE,
    ADMIN_PAGE,
    LIBRARY_PAGE,
    BOOK_PAGE,
    READER_PAGE,
    EXIT,
};

STATE state = MAIN_PAGE;

void reader_page()
{
    state = READER_PAGE;
    cout << "\n";
    label("Reader Section", "▛▜▙▟", 15);
    cout << "\n";

    // For Librarian Page
    vector<string> reader_manu = {
        "Exit",
        "Go Back",
        "Add New Reader",
        "Show Reader By ID",
        "Show List Of All Readers",
        "Take A Book",
        "Return A Book After Reading",
    };

    show_options(reader_manu, -1);

    int choice;
    ask("\nSelect an option :  ", choice);
    cout << "\n\n";

    if (choice == -1) // Exit
    {
        state = EXIT;
    }
    else if (choice == 0) // Go Back
    {
        state = LIBRARY_PAGE;
    }
    else if (choice == 1) // Add New Reader
    {
        lib.input_reader();
        cout << "\n\nNew Reader Added Successfully!\n";
    }
    else if (choice == 2) // Show Reader By ID
    {
        string id;
        ask("Enter Reader ID :  ", id);
        cout << "\n\n";
        lib.show_reader_by_id(id);
    }
    else if (choice == 3) // Show List Of All Readers
    {
        cout << "\n\n";
        lib.show_reader_all_list();
    }
    else if (choice == 4) // Take A Book
    {
        string reader_id, book_id;
        ask("Enter Reader ID :  ", reader_id);
        ask("Enter Book ID   :  ", book_id);
        cout << "\n\n";
        admin.add_book_to_being_read(book_id, reader_id);
    }
    else if (choice == 5) // Return A Book After Reading
    {
        string reader_id, book_id;
        ask("Enter Reader ID :  ", reader_id);
        ask("Enter Book ID   :  ", book_id);
        cout << "\n\n";
        admin.return_book_after_reading(book_id, reader_id);
    }
    else // Invalid Choice
    {
        cout << "Invalid Choice!\n";
    }
}

void book_page()
{
    state = BOOK_PAGE;
    cout << "\n";
    label("Book Section", "▛▜▙▟", 15);
    cout << "\n";

    // For Librarian Page
    vector<string> book_manu = {
        "Exit",
        "Go Back",
        "Add New Book",
        "Add More Copies Of A Book",
        "Show Book By ID",
        "Show List Of All Books",
        "Show List Of Available Books",
    };

    show_options(book_manu, -1);

    int choice;
    ask("\nSelect an option :  ", choice);
    cout << "\n\n";

    if (choice == -1) // Exit
    {
        state = EXIT;
    }
    else if (choice == 0) // Go Back
    {
        state = LIBRARY_PAGE;
    }
    else if (choice == 1) // Add New Book
    {
        lib.input_book();
        cout << "\n\nNew Book Added Successfully!\n";
    }
    else if (choice == 2) // Add More Copies Of A Book
    {
        string id;
        int quantity;
        ask("Enter Book ID  :  ", id);
        ask("Enter Quantity :  ", quantity);
        admin.add_existing_book(id, quantity);
    }
    else if (choice == 3) // Show Book By ID
    {
        string id;
        ask("Enter Book ID :  ", id);
        cout << "\n\n";
        lib.show_book_by_id(id);
    }
    else if (choice == 4) // Show List Of All Books
    {
        cout << "\n\n";
        lib.show_book_all_list();
    }
    else if (choice == 5) // Show List Of Available Books
    {
        cout << "\n\n";
        lib.show_book_in_shelf_list();
    }
    else // Invalid Choice
    {
        cout << "Invalid Choice!\n";
    }
}

void library_page()
{
    state = LIBRARY_PAGE;
    cout << "\n";
    label("Library", "▛▜▙▟", 15);
    cout << "\n";

    // For Librarian Page
    vector<string> library_manu = {
        "Exit",
        "Go Back",
        "Book Section    (For Book Related Functionalities)",
        "Reader Section  (For Reader Related Functionalities)",
    };

    show_options(library_manu, -1);

    int choice;
    ask("\nSelect an option :  ", choice);
    cout << "\n\n";

    if (choice == -1) // Exit
    {
        state = EXIT;
    }
    else if (choice == 0) // Go Back
    {
        state = ADMIN_PAGE;
    }
    else if (choice == 1) // Book Section
    {
        book_page();
    }
    else if (choice == 2) // Reader Section
    {
        reader_page();
    }
    else // Invalid Choice
    {
        cout << "Invalid Choice!\n";
    }
}

void admin_page()
{
    state = ADMIN_PAGE;
    cout << "\n";
    label("Admin Panel", "▛▜▙▟", 15);
    cout << "\n";

    vector<string> admin_manu = {
        "Exit",
        "Go Back",
        "Add Librarian",
        "Show Librarian By ID",
        "Show All Librarians",
        "Resign Librarian",
    };

    show_options(admin_manu, -1);

    int choice;
    ask("\nSelect an option :  ", choice);
    cout << "\n\n";

    if (choice == -1) // Exit
    {
        state = EXIT;
    }
    if (choice == 0) // Go Back
    {
        state = MAIN_PAGE;
    }
    else if (choice == 1) // Add Librarian
    {
        admin = lib.input_librarian();
        cout << "\n\nNew Librarian Added Successfully!\n";
    }
    else if (choice == 2) // Show Librarian By ID
    {
        string id;
        ask("Enter Librarian ID :  ", id);
        cout << "\n\n";
        lib.show_librarian_by_id(id);
    }
    else if (choice == 3) // Show All Librarians
    {
        cout << "\n\n";
        lib.show_librarian_all_list();
    }
    else if (choice == 4) // Resign Librarian
    {
        string id;
        ask("Enter Librarian ID :  ", id);
        cout << "\n\n";
        lib.resign_librarian(id);
        cout << "\n";
    }
    else // Invalid Choice
    {
        cout << "Invalid Choice!\n";
    }
}

void main_page()
{
    state = MAIN_PAGE;
    cout << "\n";
    label("Main Page", "▛▜▙▟", 15);
    cout << "\n";

    vector<string> main_manu = {
        "Exit",
        "Goto Admin Panel  (to add librarian and librarian related functionalities)",
        "Goto Library      (to add book/reader and book/reader related functionalities)",
    };

    show_options(main_manu, 0);

    int choice;
    ask("\nSelect an option :  ", choice);
    cout << "\n\n";

    if (choice == -1 || choice == 0)
    {
        state = EXIT;
        return;
    }
    else if (choice == 1)
    {
        admin_page();
    }
    else if (choice == 2)
    {
        library_page();
    }
    else // Invalid Choice
    {
        cout << "Invalid Choice!\n";
    }
}

int main()
{
    label(" The Library ", "▛▜▙▟", 20);
    cout << "\n\n";

    while (true)
    {
        if (state == EXIT) // Exit
        {
            break;
        }
        else if (state == MAIN_PAGE) // Main Page
        {
            main_page();
        }
        else if (state == ADMIN_PAGE) // Admin Page
        {
            admin_page();
        }
        else if (state == LIBRARY_PAGE) // Library Page
        {
            library_page();
        }
        else if (state == BOOK_PAGE) // Book Page
        {
            book_page();
        }
        else if (state == READER_PAGE) // Reader Page
        {
            reader_page();
        }
        else
        {
            main_page();
        }
    }

    //* ---------------------------------------------------- *//

    // END OF PROGRAM
    cout << "Press ENTER to Leave The Library...\n\n\n";
    cin.ignore();
    return 0;
}
