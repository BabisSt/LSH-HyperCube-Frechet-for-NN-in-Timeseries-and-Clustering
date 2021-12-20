CC = g++

OFLAGS = -std=c++14 -O3
CFLAGS = -g3 -Wall -Wextra
LDFLAGS =

BDIR = bin
ODIR = build
IDIR = include
SDIR = src

EXEC1 = lsh
EXEC2 = cube
EXEC3 = cluster
EXEC4 = frechet

_DEPS = data.h input.h LSH.h hashTable.h hyperCube.h kmeansplusplus.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o input.o data.o LSH.o hashTable.o hyperCube.o kmeansplusplus.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) $(OFLAGS) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

all: $(BDIR)/$(EXEC1) $(BDIR)/$(EXEC2) $(BDIR)/$(EXEC3) $(BDIR)/$(EXEC4)

$(BDIR)/$(EXEC1): $(OBJ)
	$(CC) $(OFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BDIR)/$(EXEC2): $(OBJ)
	$(CC) $(OFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BDIR)/$(EXEC3): $(OBJ)
	$(CC) $(OFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BDIR)/$(EXEC4): $(OBJ)
	$(CC) $(OFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean run* valgrind*

run-lsh:
	./$(BDIR)/$(EXEC1) \
	-i ./assets/nasd_input.csv \
	-q ./assets/nasd_query.csv \
	-o ./logs/logs.txt \
	-N 10

valgrind-lsh:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(BDIR)/$(EXEC1) \
	-i ./assets/dataset.csv \
	-q ./assets/query.csv \
	-o ./logs/logs.txt \
	-N 10

run-hc:
	./$(BDIR)/$(EXEC2) \
	-i ./assets/nasd_input.csv \
	-q ./assets/nasd_query.csv \
	-o ./logs/logs.txt \
	-N 50

valgrind-hc:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(BDIR)/$(EXEC2) \
	-i ./assets/dataset.csv \
	-q ./assets/query.csv \
	-o ./logs/logs.txt \
	-N 10

run-fr:
	./$(BDIR)/$(EXEC4) \
	-i ./assets/nasd_input.csv \
	-q ./assets/nasd_query.csv \
	-o ./logs/logs.txt \
	-delta 0.5 \
	-N 50

valgrind-fr:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(BDIR)/$(EXEC4) \
	-i ./assets/dataset.csv \
	-q ./assets/query.csv \
	-o ./logs/logs.txt \
	-metric discrete \
	-delta 0.1 \
	-N 10

run-cluster-classic:
	./$(BDIR)/$(EXEC3) \
	-i ./assets/nasd_input.csv \
	-c ./cluster.conf \
	-o ./logs/logs.txt \
	-m Classic

run-cluster-classic-fr:
	./$(BDIR)/$(EXEC3) \
	-i ./assets/nasd_input.csv \
	-c ./cluster.conf \
	-o ./logs/logs.txt \
	-m Classic

run-cluster-lsh:
	./$(BDIR)/$(EXEC3) \
	-i ./assets/nasd_input.csv \
	-c ./cluster.conf \
	-o ./logs/logs.txt \
	-m LSH

run-cluster-lsh-fr:
	./$(BDIR)/$(EXEC3) \
	-i ./assets/nasd_input.csv \
	-c ./cluster.conf \
	-o ./logs/logs.txt \
	-m LSH

run-cluster-hc:
	./$(BDIR)/$(EXEC3) \
	-i ./assets/nasd_input.csv \
	-c ./cluster.conf \
	-o ./logs/logs.txt \
	-m Hypercube

valgrind-cluster:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(BDIR)/$(EXEC3) \
	-i ./assets/nasd_input.csv \
	-c ./cluster.conf \
	-o ./logs/logs.txt \
	-m LSH

clean:
	rm -f $(ODIR)/*.o
	rm -f $(BDIR)/$(EXEC1)
	rm -f $(BDIR)/$(EXEC2)
	rm -f $(BDIR)/$(EXEC3)
	rm -f $(BDIR)/$(EXEC4)
