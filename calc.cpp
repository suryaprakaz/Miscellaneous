#include "Calc.h"

std::string op1, op2;

/*
Initializes and Resets the operands for every iteration
*/
void Initialize()
{
    op1 = "\0";
    op2 = "\0";
}

/*
Splits the input expression into operands and operator
*/
int Parse_string(std::string str)
{
    int position = 0;
    int numberOfDigitsOperand1;
    int numberOfDigitsOperand2;
    int operation = 0;
    while (position < strlen(str.c_str()))
    {
        const char * x = new char(str[position]);
        if (strcmp(x, new char('+')) == 0)
        {
            if (operation != 0)
                return -1;
            operation = 1;
        }
        else if (strcmp(x, new char('-')) == 0)
        {
            if (operation != 0)
                return -1;
            operation = 2;
        }
        else if (strcmp(x, new char('*')) == 0)
        {
            if (operation != 0)
                return -1;
            operation = 3;
        }
        else if (strcmp(x, new char('/')) == 0)
        {
            if (operation != 0)
                return -1;
            operation = 4;
        }
        if (operation == 0)
        {
            op1 += str[position];
        }
        else
        {
            op2 += str[position];
        }
        position++;
    }
    if (operation == 0)
        return -1;
    numberOfDigitsOperand1 = strlen(op1.c_str());
    numberOfDigitsOperand2 = strlen(op2.c_str()) - 1;
    for (int i = 0; i < numberOfDigitsOperand1; i++)
    {
        const char * x = new char(op1[i]);
        if (!isdigit(op1[i]))
            return -1;
    }
    op2.erase(0, 1); // Remove the sign from the operand
    for (int i = 0; i < numberOfDigitsOperand2; i++)
    {
        const char * x = new char(op2[i]);
        if (!isdigit(op2[i]))
            return -1;
    }
    return operation;
}

void calculate(std::string str)
{
    int operation = Parse_string(str);
    if (operation == -1)
    {
        std::cout << "Invalid expression" << std::endl;
    }
    else
    {
        switch (operation)
        {
        case 1:
            std::cout << addition(op1, op2) << std::endl;
            break;
        case 2:
            std::cout << subtraction(op1, op2) << std::endl;
            break;
        case 3:
            std::cout << multiplication(op1, op2) << std::endl;
            break;
        case 4:
            std::cout << division(op1, op2) << std::endl;
            break;
        default:
            std::cout << "Invalid" << std::endl;
            break;
        }
    }
}

