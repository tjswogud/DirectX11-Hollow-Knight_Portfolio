#pragma once

class Map
{
public:
	Map();
	~Map();

	void Update();
	void Render();
	
	vector<Collider*> GetFloors() { return rect_maps; } // Collider*¿¡ º¤ÅÍ¸¦ ¹ÝÈ¯

private:
	vector<Collider*> rect_maps; // ¹Ù´Ú

	Object* knight_map; // ¹è°æ

	Object* door;

	Object* door2;

	Object* boss_room;
};
