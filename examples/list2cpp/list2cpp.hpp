#ifndef __LIST2CPP__H_
#define __LIST2CPP__H_

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>

namespace lst {
    
    enum class ListType { STRING, CHAR };
    
    class OutputList {
    public:
        OutputList() = default;
        void addItem(std::string item);
        bool addFile(std::string filename);
        std::size_t size() const { return items.size(); }
        bool outputToFile(std::string filename, std::string varname, ListType type);
    private:
        std::vector<std::string> items;
        std::string escapeSequence(const std::string &s);
    };


}


#endif

