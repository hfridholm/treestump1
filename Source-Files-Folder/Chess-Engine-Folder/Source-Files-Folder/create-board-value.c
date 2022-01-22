
#include "../Header-Files-Folder/engine-include-file.h"

signed short team_state_value(const Piece board[], Info info, Kings kings, unsigned short team)
{
	// This gets the enemy. If the team is NONE, the enemy is NONE
	// And if the enemy is none. The return value should be nutural.
	unsigned short enemy = normal_team_enemy(team);

	if(!normal_team_exists(team) || !normal_team_exists(enemy)) return 0;

	signed short enemyValue = board_state_value(board, info, kings, enemy);
	signed short teamValue = board_state_value(board, info, kings, team);

	return (teamValue - enemyValue);
}

signed short team_pieces_value(const Piece board[], unsigned short team)
{
	// If the team does not exist:
	if(!normal_team_exists(team)) return 0;

	signed short piecesValue = 0;

	for(Point point = 0; point < BOARD_LENGTH; point += 1)
	{
		Piece piece = board[point];

		// If the piece does not exist for some reason:
		if(!board_piece_exists(piece)) continue;

    unsigned short currentPieceTeam = PIECE_TEAM_MACRO(piece);
    unsigned short currentPieceType = PIECE_TYPE_MACRO(piece);

		if(currentPieceTeam != team) continue;

		// Adding the value of the piece
		piecesValue += PIECE_VALUES[currentPieceType];

		// Adding extra value for the piece location
		signed short matrixValue = piece_matrix_value(piece, point);

		piecesValue += (signed short) ( (float) matrixValue / 10.0);
	}

	return piecesValue;
}

signed short piece_matrix_value(Piece piece, Point point)
{
	// This is a error catcher. If the point insn't inside the board, segfault is going to happen next
	if(!point_inside_board(point) || !board_piece_exists(piece)) return 0;

  unsigned short team = PIECE_TEAM_MACRO(piece);
  unsigned short type = PIECE_TYPE_MACRO(piece);

  unsigned short rank = POINT_RANK_MACRO(point);
  unsigned short file = POINT_FILE_MACRO(point);

	if(team == TEAM_WHITE)
  {
    return PIECE_MATRIX[type][rank][file];
  }

	else if(team == TEAM_BLACK)
  {
    return PIECE_MATRIX[type][BOARD_RANKS - rank - 1][file];
  }

	else return 0;
}

signed short check_mate_value(const Piece board[], Info info, Kings kings, unsigned short team)
{
	unsigned short enemy = normal_team_enemy(team);

	if(!normal_team_exists(team) || !normal_team_exists(enemy)) return 0;

	signed short mateValue = 0;

	// If the teamKing (own king) is in check mate
	if(check_mate_ending(board, info, kings, TEAM_PIECE_MACRO(team) )) mateValue += MIN_BOARD_VALUE;

	// If the enemyKing (opponent) is in check mate
	else if(check_mate_ending(board, info, kings, TEAM_PIECE_MACRO(enemy) )) mateValue += MAX_BOARD_VALUE;

	return mateValue;
}

signed short check_draw_value(const Piece board[], Info info, Kings kings, unsigned short team)
{
	unsigned short enemy = normal_team_enemy(team);

	if(!normal_team_exists(team) || !normal_team_exists(enemy)) return 0;

	signed short drawValue = 0;

	// If the own king cant move (oppenent did draw)
	if(check_draw_ending(board, info, kings, TEAM_PIECE_MACRO(team) )) drawValue += MAX_BOARD_VALUE;

	// If the opponent cant move (you did draw)
	else if(check_draw_ending(board, info, kings, TEAM_PIECE_MACRO(enemy))) drawValue += MIN_BOARD_VALUE;

	return drawValue;
}

signed short board_state_value(const Piece board[], Info info, Kings kings, unsigned short team)
{
	if(!normal_team_exists(team)) return 0;

	signed short boardValue = 0;

	boardValue += team_pieces_value(board, team);

	boardValue += check_mate_value(board, info, kings, team);

	boardValue += check_draw_value(board, info, kings, team);

	return boardValue;
}
