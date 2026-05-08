#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*class MyException : exception
{
    const string message;

public:

    MyException(const string& mess) : message(mess) {}

    string GetMessage() { return message; }

    /*const char* what() const throw() { return message.c_str(); }#1#
};*/

template<typename T>
void Print(const vector<T>& arr, int index, int size)
{
    if (index < 0 || index + size > arr.size()) throw out_of_range("Out of range from \'Print()\'");

    for (int i = index; i < index + size; i++)
    {
        cout << arr[i] << " ";
    }
}

template<typename T>
bool PrintVectors(const vector<vector<T>*>& arrs, int index, int size)
{
    if (index < 0 || index + size > arrs.size()) throw out_of_range("Out of range from \'PrintVectors()\'");

    for (int i = index; i < index + size; i++)
    {
        Print(*arrs[i], 0, (*arrs[i]).size());
        cout << '\n';
    }

    return true;
}

double Sum(double a, double b) noexcept
{
    return a + b;
}

double Sub(double a, double b) noexcept
{
    return a - b;
}

double Mul(double a, double b) noexcept
{
    return a * b;
}

double Div(double a, double b)
{
    if (b == 0) throw invalid_argument("Division by zero");

    return a / b;
}

class MathParser
{
    string expression;
    int pos = 0;

    void DelSpaces()
    {
        while (pos < expression.size() && expression[pos] == ' ')
        {
            pos++;
        }
    }

    char Current()
    {
        DelSpaces();

        if (pos >= expression.size())
        {
            return '\0';
        }

        return expression[pos];
    }

    bool Match(char expected)
    {
        DelSpaces();

        if (Current() == expected)
        {
            pos++;
            return true;
        }

        return false;
    }

    double ParseNumber()
    {
        DelSpaces();

        int start = pos;
        bool hasDot = false;

        while (pos < expression.size() && (isdigit(expression[pos]) || expression[pos] == '.'))
        {
            if (expression[pos] == '.')
            {
                if (hasDot) throw invalid_argument("Invalid number");

                hasDot = true;
            }

            pos++;
        }

        if (start == pos) throw invalid_argument("Number expected");

        return stod(expression.substr(start, pos - start));
    }

    double ParseFactor()
    {
        DelSpaces();

        if (Match('+'))
        {
            return ParseFactor();
        }

        if (Match('-'))
        {
            return Mul(-1, ParseFactor());
        }

        if (Match('('))
        {
            double result = ParseExpression();

            if (!Match(')'))
            {
                throw invalid_argument("Closing bracket expected");
            }

            return result;
        }

        return ParseNumber();
    }

    double ParseTerm()
    {
        double result = ParseFactor();

        while (true)
        {
            if (Match('*'))
            {
                result = Mul(result, ParseFactor());
            }
            else if (Match('/'))
            {
                result = Div(result, ParseFactor());
            }
            else
            {
                break;
            }
        }

        return result;
    }

    double ParseExpression()
    {
        double result = ParseTerm();

        while (true)
        {
            if (Match('+'))
            {
                result = Sum(result, ParseTerm());
            }
            else if (Match('-'))
            {
                result = Sub(result, ParseTerm());
            }
            else
            {
                break;
            }
        }

        return result;
    }

public:

    double Evaluate(const string& expression)
    {
        this->expression = expression;
        pos = 0;

        double result = ParseExpression();

        DelSpaces();

        if (pos != this->expression.size())
        {
            throw invalid_argument("Unexpected symbol");
        }

        return result;
    }
};

int main()
{
    try
    {
        MathParser parser;
        double result = parser.Evaluate("4.5*1+4-1/5*61");
        cout << result << '\n';
    }
    catch (const exception& e)
    {
        cout << e.what() << '\n';
    }


    // std::exception - what()
    // std::logic_error 
    // * std::invalid_argument
    // * std::lenght_error
    // * std::out_of_range
    // runtime_error
    // * std::overflow_error
    // * std::underflow_error
    // * std::range_error
    // std::bad_alloc
    // std::bad_cast

    //vector<vector<int>*> arrs;
    //arrs.push_back(new vector<int>{ 1, 2, 3 });
    //arrs.push_back(new vector<int>{ 4, 5, 6 });
    //arrs.push_back(new vector<int>{ 7, 8, 9 });

    //try
    //{
    //    //PrintVectors(arrs, 2, 2);

    //    throw exception("ASd");
    //}
    //catch (exception& e)
    //{
    //    cout << e.what() << '\n';
    //}
    //catch (...)
    //{
    //    cout << "Something broken" << '\n';
    //}

    //for (vector<int>* arr : arrs)
    //{
    //    delete arr;
    //}

    return 0;
}