std::string addition(std::string num1, std::string num2)
{
    int carry = 0;
    int k = 0;
    std::string ret;
    int s1 = num1.size(), s2 = num2.size();
    int i = s1 - 1;
    int j = s2 - 1;

    /*
    Add corresponding digits while there exists more digits in both operands
    */
    for (; i >= 0 && j >= 0; i--, j--, k++)
    {
        ret.insert(k, 1, '0' + ((num1[i] - '0') + (num2[j] - '0') + carry) % 10);
        carry = ((num1[i] - '0') + (num2[j] - '0') + carry) / 10;
    }

    /*
    Add remaining digits in either operands with carry
    */
    if (s1 > s2)
    {
        while (i >= 0)
        {
            ret.insert(k++, 1, '0' + ((num1[i] - '0') + carry) % 10);
            carry = ((num1[i--] - '0') + carry) / 10;
        }
        ret.insert(k++, 1, '0' + carry);
    }
    else if (s1 < s2)
    {
        while (j >= 0)
        {
            ret.insert(k++, 1, '0' + ((num2[j] - '0') + carry) % 10);
            carry = ((num2[j--] - '0') + carry) / 10;
        }
        ret.insert(k++, 1, '0' + carry);
    }
    else
    {
        if (carry > 0)
        {
            ret.insert(k, 1, '0' + carry);
            k++;
        }
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}

std::string subtraction(std::string num1, std::string num2)
{
    std::string ret;
    int operand1[50] = {};
    int operand2[50] = {};
    int result[50] = {};
    int s1 = num1.size(), s2 = num2.size();
    for (int i = 0; i < s1; i++)
    {
        const char * x = new char(num1[i]);
        operand1[i] = atoi(x);
    }
    for (int i = 0; i < s2; i++)
    {
        const char * x = new char(num2[i]);
        operand2[i] = atoi(x);
    }
    int carry = 0;
    int comp[50];

    /*
    Add 0s to the beginning of the smaller operand to
    out the sizes of the operands
    */
    if (s1 > s2)
    {
        for (int i = s2 - 1; i >= 0; i--)
            operand2[i + s1 - s2] = operand2[i];
        for (int i = 0; i < s1 - s2; i++)
            operand2[i] = 0;
        s2 = s1;
    }
    else if (s2 > s1)
    {
        for (int i = s1 - 1; i >= 0; i--)
            operand1[i + s2 - s1] = operand1[i];
        for (int i = 0; i < s2 - s1; i++)
            operand1[i] = 0;
        s1 = s2;
    }
    int digits = s2;

    /*
    Subtract using 9s complement
    */
    for (int i = digits - 1; i >= 0; i--)
    {
        comp[i] = 9 - operand2[i];
        int num = comp[i] + operand1[i] + carry;
        if (num >= 10)
        {
            result[i] = num % 10;
            carry = num / 10;
        }
        else
        {
            carry = 0;
            result[i] = num;
        }
    }
    if (carry == 0)
    {
        for (int i = 0; i < digits; i++)
        {
            result[i] = 9 - result[i];
        }
        ret.insert(0, 1, '-');
        for (int i = 1; i <= digits; i++)
        {
            ret.insert(i, 1, result[i - 1] + '0');
        }
    }
    else
    {
        int carryIndex = digits - 1;
        int carryAround;
        for (int i = carryIndex; i >= 0; i--)
        {
            carryAround = result[i] + carry;
            if (carryAround >= 10)
            {
                result[i] = carryAround % 10;
                carry = carryAround / 10;
            }
            else
            {
                result[i] = carryAround;
                break;
            }
        }
        for (int i = 0; i < digits; i++)
        {
            ret.insert(i, 1, result[i] + '0');
        }
    }
    return ret;
}

std::string multiplication(std::string num1, std::string num2)
{
    std::string ret;
    int s1 = num1.size(), s2 = num2.size(), size = s1 + s2;
    std::vector<int> digit(size, 0), carry(size, 0);

    /*
    Iteratively multiply and add carry, accumulate the values
    */
    for (int i = 0; i < s1; ++i)
    {
        for (int j = 0; j < s2; ++j)
        {
            int mul = num1[s1 - 1 - i] - '0';
            int muled = num2[s2 - 1 - j] - '0';
            int tmp = mul*muled;
            digit[size - 1 - i - j] += tmp % 10;
            carry[size - 1 - i - j - 1] += tmp / 10;
        }
    }
    int carrFlag = 0;
    for (int i = size - 1; i >= 0; --i)
    {
        int sum = digit[i] + carry[i] + carrFlag;
        ret.insert(ret.begin(), 1, '0' + sum % 10);
        carrFlag = sum / 10;
    }
    int pos(0);
    while (ret[pos] == '0')
        pos++;
    if (pos >= size)
        return "0";
    return ret.substr(pos);
}

std::string division(std::string num1, std::string num2)
{
    std::string ret;
    std::string sub;
    int quotient[50] = {};
    int qSize = 0;
    int fetchIndex = 0;
    int s1 = num1.size(), s2 = num2.size();
    int subIndex = 0;
    if (s1 < s2)
    {
        ret.insert(ret.begin(), 1, 0 + '0');
    }
    else
    {
        /*
        Divide the fist n digits of num1 with num2,
        n is the length of num2
        */
        std::string temp = num1.substr(fetchIndex, s2);
        fetchIndex += s2 - 1;
        while (fetchIndex < s1)
        {
            fetchIndex++;
            int exitFlag = 0;
            int breakFlag = 0;
            /*
            Repeated subtraction to find the quotient
            */
            while (exitFlag == 0)
            {
                temp = subtraction(temp, num2);
                if (strcmp(temp.substr(0, 1).c_str(), "-") != 0) //positive number
                {
                    quotient[qSize]++;
                }
                else
                {
                    temp.erase(0, temp.find_first_not_of('-'));
                    temp.erase(0, temp.find_first_not_of('0'));
                    if (strcmp(temp.c_str(), "") == 0)
                    {
                        quotient[qSize]++;
                        temp.append(num1.substr(fetchIndex, 1));
                        if (strcmp(subtraction(temp, num2).substr(0, 1).c_str(), "-") == 0)
                        {
                            qSize++;
                            breakFlag = 1;
                            break;
                        }
                    }
                    else
                    {
                        temp.erase(0, temp.find_first_not_of('-'));
                        temp.erase(0, temp.find_first_not_of('0'));
                        temp = subtraction(num2, temp);
                        temp.erase(0, temp.find_first_not_of('0'));
                        temp.append(num1.substr(fetchIndex, 1));
                    }
                    exitFlag = 1;
                }
            }
            if (breakFlag == 1)
                continue;
            qSize++;
        }
    }
    for (int i = 0; i < qSize; i++)
        ret.insert(i, 1, quotient[i] + '0');
    return ret;
}
