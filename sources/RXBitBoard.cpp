/*
 *  RXBitBoard.cpp
 *  Roxane
 *
 *  Created by Bruno Causse on 27/06/05.
 *  Copyright 2005 personnel. All rights reserved.
 *
 */

#include "RXBitBoard.hpp"
#include "RXEvaluation.hpp"
#include <cstddef> // define NULL
#include <iomanip>

const unsigned long long RXBitBoard::NEIGHBOR[] = { 
 0X0000000000000302ULL, 0X0000000000000604ULL, 0X0000000000000E0AULL, 0X0000000000001C14ULL, 0X0000000000003828ULL, 0X0000000000007050ULL, 0X0000000000006020ULL, 0X000000000000C040ULL,
 0X0000000000030200ULL, 0X0000000000060400ULL, 0X00000000000E0A00ULL, 0X00000000001C1400ULL, 0X0000000000382800ULL, 0X0000000000705000ULL, 0X0000000000602000ULL, 0X0000000000C04000ULL,
 0X0000000003020300ULL, 0X0000000006040600ULL, 0X000000000E0A0E00ULL, 0X000000001C141C00ULL, 0X0000000038283800ULL, 0X0000000070507000ULL, 0X0000000060206000ULL, 0X00000000C040C000ULL,
 0X0000000302030000ULL, 0X0000000604060000ULL, 0X0000000E0A0E0000ULL, 0X0000001C141C0000ULL, 0X0000003828380000ULL, 0X0000007050700000ULL, 0X0000006020600000ULL, 0X000000C040C00000ULL,
 0X0000030203000000ULL, 0X0000060406000000ULL, 0X00000E0A0E000000ULL, 0X00001C141C000000ULL, 0X0000382838000000ULL, 0X0000705070000000ULL, 0X0000602060000000ULL, 0X0000C040C0000000ULL,
 0X0003020300000000ULL, 0X0006040600000000ULL, 0X000E0A0E00000000ULL, 0X001C141C00000000ULL, 0X0038283800000000ULL, 0X0070507000000000ULL, 0X0060206000000000ULL, 0X00C040C000000000ULL,
 0X0002030000000000ULL, 0X0004060000000000ULL, 0X000A0E0000000000ULL, 0X00141C0000000000ULL, 0X0028380000000000ULL, 0X0050700000000000ULL, 0X0020600000000000ULL, 0X0040C00000000000ULL,
 0X0203000000000000ULL, 0X0406000000000000ULL, 0X0A0E000000000000ULL, 0X141C000000000000ULL, 0X2838000000000000ULL, 0X5070000000000000ULL, 0X2060000000000000ULL, 0X40C0000000000000ULL
};

const unsigned long long RXBitBoard::PRESORTED_POSITION_BITS[] = {
    0X8000000000000000ULL, 0X0000000000000080ULL, 0X0100000000000000ULL, 0X0000000000000001ULL, //corner
    0X0000800000000000ULL, 0X0000000000800000ULL, 0X2000000000000000ULL, 0X0000000000000020ULL, //A
    0X0400000000000000ULL, 0X0000000000000004ULL, 0X0000010000000000ULL, 0X0000000000010000ULL, //A
    0X0000200000000000ULL, 0X0000000000200000ULL, 0X0000040000000000ULL, 0X0000000000040000ULL, //D
    0X0000008000000000ULL, 0X0000000080000000ULL, 0X1000000000000000ULL, 0X0000000000000010ULL, //B
    0X0800000000000000ULL, 0X0000000000000008ULL, 0X0000000100000000ULL, 0X0000000001000000ULL, //B
    0X0000002000000000ULL, 0X0000000020000000ULL, 0X0000100000000000ULL, 0X0000000000100000ULL, //E
    0X0000080000000000ULL, 0X0000000000080000ULL, 0X0000000400000000ULL, 0X0000000004000000ULL, //E
    0X0000004000000000ULL, 0X0000000040000000ULL, 0X0010000000000000ULL, 0X0000000000001000ULL, //G
    0X0008000000000000ULL, 0X0000000000000800ULL, 0X0000000200000000ULL, 0X0000000002000000ULL, //G
    0X0000400000000000ULL, 0X0000000000400000ULL, 0X0020000000000000ULL, 0X0000000000002000ULL, //F
    0X0004000000000000ULL, 0X0000000000000400ULL, 0X0000020000000000ULL, 0X0000000000020000ULL, //F
    0X0080000000000000ULL, 0X0000000000008000ULL, 0X4000000000000000ULL, 0X0000000000000040ULL, //C
    0X0200000000000000ULL, 0X0000000000000002ULL, 0X0001000000000000ULL, 0X0000000000000100ULL, //C
    0X0040000000000000ULL, 0X0000000000004000ULL, 0X0002000000000000ULL, 0X0000000000000200ULL, //X
    0x0000000000000000ULL, 0x0000000000000000ULL                                                // PASS & NOMOVE
};



