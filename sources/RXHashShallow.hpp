/*
 *  RXHashShallow.hpp
 *  Roxane
 *
 *  Created by B Causse on 28/03/06.
 *  Copyleft 2006 personnel.
 *
 */


#ifndef RXHASHSHALLOW_HPP
#define RXHASHSHALLOW_HPP

#include <string>

#include "RXHashTable.hpp"
#include "RXConstantes.hpp"
#include "RXBitBoard.hpp"
#include "RXMove.hpp"



class RXHashShallow {
	
	std::vector<RXHashEntry> table;
	unsigned long _maskTable;	
	
	unsigned char date;
	

	public : 
	
		RXHashShallow(unsigned int nBT);
		~RXHashShallow() {};

		void reset();
			
		bool get(const RXBitBoard& board, RXHashValue& entry) const;
		bool get(const unsigned long long hash_code, RXHashValue& entry) const;
		
		void update(const unsigned long long hash_code, const unsigned char depth, const int alpha, const int beta, const int score, const char move);
			
	void new_search(const int n_empties);

};

inline void RXHashShallow::new_search(const int n_empties) {
	
	int stage = 60-n_empties;
	
	if(stage>date)
		date = stage;
	
}


//implementation LockFree
inline bool RXHashShallow::get(const RXBitBoard& board, RXHashValue& value) const {
	
    const unsigned long long hash_code = board.hashcode();
    
	const RXHashEntry& entry = table[static_cast<unsigned int>(hash_code>>32) & _maskTable];
	
	unsigned long long packed = entry.deepest.packed;
	unsigned long long lock = entry.deepest.lock ^ packed;
	if (hash_code == lock) {
		
		value.compact_2_wide(packed);
		
		return true;
	}
	
	
	packed = entry.newest.packed;
	lock = entry.newest.lock ^ packed;
	if (hash_code == lock) {
		
		value.compact_2_wide(packed);
		
		return true;
	}
	
	return false;
	
}

inline bool RXHashShallow::get(const unsigned long long hash_code, RXHashValue& value) const {
		
	
	const RXHashEntry& entry = table[static_cast<unsigned int>(hash_code>>32) & _maskTable];
	
	unsigned long long packed = entry.deepest.packed;
	unsigned long long lock = entry.deepest.lock ^ packed;
	if (hash_code == lock) {
		
		value.compact_2_wide(packed);
		
		return true;
	}
	
	
	packed = entry.newest.packed;
	lock = entry.newest.lock ^ packed;
	if (hash_code == lock) {
		
		value.compact_2_wide(packed);
		
		return true;
	}
	
	return false;
	
}

								  

#endif
