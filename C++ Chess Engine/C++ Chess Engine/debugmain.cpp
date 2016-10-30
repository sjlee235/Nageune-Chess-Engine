#include <stdio.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <array>
#include "board.h"
#include "movegen.h"
#include "timer.h"
#include "evaluation.h"
#include "pgn.h"

#include "debug.h"
#include "command.h"

/******************************************************************************/
/*                                   DEBUG                                    */
/******************************************************************************/
void main() {
     Board initialBoard;
     
     printf("--------------------------------------------------------------------------------\n");
     printf(" Board120Setup / FENBoardSetup Testing                                          \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");

     FENboardSetup(initialBoard, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
     boardToFEN(initialBoard);

     board120Setup(initialBoard);
     boardToFEN(initialBoard);


     printf("\n");
     printf("--------------------------------------------------------------------------------\n");
     printf(" MoveGen Testing                                                                \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");
     
     MoveList moveList = moveGeneration(initialBoard);

     printf("Movecount: %d\n", moveList.getCounter());
     for (int i = 0; i < moveList.getCounter(); i++) {
          printf("%2d  ", i + 1);
          std::cout << numberToFilerank(moveList.getMove(i).getInitial())
               << numberToFilerank(moveList.getMove(i).getTerminal()) << std::endl;
     }

     printf("\n");
     printf("--------------------------------------------------------------------------------\n");
     printf(" Perft Testing                                                                  \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");

     printf("Perft (Depth %d): %llu\n", 1, divide(1, 0, initialBoard, false));
     printf("Perft (Depth %d): %llu\n", 2, divide(2, 0, initialBoard, false));
     printf("Perft (Depth %d): %llu\n", 3, divide(3, 0, initialBoard, false));
     printf("Perft (Depth %d): %llu\n", 4, divide(4, 0, initialBoard, false));

     printf("\n");
     printf("--------------------------------------------------------------------------------\n");
     printf(" Evaluation Testing                                                             \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");

     // TODO: Include this to FENboardsetup / Board120Setup
     initialBoard.updatePieceCount();
     printf("Initial Board Evaluation: %d\n", initialBoard.boardEvaluation());

     printf("\n");
     printf("--------------------------------------------------------------------------------\n");
     printf(" MakeMove / Evaluation Testing                                                  \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");
     
     Board copiedInitBoard;

     for (int i = 0; i < moveList.getCounter(); i++) {
          copiedInitBoard = initialBoard;
          printf("%2d  ", i + 1);
          std::cout << numberToFilerank(moveList.getMove(i).getInitial())
                    << numberToFilerank(moveList.getMove(i).getTerminal());
          int capturedPiece = makeMove(copiedInitBoard, moveList.getMove(i));
          printf("  %4d\n", copiedInitBoard.boardEvaluation());
     }

     printf("\n");
     printf("--------------------------------------------------------------------------------\n");
     printf(" Depth 1 Alphabeta Testing                                                      \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");

     Board savedBoard[MAX_MOVENUMBER];
     int saveIndex = 0;

     Move bestMoves1[MAX_DEPTH];
     int bestMoveScore1 = rootAlphabeta(1, initialBoard, DEFAULT_ALPHA, DEFAULT_BETA, bestMoves1, savedBoard, saveIndex);
     printf("Best Move Score: %3d\n", bestMoveScore1);
     std::cout << "Best Moves: ";
     for (int i = 1; i >= 1; i--) {
          std::cout << numberToFilerank(bestMoves1[i].getInitial())
               << numberToFilerank(bestMoves1[i].getTerminal())
               << " ";
     }
     printf("\n");

     printf("\n");
     printf("--------------------------------------------------------------------------------\n");
     printf(" Depth 2 Alphabeta Testing                                                      \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");

     Move bestMoves2[MAX_DEPTH];
     int bestMoveScore2 = rootAlphabeta(2, initialBoard, DEFAULT_ALPHA, DEFAULT_BETA, bestMoves2, savedBoard, saveIndex);
     printf("Best Move Score: %3d\n", bestMoveScore2);
     std::cout << "Best Moves: ";
     for (int i = 2; i >= 1; i--) {
          std::cout << numberToFilerank(bestMoves2[i].getInitial())
               << numberToFilerank(bestMoves2[i].getTerminal())
               << " ";
     }
     printf("\n");

     
     printf("\n");
     printf("--------------------------------------------------------------------------------\n");
     printf(" Depth 3 Alphabeta Testing                                                      \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");

     Move bestMoves3[MAX_DEPTH];
     int bestMoveScore3 = rootAlphabeta(3, initialBoard, DEFAULT_ALPHA, DEFAULT_BETA, bestMoves3, savedBoard, saveIndex);
     printf("Best Move Score: %3d\n", bestMoveScore3);
     std::cout << "Best Moves: ";
     for (int i = 3; i >= 1; i--) {
          std::cout << numberToFilerank(bestMoves3[i].getInitial())
               << numberToFilerank(bestMoves3[i].getTerminal())
               << " ";
     }
     printf("\n");

     printf("\n");
     printf("--------------------------------------------------------------------------------\n");
     printf(" Depth 4 Alphabeta Testing                                                      \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");

     Move bestMoves4[MAX_DEPTH];
     int bestMoveScore4 = rootAlphabeta(4, initialBoard, DEFAULT_ALPHA, DEFAULT_BETA, bestMoves4, savedBoard, saveIndex);
     printf("Best Move Score: %3d\n", bestMoveScore4);
     std::cout << "Best Moves: ";
     for (int i = 4; i >= 1; i--) {
          std::cout << numberToFilerank(bestMoves4[i].getInitial())
               << numberToFilerank(bestMoves4[i].getTerminal())
               << " ";
     }
     printf("\n");

     /*
     printf("\n");
     printf("--------------------------------------------------------------------------------\n");
     printf(" Depth 5 Alphabeta Testing                                                      \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");

     Move bestMoves5[MAX_DEPTH];
     int bestMoveScore5 = rootAlphabeta(5, initialBoard, DEFAULT_ALPHA, DEFAULT_BETA, bestMoves5, savedBoard, saveIndex);
     printf("Best Move Score: %3d\n", bestMoveScore5);
     std::cout << "Best Moves: ";
     for (int i = 5; i >= 1; i--) {
          std::cout << numberToFilerank(bestMoves5[i].getInitial())
               << numberToFilerank(bestMoves5[i].getTerminal())
               << " ";
     }
     printf("\n");
     */

     printf("\n");
     printf("--------------------------------------------------------------------------------\n");
     printf(" First 4 Moves with Depth 4                                                     \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");

     for (int i = 0; i < 4; i++) {
          Move bestMoves[MAX_DEPTH];
          int bestMoveScore = rootAlphabeta(4, initialBoard, DEFAULT_ALPHA, DEFAULT_BETA, bestMoves, savedBoard, saveIndex);
          printf("Best Move Score: %3d\n", bestMoveScore);
          std::cout << "Best Moves: ";
          for (int j = 4; j >= 1; j--) {
               std::cout << numberToFilerank(bestMoves[j].getInitial())
                    << numberToFilerank(bestMoves[j].getTerminal())
                    << " ";
          }
          printf("\n");
          makeMove(initialBoard, bestMoves[4]);
     }

     printf("\n");
     printf("--------------------------------------------------------------------------------\n");
     printf(" Stalemate Test 1: No Legal Move                                                \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");
     
     Board stalemateboard1;
     Board savedBoard2[MAX_MOVENUMBER];
     int saveIndex2 = 0;
     FENboardSetup(stalemateboard1, "6bk/5p1p/5P1P/8/8/8/8/4K3 b - - 0 1");
     printSimpleBoard(stalemateboard1);

     gameState stalemate1 = checkGameState(stalemateboard1, savedBoard2, saveIndex2);
     if (stalemate1 == STALEMATE_MOVE) {
          printf("\nCorrect stalemate detected.\n");
     }
     else {
          printf("\nStalemate test 1 failed!\n");
     }

     printf("\n");
     printf("--------------------------------------------------------------------------------\n");
     printf(" Stalemate Test 2: 50 Move Rule                                                 \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");

     Board stalemateboard2;
     FENboardSetup(stalemateboard2, "7k/pppppppp/8/8/8/8/PPPPPPPP/K7 w - - 100 1");
     printSimpleBoard(stalemateboard2);

     gameState stalemate2 = checkGameState(stalemateboard2, savedBoard2, saveIndex2);
     if (stalemate2 == STALEMATE_50) {
          printf("\nCorrect stalemate detected.\n");
     }
     else {
          printf("\nStalemate test 2 failed!\n");
     }

     printf("\n");
     printf("--------------------------------------------------------------------------------\n");
     printf(" Stalemate Test 3: 75 Nove Rule                                                 \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");

     Board stalemateboard3;
     FENboardSetup(stalemateboard3, "7k/pppppppp/8/8/8/8/PPPPPPPP/K7 w - - 150 1");
     printSimpleBoard(stalemateboard2);

     gameState stalemate3 = checkGameState(stalemateboard3, savedBoard2, saveIndex2);
     if (stalemate3 == STALEMATE_75) {
          printf("\nCorrect stalemate detected.\n");
     }
     else {
          printf("\nStalemate test 3 failed!\n");
     }

     printf("\n");
     printf("--------------------------------------------------------------------------------\n");
     printf(" Stalemate Test 4: Threefold Repetition                                         \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");

     Board stalemateboard4;
     Board savedBoard3[MAX_MOVENUMBER];
     int saveIndex3 = 3;
     FENboardSetup(stalemateboard4, "7k/pppppppp/8/8/8/8/PPPPPPPP/K7 w - - 0 1");

     savedBoard3[0] = stalemateboard4;
     savedBoard3[1] = stalemateboard4;
     savedBoard3[2] = stalemateboard4;

     gameState stalemate4 = checkGameState(stalemateboard4, savedBoard3, saveIndex3);
     if (stalemate4 == STALEMATE_3F) {
          printf("Correct stalemate detected.\n");
     }
     else {
          printf("Stalemate test 4 failed!\n");
     }

     printf("\n");
     printf("--------------------------------------------------------------------------------\n");
     printf(" Checkmate Test                                                                 \n");
     printf("--------------------------------------------------------------------------------\n");
     printf("\n");

     Board checkmateboard;
     Board savedBoard4[MAX_MOVENUMBER];
     int saveIndex4 = 0;
     FENboardSetup(checkmateboard, "R6k/R7/8/8/8/8/8/7K b - - 0 1");

     gameState checkmate = checkGameState(checkmateboard, savedBoard4, saveIndex4);
     if (checkmate == WHITE_CHECKMATE) {
          printf("Correct stalemate detected.\n");
     }
     else {
          printf("Checkmate test failed!\n");
     }
}