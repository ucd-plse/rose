include $(top_srcdir)/config/Makefile.for.ROSE.includes.and.libs

SUBDIRS = AMRShift

AM_CPPFLAGS = $(ROSE_INCLUDES)

DSL_INFRASTRUCTURE_SRC = $(top_srcdir)/projects/dsl_infrastructure
DSL_INFRASTRUCTURE_BIN = $(top_builddir)/projects/dsl_infrastructure

MULTIGRID_TARGET_ABSTRACTION_BIN = $(top_builddir)/projects/amrShiftDSLcompiler/AMRShift

bin_PROGRAMS    = amrShiftDSLcompiler

CXX11FLAG = -std=c++11 

CPPFLAGS += $(CXX11FLAG) -Wunknown-pragmas

# amrShiftDSLcompiler_SOURCES = amrShiftDSLcompiler.C array.C
amrShiftDSLcompiler_SOURCES = amrShiftDSLcompiler.C

# amrShiftDSLcompiler_LIBS = $(MULTIGRID_TARGET_ABSTRACTION_BIN)/amrShift.la

# DQ (1/19/2016): Added test code for std::function support required in DSL recognition and evaluation.
testFunctionCallBack_01_SOURCES = testFunctionCallBack_01.C
testFunctionCallBack_02_SOURCES = testFunctionCallBack_02.C
testFunctionCallBack_03_SOURCES = testFunctionCallBack_03.C
testFunctionCallBack_04_SOURCES = testFunctionCallBack_04.C

# include_HEADERS = -I$(DSL_INFRASTRUCTURE_SRC)
# INCLUDES = -I$(DSL_INFRASTRUCTURE_SRC)
INCLUDES = -I$(DSL_INFRASTRUCTURE_SRC) $(AMR_INCLUDES)

# ATERM_LIB_DIR = $(ATERM_INSTALL_PATH)/lib

LDADD = $(LIBS_WITH_RPATH) $(ROSE_LIBS) $(DSL_INFRASTRUCTURE_BIN)/libdsl_infrastructure.la $(MULTIGRID_TARGET_ABSTRACTION_BIN)/libamrShift.la

TESTCODES_REQUIRED_TO_PASS = test2014_01.C

TESTCODE_CURRENTLY_FAILING =

# Automake's testing mechanism (which defines the "make check" rule) requires passing tests.
TESTCODES = $(TESTCODES_REQUIRED_TO_PASS)

ALL_TESTCODES = $(TESTCODES) $(TESTCODE_CURRENTLY_FAILING)

PASSING_TEST_Output = $(addprefix rose_,${TESTCODES})
TEST_Output = $(addprefix rose_,${ALL_TESTCODES})

PASSING_REGRESSION_TEST_Output = ${TESTCODES_REQUIRED_TO_PASS:.C=.C.passing}

AMR_INCLUDES = -I$(srcdir)/AMRShift/Multigrid -I$(srcdir)/AMRShift/StencilTools -I$(srcdir)/AMRShift/timer -I$(srcdir)/AMRShift/VisitWriter 

# Generate DOT graphs of the kind of code we need to generate using ROSE.
generateDotOfTargetGeneratedCode: generated_dsl_attributes.C generated_dsl_attributes.h 
	$(top_builddir)/tests/nonsmoke/functional/testGraphGeneration -std=c++11 -DSKIP_ROSE_HEADERS -rose:skipfinalCompileStep -I. $(srcdir)/dsl_attributes.C


generated_dsl_attributes.C: $(DSL_INFRASTRUCTURE_BIN)/attributeGenerator
#	Comment out if we don't need to regenerate the generated code for the DSL compiler.
	$(DSL_INFRASTRUCTURE_BIN)/attributeGenerator -std=c++11 -DSKIP_ROSE_HEADERS -I$(DSL_INFRASTRUCTURE_SRC) $(AMR_INCLUDES) $(srcdir)/AMRShiftAbstractions.C

# This is force to depend upon a single dependent file, even though dslSupport.o 
# depends upon generated_dsl_attributes_header.C insted of generated_dsl_attributes.C.
amrShiftDSLcompiler.o : $(builddir)/generated_dsl_attributes.C

attributeGenerator: $(DSL_INFRASTRUCTURE_BIN)/attributeGenerator
#	$(MAKE) -C../dsl_infrastructure attributeGenerator
#	cd ../dsl_infrastructure; $(MAKE) attributeGenerator
	@echo "Can't make attributeGenerator from amrShiftDSLcompiler directory (not clear why)."

testAMRShift: attributeGenerator
	$(DSL_INFRASTRUCTURE_BIN)/attributeGenerator --edg:no_warnings -w -std=c++11 -DSKIP_ROSE_HEADERS -I$(DSL_INFRASTRUCTURE_SRC) $(AMR_INCLUDES) $(srcdir)/AMRShiftAbstractions.C

testAMRShiftCompiler: amrShiftDSLcompiler
#	./amrShiftDSLcompiler -Wunknown-pragmas -DSKIP_ROSE_BUILTIN_DECLARATIONS -std=c++11 -DSKIP_ROSE_HEADERS -DDIM=2 $(AMR_INCLUDES) $(srcdir)/AMRShift/Multigrid/multigridTest.cpp
	./amrShiftDSLcompiler -Wunknown-pragmas -std=c++11 -DSKIP_ROSE_HEADERS -DDIM=2 $(AMR_INCLUDES) $(srcdir)/AMRShift/Multigrid/multigridTest.cpp


check-local:
	@echo "Tests for DSL Infrastructure examples."
	@echo "**************************************************************************************************"
	@echo "******* ROSE/projects/amrShiftDSLcompiler: make check rule complete (terminated normally) ********"
	@echo "**************************************************************************************************"


EXTRA_DIST = 

CLEANFILES = 

clean-local:
	rm -rf *.o rose_*.C generated_dsl_attributes.h generated_dsl_attributes.C generated_dsl_attributes_header.C temp_dummy_file_*.C
	rm -f a.out *.dot *.ti
	rm -f testFunctionCallBack_0?


