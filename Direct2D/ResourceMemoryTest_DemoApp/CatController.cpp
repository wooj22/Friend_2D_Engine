#include "CatController.h"

void CatController::Awake()
{
	// get component
	tr = this->gameObject->GetComponent<Transform>();

	// transform setting
	auto RandFloat = [](float min, float max) {
		return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
		};

	float posX = RandFloat(-640.0f, 640.0f);
	float posY = RandFloat(-480.0f, 480.0f);
	float scale = RandFloat(0.05f, 0.3f);

	tr->SetPosition(-posX, posY);
	tr->SetScale(scale, scale);
}

void CatController::Update()
{
	tr->Rotate(rotationSpeed * rotationDirection * Time::GetDeltaTime());
}