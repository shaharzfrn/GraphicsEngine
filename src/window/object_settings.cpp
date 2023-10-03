//
//  object_settings.cpp
//  CGApp
//
//  Created by Shahar Zafran on 06/01/2023.
//

#include "object_settings.hpp"

#include <wx/colordlg.h>
#include <string>

#include "bitmap_utils.hpp"


ObjectSettings::ObjectSettings(wxAuiNotebook* ctrl, Object* object): wxPanel(ctrl), object(object) {
	
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxVERTICAL );
	
	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer23;
	sbSizer23 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow1, wxID_ANY, wxT("Shader") ), wxHORIZONTAL );
	
	shader_phong = new wxRadioButton( sbSizer23->GetStaticBox(), wxID_ANY, wxT("Phong"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer23->Add( shader_phong, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	shader_gouraud = new wxRadioButton( sbSizer23->GetStaticBox(), wxID_ANY, wxT("Gouraud"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer23->Add( shader_gouraud, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	shader_flat = new wxRadioButton( sbSizer23->GetStaticBox(), wxID_ANY, wxT("Flat"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer23->Add( shader_flat, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizer23, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow1, wxID_ANY, wxT("Polygon Style") ), wxVERTICAL );
	
	wxGridBagSizer* gbSizer811;
	gbSizer811 = new wxGridBagSizer( 0, 0 );
	gbSizer811->SetFlexibleDirection( wxBOTH );
	gbSizer811->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	polygon_front_cull = new wxCheckBox( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Cull Front"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer811->Add( polygon_front_cull, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString polygon_front_modeChoices[] = { wxT("Solid"), wxT("Lines"), wxT("Points") };
	int polygon_front_modeNChoices = sizeof( polygon_front_modeChoices ) / sizeof( wxString );
	polygon_front_mode = new wxChoice( sbSizer5->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, polygon_front_modeNChoices, polygon_front_modeChoices, 0 );
	polygon_front_mode->SetSelection( 0 );
	gbSizer811->Add( polygon_front_mode, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	polygon_front_color = new wxButton( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Front Color"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer811->Add( polygon_front_color, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	polygon_back_cull = new wxCheckBox( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Cull Back"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer811->Add( polygon_back_cull, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString polygon_back_modeChoices[] = { wxT("Solid"), wxT("Lines"), wxT("Points") };
	int polygon_back_modeNChoices = sizeof( polygon_back_modeChoices ) / sizeof( wxString );
	polygon_back_mode = new wxChoice( sbSizer5->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, polygon_back_modeNChoices, polygon_back_modeChoices, 0 );
	polygon_back_mode->SetSelection( 0 );
	gbSizer811->Add( polygon_back_mode, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	polygon_back_color = new wxButton( sbSizer5->GetStaticBox(), wxID_ANY, wxT("Back Color"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer811->Add( polygon_back_color, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	
	sbSizer5->Add( gbSizer811, 0, 0, 5 );
	
	
	bSizer1->Add( sbSizer5, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow1, wxID_ANY, wxT("Object Style") ), wxVERTICAL );
	
	wxGridBagSizer* gbSizer13;
	gbSizer13 = new wxGridBagSizer( 0, 0 );
	gbSizer13->SetFlexibleDirection( wxBOTH );
	gbSizer13->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	object_silhouette_enable = new wxCheckBox( sbSizer6->GetStaticBox(), wxID_ANY, wxT(":"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer13->Add( object_silhouette_enable, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	object_silhouette_color = new wxButton( sbSizer6->GetStaticBox(), wxID_ANY, wxT("silhouette"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer13->Add( object_silhouette_color, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	object_silhouette_depth = new wxCheckBox( sbSizer6->GetStaticBox(), wxID_ANY, wxT("On Top"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer13->Add( object_silhouette_depth, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	object_transp_enable = new wxCheckBox( sbSizer6->GetStaticBox(), wxID_ANY, wxT(":"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer13->Add( object_transp_enable, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	object_transp_none = new wxButton( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Opaque"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer13->Add( object_transp_none, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	object_transp_full = new wxButton( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Transp"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer13->Add( object_transp_full, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	object_transp_slide = new wxSlider( sbSizer6->GetStaticBox(), wxID_ANY, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	gbSizer13->Add( object_transp_slide, wxGBPosition( 2, 0 ), wxGBSpan( 1, 3 ), wxALL|wxEXPAND, 5 );
	
	
	sbSizer6->Add( gbSizer13, 1, wxEXPAND, 5 );
	
	wxGridBagSizer* gbSizer18;
	gbSizer18 = new wxGridBagSizer( 0, 0 );
	gbSizer18->SetFlexibleDirection( wxBOTH );
	gbSizer18->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	gbSizer18->SetMinSize(250, -1);
	
	m_staticText12 = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Kd: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	gbSizer18->Add( m_staticText12, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	object_diffuse_k = new wxTextCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	gbSizer18->Add( object_diffuse_k, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	object_shadow_interact = new wxCheckBox( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Shadow"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer18->Add( object_shadow_interact, wxGBPosition( 0, 2 ), wxGBSpan( 1, 2 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText20 = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Ks:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	gbSizer18->Add( m_staticText20, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	object_specular_k = new wxTextCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	gbSizer18->Add( object_specular_k, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	object_specular_n = new wxTextCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	gbSizer18->Add( object_specular_n, wxGBPosition( 1, 3 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText21 = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Ns:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	gbSizer18->Add( m_staticText21, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer6->Add( gbSizer18, 0, wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizer6, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow1, wxID_ANY, wxT("Normals") ), wxVERTICAL );
	
	wxGridBagSizer* gbSizer19;
	gbSizer19 = new wxGridBagSizer( 0, 0 );
	gbSizer19->SetFlexibleDirection( wxBOTH );
	gbSizer19->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	normal_vertex_enable = new wxCheckBox( sbSizer7->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer19->Add( normal_vertex_enable, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	normal_vertex_color = new wxButton( sbSizer7->GetStaticBox(), wxID_ANY, wxT("Vertex"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer19->Add( normal_vertex_color, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	normal_vertex_use_calc = new wxCheckBox( sbSizer7->GetStaticBox(), wxID_ANY, wxT("Use Calc"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer19->Add( normal_vertex_use_calc, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	normal_reverse = new wxCheckBox( sbSizer7->GetStaticBox(), wxID_ANY, wxT("Reverse"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer19->Add( normal_reverse, wxGBPosition( 0, 3 ), wxGBSpan( 2, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	normal_plane_enable = new wxCheckBox( sbSizer7->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer19->Add( normal_plane_enable, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	normal_plane_color = new wxButton( sbSizer7->GetStaticBox(), wxID_ANY, wxT("Plane"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer19->Add( normal_plane_color, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	normal_plane_use_calc = new wxCheckBox( sbSizer7->GetStaticBox(), wxID_ANY, wxT("Use Calc"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer19->Add( normal_plane_use_calc, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer7->Add( gbSizer19, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizer7, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow1, wxID_ANY, wxT("Bounding Box") ), wxVERTICAL );
	
	wxGridBagSizer* gbSizer20;
	gbSizer20 = new wxGridBagSizer( 0, 0 );
	gbSizer20->SetFlexibleDirection( wxBOTH );
	gbSizer20->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	bounding_box_enable = new wxCheckBox( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer20->Add( bounding_box_enable, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bounding_box_color = new wxColourPickerCtrl( sbSizer8->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	gbSizer20->Add( bounding_box_color, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	wxString bounding_box_modeChoices[] = { wxT("Solid"), wxT("Lines"), wxT("Points") };
	int bounding_box_modeNChoices = sizeof( bounding_box_modeChoices ) / sizeof( wxString );
	bounding_box_mode = new wxChoice( sbSizer8->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, bounding_box_modeNChoices, bounding_box_modeChoices, 0 );
	bounding_box_mode->SetSelection( 3 );
	gbSizer20->Add( bounding_box_mode, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	
	sbSizer8->Add( gbSizer20, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizer8, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow1, wxID_ANY, wxT("Texture") ), wxVERTICAL );
	
	wxString texture_selectChoices[] = { wxT("None") };
	int texture_selectNChoices = sizeof( texture_selectChoices ) / sizeof( wxString );
	texture_select = new wxChoice( sbSizer9->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, texture_selectNChoices, texture_selectChoices, 0 );
	texture_select->SetSelection( 1 );
	sbSizer9->Add( texture_select, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizer9, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow1, wxID_ANY, wxT("Transform") ), wxVERTICAL );
	
	wxGridBagSizer* gbSizer21;
	gbSizer21 = new wxGridBagSizer( 0, 0 );
	gbSizer21->SetFlexibleDirection( wxBOTH );
	gbSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText25 = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Position:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	gbSizer21->Add( m_staticText25, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	position_x = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	gbSizer21->Add( position_x, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	position_y = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	gbSizer21->Add( position_y, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	position_z = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	gbSizer21->Add( position_z, wxGBPosition( 0, 3 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText26 = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Rotation:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	gbSizer21->Add( m_staticText26, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	rotation_x = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	gbSizer21->Add( rotation_x, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	rotation_y = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	gbSizer21->Add( rotation_y, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	rotation_z = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	gbSizer21->Add( rotation_z, wxGBPosition( 1, 3 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText27 = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Scale:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	gbSizer21->Add( m_staticText27, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	scale_x = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	gbSizer21->Add( scale_x, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	scale_y = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	gbSizer21->Add( scale_y, wxGBPosition( 2, 2 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	scale_z = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
	gbSizer21->Add( scale_z, wxGBPosition( 2, 3 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	sbSizer10->Add( gbSizer21, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizer10, 1, wxEXPAND, 5 );
	
	
	m_scrolledWindow1->SetSizer( bSizer1 );
	m_scrolledWindow1->Layout();
	bSizer1->Fit( m_scrolledWindow1 );
	bSizer38->Add( m_scrolledWindow1, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer38 );
	this->Layout();
	bSizer38->Fit( this );
	
	this->Centre( wxBOTH );
	
	
	SetupObject();
	
	
	// Connect Events
	shader_phong->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( ObjectSettings::OnShadowProgramChange ), NULL, this);
	shader_gouraud->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( ObjectSettings::OnShadowProgramChange ), NULL, this);
	shader_flat->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( ObjectSettings::OnShadowProgramChange ), NULL, this);
	polygon_front_cull->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnPolygonFrontCullChange ), NULL, this );
	polygon_front_mode->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ObjectSettings::OnPolygonFrontModeChange ), NULL, this );
	polygon_front_color->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjectSettings::OnPolygonFrontColorChange ), NULL, this );
	polygon_back_cull->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnPolygonBackCullChange ), NULL, this );
	polygon_back_mode->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ObjectSettings::OnPolygonBackModeChange ), NULL, this );
	polygon_back_color->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjectSettings::OnPolygonBackColorChange ), NULL, this );
	object_silhouette_enable->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnObjectSilhouetteCheck ), NULL, this );
	object_silhouette_color->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjectSettings::OnObjectSilhouetteColorClick ), NULL, this );
	object_transp_enable->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnObjectTranspCheck ), NULL, this );
	object_transp_none->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjectSettings::OnObjectTranspNoneClick ), NULL, this );
	object_transp_full->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjectSettings::OnObjectTranspFullClick ), NULL, this );
	object_diffuse_k->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnObjectKdChange ), NULL, this );
	object_shadow_interact->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnObjectShadowInteractCheck ), NULL, this );
	object_specular_k->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnObjectKsChange ), NULL, this );
	object_specular_n->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnObjectNsChange ), NULL, this );
	normal_vertex_enable->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnNormalVertexCheck ), NULL, this );
	normal_vertex_color->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjectSettings::OnNormalVertexColorClick ), NULL, this );
	normal_vertex_use_calc->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnNormalVertexUseCalcCheck ), NULL, this );
	normal_reverse->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnNormalReverseCheck ), NULL, this );
	normal_plane_enable->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnNormalPlaneCheck ), NULL, this );
	normal_plane_color->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjectSettings::OnNormalPlaneColorClick ), NULL, this );
	normal_plane_use_calc->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnNormalPlaneUseCalcCheck ), NULL, this );
	bounding_box_enable->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnBoundingBoxCheck ), NULL, this );
	bounding_box_color->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( ObjectSettings::OnBoundingBoxColorChange ), NULL, this );
	bounding_box_mode->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ObjectSettings::OnBoundingBoxModeChange ), NULL, this );
	texture_select->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ObjectSettings::OnTextureChange ), NULL, this );
	position_x->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnPositionChange ), NULL, this );
	position_y->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnPositionChange ), NULL, this );
	position_z->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnPositionChange ), NULL, this );
	rotation_x->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnRotationChange ), NULL, this );
	rotation_y->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnRotationChange ), NULL, this );
	rotation_z->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnRotationChange ), NULL, this );
	scale_x->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnScaleChange ), NULL, this );
	scale_y->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnScaleChange ), NULL, this );
	scale_z->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnScaleChange ), NULL, this );
}
ObjectSettings::~ObjectSettings() {
	// Disconnect Events
	polygon_front_cull->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnPolygonFrontCullChange ), NULL, this );
	polygon_front_mode->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ObjectSettings::OnPolygonFrontModeChange ), NULL, this );
	polygon_front_color->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjectSettings::OnPolygonFrontColorChange ), NULL, this );
	polygon_back_cull->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnPolygonBackCullChange ), NULL, this );
	polygon_back_mode->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ObjectSettings::OnPolygonBackModeChange ), NULL, this );
	polygon_back_color->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjectSettings::OnPolygonBackColorChange ), NULL, this );
	object_silhouette_enable->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnObjectSilhouetteCheck ), NULL, this );
	object_silhouette_color->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjectSettings::OnObjectSilhouetteColorClick ), NULL, this );
	object_transp_enable->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnObjectTranspCheck ), NULL, this );
	object_transp_none->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjectSettings::OnObjectTranspNoneClick ), NULL, this );
	object_transp_full->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjectSettings::OnObjectTranspFullClick ), NULL, this );
	object_diffuse_k->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnObjectKdChange ), NULL, this );
	object_shadow_interact->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnObjectShadowInteractCheck ), NULL, this );
	object_specular_k->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnObjectKsChange ), NULL, this );
	object_specular_n->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnObjectNsChange ), NULL, this );
	normal_vertex_enable->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnNormalVertexCheck ), NULL, this );
	normal_vertex_color->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjectSettings::OnNormalVertexColorClick ), NULL, this );
	normal_vertex_use_calc->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnNormalVertexUseCalcCheck ), NULL, this );
	normal_reverse->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnNormalReverseCheck ), NULL, this );
	normal_plane_enable->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnNormalPlaneCheck ), NULL, this );
	normal_plane_color->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ObjectSettings::OnNormalPlaneColorClick ), NULL, this );
	normal_plane_use_calc->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnNormalPlaneUseCalcCheck ), NULL, this );
	bounding_box_enable->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ObjectSettings::OnBoundingBoxCheck ), NULL, this );
	bounding_box_color->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( ObjectSettings::OnBoundingBoxColorChange ), NULL, this );
	bounding_box_mode->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ObjectSettings::OnBoundingBoxModeChange ), NULL, this );
	texture_select->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( ObjectSettings::OnTextureChange ), NULL, this );
	position_x->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnPositionChange ), NULL, this );
	position_y->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnPositionChange ), NULL, this );
	position_z->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnPositionChange ), NULL, this );
	rotation_x->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnRotationChange ), NULL, this );
	rotation_y->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnRotationChange ), NULL, this );
	rotation_z->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnRotationChange ), NULL, this );
	scale_x->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnScaleChange ), NULL, this );
	scale_y->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnScaleChange ), NULL, this );
	scale_z->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ObjectSettings::OnScaleChange ), NULL, this );
}



