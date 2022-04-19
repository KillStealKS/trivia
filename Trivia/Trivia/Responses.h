#pragma once

#include <iostream>

enum responseCodes
{
	RS_ERROR = 0,
	RS_SIGNUP = 1,
	RS_LOGIN
};

typedef struct LoginResponse
{
	unsigned int status;
} LoginResponse;

typedef struct SignupResponse
{
	unsigned int status;
} SignupResponse;

typedef struct ErrorResponse
{
	std::string message;
} ErrorResponse;