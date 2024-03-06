# Makefile

# 変更すべき箇所を1箇所に集約するため，マクロを使用する
#
# マクロ (変数) 名 = 値 (数字，文字列...)で定義し，
# $(変数名) で値を参照する

# "#"で始まる行はコメント行として扱われる

#----------------------------------------------------------------------
# Cコンパイラの登録
CC = gcc-12
CXX = g++-12

#----------------------------------------------------------------------
# AutoGL(おてがる)のファイルの場所の設定
# このMakefileの置かれたディレクトリからの相対パス
AUTOGL_HEADER_DIR = lib/autogl
AUTOGL_LIBRARY_DIR = lib/autogl

# AutoGL(おてがる)のライブラリ名の設定
LIBAUTOGL = $(AUTOGL_LIBRARY_DIR)/libautogl.a

#----------------------------------------------------------------------
# コンパイル時に読み込むファイルの設定
INCLUDES = -I$(AUTOGL_HEADER_DIR)
# コンパイルオプション
CFLAGS = $(INCLUDES) -std=c++11 -g -Wall -fopenmp

# リンクするライブラリの設定
LIBS =
LIBS_VIS = $(LIBS) -L$(AUTOGL_LIBRARY_DIR) -lautogl -lX11
LIBS_VIS += `${AUTOGL_LIBRARY_DIR}/advautogl-config`
# リンクオプション
LDFLAGS = $(LIBS) -fopenmp
LDFLAGS_VIS = $(LIBS_VIS) -fopenmp

#----------------------------------------------------------------------
# 作成する実行ファイルの名称
# (無指定でビルドして得られる "a.out" に相当するもの)
PROGRAM = station
PROGRAM_CALC = station-calc

#----------------------------------------------------------------------
# .cファイルをコンパイルし，.oファイルを作成するための設定
#  (サフィックスルールと呼ばれる)
.cpp.o:
	$(CXX) -c $< $(CFLAGS)

# ちなみに.oファイルは"オブジェクトファイル"と呼ばれる．
# .c/.cppファイルと実行形式のファイルの間にある"中間ファイル"である．

# 実行ファイルを構成するオブジェクトファイル
# 新たなファイル (.c/.cppファイル) を追加した場合はここに追加する
# \ で改行して続ける
OBJ = GlobalValue.o \
	Pedestrian.o \
	SimHandler.o \
	Vector2D.o \
	Virus.o \
	Wall.o

OBJ_CALC = mainCalc.o

OBJ_VIS = main.o \
	Drawer.o \
	Visualizer.o

#----------------------------------------------------------------------
# "make"と打って作成されるプログラムの指定
all : $(LIBAUTOGL) $(PROGRAM) $(PROGRAM_CALC)

# 以下は次のようなルールの記述
# (厳密にはルールではなく"ターゲット"と呼ばれる)

# ルール名 : ルールの依存対象
# [TAB] ルールの依存対象が更新された時に実行されるコマンド

# なお"$@"は特殊なマクロで，ターゲット名を表す

# 以下は"lib/autogl/libautogl.a"という名前のルールであり，
# "lib/autogl/libautogl.a"というファイルを作成するためのもの
#
# lib/autogl/*.c, lib/autogl/*.hというファイルに依存し，
# それらのファイルに更新があれば，lib/autogl/ディレクトリに移動し (cd)
# そこで改めてmakeを実行する，という意味
$(LIBAUTOGL) : $(AUTOGL_LIBRARY_DIR)/*.[ch]
	cd $(AUTOGL_LIBRARY_DIR); $(MAKE)

# 以下は"station"という名前のルールであり
# "station"というファイルを作成するためのもの
#
# $(OBJ)および$(OBJ_VIS)で定義されたオブジェクトファイルに依存し，
# それらのファイルに更新があれば，改めてファイルをまとめて (リンクして)
# stationという実行形式のファイルを作成する，という意味
$(PROGRAM) : $(OBJ) $(OBJ_VIS) $(LIBAUTOGL)
	$(CXX) -o $@ $(OBJ) $(OBJ_VIS) $(LDFLAGS_VIS)

# 以下は"station-calc"という名前のルールであり
# "station-calc"というファイルを作成するためのもの
#
# $(OBJ)および$(OBJ_CALC)で定義されたオブジェクトファイルに依存し，
# それらのファイルに更新があれば，改めてファイルをまとめて (リンクして)
# stationという実行形式のファイルを作成する，という意味
$(PROGRAM_CALC) : $(OBJ) $(OBJ_CALC)
	$(CXX) -o $@ $(OBJ) $(OBJ_CALC) $(LDFLAGS)

# これは通常の"make"でなく，"make clean"と打った時に実行されるルール
# 慣習として，"clean"というルールは中間ファイルと実行ファイルを削除する
.PHONY: clean
clean :
	rm -f *.o $(PROGRAM) $(PROGRAM_CALC)

clobber : clean
	cd $(AUTOGL_LIBRARY_DIR); make clean

# これはflymake用の設定
check-syntax :
	case $(CHK_SOURCES) in \
	*.c) \
		$(CC) $(CFLAGS) -pedantic -fsyntax-only $(CHK_SOURCES) ; \
		;; \
	*.cpp|*.h) \
		$(CXX) $(CFLAGS) -pedantic -fsyntax-only $(CHK_SOURCES) ; \
		;; \
	*) \
		;; \
	esac
