SET(libseq_SOURCE_FILES own_types.cpp digit_gen.cpp LatinSupercube.cpp LatinHypercube.cpp RandomizedTSSequence_base_2.cpp RandomizedTSSequence.cpp HaltonSequence.cpp DigitalSequence.cpp DigitalSequence_base_2.cpp DigitalSequence_classic.cpp DigitalSequence_medium_base.cpp DigitalSequence_advanced.cpp Sequence.cpp Polynomial.cpp Permutation.cpp Counter.cpp VectorMatrix.cpp VectorRing.cpp C_matrix.cpp Ring.cpp)

SET(libseq_HEADER_FILES LatinSupercube.h LatinHypercube.h RandomizedTSSequence.h HaltonSequence.h DigitalSequence.h Sequence.h Permutation.h Counter.h digit_gen.h options.h own_types.h VectorRing.h VectorMatrix.h C_matrix.h Polynomial.h Ring.h)

ADD_LIBRARY(seq STATIC ${libseq_HEADER_FILES} ${libseq_SOURCE_FILES})

SET_SOURCE_FILES_PROPERTIES(${libseq_HEADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

ADD_EXECUTABLE (SequenceTest SequenceTest.cpp)

TARGET_LINK_LIBRARIES(SequenceTest seq)
