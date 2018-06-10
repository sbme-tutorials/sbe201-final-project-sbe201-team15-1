# **Introduction**
* *Comparative Genomics :*
	Comparative genomics is a field of biological research in which the genomic features (the DNA sequence, genes, gene order..etc.) of different organisms are compared. In this branch of genomics, the comparison is used to study basic biological similarities and differences as well as evolutionary relationships between organisms. The major principle of comparative genomics is that common features of two organisms will often be encoded within the DNA that is evolutionarily conserved between them.Therefore, comparative genomic approaches start with making some form of alignment of genome sequences and looking for sequences that share a common ancestry in them and checking to what extent those sequences are conserved.
* *Evolutionary Principles :*
	When two or more of the genome sequence are compared, one can deduce the evolutionary relationships of the sequences in a phylogenetic tree (a branching tree showing the evolutionary relationships among various biological species based upon similarities and differences in their physical or genetic characteristics. All life on Earth is part of a single phylogenetic tree, indicating common ancestry). 
	Comparative genomics exploits both similarities and differences in the proteins, RNA, and regulatory regions of different organisms to infer how selection has acted upon these elements. Those elements that are responsible for similarities between different species should be conserved through time (stabilizing selection), while those elements responsible for differences among species should be divergent (positive selection). Finally, those elements that are unimportant to the evolutionary success of the organism will be unconserved (selection is neutral).

# **Sequence Alignment**

Sequence alignment is a way of arranging the sequences of DNA, RNA, or protein to identify regions of similarity that may be a consequence of functional, structural, or evolutionary relationships between the sequences.
![GitHub Logo](/alignment.png)

If two sequences in an alignment share a common ancestor, mismatches can be interpreted as point mutations and gaps as indels (that is, insertion or deletion mutations) introduced in one or both lineages in the time since they diverged from one another. 
Computational approaches to sequence alignment generally fall into two categories: global alignments and local alignments.

## Global & Local Alignments:

Global alignments, which attempt to align every residue in every sequence, are most useful when the sequences in the query set are similar and of roughly equal size. A general global alignment technique is the Needleman–Wunsch algorithm, which is based on dynamic programming. Local alignments are more useful for dissimilar sequences that are suspected to contain regions of similarity or similar sequence motifs within their larger sequence context. The Smith–Waterman algorithm is a general local alignment method also based on dynamic programming.

### Global Alignment (Needleman–Wunsch algorithm):
	
The algorithm essentially divides a large problem (e.g. the full sequence) into a series of smaller problems and uses the solutions to the smaller problems to reconstruct a solution to the larger problem. 
![GitHub Logo](/global.png)

The letters of the two strings may match, mismatch, or be matched to a gap (a deletion or insertion (indel)):
   1. Match: The two letters at the current index the same.
   2. Mismatch: The two letters at the current index are different.
   3. Indel (INsertion or DELetion): The best alignment involves one letter aligning to a gap in the other string.
Each of these scenarios is assigned a score and the sum of the score of each pairing is the score of the whole alignment candidate. 
To find the alignment with the highest score, a two-dimensional array (or matrix) F is allocated. The entry in row i and column j is denoted here by F(i,j). There is one row for each character in sequence A, and one column for each character in sequence B. 
The pseudo-code for the algorithm to compute the F matrix therefore looks like this:

* d ← MismatchScore
* for i=0 to length(A)
*  F(i,0) ← d*i 
* for j=0 to length(B)
*  F(0,j) ← d*j
* for i=1 to length(A)
*  for j=1 to length(B)
*  {
*    Match ← F(i-1,j-1) + S(Ai, Bj)
*    Delete ← F(i-1, j) + d
*    Insert ← F(i, j-1) + d
*    F(i,j) ← max(Match, Insert, Delete)
  }

Once the F matrix is computed, the entry F(n,m) gives the maximum score among all possible alignments. To compute an alignment that actually gives this score, you start from the bottom right cell, and compare the value with the three possible sources (Match, Insert, and Delete above) to see which it came from. If Match, then A(i) and B(j) are aligned, if Delete, then A(i) is aligned with a gap, and if Insert, then B(j) is aligned with a gap. (In general, more than one choice may have the same value, leading to alternative optimal alignments.)

