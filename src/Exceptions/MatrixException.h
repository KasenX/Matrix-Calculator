#ifndef MATRIXCALCULATOR_MATRIXEXCEPTION_H
#define MATRIXCALCULATOR_MATRIXEXCEPTION_H

#include <exception>

class MatrixException : public std::exception {
public:

    explicit MatrixException (std::string text)
    : m_Text(std::move(text))
    {}

    char const * what() const noexcept override {
        return m_Text.c_str();
    }

protected:

    std::string m_Text;
};

#endif //MATRIXCALCULATOR_MATRIXEXCEPTION_H
