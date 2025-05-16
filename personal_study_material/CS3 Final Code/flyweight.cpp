// flyweight pattern

#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::cin;
using std::map;
using std::string;

enum class rank {Soldier, Officer, General, Colonel};

// abstract flyweight class
class Rank {
public:
    virtual string getRank() const = 0;
};

// concrete flyweight classes
class Soldier : public Rank {
public:
    string getRank() const override { return "Soldier"; }
};

class Officer : public Rank {
public:
    string getRank() const override { return "Officer"; }
};

class General : public Rank {
public:
    string getRank() const override { return "General"; }
};

class Colonel : public Rank {
public:
    string getRank() const override { return "Colonel"; }
};

// flyweight factory
class Academy{
public:
    static Rank* getRank(rank r) {
        if (ranks_.find(r) == ranks_.end()) {
            switch (r) {
                case rank::Soldier:
                    ranks_[r] = new Soldier();
                    break;
                case rank::Officer:
                    ranks_[r] = new Officer();
                    break;
                case rank::General:
                    ranks_[r] = new General();
                    break;
                case rank::Colonel:
                    ranks_[r] = new Colonel();
                    break;
            }
        }
        return ranks_[r];
    }
private:
    static map<rank, Rank*> ranks_;
};

map<rank, Rank*> Academy::ranks_;

// client code
class Military {
public:
    Military(string name, rank r) : name_(name), rank_(Academy::getRank(r)) {}
    void show() {cout << "Name: " << name_ 
        << ", Rank: " << rank_->getRank() << endl;}
    void setRank(rank r) {rank_ = Academy::getRank(r);}
private:
    string name_;
    Rank* rank_;
};

int main() {
    Military m1("John", rank::Soldier);
    Military m2("Jane", rank::Officer);
    Military m3("Bob", rank::General);
    Military m4("Alice", rank::Colonel);

    m1.show();
    m2.show();
    m3.show();
    m4.show();

    // Change rank
    cout << "Changing rank of John to Colonel" << endl;
    m1.setRank(rank::Colonel);
    m1.show();

}