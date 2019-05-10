// Logger.cpp : Defines the entry point for the console application.
//
#include "Logger.h"

int main(int argc, char** argv)
{
    LOG_ERROR("Hello world!, %s", "Logger");
    LOG_WARNING("Hello world!, %s %d", "Logger", 1010);
    LOG_DEBUG("Hello world!, %s %x", "Logger", 1010);
}

