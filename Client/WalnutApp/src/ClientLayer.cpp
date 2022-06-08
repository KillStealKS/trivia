#include "ClientLayer.h"

float ClientLayer::m_maxCounterTime = 3;

void ClientLayer::OnAttach() {
    Communicator::communicator.startNewConnection();
}

void ClientLayer::OnUIRender() {
    updateDeltaTime();

    ImGui::Begin("Trivia", (bool *)0,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse);

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
        case Screens::Game:
            renderGame();
            break;
        case Screens::Results:
            renderResults();
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
}

void ClientLayer::OnDetach() {}

/**
 * @brief Creates an ImGui::InputInt with value limiting.
 *
 * @param label Input label.
 * @param v Value.
 * @param min Minimum value.
 * @param max Maximum value.
 */
void limitedInputInt(std::string label, int *v, int min, int max) {
    ImGui::InputInt(label.c_str(), v);
    if (*v > max)
        *v = max;
    if (*v < min)
        *v = min;
}

/**
 * @brief Centers next ImGui item.
 *
 * @param width Item width.
 * @param offset Center offset.
 */
void CenterItem(float width, float offset = 0.5f) {
    float winWidth = ImGui::GetWindowSize().x;

    float indent = (winWidth - width) * offset;

    ImGui::SetCursorPosX(indent);
}

/**
 * @brief Creates a centered text.
 *
 * @param text Text.
 */