/* order JWC */

const int RXBitBoard::PRESORTED_POSITION[] = {
	A1, A8, H1, H8,						// Corner
	A3, A6, C1, C8, F1, F8, H3, H6,		// A 
	C3, C6, F3, F6,						// D
	A4, A5, D1, D8, E1, E8, H4, H5,		// B
	C4, C5, D3, D6, E3, E6, F4, F5,		// E
	B4, B5, D2, D7, E2, E7, G4, G5,		// G
	B3, B6, C2, C7, F2, F7, G3, G6,		// F
	A2, A7, B1, B8, G1, G8, H2, H7,		// C
	B2, B7, G2, G7						// X
};


/* order Nicolet */
/*
const int RXBitBoard::PRESORTED_POSITION[] = {
	A1, A8, H1, H8,						// Corner
	C4, C5, D3, D6, E3, E6, F4, F5,		// E
	C3, C6, F3, F6,						// D
	A4, A5, D1, D8, E1, E8, H4, H5,		// B
	B4, B5, D2, D7, E2, E7, G4, G5,		// G
	A3, A6, C1, C8, F1, F8, H3, H6,		// A 
	B3, B6, C2, C7, F2, F7, G3, G6,		// F
	A2, A7, B1, B8, G1, G8, H2, H7,		// C
	B2, B7, G2, G7						// X
};
*/

const unsigned long long RXBitBoard::QUADRANT_MASK[] = {
    0x000000000F0F0F0FULL,
    0x00000000F0F0F0F0ULL,
    0x0F0F0F0F00000000ULL,
    0xF0F0F0F000000000ULL   
};

/*! a quadrant id for each square */
const int RXBitBoard::QUADRANT_ID[] = {
	0, 0, 0, 0, 1, 1, 1, 1,
	0, 0, 0, 0, 1, 1, 1, 1,
	0, 0, 0, 0, 1, 1, 1, 1,
	0, 0, 0, 0, 1, 1, 1, 1,
	2, 2, 2, 2, 3, 3, 3, 3,
	2, 2, 2, 2, 3, 3, 3, 3,
	2, 2, 2, 2, 3, 3, 3, 3,
	2, 2, 2, 2, 3, 3, 3, 3
};


RXBitBoard::RXBitBoard(): player(BLACK), n_empties(64), hash_code(0), n_nodes(0) {
	
	discs[BLACK] = 0;
	discs[WHITE] = 0;

	//n_discs[BLACK] = 0; 
	//n_discs[WHITE] = 0;
			
	set_disc(D4, WHITE);
	set_disc(E4, BLACK);
	set_disc(D5, BLACK);
	set_disc(E5, WHITE);
	
	/* create emptiesList */
	RXSquareList* iEmpties = empties_list;	//empties[0]
	iEmpties->position = NOMOVE;			//sentinel
	iEmpties->previous = NULL;				//NULL
	iEmpties->next = iEmpties + 1;
	iEmpties = iEmpties->next;
	
	for(int i = 0; i<60; i++) {
		if(((discs[BLACK] | discs[WHITE]) & (1LL<<PRESORTED_POSITION[i])) == 0) {
			iEmpties->position = PRESORTED_POSITION[i];
			iEmpties->previous = iEmpties - 1;
			iEmpties->next = iEmpties + 1 ;
		
			position_to_empties[PRESORTED_POSITION[i]] = iEmpties;
			iEmpties = iEmpties->next;
		}
	}
	iEmpties->position = NOMOVE;			//sentinel
	iEmpties->previous = iEmpties - 1; 
	iEmpties->next = 0;						//NULL
		
	init_generate_flips();
	init_generate_move();

}

