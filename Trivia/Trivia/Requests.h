#pragma once

#include <iostream>

enum requestCodes { RQ_LOGIN = 1, RQ_SIGNUP };

typedef struct LoginRequest {
    std::string username;
    std::string password;
} LoginRequest;

typedef struct SignupRequest {
    std::string username;
    std::string password;
    std::string email;
} SignupRequest;