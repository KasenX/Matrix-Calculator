#include "CDatabase.h"
#include "CParser.h"
#include "Matrix/CDense.h"
#include "Matrix/CSparse.h"
#include "Matrix/CIdentity.h"

#include <algorithm>
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

void CDatabase::add(const string & name, const shared_ptr<CMatrix> & matrix) {
    m_Matrices[name] = matrix;
}

//======================================================================================================================

shared_ptr<CMatrix> CDatabase::get(const string & name) const {
    return m_Matrices.at(name);
}

//======================================================================================================================

bool CDatabase::load(const string & path) {
    ifstream file(path, ios::in);
    if (!file.is_open())
        return false;
    string line;
    while (getline(file, line)) {
        shared_ptr<CMatrix> matrix;
        istringstream iss(line);
        string name;
        int rows, columns;
        char type;
        if (!(iss >> name) || !(iss >> rows) || rows <= 0 || !(iss >> columns) || columns <= 0 || !(iss >> type))
            return false;
        switch (type) {
            case 'D':
                matrix = loadDense(iss, rows, columns);
                break;
            case 'S':
                matrix = loadSparse(iss, rows, columns);
                break;
            case 'I':
                matrix = make_shared<CIdentity>(rows);
                break;
            default:
                file.close();
                return false;
        }
        // Matrix name to lower case
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        // Check the validity of the matrix name and loading success
        if (CParser::checkName(name) && matrix)
            add(name, matrix);
        else {
            file.close();
            return false;
        }
    }
    file.close();
    return true;
}

//======================================================================================================================

bool CDatabase::save(const string & name, const string & filename) const {
    ofstream file;
    file.exceptions(ofstream::failbit | ofstream::badbit);
    // If the name of the file is not given, generate default name of the file
    if (filename.empty())
        file = createFile();
    else
        file.open(filename, ios::out);

    if (!file.is_open())
        return false;

    shared_ptr<CMatrix> matrix = get(name);
    file << name << " " << matrix->rows() << " " << matrix->columns() << " ";
    matrix->toFile(file);
    file << '\n';
    file.close();
    return true;
}

//======================================================================================================================

bool CDatabase::saveAll(const string & filename) const {
    ofstream file;
    file.exceptions(ofstream::failbit | ofstream::badbit);
    // If the name of the file is not given, generate default name of the file
    if (filename.empty())
        file = createFile();
    else
        file.open(filename, ios::out);

    if (!file.is_open())
        return false;

    for (auto & m : m_Matrices) {
        file << m.first << " " << m.second->rows() << " " << m.second->columns() << " ";
        m.second->toFile(file);
        file << '\n';
    }
    file.close();
    return true;
}

//======================================================================================================================

bool CDatabase::remove(const string & name) {
    return m_Matrices.erase(name);
}

//======================================================================================================================

void CDatabase::clear() {
    m_Matrices.clear();
}

//======================================================================================================================

size_t CDatabase::size() const {
    return m_Matrices.size();
}

//======================================================================================================================

void CDatabase::display() const {
    cout << "Matrices in the database (" << size() << "): ";
    for (auto it = m_Matrices.begin(); it != m_Matrices.end(); ++it) {
        string name = it->first;
        transform(name.begin(), name.end(), name.begin(), ::toupper); // Transform the name of the matrix to upper case
        if (it != m_Matrices.begin())
            cout << ", " << name;
        else
            cout << name;
    }
    cout << endl;
}

//======================================================================================================================

std::ofstream CDatabase::createFile() {
    auto t = time(nullptr);
    auto tm = *localtime(&t);

    ostringstream oss;
    oss << put_time(&tm, "matrices-%Y-%m-%d-%H-%M-%S.db");

    ofstream file(oss.str(), ios::out);
    return file;
}

//======================================================================================================================

std::shared_ptr<CMatrix> CDatabase::loadDense(istringstream & src, size_t rows, size_t columns) {
    vector<vector<double>> elements(rows, vector<double>(columns));

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            // If is any element missing or fails to load -> end loading
            if (!(src >> elements[i][j]))
                return nullptr;

    return make_shared<CDense>(rows, columns, elements);
}

//======================================================================================================================

std::shared_ptr<CMatrix> CDatabase::loadSparse(istringstream & src, size_t rows, size_t columns) {
    map<pair<size_t, size_t>, double> elements;
    size_t i, j; // indexes
    double value; // value

    while (src >> i && src >> j && src >> value) {
        if (i >= rows || j >= columns)
            return nullptr;
        elements[make_pair(i, j)] = value;
    }

    return make_shared<CSparse>(rows, columns, elements);
}
