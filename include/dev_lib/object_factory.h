#ifndef __DEV_LIB_OBJECT_FACTORY_H__
#define __DEV_LIB_OBJECT_FACTORY_H__

#include <map>
#include <cassert>

template <typename K, typename V> 
class ObjectFactoryT
{
public:
  bool has(K key) const
  {
    return (data.find(key) != data.end());
  }
  void add(K key, V value)
  {
    assert(!has(key));
    data.insert(std::make_pair(key, value));
    assert(has(key));
  }
  V get(K key) const
  {
    assert(has(key));
    return data.find(key)->second;
  }
  
private:
  std::map<K,V> data;
};

#endif
