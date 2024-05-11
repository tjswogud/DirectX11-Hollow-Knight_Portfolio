#include "Framework.h"
#include "Map.h"

Map::Map()
{
	knight_map = new Object(L"knight_map.png");
	knight_map->Pos() = WIN_CENTER;
	//knight_map->Scale().x *= 1.0f, knight_map->Scale().y *= 1.0f;

	door = new Object(L"door.png");
	door->Pos() = Vector2{2753, 468};

	door2 = new Object(L"door2.png");
	door2->Pos() = Vector2{ -1325, 74 };

	Collider* collider = new ColliderRect(Vector2(650, 50));
	collider->Pos() = { -1125, -65 };
	rect_maps.push_back(collider);

	Collider* collider1 = new ColliderRect(Vector2(100, 1000)); // 왼쪽 벽
	collider1->Pos() = { -1480, 200 };
	rect_maps.push_back(collider1);

	Collider* collider2 = new ColliderRect(Vector2(460, 100));
	collider2->Pos() = { -1240, 230 };
	rect_maps.push_back(collider2);

	Collider* collider3 = new ColliderRect(Vector2(1010, 230));
	collider3->Pos() = { -380, -50 };
	rect_maps.push_back(collider3);

	Collider* collider4 = new ColliderRect(Vector2(860, 270));
	collider4->Pos() = { -390, 100 };
	rect_maps.push_back(collider4);

	Collider* collider5 = new ColliderRect(Vector2(660, 150));
	collider5->Pos() = { 400, -200 };
	rect_maps.push_back(collider5);

	Collider* collider6 = new ColliderRect(Vector2(1050, 220));
	collider6->Pos() = { 770, 180 };
	rect_maps.push_back(collider6);

	Collider* collider7 = new ColliderRect(Vector2(600, 220));
	collider7->Pos() = { 1500, 0 };
	rect_maps.push_back(collider7);

	Collider* collider8 = new ColliderRect(Vector2(1000, 220));
	collider8->Pos() = { 2200, -100 };
	rect_maps.push_back(collider8);

	Collider* collider9 = new ColliderRect(Vector2(330, 450));
	collider9->Pos() = { 2770, 150 };
	rect_maps.push_back(collider9);

	Collider* collider10 = new ColliderRect(Vector2(100, 800)); // 오른쪽 벽
	collider10->Pos() = { 2930, 700 };
	rect_maps.push_back(collider10);

	Collider* collider11 = new ColliderRect(Vector2(200, 50)); // 오른쪽 공중 계단 1
	collider11->Pos() = { 1950, 305 };
	rect_maps.push_back(collider11);

	Collider* collider12 = new ColliderRect(Vector2(110, 35)); // 오른쪽 공중 계단 2
	collider12->Pos() = { 2315, 325 };
	rect_maps.push_back(collider12);

	Collider* collider13 = new ColliderRect(Vector2(280, 700)); // 천장 길목 왼쪽
	collider13->Pos() = { 565, 840 };
	rect_maps.push_back(collider13);

	Collider* collider14 = new ColliderRect(Vector2(275, 1210)); // 천장 길목 오른쪽 
	collider14->Pos() = { 1070, 1095 };
	rect_maps.push_back(collider14);

	Collider* collider15 = new ColliderRect(Vector2(120, 10));
	collider15->Pos() = { 2750, 378 };
	rect_maps.push_back(collider15);

	// 보스방
	Collider* collider16 = new ColliderRect(Vector2(2850, 50));
	collider16->Pos() = { 8000, -255 };
	rect_maps.push_back(collider16);

	// 보스방 왼벽
	Collider* collider17 = new ColliderRect(Vector2(50, 1500));
	collider17->Pos() = { 6590, 200 };
	rect_maps.push_back(collider17);

	// 보스방 오른벽
	Collider* collider18 = new ColliderRect(Vector2(50, 1500));
	collider18->Pos() = { 9433, 200 };
	rect_maps.push_back(collider18);

	// 보스방 이미지
	boss_room = new Object(L"boss_room.png");
	boss_room->Pos() = Vector2{ 8000, 290 };
}

Map::~Map()
{
	delete knight_map;
	delete door;
	delete door2;
	delete boss_room;

	for (Collider* collider : rect_maps)
		delete collider;

	rect_maps.clear();
}

void Map::Update()
{
	knight_map->UpdateWorld();
	door->UpdateWorld();
	door2->UpdateWorld();
	boss_room->UpdateWorld();

	for (Collider* collider : rect_maps)
		collider->UpdateWorld();

}

void Map::Render()
{
	knight_map->Render();
	door->Render();
	door2->Render();
	boss_room->Render();

	for (Collider* collider : rect_maps)
	{
		collider->Render();
		/*ImGui::BeginChild("Map", ImVec2(200, 25 * rect_maps.size()), true);
		collider->Debug();
		ImGui::EndChild();*/
	}


}



