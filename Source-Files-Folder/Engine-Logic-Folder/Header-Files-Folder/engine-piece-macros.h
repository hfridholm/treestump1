
#ifndef ENGINE_PIECE_MACROS_H
#define ENGINE_PIECE_MACROS_H

#define MASK_PIECE_TYPE(PIECE) (PIECE & PIECE_TYPE_MASK)
#define MASK_PIECE_TEAM(PIECE) (PIECE & PIECE_TEAM_MASK)

#define CLEAR_PIECE_TEAM(PIECE) (PICEE & ~PIECE_TEAM_MASK)
#define CLEAR_PIECE_TYPE(PIECE) (PIECE & ~PIECE_TYPE_MASK)

#define PIECE_TEAM_MACRO(PIECE) (MASK_PIECE_TEAM(PIECE) >> PIECE_TEAM_SHIFT)
#define PIECE_TYPE_MACRO(PIECE) (MASK_PIECE_TYPE(PIECE) >> PIECE_TYPE_SHIFT)

#define TEAM_PIECE_MACRO(TEAM) MASK_PIECE_TEAM((TEAM << PIECE_TEAM_SHIFT))
#define TYPE_PIECE_MACRO(TYPE) MASK_PIECE_TYPE((TYPE << PIECE_TYPE_SHIFT))

#define ALLOC_PIECE_TEAM(PIECE, TEAM) (CLEAR_PIECE_TEAM(PIECE) | MASK_PIECE_TEAM(TEAM))
#define ALLOC_PIECE_TYPE(PIECE, TYPE) (CLEAR_PIECE_TYPE(PIECE) | MASK_PIECE_TYPE(TYPE))

#define PIECE_STORE_TYPE(PIECE, TYPE) (MASK_PIECE_TYPE(PIECE) == TYPE)

#define PIECE_TYPE_EXISTS(PIECE_TYPE) NUMBER_IN_BOUNDS(PIECE_TYPE_MACRO(PIECE_TYPE), 1, 6)
#define PIECE_TEAM_EXISTS(PIECE_TEAM) ((PIECE_TEAM == PIECE_TEAM_WHITE) || (PIECE_TEAM == PIECE_TEAM_BLACK))

#define CHESS_PIECE_EXISTS(PIECE) (PIECE_TEAM_EXISTS(MASK_PIECE_TEAM(PIECE)) && PIECE_TYPE_EXISTS(MASK_PIECE_TYPE(PIECE)))

#define PIECE_TEAMS_TEAM(PIECE_TEAM1, PIECE_TEAM2) (((PIECE_TEAM1 == PIECE_TEAM_BLACK) && (PIECE_TEAM2 == PIECE_TEAM_BLACK)) || ((PIECE_TEAM1 == PIECE_TEAM_WHITE) && (PIECE_TEAM2 == PIECE_TEAM_WHITE)))
#define PIECE_TEAMS_ENEMY(PIECE_TEAM1, PIECE_TEAM2) (((PIECE_TEAM1 == PIECE_TEAM_BLACK) && (PIECE_TEAM2 == PIECE_TEAM_WHITE)) || ((PIECE_TEAM1 == PIECE_TEAM_WHITE) && (PIECE_TEAM2 == PIECE_TEAM_BLACK)))

#define CHESS_PIECES_TEAM(PIECE1, PIECE2) PIECE_TEAMS_TEAM(MASK_PIECE_TEAM(PIECE1), MASK_PIECE_TEAM(PIECE2))
#define CHESS_PIECES_ENEMY(PIECE1, PIECE2) PIECE_TEAMS_ENEMY(MASK_PIECE_TEAM(PIECE1), MASK_PIECE_TEAM(PIECE2))

#define BOARD_POINT_TEAM(BOARD, POINT) PIECE_TEAM_MACRO(BOARD[POINT])

#define POINT_PIECE_TYPE(BOARD, POINT) MASK_PIECE_TYPE(BOARD[POINT])

#define PIECE_TEAM_ENEMY(PIECE_TEAM) ((PIECE_TEAM == PIECE_TEAM_WHITE) ? PIECE_TEAM_BLACK : ((PIECE_TEAM == PIECE_TEAM_BLACK) ? PIECE_TEAM_WHITE : PIECE_TEAM_NONE))

#define CHESS_PIECE_SCORE(PIECE) PIECE_TYPE_SCORES[PIECE_TYPE_MACRO(PIECE)]

#endif