void ObjectSettings::SetupObject() {
	
	// set the object shader
	shader_flat->SetValue(object->GetShaderProgram() == FLAT_SHADER);
	shader_gouraud->SetValue(object->GetShaderProgram() == GOURAUD_SHADER);
	shader_phong->SetValue(object->GetShaderProgram() == PHONG_SHADER);
	
	// cull enabled
	polygon_front_cull->SetValue(object->GetFaceCullingMode() & FRONT);
	polygon_back_cull->SetValue(object->GetFaceCullingMode() & BACK);
	
	// mode
	polygon_front_mode->SetSelection(FILL - object->GetFrontPolygonMode());
	polygon_back_mode->SetSelection(FILL - object->GetBackPolygonMode());
	
	// TODO: color (need to add)
	vec3 front_color = object->GetFrontFaceColor();
	CGL::SetButtonBackground(polygon_front_color, front_color, std::string(polygon_front_color->GetLabel()));
	
	vec3 back_color = object->GetBackFaceColor();
	CGL::SetButtonBackground(polygon_back_color, back_color, std::string(polygon_back_color->GetLabel()));
	
	// object style
	object_silhouette_enable->SetValue(object->IsSilhouetteEnable() == true);
	CGL::SetButtonBackground(object_silhouette_color, object->GetSilhouetteColor(), std::string(object_silhouette_color->GetLabel()));
	
	// light
	object_diffuse_k->SetValue(std::to_string(object->GetDiffuseFactor()));
	object_specular_k->SetValue(std::to_string(object->GetSpecularFactor()));
	object_specular_n->SetValue(std::to_string(object->GetSpecularExponent()));
	
	
	//bounding box
	bounding_box_enable->SetValue(object->IsBoundingBoxEnabled());
	printf("Box Polygon: %d\n", object->GetBoundingBoxPolygonMode());
	bounding_box_mode->SetSelection(FILL - object->GetBoundingBoxPolygonMode());
	
	vec3 box_color = object->GetBoundingBoxColor() * 255.0f;
	bounding_box_color->SetColour(wxColor(box_color.x, box_color.y, box_color.z, 255.0f));
	
	// texture
	texture_select->Clear();
	texture_select->Append("None");
	for (const auto& [name, _] : CGL::textures) {
		texture_select->Append(name);
	}
	
	if (!object->GetTexture().empty())
		texture_select->SetStringSelection(object->GetTexture());
	else
		texture_select->SetSelection(0);
	
}

