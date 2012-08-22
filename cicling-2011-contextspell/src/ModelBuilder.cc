#include "ModelBuilder.h"

using hfst::implementations::HfstBasicTransition;

ModelBuilder::ModelBuilder(ImplementationType type,float default_final_weight):
  type(type),
  default_final_weight(default_final_weight)
{}

HfstTransducer ModelBuilder::get_model(void)
{ return HfstTransducer(model_fst,type); }

void ModelBuilder::add_transition
(HfstState initial_state,
 HfstState target_state,
 const std::string &symbol,
 float weight)
{ model_fst.add_transition(initial_state,
			   HfstBasicTransition
			   (target_state,symbol,symbol,weight)); }

void ModelBuilder::add_transition
(HfstState initial_state,
 HfstState target_state,
 const std::string &isymbol,
 const std::string &osymbol,
 float weight)
{ model_fst.add_transition(initial_state,
			   HfstBasicTransition
			   (target_state,isymbol,osymbol,weight)); }

HfstState ModelBuilder::get_target(HfstState s,
				   const std::string &symbol,
				   bool &new_transition_required)
{
  HfstState target = NO_STATE;

  if (s == START_STATE)
    {
      if (start_state_targets.count(symbol) == 0)
	{
	  target = model_fst.add_state();
	  start_state_targets[symbol] = target;
	  new_transition_required = true;
	}
      else
	{ 
	  target = start_state_targets[symbol]; 
	  new_transition_required = false;
	} 
    }
  else
    {
      const HfstBasicTransducer::HfstTransitions &transitions = model_fst[s];

      for (HfstBasicTransducer::HfstTransitions::const_iterator it = 
	     transitions.begin();
	   it != transitions.end();
	   ++it)
	{
	  if (it->get_input_symbol() == symbol)
	    {
	      target = it->get_target_state();	      
	      break;
	    }
	}

      if (target == NO_STATE)
	{ 
	  target = model_fst.add_state(); 
	  new_transition_required = true;
	}
      else
	{ new_transition_required = false; }
    }

  model_fst.set_final_weight(target,default_final_weight);  
  return target;
}

ModelBuilder::StringVector ModelBuilder::split_at_tabs(const std::string &str)
{
  StringVector result;
  
  size_t beg_pos = 0;
  size_t end_pos = std::string::npos;
  
  do
    {
      beg_pos = end_pos + 1;
      end_pos = str.find('\t',beg_pos);
      std::string token = str.substr(beg_pos,end_pos - beg_pos);
      result.push_back(token);
    } 
  while (end_pos != std::string::npos);
  
  return result;
}

HfstState ModelBuilder::add_sequence
(ModelBuilder::StringVector::const_iterator it,
 ModelBuilder::StringVector::const_iterator end)
{
  HfstState initial_state = START_STATE;
  HfstState target_state  = NO_STATE;

  bool new_transition_required = false;

    for ( ; it != end; ++it)
    {
      target_state = get_target(initial_state,
				*it,
				new_transition_required); 
      
      if (new_transition_required)
	{ add_transition(initial_state,target_state,*it,0.0); }

      new_transition_required = false;

      initial_state = target_state;
    }

    return target_state;
}

#ifdef HFST_TAGGER_TEST_ModelBuilder
#include <cassert>
#include <iostream>
int main(void)
{
  std::cerr << "Unit test for: " << __FILE__ << "   \t";

  // Unit test begins.

  

  // Unit test ends.

  std::cerr << "PASSED" << std::endl;
}
#endif // HFST_TAGGER_TEST_ModelBuilder
