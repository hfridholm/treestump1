
#include "../Header-Files-Folder/engine-include-file.h"

const signed short PIECE_MATRIX[7][8][8] =
{
	{ // Matrix for "EMPTY"
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
	},
	{ // Matrix for "PAWN"
		{0, 0, 0, 0, 0, 0, 0, 0},
		{50, 50, 50, 50, 50, 50, 50, 50},
		{10, 10, 20, 30, 30, 20, 10, 10},
		{5, 5, 10, 27, 27, 10, 5, 5},
		{0, 0, 0, 25, 25, 0, 0, 0},
		{5, -5, -10, 0, 0, -10, -5, 5},
		{5, 10, 10, -25, -25, 10, 10, 5},
		{0, 0, 0, 0, 0, 0, 0, 0}
	},
	{ // Matrix for "BISHOP"
		{-20, -10, -10, -10, -10, -10, -10, -20},
		{-10, 0, 0, 0, 0, 0, 0, -10},
		{-10, 0, 5, 10, 10, 5, 0, -10},
		{-10, 5, 5, 10, 10, 5, 5, -10},
		{-10, 0, 10, 10, 10, 10, 0, -10},
		{-10, 10, 10, 10, 10, 10, 10, -10},
		{-10, 5, 0, 0, 0, 0, 5, -10},
		{-20, -10, -10, -10, -10, -10, -10, -20}
	},
	{ // Matrix for "KNIGHT"
		{-50, -40, -30, -30, -30, -30, -40, -50},
		{-40, -20, 0, 0, 0, 0, -20, -40},
		{-30, 0, 10, 15, 15, 10, 0, -30},
		{-30, 5, 15, 20, 20, 15, 5, -30},
		{-30, 0, 15, 20, 20, 15, 0, -30},
		{-30, 5, 10, 15, 15, 10, 5, -30},
		{-40, -20, 0, 5, 5, 0, -20, -40},
		{-50, -40, -30, -30, -30, -30, -40, -50}
	},
	{ // Matrix for "ROOK"
		{0, 0, 0, 0, 0, 0, 0, 0},
		{5, 10, 10, 10, 10, 10, 10, 5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{0, 0, 0, 5, 5, 0, 0, 0}
	},
	{ // Matrix for "QUEEN"
		{-20, -10, -10, -5, -5, -10, -10, -20},
		{-10, 0, 0, 0, 0, 0, 0, -10},
		{-10, 0, 5, 5, 5, 5, 0, -10},
		{-5, 0, 5, 5, 5, 5, 0, -5},
		{0, 0, 5, 5, 5, 5, 0, -5},
		{-10, 5, 5, 5, 5, 5, 0, -10},
		{-10, 0, 5, 0, 0, 0, 0, -10},
		{-20, -10, -10, -5, -5, -10, -10, -20}
	},
	{ // Matrix for "KING"
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
	}
};

const signed short PIECE_VALUES[] = {+0, +10, +30, +30, +50, +90, +900};
