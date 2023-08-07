#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <stdio.h> // for fflush(stdin)

using namespace std;

// ********** Helper Functions ********** //

template <typename T>
void print_vector(const vector<T> &vec)
{
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << vec[i];
        if (i < vec.size() - 1)
            cout << ", ";
    }
    cout << "]";
}

void ask(string prompt, string &input)
{
    cout << prompt;
    getline(cin, input);
    fflush(stdin);
}

void ask(string prompt, auto &input)
{
    cout << prompt;
    while (!(cin >> input))
    {
        cout << "[ Invalid input ] : Try again \n";
        cout << prompt;
    }
    fflush(stdin);
}

void label(string text, string symbol, int line_width = 64)
{
    int width = line_width - text.length();

    for (int i = 0; i < width; i++)
    {
        cout << symbol;
    }

    cout << " [ " + text + " ] ";
    for (int i = 0; i < width; i++)
    {
        cout << symbol;
    }
    cout << "\n";
}

void show_options(vector<string> items, int start_from)
{
    int i = 0;
    if (start_from == -1)
    {
        cout << "  -X- |-1 | EXIT \n";
        cout << "  <-- | 0 | GO BACK \n\n";
        i = 2;
    }
    else if (start_from == 0)
    {
        cout << "  -X- |-1 | EXIT \n\n";
        i = 1;
    }
    for (int j = 1; i < items.size(); i++, j++)
    {
        cout << "  -⸻  | " + to_string(j) + " | " + items[i] + "\n";
    }
}

// ********** Forward Declaration of 'Librarian' Class ********** //
class Librarian;

// ********** Class Declarations ********** //

class Book
{
    friend class Librarian;
    friend class Library;

    string _id;
    string _name;
    string _author;
    int _n_books;
    int _n_in_shelf;
    int _n_reading;
    vector<string> _reader_ids;

public:
    Book() {}

    ~Book()
    {
        _id.resize(0);
        _name.resize(0);
        _author.resize(0);
        _n_books = 0;
        _n_in_shelf = 0;
        _n_reading = 0;
        _reader_ids.resize(0);
    }

    void input();

    void show();
};

class Reader
{
    friend class Librarian;
    friend class Library;

    string _name;
    string _id;
    vector<string> _book_being_read_ids;

public:
    Reader() {}

    ~Reader()
    {
        _name.resize(0);
        _id.resize(0);
        _book_being_read_ids.resize(0);
    }

    void input();

    void show();
};

class Library
{
    friend class Librarian;

    map<string, Book> _books_all;
    map<string, Book> _books_in_shelf;
    map<string, Book> _books_being_read;
    map<string, Librarian> _librarians;
    map<string, Reader> _readers_all;
    map<string, Reader> _readers_active;

public:
    Library() {}

    ~Library()
    {
        _books_all.clear();
        _books_in_shelf.clear();
        _books_being_read.clear();
        _librarians.clear();
        _readers_all.clear();
        _readers_active.clear();
    }

    void input_book();

    Librarian input_librarian();

    void input_reader();

    void show_book_by_id(string book_id);
    void show_book_all_list();
    void show_book_in_shelf_list();

    void show_librarian_by_id(string librarian_id);
    void show_librarian_all_list();

    void show_reader_by_id(string reader_id);
    void show_reader_all_list();
    void resign_librarian(string librarian_id);
};

class Librarian
{
    friend class Library;

    Library *_library;
    string _name;
    string _id;

public:
    Librarian() {}

    ~Librarian()
    {
        _library = nullptr;
        _name.resize(0);
        _id.resize(0);
    }

    void show();

    void add_existing_book(string book_id, int quantity);

    void add_book_to_being_read(string book_id, string reader_id);
    void return_book_after_reading(string book_id, string reader_id);
};

// ********** Book :: Class Methods ********** //

void Book::input()
{
    ask("Book ID      : ", _id);
    ask("Book Name    : ", _name);
    ask("Book Author  : ", _author);
    ask("Total Copies : ", _n_books);

    _n_in_shelf = _n_books;
    _n_reading = 0;
    _reader_ids = {};
}

void Book::show()
{
    cout << "Book ID                    : " + _id + "\n";
    cout << "Book Name                  : " + _name + "\n";
    cout << "Author                     : " + _author + "\n";
    cout << "Total Number of Books      : " + to_string(_n_books) + "\n";
    cout << "Number of Books in Shelf   : " + to_string(_n_in_shelf) + "\n";
    cout << "Number of Books Being Read : " + to_string(_n_reading) + "\n";
    cout << "Reader IDs                 : ";
    print_vector(_reader_ids);
    cout << "\n\n";
}

// ********** Reader :: Class Methods ********** //

void Reader::input()
{
    ask("Enter Reader's Name : ", _name);
    ask("Enter Reader's ID   : ", _id);

    _book_being_read_ids = {};
}

void Reader::show()
{
    cout << "Reader's Name : " + _name + "\n";
    cout << "Reader's ID   : " + _id + "\n";
    cout << "Book IDs      : ";
    print_vector(_book_being_read_ids);
    cout << "\n\n";
}

