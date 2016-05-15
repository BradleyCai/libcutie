/*
 * Hash.hpp
 *
 * libcutie - Validate your opponent's data to detect cheating.
 * Copyright (c) 2016 Ammon Smith, Auggie Balquin, Bradley Cai
 * 
 * libcutie is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * libcutie is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with libcutie.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __HASH_HPP
#define __HASH_HPP

#include "Cutie.hpp"

namespace hash {
    enum HashAlgorithm {
        SHA256,
    };

    struct hashInfo {
        cutie::data *dataBytes;
        cutie::data *hashBytes;
        cutie::data *randBytes;
    };

    hashInfo *getHashData(cutie::data *bytesToSend, size_t randBytesLength, int algorithm);
    bool verifyHashData(const hashInfo *hash, int algorithm);
    void deleteHashData(const hashInfo *hash);
};

#endif /* __HASH_HPP */

