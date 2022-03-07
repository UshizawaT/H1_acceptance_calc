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
        int n_group = 0, __groupid = 0;
        ScintillatorObject *tmp_scinti = 0;
        LeadBlock *tmp_pbblock = 0;
        for (; child; child = child->GetNextNode()) {
          if (child->GetNodeType() == TXMLNode::kXMLElementNode) {
            // cout << "child name : " << child->GetNodeName() << endl;
            if (std::strcmp(child->GetNodeName(), nodenames[0]) == 0) {
              file_base_name = child->GetText();
            } else if (std::strcmp(child->GetNodeName(), nodenames[1]) == 0) {
              _beam = ParseBeam(child);
            } else if (std::strcmp(child->GetNodeName(), nodenames[2]) == 0) {
              _world = ParseWorld(child);
            } else if (std::strcmp(child->GetNodeName(), nodenames[3]) == 0) {
              _vacuum_volume = ParseVacuumV(child);
            } else if (std::strcmp(child->GetNodeName(), nodenames[4]) == 0) {
              _kapton_window = ParseKapton(child);
            } else if (std::strcmp(child->GetNodeName(), nodenames[5]) == 0) {
              _concrete_block = ParseShield(child);
            } else if (std::strcmp(child->GetNodeName(), nodenames[6]) == 0) {
              _exist_target = true;
              _stopping_tgt = ParseTarget(child);
            } else if (std::strcmp(child->GetNodeName(), nodenames[7]) == 0) {
              _exist_mesh = true;
              _mesh = ParseMesh(child);
            } else if (std::strcmp(child->GetNodeName(), nodenames[8]) == 0) {
              _exist_pbblocks = true;
              tmp_pbblock = ParsePbBlock(child);
              _pb_blocks->Add(tmp_pbblock);
            } else if (std::strcmp(child->GetNodeName(), nodenames[9]) == 0) {
              tmp_scinti = ParseScinti(child);
              _scintillators->Add(tmp_scinti);
              __groupid = tmp_scinti->GetScintiGroupId();
              n_group = __groupid > n_group ? __groupid : n_group;
            }
          }
        }
        _pb_block_num = _pb_blocks->GetSize();
        _scinti_num = _scintillators->GetSize();
        _scinti_group_num = n_group;
      }
    }
  }
  cout << "N pb_block : " << _pb_block_num << endl;
  cout << "N scinti : " << _scinti_num << endl;
  cout << "scinti group : " << _scinti_group_num << endl;
}

Beam *XMLParamParser::ParseBeam(TXMLNode *_child) {
  TString __beamtype = "mu+";
  double __hsize = 0., __vsize = 0., __angle = 0.;
  if (_child->HasAttributes()) {
    TList *att_list = _child->GetAttributes();
    TXMLAttr *attr = 0;
    TIter next(att_list);
    while ((attr = (TXMLAttr *)next())) {
      if (std::strcmp(attr->GetName(), "type") == 0) {
        __beamtype = TString(attr->GetValue());
      } else if (std::strcmp(attr->GetName(), "hsize") == 0) {
        __hsize = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "vsize") == 0) {
        __vsize = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "spread_angle") == 0) {
        __angle = TString(attr->GetValue()).Atof();
      }
    }
  }
  cout << "beam (type, hsize, vsize, spread_angle) : (" << __beamtype << ", "
       << __hsize << ", " << __vsize << ", " << __angle << ")" << endl;
  return new Beam(__beamtype, __hsize, __vsize, __angle);
}

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
}

DetectorWorld *XMLParamParser::ParseWorld(TXMLNode *_child) {
  std::vector<G4String> __strdata(2);
  std::vector<int> __ids(1);
  int n_attr = normalbox.size();
  std::vector<double> __numdata(n_attr - 3);
  G4ThreeVector __sizev, __pos;
  GetParams(_child, normalbox, __strdata, __ids, __numdata);
  cout << "world (material, thickness, angle) : (" << __strdata[1] << ", "
       << __numdata[2] << ", " << __numdata[6] << ")" << endl;
  __sizev = G4ThreeVector{__numdata[0], __numdata[1], __numdata[2]};
  __pos = G4ThreeVector{__numdata[3], __numdata[4], __numdata[5]};
  return new DetectorWorld(__strdata[0], __ids[0], __strdata[1], __sizev, __pos,
                           __numdata[6]);
}

VacuumVolume *XMLParamParser::ParseVacuumV(TXMLNode *_child) {
  std::vector<G4String> __strdata(2);
  std::vector<int> __ids(1);
  int n_attr = normalbox.size();
  std::vector<double> __numdata(n_attr - 3);
  G4ThreeVector __sizev, __pos;
  GetParams(_child, normalTubs, __strdata, __ids, __numdata);
  cout << "world (material, thickness, angle) : (" << __strdata[1] << ", "
       << __numdata[2] << ", " << __numdata[6] << ")" << endl;
  __sizev = G4ThreeVector{__numdata[0], __numdata[1], 0.};
  __pos = G4ThreeVector{__numdata[2], __numdata[3], __numdata[4]};
  return new VacuumVolume(__strdata[0], __ids[0], __strdata[1], __sizev, __pos,
                          __numdata[5]);
}

