#ifndef XMLPARSER_HH
#define XMLPARSER_HH

#include <Riostream.h>
#include <TDOMParser.h>
#include <TList.h>
#include <TObject.h>
#include <TXMLAttr.h>
#include <TXMLNode.h>
#include <TXMLParser.h>

#include <globals.hh>
#include <iostream>

#include "GlobalVariables.hh"
#include "XMLObject.hh"

using std::cout;
using std::endl;

class XMLParamParser {
 public:
  XMLParamParser(TString xmlfile) {
    _scintillators = new TList();
    _pb_blocks = new TList();
    if (ParseFile(xmlfile) == 0) {
      std::cerr << "can't find xml file !" << std::endl;
    }
  }
  ~XMLParamParser() {}
  TString GetFileBaseName();
  TString GetXMLBaseName();

 private:
  TString file_base_name;
  TString xml_base_name;

  TString FileName(TString fname);
  Int_t ParseFile(TString filename);
  void ParseParameters(TXMLNode *_node);
  Beam *ParseBeam(TXMLNode *_child);
  StoppingTarget *ParseTarget(TXMLNode *_child);
  Mesh *ParseMesh(TXMLNode *_child);
  LeadBlock *ParsePbBlock(TXMLNode *_child);
  XMLScintillator *ParseScinti(TXMLNode *_child);
};
#endif  // !XMLPARSER_HH