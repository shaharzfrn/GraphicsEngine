//
//  window.hpp
//  CGApp
//
//  Created by Shahar Zafran on 01/01/2023.
//

#ifndef window_hpp
#define window_hpp

#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <stdio.h>

#include "frame.hpp"
#include "panel.hpp"

class Window : public wxApp {
	
public:
	virtual bool OnInit();
};


#endif /* window_hpp */
