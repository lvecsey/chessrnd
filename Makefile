
CC=gcc

CFLAGS=-Wall -O3 -g -pg

all : chessrnd test-movement_knight test-update_game test-movement_knight2 test-gameset test-movement_bishop test-movement_queen test-movement_rook test=movement_wpawn test-movement_bpawn

chessrnd : chessrnd.o ml.o basegame.o movement_pawn.o movement_knight.o show_bitmask.o fill_rankfile.o makemove.o update_game.o pieceloc2.o gameset.o pos.o clear_position.o movement_rook.o movement_king.o movement_bishop.o movement_queen.o king_incheck.o remove_checks.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

test-movement_knight : test-movement_knight.o movement_knight.o basegame.o show_bitmask.o ml.o pieceloc2.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

test-movement_knight2 : test-movement_knight2.o movement_knight.o basegame.o show_bitmask.o ml.o pieceloc2.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

test-movement_bishop : test-movement_bishop.o movement_bishop.o basegame.o show_bitmask.o ml.o pieceloc2.o update_game.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

test-movement_queen : test-movement_queen.o movement_queen.o basegame.o show_bitmask.o ml.o pieceloc2.o update_game.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

test-movement_rook : test-movement_rook.o movement_rook.o basegame.o show_bitmask.o ml.o pieceloc2.o update_game.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

test-update_game : test-update_game.o movement_knight.o basegame.o show_bitmask.o ml.o update_game.o makemove.o fill_rankfile.o pieceloc2.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

test-fill_rankfile : test-fill_rankfile.o fill_rankfile.o makemove.o ml.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

test-movement_wpawn : test-movement_wpawn.o movement_pawn.o basegame.o show_bitmask.o ml.o update_game.o fill_rankfile.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

test-movement_bpawn : test-movement_bpawn.o movement_pawn.o basegame.o show_bitmask.o ml.o update_game.o fill_rankfile.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

test-gameset : test-gameset.o gameset.o basegame.o pieceloc2.o pos.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

clean :
	-rm *.o
