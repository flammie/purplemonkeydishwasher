#ifndef HFST_TAGGER_HEADER_LANGUAGE_MODEL_H
#define HFST_TAGGER_HEADER_LANGUAGE_MODEL_H

#include <hfst/HfstTransducer.h>

using hfst::HfstInputStream;
using hfst::HfstOutputStream;
using hfst::HfstTransducer;
using hfst::HFST_OLW_TYPE;

#define TAGGER_NAME_PREFIX "HFST-TAGGER:"

class LanguageModel
{
 public:
  class NotTaggerStream
  {};

 protected:
  static HfstTransducer read_fst(const std::string &filename);
  static void write_fst(HfstTransducer &fst,const std::string &filename);
};

#endif // HFST_TAGGER_HEADER_LANGUAGE_MODEL_H