RXBitBoard::RXBitBoard(const RXBitBoard& src) {
	
	discs[BLACK] = src.discs[BLACK];
	discs[WHITE] = src.discs[WHITE];
	
	//n_discs[BLACK] = src.n_discs[BLACK]; 
	//n_discs[WHITE] = src.n_discs[WHITE];

	player = src.player;
	n_empties = src.n_empties;
	hash_code = src.hash_code;
	n_nodes = src.n_nodes;
	
	/* create emptiesList */
	RXSquareList* iEmpties = empties_list;	//empties[0]
	iEmpties->position = NOMOVE;			//sentinel
	iEmpties->previous = NULL;				//NULL
	iEmpties->next = iEmpties + 1;
	iEmpties = iEmpties->next;
	
	for(int i = 0; i<60; i++) {
		if(((discs[BLACK] | discs[WHITE]) & (1LL<<PRESORTED_POSITION[i])) == 0) {
			iEmpties->position = PRESORTED_POSITION[i];
			iEmpties->previous = iEmpties - 1;
			iEmpties->next = iEmpties + 1 ;
			
			position_to_empties[PRESORTED_POSITION[i]] = iEmpties;
			iEmpties = iEmpties->next;
		}
	}
	iEmpties->position = NOMOVE;			//sentinel
	iEmpties->previous = iEmpties - 1; 
	iEmpties->next = 0;						//NULL
	
	/*BE CAREFULL*/
	/*copy actual empties list */
	RXSquareList* previous = empties_list;
	for(RXSquareList* empties = src.empties_list->next; empties->position != NOMOVE; empties = empties->next) {
		RXSquareList* empty = position_to_empties[empties->position];
		empty->previous = previous;
		previous->next = empty;
		previous = previous->next;
	}
	empties_list[61].previous = previous;
	previous->next = &empties_list[61];
	
		
	
	init_generate_flips();
	init_generate_move();
}




RXBitBoard& RXBitBoard::operator=(const RXBitBoard& src) {

	if(this != &src) {
	
		discs[BLACK] = src.discs[BLACK];
		discs[WHITE] = src.discs[WHITE];
		
		player = src.player;
				
		n_empties = src.n_empties;
		
		hash_code = src.hash_code;

		RXSquareList* previous = empties_list;
		for(RXSquareList* empties = src.empties_list->next; empties->position != NOMOVE; empties = empties->next) {
			RXSquareList* empty = position_to_empties[empties->position];
			empty->previous = previous;
			previous->next = empty;
			previous = previous->next;
		}
		empties_list[61].previous = previous;
		previous->next = &empties_list[61];
		
		
		n_nodes = src.n_nodes;
		
	}
	
	return *this;
}

