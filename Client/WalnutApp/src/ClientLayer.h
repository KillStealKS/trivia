#ifndef CLIENTLAYER_H_
#define CLIENTLAYER_H_

#include "Communicator.h"
#include "RequestHandler.h"
#include "Walnut/Application.h"
#include "Walnut/Image.h"
#include <chrono>
#include <ctime>

const float LOW_DELTA = 0.0167f;
const float HIGH_DELTA = 0.1f;

enum class Screens {
    Login,
    Signup,
    Menu,
    CreateRoom,
    JoinRoom,
    PersonalStats,
    Highscore,
};

class ClientLayer : public Walnut::Layer {
  private:
    float m_deltaTime;
    void updateDeltaTime();

    static void HelpMarker(const char *desc);

    Screens m_screen = Screens::Login;
    void renderLogin();
    void renderSignup();
    void renderMenu();
    void renderCreateRoom();
    void renderJoinRoom();
    void renderPersonalStats();
    void renderHighscore();

  public:
    virtual void OnUIRender() override;
};

#endif // !CLIENTLAYER_H_
