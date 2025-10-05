#include "texteditor.h"
#include <iostream>
#include <list>
#include <map>
#include <string>

// Internal implementation class using linked list for text and cursor
class TextEditorImpl {
public:
    std::list<char> text;
    std::list<char>::iterator cursor;

    TextEditorImpl() {
        cursor = text.begin();
    }

    void insertChar(char c) {
        text.insert(cursor, c);
    }

    void deleteChar() {
        if (cursor != text.begin()) {
            auto temp = cursor;
            --temp;
            text.erase(temp);
        }
    }

    void moveLeft() {
        if (cursor != text.begin()) --cursor;
    }

    void moveRight() {
        if (cursor != text.end()) ++cursor;
    }

    std::string getTextWithCursor() const {
        std::string result;
        for (auto it = text.begin(); it != text.end(); ++it) {
            if (it == cursor) result += '|';
            result += *it;
        }
        if (cursor == text.end()) result += '|';
        return result;
    }
};

// Global mapping of TextEditor objects to their internal data
static std::map<const TextEditor*, TextEditorImpl> implMap;

// Define all virtual methods of TextEditor to call the internal implementation
void TextEditor::insertChar(char c) { implMap[this].insertChar(c); }
void TextEditor::deleteChar() { implMap[this].deleteChar(); }
void TextEditor::moveLeft() { implMap[this].moveLeft(); }
void TextEditor::moveRight() { implMap[this].moveRight(); }
std::string TextEditor::getTextWithCursor() const { return implMap.at(this).getTextWithCursor(); }


int main() {
    TextEditor ed;

    ed.insertChar('a');
    std::cout << "After insert 'a': " << ed.getTextWithCursor() << "\n";

    ed.insertChar('b');
    std::cout << "After insert 'b': " << ed.getTextWithCursor() << "\n";

    ed.moveLeft();
    std::cout << "After move left: " << ed.getTextWithCursor() << "\n";

    ed.insertChar('c');
    std::cout << "After insert 'c': " << ed.getTextWithCursor() << "\n";

    ed.deleteChar();
    std::cout << "After delete: " << ed.getTextWithCursor() << "\n";

    ed.moveLeft();
    ed.moveLeft();
    std::cout << "After move left twice: " << ed.getTextWithCursor() << "\n";

    ed.moveRight();
    ed.moveRight();
    std::cout << "After move right twice: " << ed.getTextWithCursor() << "\n";

    return 0;
}