// ********** Library :: Class Methods ********** //

Librarian Library::input_librarian()
{
    Librarian librarian;
    ask("Librarian's Name : ", librarian._name);
    ask("Librarian's ID   : ", librarian._id);
    librarian._library = this;

    _librarians[librarian._id] = librarian;
    return librarian;
}

void Library::input_book()
{
    Book book;
    book.input();
    if (book._id == "" || book._name == "" || book._author == "")
    {
        cout << "\n\nSorry! Invalid Input.\n\n";
        return;
    }
    if (book._n_books < 1)
    {
        cout << "\n\nSorry! Invalid Input. Number of books must be greater than 0.\n\n";
        return;
    }
    _books_all[book._id] = book;
    _books_in_shelf[book._id] = book;
}

void Library::input_reader()
{
    Reader reader;
    reader.input();
    if (reader._id == "" || reader._name == "")
    {
        cout << "\n\nSorry! Invalid Input.\n\n";
        return;
    }
    _readers_all[reader._id] = reader;
}

void Library::resign_librarian(string librarian_id)
{
    if (_librarians.find(librarian_id) == _librarians.end())
    {
        cout << "\n\nPlease try again with a valid librarian id.\n\n";
        return;
    }

    cout << "\n\nLibrarian named '" + _librarians[librarian_id]._name + "' with id '" + librarian_id + "' has resigned.\nThanks for his/her service.\n\n";

    _librarians.erase(librarian_id);

    if (_librarians.size() == 0)
    {
        cout << "\n\nNow the library badly need a new librarian.\n\n";
        cout << "Please enter the details of a new librarian.\n\n[Sign up | Librarian]\n";
        input_librarian();
    }
}

void Library::show_librarian_by_id(string librarian_id)
{
    if (_librarians.find(librarian_id) == _librarians.end())
    {
        cout << "Librarian not found!\n";
        return;
    }
    _librarians[librarian_id].show();
}

void Library::show_librarian_all_list()
{
    if (_librarians.size() == 0)
    {
        cout << "No Librarian Found!\n";
        return;
    }
    cout << "Librarian List:\n\n";
    for (auto librarian : _librarians)
    {
        if (librarian.second._id == "")
            continue;
        librarian.second.show();
        cout << "\n\n";
    }
}

void Library::show_book_by_id(string book_id)
{
    if (_books_all.find(book_id) == _books_all.end())
    {
        cout << "Book not found!\n";
        return;
    }
    _books_all[book_id].show();
}

void Library::show_book_all_list()
{
    if (_books_all.size() == 0)
    {
        cout << "No Book Found!\n";
        return;
    }
    cout << "Book List:\n\n";
    for (auto book : _books_all)
    {
        if (book.second._id == "")
            continue;
        book.second.show();
        cout << "\n\n";
    }
}

void Library::show_book_in_shelf_list()
{
    if (_books_in_shelf.size() == 0)
    {
        cout << "No Book Found!\n";
        return;
    }
    cout << "Book List:\n\n";
    for (auto book : _books_in_shelf)
    {
        if (book.second._id == "")
            continue;
        book.second.show();
        cout << "\n\n";
    }
}

void Library::show_reader_by_id(string reader_id)
{
    if (_readers_all.find(reader_id) == _readers_all.end())
    {
        cout << "Reader not found!\n";
        return;
    }
    _readers_all[reader_id].show();
}

void Library::show_reader_all_list()
{
    if (_readers_all.size() == 0)
    {
        cout << "No reader found!\n";
        return;
    }
    cout << "Reader List:\n\n";
    for (auto reader : _readers_all)
    {
        reader.second.show();
        cout << "\n\n";
    }
}

// ********** Librarian :: Class Methods ********** //

void Librarian::show()
{
    cout << "Librarian's Name : " + _name + "\n";
    cout << "Librarian's ID   : " + _id + "\n";
}

void Librarian::add_existing_book(string book_id, int quantity)
{
    if (_library->_books_all.find(book_id) == _library->_books_all.end())
    {
        cout << "\n\nSorry! No such book exists in the library.\n\n";
        return;
    }

    if (quantity <= 1)
    {
        cout << "\n\nSorry! Invalid quantity. So, by default adding one copy of this book.\n\n";
        return;
    }

    _library->_books_all[book_id]._n_books += quantity;
    _library->_books_in_shelf[book_id]._n_books += quantity;
    _library->_books_being_read[book_id]._n_books += quantity;

    _library->_books_all[book_id]._n_in_shelf += quantity;
    _library->_books_in_shelf[book_id]._n_in_shelf += quantity;
    _library->_books_being_read[book_id]._n_in_shelf += quantity;

    cout << "\n\nSuccessfully added more books to the library.\n\n";
}

