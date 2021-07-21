#ifndef MATRIXCALCULATOR_CDATABASE_H
#define MATRIXCALCULATOR_CDATABASE_H

#include "Matrix/CMatrix.h"

#include <string>
#include <map>
#include <memory>
#include <fstream>

class CDatabase {
public:

    /**
     * Adds matrix with given name to the database, if the matrix with given name already exists, it will replace it.
     * @param name unique name of the matrix
     * @param matrix
     */
    void add (const std::string & name, const std::shared_ptr<CMatrix> & matrix);

    /**
     * Return matrix with given name, if the matrix does not exist in the database throws out of range exception.
     * @param name of the matrix
     * @return matrix
     */
    std::shared_ptr<CMatrix> get (const std::string & name) const;

    /**
     * Load matrices from the file.
     * @param path of the file
     * @return true on success, false otherwise (invalid file, unsupported format, invalid name of matrix)
     */
    bool load (const std::string & path);

    /**
     * Save matrix to the file. Filename can be passed as argument or auto-generated.
     * Throws ofstream::failbit and ofstream::badbit.
     * @param name of the matrix
     * @param filename name of the file, either given or auto-generated
     * @return true on success, false otherwise (opening file error)
     */
    bool save (const std::string & name, const std::string & filename = "") const;

    /**
     * Save all matrices in the database to the file. Filename can be passed as argument or auto-generated.
     * @param filename name of the file, either given or auto-generated
     * @return true on success, false otherwise (opening file error)
     */
    bool saveAll (const std::string & filename = "") const;

    /**
     * Removes the matrix with given name.
     * Throws ofstream::failbit and ofstream::badbit.
     * @param name of the matrix
     * @return true on success, false if the matrix does not exist in the database
     */
    bool remove (const std::string & name);

    /**
     * Delete all matrices from the database.
     */
    void clear ();

    /**
     * Return the size of the database.
     * @return size
     */
    size_t size () const;

    /**
     * Display names of all matrices in the database.
     * @return ostream with names of all matrices
     */
    void display () const;

private:

    std::map<std::string, std::shared_ptr<CMatrix>> m_Matrices; // Stored matrices

    /**
     * Creates file in the current directory with auto-generated name (matrices-<current date>.db).
     * @return created file
     */
    static std::ofstream createFile ();

    /**
     * Load elements of dense matrix from the istringstream and create dense matrix.
     * @param src contains elements of matrix
     * @param rows of the matrix
     * @param columns of the matrix
     * @return CDense in shared_ptr
     */
    static std::shared_ptr<CMatrix> loadDense (std::istringstream & src, size_t rows, size_t columns);

    /**
     * Loads elements of sparse matrix from the istringstream and create sparse matrix.
     * @param src contains indexes and elements of matrix
     * @param rows of the matrix
     * @param columns of the matrix
     * @return CSparse in shared_ptr
     */
    static std::shared_ptr<CMatrix> loadSparse (std::istringstream & src, size_t rows, size_t columns);

};

#endif //MATRIXCALCULATOR_CDATABASE_H
