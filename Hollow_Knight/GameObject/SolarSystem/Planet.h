#pragma once

class Planet : public Polygons
{
public:
	Planet(float radius, float rotationSpeed, float revolutionSpeed, UINT sectorCount = 36, Vector4 color = Vector4(1, 0, 0, 1));
	~Planet();

	void UpdateWorld() override;

	void Update(); // ���⼭ ȸ����ų����

private:

	float rotationSpeed; //���� �ӵ�

	float revolutionSpeed; //���� �ӵ�
	float revolutionAngle; //���� ����
};
