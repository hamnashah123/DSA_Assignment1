#include <iostream>
#include <string>
using namespace std;

// Node for each character
struct CharNode {
    char ch;
    CharNode* prev;
    CharNode* next;
    CharNode(char c) : ch(c), prev(NULL), next(NULL) {}
};

class TextEditor {
private:
    CharNode* head;   // start of text
    CharNode* tail;   // end of text
    CharNode* cursor; // cursor points to position (before cursor char)

public:
    TextEditor() {
        head = tail = NULL;
        cursor = NULL; // initially before any character
    }

    // Insert a character at cursor position
    void insertChar(char c) {
        CharNode* newNode = new CharNode(c);

        if (head == NULL) {
            // empty text
            head = tail = newNode;
            cursor = newNode; // cursor after this char
        } else if (cursor == NULL) {
            // insert at beginning
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            cursor = newNode; 
        } else {
            // insert after cursor
            newNode->prev = cursor;
            newNode->next = cursor->next;
            if (cursor->next != NULL) cursor->next->prev = newNode;
            cursor->next = newNode;
            if (cursor == tail) tail = newNode;
            cursor = newNode; // move cursor after new char
        }
        display("After insert '" + string(1, c) + "': ");
    }

    // Delete character before cursor
    void deleteChar() {
        if (cursor == NULL) {
            // nothing to delete (at start)
            display("After delete: ");
            return;
        }

        CharNode* toDelete = cursor;

        if (toDelete->prev != NULL)
            toDelete->prev->next = toDelete->next;
        else
            head = toDelete->next;

        if (toDelete->next != NULL)
            toDelete->next->prev = toDelete->prev;
        else
            tail = toDelete->prev;

        cursor = toDelete->prev; // move cursor left
        delete toDelete;

        display("After delete: ");
    }

    // Move cursor left
    void moveLeft() {
        if (cursor != NULL) cursor = cursor->prev;
        display("After move left: ");
    }

    // Move cursor right
    void moveRight() {
        if (cursor == NULL && head != NULL) {
            cursor = head; // move right from start
        } else if (cursor != NULL && cursor->next != NULL) {
            cursor = cursor->next;
        }
        display("After move right: ");
    }

    // Display text with cursor as '|'
    void display(string msg = "") {
        cout << msg;
        CharNode* temp = head;
        while (temp != NULL) {
            if (temp == cursor) cout << temp->ch << "|";
            else cout << temp->ch;
            temp = temp->next;
        }
        if (cursor == NULL) cout << "|"; // cursor at start
        else if (cursor == tail) cout << "|"; // cursor after last
        cout << endl;
    }
};

