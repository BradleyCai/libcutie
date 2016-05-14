/*
 * Signals.cpp
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
 
#include <csignal>
#include <cstdlib>
#include <iostream>

static void handleSignal(int signum);
 
namespace signals {
    void init() 
    {
        signal(SIGTERM, handleSignal);
        signal(SIGSEGV, handleSignal);
        signal(SIGHUP, handleSignal);
        signal(SIGINT, handleSignal);
    }
}

static void handleSignal(int signum) 
{
    switch (signum) {
        case SIGTERM:
            std::cout << "Received sigterm. Quitting.\n";
            exit(0);
        case SIGSEGV:
            std::cerr << "Segmentation fault\n";
            exit(1);
        case SIGHUP:
            exit(0);
        case SIGINT:
            std::cout << "Received interrupt. Quitting.\n";
            exit(0);
    }
}