void TextCentered(std::string text) {
    float winWidth = ImGui::GetWindowSize().x;
    float textWidth = ImGui::CalcTextSize(text.c_str()).x;

    float textIndent = (winWidth - textWidth) * 0.5f;

    float minIndentation = 20.0f;
    if (textIndent <= minIndentation) {
        textIndent = minIndentation;
    }

    ImGui::SameLine(textIndent);
    ImGui::PushTextWrapPos(winWidth - textIndent);
    ImGui::TextWrapped(text.c_str());
    ImGui::PopTextWrapPos();
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
bool ClientLayer::count(float *counter, float maxCountTime, bool autoReset) {
    if (*counter <= 0) {
        if (autoReset)
            *counter = maxCountTime;
        return true;
    }

    *counter -= m_deltaTime;
    return false;
}

/**
 * @brief Renders login screen.
 */
void ClientLayer::renderLogin() {
    TextCentered("LOGIN");

    float inputWidth = ImGui::GetWindowSize().x / 3.0f;
    ImGui::PushItemWidth(inputWidth);

    CenterItem(inputWidth);
    static char username[128] = "";
    ImGui::InputTextWithHint("##username", "Username", username,
                             IM_ARRAYSIZE(username));

    CenterItem(inputWidth);
    static char password[128] = "";
    ImGui::InputTextWithHint("##password", "Password", password,
                             IM_ARRAYSIZE(password));
    ImGui::SameLine();
    HelpMarker(
        "has to contain at least 1 lowercase letter, 1 uppercase letter, "
        "1 digit and 1 non-alphanumeric character");
    ImGui::PopItemWidth();

    float buttonWidth = ImGui::GetWindowSize().x / 4.0f;

    CenterItem(buttonWidth);
    if (ImGui::Button("Login", ImVec2(buttonWidth, 0.0f))) {
        RequestHandler::loginRequest(username, password).status;
        m_screen = Screens::Menu;
    }

    CenterItem(buttonWidth);
    if (ImGui::Button("Signup", ImVec2(buttonWidth, 0.0f))) {
        m_screen = Screens::Signup;
    }

    CenterItem(buttonWidth);
    if (ImGui::Button("Exit", ImVec2(buttonWidth, 0.0f)))
        m_app->Close();

    if (m_screen != Screens::Login) {
        memset(username, 0, sizeof(username));
        memset(password, 0, sizeof(password));
    }
}

/**
 * @brief Renders signup screen.
 */
void ClientLayer::renderSignup() {
    float inputWidth = ImGui::GetWindowSize().x / 3.0f;
    ImGui::PushItemWidth(inputWidth);

    CenterItem(inputWidth);
    static char username[128] = "";
    ImGui::InputTextWithHint("##username", "Username", username,
                             IM_ARRAYSIZE(username));

    CenterItem(inputWidth);
    static char password[128] = "";
    ImGui::InputTextWithHint("##password", "Password", password,
                             IM_ARRAYSIZE(password));
    ImGui::SameLine();
    HelpMarker(
        "has to contain at least 1 lowercase letter, 1 uppercase letter, "
        "1 digit and 1 non-alphanumeric character");

    CenterItem(inputWidth);
    static char email[128] = "";
    ImGui::InputTextWithHint("##email", "Email", email, IM_ARRAYSIZE(email));

    float addressWidth = inputWidth / 3.0f - 5.0f;
    ImGui::PushItemWidth(addressWidth);
    CenterItem(addressWidth + 5.0f, 3.0f / 8.0f);
    static char city[128] = "";
    ImGui::InputTextWithHint("##city", "City", city, IM_ARRAYSIZE(city));
    ImGui::SameLine();
    CenterItem(addressWidth);
    static char number[128] = "";
    ImGui::InputTextWithHint("##number", "Number", number,
                             IM_ARRAYSIZE(number));
    ImGui::SameLine();
    CenterItem(addressWidth - 2.5f, 5.0f / 8.0f);
    static char street[128] = "";
    ImGui::InputTextWithHint("##street", "Street", street,
                             IM_ARRAYSIZE(street));

    std::string address = std::string(city) + ", " + std::string(number) +
                          ", " + std::string(street);
    ImGui::PopItemWidth();

    CenterItem(inputWidth);
    static char phone[128] = "";
    ImGui::InputTextWithHint("##phone", "Phone", phone, IM_ARRAYSIZE(phone));

    CenterItem(inputWidth);
    static char birthDate[128] = "";
    ImGui::InputTextWithHint("##birthDate", "Birth date", birthDate,
                             IM_ARRAYSIZE(birthDate));
    ImGui::SameLine();
    HelpMarker("either DD/MM/YYYY or DD.MM.YYYY");

    ImGui::PopItemWidth();

    float buttonWidth = ImGui::GetWindowSize().x / 4.0f;

    CenterItem(buttonWidth);
    if (ImGui::Button("Signup", ImVec2(buttonWidth, 0.0f))) {
        RequestHandler::signupRequest(username, password, email, address, phone,
                                      birthDate);
        RequestHandler::loginRequest(username, password);
        m_screen = Screens::Menu;
    }

    CenterItem(buttonWidth);
    if (ImGui::Button("Login", ImVec2(buttonWidth, 0.0f)))
        m_screen = Screens::Login;

    if (m_screen != Screens::Signup) {
        memset(username, 0, sizeof(username));
        memset(password, 0, sizeof(password));
        memset(email, 0, sizeof(email));
        memset(city, 0, sizeof(city));
        memset(number, 0, sizeof(number));
        memset(street, 0, sizeof(street));
        memset(phone, 0, sizeof(phone));
        memset(birthDate, 0, sizeof(birthDate));
    }
}

/**
 * @brief Renders menu screen.
 */
void ClientLayer::renderMenu() {
    TextCentered("MENU");

    float buttonWidth = ImGui::GetWindowSize().x / 4.0f;

    CenterItem(buttonWidth);
    if (ImGui::Button("Create room", ImVec2(buttonWidth, 0.0f)))
        m_screen = Screens::CreateRoom;
    CenterItem(buttonWidth);
    if (ImGui::Button("Join room", ImVec2(buttonWidth, 0.0f)))
        m_screen = Screens::JoinRoom;
    CenterItem(buttonWidth);
    if (ImGui::Button("Statistics", ImVec2(buttonWidth, 0.0f)))
        m_screen = Screens::PersonalStats;
    CenterItem(buttonWidth);
    if (ImGui::Button("Logout", ImVec2(buttonWidth, 0.0f))) {
        RequestHandler::logoutRequest();
        m_screen = Screens::Login;
    }
    CenterItem(buttonWidth);
    if (ImGui::Button("Exit", ImVec2(buttonWidth, 0.0f))) {
        RequestHandler::logoutRequest();
        m_app->Close();
    }
}

/**
 * @brief Renders createRoom screen.
 */
void ClientLayer::renderCreateRoom() {
    TextCentered("CREATE ROOM");

    float inputWidth = ImGui::GetWindowSize().x / 3.0f;
    ImGui::PushItemWidth(inputWidth);

    CenterItem(inputWidth);
    static char roomName[128] = "";
    ImGui::InputTextWithHint("##roomName", "Room name", roomName,
                             IM_ARRAYSIZE(roomName));
    CenterItem(inputWidth);
    static int maxUsers = 5;
    limitedInputInt("Max users", &maxUsers, 1, 10);
    CenterItem(inputWidth);
    static int questionCount = 10;
    limitedInputInt("Question count", &questionCount, 1, 30);
    CenterItem(inputWidth);
    static int answerTimeout = 20;
    limitedInputInt("Answer timeout", &answerTimeout, 5, 120);

    ImGui::PopItemWidth();

    float buttonWidth = ImGui::GetWindowSize().x / 4.0f;
    if (strcmp(roomName, "")) {
        CenterItem(buttonWidth);
        if (ImGui::Button("Create room", ImVec2(buttonWidth, 0.0f))) {
            RequestHandler::createRoomRequest(roomName, maxUsers, questionCount,
                                              answerTimeout);

            m_isAdmin = true;

            m_screen = Screens::Room;
        }
    }

    CenterItem(buttonWidth);
    if (ImGui::Button("Back", ImVec2(buttonWidth, 0.0f)))
        m_screen = Screens::Menu;

    if (m_screen != Screens::CreateRoom) {
        memset(roomName, 0, sizeof(roomName));
        maxUsers = 5;
        questionCount = 10;
        answerTimeout = 20;
    }
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

    float buttonWidth = ImGui::GetWindowSize().x / 4.0f;
    if (selectedRoom != -1) {
        CenterItem(buttonWidth);
        if (ImGui::Button("Join room", ImVec2(buttonWidth, 0.0f))) {
            RequestHandler::joinRoomRequest(selectedRoom);

            m_isAdmin = false;

            m_screen = Screens::Room;
        }
    }

    CenterItem(buttonWidth);
    if (ImGui::Button("Back", ImVec2(buttonWidth, 0.0f)))
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

    float buttonWidth = ImGui::GetWindowSize().x / 4.0f;
    CenterItem(buttonWidth);
    if (ImGui::Button("Back", ImVec2(buttonWidth, 0.0f)))
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
        TextCentered(i.c_str());
    }

    float buttonWidth = ImGui::GetWindowSize().x / 4.0f;
    CenterItem(buttonWidth);
    if (ImGui::Button("Back", ImVec2(buttonWidth, 0.0f)))
        m_screen = Screens::Menu;
}

