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
    Room,
    Game,
};

class ClientLayer : public Walnut::Layer {
  private:
    float m_deltaTime;
    Walnut::Application *m_app;

    Screens m_screen = Screens::Login;
    bool m_isAdmin;
    float m_maxCounterTime = 3;

    void updateDeltaTime();
    bool count(float *counter);

    static void HelpMarker(const char *desc);
    void renderLogin();
    void renderSignup();
    void renderMenu();
    void renderCreateRoom();
    void renderJoinRoom();
    void renderPersonalStats();
    void renderHighscore();
    void renderRoom();

  public:
    ClientLayer(Walnut::Application *app) : m_app(app) {}

    virtual void OnAttach() override;
    virtual void OnUIRender() override;
    virtual void OnDetach() override;
};

#endif // !CLIENTLAYER_H_
