#include "Properties.h"

#define STRING_RESERVATION 24


Properties::Properties(File f)
  : _file(f)
{
}

/** Read all config pairs key=value into a map. */
void Properties::parseStrings(ConfigListener consumer)
{
  while (_file.available())
  {
    readPair();
    if (_key.length() == 0) continue;
    consumer(_key, _value);
  }
}

/** Read the value of a config with the given key. */
String Properties::readString(String& key)
{
  while (_file.available()) {
    readPair();
    if (_key.length() > 0 && key.equalsIgnoreCase(_key)) {
      return _value;
    }
  }
  return String();
}

/** Read a config pair key=value from a stream. */
void Properties::readPair()
{
  _key = String();
  _value = String();
  readUntil('=', _key);
  if (_key.length() == 0 || _key.equals("\n"))
  {
    _key = String();
  }
  else
  {
    readUntil('\n', _value);
    _key.trim();
    _value.trim();
  }
}

/** Read stream until a limit character appears. */
void Properties::readUntil(char limit, String& target)
{
  target.reserve(STRING_RESERVATION);
  bool comment = false;
  char prev = '\0';
  char ch = '\0';
  while (_file.available() && ch != limit && ch != '\n')
  {
    prev = ch;
    ch = _file.read();
    if (prev == ch && ch == '/' && !comment)
    {
      target.remove(target.length() - 1);
      comment = true;
    }
    else if (ch != limit && ch != '\r' && !comment)
    {
      target.concat(ch);
    }
  }
}
