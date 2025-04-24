// implements command history (multiple undos)
// demonstrates command pattern
// Mikhail Nesterenko
// 11/7/2024

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// receiver
class Document {
public:
   Document(const vector<string> &lines = {}) : lines_(lines) {}

   // actions
   void insert(int line, const string &str) {
      const int index = line - 1;
      if (index <= lines_.size())
         lines_.insert(lines_.begin() + index, str);
      else
         cout << "line out of range" << endl;
   }

   const string remove(int line) {
      const int index = line - 1;
      string deletedLine = "";
      if (index < lines_.size()) {
         deletedLine = *(lines_.begin() + index);
         lines_.erase(lines_.begin() + index);
      }
      else
         cout << "line out of range" << endl;
      return deletedLine;
   }

   void show() const {
      for (int i = 0; i < lines_.size(); ++i)
         cout << i + 1 << ". " << *(lines_.begin() + i) << endl;
   }

   class Memento *checkpoint() const;
   void rollback(const class Memento *mem);

private:
   vector<string> lines_;
};

// abstract command
class Command {
public:
   Command(Document *doc) : doc_(doc) {}
   virtual void execute() = 0;
   virtual void unexecute() = 0;
   virtual string getName() = 0;
   virtual Command* clone() const = 0;
   virtual ~Command() {}

protected:
   Document *doc_;
};

// two concrete commands
class InsertCommand : public Command {
public:
   InsertCommand(Document *doc, int line, const string &str) : Command(doc), line_(line), str_(str) {}
   void execute() override { doc_->insert(line_, str_); }
   void unexecute() override { doc_->remove(line_); }
   string getName() override { return "insert \"" + str_ + "\" at line " + std::to_string(line_); }
   Command* clone() const override { return new InsertCommand(*this); }

private:
   int line_;
   string str_;
};

class EraseCommand : public Command {
public:
   EraseCommand(Document *doc, int line) : Command(doc), line_(line), str_("") {}
   void execute() override { str_ = doc_->remove(line_); }
   void unexecute() override { doc_->insert(line_, str_); }
   string getName() override { return "erase line " + std::to_string(line_); }
   Command* clone() const override { return new EraseCommand(*this); }

private:
   int line_;
   string str_;
};

// invoker
class DocumentWithHistory {
public:
   DocumentWithHistory(const vector<string> &doc = {}) : doc_(doc) {}

   void insert(int line, const string &str) {
      Command *com = new InsertCommand(&doc_, line, str);
      com->execute();
      doneCommands_.push(com);
   }

   void erase(int line) {
      Command *com = new EraseCommand(&doc_, line);
      com->execute();
      doneCommands_.push(com);
   }

   void undo() {
      if (!doneCommands_.empty()) {
         Command *com = doneCommands_.top();
         doneCommands_.pop();
         com->unexecute();
         delete com;
      } else {
         cout << "no commands to undo" << endl;
      }
   }

   void showCommands() const {
      std::stack<Command *> temp = doneCommands_;
      int i = 1;
      while(!temp.empty()) {
         cout << i << ". " + (temp.top()->getName()) << endl;
         temp.pop();
         i++;
      }
   }

   void show() const { doc_.show(); }

   bool rollback();
   void checkpoint();

   void copyCommand(int num) {
      if (doneCommands_.empty()) {
         cout << "no commands to redo" << endl;
         return;
      }

      std::stack<Command *> temp = doneCommands_;
      for (int i = 1; !temp.empty(); ++i) {
         if (i == num) {
            Command *copiedCommand = temp.top()->clone();
            copiedCommand->execute();
            doneCommands_.push(copiedCommand);
            return;
         }
         temp.pop();
      }
      cout << "number out of bounds of command stack" << endl;
   }

   bool isHistoryEmpty() const { return doneCommands_.empty(); }

private:
   Document doc_;
   std::stack<Command *> doneCommands_;
   std::stack<Command *> storedCommands_;
   
   Memento *checkPoint_ = nullptr;
};

// memento
class Memento {
public:
   Memento(const DocumentWithHistory *doc) : doc_(new DocumentWithHistory(*doc)) {}
   const DocumentWithHistory *getState() const { return doc_; }
   ~Memento() { delete doc_; }

private:
   DocumentWithHistory *doc_;
};

bool DocumentWithHistory::rollback() {
   if (checkPoint_) {
      doc_ = checkPoint_->getState()->doc_;

      while (!doneCommands_.empty()) {
         delete doneCommands_.top();
         doneCommands_.pop();
      }

      std::stack<Command *> temp = storedCommands_;
      while (!temp.empty()) {
         doneCommands_.push(temp.top()->clone());
         temp.pop();
      }

      return true;
   } else {
      return false;
   }
}

void DocumentWithHistory::checkpoint() {
   if (checkPoint_) {
      delete checkPoint_;
   }

   while (!storedCommands_.empty()) {
      delete storedCommands_.top();
      storedCommands_.pop();
   }

   std::stack<Command *> temp = doneCommands_;
   while (!temp.empty()) {
      storedCommands_.push(temp.top()->clone());
      temp.pop();
   }

   checkPoint_ = new Memento(this);
}

// client
int main() {
   DocumentWithHistory his({"Lorem Ipsum is simply dummy text of the printing and typesetting",
                            "industry. Lorem Ipsum has been the industry's standard dummy text",
                            "ever since the 1500s, when an unknown printer took a galley of",
                            "type and scrambled it to make a type specimen book. It has",
                            "survived five centuries."});

   char option;
   do {

      his.show();
      cout << endl;

      cout << "Enter option (i)nsert line, (e)rase line,";
      cout << " (u)ndo last command (c)heckpoint roll(b)ack ";
      cout << "(h)history (r)edo command, or e(x)it: ";
      cin >> option;

      int line;
      string str;
      switch (option) {
      case 'i':
         cout << "line number to insert: ";
         cin >> line;
         cout << "line to insert: ";
         cin.get();
         getline(cin, str);
         his.insert(line, str);
         break;

      case 'e':
         cout << "line number to remove: ";
         cin >> line;
         his.erase(line);
         break;

      case 'u':
         his.undo();
         break;

      case 'r':
         cout << "previously run commands:" << endl;
         his.showCommands();
         cout << endl;
        cout << "command number to redo: ";
         cin >> line;
         his.copyCommand(line);
         break;

      case 'h':
         if (his.isHistoryEmpty()) {
            cout << "no command history" << endl;
            break;
         }
         his.showCommands();
         break;

      case 'c':
         his.checkpoint();
         cout << "Checkpoint Made!" << endl;
         break;

      case 'b':
         if (his.rollback()) {
            cout << "Checkpoint Loaded!" << endl;
         } else {
            cout << "No Checkpoint Found!" << endl;
         }
         break;

      case 'x':
         cout << "Exiting..." << endl;
         break;

      default:
         cout << "invalid option" << endl;
         break;
      }
   } while (option == 'i' || option == 'e' || option == 'u'|| option == 'c' || option == 'b' 
              || option == 'r' || option == 'h' || option != 'x');
}
