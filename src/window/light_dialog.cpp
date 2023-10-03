//
//  light_dialog.cpp
//  CGApp
//
//  Created by Shahar Zafran on 21/01/2023.
//

#include "light_dialog.hpp"
#include "light.hpp"
#include "shadow.hpp"

#include "math.hpp"

#include "application.hpp"
#include "camera.hpp"

LightDialog::LightDialog(): AbstractLightDialog(nullptr) {
	selected_light_index = 0;
}

void LightDialog::OnAmbiantLightChange( wxColourPickerEvent& event ) {
	
	wxColour color = event.GetColour();
	
	CGL::ambiant_light.color.x = color.GetRed() / 255.0f;
	CGL::ambiant_light.color.y = color.GetGreen() / 255.0f;
	CGL::ambiant_light.color.z = color.GetBlue() / 255.0f;
	
	CGL::app->Refresh();
	
}
void LightDialog::OnAmbiantLightSChange( wxCommandEvent& event ) {
	try {
		float s = std::stof(std::string(ambiant_light_s->GetValue()));
		CGL::ambiant_light.strength = s;
	} catch(...) {
		ambiant_light_s->SetValue(std::to_string(CGL::ambiant_light.strength));
	}
	
	CGL::app->Refresh();
}
void LightDialog::OnLightSelect( wxCommandEvent& event ) {
	
	selected_light_index = event.GetSelection();
	
	Update();
}
void LightDialog::OnLightChecke( wxCommandEvent& event ) {
	CGL::lights[selected_light_index].enabled = event.IsChecked();
	CGL::app->Refresh();
}
void LightDialog::OnLightTypeChange( wxCommandEvent& event ) {
	
	printf("%d\n", event.GetSelection());
	CGL::lights[selected_light_index].type = (LightType) event.GetSelection();
	
	if (CGL::shadows[selected_light_index] != nullptr) delete CGL::shadows[selected_light_index];
	
	if (shadow_map->GetValue())
		CGL::shadows[selected_light_index] = new ShadowMap(CGL::lights[selected_light_index], {0 ,0 ,0}, CGL::shadows_settings[selected_light_index]);
	else {
		CGL::shadows[selected_light_index] = new ShadowVolume(CGL::lights[selected_light_index], {0 ,0 ,0}, CGL::shadows_settings[selected_light_index]);
	}
	
	CGL::app->Refresh();
}
void LightDialog::OnLightPositionChange( wxCommandEvent& event ) {
	
	try {
		float x = std::stof(std::string(position_x->GetValue()));
		CGL::lights[selected_light_index].position.x = x;
	} catch(...) {
		position_x->SetValue(std::to_string(CGL::lights[selected_light_index].position.x));
	}
	
	try {
		float y = std::stof(std::string(position_y->GetValue()));
		CGL::lights[selected_light_index].position.y = y;
	} catch(...) {
		position_y->SetValue(std::to_string(CGL::lights[selected_light_index].position.y));
	}
	
	try {
		float z = std::stof(std::string(position_z->GetValue()));
		CGL::lights[selected_light_index].position.z = z;
	} catch(...) {
		position_z->SetValue(std::to_string(CGL::lights[selected_light_index].position.z));
	}
	
	if (CGL::shadows[selected_light_index] != nullptr) delete CGL::shadows[selected_light_index];
	
	if (shadow_map->GetValue())
		CGL::shadows[selected_light_index] = new ShadowMap(CGL::lights[selected_light_index], {0 ,0 ,0}, CGL::shadows_settings[selected_light_index]);
	else
		CGL::shadows[selected_light_index] = new ShadowVolume(CGL::lights[selected_light_index], {0 ,0 ,0}, CGL::shadows_settings[selected_light_index]);
	
	CGL::app->Refresh();
	
}
void LightDialog::OnLightDirectionChange( wxCommandEvent& event ) {
	
	try {
		float x = std::stof(std::string(direction_x->GetValue()));
		CGL::lights[selected_light_index].direction.x = x;
	} catch(...) {
		direction_x->SetValue(std::to_string(CGL::lights[selected_light_index].direction.x));
	}
	
	try {
		float y = std::stof(std::string(direction_y->GetValue()));
		CGL::lights[selected_light_index].direction.y = y;
	} catch(...) {
		direction_y->SetValue(std::to_string(CGL::lights[selected_light_index].direction.y));
	}
	
	try {
		float z = std::stof(std::string(direction_z->GetValue()));
		CGL::lights[selected_light_index].direction.z = z;
	} catch(...) {
		direction_z->SetValue(std::to_string(CGL::lights[selected_light_index].direction.z));
	}
	
	if (CGL::shadows[selected_light_index] != nullptr) delete CGL::shadows[selected_light_index];
	
	if (shadow_map->GetValue())
		CGL::shadows[selected_light_index] = new ShadowMap(CGL::lights[selected_light_index], {0 ,0 ,0}, CGL::shadows_settings[selected_light_index]);
	else
		CGL::shadows[selected_light_index] = new ShadowVolume(CGL::lights[selected_light_index], {0 ,0 ,0}, CGL::shadows_settings[selected_light_index]);
	
	CGL::app->Refresh();
	
}