Kapton *XMLParamParser::ParseKapton(TXMLNode *_child) {
  std::vector<G4String> __strdata(2);
  std::vector<int> __ids(1);
  int n_attr = normalbox.size();
  std::vector<double> __numdata(n_attr - 3);
  G4ThreeVector __sizev, __pos;
  GetParams(_child, normalTubs, __strdata, __ids, __numdata);
  cout << "world (material, thickness, angle) : (" << __strdata[1] << ", "
       << __numdata[2] << ", " << __numdata[6] << ")" << endl;
  __sizev = G4ThreeVector{__numdata[0], __numdata[1], 0.};
  __pos = G4ThreeVector{__numdata[2], __numdata[3], __numdata[4]};
  return new Kapton(__strdata[0], __ids[0], __strdata[1], __sizev, __pos,
                    __numdata[5]);
}

Shield *XMLParamParser::ParseShield(TXMLNode *_child) {
  std::vector<G4String> __strdata(2);
  std::vector<int> __ids(1);
  int n_attr = normalbox.size();
  std::vector<double> __numdata(n_attr - 3);
  G4ThreeVector __sizev, __pos;
  GetParams(_child, normalbox, __strdata, __ids, __numdata);
  cout << "shield (material, thickness, angle) : (" << __strdata[1] << ", "
       << __numdata[2] << ", " << __numdata[6] << ")" << endl;
  __sizev = G4ThreeVector{__numdata[0], __numdata[1], __numdata[2]};
  __pos = G4ThreeVector{__numdata[3], __numdata[4], __numdata[5]};
  return new Shield(__strdata[0], __ids[0], __strdata[1], __sizev, __pos,
                    __numdata[6]);
}

StoppingTarget *XMLParamParser::ParseTarget(TXMLNode *_child) {
  // G4String __material = "Fe", __name;
  std::vector<G4String> __strdata(2);
  std::vector<int> __ids(1);
  int n_attr = normalbox.size();
  std::vector<double> __numdata(n_attr - 3);
  G4ThreeVector __sizev, __pos;
  GetParams(_child, normalbox, __strdata, __ids, __numdata);
  cout << "stopping target (material, thickness, angle) : (" << __strdata[1]
       << ", " << __numdata[2] << ", " << __numdata[6] << ")" << endl;
  __sizev = G4ThreeVector{__numdata[0], __numdata[1], __numdata[2]};
  __pos = G4ThreeVector{__numdata[3], __numdata[4], __numdata[5]};
  return new StoppingTarget(__strdata[0], __ids[0], __strdata[1], __sizev,
                            __pos, __numdata[6]);
}

Mesh *XMLParamParser::ParseMesh(TXMLNode *_child) {
  std::vector<G4String> __strdata(2);
  std::vector<int> __ids(1);
  int n_attr = mesh_node.size();
  std::vector<double> __numdata(n_attr - 3);
  G4ThreeVector __sizev, __pos;
  GetParams(_child, mesh_node, __strdata, __ids, __numdata);
  cout << "mesh (material, wire_dia., length, pitch) : (" << __strdata[1]
       << ", " << __numdata[0] << ", " << __numdata[1] << "," << __numdata[2]
       << ")" << endl;
  __sizev = G4ThreeVector{__numdata[0], __numdata[1], __numdata[2]};
  __pos = G4ThreeVector{__numdata[3], __numdata[4], __numdata[5]};
  return new Mesh(__strdata[0], __ids[0], __strdata[1], __sizev, __pos,
                  __numdata[6]);
}

LeadBlock *XMLParamParser::ParsePbBlock(TXMLNode *_child) {
  std::vector<G4String> __strdata(2);
  std::vector<int> __ids(1);
  int n_attr = mesh_node.size();
  std::vector<double> __numdata(n_attr - 3);
  G4ThreeVector __sizev, __pos;
  GetParams(_child, normalbox, __strdata, __ids, __numdata);
  cout << "LeadBlock size(s1, s2, s3) : (" << __strdata[1] << ", "
       << __numdata[0] << ", " << __numdata[1] << "," << __numdata[2] << ")"
       << endl;
  __sizev = G4ThreeVector{__numdata[0], __numdata[1], __numdata[2]};
  __pos = G4ThreeVector{__numdata[3], __numdata[4], __numdata[5]};
  return new LeadBlock(__strdata[0], __ids[0], __strdata[1], __sizev, __pos,
                       __numdata[6]);
}

ScintillatorObject *XMLParamParser::ParseScinti(TXMLNode *_child) {
  std::vector<G4String> __strdata(2);
  std::vector<int> __ids(2);
  int n_attr = mesh_node.size();
  std::vector<double> __numdata(n_attr - 4);
  G4ThreeVector __sizev, __pos;
  GetParams(_child, scinti_node, __strdata, __ids, __numdata);
  __sizev = G4ThreeVector{__numdata[0], __numdata[1], __numdata[2]};
  __pos = G4ThreeVector{__numdata[3], __numdata[4], __numdata[5]};
  cout << "Scinti. size(s1, s2, s3) : (" << __strdata[1] << ", " << __numdata[0]
       << ", " << __numdata[1] << "," << __numdata[2] << ")" << endl;
  return new ScintillatorObject(__strdata[0], __ids[0], __ids[1], __strdata[1],
                                __sizev, __pos, __numdata[6]);
}

TString XMLParamParser::GetXMLBaseName() { return xml_base_name; }

TString XMLParamParser::GetFileBaseName() { return file_base_name; }