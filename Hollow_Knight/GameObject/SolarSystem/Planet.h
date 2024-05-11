#pragma once

class Planet : public Polygons
{
public:
	Planet(float radius, float rotationSpeed, float revolutionSpeed, UINT sectorCount = 36, Vector4 color = Vector4(1, 0, 0, 1));
	~Planet();

	void UpdateWorld() override;

	void Update(); // 여기서 회전시킬거임

private:

	float rotationSpeed; //자전 속도

	float revolutionSpeed; //공전 속도
	float revolutionAngle; //공전 각도
};
