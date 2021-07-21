#ifndef MATRIXCALCULATOR_COMMANDS_H
#define MATRIXCALCULATOR_COMMANDS_H

struct Command {
    constexpr static const char * const TRANSPOSE = "transpose";
    constexpr static const char * const TRANS = "trans";
    constexpr static const char * const MERGE = "merge";
    constexpr static const char * const TOP = "top";
    constexpr static const char * const SIDE = "side";
    constexpr static const char * const SPLIT = "split";
    constexpr static const char * const INVERSE = "inverse";
    constexpr static const char * const INV = "inv";
    constexpr static const char * const GEM = "gem";
    constexpr static const char * const DETERMINANT = "determinant";
    constexpr static const char * const DET = "det";
    constexpr static const char * const RANK = "rank";
    constexpr static const char * const SCAN = "scan";
    constexpr static const char * const DELETE = "delete";
    constexpr static const char * const DEL = "del";
    constexpr static const char * const SAVE = "save";
    constexpr static const char * const LOAD = "load";
    constexpr static const char * const PRINT = "print";
    constexpr static const char * const ALL = "all";
    constexpr static const char * const HELP = "help";
    constexpr static const char * const QUIT = "quit";
};

#endif //MATRIXCALCULATOR_COMMANDS_H
