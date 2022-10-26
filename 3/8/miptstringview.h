#pragma once
#include <iostream>
namespace mipt {
    
class String;

class StringView {

private:
    const char* mpData;
    size_t mSize;

public:  
    StringView();
    StringView(const StringView& str);
    StringView(const mipt::String& s);
    StringView(const char* s);
    const char& at(size_t i);
    const char& operator[](size_t i) const;
    bool operator<(const StringView& right) const;
    size_t size() const;
    StringView substr(size_t pos, size_t count);
    void remove_prefix(size_t n); 
    void remove_suffix(size_t n);
};

std::ostream& operator<<(std::ostream& out, const StringView& sv);

}
