#ifndef HEADER_CACHED_FUNCTION_INCLUDED
#define HEADER_CACHED_FUNCTION_INCLUDED

#include <map>
#include <functional>
#include <unordered_map>

template< typename _ResultType(typename _DataType) >
class CachedFunction {
private:
    std::function< _ResultType(_DataType) > function;
    std::map< _DataType, _ResultType > cache;
public:
    CachedFunction( std::function< _ResultType(_DataType) > && f) : function(f) {
    }
    _ResultType operator ()(_DataType arg) {
        std::map< _DataType, _ResultType >::iterator iter = cache.find(arg);
        if (iter != cache.end())
            return iter->second;
        
        _ResultType res = function(arg);
        cache[arg] = res;
        return res;
    }
};

#endif