/*
 Try out using the Symbol Table with some tests...
 */
// comment out below line for no debug info
#define DEBUG_INFO
#include "table.hpp"

struct SymbolType {
    std::string name, str_val;
    double value;
    SymbolType() : value(0) {}
    SymbolType(std::string n, double v) : name(n), value(v) {}
    SymbolType(std::string n, std::string v) : name(n), str_val(v), value(0) {}
};

std::ostream &operator<<(std::ostream &out, SymbolType &type) {
    out << type.name << ":" << type.value << ":" << type.str_val << "\n";
    return out;
}

int main() {
    sym::SymbolTable<SymbolType> symbols;
    symbols.pushTree("Local[main]");
    symbols.insertTop("x", SymbolType("test", 25));
    
    typename tree::Tree<SymbolType>::node_type *var = symbols.searchStack("x");
    if(var != nullptr) {
        std::cout << "Found symbol: " << var->value << "\n";
    } else {
        std::cout << "Symbol Not Found\n";
    }
    var = symbols.searchStack("Local_Var");
    if(var != nullptr) {
        std::cout << "Found symbol: " << var->value << "\n";
    } else {
        std::cout << "Symbol Not Found\n";
    }
    
    for(int i = 0;  i < 10; ++i) {
        symbols.pushTree();
        symbols.insertTop("test1", SymbolType("test1", i));
        std::cout << "****** PRINT TABLE ******\n";
        symbols.printTable();
        std::cout << "******* END TABLE  *******\n";
        symbols.popTree();
    }
    
    // test move constructor
    sym::SymbolTable<SymbolType> move_sym(std::move(symbols));
    std::cout << "***** PRINT TABLE *****\n";
    move_sym.printTable();
    std::cout << "***** END   TABLE *****\n";
    
    return 0;
}
