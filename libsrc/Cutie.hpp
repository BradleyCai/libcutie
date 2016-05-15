/*
 * Cutie.hpp
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

#ifndef __CUTIE_HPP
#define __CUTIE_HPP

#include <netinet/in.h>
#include <sys/socket.h>

namespace cutie {
    struct data {
        char *data;
        size_t length;
    };

    void setRejectTimes(unsigned int reject);

    bool createSession(int port);
    bool joinSession(const char *ipAddress, int port);
    bool endSession();

    bool init(data *bytes, bool (*check)(data *));
    data *doTurn(data *bytesToSend, bool (*check)(data *), bool &forgery);
};

#endif /* __CUTIE_HPP */

