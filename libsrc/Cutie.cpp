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

#include <cstring>
#include <functional>

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

static cutie::data *getHashData(const cutie::data *bytesToSend);
static cutie::data *getInitData(std::function<bool (cutie::data *)> check);
static bool sendInitData(cutie::data *bytes);

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

    bool init(data *bytes, std::function<bool (data *)> check)
    {
        if (amHost) {
            if (!sendInitData(bytes)) {
                return false;
            }

            if (!getInitData(check)) {
                return false;
            }
        } else {
            if (!getInitData(check)) {
                return false;
            }

            if (!sendInitData(bytes)) {
                return false;
            }
        }
    }

    data *doTurn(data *bytesToSend, std::function<bool (data *)> check)
    {
        int ret;
        data *hash = getHashData(bytesToSend);

        if (amHost) {
            ret = send(sockfd, bytesToSend->data, bytesToSend->length, 0);

            if (ret < 0) {
                return NULL;
            }
        } else {
        }

        ret = send(sockfd, bytesToSend->data, bytesToSend->length, 0);
        
        if (ret < 0) {
            return NULL;
        }

        return NULL; //
    }
};


static cutie::data *getHashData(const cutie::data *bytesToSend)
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

    /* Concatenate bytes + rand */
    cutie::data *bytesToHash = new cutie::data;
    bytesToHash->data = new char[bytesToSend->length + randBytesLength];
    bytesToHash->length = bytesToSend->length + randBytesLength;

    memcpy(bytesToHash->data, bytesToSend->data, bytesToSend->length);
    memcpy(bytesToHash->data + bytesToSend->length, randBytes, randBytesLength);

    /* Generate hash */
    return hash::doHash(bytesToHash, algorithm);
}

static cutie::data *getInitData(std::function<bool (cutie::data *)> check)
{
    cutie::data *bytes;
    int ret;

    for (unsigned i = 0; i < rejectTimes; i++) {
        bool success;
        bytes->length = util::getLength(sockfd, success);
        bytes->data = new char[bytes->length];

        if (!success) {
            delete bytes->data;
            return NULL;
        }

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

static bool sendInitData(cutie::data *bytes)
{
    char response = 0;
    int ret;
    for (unsigned i = 0; !response; i++) {
        if (!util::sendLength(sockfd, bytes->length)) {
            return false;
        }

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
