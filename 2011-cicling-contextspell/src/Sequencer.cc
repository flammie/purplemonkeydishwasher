#include "Sequencer.h"

#include "StreamFieldInverter.h"
#include "LogSequenceWeightTable.h"
#include "IdentityTransformer.h"
#include "LexiconDivisorTransformer.h"
#include "ToEmptyStringTransformer.h"
#include "TrieBuilder.h"
#include "StreamTokenizer.h"

#define UNKNOWN_TAG "<?>"

using hfst::TROPICAL_OPENFST_TYPE;
using hfst::internal_identity;
using hfst::internal_epsilon;
using hfst::internal_unknown;
using hfst::implementations::HfstBasicTransition;
using hfst::implementations::ComposeIntersectLexicon;

std::istringstream in("||\t||");

HfstTransducer remove_letters(HfstTransducer &model)
{
  HfstBasicTransducer basic(model);
  HfstBasicTransducer basic_wo_letters;

  HfstState s = 0;

  for (HfstBasicTransducer::const_iterator it = basic.begin();
       it != basic.end();
       ++it)
    {
      const HfstBasicTransducer::HfstTransitions &transitions = *it;
      for (HfstBasicTransducer::HfstTransitions::const_iterator jt = 
	     transitions.begin();
	   jt != transitions.end();
	   ++jt)
	{
	  HfstBasicTransition transition
	    (jt->get_target_state(),
	     jt->get_input_symbol(),
	     (jt->get_input_symbol() != internal_epsilon 
	      ? 
	      internal_epsilon 
	      :
	      jt->get_output_symbol()),
	     jt->get_weight());

	  basic_wo_letters.add_transition(s,transition);
	}

      if (basic.is_final_state(s))
	{ basic_wo_letters.set_final_weight(s,basic.get_final_weight(s)); }

      ++s;
    }
  return HfstTransducer(basic_wo_letters,TROPICAL_OPENFST_TYPE);
}

HfstTransducer add_dummy_letter(HfstTransducer &model)
{ 
  HfstBasicTransducer basic(model);
  HfstBasicTransducer basic_with_dummy_letters;
  (void)basic_with_dummy_letters.add_state(basic.get_max_state());
  
  HfstState s = 0;

  for (HfstBasicTransducer::const_iterator it = basic.begin();
       it != basic.end();
       ++it)
    {
      const HfstBasicTransducer::HfstTransitions &transitions = *it;
      for (HfstBasicTransducer::HfstTransitions::const_iterator jt = 
	     transitions.begin();
	   jt != transitions.end();
	   ++jt)
	{
	  HfstState source = s;

	  if (jt->get_input_symbol() == internal_epsilon)
	    {
	      HfstState intermediate_target = 
		basic_with_dummy_letters.add_state();
	      
	      HfstBasicTransition dummy_letter_transition(intermediate_target,
							  internal_epsilon,
							  "<L>",
							  0.0);
	      basic_with_dummy_letters.add_transition
		(source,dummy_letter_transition);
	      source = intermediate_target;
	    }

	  HfstState target = jt->get_target_state();

	  HfstBasicTransition transition(target,
					 jt->get_input_symbol(),
					 jt->get_output_symbol(),
					 jt->get_weight());
	  
	  basic_with_dummy_letters.add_transition
	    (source,transition);
	}

      if (basic.is_final_state(s))
	{ basic_with_dummy_letters.set_final_weight
	    (s,basic.get_final_weight(s)); }

      ++s;
    }
  return HfstTransducer(basic_with_dummy_letters,
			TROPICAL_OPENFST_TYPE).minimize();
}

