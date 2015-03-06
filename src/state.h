#ifndef STATE_H
#define STATE_H

#include <set>

#include "utils.h"
#include "corpus.h"
#include "stirln.h"

using namespace std;

#define INIT_SIZE 100
#define LAZY_CHECK 5000
#define TOPIC_THRESHOLD 1.95

struct WordInfo {
public:
  long word_;
  long count_;
  long topic_assignment_;
};

class DocState {
public:
  long doc_id_;
  WordInfo* words_;
  long doc_length_;
public:
  DocState();
  ~DocState();
public:
 void setup_state_from_doc(const Document* doc); 
};

class HDPState {
public:
  HDPState();
  ~HDPState();
  void init_hdp_state(double eta, double gamma, double alpha, long size_vocab);
  void copy_hdp_state(const HDPState& src_state);
  void compact_hdp_state(vct_long* k_to_new_k);
  void save_hdp_state(const char* name);
  void load_hdp_state(const char* name);
public:
  vector<long* > topic_lambda_; // Not counting the prior, eta
  vct_long word_counts_by_topic_;
  vct_long beta_u_; // Not counting the prior 1.0
  //vct beta_v_; // Not counting the piror gamma
  vct pi_;     // A sample of pi.
  double pi_left_;

  // Hyper parameters
  double eta_;
  double gamma_;
  double alpha_; 

  long num_topics_;
  long size_vocab_;
};

class HDP {
public: // Not fixed.
  long num_docs_;
  DocState** doc_states_;
  
  vector<long*> word_counts_by_topic_doc_;  // Number of words by topic, doc
  vector<long*> table_counts_by_topic_doc_; // Number of tables by topic, doc.

  HDPState* hdp_state_;

  // For fast Gibbs sampling using Mimno's trick.
  vector<set<long> > unique_topic_by_word_;
  vector<set<long> > unique_topic_by_doc_;
  vct smoothing_prob_;
  double smoothing_prob_sum_;
  vector<double* > doc_prob_;
  vct doc_prob_sum_;

public:
  Stirling stirling_;

public:
  HDP();
  ~HDP();
  
  void init_hdp(double eta, double gamma, double alpha, long size_vocab);
  void setup_doc_states(const vector<Document* >& docs);
  void remove_doc_states();

  void compact_hdp_state();

  long iterate_gibbs_state(bool remove, bool permute);
  long  sample_word_assignment(DocState* doc_state, long i, bool remove, vct* p);
  void doc_state_update(DocState* doc_state, long i, long update);
  void sample_table_counts(DocState* doc_state, vct* p);
  void sample_top_level_proportions();

  double log_likelihood(const HDPState* old_hdp_state = NULL);
  void save_state(const char* name);
  void load_state(const char* name);
  void hyper_inference(double gamma_a, double gamma_b, double alpha_a, double alpha_b);

  void init_fast_gibbs_sampling_variables();
  void save_doc_states(const char* name); 
  void sample_first_level_concentration(double gamma_a, double gamma_b);
  void sample_second_level_concentration(double alpha_a, double alpha_b);
};

#endif // STATE_H
