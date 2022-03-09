#ifndef XMLPARSER_HH
#define XMLPARSER_HH

#include <Riostream.h>
#include <TDOMParser.h>
#include <TList.h>
#include <TObject.h>
#include <TXMLAttr.h>
#include <TXMLNode.h>
#include <TXMLParser.h>

#include <G4LogicalVolume.hh>
#include <algorithm>  // std::sort, std::unique
#include <globals.hh>
#include <iostream>

#include "BaseBox.hh"
#include "BaseConstruct.hh"
#include "BaseTubs.hh"
#include "Beam.hh"
#include "GlobalVariables.hh"
#include "Mesh.hh"
#include "Scintillator.hh"

using std::cout;
using std::endl;
using namespace CLHEP;

class XMLParamParser {
 public:
  XMLParamParser(TString xmlfile, Scintillator *_scinti) {
    scinti = _scinti;
    nodenames = {"filename", "beam", "basebox", "basetubs", "mesh"};
    beamnode = {"size", "spread_angle", "mean_momentum", "momentum_width"};
    normalconst = {"parent", "size", "position", "angle", "color"};
    mesh_node = {"parent", "size", "pitch", "position", "angle", "color"};
    // attrlist = {"name", "type", "ID", "groupID", "index", "unit"};

    if (ParseFile(xmlfile) == 0) {
      std::cerr << "can't find xml file !" << std::endl;
    }
  }
  ~XMLParamParser() {}
  TString GetFileBaseName();
  TString GetXMLBaseName();
  std::vector<BaseConstruct *> GetConstructsList();
  BaseConstruct *GetConstruct(int index);
  BaseConstruct *GetWorld();
  int GetConstNumber();

 private:
  TString file_base_name;
  TString xml_base_name;
  Scintillator *scinti;
  std::vector<BaseConstruct *> constructs;
  std::vector<TString> nodenames, beamnode, normalconst, mesh_node,
      construct_names, construct_type;  //, attrlist;
  std::vector<int> construct_number;

  TString FileName(TString fname);
  Int_t ParseFile(TString filename);
  void ParseParameters(TXMLNode *_node);
  bool judgeElementNode(TXMLNode *_node);
  int GetIntFromAttribute(TXMLAttr *attr, TString attrname);
  double GetDoubleFromAttribute(TXMLAttr *attr, TString attrname);
  void GetStringFromAttribute(TXMLNode *node, TString attrname,
                              TString &output);
  void GetStringFromAttribute(TXMLNode *node, std::vector<TString> attrname,
                              std::vector<TString> &output);
  G4double GetUnitFromAttribute(TXMLAttr *attr);
  void GetDoubleFromNode(TXMLNode *_node, G4double &output);
  void GetDoubleFromNode(TXMLNode *_node, G4ThreeVector &output);
  void GetDoubleFromNode(TXMLNode *_node, G4TwoVector &output);
  void SetConstructNumber();
  void SetScintiGroupNumber();
  Beam *ParseBeam(TXMLNode *_child);
  BaseBox *ParseBox(TXMLNode *_child);
  BaseTubs *ParseTubs(TXMLNode *_child);
  Mesh *ParseMesh(TXMLNode *_child);
};
inline bool XMLParamParser::judgeElementNode(TXMLNode *_node) {
  return _node->GetNodeType() == TXMLNode::kXMLElementNode;
}

inline int XMLParamParser::GetIntFromAttribute(TXMLAttr *_attr,
                                               TString attrname) {
  int output = 0;
  TString gotname = _attr->GetName();
  if (gotname.Contains(attrname)) {
    output = TString(_attr->GetValue()).Atoi();
  }
  return output;
}

inline double XMLParamParser::GetDoubleFromAttribute(TXMLAttr *_attr,
                                                     TString attrname) {
  double output = 0;
  TString gotname = _attr->GetName();
  if (gotname.Contains(attrname)) {
    output = TString(_attr->GetValue()).Atof();
  }
  return output;
}

inline void XMLParamParser::GetStringFromAttribute(TXMLNode *_node,
                                                   TString attrname,
                                                   TString &output) {
  TString gotname;
  G4double unit = 0.;
  TList *att_list = _node->GetAttributes();
  TXMLAttr *attr = 0;
  TIter next(att_list);
  if (_node->HasAttributes()) {
    while ((attr = (TXMLAttr *)next())) {
      gotname = attr->GetName();
      if (gotname.Contains(attrname)) {
        output = TString(attr->GetValue());
      }
    }
  }
}

