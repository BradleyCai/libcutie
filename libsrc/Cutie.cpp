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

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "Cutie.hpp"

namespace {
    int sockfd = -1;
    unsigned int rejectTimes = 10;
};

namespace cutie {
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

        return true;
    }
        
    void setRejectTimes(unsigned int value)
    {
        rejectTimes = value;
    }
};

