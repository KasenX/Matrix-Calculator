CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++14

TARGET = matrixcalculator
BUILD_DIR = build

HEADERS = $(wildcard src/*.h src/*/*.h)
SOURCES = $(wildcard src/*.cpp src/*/*.cpp)
# String substitution for every C++ file
OBJECTS = $(SOURCES:src/%.cpp=$(BUILD_DIR)/%.o)

.PHONY: all
all: compile doc

.PHONY: run
run: compile
	./$(TARGET)

.PHONY: compile
compile: $(TARGET)

$(TARGET): $(BUILD_DIR)/main
	cp $< $@

$(BUILD_DIR)/main: $(OBJECTS)
	mkdir -p $(@D)
	$(CXX) $^ -o $@

$(BUILD_DIR)/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -c -o $@

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf $(TARGET) $(BUILD_DIR)/ doc/ 2>/dev/null

# Dependencies
# Generated by "g++ -MM"
CApplication.o: src/CApplication.cpp src/CApplication.h src/CParser.h \
 src/CDatabase.h src/Matrix/CMatrix.h src/Operation/Op.h \
 src/Operation/../Matrix/CMatrix.h src/Enums/EState.h
CDatabase.o: src/CDatabase.cpp src/CDatabase.h src/Matrix/CMatrix.h \
 src/CParser.h src/Operation/Op.h src/Operation/../Matrix/CMatrix.h \
 src/Enums/EState.h src/Matrix/CDense.h src/Matrix/CMatrix.h \
 src/Matrix/CSparse.h src/Matrix/CIdentity.h
CParser.o: src/CParser.cpp src/CParser.h src/CDatabase.h \
 src/Matrix/CMatrix.h src/Operation/Op.h \
 src/Operation/../Matrix/CMatrix.h src/Enums/EState.h \
 src/Enums/commands.h src/Exceptions/MatrixException.h \
 src/Exceptions/ParsingException.h src/Matrix/CDense.h \
 src/Matrix/CMatrix.h src/Matrix/CSparse.h src/Matrix/CIdentity.h \
 src/Operation/OpAdd.h src/Operation/OpBinary.h src/Operation/Op.h \
 src/Operation/OpGEM.h src/Operation/OpInverse.h \
 src/Operation/OpMergeSide.h src/Operation/OpMergeTop.h \
 src/Operation/OpMultiply.h src/Operation/OpScale.h \
 src/Operation/OpSplit.h src/Operation/OpSubtract.h \
 src/Operation/OpTranspose.h
main.o: src/main.cpp src/CApplication.h src/CParser.h src/CDatabase.h \
 src/Matrix/CMatrix.h src/Operation/Op.h \
 src/Operation/../Matrix/CMatrix.h src/Enums/EState.h
CDense.o: src/Matrix/CDense.cpp src/Matrix/CDense.h src/Matrix/CMatrix.h
CIdentity.o: src/Matrix/CIdentity.cpp src/Matrix/CIdentity.h \
 src/Matrix/CMatrix.h
CMatrix.o: src/Matrix/CMatrix.cpp src/Matrix/CMatrix.h \
 src/Matrix/../Exceptions/MatrixException.h \
 src/Matrix/../Operation/OpGEM.h src/Matrix/../Operation/Op.h \
 src/Matrix/../Operation/../Matrix/CMatrix.h
CSparse.o: src/Matrix/CSparse.cpp src/Matrix/CSparse.h \
 src/Matrix/CMatrix.h
Op.o: src/Operation/Op.cpp src/Operation/Op.h \
 src/Operation/../Matrix/CMatrix.h
OpAdd.o: src/Operation/OpAdd.cpp src/Operation/OpAdd.h \
 src/Operation/OpBinary.h src/Operation/Op.h \
 src/Operation/../Matrix/CMatrix.h \
 src/Operation/../Exceptions/MatrixException.h
OpBinary.o: src/Operation/OpBinary.cpp src/Operation/OpBinary.h \
 src/Operation/Op.h src/Operation/../Matrix/CMatrix.h
OpGEM.o: src/Operation/OpGEM.cpp src/Operation/OpGEM.h src/Operation/Op.h \
 src/Operation/../Matrix/CMatrix.h
OpInverse.o: src/Operation/OpInverse.cpp src/Operation/OpInverse.h \
 src/Operation/Op.h src/Operation/../Matrix/CMatrix.h \
 src/Operation/OpMergeSide.h src/Operation/OpBinary.h \
 src/Operation/OpSplit.h src/Operation/../Matrix/CIdentity.h \
 src/Operation/../Matrix/CMatrix.h \
 src/Operation/../Exceptions/MatrixException.h
OpMergeSide.o: src/Operation/OpMergeSide.cpp src/Operation/OpMergeSide.h \
 src/Operation/OpBinary.h src/Operation/Op.h \
 src/Operation/../Matrix/CMatrix.h \
 src/Operation/../Exceptions/MatrixException.h
OpMergeTop.o: src/Operation/OpMergeTop.cpp src/Operation/OpMergeTop.h \
 src/Operation/OpBinary.h src/Operation/Op.h \
 src/Operation/../Matrix/CMatrix.h \
 src/Operation/../Exceptions/MatrixException.h
OpMultiply.o: src/Operation/OpMultiply.cpp src/Operation/OpMultiply.h \
 src/Operation/OpBinary.h src/Operation/Op.h \
 src/Operation/../Matrix/CMatrix.h \
 src/Operation/../Exceptions/MatrixException.h
OpScale.o: src/Operation/OpScale.cpp src/Operation/OpScale.h \
 src/Operation/Op.h src/Operation/../Matrix/CMatrix.h
OpSplit.o: src/Operation/OpSplit.cpp src/Operation/OpSplit.h \
 src/Operation/Op.h src/Operation/../Matrix/CMatrix.h \
 src/Operation/../Exceptions/MatrixException.h
OpSubtract.o: src/Operation/OpSubtract.cpp src/Operation/OpSubtract.h \
 src/Operation/OpBinary.h src/Operation/Op.h \
 src/Operation/../Matrix/CMatrix.h \
 src/Operation/../Exceptions/MatrixException.h
OpTranspose.o: src/Operation/OpTranspose.cpp src/Operation/OpTranspose.h \
 src/Operation/Op.h src/Operation/../Matrix/CMatrix.h
