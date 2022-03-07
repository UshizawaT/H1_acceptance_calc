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
        XMLScintillator *tmp_scinti = 0;
        LeadBlock *tmp_pbblock = 0;
        _n_target = 0;
        for (; child; child = child->GetNextNode()) {
          if (child->GetNodeType() == TXMLNode::kXMLElementNode) {
            // cout << "child name : " << child->GetNodeName() << endl;
            if (std::strcmp(child->GetNodeName(), "filename") == 0) {
              file_base_name = child->GetText();
            } else if (std::strcmp(child->GetNodeName(), "beam") == 0) {
              _beam = ParseBeam(child);
            } else if (std::strcmp(child->GetNodeName(), "target") == 0) {
              _exist_target = true;
              _n_target += 1;
              _stopping_tgt = ParseTarget(child);
              if (_n_target > 1) _stopping_tgt2 = ParseTarget(child);
            } else if (std::strcmp(child->GetNodeName(), "mesh") == 0) {
              _exist_mesh = true;
              _mesh = ParseMesh(child);
            } else if (std::strcmp(child->GetNodeName(), "pb_block") == 0) {
              _exist_pbblocks = true;
              tmp_pbblock = ParsePbBlock(child);
              _pb_blocks->Add(tmp_pbblock);
            } else if (std::strcmp(child->GetNodeName(), "scintillator") == 0) {
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
  cout << "N scinti : " << _scinti_num << endl;
  cout << "scinti group : " << _scinti_group_num << endl;
}

Beam *XMLParamParser::ParseBeam(TXMLNode *_child) {
  TString __beamtype = "mu+";
  double __hsize = 0., __vsize = 0., __angle = 0., __mom = 0., __pp;
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
      } else if (std::strcmp(attr->GetName(), "momentum") == 0) {
        __mom = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "mom_dist") == 0) {
        __pp = TString(attr->GetValue()).Atof();
      }
    }
  }
  cout << "beam (type, hsize, vsize, spread_angle) : (" << __beamtype << ", "
       << __hsize << ", " << __vsize << ", " << __angle << ")" << endl;
  return new Beam(__beamtype, __hsize, __vsize, __angle, __mom, __pp);
}

StoppingTarget *XMLParamParser::ParseTarget(TXMLNode *_child) {
  TString __material = "Fe";
  double __angle = 0., __thickness = 0., __hsize = 0., __vsize = 0.;
  if (_child->HasAttributes()) {
    TList *att_list = _child->GetAttributes();
    TXMLAttr *attr = 0;
    TIter next(att_list);
    while ((attr = (TXMLAttr *)next())) {
      if (std::strcmp(attr->GetName(), "type") == 0) {
        __material = TString(attr->GetValue());
      } else if (std::strcmp(attr->GetName(), "angle") == 0) {
        __angle = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "thickness") == 0) {
        __thickness = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "hsize") == 0) {
        __hsize = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "vsize") == 0) {
        __vsize = TString(attr->GetValue()).Atof();
      }
    }
  }
  cout << "stopping target (material, thickness, angle) : (" << __material
       << ", " << __thickness << ", " << __angle << ")" << endl;
  return new StoppingTarget(__material, __thickness, __hsize, __vsize, __angle);
}

Mesh *XMLParamParser::ParseMesh(TXMLNode *_child) {
  TString __material = "SUS304";
  double __dia = 0., __len = 0., __pitch = 0.;
  if (_child->HasAttributes()) {
    TList *att_list = _child->GetAttributes();
    TXMLAttr *attr = 0;
    TIter next(att_list);
    while ((attr = (TXMLAttr *)next())) {
      if (std::strcmp(attr->GetName(), "type") == 0) {
        __material = TString(attr->GetValue());
      } else if (std::strcmp(attr->GetName(), "wire_diameter") == 0) {
        __dia = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "length") == 0) {
        __len = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "pitch") == 0) {
        __pitch = TString(attr->GetValue()).Atof();
      }
    }
  }
  cout << "stopping target (material, wire_dia., length, pitch) : ("
       << __material << ", " << __dia << ", " << __len << "," << __pitch << ")"
       << endl;
  return new Mesh(__material, __dia, __len, __pitch);
}

LeadBlock *XMLParamParser::ParsePbBlock(TXMLNode *_child) {
  int __id = 0;
  double __xsize = 0., __ysize = 0., __zsize = 0., __xpos = 0., __ypos = 0.,
         __zpos = 0.;
  if (_child->HasAttributes()) {
    TList *att_list = _child->GetAttributes();
    TXMLAttr *attr = 0;
    TIter next(att_list);
    while ((attr = (TXMLAttr *)next())) {
      if (std::strcmp(attr->GetName(), "ID") == 0) {
        __id = TString(attr->GetValue()).Atoi();
      } else if (std::strcmp(attr->GetName(), "xsize") == 0) {
        __xsize = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "ysize") == 0) {
        __ysize = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "zsize") == 0) {
        __zsize = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "xpos") == 0) {
        __xpos = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "ypos") == 0) {
        __ypos = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "zpos") == 0) {
        __zpos = TString(attr->GetValue()).Atof();
      }
    }
  }
  return new LeadBlock(__id, __xsize, __ysize, __zsize, __xpos, __ypos, __zpos);
}

XMLScintillator *XMLParamParser::ParseScinti(TXMLNode *_child) {
  int __id = 0, __groupid = 0;
  double __hsize = 10., __vsize = 10., __thickness = 2., __xpos = 3000.,
         __ypos = 0.0, __zpos = 200., __angle = 0.;
  if (_child->HasAttributes()) {
    TList *att_list = _child->GetAttributes();
    TXMLAttr *attr = 0;
    TIter next(att_list);
    while ((attr = (TXMLAttr *)next())) {
      if (std::strcmp(attr->GetName(), "ID") == 0) {
        __id = TString(attr->GetValue()).Atoi();
      } else if (std::strcmp(attr->GetName(), "groupID") == 0) {
        __groupid = TString(attr->GetValue()).Atoi();
      } else if (std::strcmp(attr->GetName(), "hsize") == 0) {
        __hsize = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "vsize") == 0) {
        __vsize = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "thickness") == 0) {
        __thickness = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "angle") == 0) {
        __angle = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "xpos") == 0) {
        __xpos = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "ypos") == 0) {
        __ypos = TString(attr->GetValue()).Atof();
      } else if (std::strcmp(attr->GetName(), "zpos") == 0) {
        __zpos = TString(attr->GetValue()).Atof();
      }
    }
  }
  return new XMLScintillator(__id, __groupid, __hsize, __vsize, __thickness,
                             __angle, __xpos, __ypos, __zpos);
}

TString XMLParamParser::GetXMLBaseName() { return xml_base_name; }

TString XMLParamParser::GetFileBaseName() { return file_base_name; }