void RXBitBoard::build(const std::string& init) {
    
	discs[BLACK] = discs[WHITE] = 0LL;
	//n_discs[BLACK] = n_discs[WHITE] = 0;
	hash_code = 0;
	
	n_empties = 64;
	
	player = UNDEF;

	int id = 0;
	for (int i = A1; i >= H8; i--) {
		
		switch (std::tolower(init[id])) {
			case 'b':
			case 'x':
			case '*':
				set_disc(i, BLACK);
				break;
			case 'o':
			case 'w':
				set_disc(i, WHITE);
				break;
			case '-':
			case '.':
				break;
			case ' ':
			case '[':
				i++;
				break;
			default:
				std::cerr << "RXBoard::build incorrect board" << std::endl;
				exit(EXIT_FAILURE);
			}
		id++;
	}

	for(;id<init.length() && player == UNDEF; id++)
		switch (std::tolower(init[id])) {
			case 'b':
			case 'x':
			case '*':
				player = BLACK;
				break;
			case 'o':
			case 'w':
				player = WHITE;
				break;
			default:
				break;
		}
	
	if((n_empties%2 == BLACK && player == WHITE) || (n_empties%2 == WHITE && player == BLACK))
		hash_code ^= 0xBB20B460D4D95138ULL;
		
	if(player == UNDEF) {
		std::cerr<< "RXBoard::build incorrect player value" << std::endl;
		exit(EXIT_FAILURE);
	}

	RXSquareList* previous = empties_list;
	for(int id = 0; id<60; id++) {
		if(((discs[BLACK] | discs[WHITE]) & (1ULL<<PRESORTED_POSITION[id])) == 0) {
			RXSquareList* empty = position_to_empties[PRESORTED_POSITION[id]];
			empty->previous = previous;
			previous->next = empty;
			previous = previous->next;
		}
	}
	empties_list[61].previous = previous;
	previous->next = &empties_list[61];
	

}

std::ostream& operator<<(std::ostream& os, RXBitBoard& board) {

	os << "\n  A B C D E F G H " << std::endl;
	for(int iLine = 1; iLine<=8; iLine++) {
		os << iLine << " ";
		for(int iPosition = (9-iLine)*8 - 1; iPosition>(8-iLine)*8-1; iPosition--) {
			unsigned long long _mask = 1ULL<<iPosition;
			if((board.discs[BLACK] & _mask) != 0) {
					os << "# ";
			} else if((board.discs[WHITE] & _mask) !=0) {
					os << "O ";
			} else {
					os << ". ";
			}
			
		}
		os << iLine;
		if(iLine == 4)
			os << "\tNoirs: " << __builtin_popcountll(board.discs[BLACK]) << "\tBlancs: " << __builtin_popcountll(board.discs[WHITE]);
		if(iLine == 5)
			os << "\t" << (board.player == WHITE ? "BLANCS" : "NOIRS") << " au trait";

		os << std::endl;
	}
	os << "  A B C D E F G H \n" << std::endl;
	
	return os;

}

bool RXBitBoard::squareIsEmpty(const int position) const {
	if((discs[BLACK] | discs[WHITE]) & 1ULL<<position)
		return false;
	return true;
}



bool RXBitBoard::isPassed() {	
	if(get_mobility(discs[player], discs[player^1]) != 0)
		return false;
			
	return true;
}

bool RXBitBoard::isEndGame() {
	if(isPassed()) {
		player ^= 1;
		if(isPassed()) {
			player ^= 1;
			return true;
		}
		player ^= 1;
	}
	return false;
}

int RXBitBoard::local_Parity(const int position) const {
    
    const unsigned long long quadrant_Filled = (discs[BLACK] | discs[WHITE]) & QUADRANT_MASK[QUADRANT_ID[position]];
    
    return static_cast<int>(__builtin_popcountll(quadrant_Filled) & 0x00000000000001ULL);
}



int RXBitBoard::final_score() const {
	int score = __builtin_popcountll(discs[player])-__builtin_popcountll(discs[player^1]);
	if(score<0)
		score -= n_empties;
	else if(score>0)
		score += n_empties;
		
	return score*VALUE_DISC;
}

int RXBitBoard::final_score_1 () const {
	int score = 63-2*__builtin_popcountll(discs[player^1]);
	
	int pos = empties_list->next->position;
	int nFlips;
	
	if((nFlips = count_flips[pos](discs[player]))>0) {
		score += nFlips+1;
	} else if((nFlips = count_flips[pos](discs[player^1]))>0) {
		score -= nFlips+1;
	} else if(score<0)
		score--;
	else if (score>0)
		score++;
	
	return score*VALUE_DISC;
}

