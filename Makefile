PROGRAM=tower

# Add your objs to generate in OBJS var
OBJS= src/main.o src/util/mathHelper.o src/render.o src/util/dataHolder.o src/util/renderUtil.o src/util/direction.o src/tile/tileMap.o src/tile/tiles.o
OBJS+= src/enemies/enemy.o src/enemies/classicEnemy.o src/enemies/bigEnemy.o src/enemies/healerEnemy.o src/towers/tower.o src/towers/classicTower.o src/towers/slowingTower.o
OBJS+= src/towers/explosiveTower.o src/object/missile.o src/particles/particle.o src/particles/explosion.o src/particles/heal.o src/util/gameUtil.o src/tile/tileHolder.o
OBJS+= src/towers/towerHolder.o src/entities/entity.o src/particles/enemyExplosion.o src/enemies/bossEnemy.o src/particles/bigExplosion.o src/particles/laser.o src/util/timeCounter.o
OBJS+= src/util/saveFile.o

CXX?=g++
TARGET?=$(shell $(CXX) -dumpmachine)

OPTIM_FLAGS?=-O0
CXXFLAGS=$(OPTIM_FLAGS) -g -Wall -Wextra -Wno-unused-parameter
CPPFLAGS=-Iinclude -Ithird_party/include -MMD -DWIN
LDFLAGS=-Lthird_party/libs-$(TARGET)
LDLIBS=-lraylib

ifeq ($(TARGET),x86_64-linux-gnu)
LDLIBS+=-ldl -lpthread -lm
else ifeq ($(TARGET),x86_64-pc-cygwin)
LDLIBS+=-lgdi32
else ifeq ($(TARGET),wasm32-unknown-emscripten)
OPTIM_FLAGS=-Os
LDFLAGS+=-s ASYNCIFY
LDFLAGS+=-s USE_GLFW=3
LDFLAGS+=--preload-file assets
EXT=.html
endif

DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: $(PROGRAM)$(EXT)

-include $(DEPS)

%.o: %.c
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(PROGRAM)$(EXT): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

build.tar.gz: $(PROGRAM) $(wildcard assets/*)
	tar czf build.tar.gz $(PROGRAM) assets

host: $(PROGRAM)$(EXT)
	python3 -m http.server 8000

clean:
	rm -f $(OBJS) $(DEPS) $(PROGRAM) build.tar.gz
	rm -f $(PROGRAM).html $(PROGRAM).js $(PROGRAM).data $(PROGRAM).wasm