void LightDialog::OnLightCutoffChange( wxCommandEvent& event ) {
	
	try {
		float angle = std::stof(std::string(cutoff_angle->GetValue()));
		CGL::lights[selected_light_index].cutoff_angle = cos((angle * ( M_PI / 180.0f)));
		
	} catch(...) {
		cutoff_angle->SetValue(std::to_string(CGL::lights[selected_light_index].cutoff_angle));
	}
	CGL::app->Refresh();
}

void LightDialog::OnLightColorChange( wxColourPickerEvent& event ) {
	wxColour color = event.GetColour();
	
	CGL::lights[selected_light_index].color.x = color.GetRed() / 255.0f;
	CGL::lights[selected_light_index].color.y = color.GetGreen() / 255.0f;
	CGL::lights[selected_light_index].color.z = color.GetBlue() / 255.0f;
	
	CGL::app->Refresh();
}

void LightDialog::OnShadowTypeChange( wxCommandEvent& event ) {
	
	if (CGL::shadows[selected_light_index] != nullptr) delete CGL::shadows[selected_light_index];
	
	if (shadow_map->GetValue())
		CGL::shadows[selected_light_index] = new ShadowMap(CGL::lights[selected_light_index], {0 ,0 ,0}, CGL::shadows_settings[selected_light_index]);
	else
		CGL::shadows[selected_light_index] = new ShadowVolume(CGL::lights[selected_light_index], {0 ,0 ,0}, CGL::shadows_settings[selected_light_index]);
	
	CGL::app->Refresh();
}
void LightDialog::OnShadowViewChange( wxCommandEvent& event ) {
	
	
	try {
		float width = std::stof(std::string(shadow_width->GetValue()));
		CGL::shadows_settings[selected_light_index].width = width;
	} catch(...) {
		shadow_width->SetValue(std::to_string(CGL::shadows_settings[selected_light_index].width));
	}
	
	try {
		float height = std::stof(std::string(shadow_height->GetValue()));
		CGL::shadows_settings[selected_light_index].height = height;
	} catch(...) {
		shadow_height->SetValue(std::to_string(CGL::shadows_settings[selected_light_index].height));
	}
	
	try {
		float near = std::stof(std::string(shadow_near->GetValue()));
		CGL::shadows_settings[selected_light_index].near = near;
	} catch(...) {
		shadow_near->SetValue(std::to_string(CGL::shadows_settings[selected_light_index].near));
	}
	
	try {
		float far = std::stof(std::string(shadow_far->GetValue()));
		CGL::shadows_settings[selected_light_index].far = far;
	} catch(...) {
		shadow_far->SetValue(std::to_string(CGL::shadows_settings[selected_light_index].far));
	}
	
	if (CGL::shadows[selected_light_index] != nullptr) delete CGL::shadows[selected_light_index];
	
	if (shadow_map->GetValue())
		CGL::shadows[selected_light_index] = new ShadowMap(CGL::lights[selected_light_index], {0 ,0 ,0}, CGL::shadows_settings[selected_light_index]);
	else
		CGL::shadows[selected_light_index] = new ShadowVolume(CGL::lights[selected_light_index], {0 ,0 ,0}, CGL::shadows_settings[selected_light_index]);
	CGL::app->Refresh();
}


void LightDialog::Update() {
	vec3 color = CGL::ambiant_light.color * 255;
	ambiant_light_color->SetColour(wxColor(color.x, color.y, color.z, 255.0f));
	ambiant_light_s->SetValue(std::to_string(CGL::ambiant_light.strength));
	
	m_choice10->SetSelection(selected_light_index);
	
	enable_light->SetValue(CGL::lights[selected_light_index].enabled);
	m_choice11->SetSelection(CGL::lights[selected_light_index].type);
	
	color = CGL::lights[selected_light_index].color * 255;
	light_color->SetColour(wxColor(color.x, color.y, color.z, 255.0f));
	
	vec3 direction = CGL::lights[selected_light_index].direction;
	direction_x->SetValue(std::to_string(direction.x));
	direction_y->SetValue(std::to_string(direction.y));
	direction_z->SetValue(std::to_string(direction.z));
	
	vec3 position = CGL::lights[selected_light_index].position;
	position_x->SetValue(std::to_string(position.x));
	position_y->SetValue(std::to_string(position.y));
	position_z->SetValue(std::to_string(position.z));
	
	shadow_map->SetValue(CGL::shadows_settings[selected_light_index].type == MAP_SHADOW);
	shadow_volume->SetValue(CGL::shadows_settings[selected_light_index].type == VOLUME_SHADOW);
	
	shadow_width->SetValue(std::to_string(CGL::shadows_settings[selected_light_index].width));
	shadow_height->SetValue(std::to_string(CGL::shadows_settings[selected_light_index].height));
	shadow_near->SetValue(std::to_string(CGL::shadows_settings[selected_light_index].near));
	shadow_far->SetValue(std::to_string(CGL::shadows_settings[selected_light_index].far));
}
