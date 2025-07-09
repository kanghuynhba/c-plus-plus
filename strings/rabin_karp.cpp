#include <cassert>
#include <cmath>
#include <iostream>
#ifdef _MSC_VER
#include <string>
#else
#include <cstring>
#endif

#define PRIME 5

namespace string_search {
    // Hashing
    int64_t create_hash(const std::string& s, int n) {
        int64_t result=0;
        for(int i=0; i<n; ++i) {
            result+=(int64_t)(s[i]*(int64_t)pow(PRIME, i));
        }
        return result;
    }

    // Rolling
    int64_t recalculate_hash(const std::string& s, int old_index, int new_index, int64_t old_hash, int patLength) {
        int64_t new_hash=old_hash-s[old_index];
        new_hash/=PRIME;
        new_hash+=(int64_t)(s[new_index]*(int64_t)pow(PRIME, patLength-1));
        return new_hash;
    }
    // Check whether valid match or spurious hit
    bool check_is_equal(const std::string& str1, const std::string& str2, int start1, int end1, int start2, int end2) {
        if(end1-start1!=end2-start2) {
            return false;
        }
        while(start1<=end1 && start2<=end2) {
            if(str1[start1]!=str2[start2]) {
                return false;
            }
            start1++;
            start2++;
        }
        return true;
    }
    int rabin_karp(const std::string& str, const std::string& pat) {
        int64_t pat_hash=create_hash(pat, pat.size());
        int64_t str_hash=create_hash(str, pat.size());
        for(int i=0; i<=str.size()-pat.size(); ++i) {
            if(pat_hash==str_hash && check_is_equal(str, pat, i, i+pat.size()-1, 0, pat.size()-1)) {
                return i;
            }  
            if(i<str.size()-pat.size()) {
                str_hash=recalculate_hash(str, i, i+pat.size(), str_hash, pat.size());
            }
        } 
        return -1;
    }
} // namespace string_search

using string_search::rabin_karp;

int main(void) {
    assert(rabin_karp("helloWorld", "world")==-1);
    assert(rabin_karp("helloWorld", "World")==5);
    assert(rabin_karp("this_is_c++", "c++")==8);
    assert(rabin_karp("happy_coding", "happy")==0);
}
