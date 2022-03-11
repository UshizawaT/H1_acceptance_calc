#include "XMLParamParser.hh"

TString XMLParamParser::FileName(TString fname) {
  TString xmlfilename;
  if (fname.Contains(".xml", TString::kExact)) {
    xml_base_name = fname;
    xml_base_name.ReplaceAll(".xml", "");
    xmlfilename = fname;
  } else {
    xml_base_name = fname;
    xmlfilename = fname + ".xml";
  }
  return xmlfilename;
}

Int_t XMLParamParser::ParseFile(TString filename) {
  TDOMParser *domParser = new TDOMParser();
  domParser->SetValidate(false);
  TString ifname = FileName(filename);
  int parsecode = domParser->ParseFile(ifname);
  if (parsecode < 0) {
    std::cerr << domParser->GetParseCodeMessage(parsecode) << std::endl;
    return 0;
  }
  TXMLNode *xmlnode = domParser->GetXMLDocument()->GetRootNode();
  ParseParameters(xmlnode);
  // std::cout << "Sucess load xml" << std::endl;
  return 1;
}

void XMLParamParser::ParseParameters(TXMLNode *_node) {
  TXMLNode *child;
  for (; _node; _node = _node->GetNextNode()) {
    if (_node->GetNodeType() == TXMLNode::kXMLElementNode) {
      // cout << "node name : " << _node->GetNodeName() << endl;
      if (std::strcmp(_node->GetNodeName(), "params") == 0) {
        child = _node->GetChildren();
        int n_group = 0, __groupid = 0, nodetypes = 0;
        BaseConstruct *tmpconst;
        bool consistent = false;
        nodetypes = nodenames.size();
        for (; child; child = child->GetNextNode()) {
          if (judgeElementNode(_node)) {
            for (int i = 0; i < nodetypes; ++i) {
              consistent =
                  (std::strcmp(child->GetNodeName(), nodenames[i]) == 0);
              if (consistent && i == 0) {
                file_base_name = child->GetText();
              } else if (consistent && i == 1) {
                _beam = ParseBeam(child);
              } else if (consistent && i == 2) {
                tmpconst = ParseBox(child);
                constructs.emplace_back(tmpconst);
              } else if (consistent && i == 3) {
                tmpconst = ParseTubs(child);
                constructs.emplace_back(tmpconst);
              } else if (consistent && i == 4) {
                tmpconst = ParseMesh(child);
                constructs.emplace_back(tmpconst);
              }
            }
          }
        }
      }
    }
  }
  SetScintiGroupNumber();
  cout << "N scinti : " << _scinti_num << endl;
  cout << "scinti group : " << _scinti_group_num << endl;
}

Beam *XMLParamParser::ParseBeam(TXMLNode *_node) {
  TString __beamtype = "mu+", node_name;
  G4double __angle = 0., mom_w, mom_m;
  G4TwoVector __size, __mom;
  std::vector<TString> attrnames = {"type"};
  std::vector<TString> attrvalue;
  GetStringFromAttribute(_node, attrnames, attrvalue);
  if (attrvalue.size() == 1) __beamtype = attrvalue[0];
  bool consistent = false;
  int n_node = beamnode.size();
  TXMLAttr *attr = 0;
  int index;
  G4double unit;
  TXMLNode *child = _node->GetChildren();
  for (; child; child = child->GetNextNode()) {
    if (judgeElementNode(child)) {
      node_name = TString(child->GetNodeName());
      // G4cout << "beam node name : " << node_name << G4endl;
      for (int i = 0; i < n_node; ++i) {
        consistent = node_name.Contains(beamnode[i]);
        if (consistent) {
          if (i == 0) {
            GetDoubleFromNode(child, __size);
          } else if (i == 1) {
            GetDoubleFromNode(child, __angle);
          } else if (i == 2) {
            GetDoubleFromNode(child, mom_m);
            __mom[0] = mom_m;
          } else if (i == 3) {
            // GetDoubleFromNode(_node, mom_w);
            TString strunit;
            GetStringFromAttribute(child, "unit", strunit);
            GetUnitFromString(strunit, unit);
            mom_w = TString(child->GetText()).Atof() * unit;
            if (strunit.Contains("%")) {
              __mom[1] = mom_w * mom_m;
            } else {
              __mom[1] = mom_w;
            }
          }
        }
      }
    }
  }
  cout << "beam (type, hsize, vsize, spread_angle, mean_mom, w_mom) : ("
       << __beamtype << ", " << __size[0] << ", " << __size[1] << ", "
       << __angle << ", " << __mom[0] << ", " << __mom[1] << ")" << endl;
  return new Beam(__beamtype, __size, __angle, __mom);
}
/*
void XMLParamParser::GetParams(TXMLNode *_child, std::vector<TString> attr_name,
                               std::vector<G4String> &strdata,
                               std::vector<int> &ids,
                               std::vector<double> &numdata) {
  int n_attr = attr_name.size();
  int n_names = strdata.size();
  int n_ids = ids.size();
  bool groupflag = (std::strcmp(attr_name[3], "groupID") == 0);

  if (_child->HasAttributes()) {
    TList *att_list = _child->GetAttributes();
    TXMLAttr *attr = 0;
    TIter next(att_list);
    while ((attr = (TXMLAttr *)next())) {
      for (int i = 0; i < n_attr; i++) {
        if (std::strcmp(attr->GetName(), attr_name[i]) == 0) {
          if (i == 0 || i == 1) {
            strdata[i] = G4String(attr->GetValue());
          } else if (i == 2) {
            ids[0] = TString(attr->GetValue()).Atoi();
          } else if (i == 3 && groupflag) {
            ids[1] = TString(attr->GetValue()).Atoi();
          } else {
            numdata[i - n_names - n_ids] = TString(attr->GetValue()).Atof();
          }
        }
      }
    }
  }
}**/