void ObjectSettings::OnFocus() {
	SetupObject();
}



void ObjectSettings::OnShadowProgramChange( wxCommandEvent& event ) {
	
	if (shader_flat->GetValue()) {
		object->SetShaderProgram(FLAT_SHADER);
	} else if (shader_gouraud->GetValue()) {
		object->SetShaderProgram(GOURAUD_SHADER);
	} else if (shader_phong->GetValue()) {
		object->SetShaderProgram(PHONG_SHADER);
	}
	
	CGL::app->Refresh();
};

void ObjectSettings::OnPolygonFrontCullChange( wxCommandEvent& event ) {
	
	u_int8_t cull_mode = object->GetFaceCullingMode();
	if (event.IsChecked()) {
		object->EnableFaceCulling();
		object->SetFaceCullingMode(cull_mode | FRONT);
	} else {
		object->SetFaceCullingMode(cull_mode & ~FRONT);
		if (cull_mode == FRONT) {
			object->DisableFaceCulling();
		}
	}
	
	CGL::app->Refresh();
	event.Skip();
	
}
void ObjectSettings::OnPolygonFrontModeChange( wxCommandEvent& event ) {
	
	object->SetFrontPolygonMode(FILL - event.GetSelection());
	CGL::app->Refresh();
	
	event.Skip();
	
}
void ObjectSettings::OnPolygonFrontColorChange( wxCommandEvent& event ) {
	vec3 curr_colour = object->GetFrontFaceColor() * 255;
	wxColourData colour_data;
	colour_data.SetColour(wxColour(curr_colour.x, curr_colour.y, curr_colour.z));
	wxColourDialog dialog(this, &colour_data);
	
	if (dialog.ShowModal() == wxID_OK) {
		
		wxColour color = dialog.GetColourData().GetColour();
		
		vec3 new_color;
		new_color.x = color.GetRed() / 255.0f;
		new_color.y = color.GetGreen() / 255.0f;
		new_color.z = color.GetBlue() / 255.0f;
		
		object->SetFrontFaceColor(new_color);
		CGL::SetButtonBackground(polygon_front_color, color, std::string(polygon_front_color->GetLabel()));
		
		CGL::app->Refresh();
	}
	event.Skip();
	
}
void ObjectSettings::OnPolygonBackCullChange( wxCommandEvent& event ) {
	u_int8_t cull_mode = object->GetFaceCullingMode();
	if (event.IsChecked()) {
		object->EnableFaceCulling();
		object->SetFaceCullingMode(cull_mode | BACK);
	} else {
		object->SetFaceCullingMode(cull_mode & ~BACK);
		if (cull_mode == BACK) {
			object->DisableFaceCulling();
		}
	}
	
	CGL::app->Refresh();
	event.Skip();
	
}
void ObjectSettings::OnPolygonBackModeChange( wxCommandEvent& event ) {
	object->SetBackPolygonMode(FILL - event.GetSelection());
	CGL::app->Refresh();
	event.Skip();
	
}
void ObjectSettings::OnPolygonBackColorChange( wxCommandEvent& event ) {
	
	vec3 curr_colour = object->GetBackFaceColor() * 255;
	wxColourData colour_data;
	colour_data.SetColour(wxColour(curr_colour.x, curr_colour.y, curr_colour.z));
	wxColourDialog dialog(this, &colour_data);
	
	if (dialog.ShowModal() == wxID_OK) {
		
		wxColour color = dialog.GetColourData().GetColour();
		
		vec3 new_color;
		new_color.x = color.GetRed() / 255.0f;
		new_color.y = color.GetGreen() / 255.0f;
		new_color.z = color.GetBlue() / 255.0f;
		
		object->SetBackFaceColor(new_color);
		CGL::SetButtonBackground(polygon_back_color, color, std::string(polygon_back_color->GetLabel()));
		
		CGL::app->Refresh();
	}
	
	event.Skip();
}

