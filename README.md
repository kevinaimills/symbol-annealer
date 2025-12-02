# Symbol Annealer

> **Context:** This codebase is a snapshot from October 2023. It is a fork of Michael Dickens' keyboard layout optimizer that I significantly re-engineered to help overcome a health crisis that greatly limited the use of my voice and hands. I relied extensively on an eye-tracker to write the code, and it has many artifacts that reveal its origins. It is presented here in the original, unpolished form that generated the layout I now type on and that helped me regain the use of my hands.

## Project Overview

Typing (both code and natural language) exhibits predictable statistical patterns. Layout optimizers map these patterns onto keyboard layouts in ways that (ideally) maximize comfortable, low-work movements and minimize the opposite. Unfortunately, typing comfort exhibits considerable variability, and what's comfortable for one person can be painful for another. As I could not find an existing layout that adequately conformed to the constraints of my hands, I felt compelled to make my own.

**Symbol Annealer** operationalizes typing ergonomics with a sophisticated model of typing work and comfort. It uses a parallel simulated-annealing algorithm to find the optimal mapping of statistical typing data onto this model. Distinctively, it includes a "cognitive overhead"/"aesthetics" component that ensures symbols are placed in intuitive, easy-to-remember locations (since an undifferentiated mess of symbols is not a good layout regardless of physical optimality).

## Key Changes

### 1\. Core Algorithm (file: `cjalgorithm.c`)

The original simulated annealing algorithm used parallel processing (via Pthreads) to alternate between optimizing random layouts and iteratively improving the single best layout. This was highly vulnerable to local minima and often required restarting the algorithm to escape. I refactored the algorithm to maintain a leaderboard of top layouts that are improved in parallel.

  * **Parallel Optimization:** Threads now probabilistically select layouts to work on from either: (i) the leaderboard; (ii) a semi-random "warm start" (see **Warm Start**, below); (iii) a purely random layout.
  * **Equivalence Checks:** The leaderboard intelligently merges functionally-equivalent entries to avoid pollution by minor variations on what is effectively the same layout (e.g. layouts differing only in that they swap the locations of two low-frequency symbols).
  * **Diversity and Stagnation:** Underperforming and non-improving layouts are periodically purged from the leaderboard to facilitate diversity.
  * **Memory Safety:** Avoids race conditions and memory corruption by giving each thread its own copy of the leaderboard to work on; the threads terminate after a fixed number of cycles, merge their leaderboards, and then spawn new threads with updated information (I inherited this basic architecture from Michael Dickens).

**Example contributions:** `purgeOutdatedKeyboards`; `selectNextKeyboard`; various changes to `runAlgorithm` and the functions it calls.

### 2\. Fitness Function (file: `fitness.c`)

  * **Trigram Data:** Updated the fitness function to use trigrams (statistical data about 3-character sequences) in addition to bigrams (see also: **Data Pipeline**). This is important because some (un)ergonomic patterns are invisible at the bigram level (e.g. a "split same-finger bigram", where one finger has to jump around to hit two keys even though there is another key interspersed between them. This isn't as bad as where no key is interspersed between them, but also isn't ideal).
  * **Granularity and Abstraction:** The typing comfort model was almost entirely rewritten. Most of the popular abstractions proved insufficiently granular for my use case (consider e.g. "scissors", where one finger flexes and the other extends for a bigram that spans the top and bottom rows. This feels *very* different depending on which fingers are involved). My solution was to (nearly) exhaustively map bigram key transitions for one half of the core 30 keys and assume symmetry for the other half (an example mapping: pressing upper-row pinky and then bottom-row ring in succession is particularly uncomfortable and heavily penalized for common bigrams). The search space was small enough to make this approach viable, and I am convinced abstraction is actually not a virtue here, because it doesn't respect the granularity of the problem space. I retained the category labels for organization, but the penalties depend on the specific fingers involved; see e.g. `calcHalfScissor`, `calcLateralStretch`.
  * **Cognitive Load Modeling:** I added "aesthetics" penalties to the fitness function to incentivize symbol layouts that can be learned efficiently. For example, layouts are penalized heavily if bracket pairs, e.g. `()` and `[]`, do not stand in consistent spatial relations to one another. For example, if `(` and `)` are vertically staggered and facing one another, then all bracket pairs must follow this logic (with some allowances for mirror images on opposite hands). Many of these penalties are so steep that they function as hard constraints, so while a layout might violate them early in its evolutionary history, it is extremely unlikely to do so by the time it hits the leaderboard (as a result, the aesthetics penalty for keyboards on the leaderboard is typically 0; this is just right, because again, I do not want to try and learn an undifferentiated mess of symbols). See e.g. `sameRelation`; `calcAesthetics`.
  * **Layer Transitions:** Since I implemented a symbol layer (see **Dimensionality**, below), I had to penalize layouts that do not use it ergonomically. In particular, tapping (or holding) the layer-access key is not ergonomically free, and context switching (transitioning between layers) within a single word or "symbol chain" is disruptive both cognitively and physically. So, the fitness function incentivizes putting lower-priority keys on the symbol layer, and tries to put common bigrams and trigrams on the same layer to reduce transitions between them. (See e.g. `calcBiLayerChange`)

