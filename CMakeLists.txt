CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(libseq)

# Make sure we have Boost
FIND_PACKAGE(Boost 1.42.0 REQUIRED)
MESSAGE(STATUS "Found Boost include directory at ${Boost_INCLUDE_DIRS}")

# Set our global include files search path
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

SET(libseq_SOURCE_FILES own_types.C digit_gen.C LatinSupercube.C LatinHypercube.C RandomizedTSSequence_base_2.C RandomizedTSSequence.C HaltonSequence.C DigitalSequence.C DigitalSequence_base_2.C DigitalSequence_classic.C DigitalSequence_medium_base.C DigitalSequence_advanced.C Sequence.C Polynomial.C Permutation.C Counter.C VectorMatrix.C VectorRing.C C_matrix.C Ring.C)

SET(libseq_HEADER_FILES LatinSupercube.h LatinHypercube.h RandomizedTSSequence.h HaltonSequence.h DigitalSequence.h Sequence.h Permutation.h Counter.h digit_gen.h options.h own_types.h VectorRing.h VectorMatrix.h C_matrix.h Polynomial.h Ring.h)

ADD_LIBRARY(libseq STATIC ${libseq_HEADER_FILES} ${libseq_SOURCE_FILES})

SET_SOURCE_FILES_PROPERTIES(${libseq_HEADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

ADD_EXECUTABLE (SequenceTest SequenceTest.C)

TARGET_LINK_LIBRARIES(SequenceTest libseq)
