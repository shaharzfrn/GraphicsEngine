//
//  application.cpp
//  CGApp
//
//  Created by Shahar Zafran on 01/01/2023.
//

#include "application.hpp"


Application *app = nullptr;

void Application::SetUpdateFunc(std::function<void()> refresh) {
	this->refresh = refresh;
};
void Application::Refresh() {
	refresh();
};
