
CXX := g++
CXXFLAGS := -g -std=c++20 -Wall -Werror -Wpedantic -Wconversion -Iinclude
LDFLAGS := -L./lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image

#käsurealt argumentide andmiseks (võib ka tühjaks jääda)
ARGS:=

#exe faili nimi
EXE_NIMI := pong

#peafail (selle nimeks võiks jäädagi main.cpp, muutujasse paneme selle ilma faililaiendita)
TARGET := src/mainfile/main

#lisafailid (mõlemad võivad ka tühjaks jääda)
LISA_CPP_FAILID := $(wildcard src/*.cpp)
O_KAUST := obj

$(shell if not exist assets mkdir assets)
$(shell if not exist $(O_KAUST) mkdir $(O_KAUST))

O_FAILID := $(LISA_CPP_FAILID:src/%.cpp=$(O_KAUST)/%.o)


.FORCE:

$(TARGET).exe: $(TARGET).cpp $(O_FAILID) .FORCE
	@echo.
	@echo Kompileerime programmi
	$(CXX) $(CXXFLAGS) $(TARGET).cpp $(O_FAILID) -o $(EXE_NIMI) $(LDFLAGS)
	@echo Kompileeritud!
	@echo.

$(O_KAUST)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET).exe
	@cls
	@echo.
	@echo **Käivitame programmi**
	@echo.
	@./$(EXE_NIMI).exe $(ARGS)
	@echo.
	@echo **Programmi töö lõpp**
	@echo.

clean:
	@echo.
	@echo Kustutame .exe ja .o failid
	@echo.
	@if exist $(EXE_NIMI).exe del *.exe
	@if exist $(O_KAUST) rd /S /Q $(O_KAUST)
	@echo.
	@echo Kustutatud!
	@echo.

.PHONY: run clean