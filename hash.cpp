//
//  hash.cpp
//  
//
//  Created by Causse Bruno on 05/08/2024.
//

#include "hash.hpp"





unsigned long long hashSquare[64][2] = {
    
    {0X5F4871C661CF2338ULL,  0X33FEA1852435F281ULL},    //H8
    {0XB0CD851861F3B7B6ULL,  0XAD2822A305818B27ULL},
    {0XF71AA37EC76E7E58ULL,  0X790B918AF5599202ULL},
    {0XF899D4E5A6A89530ULL,  0X8B6C247FA77ECE8DULL},
    {0X076CEBC185343BB6ULL,  0XAC75D5F3EEAC23EDULL},
    {0XEE4FFAA05000D7A3ULL,  0XFB0397FEE53662B8ULL},
    {0X339D774EDFF65CDCULL,  0X8DF5C2DF4A2A15B4ULL},
    {0X2C89DA6AD9CF1CE1ULL,  0X4BEB70B395691171ULL},    //A8
    
    {0X96F1CBC65D7D8FD0ULL,  0XA607EB34997673B4ULL},    //H7
    {0XF484677142134734ULL,  0X3CAFC19BD170E9B1ULL},
    {0X0DBAAFDBEE9F073CULL,  0X55FB5E5E7C47E4C4ULL},
    {0X8B9289F7BDFA0A8AULL,  0XA47C8B4039BCB0AAULL},
    {0XEBBC7CB71EB476C1ULL,  0X7B37BFCED13DA3C5ULL},
    {0X06995AE685421F11ULL,  0X1A85D295BD09A404ULL},
    {0X1A7A170899D82293ULL,  0X6A7D78272C960D12ULL},
    {0XBDD43971341B3DD5ULL,  0X0B43C7CF79974871ULL},    //A7
    
    {0XF4FD8BED713AE0E8ULL,  0X316CCD2549DAB6C9ULL},    //H6
    {0X2F58A940D4150E0AULL,  0X39E06B75DE5CE056ULL},
    {0X06AB4E930C3C3B4CULL,  0X5FD90096024DF466ULL},
    {0XE141127AFF5D9D88ULL,  0X10D8EAC48C06DE04ULL},
    {0X0B23D602B5E730EAULL,  0XD3B38CA27A921409ULL},
    {0XF70DDB51ECA37304ULL,  0XD6EC1B708B88569BULL},
    {0XF8F082FDDBDC088FULL,  0X5FAF128D15EA6EC5ULL},
    {0X91FAB6AA406CD6A5ULL,  0XBA20CE704CD47BF8ULL},    //A6
    
    {0X20578A4BAF901694ULL,  0X870EE4BE453C62DCULL},    //H5
    {0X0857FDCD16047C54ULL,  0X05EFC5AC69AB23A9ULL},
    {0XE9805D61927900E1ULL,  0XB9DB7BDA202AF62DULL},
    {0XC166DDDA59B65540ULL,  0X0F17EFBCE39044FCULL},
    {0X3E6B68BDE78C5A9DULL,  0XE6E96506B43E6FB4ULL},
    {0XC40E3C62E1FEA4BCULL,  0X3A978668A91214FCULL},
    {0XB04308D12EEC231FULL,  0X1EAF06CA86DAF90EULL},
    {0X2701859A5F3AF238ULL,  0X53BC2008F2D25753ULL},    //A5
    
    {0X3337CBDC99AA5E0AULL,  0X5017DC3A9B25A0BAULL},    //H4
    {0XBBD04C6669A079B3ULL,  0XF5F2A2476242DC67ULL},
    {0XAD14C7E539D51489ULL,  0X628EB79D013AED72ULL},
    {0XB9BA6F83E508A4C5ULL,  0XE1B6AFE2052E6185ULL},
    {0X62085D596EDD05D2ULL,  0XB675DDD7E48FDDCEULL},
    {0XFA4AAF1082BF8F7FULL,  0XF40449D76ACF7033ULL},
    {0X7F57A1BC6CC0C6A5ULL,  0X3B7B27D177417115ULL},
    {0X43F10D75AF82EBDAULL,  0X46167C438D560803ULL},    //A4
    
    {0XB73929FE1D7104E6ULL,  0XA9755943D41419CCULL},    //H3
    {0X4302A6DC441AD82FULL,  0XE1459CBBB4C45326ULL},
    {0X3B588BDB6258EA64ULL,  0X46CF4DFA45B61335ULL},
    {0XCD6BD259CC4531BBULL,  0X617252D2AC6A3AD3ULL},
    {0X76CC6FE07CF98A2CULL,  0XCA21EC1086C9E72DULL},
    {0X024BD24533582E8BULL,  0X1647A1749D5B9850ULL},
    {0X90B88D84F01528F6ULL,  0X4D6A926EE41512F5ULL},
    {0X457499DA8421ACB2ULL,  0X5933951DAE4A3B3AULL},    //A3
    
    {0XB8844A364A8FD77AULL,  0XDFCA3250484C75AFULL},    //H2
    {0X73580BBFB1F518E3ULL,  0X4921EF8710445B6EULL},
    {0X0D521A9B644685DEULL,  0X8D3331D1D88D7DC2ULL},
    {0X0A1AA93994AA5A9EULL,  0X7E54706B26656D15ULL},
    {0X619F1FAEC1E82DE0ULL,  0XB9594228BEF7E84CULL},
    {0X96F29C5A9B6FD15EULL,  0X8C9205ABE0CB15FAULL},
    {0X668131FA5C735273ULL,  0X27F2A9E3DF582978ULL},
    {0X60DE7E0E3A76FDF0ULL,  0X4397F9C76A4D8E62ULL},    //A2
    
    {0XBA0543A47E6FF2A9ULL,  0XA96D02C2645A0456ULL},    //H1
    {0X9F8AA3178F2B1394ULL,  0XCDA4D30C92EC5F45ULL},
    {0X03CCD1127F12F62DULL,  0X0C2CF1A1C4AD6D13ULL},
    {0XAE6327AFFB44559EULL,  0X41A36D679A564A91ULL},
    {0X5D1A65EE28CACBF8ULL,  0X996955F15F1650CBULL},
    {0X6DE130CFBD5E4B03ULL,  0X3DF572416D1530A5ULL},
    {0X008F6EF4453495A8ULL,  0X6A1AD5C0D79E1AE4ULL},
    {0XC79BFEF60AF9617CULL,  0X0429197C2FC669EEULL},    //A1
}

