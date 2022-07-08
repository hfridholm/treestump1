
#ifndef CHESS_MOVES_LEGAL_H
#define CHESS_MOVES_LEGAL_H

bool move_fully_legal(const Piece[], Info, Move);

bool move_pseudo_legal(const Piece[], Info, Move);

bool piece_legal_moves(Move**, const Piece[], Info, Point);

bool team_legal_moves(Move**, const Piece[], Info, unsigned short);

#endif
