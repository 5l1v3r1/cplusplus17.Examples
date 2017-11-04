/*
 	Policy and Traits classes
	 based on "C++ Templates the Complete Guide: Second Edition"
*/

#include<iostream>
#include<vector>
#include<string>

template<typename T>
class ValueTraits;

template<>
class ValueTraits<char> {
public:
    using Type = int;
    static constexpr char zero() { return 0; }
    
};

template<>
class ValueTraits<int> {
public:
    using Type = long;
    static constexpr long zero() { return 0; }
};

template<>
class ValueTraits<long> {
public:
    using Type = long;
    static constexpr long zero() { return 0; }
};

template<>
class ValueTraits<float> {
public:
    using Type = float;
    static constexpr float zero() { return 0; }
};

template<>
class ValueTraits<std::string> {
public:
    using Type = std::string;
    static std::string zero() { return ""; }
};

template<typename T>
class ValueAddPolicy;

template<>
class ValueAddPolicy<char> {
public:
    static int operation(int start, char val) {
        return (start+val);
    }
};

template<>
class ValueAddPolicy<int> {
public:
    static long operation(int start, int val) {
        return (start+val);
    }
};

template<>
class ValueAddPolicy<long> {
public:
    static long operation(long start, long val) {
        return (start+val);
    }
};

template<>
class ValueAddPolicy<float> {
public:
    static float operation(float start, float val) {
        return (start+val);
    }
};

template<>
class ValueAddPolicy<std::string> {
public:
    static std::string operation(std::string start, std::string val) {
        std::string value = start;
        value += val;
        return value;
    }
};

// Output via Stream
template<typename T>
class ValueStreamPolicy {
public:
    static std::string operation(std::string start, std::string val) {
        std::cout << "Stream output: " << val << "\n";
        return start;
    }
};

template<typename T, typename Iter, typename Policy = ValueAddPolicy<T>>
auto procValues(Iter start, Iter stop) {
    using Type = typename ValueTraits<T>::Type;
    Type type = ValueTraits<T>::zero();
    while(start != stop) {
        type = Policy::operation(type, *start);
        start++;
    }
    return type;
}

int main(){
    std::vector<int> values {5,5,5,5};
    long result = procValues<int>(values.begin(), values.end());
    std::cout << "Value: " << result << "\n";
    std::vector<std::string> string_values {"Hello, ", "World!", " with ", " Traits!"};
    std::string string_result = procValues<std::string>(string_values.begin(), string_values.end());
    std::cout << "String concat: " << string_result << "\n";
    std::vector<char> ch_values { 'a', 'z', 'q' };
    int total = procValues<char>(ch_values.begin(), ch_values.end());
    std::cout << "Ch./ total: " << total << "\n";
    // stream output using different Policy
    using vIt = typename std::vector<std::string>::iterator;
    procValues<std::string, vIt, ValueStreamPolicy<std::string>>(string_values.begin(), string_values.end());
    
    
    return 0;
}