void ObjectSettings::OnObjectSilhouetteCheck( wxCommandEvent& event ) {
	if (event.IsChecked())
		object->EnableSilhouette();
	else
		object->DisableSilhouette();
	
	CGL::app->Refresh();
	event.Skip();
}
void ObjectSettings::OnObjectSilhouetteColorClick( wxCommandEvent& event ) {
	vec3 curr_colour = object->GetSilhouetteColor() * 255;
	wxColourData colour_data;
	colour_data.SetColour(wxColour(curr_colour.x, curr_colour.y, curr_colour.z));
	wxColourDialog dialog(this, &colour_data);
	
	if (dialog.ShowModal() == wxID_OK) {
		
		wxColour color = dialog.GetColourData().GetColour();
		
		vec3 new_color;
		new_color.x = color.GetRed() / 255.0f;
		new_color.y = color.GetGreen() / 255.0f;
		new_color.z = color.GetBlue() / 255.0f;
		
		object->SetSilhouetteColor(new_color);
		
		CGL::SetButtonBackground(object_silhouette_color, color, std::string(object_silhouette_color->GetLabel()));
		
		CGL::app->Refresh();
	}
	event.Skip();
	
}

void ObjectSettings::OnObjectTranspCheck( wxCommandEvent& event ) { event.Skip(); }
void ObjectSettings::OnObjectTranspNoneClick( wxCommandEvent& event ) { event.Skip(); }
void ObjectSettings::OnObjectTranspFullClick( wxCommandEvent& event ) { event.Skip(); }

