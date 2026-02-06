#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std; 

class Book {
private:
    string title; 
    string author; 
    bool isAvailable; 

public:
    Book(string t, string a) {
        title = t;
        author = a;
        isAvailable = true;
    }

    string getTitle() { return title; }
    string getAuthor() { return author; }
    bool isAvailableNow() { return isAvailable; }

    void setAvailability(bool status) {
        isAvailable = status;
    }
};

class Member {
private:
    string name; 
    int memberID; 
    vector<string> borrowedBooks;

public:
    Member(string n, int id) {
        name = n;
        memberID = id;
    }

    string getName() { return name; }
    int getMemberID() { return memberID; }
    vector<string> getBorrowedBooks() { return borrowedBooks; }

    bool hasBorrowed(string title) {
        for (int i = 0; i < borrowedBooks.size(); i++) {
            if (borrowedBooks[i] == title) {
                return true;
            }
        }
        return false;
    }

    void borrowBook(string title) {
        borrowedBooks.push_back(title);
    }

    void returnBook(string title) {
        for (vector<string>::iterator it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == title) {
                borrowedBooks.erase(it);
                return;
            }
        }
    }
};

class Library {
private:
    vector<Book> books; 
    vector<Member> members;
    int nextMemberID; 

public:
    Library() {
        nextMemberID = 1;
    }

    void addBook(string title, string author) {
        
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getTitle() == title) {
                cout << "Book with this title already exists." << endl;
                return;
            }
        }
        Book newBook(title, author);
        books.push_back(newBook);
        cout << "Book added successfully." << endl;
    }

    void removeBook(string title) {
        for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
            if (it->getTitle() == title) {
                if (!it->isAvailableNow()) {
                    cout << "Cannot remove a borrowed book." << endl;
                    return;
                }
                books.erase(it);
                cout << "Book removed successfully." << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void searchBook(string query) {
        bool found = false;
        for (int i = 0; i < books.size(); i++) {
            Book book = books[i];
            if (book.getTitle().find(query) != string::npos ||
                book.getAuthor().find(query) != string::npos) {
                cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor()
                     << ", Available: "
                     << (book.isAvailableNow() ? "Yes" : "No") << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No matching books found." << endl;
        }
    }

    void addMember(string name) {
        Member newMember(name, nextMemberID);
        members.push_back(newMember);
        cout << "Member added. ID: " << nextMemberID << endl;
        nextMemberID = nextMemberID + 1;
    }

    void borrowBook(int memberID, string title) {
        
        bool memberFound = false;
        for (int i = 0; i < members.size(); i++) {
            if (members[i].getMemberID() == memberID) {
                memberFound = true;
               
                bool bookFound = false;
                for (int j = 0; j < books.size(); j++) {
                    if (books[j].getTitle() == title) {
                        bookFound = true;
                        if (!books[j].isAvailableNow()) {
                            cout << "Book is currently not available." << endl;
                            return;
                        }
                        if (members[i].hasBorrowed(title)) {
                            cout << "Member already borrowed this book." << endl;
                            return;
                        }
                        books[j].setAvailability(false);
                        members[i].borrowBook(title);
                        cout << "Book borrowed successfully." << endl;
                        return;
                    }
                }
                if (!bookFound) {
                    cout << "Book not found." << endl;
                    return;
                }
            }
        }
        if (!memberFound) {
            cout << "Member not found." << endl;
        }
    }

    void returnBook(int memberID, string title) {
       
        bool memberFound = false;
        for (int i = 0; i < members.size(); i++) {
            if (members[i].getMemberID() == memberID) {
                memberFound = true;
                if (!members[i].hasBorrowed(title)) {
                    cout << "This member did not borrow that book." << endl;
                    return;
                }
                
                bool bookFound = false;
                for (int j = 0; j < books.size(); j++) {
                    if (books[j].getTitle() == title) {
                        bookFound = true;
                        books[j].setAvailability(true);
                        members[i].returnBook(title);
                        cout << "Book returned successfully." << endl;
                        return;
                    }
                }
                if (!bookFound) {
                    cout << "Book record not found." << endl;
                    return;
                }
            }
        }
        if (!memberFound) {
            cout << "Member not found." << endl;
        }
    }

    void displayBooks() {
        if (books.size() == 0) {
            cout << "No books in the library." << endl;
            return;
        }
        for (int i = 0; i < books.size(); i++) {
            Book book = books[i];
            cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor()
                 << ", Available: "
                 << (book.isAvailableNow() ? "Yes" : "No") << endl;
        }
    }

    void displayMembers() {
        if (members.size() == 0) {
            cout << "No members in the library." << endl;
            return;
        }
        for (int i = 0; i < members.size(); i++) {
            Member member = members[i];
            cout << "Name: " << member.getName() << ", ID: " << member.getMemberID() << endl;
            cout << "Borrowed Books: ";
            vector<string> borrowed = member.getBorrowedBooks();
            if (borrowed.size() == 0) {
                cout << "None";
            } else {
                for (int j = 0; j < borrowed.size(); j++) {
                    cout << borrowed[j] << " ";
                }
            }
            cout << endl;
        }
    }
};

void showMenu() {
    cout << "\nLibrary Management System Menu" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Remove Book" << endl;
    cout << "3. Search Book" << endl;
    cout << "4. Add Member" << endl;
    cout << "5. Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Display All Books" << endl;
    cout << "8. Display All Members" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Library library;

    
    library.addBook("The Great Gatsby", "F. Scott Fitzgerald");
    library.addBook("1984", "George Orwell");
    library.addMember("Emmanuel merinyo");
    library.addMember("Precious Dhahabu");

    int choice;
    int memberID;
    string title, author, query, name;

    do {
        showMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        if (choice == 1) {
            cout << "Enter title: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            library.addBook(title, author);
        } else if (choice == 2) {
            cout << "Enter title to remove: ";
            getline(cin, title);
            library.removeBook(title);
        } else if (choice == 3) {
            cout << "Enter search query (title or author): ";
            getline(cin, query);
            library.searchBook(query);
        } else if (choice == 4) {
            cout << "Enter member name: ";
            getline(cin, name);
            library.addMember(name);
        } else if (choice == 5) {
            cout << "Enter member ID: ";
            cin >> memberID;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter title to borrow: ";
            getline(cin, title);
            library.borrowBook(memberID, title);
        } else if (choice == 6) {
            cout << "Enter member ID: ";
            cin >> memberID;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter title to return: ";
            getline(cin, title);
            library.returnBook(memberID, title);
        } else if (choice == 7) {
            library.displayBooks();
        } else if (choice == 8) {
            library.displayMembers();
        } else if (choice == 9) {
            cout << "Exiting the system." << endl;
        } else {
            cout << "Invalid choice." << endl;
        }
    } while (choice != 9);

    return 0;
}
