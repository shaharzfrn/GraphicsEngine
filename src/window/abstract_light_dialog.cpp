
#include "abstract_light_dialog.hpp"

AbstractLightDialog::AbstractLightDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, "Light Settings", pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

		wxBoxSizer* bSizer5;
		bSizer5 = new wxBoxSizer( wxVERTICAL );

		wxStaticBoxSizer* sbSizer14;
		sbSizer14 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Ambiant Light") ), wxHORIZONTAL );

		ambiant_light_color = new wxColourPickerCtrl( sbSizer14->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
		sbSizer14->Add( ambiant_light_color, 0, wxALL, 5 );

		ambiant_light_s = new wxTextCtrl( sbSizer14->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
		sbSizer14->Add( ambiant_light_s, 1, wxALL, 5 );


		bSizer5->Add( sbSizer14, 1, wxEXPAND, 5 );

		wxStaticBoxSizer* sbSizer15;
		sbSizer15 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Light") ), wxVERTICAL );

		wxGridBagSizer* gbSizer13;
		gbSizer13 = new wxGridBagSizer( 0, 0 );
		gbSizer13->SetFlexibleDirection( wxBOTH );
		gbSizer13->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

		wxString m_choice10Choices[] = { wxT("Light 1"), wxT("Light 2"), wxT("Light 3"), wxT("Light 4"), wxT("Light 5"), wxT("Light 6"), wxT("Light 7"), wxT("Light 1"), wxT("Light 1"), wxEmptyString };
		int m_choice10NChoices = sizeof( m_choice10Choices ) / sizeof( wxString );
		m_choice10 = new wxChoice( sbSizer15->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice10NChoices, m_choice10Choices, 0 );
		m_choice10->SetSelection( 0 );
		gbSizer13->Add( m_choice10, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );

		enable_light = new wxCheckBox( sbSizer15->GetStaticBox(), wxID_ANY, wxT("Enable"), wxDefaultPosition, wxDefaultSize, 0 );
		gbSizer13->Add( enable_light, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

		wxString m_choice11Choices[] = { wxT("Direction"), wxT("Point"), wxT("Spot") };
		int m_choice11NChoices = sizeof( m_choice11Choices ) / sizeof( wxString );
		m_choice11 = new wxChoice( sbSizer15->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice11NChoices, m_choice11Choices, 0 );
		m_choice11->SetSelection( 0 );
		gbSizer13->Add( m_choice11, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALL, 5 );


		sbSizer15->Add( gbSizer13, 0, wxEXPAND, 5 );

		wxGridBagSizer* gbSizer15;
		gbSizer15 = new wxGridBagSizer( 0, 0 );
		gbSizer15->SetFlexibleDirection( wxBOTH );
		gbSizer15->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

		m_staticText15 = new wxStaticText( sbSizer15->GetStaticBox(), wxID_ANY, wxT("Direction"), wxDefaultPosition, wxDefaultSize, 0 );
		m_staticText15->Wrap( -1 );
		gbSizer15->Add( m_staticText15, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

			direction_x = new wxTextCtrl( sbSizer15->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
		gbSizer15->Add( 	direction_x, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );

			direction_y = new wxTextCtrl( sbSizer15->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
		gbSizer15->Add( 	direction_y, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALL, 5 );

			direction_z = new wxTextCtrl( sbSizer15->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
		gbSizer15->Add( 	direction_z, wxGBPosition( 1, 3 ), wxGBSpan( 1, 1 ), wxALL, 5 );

		m_staticText16 = new wxStaticText( sbSizer15->GetStaticBox(), wxID_ANY, wxT("Position"), wxDefaultPosition, wxDefaultSize, 0 );
		m_staticText16->Wrap( -1 );
		gbSizer15->Add( m_staticText16, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

		position_x = new wxTextCtrl( sbSizer15->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_PROCESS_ENTER );
		gbSizer15->Add( position_x, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

		position_y = new wxTextCtrl( sbSizer15->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
		gbSizer15->Add( position_y, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALL, 5 );

		position_z = new wxTextCtrl( sbSizer15->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
		gbSizer15->Add( position_z, wxGBPosition( 0, 3 ), wxGBSpan( 1, 1 ), wxALL, 5 );

		light_color = new wxColourPickerCtrl( sbSizer15->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
		gbSizer15->Add( light_color, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
		cutoff_angle = new wxTextCtrl( sbSizer15->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
		gbSizer15->Add( cutoff_angle, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );

		wxStaticBoxSizer* sbSizer16;
		sbSizer16 = new wxStaticBoxSizer( new wxStaticBox( sbSizer15->GetStaticBox(), wxID_ANY, wxT("Shadow") ), wxHORIZONTAL );

		wxGridBagSizer* gbSizer17;
		gbSizer17 = new wxGridBagSizer( 0, 0 );
		gbSizer17->SetFlexibleDirection( wxBOTH );
		gbSizer17->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

		shadow_map = new wxRadioButton( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Map"), wxDefaultPosition, wxDefaultSize, 0 );
		gbSizer17->Add( shadow_map, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );

		shadow_volume = new wxRadioButton( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Volume"), wxDefaultPosition, wxDefaultSize, 0 );
		gbSizer17->Add( shadow_volume, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );

		m_staticText20 = new wxStaticText( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Width"), wxDefaultPosition, wxDefaultSize, 0 );
		m_staticText20->Wrap( -1 );
		gbSizer17->Add( m_staticText20, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );

		shadow_width = new wxTextCtrl( sbSizer16->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
		gbSizer17->Add( shadow_width, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

		m_staticText21 = new wxStaticText( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Height"), wxDefaultPosition, wxDefaultSize, 0 );
		m_staticText21->Wrap( -1 );
		gbSizer17->Add( m_staticText21, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );

		shadow_height = new wxTextCtrl( sbSizer16->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
		gbSizer17->Add( shadow_height, wxGBPosition( 1, 3 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

		m_staticText22 = new wxStaticText( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Near"), wxDefaultPosition, wxDefaultSize, 0 );
		m_staticText22->Wrap( -1 );
		gbSizer17->Add( m_staticText22, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_RIGHT, 5 );

		shadow_near = new wxTextCtrl( sbSizer16->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
		gbSizer17->Add( shadow_near, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );

		m_staticText24 = new wxStaticText( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Far"), wxDefaultPosition, wxDefaultSize, 0 );
		m_staticText24->Wrap( -1 );
		gbSizer17->Add( m_staticText24, wxGBPosition( 2, 2 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );

		shadow_far = new wxTextCtrl( sbSizer16->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), wxTE_PROCESS_ENTER );
		gbSizer17->Add( shadow_far, wxGBPosition( 2, 3 ), wxGBSpan( 1, 1 ), wxALL, 5 );


		sbSizer16->Add( gbSizer17, 1, wxEXPAND, 5 );


		gbSizer15->Add( sbSizer16, wxGBPosition( 3, 0 ), wxGBSpan( 1, 4 ), wxEXPAND, 5 );


		sbSizer15->Add( gbSizer15, 1, wxEXPAND, 5 );


		bSizer5->Add( sbSizer15, 0, wxEXPAND, 5 );


		this->SetSizer( bSizer5 );
		this->Layout();
		bSizer5->Fit( this );

		this->Centre( wxBOTH );

		// Connect Events
		ambiant_light_color->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( AbstractLightDialog::OnAmbiantLightChange ), NULL, this );
		ambiant_light_s->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnAmbiantLightSChange ), NULL, this );
		m_choice10->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( AbstractLightDialog::OnLightSelect ), NULL, this );
		enable_light->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AbstractLightDialog::OnLightChecke ), NULL, this );
		m_choice11->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( AbstractLightDialog::OnLightTypeChange ), NULL, this );
			direction_x->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnLightDirectionChange ), NULL, this );
			direction_y->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnLightDirectionChange ), NULL, this );
			direction_z->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnLightDirectionChange ), NULL, this );
		position_x->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnLightPositionChange ), NULL, this );
		position_y->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnLightPositionChange ), NULL, this );
		position_z->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnLightPositionChange ), NULL, this );
		cutoff_angle->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnLightCutoffChange ), NULL, this );
		light_color->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( AbstractLightDialog::OnLightColoeChange ), NULL, this );
		shadow_map->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AbstractLightDialog::OnShadowTypeChange ), NULL, this );
		shadow_volume->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AbstractLightDialog::OnShadowTypeChange ), NULL, this );
		shadow_width->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnShadowViewChange ), NULL, this );
		shadow_height->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnShadowViewChange ), NULL, this );
		shadow_near->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnShadowViewChange ), NULL, this );
		shadow_far->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnShadowViewChange ), NULL, this );
}

