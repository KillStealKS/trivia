#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include "Requests.h"
#include "json.hpp"
#include <vector>

using json = nlohmann::json;

class Serializer {
  public:
    static std::vector<unsigned char> serializeRequest(LoginRequest l);
    static std::vector<unsigned char> serializeRequest(SignupRequest s);
    static std::vector<unsigned char>
    serializeRequest(GetPlayersInRoomRequest gp);
    static std::vector<unsigned char> serializeRequest(JoinRoomRequest jr);
    static std::vector<unsigned char> serializeRequest(CreateRoomRequest cr);
    static std::vector<unsigned char> serializeRequest(SubmitAnswerRequest sa);
};

#endif // !SERIALIZER_H_
