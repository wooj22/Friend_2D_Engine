#include "Cat.h"

void Cat::Awake()
{
	
}

void Cat::SceneStart() 
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