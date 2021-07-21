#include "CParser.h"
#include "Enums/commands.h"
#include "Exceptions/MatrixException.h"
#include "Exceptions/ParsingException.h"
#include "Matrix/CDense.h"
#include "Matrix/CSparse.h"
#include "Matrix/CIdentity.h"
#include "Operation/OpAdd.h"
#include "Operation/OpGEM.h"
#include "Operation/OpInverse.h"
#include "Operation/OpMergeSide.h"
#include "Operation/OpMergeTop.h"
#include "Operation/OpMultiply.h"
#include "Operation/OpScale.h"
#include "Operation/OpSplit.h"
#include "Operation/OpSubtract.h"
#include "Operation/OpTranspose.h"

#include <iostream>
#include <algorithm>
#include <regex>

using namespace std;

EState CParser::parseInput() {
    vector<string> tokens = tokenizeLine();
    // Only new line
    if (tokens.empty())
        return EState::RUN;
    string command = tokens[0];

    unique_ptr<Op> operation;

    try {
        if (command == Command::HELP && tokens.size() == 1)
            return EState::HELP;
        else if (command == Command::QUIT && tokens.size() == 1)
            return EState::QUIT;
        else if (command == Command::PRINT)
            return printMatrix(tokens);
        else if (command == Command::LOAD)
            return loadMatrix(tokens);
        else if (command == Command::SAVE)
            return saveMatrix(tokens);
        else if (command == Command::SCAN)
            return scanMatrix(tokens);
        else if (command == Command::DELETE || command == Command::DEL)
            return delMatrix(tokens);
        else if (command == Command::DETERMINANT || command == Command::DET)
            return deterMatrix(tokens);
        else if (command == Command::RANK)
            return rankMatrix(tokens);
        else
            operation = readOperation(tokens);
    } catch (out_of_range & e) {
        cout << "Matrix with given name does not exist." << endl;
        return EState::RUN;
    } catch (exception & e) { // Parsing and Matrix exception
        cout << e.what() << endl;
        return EState::RUN;
    }

    // Unknown operation
    if (!operation)
        return EState::UNKNOWN;
    // Perform operation
    try {
        vector<vector<double>> elements = operation->perform();
        std::shared_ptr<CMatrix> matrix = buildMatrix(elements);
        m_Database.add(tokens[0], matrix);
    } catch (MatrixException & e) {
        cout << e.what() << endl;
    }

    return EState::RUN;
}

//======================================================================================================================

vector<string> CParser::tokenizeLine() {

    regex re(R"([\s]+|[=|+|-|*|\[|\]|\(|\)|,])"); // Delimiters: white-space characters, =, +, -, *, [, ], (, ) and ,
    string line;
    getline(cin, line);
    // EOF - end the application by the sending quit command
    if (cin.eof())
        return vector<string>{"quit"};
    // To lower case
    transform(line.begin(), line.end(), line.begin(), ::tolower);
    // Collect both non-matched and matched substrings
    sregex_token_iterator it(line.begin(), line.end(), re, {-1, 0});
    vector<string> tokens(it, {});
    // Remove empty and whitespace strings
    tokens.erase(
            remove_if(tokens.begin(), tokens.end(), [](const string & s) {
                return s.empty() || s[0] == ' ' || s[0] == '\t';}), tokens.end());

    return tokens;
}

//======================================================================================================================

bool CParser::checkName(const string & name) {
    string keywords[] = {Command::TRANSPOSE, Command::TRANS, Command::MERGE, Command::TOP, Command::SIDE, Command::SPLIT,
                         Command::INVERSE, Command::INV, Command::GEM, Command::DETERMINANT, Command::DET, Command::RANK,
                         Command::SCAN, Command::DELETE, Command::DEL, Command::SAVE, Command::LOAD, Command::PRINT,
                         Command::ALL, Command::HELP, Command::QUIT};
    // Name cannot be the calculator key word
    for (auto & keyword : keywords)
        if (name == keyword)
            return false;
    // Cannot begin with non-alpha character or contain delimiters
    return !name.empty() && isalpha(name[0]) && all_of(name.begin(), name.end(), [](char ch)
    { return ch != '=' && ch != '+' && ch != '-' && ch != '*' && ch != '[' && ch != ']' && ch != '(' && ch != ')' && ch != ','; });
}

