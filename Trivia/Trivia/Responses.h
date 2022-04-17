#pragma once

#include <iostream>

enum responseCodes
{
	RS_ERROR = -1,
	RS_LOGIN = 1,
	RS_SIGNUP
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