Sequencer::Sequencer(StreamReinitializer stream_reinitializer,
		     std::string name):
  LexicalModel(in,name)
{
  model.convert(TROPICAL_OPENFST_TYPE);
  
  LogSequenceWeightTable morpheme_table
    (IdentityTransformer(),
     ToEmptyStringTransformer(),
     StreamTokenizer(stream_reinitializer.get_stream()).get_stream());
  
  TrieBuilder morphemes(morpheme_table);
  
  model = morphemes.get_model();
  
  float penalty_weight = morpheme_table.get_penalty_weight();
  
  HfstTransducer unknown(TROPICAL_OPENFST_TYPE);
  HfstTransducer a("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer b("b",TROPICAL_OPENFST_TYPE);
  HfstTransducer c("c",TROPICAL_OPENFST_TYPE);
  HfstTransducer d("d",TROPICAL_OPENFST_TYPE);
  HfstTransducer e("e",TROPICAL_OPENFST_TYPE);
  HfstTransducer f("f",TROPICAL_OPENFST_TYPE);
  HfstTransducer g("g",TROPICAL_OPENFST_TYPE);
  HfstTransducer h("h",TROPICAL_OPENFST_TYPE);
  HfstTransducer i("i",TROPICAL_OPENFST_TYPE);
  HfstTransducer j("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer k("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer l("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer m("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer n("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer o("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer p("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer q("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer r("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer s("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer t("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer u("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer v("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer w("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer x("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer y("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer z("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer aa("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer ae("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer oe("a",TROPICAL_OPENFST_TYPE);

  unknown.disjunct(a).disjunct(b).disjunct(c).disjunct(d).disjunct(e).disjunct(f).disjunct(g).disjunct(h).disjunct(i).disjunct(j).disjunct(k).disjunct(l).disjunct(m).disjunct(n).disjunct(o).disjunct(p).disjunct(q).disjunct(r).disjunct(s).disjunct(t).disjunct(u).disjunct(v).disjunct(w).disjunct(x).disjunct(y).disjunct(z).disjunct(oe).disjunct(ae).disjunct(aa).minimize();

  HfstTransducer unknown_tag
    (internal_epsilon,UNKNOWN_TAG,TROPICAL_OPENFST_TYPE);
  unknown.concatenate(unknown_tag).minimize();
  unknown.set_final_weights(penalty_weight);
  
  model.disjunct(unknown).minimize();
  
  model = remove_letters(model);
  model = add_dummy_letter(model);

  /*
  HfstTransducer number(TROPICAL_OPENFST_TYPE);
  HfstTransducer one("1",TROPICAL_OPENFST_TYPE);
  HfstTransducer two("2",TROPICAL_OPENFST_TYPE);
  HfstTransducer three("3",TROPICAL_OPENFST_TYPE);
  HfstTransducer four("4",TROPICAL_OPENFST_TYPE);
  HfstTransducer five("5",TROPICAL_OPENFST_TYPE);
  HfstTransducer six("6",TROPICAL_OPENFST_TYPE);
  HfstTransducer seven("7",TROPICAL_OPENFST_TYPE);
  HfstTransducer eight("8",TROPICAL_OPENFST_TYPE);
  HfstTransducer nine("9",TROPICAL_OPENFST_TYPE);
  HfstTransducer zero("0",TROPICAL_OPENFST_TYPE);
  number.disjunct(one).disjunct(two).disjunct(three).disjunct(four).disjunct(five).disjunct(six).disjunct(seven).disjunct(eight).disjunct(nine).disjunct(zero).minimize();
  */
  
  HfstTransducer def("<DEFAULT>",internal_epsilon,TROPICAL_OPENFST_TYPE);

  model.insert_freely(def);

  HfstTransducer border("||",TROPICAL_OPENFST_TYPE);
  border.concatenate(border);
  model.disjunct(border).minimize();

  model.repeat_star().minimize();

}

Sequencer::Sequencer(const std::string filename):
  LexicalModel(filename,false),
  sequencer(model)
{}

HfstTransducer &Sequencer::operator[](HfstTransducer &fst)
{ 
  ComposeIntersectLexicon fst_lex(fst);
  HfstBasicTransducer res = fst_lex.compose_with_rules(&sequencer);
  fst = HfstTransducer(res,TROPICAL_OPENFST_TYPE);
  fst.minimize();
  return fst;
  //  return fst.compose(model).minimize(); 
}

void Sequencer::smoothe_tag_probabilities
(const WeightStringVectorVector &prefix_tag_probabilities,
 WeightStringVector &tag_probabilities)
{
  (void)prefix_tag_probabilities;
  (void)tag_probabilities;
  return;
}

#ifdef HFST_TAGGER_TEST_Sequencer
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "\t";

  // Unit test begins.

  const char * input_data =
    "man\t<man>\n"
    "man\t<man>\n"
    "nam\t<nam>\n"
    "can\t<can>\n"
    "ma\t<ma>\n";

  std::istringstream in(input_data);

  Sequencer sequencer(in,"");
  
  HfstTokenizer tokenizer;
  HfstTransducer man_can("mancan",tokenizer,TROPICAL_OPENFST_TYPE); 
  sequencer[man_can];

  std::cerr << man_can.minimize() << std::endl;
  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_Sequencer
