#include "ClientLayer.h"

void ClientLayer::OnUIRender() {
    updateDeltaTime();

    ImGui::Begin("Trivia");
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
    default:
        break;
    }
    ImGui::End();

    ImGui::ShowDemoWindow();
}

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
    if (LOW_DELTA > m_deltaTime)
        m_deltaTime = LOW_DELTA;
    if (HIGH_DELTA < m_deltaTime)
        m_deltaTime = HIGH_DELTA;

    lastTime = currTime;
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
    HelpMarker("has to contain at least 1 lowercase letter, 1 uppercase letter, "
        "1 digit and 1 non-alphanumeric character");

    if (ImGui::Button("Login")) {
        try {
            if (RequestHandler::loginRequest(username, password).status ==
                RS_LOGIN)
                m_screen = Screens::Menu;
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
        }
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
    HelpMarker("has to contain at least 1 lowercase letter, 1 uppercase letter, "
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
        try {
            if (RequestHandler::signupRequest(username, password, email,
                                              address, phone, birthDate)
                    .status == RS_SIGNUP) {
                if (RequestHandler::loginRequest(username, password).status ==
                    RS_LOGIN)
                    m_screen = Screens::Menu;
            }
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
        }
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
    if (ImGui::Button("Exit")) {
        // TODO
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
        if (RequestHandler::createRoomRequest(roomName, maxUsers, questionCount,
                                              answerTimeout)
                .status == RS_CREATEROOM)
            m_screen = Screens::Menu;
    }

    if (ImGui::Button("Back"))
        m_screen = Screens::Menu;
}

/**
 * @brief Renders joinRoom screen.
 */
void ClientLayer::renderJoinRoom() {
    GetRoomsResponse rooms = RequestHandler::getRoomsRequest();
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

            GetPlayersInRoomResponse players =
                RequestHandler::getPlayersInRoomRequest(r.id);
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
            m_screen = Screens::Menu;
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

    GetPersonalStatsResponse stats = RequestHandler::getPersonalStatsRequest();

    std::string gamesWon = std::to_string(stats.statistics.gamesWon) + "/" +
                           std::to_string(stats.statistics.totalGames);
    std::string correctAnswers =
        std::to_string(stats.statistics.correctAnswers) + "/" +
        std::to_string(stats.statistics.totalAnswers);

    if (ImGui::BeginTable("Rooms", 2,
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

    GetHighScoreResponse highscore = RequestHandler::getHighscoreRequest();

    for (auto i : highscore.statistics) {
        ImGui::Text(i.c_str());
    }

    if (ImGui::Button("Back"))
        m_screen = Screens::Menu;
}
