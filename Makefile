CXX       = g++
CXXFLAGS  = -std=c++17 -Wall
LDFLAGS   =
LIBS      =
INCLUDES  = -I./header
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
TINCLUDES = $(INCLUDES)

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

TARGETMAINSRC = ml.cpp

# 1. サブディレクトリを含むディレクトリリストの生成
SRCDIRLIST  := $(shell find $(SOURCEDIR) -type d)
TSRCDIRLIST := $(shell find $(TSOURCEDIR) -type d)

# 2. すべての cpp ファイルのリストの生成
SRCLIST  = $(foreach srcdir, $(SRCDIRLIST), $(wildcard $(srcdir)/*.cpp))
TSRCLIST = $(foreach tsrcdir, $(TSRCDIRLIST), $(wildcard $(tsrcdir)/*.cpp))

# 3. トリミング
CUTSRCLIST  = $(subst $(SOURCEDIR),.,$(SRCLIST))
CUTTSRCLIST = $(subst $(TSOURCEDIR),.,$(TSRCLIST))

# 4. オブジェクトファイル名の決定
ROBJLIST = $(addprefix $(ROBJDIR)/, $(CUTSRCLIST:.cpp=.o))
DOBJLIST = $(addprefix $(DOBJDIR)/, $(CUTSRCLIST:.cpp=.o))
TOBJLIST = $(addprefix $(TOBJDIR)/, $(CUTTSRCLIST:.cpp=.o))

# 5. テスト用に main を含むファイルの除外
TEMPSRCLIST = $(filter-out %$(TARGETMAINSRC), $(CUTSRCLIST))
TMODULELIST = $(addprefix $(DOBJDIR)/, $(TEMPSRCLIST:.cpp=.o))

# 6. ディレクトリ構造のリスト化
ROBJDIRLIST = $(addprefix $(ROBJDIR)/, $(SRCDIRLIST))
DOBJDIRLIST = $(addprefix $(DOBJDIR)/, $(SRCDIRLIST))
TOBJDIRLIST = $(addprefix $(TOBJDIR)/, $(TSRCDIRLIST))

# 7. 各種ビルドターゲット設定
.PHONY: build clean rebuild build_debug clean_debug rebuild_debug build_test clean_test rebuild_test run_test clean_all

build: $(RTARGETS)

clean:
	rm -f $(ROBJLIST) $(RTARGETDIR)/$(RTARGETS)

rebuild: clean build

build_debug: $(DTARGETS)

clean_debug:
	rm -f $(DOBJLIST) $(DTARGETDIR)/$(DTARGETS)

rebuild_debug: clean_debug build_debug

build_test: $(DTARGETS) $(TTARGETS)

clean_test:
	rm -f $(TOBJLIST) $(DOBJLIST) $(TTARGETDIR)/$(TTARGETS)

rebuild_test: clean_test build_test

run_test: rebuild_test
	$(TTARGETDIR)/$(TTARGETS)

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
