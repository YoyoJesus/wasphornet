#include <iostream>

int fibRecursive(int);
int fibTail(int, int, int);

int main() {
    std::cout << "Enter a number: ";
    int num;
    std::cin >> num;
    
    //print out recursive fibonacci to num
    std::cout << "Recursive Fibonacci Sequence: " << std::endl;
    for (int i = 0; i <= num; ++i){
        std::cout << fibRecursive(i) << ", ";
    }
    std::cout << std::endl;

    //print out recursive tail fibonacci to num
    std::cout << "Tail Recursive Fibonacci Sequence: " << std:: endl;
    for (int i = 0; i <= num; ++i) {
        std::cout << fibTail(i, 0, 1) << ", ";
    }
    std::cout << std::endl;

}

int fibRecursive(int n) {
    if (n <= 1)
        return n;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

int fibTail (int n, int a, int b) {
    if (n == 0)
	return a;
    if (n == 1)
	return b;
    
    return fibTail(n - 1, b, a + b);
}
