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
#include "Client.hpp"
#include <vector>

Client::~Client() {
}

char action_board_1[BOARD_SIZE][BOARD_SIZE];
char action_board_2[BOARD_SIZE][BOARD_SIZE];

void Client::initialize(unsigned int player, unsigned int board_size){

    vector<vector<int> > vec(BOARD_SIZE, vector<int> (BOARD_SIZE,0));

    // serialize the array
    ofstream array_ofp("player_1.action_board.json"); // create an output file stream
    cereal::JSONOutputArchive write_archive(array_ofp); // initialize an archive on the file
    write_archive(cereal::make_nvp("board", vec)); // serialize the data giving it a name

    if(player < 1 || player > 2){
        throw ClientException("Bad Player Number");
    } else  initialized = true;

}


void Client::fire(unsigned int x, unsigned int y) {

    ofstream out_file("player_1.shot.json");
    cereal::JSONOutputArchive archive_Out(out_file);
    archive_Out(CEREAL_NVP(x),CEREAL_NVP(y));

}


bool Client::result_available() {
}


int Client::get_result() {

    int result;

    ifstream in_file("player_1.result.json");
    cereal::JSONInputArchive archive_in(in_file);
    archive_in(result);

    remove("player_1.result.json");

    if(result < -1 or result > 1){
        throw ClientException("Bad Result from file");
    }


    return result;
}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {

    vector<vector<int> > vect(BOARD_SIZE, vector<int> (BOARD_SIZE,0));

    vect[y][x] = result;

    // serialize the array
    ofstream array_ofp("player_1.action_board.json"); // create an output file stream
    cereal::JSONOutputArchive write_archive(array_ofp); // initialize an archive on the file
    write_archive(cereal::make_nvp("board", vect)); // serialize the data giving it a name



}


string Client::render_action_board(){
}