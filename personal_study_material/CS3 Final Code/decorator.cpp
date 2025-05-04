// decorator design pattern
// markdown example

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::cin;

// component
class Text {
public:
    Text(const string& text="") : text_(text) {}
    virtual string getText() const { return text_; }
private:
    const string text_;
};

// decorator
class BoldText : public Text {
public:
    BoldText(const Text *wrappedText) : wrappedText_(wrappedText) {}
    string getText() const override { return "**" + wrappedText_->getText() + "**"; }
private:
    const Text *wrappedText_;
};

class ItalicText : public Text {
public:
    ItalicText(const Text *wrappedText) : wrappedText_(wrappedText) {}
    string getText() const override { return "*" + wrappedText_->getText() + "*"; }
private:
    const Text *wrappedText_;
};

class StrikethroughText : public Text {
public:
    StrikethroughText(const Text *wrappedText) : wrappedText_(wrappedText) {}
    string getText() const override { return "~~" + wrappedText_->getText() + "~~"; }
private:
    const Text *wrappedText_;
};

//client code
int main() {
    Text words("Hello, World!");

    BoldText bold(&words);
    ItalicText italic(&bold);

    cout << StrikethroughText(&italic).getText() << endl;
    // Output: ~~***Hello, World!***~~

}