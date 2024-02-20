#include <string>

#pragma once

#ifndef CLI_HANDLER_HPP
#define CLI_HANDLER_HPP

template <typename T> static T request(const std::string &request);

void run_cli();

#endif