void ObjectSettings::OnObjectKdChange( wxCommandEvent& event ) {
	
	try {
		float kd = std::stof(std::string(event.GetString()));
		object->SetDiffuseFactor(kd);
		CGL::app->Refresh();
	} catch(...) {
		object_diffuse_k->SetValue(std::to_string(object->GetDiffuseFactor()));
	}
	
	event.Skip();
}
void ObjectSettings::OnObjectShadowInteractCheck( wxCommandEvent& event ) { event.Skip(); }
void ObjectSettings::OnObjectKsChange( wxCommandEvent& event ) {
	try {
		float ks = std::stof(std::string(event.GetString()));
		object->SetSpecularFactor(ks);
		CGL::app->Refresh();
	} catch(...) {
		object_specular_k->SetValue(std::to_string(object->GetSpecularFactor()));
	}
	
	event.Skip();
	
}
void ObjectSettings::OnObjectNsChange( wxCommandEvent& event ) {
	try {
		float ns = std::stof(std::string(event.GetString()));
		object->SetSpecularExponent(ns);
		CGL::app->Refresh();
	} catch(...) {
		object_specular_n->SetValue(std::to_string(object->GetSpecularExponent()));
	}
	event.Skip();
}

void ObjectSettings::OnNormalVertexCheck( wxCommandEvent& event ) {
	
	if (event.IsChecked())
		object->EnableVertexNormals();
	else
		object->DisableVertexNormals();
	
	CGL::app->Refresh();
	
	event.Skip();
}
void ObjectSettings::OnNormalVertexColorClick( wxCommandEvent& event ) {
	vec3 curr_colour = object->GetVertexNormalsColor() * 255;
	wxColourData colour_data;
	colour_data.SetColour(wxColour(curr_colour.x, curr_colour.y, curr_colour.z));
	
	wxColourDialog dialog(this, &colour_data);
	
	if (dialog.ShowModal() == wxID_OK) {
		
		wxColour color = dialog.GetColourData().GetColour();
		
		vec3 new_color;
		new_color.x = color.GetRed() / 255.0f;
		new_color.y = color.GetGreen() / 255.0f;
		new_color.z = color.GetBlue() / 255.0f;
		
		object->SetVertexNormalsColor(new_color);
		
		CGL::SetButtonBackground(normal_vertex_color, color, std::string(normal_vertex_color->GetLabel()));
		
		CGL::app->Refresh();
	}
	event.Skip();
}
void ObjectSettings::OnNormalVertexUseCalcCheck( wxCommandEvent& event ) {
	if (event.IsChecked())
		object->EnableCalcVertexNormals();
	else
		object->EnableLoadVertexNormals();
	
	CGL::app->Refresh();
	event.Skip();
}
void ObjectSettings::OnNormalPlaneCheck( wxCommandEvent& event ) {
	if (event.IsChecked())
		object->EnablePlaneNormals();
	else
		object->DisablePlaneNormals();
	
	CGL::app->Refresh();
	event.Skip();
}
void ObjectSettings::OnNormalPlaneColorClick( wxCommandEvent& event ) {
	vec3 curr_colour = object->GetPlaneNormalsColor() * 255;
	wxColourData colour_data;
	colour_data.SetColour(wxColour(curr_colour.x, curr_colour.y, curr_colour.z));
	
	wxColourDialog dialog(this, &colour_data);
	
	if (dialog.ShowModal() == wxID_OK) {
		
		wxColour color = dialog.GetColourData().GetColour();
		
		vec3 new_color;
		new_color.x = color.GetRed() / 255.0f;
		new_color.y = color.GetGreen() / 255.0f;
		new_color.z = color.GetBlue() / 255.0f;
		
		object->SetPlaneNormalsColor(new_color);
		
		CGL::SetButtonBackground(normal_plane_color, color, std::string(normal_plane_color->GetLabel()));
		
		CGL::app->Refresh();
	}
	event.Skip();
}
void ObjectSettings::OnNormalPlaneUseCalcCheck( wxCommandEvent& event ) {
	if (event.IsChecked())
		object->EnableCalcPlaneNormals();
	else
		object->EnableLoadPlaneNormals();
	
	CGL::app->Refresh();
	event.Skip();
}