inline void XMLParamParser::GetStringFromAttribute(
    TXMLNode *_node, std::vector<TString> attrname,
    std::vector<TString> &output) {
  TString gotname;
  int n_attr = attrname.size();
  // output.resize(n_attr);
  G4double unit = 0.;
  TList *att_list = _node->GetAttributes();
  TXMLAttr *attr = 0;
  TIter next(att_list);
  if (_node->HasAttributes()) {
    while ((attr = (TXMLAttr *)next())) {
      gotname = attr->GetName();
      for (int i = 0; i < n_attr; ++i) {
        if (gotname.Contains(attrname[i])) {
          output.emplace_back(TString(attr->GetValue()));
        }
      }
    }
  }
}

inline G4double XMLParamParser::GetUnitFromAttribute(TXMLAttr *_attr) {
  std::vector<TString> unitsymbol = {"mm", "cm",  "m",   "deg", "rad",
                                     "%",  "keV", "MeV", "GeV"};
  TString tmpstr;
  G4double output;
  int n_unit = unitsymbol.size();
  std::vector<G4double> unitnum = {mm, cm, m, deg, rad, perCent, keV, MeV, GeV};
  if (std::strcmp(_attr->GetName(), "unit") == 0) {
    tmpstr = TString(_attr->GetValue());
    for (int i = 0; i < n_unit; ++i) {
      if (tmpstr.Contains(unitsymbol[i])) {
        output = unitnum[i];
      }
    }
  }
  return output;
}

inline void XMLParamParser::GetDoubleFromNode(TXMLNode *_node,
                                              G4double &output) {
  G4double unit = 0.;
  TList *att_list = _node->GetAttributes();
  TXMLAttr *attr = 0;
  TIter next(att_list);
  if (_node->HasAttributes()) {
    while ((attr = (TXMLAttr *)next())) {
      unit = GetUnitFromAttribute(attr);
    }
    output = TString(_node->GetText()).Atof() * unit;
  }
}

inline void XMLParamParser::GetDoubleFromNode(TXMLNode *_node,
                                              G4ThreeVector &output) {
  G4double unit = 0.;
  int index = 0;
  TList *att_list = _node->GetAttributes();
  TXMLAttr *attr = 0;
  TIter next(att_list);
  if (_node->HasAttributes()) {
    while ((attr = (TXMLAttr *)next())) {
      unit = GetUnitFromAttribute(attr);
      index = GetIntFromAttribute(attr, "index");
    }
    output[index] = TString(_node->GetText()).Atof() * unit;
  }
}

inline void XMLParamParser::GetDoubleFromNode(TXMLNode *_node,
                                              G4TwoVector &output) {
  G4double unit = 0.;
  int index = 0;
  TList *att_list = _node->GetAttributes();
  TXMLAttr *attr = 0;
  TIter next(att_list);
  if (_node->HasAttributes()) {
    while ((attr = (TXMLAttr *)next())) {
      unit = GetUnitFromAttribute(attr);
      index = GetIntFromAttribute(attr, "index");
    }
    output[index] = TString(_node->GetText()).Atof() * unit;
  }
}

inline void XMLParamParser::SetConstructNumber() {
  construct_type = construct_names;
  std::sort(construct_type.begin(), construct_type.end());
  construct_type.erase(
      std::unique(construct_type.begin(), construct_type.end()));
  int n_type = construct_type.size();
  for (int i = 0; i < n_type; ++i) {
    construct_number.emplace_back(std::count(
        construct_names.begin(), construct_names.end(), construct_type[i]));
  }
}

inline std::vector<BaseConstruct *> XMLParamParser::GetConstructsList() {
  return constructs;
}

inline BaseConstruct *XMLParamParser::GetConstruct(int index) {
  return constructs[index];
}

inline int XMLParamParser::GetConstNumber() { return constructs.size(); }

inline BaseConstruct *XMLParamParser::GetWorld() {
  auto itr = std::find(construct_names.begin(), construct_names.end(), "world");
  int index = 0;
  if (itr != construct_names.end()) {
    index = std::distance(construct_names.begin(), itr);
  }
  return constructs[index];
}

inline void XMLParamParser::SetScintiGroupNumber() { _scinti_group_num += 1; }

#endif  // !XMLPARSER_HH