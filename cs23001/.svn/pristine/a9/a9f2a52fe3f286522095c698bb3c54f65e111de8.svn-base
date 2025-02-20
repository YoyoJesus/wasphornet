#include "utilities.hpp"

void Postfix(std::istream& in, std::ostream& out) {
    stack<String> s_stack;
    stack<String> infix;
    String left, right, current_token, function;
    String infix_right, infix_left, infix_expression;
    char token[100];

    while (in >> token) {
        current_token = String(token);

        if (current_token == ";") {
            out << "Infix Expression: " << infix.top() << std::endl;
            out << "Postfix Expression: " << s_stack.top() << std::endl;
            out << "Assembly: " << std::endl;
            Assembly(s_stack.top(), out);
            out << std::endl;

            infix = stack<String>();
            s_stack = stack<String>();
        } else if (current_token == ")") {
            right = s_stack.top(); s_stack.pop();
            function = s_stack.top(); s_stack.pop();
            left = s_stack.top(); s_stack.pop();
            s_stack.push(left + right + function);
            
            infix_right = infix.top(); infix.pop();
            infix.pop(); // Pop the function symbol
            infix_left = infix.top(); infix.pop();
            infix_expression = "( " + infix_left + " " + function + infix_right + " )";
            infix.push(infix_expression);
        } else if (current_token != "(") {
            s_stack.push(current_token + " ");
            infix.push(current_token);
        }
    }
}

void Prefix(std::istream& in, std::ostream& out) {
    stack<String> s_stack;
    stack<String> infix;
    String left, right, current_token, function;
    String infix_right, infix_left, infix_expression;
    char token[100];

    while (in >> token) {
        current_token = String(token);

        if (current_token == ";") {
            out << "Infix Expression: " << infix.top() << std::endl;
            out << "Prefix Expression: " << s_stack.top() << std::endl;
            out << "Assembly: " << std::endl;
            AssemblyPre(s_stack.top(), out);
            out << std::endl;

            infix = stack<String>();
            s_stack = stack<String>();
        } else if (current_token == ")") {
            right = s_stack.top(); s_stack.pop();
            function = s_stack.top(); s_stack.pop();
            left = s_stack.top(); s_stack.pop();
            s_stack.push(function + left + right);
            
            infix_right = infix.top(); infix.pop();
            infix.pop(); // Pop the function symbol
            infix_left = infix.top(); infix.pop();
            infix_expression = "( " + infix_left + " " + function + infix_right + " )";
            infix.push(infix_expression);
        } else if (current_token != "(") {
            s_stack.push(current_token + " ");
            infix.push(current_token);
        }
    }
}

void Assembly(const String& input, std::ostream& out) {
    stack<String> s;
    String lhs, rhs, op, tempv, ctoken;
    int tempN = 1;

    // Split input String into tokens based on space or semicolon
    std::vector<String> tokens = input.split(' ');

    for (const auto& token : tokens) {
        ctoken = token;

        if (ctoken == ";") {
            if (!s.empty()) {
                // If there are items left in the stack, there's an expression to evaluate
                rhs = s.top(); s.pop(); // Pop the top of stack as RHS
                lhs = s.top(); s.pop(); // Pop the next top of stack as LHS

                op = get_operator(ctoken);
                tempv = "TMP" + to_string(tempN++);

                out << "   LD    " << lhs << std::endl;
                out << op << rhs << std::endl;
                out << "   ST    " << tempv << std::endl;

                s.push(tempv); // Push the temporary variable back to stack
            }

            // Add a comment for the current line
            out << "; " << ctoken << std::endl;
        } else if (ctoken != "+" && ctoken != "-" && ctoken != "*" && ctoken != "/") {
            s.push(ctoken);
        } else {
            rhs = s.top(); s.pop(); // Pop the top of stack as RHS
            lhs = s.top(); s.pop(); // Pop the next top of stack as LHS

            op = get_operator(ctoken);
            tempv = "TMP" + to_string(tempN++);

            out << "   LD    " << lhs << std::endl;
            out << op << rhs << std::endl;
            out << "   ST    " << tempv << std::endl;

            s.push(tempv); // Push the temporary variable back to stack
        }
    }

    // If there are items left in the stack after processing, it's the final result
    if (!s.empty()) {
        out << std::endl;
    }
}

void AssemblyPre(const String& input, std::ostream& out) {
    stack<String> s;
    String lhs, rhs, op, tempv, ctoken;
    int tempN = 1;

    // Split input String into tokens based on space
    std::vector<String> tokens = input.split(' ');

    // Iterate through tokens in reverse order for prefix notation
    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        ctoken = *it;

        if (ctoken != "+" && ctoken != "-" && ctoken != "*" && ctoken != "/") {
            s.push(ctoken);
        } else {
            lhs = s.top(); s.pop(); // Pop the top of stack as LHS
            rhs = s.top(); s.pop(); // Pop the next top of stack as RHS

            op = get_operator(ctoken);
            tempv = "TMP" + to_string(tempN++);

            out << "   LD    " << lhs << std::endl;
            out << op << rhs << std::endl;
            out << "   ST    " << tempv << std::endl;

            s.push(tempv); // Push the temporary variable back to stack
        }
    }

    // If there are items left in the stack after processing, it's the final result
    if (!s.empty()) {
        out << std::endl;
    }
}

String get_operator(const String& op)
{
    switch (op[0]) {
        case '+':
            return "   AD\t ";
            break;
        case '-':
            return "   SB\t ";
            break;
        case '*':
            return "   MU\t ";
            break;
        case '/':
            return "   DV\t ";
            break;
        default:
            return "    UNDEF\t";
    }
}

String to_string(int x) {
    if (!x) {
        return "0";
    }

    String result;

    do {
        result += (x % 10 + 48);
        x /= 10;
    } while (x > 0);

    return result;
}


String get_token(std::istream& in) {
    String result;
    char token = '\0';

    // Skip leading whitespace
    while (in.get(token) && std::isspace(token)) {
        // Skip
    }

    // Read until space or semicolon
    while (in && !std::isspace(token) && token != ';') {
        result += token;
        in.get(token);
    }

    return result;
}