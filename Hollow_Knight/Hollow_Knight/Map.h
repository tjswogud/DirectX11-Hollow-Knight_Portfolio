#pragma once

class Map
{
public:
	Map();
	~Map();

	void Update();
	void Render();
	
	vector<Collider*> GetFloors() { return rect_maps; } // Collider*�� ���͸� ��ȯ

private:
	vector<Collider*> rect_maps; // �ٴ�

	Object* knight_map; // ���

	Object* door;

	Object* door2;

	Object* boss_room;
};
