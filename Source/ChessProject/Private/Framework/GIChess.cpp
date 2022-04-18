// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GIChess.h"

bool UGIChess::GetChessPawnClass(const EPieceTypes Piece, TSubclassOf<AChessPiece>& ClassOut)

{
	if (const TSubclassOf<AChessPiece>* ClassPtr = ChessPawnClasses.Find(Piece))
	{
		ClassOut = *ClassPtr;
		return true;
	}
	return false;
}
