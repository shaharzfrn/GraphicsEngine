//
//  init.cpp
//  CGApp
//
//  Created by Shahar Zafran on 02/01/2023.
//

#include "init.hpp"

void InitApplication() {
	if (CGL::app == nullptr)
		CGL::app = new CGLApp();
}
