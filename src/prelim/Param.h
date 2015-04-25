#ifndef PARAM_H
#define PARAM_H

#include <map>
#include <list>
#include <vector>
#include <string>
#include <sstream>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;


template <class T>
bool from_string(T& t, const std::string &s, std::ios_base& (*f)(std::ios_base&)) 
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}


#define MAX_LINE_LENGTH         10000

/**
 * stores tokens related to the first keyword
 */
class Param {

public:
  int flag;

public:
  vector<string> token;
  int requestCount;

public:
  // constructors and destructors
  Param() :
    requestCount(0), flag(0) {
  }

  Param(const string &n) {
    tokenizeString(token, n, " =:\t");
    requestCount = 0;
  }

  void tokenizeString(vector<string> &tokens, const string &str, const string &delimiters) {
    string::size_type lastPos = str.find_first_not_of(delimiters, 0); // skip delimiters at beginning
    string::size_type pos = str.find_first_of(delimiters, lastPos); // find first "non-delimiter"

    while (string::npos != pos || string::npos != lastPos) {
      tokens.push_back(str.substr(lastPos, pos - lastPos)); // add token to the vector<string>
      lastPos = str.find_first_not_of(delimiters, pos); // skip delimiters
      pos = str.find_first_of(delimiters, lastPos); // find next "non-delimiter"
    }
  }
  
  void eraseString(int pos)
  {
    if (pos < token.size())
      token.erase(token.begin()+pos);
    else 
    {
      cerr << "no value at pos: " << pos << " of " << token[0] << endl;
      throw(-1);
    }
  }
  
  void insertString(int pos, const string &str)
  {
    if (pos < token.size())
      token.insert(token.begin()+pos, str);
  }
  
  void attachStringAtEnd(const string &str)
  {
    token.push_back(str);
  }
  
  friend ostream& operator<< (ostream &out, Param &par);

  void print() {
    for (vector<string>::iterator it=token.begin(); it<token.end(); it++)
      cout << *it << " ";
    cout << endl;
  }

  void writeToFile(FILE *fp) {

    vector<string>::iterator it=token.begin();
    fprintf(fp, "%s = ", (*it).c_str());

    for (it=token.begin()+1; it<token.end(); it++)
      fprintf(fp, "%s ", (*it).c_str());

    fprintf(fp, "\n");
  }

  int getSize() {
    return (token.size());
  }

  int isInt(size_t pos = 1) {
    requestCount ++;
    if (pos < token.size()) {
      int value;
      return(from_string<int>(value,token[pos],std::dec));
    }
    else {
      cerr << "no value at pos: " << pos << " of " << token[0] << endl;
      throw(-1);
    }
  }

  int getInt(int pos = 1) {
    requestCount ++;
    if (pos < token.size()) {
      int value;
      if (from_string<int>(value, token[pos], std::dec)) {
        return (value);
      } else {
        cerr << "value at pos: "<< pos << " of "<< token[0]<< " is not int."<< endl;
        throw(-1);
      }
    } else {
      cerr << "no value at pos: "<< pos << " of "<< token[0]<< endl;
      throw(-1);
    }
  }

  int getInt(string afterTokenName) {
    requestCount ++;

    // search for token after parameter keyword
    int pos = 1;
    while ((token[pos] != afterTokenName) && (pos < token.size()-1))
      pos++;

    pos++;

    if (pos == token.size())
    {
      cerr << "no name \"" << afterTokenName << "\" found in paramter \"" << token[0] << "\"" << endl;
      throw(-1);
    }

    return getInt(pos);
  }

  int isDouble(size_t pos = 1) {
    requestCount ++;
    if (pos < token.size()) {
      double value;
      return (from_string<double>(value, token[pos], std::dec));
    } else {
      cerr << "no value at pos: "<< pos << " of "<< token[0]<< endl;
      throw(-1);
    }
  }

  double getDouble(int pos = 1) {
    requestCount ++;
    if (pos < token.size()) {
      double value;
      if (from_string<double>(value, token[pos], std::dec)) {
        return (value);
      } else {
        cerr << "value at pos: "<< pos << " of "<< token[0]<< " is not double."<< endl;
        throw(-1);
      }
    } else {
      cerr << "no value at pos: "<< pos << " of "<< token[0]<< endl;
      throw(-1);
    }
  }