### 3\. Keyboard Scaffolding / Initial Layout Seed (file: `keyboard.c`)

  * **Warm Start:** New keyboards (i.e. those not already in the leaderboard) are no longer always initialized randomly; 50% of the time, they receive a "warm start" by forcing the home row to contain 8 of the 16 most common characters. (Both a priori and based on observation, layouts that violate this constraint are not serious contenders for the leaderboard.) See: `forcePlausibleHomerow`.
  * **Dimensionality:** Re-architectured the keyboard data structure to include a symbol "layer" (essentially, a higher dimensional space that maps symbols to letter keys when a modifier is pressed). This is a now-standard solution that allows the most ergonomic keys and patterns to be reused for symbols (see e.g. `setLayout`).

### 4\. Data Pipeline (files: `datagen/merge.pl`, `datagen/process.pl`)

A layout optimizer is only as good as the data it infers statistical typing patterns from. I made several changes to the data pipeline:

  * **Letter Data:** I updated the English character data to use Peter Norvig's dataset; this was extracted from Google Books, and I regard it as the best available data source at the moment.
  * **Symbol Data:** I curated a dataset of code examples from books and Github repositories I regard as high-quality and/or similar to my own style. I cleaned the data in various ways (see e.g. `filterASCIIArt` in `process.pl`) and then extracted the relevant statistical data for the model.
  * **Synthetic Data:** The popularity of snake\_case (e.g. in Python) has surprising ergonomic implications. This convention effectively turns underscore into a secondary spacebar. Since spacebar is the highest-frequency key in typing, this essentially forces underscore (a symbol that could otherwise be relegated to the periphery) onto the home row of the symbol layer. It also has implications for data sources: corpus data for `_` is highly sensitive to the specific variable naming conventions of the source (which seriously risks overfitting). So, I synthesized artificial bigram data for `_` using the Norvig dataset, to model the probability of it being used as a space between arbitrary English words (See the `if ($constructSnakeCaseData)` block in `merge.pl`).
  * **Data Scaling:** Code data is normalized (since languages are not equally represented in the corpus), and the user can specify how heavily to weight any individual language (e.g. one could set Python and Rust to 50 and everything else to 0; but of course, this would produce an overfitted layout that would not generalize well to other languages). See e.g. the `%languageScales` hash in `merge.pl`.

## Results

Here is the layout my optimizer generated, and that I now type on. Note that a "0" in the layout is an unbound key that can be bound to hotkeys, etc.

```text
Rank #1 (fitness: 128686029)
Hands:   48.05% 51.95%
Fingers: 7.7% 8.9% 12.1% 19.3%   12.6% 19.9% 10.6% 8.7%
Travel:  0.3% 3.7% 5.8%  10.0%    6.4%  8.2%  3.7%  0.9%

 Q  Y  M  P  B   J  W  O  U  0
 N  H  S  T  G   K  R  E  I  A
 X  F  C  D  V   Z  L  \  %  0

 q  y  m  p  b   j  w  o  u  .
 n  h  s  t  g   k  r  e  i  a
 x  f  c  d  v   z  l  '  ,  @

 0  -  =  &  +   ~  |  /  ?  0
 _  (  )  "  *   $  :  >  <  ;
 ^  #  {  }  0   `  ]  [  !  0

Fitness (-aesthetics):  128686029 (128686029)
Finger travel:          51028900
Excess finger press:    802135
Excess finger travel:   1005600
Hand travel:            19589240
Hand imbalance:         463933
Aesthetics:             0
Layer change:           20429440
(Bigram) layer, diff:       5.12% (-2940320)
(Bigram) layer, diff hands: 1.02% (1019840)
(Bigram) rolls, separated   13.83% (-866680)
(Bigram) rolls, consec:     7.92% (-496390)
(Bigram) same hand:         39.26% (0)
(Bigram) same finger:       1.22% (13492160)
(Bigram) sfb above max:     1.22% (0)
(Bigram) same row:          2.03% (-164470)
(Bigram) double tap:        0.27% (1975800)
(Bigram) scissors, half:    12.99% (10689640)
(Bigram) scissors, full:    1.45% (2892480)
(Bigram) lat stretch:       0.96% (1522640)
(Trigram) same finger, split:   1.76% (2578000)
(Trigram) same row, split:      1.03% (-49950)
(Trigram) rolls:                57.18% (-2384420)
(Trigram) alternates:           30.84% (-128608)
(Trigram) bad redirects:        4.59% (1530880)
(Trigram) scissors, one hand:   0.42% (79384)
(Trigram) scissors, half split: 6.58% (1891146)
(Trigram) scissors, full split: 1.93% (4436640)
(Trigram) lat stretch, split:   0.54% (289009)
```
