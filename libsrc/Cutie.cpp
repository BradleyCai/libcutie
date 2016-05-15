/*
 * Cutie.cpp
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

#include <cstdio>
#include <cstring>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Cutie.hpp"
#include "Hash.hpp"
#include "Util.hpp"

namespace {
    /* Session data */
    int sockfd = -1;
    bool amHost;

    /* Options */
    unsigned int rejectTimes = 10;
    unsigned int randBytesLength = 10;
    int algorithm = hash::SHA256;
};

static cutie::data *getData(bool (*check)(cutie::data *));
static bool sendData(cutie::data *bytes);

namespace cutie {
    void setRejectTimes(unsigned int value)
    {
        rejectTimes = value;
    }

    void setRandBytesLength(unsigned int value)
    {
        randBytesLength = value;
    }

    bool createSession(int port)
    {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            return false;
        }

        sockaddr_in addr;

        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);

        int ret = bind(sockfd, (const sockaddr *)(&addr), sizeof(sockaddr_in));
        if (ret < 0) {
            return false;
        }

        amHost = true;
        return true;
    }

    bool joinSession(const char *ipAddress, int port)
    {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            return false;
        }

        sockaddr_in addr;

        addr.sin_addr.s_addr = inet_addr(ipAddress);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);

        int ret = connect(sockfd, (sockaddr *)(&addr), sizeof(addr));
        if (ret < 0) {
            return false;
        }

        amHost = false;
        return true;
    }

    bool endSession()
    {
        if (sockfd >= 0) {
            return close(sockfd) >= 0;
        }

        return true;
    }

    bool init(data *bytes, bool (*check)(data *))
    {
        data *theirBytes;
        if (amHost) {
            if (!sendData(bytes)) {
                return false;
            }

            theirBytes = getData(check);
            if (!theirBytes) {
                return false;
            }
        } else {
            theirBytes = getData(check);
            if (!theirBytes) {
                return false;
            }

            if (!sendData(bytes)) {
                return false;
            }
        }

        return true;
    }

    data *doTurn(data *bytesToSend, bool (*check)(data *), bool &forgery)
    {
        hash::hashInfo *hash = hash::getHashData(bytesToSend, randBytesLength, algorithm);
        data *theirData = new data;
        (void)(theirData);
        forgery = true;

        data *theirBytes;
        if (amHost) {
            if (!sendData(hash->hashBytes)) {
                return NULL;
            }

            theirBytes = getData(check);
            if (!theirBytes) {
                return NULL;
            }
        } else {
            theirBytes = getData(check);
            if (!theirBytes) {
                return NULL;
            }

            if (!sendData(hash->hashBytes)) {
                return NULL;
            }
        }

        // forgery = hash::verifyHashData();

        return theirBytes;
    }
};

static cutie::data *getData(bool (*check)(cutie::data *))
{
    cutie::data *bytes = new cutie::data;
    int ret;
    bool success;

    bytes->length = util::getLength(sockfd, success);

    if (!success) {
        return NULL;
    }

    bytes->data = new char[bytes->length];

    for (unsigned int i = 0; i < rejectTimes; i++) {
        ret = recv(sockfd, bytes->data, bytes->length, 0);

        if (ret < 0) {
            return NULL;
        }

        success = check(bytes);
        ret = send(sockfd, &success, 1, 0);

        if (ret < 0) {
            return NULL;
        } else if (success) {
            return bytes;
        }
    }

    return NULL;
}

static bool sendData(cutie::data *bytes)
{
    char response = 0;
    int ret;

    if (!util::sendLength(sockfd, bytes->length)) {
        return false;
    }

    for (unsigned int i = 0; !response; i++) {
        ret = send(sockfd, bytes->data, bytes->length, 0);

        if (ret < 0) {
            return false;
        }

        ret = recv(sockfd, &response, 1, 0);

        if (ret < 0 || i >= rejectTimes) {
            return false;
        }
    }

    return true;
}

