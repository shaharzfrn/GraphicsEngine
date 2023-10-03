//
//  light_dialog.hpp
//  CGApp
//
//  Created by Shahar Zafran on 21/01/2023.
//

#ifndef light_dialog_hpp
#define light_dialog_hpp

#include <stdio.h>

#include "abstract_light_dialog.hpp"

class LightDialog : public AbstractLightDialog {
	
	int selected_light_index;
	
public:
	
	LightDialog();
	
	virtual void OnAmbiantLightChange( wxColourPickerEvent& event );
	virtual void OnAmbiantLightSChange( wxCommandEvent& event );
	virtual void OnLightSelect( wxCommandEvent& event );
	virtual void OnLightChecke( wxCommandEvent& event );
	virtual void OnLightTypeChange( wxCommandEvent& event );
	virtual void OnLightPositionChange( wxCommandEvent& event );
	virtual void OnLightDirectionChange( wxCommandEvent& event );
	virtual void OnLightCutoffChange( wxCommandEvent& event );
	virtual void OnLightColorChange( wxColourPickerEvent& event );
	virtual void OnShadowTypeChange( wxCommandEvent& event );
	virtual void OnShadowViewChange( wxCommandEvent& event );
	
	void Update();
};



#endif /* light_dialog_hpp */
