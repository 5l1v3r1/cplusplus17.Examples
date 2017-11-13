#include "list2cpp.hpp"

namespace lst {
    
    OutputList::OutputList(const OutputList &l) : items(l.items) {
        
    }
    OutputList::OutputList(OutputList &&l) : items(std::move(l.items)) {
        
    }
    OutputList& OutputList::operator=(OutputList &l) {
        items = l.items;
        return *this;
    }
    
    OutputList& OutputList::operator=(OutputList &&l) {
        items = std::move(l.items);
        return *this;
    }
    
    std::string OutputList::escapeSequence(const std::string &s) {
        std::string temp;
        for(std::size_t i = 0; i < s.length(); ++i) {
            if(s[i] == '\"' || s[i] == '\\') {
                temp += "\\";
                temp += s[i];
            } else {
                temp += s[i];
            }
        }
        return temp;
    }
    
    bool OutputList::validName(const std::string &s) {
        if(s.length() == 0) return false;
        if(isdigit(s[0])) {
            return false;
        }
        for(unsigned int i = 0; i < s.length(); ++i) {
            if (!isdigit(s[i]) && !isalpha(s[i]) && s[i] != '_') {
                return false;
            }
        }
        return true;
    }
    
    
    void OutputList::addItem(std::string type) {
        items.push_back(type);
    }
    
    bool OutputList::addFile(std::string name) {
        std::fstream file;
        file.open(name, std::ios::in);
        if(!file.is_open()) {
            std::cerr << "Error: could not open file...\n";
            return false;
        }
        addStream(file);
        file.close();
        return true;
    }
    
    bool OutputList::addStream(std::istream &file) {
        while(!file.eof()) {
            std::string value;
            std::getline(file, value);
            if(file && value.length()>0) items.push_back(escapeSequence(value));
        }
        return true;
    }
    
    bool OutputList::outputToFile(std::ostream &file, std::string varname, ListType type) {
        file << "#ifndef __LIST2CPP_" << varname << "\n";
        file << "#define __LIST2CPP_" << varname << "\n";
        switch(type) {
            case ListType::STRING: {
                file << "#include<string>\n\n\n";
                file << "inline unsigned long " << varname << "_size = " << size() << ";\n";
                file << "\n\ninline std::string " << varname << "_arr"  << "[] = {\n";
                for(std::size_t i = 0; i < size(); ++i) {
                    if(i > size()-2) {
                        file << "\"" << items[i] << "\"\n};\n";
                    } else {
                        file << "\"" << items[i] << "\",\n";
                    }
                }
            }
                break;
            case ListType::CHAR: {
                file << "inline unsigned long " << varname << "_size = " << size() << ";\n";
                file << "\n\n\ninline const char *" << varname << "_str[] = {";
                for(std::size_t i = 0; i < size(); ++i) {
                    if(i > size()-2) {
                        file << "\"" << items[i] << "\"\n};\n";
                    } else {
                        file << "\"" << items[i] << "\",\n";
                    }
                }
            }
                break;
        }
        file << "\n\n#endif\n\n";
        return true;
    }
    
    bool OutputList::outputToFile(std::string filename,std::string varname,ListType type) {
        std::fstream file;
        file.open(filename, std::ios::out);
        if(!file.is_open()) {
            std::cerr << "Error: could not open output file...\n";
            return false;
        }
        outputToFile(file, varname, type);
        file.close();
        return true;
    }

}
