# Hierarchical Dirichlet Process

Hierarchical Dirichlet Process in C++, originally written by Chong Wang and David Blei, and slightly modified by Henri Dwyer. 

The original can be downloaded here: [original hdp](http://www.cs.cmu.edu/~chongw/software/hdp.tar.gz) (hdp-faster)

The changes are that the library now works with corpuses larger than 32767, and saves the document states.

# Compiling

Type "make" in a shell. Make sure the GSL is installed. You may need to change the Makefile a bit.

# Posterior Inference

The following shows an example of performing posterior inference on a set of documents:

```hdp --train_data data --directory output```


## Parameters

The meaning of the parameters is the same as in the in the following paper:

[Y. Teh, M. Jordan, M. Beal, and D. Blei. Hierarchical Dirichlet processes.
Journal of the American Statistical Association, 2006. 101[476]:1566-1581](http://www.stat.berkeley.edu/~aldous/206-Exch/Papers/hierarchical_dirichlet.pdf)

      usage:
      hdp               [options]
      --help:           print help information.
      --verbose:        print running information.

      control parameters:
      --directory:       the saving directory, required.
      --random_seed:     the random seed, default from the current time.
      --max_iter:        the max number of iterations, default 100 (-1 means infinite).
      --max_time:        the max time allowed (in seconds), default 1800 (-1 means infinite).
      --save_lag:        the saving point, default 5.

      data parameters:
      --train_data:      the training data file/pattern, in lda-c format.

      model parameters:
      --eta:             the topic Dirichlet parameter, default 0.05.
      --gamma:           the first-level concentration parameter in hdp, default 1.0.
      --alpha:           the second-level concentration parameter in hdp, default 1.0.
      --gamma_a:        shape for 1st-level concentration parameter, default 1.0.
      --gamma_b:        scale for 1st-level concentration parameter, default 1.0.
      --alpha_a:        shape for 2nd-level concentration parameter, default 1.0.
      --alpha_b:        scale for 2nd-level concentration parameter, default 1.0.
      --sample_hyper:   sample 1st and 2nd-level concentration parameter, default false

      test only parameters:
      --test_data:       the test data file/pattern, in lda-c format.
      --model_prefix:    the model_prefix.

## Data Format 

--data points to a file where each line is of the form (the LDA-C format):

     [M] [term_1]:[count] [term_2]:[count] ...  [term_N]:[count]

where [M] is the number of unique terms in the document, and the [count] associated with each term is how many times that term appeared in the document. 


## Output

The sampler will produce 6 files in the --directory. For the topics, 3 are important:

- counts: the number words in each topic. 1 line per topic.

- topics: how many times each word is in each topic. 1 line per topic, each line a space separated list of word counts.

- doc_states: topics counts in each document. 1 line per topic, each line a space separated list of topic counts.

# Example

For an example on how to analyze the output in python, see this ipython notebooks:

- [Topic Modeling.ipynb](http://henri.io/posts/topic modeling.ipynb) - ([on github](http://github.com/henridwyer/company-reviews/topic modeling.ipynb))

# License

hdp is free software; you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation;
either version 2 of the License, or (at your option) any later version.

hdp is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA
