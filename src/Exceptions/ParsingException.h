#ifndef MATRIXCALCULATOR_PARSINGEXCEPTION_H
#define MATRIXCALCULATOR_PARSINGEXCEPTION_H

#include <exception>

class ParsingException : public std::exception {
public:

    explicit ParsingException (std::string text)
    : m_Text(std::move(text))
    {}

    char const * what() const noexcept override {
        return m_Text.c_str();
    }

protected:

    std::string m_Text;
};

#endif //MATRIXCALCULATOR_PARSINGEXCEPTION_H