BaseBox *XMLParamParser::ParseBox(TXMLNode *_node) {
  TString node_name, parent_name, colorname;
  std::vector<int> __id(2);
  G4double __angle = 0.;
  G4ThreeVector __size, __pos;
  bool sd_flag = false, consistent = false;
  std::vector<TString> attrnames = {"name", "type", "ID", "groupID"};
  std::vector<TString> attrvalue;
  GetStringFromAttribute(_node, attrnames, attrvalue);
  if (attrvalue.size() == attrnames.size() - 1) {
    __id[0] = attrvalue[2].Atoi();
  } else if (attrvalue.size() == attrnames.size()) {
    __id[0] = attrvalue[2].Atoi();
    __id[1] = attrvalue[3].Atoi();
    _scinti_group_ids.emplace_back(__id[1]);
    _scinti_num += 1;
    _scinti_group_num =
        _scinti_group_num < __id[1] ? __id[1] : _scinti_group_num;
    sd_flag = true;
    G4cout << "Sensitive Detector!" << G4endl;
  }
  construct_names.emplace_back(attrvalue[0]);
  int n_node = normalconst.size();
  int parent_index = 0;
  bool worldflag = false;
  G4LogicalVolume *logicalparent;
  TXMLNode *child = _node->GetChildren();
  for (; child; child = child->GetNextNode()) {
    if (judgeElementNode(child)) {
      node_name = TString(child->GetNodeName());
      for (int i = 0; i < n_node; ++i) {
        consistent = node_name.Contains(normalconst[i]);
        if (consistent) {
          if (i == 0) {
            parent_name = child->GetText();
            auto itr = std::find(construct_names.begin(), construct_names.end(),
                                 parent_name);
            if (itr == construct_names.end() && parent_name.Contains("none")) {
              worldflag = true;
            } else if (itr != construct_names.end()) {
              parent_index = std::distance(construct_names.begin(), itr);
              logicalparent = constructs[parent_index]->GetLogicalVol();
            } else {
              G4cerr << "no parents !" << G4endl;
            }
          } else if (i == 1) {
            GetDoubleFromNode(child, __size);
          } else if (i == 2) {
            GetDoubleFromNode(child, __pos);
          } else if (i == 3) {
            GetDoubleFromNode(child, __angle);
          } else if (i == 4) {
            colorname = child->GetText();
          }
        }
      }
    }
  }
  BaseBox *outputobj;
  cout << "box (type, hsize, vsize, thickness, angle) : (" << attrvalue[1]
       << ", " << __size[0] << ", " << __size[1] << ", " << __size[2] << ", "
       << __angle << ")" << endl;
  if (worldflag) {
    outputobj = new BaseBox(attrvalue[0], __id[0], attrvalue[1], __size, __pos,
                            __angle, colorname);
  } else if (sd_flag) {
    outputobj =
        new BaseBox(logicalparent, scinti, attrvalue[0], __id[0], __id[1],
                    attrvalue[1], __size, __pos, __angle, colorname);
  } else {
    outputobj = new BaseBox(logicalparent, attrvalue[0], __id[0], attrvalue[1],
                            __size, __pos, __angle, colorname);
  }
  outputobj->Initialize(material, visatt);
  outputobj->SetGeometry();
  cout << endl;
  return outputobj;
}

