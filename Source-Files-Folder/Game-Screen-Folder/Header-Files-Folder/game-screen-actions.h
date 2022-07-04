
#ifndef GAME_SCREEN_ACTIONS_H
#define GAME_SCREEN_ACTIONS_H

bool input_promote_flag(Move*, Screen, unsigned short);

bool input_mark_parser(Point*, Screen, const Piece[], Info, Kings, const Move[], Event, bool);

bool input_screen_move(Move*, Screen, const Piece[], Info, Kings, const Move[], bool*);

bool input_move_parser(Move*, Screen, const Piece[], Info, Kings, const Move[], Event, bool);

bool input_single_move(Move*, Screen, const Piece[], Info, Kings, const Move[], bool*);

bool input_legal_move(Move*, Screen, const Piece[], Info, Kings, const Move[], bool*);

#endif
