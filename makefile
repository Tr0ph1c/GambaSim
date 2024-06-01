BIN = ./bin/
FILES = $(BIN)Generators.o $(BIN)CrossPlatFuncs.o $(BIN)InventorySystem.o $(BIN)Cases.o $(BIN)Player.o $(BIN)EventSystem.o

$(BIN)Gamba: Gamba.cpp SaveSystem.cpp $(FILES)
	g++ -I./Include/ -g Gamba.cpp $(FILES) -o Gamba

$(BIN)Player.o: Player.cpp
	g++ -I./Include/ Player.cpp -c -o $(BIN)Player.o

$(BIN)Cases.o: Cases.cpp
	g++ -I./Include/ Cases.cpp -c -o $(BIN)Cases.o

$(BIN)InventorySystem.o: InventorySystem.cpp
	g++ -I./Include/ InventorySystem.cpp -c -o $(BIN)InventorySystem.o

$(BIN)CrossPlatFuncs.o: CrossPlatFuncs.cpp
	g++ -I./Include/ CrossPlatFuncs.cpp -c -o $(BIN)CrossPlatFuncs.o

$(BIN)Generators.o: Generators.cpp
	g++ -I./Include/ Generators.cpp -c -o $(BIN)Generators.o

$(BIN)EventSystem.o: EventSystem.cpp
	g++ -I./Include/ EventSystem.cpp -c -o $(BIN)EventSystem.o