/**
 * @brief Render room screen.
 */
void ClientLayer::renderRoom() {
    static GetRoomStateResponse roomState;
    m_roomState = roomState;
    static float getRoomStateCounter = 0;
    if (count(&getRoomStateCounter))
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
        float buttonWidth = ImGui::GetWindowSize().x / 8.0f - 5.0f;
        CenterItem(buttonWidth + 5.0f, 3.0f / 7.0f);
        if (ImGui::Button("Start game", ImVec2(buttonWidth, 0.0f))) {
            RequestHandler::startGameRequest();
            m_screen = Screens::Game;
        }
        ImGui::SameLine();
        CenterItem(buttonWidth - 2.5f, 4.0f / 7.0f);
        if (ImGui::Button("Close room", ImVec2(buttonWidth, 0.0f))) {
            RequestHandler::closeRoomRequest();
            m_screen = Screens::Menu;
        }
    } else {
        float buttonWidth = ImGui::GetWindowSize().x / 4.0f;
        CenterItem(buttonWidth);
        if (ImGui::Button("Leave room", ImVec2(buttonWidth, 0.0f))) {
            RequestHandler::leaveRoomRequest();
            m_screen = Screens::Menu;
        }
    }
}

/**
 * @brief Render game screen.
 */
void ClientLayer::renderGame() {
    static int questionCount = 0;
    if (questionCount == m_roomState.questionCount) {
        questionCount = 0;
        m_screen = Screens::Results;
    }

    static GetQuestionResponse question = {
        0, "", std::map<unsigned int, std::string>()};
    static SubmitAnswerResponse submit;

    static bool hasQuestion = false;
    static bool showResult = false;
    static unsigned int selectedAnswer = -1;

    const float maxQuestionTime = m_roomState.answerTimeout;
    static float questionTimeCounter = maxQuestionTime;
    static float resultTimeCounter = m_maxCounterTime;

    // Question countdown
    if (hasQuestion) {
        if (count(&questionTimeCounter, maxQuestionTime)) {
            submit = RequestHandler::submitAnswerRequest(-1, 0);
            hasQuestion = false;
            showResult = true;
            selectedAnswer = -1;
        }
    }

    // Result countdown
    if (showResult) {
        if (count(&resultTimeCounter)) {
            showResult = false;
            questionTimeCounter = maxQuestionTime;
            questionCount++;
        }
    }

    // Get new question
    if (!hasQuestion && !showResult) {
        question = RequestHandler::getQuestionRequest();
        if (question.status == 1)
            hasQuestion = true;
        selectedAnswer = -1;
    }

    if (!hasQuestion && !showResult) {
        TextCentered("Waiting for question...");
    } else {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2)
               << questionTimeCounter; // Format time to %f.2
        ImGui::Text(stream.str().c_str());

        TextCentered(question.question.c_str());

        for (auto i : question.answers) {
            if (showResult) {
                ImGui::PushID(1);
                if (i.first == submit.correctAnswer) {
                    // Make button green.
                    ImGui::PushStyleColor(
                        ImGuiCol_Button,
                        (ImVec4)ImColor::HSV(0.35f, 0.95f, 0.7f));
                    ImGui::PushStyleColor(
                        ImGuiCol_ButtonHovered,
                        (ImVec4)ImColor::HSV(0.35f, 0.95f, 0.7f));
                    ImGui::PushStyleColor(
                        ImGuiCol_ButtonActive,
                        (ImVec4)ImColor::HSV(0.35f, 0.95f, 0.7f));
                } else if (i.first == selectedAnswer) {
                    // Make button red.
                    ImGui::PushStyleColor(
                        ImGuiCol_Button,
                        (ImVec4)ImColor::HSV(0.0f, 0.95f, 0.95f));
                    ImGui::PushStyleColor(
                        ImGuiCol_ButtonHovered,
                        (ImVec4)ImColor::HSV(0.0f, 0.95f, 0.95f));
                    ImGui::PushStyleColor(
                        ImGuiCol_ButtonActive,
                        (ImVec4)ImColor::HSV(0.0f, 0.95f, 0.95f));
                } else {
                    // Make button grey.
                    ImGui::PushStyleColor(
                        ImGuiCol_Button,
                        (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(
                        ImGuiCol_ButtonHovered,
                        (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(
                        ImGuiCol_ButtonActive,
                        (ImVec4)ImColor::HSV(0.0f, 0.0f, 0.5f));
                }
            }
            float buttonWidth = ImGui::GetWindowSize().x / 4.0f;
            CenterItem(buttonWidth);
            if (ImGui::Button(i.second.c_str(), ImVec2(buttonWidth, 0.0f))) {
                submit = RequestHandler::submitAnswerRequest(
                    i.first, questionTimeCounter);
                hasQuestion = false;
                showResult = true;
            }
            if (showResult) {
                if (selectedAnswer == -1) {
                    // Question timed out.
                    selectedAnswer =
                        i.first; // Change selectedAnswer so there would be no
                                 // incorrect highlight.
                    continue;
                }
                ImGui::PopStyleColor(3);
                ImGui::PopID();
            }
        }
    }

    float buttonWidth = ImGui::GetWindowSize().x / 5.0f;
    CenterItem(buttonWidth);
    if (ImGui::Button("Leave game", ImVec2(buttonWidth, 0.0f))) {
        RequestHandler::leaveGameRequest();
        m_screen = Screens::Menu;
    }
}

/**
 * @brief Renders results screen.
 */
void ClientLayer::renderResults() {
    static GetGameResultsResponse results = {0, std::vector<PlayerResults>()};
    static float getResultsCounter = 0;
    if (count(&getResultsCounter) && results.status == 0) {
        results = RequestHandler::getGameResultsRequest();
    }

    if (results.status == 0) {
        TextCentered("Please wait for all the players to finish...");
        return;
    }

    if (ImGui::BeginTable("Room data", 3,
                          ImGuiTableFlags_Resizable |
                              ImGuiTableFlags_NoSavedSettings |
                              ImGuiTableFlags_Borders)) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Username");

        ImGui::TableNextColumn();
        ImGui::Text("Correct answers");

        ImGui::TableNextColumn();
        ImGui::Text("Average answer time");

        for (auto i : results.results) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text(i.username.c_str());

            std::string answers =
                std::to_string(i.correctAnswerCount) + "/" +
                std::to_string(i.correctAnswerCount + i.wrongAnswerCount);
            ImGui::TableNextColumn();
            ImGui::Text(answers.c_str());

            ImGui::TableNextColumn();
            ImGui::Text(std::to_string(i.averageAnswerTime).c_str());
        }

        ImGui::EndTable();
    }

    float buttonWidth = ImGui::GetWindowSize().x / 4.0f;
    CenterItem(buttonWidth);
    if (ImGui::Button("Menu", ImVec2(buttonWidth, 0.0f)))
        m_screen = Screens::Menu;
}