void init_hashCodeTable() {
    
    for(unsigned int row = 0; row < 256*256; row++ {
        
        hashcodeTable_lines1_2[row][black] = 0;
        hashcodeTable_lines3_4[row][black] = 0;
        hashcodeTable_lines5_6[row][black] = 0;
        hashcodeTable_lines7_8[row][black] = 0;

        hashcodeTable_lines1_2[row][white] = 0;
        hashcodeTable_lines2_3[row][white] = 0;
        hashcodeTable_lines5_6[row][white] = 0;
        hashcodeTable_lines7_8[row][white] = 0;

        for (int bit = 0 bit<16; bit++) {
            
            if(row & 1<<bit) {
                
                hashcodeTable_lines1_2[row][black] ^= hashSquare[bit   ][Black];
                hashcodeTable_lines3_4[row][black] ^= hashSquare[bit+16][Black];
                hashcodeTable_lines5_6[row][black] ^= hashSquare[bit+32][Black];
                hashcodeTable_lines7_8[row][black] ^= hashSquare[bit+48][Black];

                hashcodeTable_lines1_2[row][white] ^= hashSquare[bit   ][white];
                hashcodeTable_lines3_4[row][white] ^= hashSquare[bit+16][white];
                hashcodeTable_lines5_6[row][white] ^= hashSquare[bit+32][white];
                hashcodeTable_lines7_8[row][white] ^= hashSquare[bit+48][white];

            }
        }
        
    }
}
        
    unsigned long long hascode() {
        
        unsigned long long p = discs[player];
        unsigned long long o = discs[player^1];
        
        lines1_2 = (p & 0xFFFF000000000000ULL) >> 48;
        lines3_4 = (p & 0x0000FFFF00000000ULL) >> 32;
        lines3_4 = (p & 0x00000000FFFF0000ULL) >> 16;
        lines3_4 = (p & 0x000000000000FFFFULL);

        
        unsigned long long
        hashcode  = hashcodeTable_lines1_2[lines1_2][player]
        hashcode ^= hashcodeTable_lines3_4[lines2-3][player]
        hashcode ^= hashcodeTable_lines5_6[lines4_5][player]
        hashcode ^= hashcodeTable_lines7_8[lines7_8][player]
        
        int opponent = player^1;
        
        hashcode ^= hashcodeTable_lines1_2[lines1_2][opponent]
        hashcode ^= hashcodeTable_lines3_4[lines2-3][opponent]
        hashcode ^= hashcodeTable_lines5_6[lines4_5][opponent]
        hashcode ^= hashcodeTable_lines7_8[lines7_8][opponent]
 
        if((n_empties%2 == BLACK && player == WHITE) || (n_empties%2 == WHITE && player == BLACK))
            hash_code ^= 0xBB20B460D4D95138ULL;

        
    }






