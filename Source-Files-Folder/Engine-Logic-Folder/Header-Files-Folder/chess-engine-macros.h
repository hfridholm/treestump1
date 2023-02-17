
#ifndef CHESS_ENGINE_MACROS_H
#define CHESS_ENGINE_MACROS_H

#define NUMBER_IN_BOUNDS(NUMBER, MINIMUM, MAXIMUM) (NUMBER >= MINIMUM && NUMBER <= MAXIMUM)

#define MAX_NUMBER_VALUE(NUMBER1, NUMBER2) ((NUMBER2 > NUMBER1) ? NUMBER2 : NUMBER1)

#define MIN_NUMBER_VALUE(NUMBER1, NUMBER2) ((NUMBER2 < NUMBER1) ? NUMBER2 : NUMBER1)

#define NORMAL_TYPE_EXISTS(TYPE) NUMBER_IN_BOUNDS(TYPE, 1, 6)

#define NORMAL_TEAM_EXISTS(TEAM) ((TEAM == TEAM_WHITE) || (TEAM == TEAM_BLACK))

#define TEAM_WEIGHT_SCORE(SCORE, TEAM) ((TEAM == TEAM_BLACK) ? -SCORE : SCORE)

#define TEAM_SCORE_WEIGHT(TEAM) ((TEAM == TEAM_WHITE) ? 1 : -1)

#define CURRENT_TEAM_WEIGHT(STATE) TEAM_SCORE_WEIGHT(STATE_CURRENT_MACRO(STATE))

#define TEAM_MATRIX_RANK(RANK, TEAM) ((TEAM == TEAM_WHITE) ? RANK : (BOARD_RANKS - RANK - 1))

#define MATRIX_POINT_RANK(POINT, TEAM) TEAM_MATRIX_RANK(POINT_RANK_MACRO(POINT), TEAM)

#define TEAM_TYPE_EXISTS(TEAM, TYPE) (NORMAL_TEAM_EXISTS(TEAM) && NORMAL_TYPE_EXISTS(TYPE))

#endif