  double getDouble(string afterTokenName) {
    requestCount ++;

    // search for token after parameter keyword
    int pos = 1;
    while ((token[pos] != afterTokenName) && (pos < token.size()-1))
      pos++;

    pos++;

    if (pos == token.size())
    {
      cerr << "no name \"" << afterTokenName << "\" found in paramter \"" << token[0] << "\"" << endl;
      throw(-1);
    }

    return getDouble(pos);
  }

  string getString(int pos = 1) {
    requestCount ++;
    if (pos <= token.size()-1)
      return token[pos]; // returns copy
    else {
      cerr << "no parameter at pos: " << pos << " of " << token[0] << endl;
      throw(-1);
    }
  }

  string getString(string afterTokenName) {
    requestCount ++;

    // search for token after parameter keyword
    int pos = 1;
    while ((token[pos] != afterTokenName) && (pos < token.size()-1))
      pos++;

    pos++;

    if (pos == token.size())
    {
      cerr << "no name \"" << afterTokenName << "\" found in paramter \"" << token[0] << "\"" << endl;
      throw(-1);
    }

    return getString(pos);
  }

  int findString(const string &str)
  {
    int i=0;
    while (i < token.size())
    {
      if (token[i] == str)
        return i;
      i++;
    }
    return 0;
  }

  int getStringPos(const string &str) 
  {
    int i=0;
    while (i < token.size())
    {
      if (token[i] == str)
        return i;
      i++;
    }
    cerr << "string \"" << str << "\" not found" << endl; 
    throw(-1);
  }

  string getParamName() {
    return token[0];
  }

  int getRequestedCount() {
    return requestCount;
  }

};



/**
 * stores parameters in a STL map,
 * map
 */
class ParamMap {

protected:
  std::map<string, vector<Param> > paraMap; ///< the STL map for the parameters

public:

  ParamMap(const char *fileName) {
    getParamFromFile(fileName);
  }

  ParamMap() {}


  ParamMap & getThisParamMap()
  {
    return *this;
  }

  int getIntParam(const string &k); //, size_t iParamVec = 0
  int getIntParam(const string &k, const int defaultValue);
  int getIntParam(const string &str, const string &numberStr);

  double getDoubleParam(const string &str);
  double getDoubleParam(const string &str, const double defaultValue);
  double getDoubleParam(const string &str, const string &numberStr);

  string getStringParam(const string &k);
  string getStringParam(const string &k, const string &numberStr);



  void Remove(const string &str);

  /**
   * finds string in parameter map,
   * \param string
   */
  bool checkParam(const string &str);

  /**
   * return the STL vector of the parameters stored in the map if the keyword is present in the map
   * \param string
   * \return Param *
   */
  bool getParam(vector<Param> *&lst, const string &str);

  /**
   * finds string in parameter map,
   * \param string
   * \return boolean
   * \return pointer ref to Param
   */
  bool getParam(Param *&p_ptr, const string &str, size_t iVecPara = 0);

  /**
   * finds string in parameter map
   * \param string
   * \return Param *
   */
  Param * getParam(const string &str, size_t iVecPara = 0);

  /**
   * operator[] finds string in parameter map
   * \param string
   * \return Param &
   */
//  Param * operator[](const string &str);

  /**
   * return the STL vector of the parameters stored in the map associated with a keyword
   * \param string=name of the keyword
   * \return parameter vector associated with the keyword
   */
  vector<Param> * getParamVector(const string &str);

  /**
   * adds string to parameter map and checks first if there is a # somewhere
   */
  void add(const string &str);

  /**
   * get the parameters from file
   * \param filename
   */
  void getParamFromFile(const char *fileName);


  /**
  * use for the the add function in getParamFromFile
  *
  */
  int checkHash(const string &str);

  /**
   * dump the parameters in the map to a file
   * \param FILE *fp
   */
  void writeParamToFileASCIIstyleC(char fname[]);

};

#endif

