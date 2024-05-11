#pragma once

class SolarScene : public Scene
{
public:
	SolarScene();
	~SolarScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	Planet* sun;
	Planet* earth;
	Planet* moon;
};