std::string RXBitBoard::cassio_script() const {
	
	std::ostringstream buffer;
	
	for (int square=A1; square>=H8; square--) {
		unsigned long long mask = 0x1ULL<<square;
		if (discs[BLACK] & mask)
			buffer << 'X';
		else if (discs[WHITE] & mask)
			buffer << 'O';
		else 
			buffer << '-';
	}
	
	if (player == BLACK)
		buffer << "X";
	else 
		buffer << "O";
	
	return buffer.str();
}



/* DEBUG */
void RXBitBoard::print_empties_list() const {
	std::cout << "emptiesList";
	for(RXSquareList *empties = empties_list->next; empties->position != NOMOVE; empties = empties->next)
		std::cout << " : " << RXMove::index_to_coord(empties->position);
	std::cout << std::endl;
}

void RXBitBoard::print_moves_list(RXMove* Moves) const {
    std::cout << "MovesList";
    for(; Moves->position != NULL; Moves = Moves->next)
        std::cout << " : " << RXMove::index_to_coord(Moves->position);
    std::cout << std::endl;
}

void RXBitBoard::print_64bits(unsigned long long n) {

	std::cout << "\n  A B C D E F G H " << std::endl;
	for(int iLine = 1; iLine<=8; iLine++) {
		std::cout  << iLine << " ";
		for(int iPosition = (9-iLine)*8 - 1; iPosition>(8-iLine)*8-1; iPosition--) {
			unsigned long long _mask = 1ULL<<iPosition;
			if((n & _mask) != 0) {
					std::cout  << "@ ";
			} else {
					std::cout  << ". ";
			}
			
		}
		std::cout  << iLine << std::endl;
	}
	std::cout << "  A B C D E F G H \n" << std::endl;
		
}

void RXBitBoard::print_Board() {

    std::cout << "\n  A B C D E F G H " << std::endl;
    for(int iLine = 1; iLine<=8; iLine++) {
        std::cout << iLine << " ";
        for(int iPosition = (9-iLine)*8 - 1; iPosition>(8-iLine)*8-1; iPosition--) {
            unsigned long long _mask = 1ULL<<iPosition;
            if((discs[BLACK] & _mask) != 0) {
                std::cout << "# ";
            } else if((discs[WHITE] & _mask) !=0) {
                std::cout << "O ";
            } else {
                std::cout << ". ";
            }
            
        }
        std::cout << iLine;
        if(iLine == 4)
            std::cout << "\tNoirs: " << __builtin_popcountll(discs[BLACK]) << "\tBlancs: " << __builtin_popcountll(discs[WHITE]);
        if(iLine == 5)
            std::cout << "\t" << (player == WHITE ? "BLANCS" : "NOIRS") << " au trait";

        std::cout << std::endl;
    }
    std::cout << "  A B C D E F G H \n" << std::endl;
    

}



/*
unsigned long long RXBitBoard::cntbset(unsigned long long n) {

	unsigned long long mobility;
	
	mobility = ((n          >>  1) & 0x5555555555555555ULL) + (n          & 0x5555555555555555ULL);
	mobility = ((mobility	>>  2) & 0x3333333333333333ULL) + (mobility   & 0x3333333333333333ULL);
	mobility = ((mobility	>>  4) & 0x0F0F0F0F0F0F0F0FULL) + (mobility   & 0x0F0F0F0F0F0F0F0FULL);
	mobility = ((mobility	>>  8) & 0x00FF00FF00FF00FFULL) + (mobility   & 0x00FF00FF00FF00FFULL);
	mobility = ((mobility	>> 16) & 0x0000FFFF0000FFFFULL) + (mobility   & 0x0000FFFF0000FFFFULL);
	mobility = ((mobility	>> 32) & 0x00000000FFFFFFFFULL) + (mobility   & 0x00000000FFFFFFFFULL);

	return mobility;
}
 


void RXBitBoard::build(const unsigned long long discs_player, const unsigned long long discs_opp, const int color) {
	discs[color] = discs_player;
	discs[color^1] = discs_opp;
	player = color;
}
 
*/
