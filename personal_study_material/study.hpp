//forward friend declaration
template <typename T>
class Name;

template <typename T>
bool equal(const Name<T>& rhs, const Name<T>& lhs);

template <typename T = int>
class Name {
    public:
        // default constructor
        Name(std::string name="", <T>age = 0): name_(name), age_(age) {};
        // move constructor
        Name(Name<T> && org) noexcept;
        // copy constructor
        Name(const Name<T>& rhs);
        // destructor - really doesn't do anything in this example
        ~Name() {};

        //accessors
        std::string get_name() const {return name_;}
        T get_age() const {return age_;}

        Name<T>& operator=(Name<T> rhs) {std::swap(*this, rhs); return *this;};
        friend bool equal(const Name<T>& rhs, const Name<T>& lhs);

    private:
        std::string name_;
        T age_;
};

template <typename T>
bool equal(const Name<T>& rhs, const Name<T>& lhs) {
    return rhs.name_ == lhs.name_ && rhs.age_ == lhs.age_;
}

template <typename T>
Name<T>::Name(Name<T> && org) noexcept {
    name_ = std::move(org.name_);
    age_ = std::move(org.age_);
}

template <typename T>
Name<T>::Name(const Name<T>& rhs) {
    name_ = rhs.name_;
    age_ = rhs.age_;
}

int main () {
    Name<int> n1("John", 21);
    Name<int> n2("Jane", 22);
    Name<int> n3("John", 21);

    if (equal(n1, n2)) {
        std::cout << "n1 and n2 are equal" << std::endl;
    } else {
        std::cout << "n1 and n2 are not equal" << std::endl;
    }

    if (equal(n1, n3)) {
        std::cout << "n1 and n3 are equal" << std::endl;
    } else {
        std::cout << "n1 and n3 are not equal" << std::endl;
    }

    n1 = n2;
    n2 = std::move(n3);
    return 0;
}