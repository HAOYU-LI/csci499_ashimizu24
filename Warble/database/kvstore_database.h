#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <bits/stdc++.h>

// Database class - holds unordered map with all warble information
// key - prefix (what type of data) + id (user id/warble id)
// value - struct object serialized into string
class KVStoreDb {

public:
  // Insert given key and value pair into the database
  // Parameters: string with the key and value to insert into db
  // Return: void
  void Put(const std::string key, const std::string value);

  // Getting value from database
  // Parameter: string with the key to find from db
  // Return: string with value, key is associated with
  std::string Get(const std::string key);

  // Removing key/value pair from database
  // Parameter: string with key to remove from db
  // Return: void
  void Remove(std::string key);

  // Put serialized_warble to corresponding set of hashtag
  // Parameters: hashtag as key, serialized_warble as value.
  void PutStream(const std::string hashtag, const std::string serialized_warble);

  // Getting a set of unique serialized_warbles, which 
  // contain hashtag in their text.
  // Parameters: hashtag as key
  // Return: a set of distinct serialized warbles.
  std::unordered_set<std::string> GetStream(const std::string hashtag);


private:
  // database mapping key (prefix+id/username) to serialized struct
  std::unordered_map<std::string, std::string> db_;

  // database of hashtag, which is used to collect hashtag and warbles(unique)
  // unordered_set is used instead of vector because
  // the text of a warble may contain hashtag more than once.
  // Duplicate warbles of a hashtag should be avoided.
  std::unordered_map<std::string, std::unordered_set<std::string>> hashtag_db_;
};
