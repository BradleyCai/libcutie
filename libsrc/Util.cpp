/*
 * Util.cpp
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

#include "Util.hpp"

#include <sys/socket.h>

namespace util {
    bool sendLength(int fd, size_t length)
    {
        char len[4];
        len[0] = (char)length >> 24;
        len[1] = (char)length >> 16;
        len[2] = (char)length >> 8;
        len[3] = (char)length;

        int ret = send(fd, &len, 4, 0);
        return ret >= 0;
    }

    size_t getLength(int fd, bool &success)
    {
        char len[4];
        int ret = recv(fd, len, 4, 0);

        if (ret < 0) {
            success = false;
            return 0;
        }

        success = true;
        return len[0] << 24 | len[1] << 16 | len[2] << 8 | len[3];
    }
};

