#include <iostream>
#include <string>
#include <vector>

// Command Interface
class ICommand {
    public:
        virtual void execute() = 0;
        virtual void undo() = 0;
        virtual ~ICommand() = default;
};

// Receiver
class TextEditor {
    std::string text;

    public:
        void appendText(const std::string& newText) {
            text += newText;
            std::cout << "Text after append: " << text << std::endl;
        }

        void removeLast(size_t length) {
            if (length > text.size()) {
                text.clear();
            } 
            else {
                text.erase(text.size() - length, length);
            }
            std::cout << "Text after removal: " << text << std::endl;
        }

        const std::string& getText() const {
            return text;
        }
};

// Concrete Command: Append
class AppendCommand : public ICommand {
    TextEditor* editor;
    std::string textToAppend;

    public:
        AppendCommand(TextEditor* editor, const std::string& text) : editor(editor), textToAppend(text) {}

        void execute() override {
            editor->appendText(textToAppend);
        }

        void undo() override {
            editor->removeLast(textToAppend.size());
        }
};

// Invoker
class CommandManager {
    std::vector<ICommand*> commandHistory;

    public:
        void executeCommand(ICommand* command) {
            command->execute();
            commandHistory.push_back(command);
        }

        void undoLastCommand() {
            if (!commandHistory.empty()) {
                ICommand* command = commandHistory.back();
                command->undo();
                commandHistory.pop_back();
            } 
            else {
                std::cout << "No commands to undo.\n";
            }
        }
};

int main() {
    TextEditor editor;
    CommandManager manager;

    AppendCommand command1(&editor, "Hello, ");
    AppendCommand command2(&editor, "World!");

    std::cout << "Executing commands:\n";
    manager.executeCommand(&command1);
    manager.executeCommand(&command2);

    std::cout << "\nUndoing last command:\n";
    manager.undoLastCommand();

    std::cout << "\nUndoing another command:\n";
    manager.undoLastCommand();

    return 0;
}
