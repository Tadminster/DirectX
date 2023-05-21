#include "stdafx.h"
#include "Player.h"
#include "Ball.h"
#include "Main.h"

Main::Main()
{
	for (auto& player : player)
		player = new Player();

    for (auto& goalpost : goalpost)
        goalpost = new Player();

	ball = new Ball();
}

Main::~Main()
{
}

void Main::Init()
{
	player[0]->Init(Vector2(-app.GetWidth() / 4.f, 0), false);
	player[1]->Init(Vector2(app.GetWidth() / 4.f, 0), true);

    goalpost[0]->Init(Vector2(-app.GetHalfWidth(), 0), false);
    goalpost[1]->Init(Vector2(app.GetHalfWidth(), 0), true);
    for (auto& goalpost : goalpost)
    {
        goalpost->hasAxis = false;
        goalpost->scale = Vector2(100.f, 100.f);
    }

	ball->Init(Vector2(0, 0), true);
    ball->speed = 0;
}

void Main::Release()
{
   
}

void Main::Update()
{
    ImGui::Text("Score \n");
    ImGui::Text("Player 1 : %d\n", player[0]->score);
    ImGui::Text("Player 2 : %d\n", player[1]->score);

    ImGui::Text("\n\n\n");
    ImGui::Text("Keys\n");
    ImGui::Text("1p move: [W][A][S][D] \n");
    ImGui::Text("2p move: [UP][DOWN][LEFT][RIGHT]\n");

    // 플레이어 업데이트, 이동, 충돌처리
	for (auto& player : player)
		{
			player->Update();
			ball->collision(player);
		}

    // 플레이어 이동
    if (INPUT->KeyPress('W'))
            player[0]->Control(UP);
    if (INPUT->KeyPress('S'))
            player[0]->Control(DOWN);
    if (INPUT->KeyPress('A'))
            player[0]->Control(LEFT);
    if (INPUT->KeyPress('D'))
            player[0]->Control(RIGHT);
    
    if (INPUT->KeyPress(VK_UP))
        player[1]->Control(UP);
    if (INPUT->KeyPress(VK_DOWN))
        player[1]->Control(DOWN);
    if (INPUT->KeyPress(VK_LEFT))
        player[1]->Control(LEFT);
    if (INPUT->KeyPress(VK_RIGHT))
        player[1]->Control(RIGHT);

    // 골대 업데이트
    for (auto& goalpost : goalpost)
        goalpost->Update();
    
    // 득점처리
    if (ball->collision(goalpost[0]))
    {
        player[1]->score++;
        Init();
    }
    else if (ball->collision(goalpost[1]))
    {
        player[0]->score++;
        Init();
    }



	ball->Update();
}

void Main::LateUpdate()
{
    // 볼이 맵 밖을 벗어날 때 충돌처리
    int map_side{ 10 }; //
    // x축
    if (ball->GetWorldPos().x < -app.GetHalfWidth() + map_side)
    {
        ball->SetWorldPosX(-app.GetHalfWidth() + map_side);
        ball->reflection_y();
        // ball->rotation.z = atan2f(ball->get_right().y, -ball->get_right().x);
    }
    else if (ball->GetWorldPos().x > app.GetHalfWidth() - map_side)
    {
        ball->SetWorldPosX(app.GetHalfWidth() - map_side);
        ball->reflection_y();
        // ball->rotation.z = atan2f(ball->get_right().y, -ball->get_right().x);
    }
    // y축
    if (ball->GetWorldPos().y < -app.GetHalfHeight() + map_side)
    {
        ball->SetWorldPosY(-app.GetHalfHeight() + map_side);
        ball->reflection_x();
        // ball->rotation.z = atan2f(-ball->get_right().y, ball->get_right().x);
    }
    else if (ball->GetWorldPos().y > app.GetHalfHeight() - map_side)
    {
        ball->SetWorldPosY(app.GetHalfHeight() - map_side);
        ball->reflection_x();
        // ball->rotation.z = atan2f(-ball->get_right().y, ball->get_right().x);
    }
}

void Main::Render()
{
	for (auto& player : player)
		player->Render();

    for (auto& goalpost : goalpost)
        goalpost->Render();

	ball->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(800.0f,600.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}