* AlignmentA ← ""
* AlignmentB ← ""
* i ← length(A)
* j ← length(B)
* while (i > 0 or j > 0)
* {
*   if (i > 0 and j > 0 and F(i,j) == F(i-1,j-1) + S(Ai, Bj))
*   {
*     AlignmentA ← Ai + AlignmentA
*     AlignmentB ← Bj + AlignmentB
*     i ← i - 1
*     j ← j - 1
*   }
*   else if (i > 0 and F(i,j) == F(i-1,j) + d)
*   {
*     AlignmentA ← Ai + AlignmentA
*     AlignmentB ← "-" + AlignmentB
*     i ← i - 1
*   } 
*   else
*   {
*     AlignmentA ← "-" + AlignmentA
*     AlignmentB ← Bj + AlignmentB
*     j ← j - 1
*   }
* }

	The algorithm uses the algorithms for The Change problem & The Manhattan Tourist problem.
### Local Alignment (Smith–Waterman algorithm):
The Smith–Waterman algorithm performs local sequence alignment; that is, for determining similar regions between two strings of nucleic acid sequences or protein sequences. Instead of looking at the entire sequence, the Smith–Waterman algorithm compares segments of all possible lengths and optimizes the similarity measure.
![Gif](https://upload.wikimedia.org/wikipedia/commons/9/92/Smith-Waterman-Algorithm-Example-En.gif)	

* *Explanation:*
 1. **Determine the substitution matrix and the gap penalty scheme**. A substitution matrix assigns each pair of bases or amino acids a score for match or mismatch. Usually matches get positive scores, whereas mismatches get relatively lower scores. A gap penalty function determines the score cost for opening or extending gaps. 
 2. **Initialize the scoring matrix**. The dimensions of the scoring matrix are 1+length of each sequence respectively. All the elements of the first row and the first column are set to 0. The extra first row and first column make it possible to align one sequence to another at any position, and setting them to 0 makes the terminal gap free from penalty.
 3. **Scoring**. Score each element from left to right, top to bottom in the matrix, considering the outcomes of substitutions (diagonal scores) or adding gaps (horizontal and vertical scores). If none of the scores are positive, this element gets a 0. Otherwise the highest score is used and the source of that score is recorded.
 4. **Traceback**. Starting at the element with the highest score, traceback based on the source of each score recursively, until 0 is encountered. The segments that have the highest similarity score based on the given scoring system is generated in this process. To obtain the second best local alignment, apply the traceback process starting at the second highest score outside the trace of the best alignment.
* *Algorithm:*

# **Comparison between alignments**
The Smith–Waterman algorithm finds the segments in two sequences that have similarities while the Needleman–Wunsch algorithm aligns two complete sequences. Therefore, they serve different purposes. Both algorithms use the concepts of a substitution matrix, a gap penalty function, a scoring matrix, and a traceback process. Three main differences are:

POC		|Smith–Waterman algorithm |	Needleman–Wunsch algorithm
----------------|-------------------------|--------------------------------------------------------------------------------------------------------------------------
Initialization |	First row and first column are set to 0 |	First row and first column are subject to gap penalty
Scoring        |	Negative score is set to 0 	        |      Score can be negative
Traceback      | 	Begin with the highest score, end when 0 is encountered |	Begin with the cell at the lower right of the matrix, end at top left cell

# **References**
1. https://www.youtube.com/watch?v=kGJ9QZ5lwqs
2. https://biology.stackexchange.com/questions/11263/what-is-the-difference-between-local-and-global-sequence-alignments
3. https://en.wikipedia.org/wiki/Comparative_genomics
4. https://en.wikipedia.org/wiki/Smith%E2%80%93Waterman_algorithm
5. https://en.wikipedia.org/wiki/Sequence_alignment
6. https://en.wikipedia.org/wiki/Needleman%E2%80%93Wunsch_algorithm