void ObjectSettings::OnNormalReverseCheck( wxCommandEvent& event ) {
	if (event.IsChecked())
		object->EnableReverseNormals();
	else
		object->DisableReverseNormals();
	
	CGL::app->Refresh();
	event.Skip();
}

void ObjectSettings::OnBoundingBoxCheck( wxCommandEvent& event ) {
	if (event.IsChecked())
		object->EnableBoundingBox();
	else
		object->DisableBoundingBox();
	
	CGL::app->Refresh();
	event.Skip();
}
void ObjectSettings::OnBoundingBoxColorChange( wxColourPickerEvent& event ) {
	
	wxColour color = event.GetColour();
	vec3 new_color;
	
	new_color.x = color.GetRed() / 255.0f;
	new_color.y = color.GetGreen() / 255.0f;
	new_color.z = color.GetBlue() / 255.0f;
	
	object->SetBoundingBoxColor(new_color);

	CGL::app->Refresh();
	event.Skip();
	
}
void ObjectSettings::OnBoundingBoxModeChange( wxCommandEvent& event ) {
	object->SetBoundingBoxPolygonMode(FILL - event.GetSelection());
	CGL::app->Refresh();
	event.Skip();
	
}

void ObjectSettings::OnTextureChange( wxCommandEvent& event ) {
	
	std::string texture = std::string(event.GetString());
	if (texture.compare("None") != 0)
		object->SetTexture(texture);
	else
		object->SetTexture("");
	
	CGL::app->Refresh();
	event.Skip();
	
}

