/*
 *  RXBBSetDisc.cpp
 *  Roxane
 *
 *  Created by Bruno Causse on 27/06/05.
 *  Copyright 2005 personnel. All rights reserved.
 *
 */

#include "RXBitBoard.h"

void RXBitBoard::set_disc(const int position, const int color) {


	switch (position) {

		case A1:

			discs[color] |= 0X8000000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0XC79BFEF60AF9617CULL;
			} else {
				hash_code ^= 0X0429197C2FC669EEULL;
			}

			break;

		case B1:

			discs[color] |= 0X4000000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X008F6EF4453495A8ULL;
			} else {
				hash_code ^= 0X6A1AD5C0D79E1AE4ULL;
			}

			break;

		case C1:

			discs[color] |= 0X2000000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X6DE130CFBD5E4B03ULL;
			} else {
				hash_code ^= 0X3DF572416D1530A5ULL;
			}

			break;

		case D1:

			discs[color] |= 0X1000000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X5D1A65EE28CACBF8ULL;
			} else {
				hash_code ^= 0X996955F15F1650CBULL;
			}

			break;

		case E1:

			discs[color] |= 0X0800000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0XAE6327AFFB44559EULL;
			} else {
				hash_code ^= 0X41A36D679A564A91ULL;
			}

			break;

		case F1:

			discs[color] |= 0X0400000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X03CCD1127F12F62DULL;
			} else {
				hash_code ^= 0X0C2CF1A1C4AD6D13ULL;
			}

			break;

		case G1:

			discs[color] |= 0X0200000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X9F8AA3178F2B1394ULL;
			} else {
				hash_code ^= 0XCDA4D30C92EC5F45ULL;
			}

			break;

		case H1:

			discs[color] |= 0X0100000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0XBA0543A47E6FF2A9ULL;
			} else {
				hash_code ^= 0XA96D02C2645A0456ULL;
			}

			break;

		case A2:

			discs[color] |= 0X0080000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X60DE7E0E3A76FDF0ULL;
			} else {
				hash_code ^= 0X4397F9C76A4D8E62ULL;
			}

			break;

		case B2:

			discs[color] |= 0X0040000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X668131FA5C735273ULL;
			} else {
				hash_code ^= 0X27F2A9E3DF582978ULL;
			}

			break;

		case C2:

			discs[color] |= 0X0020000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X96F29C5A9B6FD15EULL;
			} else {
				hash_code ^= 0X8C9205ABE0CB15FAULL;
			}

			break;

		case D2:

			discs[color] |= 0X0010000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X619F1FAEC1E82DE0ULL;
			} else {
				hash_code ^= 0XB9594228BEF7E84CULL;
			}

			break;

		case E2:

			discs[color] |= 0X0008000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X0A1AA93994AA5A9EULL;
			} else {
				hash_code ^= 0X7E54706B26656D15ULL;
			}

			break;

		case F2:

			discs[color] |= 0X0004000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X0D521A9B644685DEULL;
			} else {
				hash_code ^= 0X8D3331D1D88D7DC2ULL;
			}

			break;

		case G2:

			discs[color] |= 0X0002000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X73580BBFB1F518E3ULL;
			} else {
				hash_code ^= 0X4921EF8710445B6EULL;
			}

			break;

		case H2:

			discs[color] |= 0X0001000000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0XB8844A364A8FD77AULL;
			} else {
				hash_code ^= 0XDFCA3250484C75AFULL;
			}

			break;

		case A3:

			discs[color] |= 0X0000800000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X457499DA8421ACB2ULL;
			} else {
				hash_code ^= 0X5933951DAE4A3B3AULL;
			}

			break;

		case B3:

			discs[color] |= 0X0000400000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X90B88D84F01528F6ULL;
			} else {
				hash_code ^= 0X4D6A926EE41512F5ULL;
			}

			break;

		case C3:

			discs[color] |= 0X0000200000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X024BD24533582E8BULL;
			} else {
				hash_code ^= 0X1647A1749D5B9850ULL;
			}

			break;

		case D3:

			discs[color] |= 0X0000100000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X76CC6FE07CF98A2CULL;
			} else {
				hash_code ^= 0XCA21EC1086C9E72DULL;
			}

			break;

		case E3:

			discs[color] |= 0X0000080000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0XCD6BD259CC4531BBULL;
			} else {
				hash_code ^= 0X617252D2AC6A3AD3ULL;
			}

			break;

		case F3:

			discs[color] |= 0X0000040000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X3B588BDB6258EA64ULL;
			} else {
				hash_code ^= 0X46CF4DFA45B61335ULL;
			}

			break;

		case G3:

			discs[color] |= 0X0000020000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X4302A6DC441AD82FULL;
			} else {
				hash_code ^= 0XE1459CBBB4C45326ULL;
			}

			break;

		case H3:

			discs[color] |= 0X0000010000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0XB73929FE1D7104E6ULL;
			} else {
				hash_code ^= 0XA9755943D41419CCULL;
			}

			break;

		case A4:

			discs[color] |= 0X0000008000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X43F10D75AF82EBDAULL;
			} else {
				hash_code ^= 0X46167C438D560803ULL;
			}

			break;

		case B4:

			discs[color] |= 0X0000004000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X7F57A1BC6CC0C6A5ULL;
			} else {
				hash_code ^= 0X3B7B27D177417115ULL;
			}

			break;

		case C4:

			discs[color] |= 0X0000002000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0XFA4AAF1082BF8F7FULL;
			} else {
				hash_code ^= 0XF40449D76ACF7033ULL;
			}

			break;

		case D4:

			discs[color] |= 0X0000001000000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X62085D596EDD05D2ULL;
			} else {
				hash_code ^= 0XB675DDD7E48FDDCEULL;
			}

			break;

		case E4:

			discs[color] |= 0X0000000800000000ULL;
			if(color == BLACK) {
				hash_code ^= 0XB9BA6F83E508A4C5ULL;
			} else {
				hash_code ^= 0XE1B6AFE2052E6185ULL;
			}

			break;

		case F4:

			discs[color] |= 0X0000000400000000ULL;
			if(color == BLACK) {
				hash_code ^= 0XAD14C7E539D51489ULL;
			} else {
				hash_code ^= 0X628EB79D013AED72ULL;
			}

			break;

		case G4:

			discs[color] |= 0X0000000200000000ULL;
			if(color == BLACK) {
				hash_code ^= 0XBBD04C6669A079B3ULL;
			} else {
				hash_code ^= 0XF5F2A2476242DC67ULL;
			}

			break;

		case H4:

			discs[color] |= 0X0000000100000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X3337CBDC99AA5E0AULL;
			} else {
				hash_code ^= 0X5017DC3A9B25A0BAULL;
			}

			break;

		case A5:

			discs[color] |= 0X0000000080000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X2701859A5F3AF238ULL;
			} else {
				hash_code ^= 0X53BC2008F2D25753ULL;
			}

			break;

		case B5:

			discs[color] |= 0X0000000040000000ULL;
			if(color == BLACK) {
				hash_code ^= 0XB04308D12EEC231FULL;
			} else {
				hash_code ^= 0X1EAF06CA86DAF90EULL;
			}

			break;

		case C5:

			discs[color] |= 0X0000000020000000ULL;
			if(color == BLACK) {
				hash_code ^= 0XC40E3C62E1FEA4BCULL;
			} else {
				hash_code ^= 0X3A978668A91214FCULL;
			}

			break;

		case D5:

			discs[color] |= 0X0000000010000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X3E6B68BDE78C5A9DULL;
			} else {
				hash_code ^= 0XE6E96506B43E6FB4ULL;
			}

			break;

		case E5:

			discs[color] |= 0X0000000008000000ULL;
			if(color == BLACK) {
				hash_code ^= 0XC166DDDA59B65540ULL;
			} else {
				hash_code ^= 0X0F17EFBCE39044FCULL;
			}

			break;

		case F5:

			discs[color] |= 0X0000000004000000ULL;
			if(color == BLACK) {
				hash_code ^= 0XE9805D61927900E1ULL;
			} else {
				hash_code ^= 0XB9DB7BDA202AF62DULL;
			}

			break;

		case G5:

			discs[color] |= 0X0000000002000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X0857FDCD16047C54ULL;
			} else {
				hash_code ^= 0X05EFC5AC69AB23A9ULL;
			}

			break;

		case H5:

			discs[color] |= 0X0000000001000000ULL;
			if(color == BLACK) {
				hash_code ^= 0X20578A4BAF901694ULL;
			} else {
				hash_code ^= 0X870EE4BE453C62DCULL;
			}

			break;

		case A6:

			discs[color] |= 0X0000000000800000ULL;
			if(color == BLACK) {
				hash_code ^= 0X91FAB6AA406CD6A5ULL;
			} else {
				hash_code ^= 0XBA20CE704CD47BF8ULL;
			}

			break;

		case B6:

			discs[color] |= 0X0000000000400000ULL;
			if(color == BLACK) {
				hash_code ^= 0XF8F082FDDBDC088FULL;
			} else {
				hash_code ^= 0X5FAF128D15EA6EC5ULL;
			}

			break;

		case C6:

			discs[color] |= 0X0000000000200000ULL;
			if(color == BLACK) {
				hash_code ^= 0XF70DDB51ECA37304ULL;
			} else {
				hash_code ^= 0XD6EC1B708B88569BULL;
			}

			break;

		case D6:

			discs[color] |= 0X0000000000100000ULL;
			if(color == BLACK) {
				hash_code ^= 0X0B23D602B5E730EAULL;
			} else {
				hash_code ^= 0XD3B38CA27A921409ULL;
			}

			break;

		case E6:

			discs[color] |= 0X0000000000080000ULL;
			if(color == BLACK) {
				hash_code ^= 0XE141127AFF5D9D88ULL;
			} else {
				hash_code ^= 0X10D8EAC48C06DE04ULL;
			}

			break;

		case F6:

			discs[color] |= 0X0000000000040000ULL;
			if(color == BLACK) {
				hash_code ^= 0X06AB4E930C3C3B4CULL;
			} else {
				hash_code ^= 0X5FD90096024DF466ULL;
			}

			break;

		case G6:

			discs[color] |= 0X0000000000020000ULL;
			if(color == BLACK) {
				hash_code ^= 0X2F58A940D4150E0AULL;
			} else {
				hash_code ^= 0X39E06B75DE5CE056ULL;
			}

			break;

		case H6:

			discs[color] |= 0X0000000000010000ULL;
			if(color == BLACK) {
				hash_code ^= 0XF4FD8BED713AE0E8ULL;
			} else {
				hash_code ^= 0X316CCD2549DAB6C9ULL;
			}

			break;

		case A7:

			discs[color] |= 0X0000000000008000ULL;
			if(color == BLACK) {
				hash_code ^= 0XBDD43971341B3DD5ULL;
			} else {
				hash_code ^= 0X0B43C7CF79974871ULL;
			}

			break;

		case B7:

			discs[color] |= 0X0000000000004000ULL;
			if(color == BLACK) {
				hash_code ^= 0X1A7A170899D82293ULL;
			} else {
				hash_code ^= 0X6A7D78272C960D12ULL;
			}

			break;

		case C7:

			discs[color] |= 0X0000000000002000ULL;
			if(color == BLACK) {
				hash_code ^= 0X06995AE685421F11ULL;
			} else {
				hash_code ^= 0X1A85D295BD09A404ULL;
			}

			break;

		case D7:

			discs[color] |= 0X0000000000001000ULL;
			if(color == BLACK) {
				hash_code ^= 0XEBBC7CB71EB476C1ULL;
			} else {
				hash_code ^= 0X7B37BFCED13DA3C5ULL;
			}

			break;

		case E7:

			discs[color] |= 0X0000000000000800ULL;
			if(color == BLACK) {
				hash_code ^= 0X8B9289F7BDFA0A8AULL;
			} else {
				hash_code ^= 0XA47C8B4039BCB0AAULL;
			}

			break;

		case F7:

			discs[color] |= 0X0000000000000400ULL;
			if(color == BLACK) {
				hash_code ^= 0X0DBAAFDBEE9F073CULL;
			} else {
				hash_code ^= 0X55FB5E5E7C47E4C4ULL;
			}

			break;

		case G7:

			discs[color] |= 0X0000000000000200ULL;
			if(color == BLACK) {
				hash_code ^= 0XF484677142134734ULL;
			} else {
				hash_code ^= 0X3CAFC19BD170E9B1ULL;
			}

			break;

		case H7:

			discs[color] |= 0X0000000000000100ULL;
			if(color == BLACK) {
				hash_code ^= 0X96F1CBC65D7D8FD0ULL;
			} else {
				hash_code ^= 0XA607EB34997673B4ULL;
			}

			break;

		case A8:

			discs[color] |= 0X0000000000000080ULL;
			if(color == BLACK) {
				hash_code ^= 0X2C89DA6AD9CF1CE1ULL;
			} else {
				hash_code ^= 0X4BEB70B395691171ULL;
			}

			break;

		case B8:

			discs[color] |= 0X0000000000000040ULL;
			if(color == BLACK) {
				hash_code ^= 0X339D774EDFF65CDCULL;
			} else {
				hash_code ^= 0X8DF5C2DF4A2A15B4ULL;
			}

			break;

		case C8:

			discs[color] |= 0X0000000000000020ULL;
			if(color == BLACK) {
				hash_code ^= 0XEE4FFAA05000D7A3ULL;
			} else {
				hash_code ^= 0XFB0397FEE53662B8ULL;
			}

			break;

		case D8:

			discs[color] |= 0X0000000000000010ULL;
			if(color == BLACK) {
				hash_code ^= 0X076CEBC185343BB6ULL;
			} else {
				hash_code ^= 0XAC75D5F3EEAC23EDULL;
			}

			break;

		case E8:

			discs[color] |= 0X0000000000000008ULL;
			if(color == BLACK) {
				hash_code ^= 0XF899D4E5A6A89530ULL;
			} else {
				hash_code ^= 0X8B6C247FA77ECE8DULL;
			}

			break;

		case F8:

			discs[color] |= 0X0000000000000004ULL;
			if(color == BLACK) {
				hash_code ^= 0XF71AA37EC76E7E58ULL;
			} else {
				hash_code ^= 0X790B918AF5599202ULL;
			}

			break;

		case G8:

			discs[color] |= 0X0000000000000002ULL;
			if(color == BLACK) {
				hash_code ^= 0XB0CD851861F3B7B6ULL;
			} else {
				hash_code ^= 0XAD2822A305818B27ULL;
			}

			break;

		case H8:

			discs[color] |= 0X0000000000000001ULL;
			if(color == BLACK) {
				hash_code ^= 0X5F4871C661CF2338ULL;
			} else {
				hash_code ^= 0X33FEA1852435F281ULL;
			}

			break;

	}

	n_empties--;
	//n_discs[color]++;
}




