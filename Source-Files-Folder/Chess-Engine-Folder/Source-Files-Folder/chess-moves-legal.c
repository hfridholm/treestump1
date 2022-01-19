
#include "../Header-Files-Folder/engine-include-file.h"

// This function should check:
// - the move is pseudo legal
// - the own king is not set in check
bool move_fully_legal(const Piece board[], Info info, Kings kings, Move move)
{
	if(!move_inside_board(move)) return false;

	// This function should check:
	// - the piece is allowed to move that way
	// - the move path is clear (except for the knight)
	if(!move_pseudo_legal(board, info, move)) return false;

	// This function should check if the inputted move prevents check.
	// It can do that by executing the move, and see if the king is in check
	if(!move_prevent_check(board, info, kings, move))
	{
		printf("(%d-%d) -> (%d-%d) not prevent check\n",
			POINT_RANK_MACRO(MOVE_START_MACRO(move)),
			POINT_FILE_MACRO(MOVE_START_MACRO(move)),
			POINT_RANK_MACRO(MOVE_STOP_MACRO(move)),
			POINT_FILE_MACRO(MOVE_STOP_MACRO(move)));

		return false;
	}



	return true;
}

// This function should check:
// - the piece is allowed to move that way
// - the move path is clear (except for the knight)
bool move_pseudo_legal(const Piece board[], Info info, Move move)
{
	if(!move_inside_board(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Piece startPiece = board[startPoint];

	Piece startTeam = (startPiece & PIECE_TEAM_MASK);

	if(!current_team_move(info, startTeam)) return false;

	// This function checks:
	// - if the moving pattern and flag matches the piece
	if(!move_pattern_valid(move, startPiece)) return false;

	// This function checks:
	// - if the move can be done, if it has the ability (castling)
	if(!move_ability_valid(move, startPiece, info)) return false;

	// This function checks:
	// - if the move pattern fits on the board and iteracts with the pieces that it needs
	if(!move_pattern_fits(board, info, move)) return false;

	// This function checks:
	// - if the path between the start point and the stop point is clear
	if(!clear_moving_path(board, move, startPiece)) return false;

	return true;
}

// This function should check if the inputted move prevents check.
// It can do that by executing the move, and see if the king is in check
bool move_prevent_check(const Piece board[], Info info, Kings kings, Move move)
{
	if(!move_inside_board(move)) return false;


	Point startPoint = MOVE_START_MACRO(move);
	Piece pieceTeam = (board[startPoint] & PIECE_TEAM_MASK);


	Piece* boardCopy = malloc(sizeof(Piece) * BOARD_LENGTH);
	memcpy(boardCopy, board, sizeof(Piece) * BOARD_LENGTH);

	Info infoCopy = info;
	Kings kingsCopy = kings;

	if(!execute_chess_move(boardCopy, &infoCopy, &kingsCopy, move))
	{
		free(boardCopy);

		printf("if(!execute_chess_move(boardCopy, &infoCopy, &kingsCopy, move))\n");

		return false;
	}


	Point kingPoint = POINT_NONE;

	if(pieceTeam == PIECE_TEAM_WHITE)
	{
		printf("white king!\n");
		kingPoint = KINGS_WHITE_MACRO(kingsCopy);
	}

	else if(pieceTeam == PIECE_TEAM_BLACK)
	{
		printf("black king!\n");
		kingPoint = KINGS_BLACK_MACRO(kingsCopy);
		printf("King Point: (%d-%d)\n", POINT_RANK_MACRO(kingPoint), POINT_FILE_MACRO(kingPoint));
	}


	printf("startTeam: %d\tstopTeam: %d\n", (board[startPoint] & PIECE_TEAM_MASK), (board[MOVE_STOP_MACRO(move)] & PIECE_TEAM_MASK));



	if(king_inside_check(boardCopy, infoCopy, kingPoint))
	{
		free(boardCopy);

		printf("king_inside_check\n");

		return false;
	}

	printf("not king_inside_check\n");


	free(boardCopy);

	return true;
}

bool clear_moving_path(const Piece board[], Move move, Piece piece)
{
	if(!move_inside_board(move)) return false;

	//Piece pieceTeam = PIECE_TEAM_MACRO(piece);
	Piece pieceType = PIECE_TYPE_MACRO(piece);

	if(pieceType == PIECE_TYPE_KNIGHT) return true;


	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	unsigned short startRank = POINT_RANK_MACRO(startPoint);
	unsigned short startFile = POINT_FILE_MACRO(startPoint);

	unsigned short stopFile = POINT_FILE_MACRO(stopPoint);
	unsigned short stopRank = POINT_RANK_MACRO(stopPoint);

	signed short rankOffset = (stopRank - startRank);
	signed short fileOffset = (stopFile - startFile);

	unsigned short absRankOffset = ABS_SHORT_NUMBER(rankOffset);
	unsigned short absFileOffset = ABS_SHORT_NUMBER(fileOffset);

	// If both rank- and file-offset is 0, then its not moving
	if(absRankOffset == 0 && absFileOffset == 0) return false;

	// Either it can go straight (one is 0), or it can go diagonal (both the same)

	if( (absRankOffset != 0 && absFileOffset != 0) && absRankOffset != absFileOffset) return false;

	unsigned short moveSteps = (absRankOffset > absFileOffset) ? absRankOffset : absFileOffset;


	signed short rankFactor = (absRankOffset == 0) ? 0 : (rankOffset / absRankOffset);
	signed short fileFactor = (absFileOffset == 0) ? 0 : (fileOffset / absFileOffset);


	for(unsigned short index = 1; index < moveSteps; index = index + 1)
	{
		unsigned short currentFile = startFile + (index * fileFactor);
		unsigned short currentRank = startRank + (index * rankFactor);

		Point point = (currentFile << POINT_FILE_SHIFT) | (currentRank << POINT_RANK_SHIFT);

		Piece currentTeam = (board[point] & PIECE_TEAM_MASK);
		Piece currentType = (board[point] & PIECE_TYPE_MASK);

		if(currentType != PIECE_TYPE_NONE || currentTeam != PIECE_TEAM_NONE) return false;
	}

	return true;
}

bool move_ability_valid(Move move, Piece piece, Info info)
{
	if(!move_inside_board(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);


	Piece pieceTeam = (piece & PIECE_TEAM_MASK);


	signed short movePattern = (stopPoint - startPoint);



	Move moveFlag = move & MOVE_FLAG_MASK;


	if(moveFlag == MOVE_FLAG_CASTLE)
	{
		// If the move flag is saying that the move is a castle:
		// - we have to check if the ability at that side is valid



		Info castles = (info & INFO_CASTLES_MASK);


		if(pieceTeam == PIECE_TEAM_WHITE)
		{
			if(movePattern == KING_CASTLE_PAT)
			{
				if(!(castles & INFO_WHITE_KING)) return false;
			}
			else if(movePattern == QUEEN_CASTLE_PAT)
			{
				if(!(castles & INFO_WHITE_QUEEN)) return false;
			}
			else return false;
		}
		else if(pieceTeam == PIECE_TEAM_BLACK)
		{
			if(movePattern == KING_CASTLE_PAT)
			{
				if(!(castles & INFO_BLACK_KING)) return false;
			}
			else if(movePattern == QUEEN_CASTLE_PAT)
			{
				if(!(castles & INFO_BLACK_QUEEN)) return false;
			}
			else return false;
		}
		else return false;
	}

	return true;
}

bool current_team_move(Info info, Piece pieceTeam)
{
	unsigned short infoTeamValue = INFO_TEAM_MACRO(info);
	unsigned short pieceTeamValue = PIECE_TEAM_MACRO(pieceTeam);

	if(infoTeamValue == pieceTeamValue && pieceTeamValue != 0) return true;

	return false;
}

// This function is going to check if the move-pattern
// fits inside the board (pawn-takes, castling, pawn double jump)
// - the stop piece can't be of same team
// - the stop piece must be empty if the pawn moves forward
// - it must be a rook in the corner, if it is castle
bool move_pattern_fits(const Piece board[], Info info, Move move)
{
	if(!move_inside_board(move)) return false;

	Point startPoint = MOVE_START_MACRO(move);
	Point stopPoint = MOVE_STOP_MACRO(move);

	unsigned short stopFile = POINT_FILE_MACRO(stopPoint);

	unsigned short passantFile = INFO_PASSANT_MACRO(info);

	Piece startTeam = (board[startPoint] & PIECE_TEAM_MASK);
	Piece startType = (board[startPoint] & PIECE_TYPE_MASK);

	Piece stopTeam = (board[stopPoint] & PIECE_TEAM_MASK);


	unsigned short fileOffset = ABS_SHORT_NUMBER(move_file_offset(move, startTeam));
	signed short rankOffset = move_rank_offset(move, startTeam);


	Move moveFlag = (move & MOVE_FLAG_MASK);


	if(board_teams_team(startTeam, stopTeam)) return false;


	if(moveFlag == MOVE_FLAG_CASTLE)
	{
		// This checks if the king is the one moving, and if the rook is in its place
		return false; // just for now
	}

	if(startType == PIECE_TYPE_PAWN)
	{
		if(fileOffset == 0 && (rankOffset == 1 || rankOffset == 2))
		{
			if(!chess_piece_empty(board[stopPoint])) return false;
		}

		else if(fileOffset == 1 && rankOffset == 1)
		{
			if(moveFlag == MOVE_FLAG_PASSANT && (stopFile + 1) == passantFile)
			{
				// This is the exeption
			}
			else
			{
				if(!board_teams_enemy(startTeam, stopTeam)) return false;
			}
		}
	}

	return true;
}
