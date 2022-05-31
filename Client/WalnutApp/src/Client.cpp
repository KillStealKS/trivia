#include "ClientLayer.h"
#include "Walnut/EntryPoint.h"

Walnut::Application *Walnut::CreateApplication(int argc, char **argv) {
    Walnut::ApplicationSpecification spec;
    spec.Name = "Trivia Client";

    Walnut::Application *app = new Walnut::Application(spec);
    app->PushLayer<ClientLayer>();
    app->SetMenubarCallback([app]() {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit")) {
                app->Close();
            }
            ImGui::EndMenu();
        }
    });
    return app;
}