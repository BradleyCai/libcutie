/*
 * Hash.cpp
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

#include <cstring>
#include <string>

#include "Cutie.hpp"
#include "Hash.hpp"
#include "Sha256.hpp"

static cutie::data *doHash(cutie::data *bytes, int algorithm);
static bool dataEquals(const cutie::data *a, const cutie::data *b);

namespace hash {
    hashInfo *getHashData(cutie::data *bytesToSend, size_t randBytesLength, int algorithm)
    {
        /* Get random string */
        FILE *randFh;
        char *randBytes = new char[randBytesLength];

        randFh = fopen("/dev/urandom", "r");

        if (randFh == NULL) {
            return NULL;
        }

        if (fgets(randBytes, randBytesLength, randFh) == NULL) {
            delete randBytes;
            return NULL;
        }

        /* Concatenate strings */
        size_t length = bytesToSend->length + randBytesLength;
        char bytesToHash[length];

        memcpy(&bytesToHash, bytesToSend->data, bytesToSend->length);
        memcpy(&bytesToHash + bytesToSend->length, randBytes, randBytesLength);

        /* Calculate hash */
        cutie::data dataToHash;
        dataToHash.data = bytesToHash;
        dataToHash.length = length;
        cutie::data *hash = doHash(&dataToHash, algorithm);

        hashInfo *info = new hashInfo;
        info->dataBytes = bytesToSend;
        info->hashBytes = hash;
        info->randBytes = randBytes;
        info->randBytesLength = randBytesLength;

        return info;
    }

    bool verifyHashData(const hashInfo *info, int algorithm)
    {
        /* Concatenate strings */
        size_t length = info->dataBytes->length + info->randBytesLength;
        char bytesToHash[length];

        memcpy(&bytesToHash, info->dataBytes->data, info->dataBytes->length);
        memcpy(&bytesToHash + info->dataBytes->length, info->randBytes, info->randBytesLength);

        /* Calculate hash */
        cutie::data dataToHash;
        dataToHash.data = bytesToHash;
        dataToHash.length = length;
        cutie::data *hash = doHash(&dataToHash, algorithm);

        /* Compare actual and expected hashes */
        return dataEquals(info->hashBytes, hash);
    }

    void deleteHashData(const hashInfo *hash)
    {
        delete hash->dataBytes->data;
        delete hash->dataBytes;
        delete hash->hashBytes->data;
        delete hash->hashBytes;
        delete hash->randBytes;
        delete hash;
    }
}

static cutie::data *doHash(cutie::data *bytes, int algorithm)
{
    switch (algorithm) {
        case hash::SHA256:
            return sha256::digest(bytes);
        default:
            return 0;
    }
}

static bool dataEquals(const cutie::data *a, const cutie::data *b)
{
    if (a->length != b->length) {
        return false;
    }

    for (unsigned int i = 0; i < a->length; i++) {
        if (a->data[i] != b->data[i]) {
            return false;
        }
    }

    return true;
}