BaseTubs *XMLParamParser::ParseTubs(TXMLNode *_node) {
  TString node_name, parent_name, colorname;
  std::vector<int> __id(2);
  G4double __angle = 0.;
  G4TwoVector __size;
  G4ThreeVector __pos;
  bool sd_flag = false, consistent = false;
  std::vector<TString> attrnames = {"name", "type", "ID", "groupID"};
  std::vector<TString> attrvalue;
  GetStringFromAttribute(_node, attrnames, attrvalue);
  if (attrvalue.size() == attrnames.size() - 1) {
    __id[0] = attrvalue[2].Atoi();
  } else if (attrvalue.size() == attrnames.size()) {
    __id[0] = attrvalue[2].Atoi();
    __id[1] = attrvalue[3].Atoi();
    sd_flag = true;
  }
  construct_names.emplace_back(attrvalue[0]);
  int n_node = normalconst.size();
  int parent_index = 0;
  bool worldflag = false;
  G4LogicalVolume *logicalparent;
  TXMLNode *child = _node->GetChildren();
  for (; child; child = child->GetNextNode()) {
    if (judgeElementNode(child)) {
      node_name = TString(child->GetNodeName());
      for (int i = 0; i < n_node; ++i) {
        consistent = node_name.Contains(normalconst[i]);
        if (consistent) {
          if (i == 0) {
            parent_name = child->GetText();
            auto itr = std::find(construct_names.begin(), construct_names.end(),
                                 parent_name);
            if (itr == construct_names.end() && parent_name.Contains("none")) {
              worldflag = true;
            } else if (itr != construct_names.end()) {
              parent_index = std::distance(construct_names.begin(), itr);
              logicalparent = constructs[parent_index]->GetLogicalVol();
            } else {
              G4cerr << "no parents !" << G4endl;
            }

          } else if (i == 1) {
            GetDoubleFromNode(child, __size);
          } else if (i == 2) {
            GetDoubleFromNode(child, __pos);
          } else if (i == 3) {
            GetDoubleFromNode(child, __angle);
          } else if (i == 4) {
            colorname = child->GetText();
          }
        }
      }
    }
  }
  BaseTubs *outputobj;
  cout << "tubs (type, dia, thickness, angle) : (" << attrvalue[1] << ", "
       << __size[0] << ", " << __size[1] << ", " << __angle << ")" << endl;
  if (worldflag) {
    outputobj = new BaseTubs(attrvalue[0], __id[0], attrvalue[1], __size, __pos,
                             __angle, colorname);
  } else {
    outputobj = new BaseTubs(logicalparent, attrvalue[0], __id[0], attrvalue[1],
                             __size, __pos, __angle, colorname);
  }
  outputobj->Initialize(material, visatt);
  outputobj->SetGeometry();
  cout << endl;
  return outputobj;
}

Mesh *XMLParamParser::ParseMesh(TXMLNode *_node) {
  TString node_name, parent_name, colorname;
  std::vector<int> __id(1);
  G4double __angle = 0., __pitch = 0.;
  G4ThreeVector __size, __pos;
  bool consistent = false;
  std::vector<TString> attrnames = {"name", "type", "ID"};
  std::vector<TString> attrvalue;
  GetStringFromAttribute(_node, attrnames, attrvalue);
  if (attrvalue.size() == attrnames.size()) {
    __id[0] = attrvalue[2].Atoi();
  }
  construct_names.emplace_back(attrvalue[0]);
  int n_node = mesh_node.size();
  int parent_index = 0;
  G4LogicalVolume *logicalparent;
  TXMLNode *child = _node->GetChildren();
  for (; child; child = child->GetNextNode()) {
    if (judgeElementNode(child)) {
      node_name = TString(child->GetNodeName());
      for (int i = 0; i < n_node; ++i) {
        consistent = node_name.Contains(mesh_node[i]);
        if (consistent) {
          if (i == 0) {
            parent_name = child->GetText();
            auto itr = std::find(construct_names.begin(), construct_names.end(),
                                 parent_name);
            if (itr != construct_names.end()) {
              parent_index = std::distance(construct_names.begin(), itr);
              logicalparent = constructs[parent_index]->GetLogicalVol();
            } else {
              G4cerr << "no parents !" << G4endl;
            }
          } else if (i == 1) {
            GetDoubleFromNode(child, __size);
          } else if (i == 2) {
            GetDoubleFromNode(child, __size[2]);
          } else if (i == 3) {
            GetDoubleFromNode(child, __pos);
          } else if (i == 4) {
            GetDoubleFromNode(child, __angle);
          } else if (i == 5) {
            colorname = child->GetText();
          }
        }
      }
    }
  }
  Mesh *outputobj;
  cout << "mesh (type, dia, length, pitch, angle) : (" << attrvalue[1] << ", "
       << __size[0] << ", " << __size[1] << ", " << __size[2] << ", " << __angle
       << ")" << endl;

  outputobj = new Mesh(logicalparent, attrvalue[0], __id[0], attrvalue[1],
                       __size, __pos, __angle, colorname);
  outputobj->Initialize(material, visatt);
  outputobj->SetGeometry();
  cout << endl;
  return outputobj;
}

TString XMLParamParser::GetXMLBaseName() { return xml_base_name; }

TString XMLParamParser::GetFileBaseName() { return file_base_name; }