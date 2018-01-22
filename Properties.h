#ifndef __Properties_h__
#define __Properties_h__

#include "Arduino.h"
#include <SD.h>


class Properties
{
public:
  typedef void (*ConfigListener) (String key, String value);

  Properties(File file);

  void parseStrings(ConfigListener consumer);
  String readString(const char* searchKey) { String key = String(searchKey); return readString(key); }
  String readString(String& searchKey);

protected:
  void readPair();
  void readUntil(char limit, String& target);

private:
  File _file;
  String _key;
  String _value;
};

#endif // __Properties_h__
