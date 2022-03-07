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

#include "BaseConstruct.hh"
#include "Beam.hh"
#include "DetectorWorld.hh"
#include "GlobalVariables.hh"
#include "Kapton.hh"
#include "LeadBlock.hh"
#include "Mesh.hh"
#include "ScintillatorObject.hh"
#include "Shield.hh"
#include "StoppingTarget.hh"
#include "VacuumVolume.hh"

using std::cout;
using std::endl;

class XMLParamParser {
 public:
  XMLParamParser(TString xmlfile) {
    _scintillators = new TList();
    _pb_blocks = new TList();
    nodenames = {"filename", "beam",   "world", "vacuum",   "kapton",
                 "shield",   "target", "mesh",  "pb_block", "scintillator"};
    normalbox = {"name",      "type", "ID",   "hsize", "vsize",
                 "thickness", "xpos", "ypos", "zpos",  "angle"};
    normalTubs = {"name", "type", "ID",   "diameter", "length",
                  "xpos", "ypos", "zpos", "angle"};
    scinti_node = {"name",      "type", "ID",   "groupID", "hsize", "vsize",
                   "thickness", "xpos", "ypos", "zpos",    "angle"};
    mesh_node = {"name",  "type", "ID",   "wire_diameter", "length",
                 "pitch", "xpos", "ypos", "zpos"};

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
  std::vector<TString> nodenames;
  std::vector<TString> normalbox;
  std::vector<TString> normalTubs;
  std::vector<TString> scinti_node;
  std::vector<TString> mesh_node;

  TString FileName(TString fname);
  Int_t ParseFile(TString filename);
  void ParseParameters(TXMLNode *_node);
  void GetParams(TXMLNode *_child, std::vector<TString> attr_name,
                 std::vector<G4String> &strdata, std::vector<int> &ids,
                 std::vector<double> &numdata);
  Beam *ParseBeam(TXMLNode *_child);
  DetectorWorld *ParseWorld(TXMLNode *_child);
  VacuumVolume *ParseVacuumV(TXMLNode *_child);
  Kapton *ParseKapton(TXMLNode *_child);
  Shield *ParseShield(TXMLNode *_child);
  StoppingTarget *ParseTarget(TXMLNode *_child);
  Mesh *ParseMesh(TXMLNode *_child);
  LeadBlock *ParsePbBlock(TXMLNode *_child);
  ScintillatorObject *ParseScinti(TXMLNode *_child);
};
#endif  // !XMLPARSER_HH