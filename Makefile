CXX       = g++
CXXFLAGS  = -std=c++17 -Wall
LDFLAGS   =
LIBS      =
INCLUDES  =
RCXXFLAGS = $(CXXFLAGS) -O3
RLDFLAGS  = $(LDFLAGS)
RLIBS     = $(LIBS)
RINCLUDES = $(INCLUDES)
DCXXFLAGS = $(CXXFLAGS) -O0 -g
DLDFLAGS  = $(LDFLAGS)
DLIBS     = $(LIBS)
DINCLUDES = $(INCLUDES)
TCXXFLAGS = $(CXXFLAGS) -pthread
TLDFLAGS  = $(LDFLAGS) -lgtest
TLIBS     = $(LIBS)
TINCLUDES = $(INCLUDES) -I./src

RTARGETS = ml
DTARGETS = ml_debug
TTARGETS = ml_test

RTARGETDIR = ./bin/release
DTARGETDIR = ./bin/debug
TTARGETDIR = ./bin/test

ROBJDIR = ./obj/release
DOBJDIR = ./obj/debug
TOBJDIR = ./obj/test

SOURCEDIR  = ./src
TSOURCEDIR = ./test

# bison
BISONSRC = $(SOURCEDIR)/ml_parser.yy
BISONOUTSRC = $(SOURCEDIR)/ml_parser.tab.cpp
BISONOUTLIST = \
	$(SOURCEDIR)/ml_parser.output \
	$(BISONOUTSRC) \
	$(SOURCEDIR)/location.hh \
	$(SOURCEDIR)/ml_parser.tab.hpp \
	$(SOURCEDIR)/position.hh \
	$(SOURCEDIR)/stack.hh

# flex
FLEXSRC = $(SOURCEDIR)/ml_lexer.l
FLEXOUTSRC = $(SOURCEDIR)/ml_lexer.yy.cpp
FLEXOUTLIST = $(FLEXOUTSRC)

# 1. サブディレクトリを含むディレクトリリストの生成
SRCDIRLIST  := $(shell find $(SOURCEDIR) -type d)
TSRCDIRLIST := $(shell find $(TSOURCEDIR) -type d)

# 2. すべての cpp ファイルのリストの生成
OUTSRCLIST = $(BISONOUTSRC) $(FLEXOUTSRC)
SRCLIST = \
	$(OUTSRCLIST) \
	$(filter-out $(OUTSRCLIST), $(foreach srcdir, $(SRCDIRLIST), $(wildcard $(srcdir)/*.cpp)))
TSRCLIST = $(foreach tsrcdir, $(TSRCDIRLIST), $(wildcard $(tsrcdir)/*.cpp))

# 3. トリミング
CUTSRCLIST  = $(subst $(SOURCEDIR),.,$(SRCLIST))
CUTTSRCLIST = $(subst $(TSOURCEDIR),.,$(TSRCLIST))

# 4. オブジェクトファイル名の決定
ROBJLIST = $(addprefix $(ROBJDIR)/, $(CUTSRCLIST:.cpp=.o))
DOBJLIST = $(addprefix $(DOBJDIR)/, $(CUTSRCLIST:.cpp=.o))
TOBJLIST = $(addprefix $(TOBJDIR)/, $(CUTTSRCLIST:.cpp=.o))

# 5. テストに使用しないファイルの除外
TEXCLUDELIST = ml.cpp
TEMPSRCLIST = $(filter-out %$(TEXCLUDELIST), $(CUTSRCLIST))
TMODULELIST = $(addprefix $(DOBJDIR)/, $(TEMPSRCLIST:.cpp=.o))

# 6. ディレクトリ構造のリスト化
ROBJDIRLIST = $(addprefix $(ROBJDIR)/, $(SRCDIRLIST))
DOBJDIRLIST = $(addprefix $(DOBJDIR)/, $(SRCDIRLIST))
TOBJDIRLIST = $(addprefix $(TOBJDIR)/, $(TSRCDIRLIST))

# 7. 各種ビルドターゲット設定
.PHONY: build clean rebuild build_debug clean_debug rebuild_debug build_test clean_test rebuild_test run_test clean_all

build: $(RTARGETS)

clean: clean_bison clean_flex
	rm -f $(ROBJLIST) $(RTARGETDIR)/$(RTARGETS)

# bison と flex が生成する cpp を生成するルールがないというエラーがでるので一旦コメントアウト
# rebuild: clean build

build_debug: $(DTARGETS)

clean_debug: clean_bison clean_flex
	rm -f $(DOBJLIST) $(DTARGETDIR)/$(DTARGETS)

# bison と flex が生成する cpp を生成するルールがないというエラーがでるので一旦コメントアウト
# rebuild_debug: clean_debug build_debug

build_test: $(DTARGETS) $(TTARGETS)

clean_test: clean_bison clean_flex
	rm -f $(TOBJLIST) $(DOBJLIST) $(TTARGETDIR)/$(TTARGETS)

# bison と flex が生成する cpp を生成するルールがないというエラーがでるので一旦コメントアウト
# rebuild_test: clean_test build_test

# rebuild_test がうまく動かないので、rebuild_test に依存しない形のものを一旦使う
# run_test: rebuild_test
run_test:
	$(TTARGETDIR)/$(TTARGETS)

clean_bison:
	rm -f $(BISONOUTLIST)

clean_flex:
	rm -f $(FLEXOUTLIST)

clean_all: clean clean_debug clean_test

# 8. ターゲット実行ファイルの生成
$(RTARGETS): $(ROBJLIST)
	@echo "$^"
	@if [ ! -e $(RTARGETDIR) ]; then mkdir -p $(RTARGETDIR); fi
	$(CXX) -o $(RTARGETDIR)/$@ $^ $(RLDFLAGS) $(RLIBS)

$(DTARGETS): $(DOBJLIST)
	@echo "$^"
	@if [ ! -e $(DTARGETDIR) ]; then mkdir -p $(DTARGETDIR); fi
	$(CXX) -o $(DTARGETDIR)/$@ $^ $(DLDFLAGS) $(DLIBS)

$(TTARGETS): $(TOBJLIST)
	@echo "$^"
	@if [ ! -e $(TTARGETDIR) ]; then mkdir -p $(TTARGETDIR); fi
	$(CXX) -o $(TTARGETDIR)/$@ $^ $(TMODULELIST) $(TLDFLAGS) $(TLIBS)

# 9. 中間バイナリの生成
$(ROBJDIR)/%.o: $(SOURCEDIR)/%.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(RCXXFLAGS) $(RINCLUDES) -o $@ -c $<

$(DOBJDIR)/%.o: $(SOURCEDIR)/%.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(DCXXFLAGS) $(DINCLUDES) -o $@ -c $<

$(TOBJDIR)/%.o: $(TSOURCEDIR)/%.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(TCXXFLAGS) $(TINCLUDES) -o $@ -c $<

$(ROBJDIR)/./%.o: $(SOURCEDIR)/%.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(RCXXFLAGS) $(RINCLUDES) -o $@ -c $<

# bison
$(BISONOUTSRC): $(BISONSRC)
	bison -dv --output=$@ $<

# flex
$(FLEXOUTSRC): $(FLEXSRC) $(BISONOUTSRC)
	flex --outfile=$@ $<
