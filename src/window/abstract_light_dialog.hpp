
#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/clrpicker.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/gbsizer.h>
#include <wx/stattext.h>
#include <wx/radiobut.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

class AbstractLightDialog : public wxDialog
{
private:
	
protected:
	wxColourPickerCtrl* ambiant_light_color;
	wxTextCtrl* ambiant_light_s;
	wxChoice* m_choice10;
	wxCheckBox* enable_light;
	wxChoice* m_choice11;
	wxStaticText* m_staticText15;
	wxTextCtrl* 	direction_x;
	wxTextCtrl* 	direction_y;
	wxTextCtrl* 	direction_z;
	wxStaticText* m_staticText16;
	wxTextCtrl* position_x;
	wxTextCtrl* position_y;
	wxTextCtrl* position_z;
	wxTextCtrl* cutoff_angle;
	wxColourPickerCtrl* light_color;
	wxRadioButton* shadow_map;
	wxRadioButton* shadow_volume;
	wxStaticText* m_staticText20;
	wxTextCtrl* shadow_width;
	wxStaticText* m_staticText21;
	wxTextCtrl* shadow_height;
	wxStaticText* m_staticText22;
	wxTextCtrl* shadow_near;
	wxStaticText* m_staticText24;
	wxTextCtrl* shadow_far;
	
	// Virtual event handlers, override them in your derived class
	virtual void OnAmbiantLightChange( wxColourPickerEvent& event ) { event.Skip(); }
	virtual void OnAmbiantLightSChange( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnLightSelect( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnLightChecke( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnLightTypeChange( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnLightPositionChange( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnLightDirectionChange( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnLightCutoffChange( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnLightColoeChange( wxColourPickerEvent& event ) { event.Skip(); }
	virtual void OnShadowTypeChange( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnShadowViewChange( wxCommandEvent& event ) { event.Skip(); }
	
	
public:
	
	AbstractLightDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
	
	~AbstractLightDialog();
	
};

