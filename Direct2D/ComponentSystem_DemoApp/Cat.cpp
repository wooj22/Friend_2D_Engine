#include "Cat.h"

void Cat::Awake()
{
	transform = AddComponent<Transform>();
	sr = AddComponent<SpriteRenderer>();
	tr = AddComponent<WorldTextRenderer>();
	catController = AddComponent<CatController>();
}

void Cat::Start() 
{
	
}

void Cat::Update()
{
	
}

void Cat::Destroyed() 
{
	
}