//======================================================================================================================

EState CParser::scanMatrix(const vector<string> & tokens) {
    if ((tokens.size() != 8 && tokens.size() != 9) || tokens[2] != "[" || tokens[4] != "]" || tokens[5] != "[" || tokens[7] != "]")
        return EState::UNKNOWN;
    if (!checkName(tokens[1]))
        throw ParsingException("Invalid name of the matrix, try: help.");

    // Get rows and columns
    auto reg = regex("^[0-9]*[1-9][0-9]*$"); // Only digits excluding value 0
    if (!regex_match(tokens[3], reg) || !regex_match(tokens[6], reg))
        throw ParsingException("Invalid size of the matrix.");
    size_t rows = (size_t) stoi(tokens[3]);
    size_t columns = (size_t) stoi(tokens[6]);

    // Identity matrix scan
    if (tokens.size() == 9) {
        if (tokens[8] == "1" && rows == columns) {
            m_Database.add(tokens[1], make_shared<CIdentity>(rows));
            return EState::RUN;
        }
        return EState::UNKNOWN;
    }

    // Get elements from input
    vector<vector<double>> elements;
    string line;
    for (size_t i = 0; i < rows; ++i) {
        cout << "Enter the values (separated by whitespaces) of the row number " << i + 1 << ":" << endl;
        // Scan row, on invalid input try again
        while (true) {
            getline(cin, line);
            // EOF - stop matrix scanning
            if (cin.eof()) {
                cin.clear();
                return EState::RUN;
            }
            istringstream iss(line);
            vector<double> row(istream_iterator<double>{iss}, istream_iterator<double>{});
            if (row.size() == columns) {
                elements.push_back(row);
                break;
            }
            cout << "Row number " << i + 1 << " failed to load. Please try again:" << endl;
        }
    }

    shared_ptr<CMatrix> matrix = buildMatrix(elements);
    m_Database.add(tokens[1], matrix);
    return EState::RUN;
}

//======================================================================================================================

unique_ptr<Op> CParser::readOperation(const vector<string> & tokens) const {
    if (tokens.size() < 4 || tokens[1] != "=")
        return nullptr;
    if (!checkName(tokens[0]))
        throw ParsingException("Invalid name of the matrix, try: help.");

    // Transposition, Inversion, GEM
    if (tokens.size() == 4) {
        string command = tokens[2];
        shared_ptr<CMatrix> lhs = m_Database.get(tokens[3]);
        if (command == Command::TRANSPOSE || command == Command::TRANS)
            return make_unique<OpTranspose>(lhs);
        if (command == Command::INVERSE || command == Command::INV)
            return make_unique<OpInverse>(lhs);
        if (command == Command::GEM)
            return make_unique<OpGEM>(lhs);
    }
    // Scale, Add, Subtract, Multiply
    if (tokens.size() == 5 && (tokens[3] == "+" || tokens[3] == "-" || tokens[3] == "*")) {
        string command = tokens[3];
        shared_ptr<CMatrix> rhs = m_Database.get(tokens[4]);
        try {
            double scalar = stod(tokens[2]); // Try convert third token to double
            return make_unique<OpScale>(rhs, scalar); // On success matrix scale operation
        } catch (invalid_argument & e) {
            shared_ptr<CMatrix> lhs = m_Database.get(tokens[2]);
            if (command == "+")
                return make_unique<OpAdd>(lhs, rhs);
            if (command == "-")
                return make_unique<OpSubtract>(lhs, rhs);
            if (command == "*")
                return make_unique<OpMultiply>(lhs, rhs);
        }
    }
    // Merge
    if (tokens.size() == 6) {
        string command = tokens[5];
        shared_ptr<CMatrix> lhs = m_Database.get(tokens[3]);
        shared_ptr<CMatrix> rhs = m_Database.get(tokens[4]);
        if (tokens[2] != Command::MERGE)
            return nullptr;
        if (command == Command::TOP)
            return make_unique<OpMergeTop>(lhs, rhs);
        if (command == Command::SIDE)
            return make_unique<OpMergeSide>(lhs, rhs);
    }
    // Split
    if (tokens.size() == 15) {
        if (tokens[2] != Command::SPLIT || tokens[4] != "[" || tokens[6] != "]" || tokens[7] != "["
        || tokens[9] != "]" || tokens[10] != "(" || tokens[12] != "," || tokens[14] != ")")
            return nullptr;
        shared_ptr<CMatrix> rhs = m_Database.get(tokens[3]);
        int r, c, x, y;
        istringstream ir(tokens[5]), ic(tokens[8]), ix(tokens[11]), iy(tokens[13]);
        if (ir >> r && ic >> c && ix >> x && iy >> y && r > 0 && c > 0 && x > 0 && y > 0)
            return make_unique<OpSplit>(rhs, r, c, x, y);
    }

    return nullptr;
}

