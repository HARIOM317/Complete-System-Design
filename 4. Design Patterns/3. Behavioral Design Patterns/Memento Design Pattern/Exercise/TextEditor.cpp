#include <iostream>
#include <stack>

using namespace std;

// Memento
class Memento
{
    string content;

public:
    Memento(string content) : content(content) {}

    string getContent() const
    {
        return content;
    }
};

// Originator (TextEditor)
class textEditor
{
    string content;

public:
    void type(const string &words)
    {
        content += words;
    }

    string getContent() const
    {
        return content;
    }

    // Create a snapshot
    Memento save()
    {
        return Memento(content);
    }

    // Restore a snapshot
    void restore(const Memento &m)
    {
        content = m.getContent();
    }
};

// Caretaker (History Stack)
class History
{
    stack<Memento> history;

public:
    void save(const Memento &m)
    {
        history.push(m);
    }

    Memento undo()
    {
        if (!history.empty())
        {
            history.pop();
            return history.top();
        }
        return Memento(""); // empty fallback
    }
};

// Client
int main()
{
    textEditor editor;
    History history;

    editor.type("Hello ");
    history.save(editor.save()); // snapshot 1

    editor.type("World!");
    history.save(editor.save()); // snapshot 2

    editor.type(" Let's Code...");
    history.save(editor.save()); // snapshot 3

    cout << "Current Content: " << editor.getContent() << endl;

    // Undo once
    editor.restore(history.undo());
    cout << "After Undo 1: " << editor.getContent() << endl;

    // Undo again
    editor.restore(history.undo());
    cout << "After Undo 2: " << editor.getContent() << endl;

    return 0;
}