#include "Cat.h"

void Cat::Awake()
{
	transform = AddComponent<Transform>();
	sr = AddComponent<SpriteRenderer>();
	tr = AddComponent<WorldTextRenderer>();
	catController = AddComponent<CatController>();
}

void Cat::SceneStartInit() 
{
	// find other component
	catController->fishTransform = GameObject::Find("Fish")->GetComponent<Transform>();
}

void Cat::Update()
{
	
}

void Cat::Destroyed() 
{
	
}