//======================================================================================================================

EState CParser::deterMatrix(const vector<string> & tokens) const {
    if (tokens.size() != 2)
        return EState::UNKNOWN;
    string name = tokens[1];
    shared_ptr<CMatrix> matrix = m_Database.get(name);
    cout << "Determinant of " << name << ": " << matrix->determinant() << endl;
    return EState::RUN;
}

//======================================================================================================================

EState CParser::rankMatrix(const vector<string> & tokens) const {
    if (tokens.size() != 2)
        return EState::UNKNOWN;
    string name = tokens[1];
    shared_ptr<CMatrix> matrix = m_Database.get(name);
    transform(name.begin(), name.end(), name.begin(), ::toupper);
    cout << "Rank of " << name << ": " << matrix->rank() << endl;
    return EState::RUN;
}

//======================================================================================================================

EState CParser::delMatrix(const vector<std::string> & tokens) {
    if (tokens.size() != 2)
        return EState::UNKNOWN;

    if (tokens[1] == Command::ALL) {
        cout << "All (" << m_Database.size() << ") matrices were successfully deleted." << endl;
        m_Database.clear();
    }
    else {
        if (m_Database.remove(tokens[1]))
            cout << "Matrix " << tokens[1] << " was successfully deleted." << endl;
        else
            cout << "Matrix with given name does not exist." << endl;
    }
    return EState::RUN;
}

//======================================================================================================================

shared_ptr<CMatrix> CParser::buildMatrix(const vector<vector<double>> & elements) {
    size_t zeros = 0;
    size_t rows = elements.size();
    size_t columns = elements.front().size();
    // Count zero elements
    for (auto & row : elements) {
        for (auto el : row) {
            if (el == 0)
                zeros++;
        }
    }
    // If count of zero elements is more than half of the size of the matrix -> make Sparse matrix, else Dense
    if (zeros > rows * columns / 2) {
        map<pair<size_t, size_t>, double> el;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                if (elements[i][j] != 0)
                    el[make_pair(i, j)] = elements[i][j];
            }
        }
        return make_shared<CSparse>(rows, columns, el);
    }
    return make_shared<CDense>(rows, columns, elements);
}

//======================================================================================================================

EState CParser::printMatrix(const vector<std::string> & tokens) const {
    if (tokens.size() != 2)
        return EState::UNKNOWN;
    if (tokens[1] == Command::ALL)
        m_Database.display();
    else {
        string name = tokens[1];
        shared_ptr<CMatrix> matrix = m_Database.get(name);
        transform(name.begin(), name.end(), name.begin(), ::toupper);
        cout << "Matrix " << name << ":" << endl;
        matrix->print();
    }
    return EState::RUN;
}

//======================================================================================================================

EState CParser::loadMatrix(const vector<std::string> & tokens) {
    if (tokens.size() != 2)
        return EState::UNKNOWN;
    if (!m_Database.load(tokens[1]))
            cout << "Matrices failed to load. Please check the file." << endl;
    return EState::RUN;
}

//======================================================================================================================

EState CParser::saveMatrix(const vector<std::string> & tokens) const {
    if (tokens.size() != 2 && tokens.size() != 3)
        return EState::UNKNOWN;
    string fileName = tokens.size() == 3 ? tokens[2] : "";
    try {
        bool success;
        if (tokens[1] == Command::ALL)
            success = m_Database.saveAll(fileName);
        else
            success = m_Database.save(tokens[1], fileName);
        if (!success)
            cout << "Matrices failed to save. Please check the file." << endl;
    } catch (ofstream::failure & e) {
        cout << "Matrices failed to save. Please check the file." << endl;
    }
    return EState::RUN;
}