void Librarian::return_book_after_reading(string book_id, string reader_id)
{
    if (_library->_readers_all.find(reader_id) == _library->_readers_all.end())
    {
        cout << "\n\nSorry! No such reader exists in the library.\n\n";
        return;
    }
    if (_library->_books_all.find(book_id) == _library->_books_all.end())
    {
        cout << "\n\nSorry! No such book exists in the library.\n\n";
        return;
    }
    if (find(_library->_books_being_read[book_id]._reader_ids.begin(), _library->_books_being_read[book_id]._reader_ids.end(), reader_id) != _library->_books_being_read[book_id]._reader_ids.end())
    {
        try
        {
            _library->_books_all[book_id]._n_in_shelf += 1;
            _library->_books_in_shelf[book_id]._n_in_shelf += 1;
            _library->_books_being_read[book_id]._n_in_shelf += 1;

            _library->_books_all[book_id]._n_reading -= 1;
            _library->_books_in_shelf[book_id]._n_reading -= 1;
            _library->_books_being_read[book_id]._n_reading -= 1;

            _library->_books_all[book_id]._reader_ids.erase(remove(_library->_books_all[book_id]._reader_ids.begin(), _library->_books_all[book_id]._reader_ids.end(), reader_id), _library->_books_all[book_id]._reader_ids.end());

            _library->_books_in_shelf[book_id]._reader_ids.erase(remove(_library->_books_in_shelf[book_id]._reader_ids.begin(), _library->_books_in_shelf[book_id]._reader_ids.end(), reader_id), _library->_books_in_shelf[book_id]._reader_ids.end());

            _library->_books_being_read[book_id]._reader_ids.erase(remove(_library->_books_being_read[book_id]._reader_ids.begin(), _library->_books_being_read[book_id]._reader_ids.end(), reader_id), _library->_books_being_read[book_id]._reader_ids.end());

            _library->_readers_all[reader_id]._book_being_read_ids.erase(remove(_library->_readers_all[reader_id]._book_being_read_ids.begin(), _library->_readers_all[reader_id]._book_being_read_ids.end(), book_id), _library->_readers_all[reader_id]._book_being_read_ids.end());

            _library->_readers_active[reader_id]._book_being_read_ids.erase(remove(_library->_readers_active[reader_id]._book_being_read_ids.begin(), _library->_readers_active[reader_id]._book_being_read_ids.end(), book_id), _library->_readers_active[reader_id]._book_being_read_ids.end());

            cout << "\n\nAfter Reading, Reader named '" + _library->_readers_all[reader_id]._name + "' with id '" + reader_id + "' has returned book named '" + _library->_books_all[book_id]._name + "' with id '" + book_id + "'.\n\n";
        }
        catch (const exception &e)
        {
            cout << "\n\nSorry! Some error occured while returning the book.\n\n";
        }
    }
    else
    {
        cout << "\n\nInvalid Input! Please try again.\n\n";
    }
}

void Librarian::add_book_to_being_read(string book_id, string reader_id)
{
    if (_library->_readers_all.find(reader_id) == _library->_readers_all.end())
    {
        cout << "\n\nSorry! No such reader exists in the library.\n\n";
        return;
    }
    if (_library->_books_all[book_id]._n_in_shelf == 0)
    {
        cout << "\n\nSorry! No such book exists in the shelf.\n\n";
        return;
    }
    if (_library->_books_all.find(book_id) == _library->_books_all.end())
    {
        cout << "\n\nSorry! No such book exists in the library.\n\n";
        return;
    }
    if (find(_library->_books_being_read[book_id]._reader_ids.begin(), _library->_books_being_read[book_id]._reader_ids.end(), reader_id) != _library->_books_being_read[book_id]._reader_ids.end())
    {
        cout << "\n\nSorry! The reader is already reading this book.\n\n";
        return;
    }
    if (_library->_books_being_read[book_id]._n_reading > 0 && _library->_books_being_read[book_id]._n_reading == _library->_books_being_read[book_id]._n_books)
    {
        cout << "\n\nSorry! All the copies of this book are being read.\n\n";
        return;
    }
    try
    {
        _library->_books_all[book_id]._n_in_shelf -= 1;
        _library->_books_in_shelf[book_id]._n_in_shelf -= 1;
        _library->_books_being_read[book_id]._n_in_shelf -= 1;

        _library->_books_all[book_id]._n_reading += 1;
        _library->_books_in_shelf[book_id]._n_reading += 1;
        _library->_books_being_read[book_id]._n_reading += 1;

        _library->_books_all[book_id]._reader_ids.push_back(reader_id);
        _library->_books_in_shelf[book_id]._reader_ids.push_back(reader_id);
        _library->_books_being_read[book_id]._reader_ids.push_back(reader_id);

        _library->_readers_all[reader_id]._book_being_read_ids.push_back(book_id);
        _library->_readers_active[reader_id]._book_being_read_ids.push_back(book_id);

        cout << "\n\nReader named '" + _library->_readers_all[reader_id]._name + "' with id '" + reader_id + "' is now reading book named '" + _library->_books_all[book_id]._name + "' with id '" + book_id + "'.\n\n";
    }
    catch (const exception &e)
    {
        cout << "\n\nSorry! No such book exists in the library.\n\n";
    }
}

#endif // BOOK_HPP
