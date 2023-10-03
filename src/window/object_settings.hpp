//
//  object_settings.hpp
//  CGApp
//
//  Created by Shahar Zafran on 06/01/2023.
//

#ifndef object_settings_hpp
#define object_settings_hpp

#include <stdio.h>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/aui/aui.h>
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/clrpicker.h>
#include <wx/gbsizer.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/slider.h>
#include <wx/panel.h>

#include <stdio.h>

#include "model.hpp"
#include "application.hpp"
#include "loader.hpp"

class ObjectSettings : public wxPanel {
	
	Object *object;
	
	
protected:
	wxScrolledWindow* m_scrolledWindow1;
	wxRadioButton* shader_phong;
	wxRadioButton* shader_gouraud;
	wxRadioButton* shader_flat;
	wxCheckBox* polygon_front_cull;
	wxChoice* polygon_front_mode;
	wxButton* polygon_front_color;
	wxCheckBox* polygon_back_cull;
	wxChoice* polygon_back_mode;
	wxButton* polygon_back_color;
	wxCheckBox* object_silhouette_enable;
	wxButton* object_silhouette_color;
	wxCheckBox* object_silhouette_depth;
	wxCheckBox* object_transp_enable;
	wxButton* object_transp_none;
	wxButton* object_transp_full;
	wxSlider* object_transp_slide;
	wxStaticText* m_staticText12;
	wxTextCtrl* object_diffuse_k;
	wxCheckBox* object_shadow_interact;
	wxStaticText* m_staticText20;
	wxTextCtrl* object_specular_k;
	wxTextCtrl* object_specular_n;
	wxStaticText* m_staticText21;
	wxCheckBox* normal_vertex_enable;
	wxButton* normal_vertex_color;
	wxCheckBox* normal_vertex_use_calc;
	wxCheckBox* normal_reverse;
	wxCheckBox* normal_plane_enable;
	wxButton* normal_plane_color;
	wxCheckBox* normal_plane_use_calc;
	wxCheckBox* bounding_box_enable;
	wxColourPickerCtrl* bounding_box_color;
	wxChoice* bounding_box_mode;
	wxChoice* texture_select;
	wxStaticText* m_staticText25;
	wxTextCtrl* position_x;
	wxTextCtrl* position_y;
	wxTextCtrl* position_z;
	wxStaticText* m_staticText26;
	wxTextCtrl* rotation_x;
	wxTextCtrl* rotation_y;
	wxTextCtrl* rotation_z;
	wxStaticText* m_staticText27;
	wxTextCtrl* scale_x;
	wxTextCtrl* scale_y;
	wxTextCtrl* scale_z;
	
	void SetupObject();
	
	
	// Virtual event handlers, override them in your derived class
	virtual void OnShadowProgramChange( wxCommandEvent& event );
	virtual void OnPolygonFrontCullChange( wxCommandEvent& event );
	virtual void OnPolygonFrontModeChange( wxCommandEvent& event );
	virtual void OnPolygonFrontColorChange( wxCommandEvent& event );
	virtual void OnPolygonBackCullChange( wxCommandEvent& event );
	virtual void OnPolygonBackModeChange( wxCommandEvent& event );
	virtual void OnPolygonBackColorChange( wxCommandEvent& event );
	virtual void OnObjectSilhouetteCheck( wxCommandEvent& event );
	virtual void OnObjectSilhouetteColorClick( wxCommandEvent& event );
	virtual void OnObjectTranspCheck( wxCommandEvent& event );
	virtual void OnObjectTranspNoneClick( wxCommandEvent& event );
	virtual void OnObjectTranspFullClick( wxCommandEvent& event );
	virtual void OnObjectKdChange( wxCommandEvent& event );
	virtual void OnObjectShadowInteractCheck( wxCommandEvent& event );
	virtual void OnObjectKsChange( wxCommandEvent& event );
	virtual void OnObjectNsChange( wxCommandEvent& event );
	virtual void OnNormalVertexCheck( wxCommandEvent& event );
	virtual void OnNormalVertexColorClick( wxCommandEvent& event );
	virtual void OnNormalVertexUseCalcCheck( wxCommandEvent& event );
	virtual void OnNormalReverseCheck( wxCommandEvent& event );
	virtual void OnNormalPlaneCheck( wxCommandEvent& event );
	virtual void OnNormalPlaneColorClick( wxCommandEvent& event );
	virtual void OnNormalPlaneUseCalcCheck( wxCommandEvent& event );
	virtual void OnBoundingBoxCheck( wxCommandEvent& event );
	virtual void OnBoundingBoxColorChange( wxColourPickerEvent& event );
	virtual void OnBoundingBoxModeChange( wxCommandEvent& event );
	virtual void OnTextureChange( wxCommandEvent& event );
	virtual void OnPositionChange( wxCommandEvent& event );
	virtual void OnRotationChange( wxCommandEvent& event );
	virtual void OnScaleChange( wxCommandEvent& event );
	
public:
	
	ObjectSettings(wxAuiNotebook* ctrl, Object* object);
	~ObjectSettings();
	
	void OnFocus();
};


#endif /* object_settings_hpp */
