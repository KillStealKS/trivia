#include "ClientLayer.h"

void ClientLayer::OnAttach() {
    Communicator::communicator.startNewConnection();
}

void ClientLayer::OnUIRender() {
    updateDeltaTime();

    ImGui::Begin("Trivia");

    static std::string errStr;
    try {
        switch (m_screen) {
        case Screens::Login:
            renderLogin();
            break;
        case Screens::Signup:
            renderSignup();
            break;
        case Screens::Menu:
            renderMenu();
            break;
        case Screens::CreateRoom:
            renderCreateRoom();
            break;
        case Screens::JoinRoom:
            renderJoinRoom();
            break;
        case Screens::PersonalStats:
            renderPersonalStats();
            break;
        case Screens::Highscore:
            renderHighscore();
            break;
        case Screens::Room:
            renderRoom();
            break;
        }
    } catch (const std::exception &e) {
        errStr = e.what();
        ImGui::OpenPopup("Error");
    }

    if (ImGui::BeginPopupModal("Error", NULL,
                               ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text(errStr.c_str());

        if (ImGui::Button("Close")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
    
    ImGui::End();

    ImGui::ShowDemoWindow();
}

void ClientLayer::OnDetach() {}

/**
 * @brief Creates a tooltip help marker.
 *
 * @param desc Tooltip text.
 */
void ClientLayer::HelpMarker(const char *desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

/**
 * @brief Updates the delta time.
 */
void ClientLayer::updateDeltaTime() {
    // Get time since last frame.
    static auto lastTime = std::chrono::system_clock::now();
    auto currTime = std::chrono::system_clock::now();
    std::chrono::duration<float> duration = currTime - lastTime;
    m_deltaTime = duration.count();

    // Limit framerate.
    if (LOW_DELTA > m_deltaTime) {
        // Sleep until next frame
        std::chrono::duration<double, std::milli> delta_ms(LOW_DELTA * 1000 -
                                                           m_deltaTime * 1000);
        auto delta_ms_duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
        std::this_thread::sleep_for(
            std::chrono::milliseconds(delta_ms_duration.count()));
        m_deltaTime = LOW_DELTA;
    }
    if (HIGH_DELTA < m_deltaTime)
        m_deltaTime = HIGH_DELTA;

    lastTime = currTime;
}

/**
 * @brief Counts down.
 *
 * @param counter Counter variable.
 * @return true If counter reached 0.
 * @return false If not.
 */
bool ClientLayer::count(float *counter) {
    if (*counter <= 0) {
        *counter = m_maxCounterTime;
        return true;
    }

    *counter -= m_deltaTime;
    return false;
}

/**
 * @brief Renders login screen.
 */
void ClientLayer::renderLogin() {
    static char username[128] = "";
    ImGui::InputTextWithHint("##username", "Username", username,
                             IM_ARRAYSIZE(username));
    static char password[128] = "";
    ImGui::InputTextWithHint("##password", "Password", password,
                             IM_ARRAYSIZE(password));
    ImGui::SameLine();
    HelpMarker(
        "has to contain at least 1 lowercase letter, 1 uppercase letter, "
        "1 digit and 1 non-alphanumeric character");

    if (ImGui::Button("Login")) {
        if (RequestHandler::loginRequest(username, password).status == RS_LOGIN)
            m_screen = Screens::Menu;
    }

    if (ImGui::Button("Signup")) {
        m_screen = Screens::Signup;
        return;
    }
}

/**
 * @brief Renders signup screen.
 */
void ClientLayer::renderSignup() {
    static char username[128] = "";
    ImGui::InputTextWithHint("##username", "Username", username,
                             IM_ARRAYSIZE(username));
    static char password[128] = "";
    ImGui::InputTextWithHint("##password", "Password", password,
                             IM_ARRAYSIZE(password));
    ImGui::SameLine();
    HelpMarker(
        "has to contain at least 1 lowercase letter, 1 uppercase letter, "
        "1 digit and 1 non-alphanumeric character");
    static char email[128] = "";
    ImGui::InputTextWithHint("##email", "Email", email, IM_ARRAYSIZE(email));
    static char address[128] = "";
    ImGui::InputTextWithHint("##address", "Address", address,
                             IM_ARRAYSIZE(address));
    static char phone[128] = "";
    ImGui::InputTextWithHint("##phone", "Phone", phone, IM_ARRAYSIZE(phone));
    static char birthDate[128] = "";
    ImGui::InputTextWithHint("##birthDate", "Birth date", birthDate,
                             IM_ARRAYSIZE(birthDate));
    ImGui::SameLine();
    HelpMarker("either DD/MM/YYYY or DD.MM.YYYY");

    if (ImGui::Button("Signup")) {
        RequestHandler::signupRequest(username, password, email, address, phone,
                                      birthDate);
        RequestHandler::loginRequest(username, password);
        m_screen = Screens::Menu;
    }

    if (ImGui::Button("Login")) {
        m_screen = Screens::Login;
        return;
    }
}

/**
 * @brief Renders menu screen.
 */
void ClientLayer::renderMenu() {
    if (ImGui::Button("Create room"))
        m_screen = Screens::CreateRoom;
    if (ImGui::Button("Join room"))
        m_screen = Screens::JoinRoom;
    if (ImGui::Button("Statistics"))
        m_screen = Screens::PersonalStats;
    if (ImGui::Button("Logout")) {
        RequestHandler::logoutRequest();
        m_screen = Screens::Login;
    }
    if (ImGui::Button("Exit")) {
        RequestHandler::logoutRequest();
        m_app->Close();
    }
}

/**
 * @brief Renders createRoom screen.
 */
void ClientLayer::renderCreateRoom() {
    static char roomName[128] = "";
    ImGui::InputTextWithHint("##roomName", "Room name", roomName,
                             IM_ARRAYSIZE(roomName));
    static int maxUsers = 5;
    ImGui::InputInt("Max users", &maxUsers);
    static int questionCount = 10;
    ImGui::InputInt("Question count", &questionCount);
    static int answerTimeout = 20;
    ImGui::InputInt("Answer timeout", &answerTimeout);

    if (ImGui::Button("Create room")) {
        RequestHandler::createRoomRequest(roomName, maxUsers, questionCount,
                                          answerTimeout);

        m_isAdmin = true;

        m_screen = Screens::Room;
    }

    if (ImGui::Button("Back"))
        m_screen = Screens::Menu;
}

/**
 * @brief Renders joinRoom screen.
 */
void ClientLayer::renderJoinRoom() {
    static GetRoomsResponse rooms;
    static float getRoomsCounter = 0;
    if (count(&getRoomsCounter))
        rooms = RequestHandler::getRoomsRequest();

    static int selectedRoom = -1;

    if (ImGui::BeginTable("Rooms", 4,
                          ImGuiTableFlags_Resizable |
                              ImGuiTableFlags_NoSavedSettings |
                              ImGuiTableFlags_Borders)) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Name");
        ImGui::TableNextColumn();
        ImGui::Text("Users");
        ImGui::TableNextColumn();
        ImGui::Text("Question count");
        ImGui::TableNextColumn();
        ImGui::Text("Time per question");

        for (auto r : rooms.rooms) {
            if (r.isActive)
                continue;

            GetPlayersInRoomResponse players;
            static float getPlayersCounter = 0;
            if (count(&getPlayersCounter))
                players = RequestHandler::getPlayersInRoomRequest(r.id);
            std::string playersStr = std::to_string(players.players.size()) +
                                     "/" + std::to_string(r.maxPlayers);

            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            if (ImGui::Selectable(r.name.c_str(), selectedRoom == r.id))
                selectedRoom = r.id;
            ImGui::TableNextColumn();
            ImGui::Text(playersStr.c_str());
            ImGui::TableNextColumn();
            ImGui::Text(std::to_string(r.numOfQuestions).c_str());
            ImGui::TableNextColumn();
            ImGui::Text(std::to_string(r.timePerQuestion).c_str());
        }

        ImGui::EndTable();
    }

    if (selectedRoom != -1) {
        if (ImGui::Button("Join room")) {
            RequestHandler::joinRoomRequest(selectedRoom);

            m_isAdmin = false;

            m_screen = Screens::Room;
        }
    }

    if (ImGui::Button("Back"))
        m_screen = Screens::Menu;
}

/**
 * @brief Renders personalStats screen.
 */
void ClientLayer::renderPersonalStats() {
    if (ImGui::Button("Highscores")) {
        m_screen = Screens::Highscore;
        return;
    }

    static GetPersonalStatsResponse stats =
        RequestHandler::getPersonalStatsRequest();

    std::string gamesWon = std::to_string(stats.statistics.gamesWon) + "/" +
                           std::to_string(stats.statistics.totalGames);
    std::string correctAnswers =
        std::to_string(stats.statistics.correctAnswers) + "/" +
        std::to_string(stats.statistics.totalAnswers);

    if (ImGui::BeginTable("Statistics", 2,
                          ImGuiTableFlags_Resizable |
                              ImGuiTableFlags_NoSavedSettings |
                              ImGuiTableFlags_Borders)) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Games won");
        ImGui::TableNextColumn();
        ImGui::Text(gamesWon.c_str());

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Correct answers");
        ImGui::TableNextColumn();
        ImGui::Text(correctAnswers.c_str());

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Total answer time");
        ImGui::TableNextColumn();
        ImGui::Text(std::to_string(stats.statistics.totalAnswerTime).c_str());

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Highscore");
        ImGui::TableNextColumn();
        ImGui::Text(std::to_string(stats.statistics.highscore).c_str());

        ImGui::EndTable();
    }

    if (ImGui::Button("Back"))
        m_screen = Screens::Menu;
}

/**
 * @brief Renders highscore screen.
 */
void ClientLayer::renderHighscore() {
    if (ImGui::Button("Personal stats")) {
        m_screen = Screens::PersonalStats;
        return;
    }

    static GetHighScoreResponse highscore =
        RequestHandler::getHighscoreRequest();

    for (auto i : highscore.statistics) {
        ImGui::Text(i.c_str());
    }

    if (ImGui::Button("Back"))
        m_screen = Screens::Menu;
}

/**
 * @brief Render room screen.
 */
void ClientLayer::renderRoom() {
    GetRoomStateResponse roomState;
    static float getRoomSateCounter = 0;
    if (count(&getRoomSateCounter))
        roomState = RequestHandler::getRoomStateRequest();

    if (roomState.hasGameBegun)
        m_screen = Screens::Game;

    if (ImGui::BeginTable("Room data", 2,
                          ImGuiTableFlags_Resizable |
                              ImGuiTableFlags_NoSavedSettings |
                              ImGuiTableFlags_Borders)) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Players");
        ImGui::TableNextColumn();
        for (auto i : roomState.players)
            ImGui::Text(i.c_str());

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Question count");
        ImGui::TableNextColumn();
        ImGui::Text(std::to_string(roomState.questionCount).c_str());

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Answer timout");
        ImGui::TableNextColumn();
        ImGui::Text(std::to_string(roomState.answerTimeout).c_str());

        ImGui::EndTable();
    }

    if (m_isAdmin) {
        if (ImGui::Button("Start game")) {
            RequestHandler::startGameRequest();
            m_screen = Screens::Game;
        }
        ImGui::SameLine();
        if (ImGui::Button("Close room")) {
            RequestHandler::closeRoomRequest();
            m_screen = Screens::Menu;
        }
    } else {
        if (ImGui::Button("Leave room")) {
            RequestHandler::leaveRoomRequest();
            m_screen = Screens::Menu;
        }
    }
}
