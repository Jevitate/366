//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "common.hpp"
#include "Server.hpp"
#include <fstream>
#include <iostream>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>


#include <string>
#include <streambuf>


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
    //return 2;
    //read in file and check x and y lengths to make sure they are square. Then return the length.
}

char board_1_array[BOARD_SIZE][BOARD_SIZE];
char board_2_array[BOARD_SIZE][BOARD_SIZE];

char BitBoard1[BOARD_SIZE][BOARD_SIZE];
char BitBoard2[BOARD_SIZE][BOARD_SIZE];

Server::~Server() {
  //Deallocate Memory
  //Don't Touch
}

BitArray2D *Server::scan_setup_board(string setup_board_name){

  //ifstream board_start;
  //board_start.open("player_1.setup_board.txt");
  //&A[i][j] = Xa + L(C * i + j)
  p1_setup_board = new BitArray2D(BOARD_SIZE,BOARD_SIZE);
  p2_setup_board = new BitArray2D(BOARD_SIZE,BOARD_SIZE);

  for(int r = 0; r < BOARD_SIZE; r++){
    for(int c = 0; c < BOARD_SIZE; c++){
      //set up bit board array
      if(board_2_array[r][c] != '_'){
        //BitBoard1[r][c] = '1';
        p2_setup_board->set(r,c);
        //cout << p1_setup_board->get(r,c);
      }else{
        //BitBoard1[r][c] = '0';
        //cout << BitBoard1[r][c];
      }
      }
    //cout << "\n";
  }

}





void Server::initialize(unsigned int board_size,string p1_setup_board,string p2_setup_board){
    this -> board_size = board_size;
    //ifstream *ifs ((ifstream *) "player_1.set.setup_board.txt");
    //int file_length = get_file_length(ifs);
    //cout << file_length << "\n";

    if(board_size != BOARD_SIZE){
        //__throw_bad_exception();
        throw ServerException("Wrong");

    }


    if(p1_setup_board != "player_1.setup_board.txt" or p2_setup_board != "player_2.setup_board.txt"){
        throw ServerException("Bad Player Board");
        //__throw_bad_exception();
    }

    ifstream board_start;
    board_start.open("player_1.setup_board.txt");

    for(int r = 0; r < BOARD_SIZE; r++){
        for(int c = 0; c < BOARD_SIZE; c++){
            board_start >> board_1_array[r][c];
            //cout << board_1_array[r][c];
        }
        //cout << "\n";
    }
    board_start.close();

    ifstream board_start2;
    board_start2.open("player_2.setup_board.txt");

    for(int r = 0; r < BOARD_SIZE; r++){
        for(int c = 0; c < BOARD_SIZE; c++){
            board_start2 >> board_2_array[r][c];
            //cout << board_2_array[r][c];
        }
        //cout << "\n";
    }
    board_start2.close();



    scan_setup_board("sometin");
    //scan_setup_board("player_2.setup_board.txt");

}

int player_result;

int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    //Out of bounds = 0
    //Miss = -1
    //Hit = 1
    // X are the columns, Y are the Rows, Array is Row by Columns
    if(player > 2 || player < 1){
        throw ServerException("Bad player number");
        //__throw_bad_exception();
    }


    if(x >= BOARD_SIZE || y >= BOARD_SIZE){
        return OUT_OF_BOUNDS;
    }
    if(player == 1){
      if(p2_setup_board->get(y,x) == 0){
        return MISS;
      }
      else{
        return HIT;
      }
    }
//    if(player == 1) {
//        if (board_2_array[y][x] == '_') {
//            return MISS;
//        }
//        else{
//            return HIT;
//        }
//        //if(board_2_array[y][x] != '_'){
//
//        //}
//
//    }

}


int Server::process_shot(unsigned int player) {

    int x;
    int y;

    if(player > 2 || player < 1){
        throw ServerException("Bad player Number");
        //__throw_bad_exception();
    }

    ifstream shot_file("player_1.shot.json");
    cereal::JSONInputArchive arch(shot_file);
    arch(x,y);
    shot_file.close();
    //cout << "\n\n" << x << '\n' << y << '\n' << '\n';
    int result = evaluate_shot(player,x,y);
    //cout << "\n\n" << result << "\n\n";
    //remove("player1.result.json");
    ofstream out_file("player_1.result.json");
    cereal::JSONOutputArchive archiveOut(out_file);
    archiveOut(CEREAL_NVP(result));

    remove("player_1.shot.json");
    return NO_SHOT_FILE;
}