AbstractLightDialog::~AbstractLightDialog()
{
	// Disconnect Events
	ambiant_light_color->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( AbstractLightDialog::OnAmbiantLightChange ), NULL, this );
		ambiant_light_s->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnAmbiantLightSChange ), NULL, this );
		m_choice10->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( AbstractLightDialog::OnLightSelect ), NULL, this );
		enable_light->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AbstractLightDialog::OnLightChecke ), NULL, this );
		m_choice11->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( AbstractLightDialog::OnLightTypeChange ), NULL, this );
			direction_x->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnLightPositionChange ), NULL, this );
			direction_y->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnLightPositionChange ), NULL, this );
			direction_z->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnLightPositionChange ), NULL, this );
		position_x->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnLightDirectionChange ), NULL, this );
		position_y->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnLightDirectionChange ), NULL, this );
		position_z->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnLightDirectionChange ), NULL, this );
		shadow_map->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AbstractLightDialog::OnShadowTypeChange ), NULL, this );
		shadow_volume->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AbstractLightDialog::OnShadowTypeChange ), NULL, this );
		shadow_width->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnShadowViewChange ), NULL, this );
		shadow_height->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnShadowViewChange ), NULL, this );
		shadow_near->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnShadowViewChange ), NULL, this );
		shadow_far->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AbstractLightDialog::OnShadowViewChange ), NULL, this );
}
