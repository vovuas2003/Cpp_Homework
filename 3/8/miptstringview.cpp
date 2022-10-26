#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include "miptstring.h"
#include "miptstringview.h"

using std::cout, std::cin, std::endl, std::size_t;

namespace mipt {
    
    StringView::StringView() {
        mSize = 0;
        mpData = nullptr;
    }
    
    StringView::StringView(const StringView& str) {
        mSize = str.mSize;
        mpData = str.mpData;
    }
    
    StringView::StringView(const mipt::String& s) {
        mSize = s.getSize();
        mpData = s.cStr();  
    }
    
    StringView::StringView(const char* s) {
        mpData = s;
        mSize = strlen(s); 
    }
    
    const char& StringView::at(size_t i) {
        if (i >= mSize)
        {
            throw std::out_of_range("Index is out of range!");
        }
        return mpData[i];
    }
    
    const char& StringView::operator[](size_t i) const {
        return mpData[i];
    }
    
    bool StringView::operator<(const StringView& right) const {
        size_t i = 0;
        while (i < mSize && i < right.mSize && mpData[i] == right.mpData[i])
            i++;

        return mpData[i] < right.mpData[i];
    }
    
    size_t StringView::size() const {
        return mSize;
    }
    
    StringView StringView::substr(size_t pos, size_t count) {
        if (pos > mSize) 
                throw std::out_of_range("Error! Index is out of bounds.");
        if (pos + count > mSize)
              count = mSize - pos;
        StringView result;
        result.mpData = mpData + pos;
        result.mSize = count;
        return result;
    }
    
    void StringView::remove_prefix(size_t n) {
            mSize -= n;
    }
    
    void StringView::remove_suffix(size_t n) {
            mSize -= n;
            mpData += n;
    }
    
std::ostream& operator<<(std::ostream& out, const mipt::StringView& sv) {
    size_t size = sv.size();
    for (int i = 0; i < size; ++i)
            out << sv[i];
    return out; 
}
    
};