void ObjectSettings::OnPositionChange( wxCommandEvent& event ) {
	
	try {
		float x = std::stof(std::string(position_x->GetValue()));
		object->position.x = x;
	} catch(...) {
		position_x->SetValue(std::to_string(object->position.x));
	}
	
	try {
		float y = std::stof(std::string(position_y->GetValue()));
		object->position.y = y;
	} catch(...) {
		position_y->SetValue(std::to_string(object->position.y));
	}
	
	try {
		float z = std::stof(std::string(position_z->GetValue()));
		object->position.z = z;
	} catch(...) {
		position_z->SetValue(std::to_string(object->position.z));
	}
	
	CGL::app->Refresh();
	
	event.Skip();
	
}
void ObjectSettings::OnRotationChange( wxCommandEvent& event ) {
	try {
		float x = std::stof(std::string(rotation_x->GetValue()));
		object->rotation.x = x;
	} catch(...) {
		rotation_x->SetValue(std::to_string(object->rotation.x));
	}
	
	try {
		float y = std::stof(std::string(rotation_y->GetValue()));
		object->rotation.y = y;
	} catch(...) {
		rotation_y->SetValue(std::to_string(object->rotation.y));
	}
	
	try {
		float z = std::stof(std::string(rotation_z->GetValue()));
		object->rotation.z = z;
	} catch(...) {
		rotation_z->SetValue(std::to_string(object->rotation.z));
	}
	
	CGL::app->Refresh();
	event.Skip();
	
}
void ObjectSettings::OnScaleChange( wxCommandEvent& event ) {
	try {
		float x = std::stof(std::string(scale_x->GetValue()));
		object->scale.x = x;
	} catch(...) {
		scale_x->SetValue(std::to_string(object->scale.x));
	}
	
	try {
		float y = std::stof(std::string(scale_y->GetValue()));
		object->scale.y = y;
	} catch(...) {
		scale_y->SetValue(std::to_string(object->scale.y));
	}
	
	try {
		float z = std::stof(std::string(scale_z->GetValue()));
		object->scale.z = z;
	} catch(...) {
		scale_z->SetValue(std::to_string(object->scale.z));
	}
	
	CGL::app->Refresh();
	event.Skip();
	
}

