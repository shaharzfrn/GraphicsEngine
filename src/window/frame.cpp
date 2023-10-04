//
//  frame.cpp
//  CGApp
//
//  Created by Shahar Zafran on 01/01/2023.
//



#include "frame.hpp"
#include "projection.hpp"
#include "loader.hpp"
#include "object_settings.hpp"

#include "wx/rawbmp.h"
#include <iterator>

#include "cgl_environment.h"

enum {
	CGL_VIEW_PRESPECTIVE_ID = wxID_HIGHEST + 1,
	CGL_VIEW_OTHOGRAPHIC_ID,
};


Frame::Frame(const std::string& title, const wxSize& size, const wxPoint& pos): wxFrame(nullptr, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE) {
	
	wxInitAllImageHandlers();
	
	Bind(wxEVT_CLOSE_WINDOW, &Frame::OnClose, this);
	
	manager.SetManagedWindow(this);
	
	CreateMenu();
	CreateMainToolBar();
	CreateSettingsNodeBook();
	
	manager.AddPane(new Panel(this), wxAuiPaneInfo().Name("cgl_panel").Caption("CGL").CenterPane().PaneBorder(false));
	
	manager.GetPane("tb1").Show(true);
	manager.GetPane("models").Show(true);
	manager.Update();
	
	UpdateModelsTree();
}


void Frame::CreateMenu() {
	
	menu_bar = new wxMenuBar(0);
	
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Add Model") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem1 );

	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Add Texture") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem2 );

	m_menu1->AppendSeparator();

	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Reset Scene") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem3 );

	wxMenuItem* m_menuItem4;
	m_menuItem4 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Clear Scene") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem4 );

	m_menu1->AppendSeparator();

	wxMenuItem* m_menuItem8;
	m_menuItem8 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem8 );

	menu_bar->Append( m_menu1, wxT("File") );

	m_menu3 = new wxMenu();
	wxMenuItem* m_menuItem12;
	m_menuItem12 = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Save Scene") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuItem12 );

	menu_bar->Append( m_menu3, wxT("Save") );

	m_menu2 = new wxMenu();
	wxMenuItem* m_menuItem6;
	m_menuItem6 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("Show Toolbar") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( m_menuItem6 );

	wxMenuItem* m_menuItem7;
	m_menuItem7 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("Show Models Tree") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( m_menuItem7 );

	m_menu2->AppendSeparator();

	m_menu21 = new wxMenu();
	wxMenuItem* m_menu21Item = new wxMenuItem( m_menu2, wxID_ANY, wxT("Background"), wxEmptyString, wxITEM_NORMAL, m_menu21 );
	wxMenuItem* m_menuItem10;
	m_menuItem10 = new wxMenuItem( m_menu21, wxID_ANY, wxString( wxT("Image") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu21->Append( m_menuItem10 );

	wxMenuItem* m_menuItem11;
	m_menuItem11 = new wxMenuItem( m_menu21, wxID_ANY, wxString( wxT("Color") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu21->Append( m_menuItem11 );

	m_menu2->Append( m_menu21Item );

	menu_bar->Append( m_menu2, wxT("View") );


		// Connect Events
		m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::OnAddModel ), this, m_menuItem1->GetId());
		m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::OnAddTexture ), this, m_menuItem2->GetId());
		m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::OnReset ), this, m_menuItem3->GetId());
		m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::OnClear ), this, m_menuItem4->GetId());
		m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::OnExit ), this, m_menuItem8->GetId());
		m_menu3->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::OnSaveScene ), this, m_menuItem12->GetId());
		m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::OnShowToolbar ), this, m_menuItem6->GetId());
		m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::OnShowModelsTree ), this, m_menuItem7->GetId());
		m_menu21->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::OnImageBackground ), this, m_menuItem10->GetId());
		m_menu21->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::OnColorBackground ), this, m_menuItem11->GetId());
	
	this->SetMenuBar(menu_bar);
}
//
/* ====================================================================== */
void Frame::OnAddModel( wxCommandEvent& event ) {
	wxFileDialog load_file(nullptr, "Load IRIT Model File", "", "", "*.itd", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (load_file.ShowModal() == wxID_OK) {
		std::string path = std::string(load_file.GetPath());
		CGL::LoadModel(path);
		UpdateModelsTree();
		CGL::app->Refresh();
	}
	
	event.Skip();
}
void Frame::OnAddTexture( wxCommandEvent& event ) {
	wxFileDialog load_file(nullptr, "Load Texture File", "", "", "*.png", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (load_file.ShowModal() == wxID_OK) {
		std::string path = std::string(load_file.GetPath());
		CGL::LoadTexture(path);
		
		wxWindow* curr_page = objects_settings->GetCurrentPage();
		if (curr_page)
			((ObjectSettings*)curr_page)->OnFocus();
	}
	event.Skip();
}
void Frame::OnReset( wxCommandEvent& event ) {
	event.Skip();
}
void Frame::OnClear( wxCommandEvent& event ) {
	
	CGL::objects.clear();
	CGL::textures.clear();
	
	UpdateModelsTree();
	objects_settings->DeleteAllPages();
	
	CGL::selected_object = nullptr;
	CGL::is_object_selected = false;
	
	event.Skip();
}
void Frame::OnExit( wxCommandEvent& event ) {
	this->Close();
	event.Skip();
}
void Frame::OnSaveScene( wxCommandEvent& event ) {
	// TODO: Dialog for size
	event.Skip();
}
void Frame::OnShowToolbar( wxCommandEvent& event ) {
	manager.GetPane("tb1").Show(true);
	manager.Update();
	event.Skip();
}
void Frame::OnShowModelsTree( wxCommandEvent& event ) {
	manager.GetPane("models").Show(true);
	manager.Update();
	event.Skip();
}
void Frame::OnImageBackground( wxCommandEvent& event ) {
	// add image
	// TODO: change to dialog with reapit & scale
	wxFileDialog load_file(nullptr, "Load Background File", "", "", "*.png", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (load_file.ShowModal() == wxID_OK) {
		std::string path = std::string(load_file.GetPath());
		if (CGL::background_image != nullptr) delete CGL::background_image;
		CGL::background_image = new wxBitmap(path, wxBITMAP_TYPE_PNG);
	}
	CGL::app->Refresh();
	event.Skip();
}
void Frame::OnColorBackground( wxCommandEvent& event ) {
	vec4 curr_colour = CGL::background_color;
	wxColourData colour_data;
	colour_data.SetColour(wxColour(curr_colour.x, curr_colour.y, curr_colour.z, curr_colour.w));
	wxColourDialog dialog(this, &colour_data);
	
	if (dialog.ShowModal() == wxID_OK) {
		
		wxColour color = dialog.GetColourData().GetColour();
		
		vec4 new_color;
		new_color.x = color.GetRed() / 255.0f;
		new_color.y = color.GetGreen() / 255.0f;
		new_color.z = color.GetBlue() / 255.0f;
		new_color.w = color.GetAlpha() / 255.0f;
		
		CGL::background_color = new_color;
		CGL::app->Refresh();
	}
	
	event.Skip();
}
/* ====================================================================== */









void Frame::CreateMainToolBar() {
	wxAuiToolBar* tb1 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
											 wxAUI_TB_PLAIN_BACKGROUND | wxAUI_TB_GRIPPER);
	
	
	tb1->AddTool(CGL_VIEW_PRESPECTIVE_ID, "Perspective", wxBitmap("./res/view_persp.xpm", wxBITMAP_TYPE_XPM));
	
	tb1->AddTool(CGL_VIEW_OTHOGRAPHIC_ID, "Orthographic", wxBitmap("./res/view_ortho.xpm", wxBITMAP_TYPE_XPM));
	
	tb1->AddTool(CGL_VIEW_OTHOGRAPHIC_ID+1, "Orthographic", wxBitmap("./res/light.png", wxBITMAP_TYPE_PNG));
	tb1->AddTool(CGL_VIEW_OTHOGRAPHIC_ID+5, "Orthographic", wxBitmap("./res/shadow.png", wxBITMAP_TYPE_PNG));
	
	tb1->Realize();
	
	tb1->Connect(CGL_VIEW_PRESPECTIVE_ID, wxEVT_COMMAND_AUITOOLBAR_TOOL_DROPDOWN, wxAuiToolBarEventHandler(Frame::OnViewPerspective), NULL, this);
	tb1->Connect(CGL_VIEW_OTHOGRAPHIC_ID, wxEVT_COMMAND_AUITOOLBAR_TOOL_DROPDOWN, wxAuiToolBarEventHandler(Frame::OnViewOrthographic), NULL, this);
	
	tb1->Connect(CGL_VIEW_OTHOGRAPHIC_ID+1, wxEVT_COMMAND_AUITOOLBAR_TOOL_DROPDOWN, wxAuiToolBarEventHandler(Frame::OnLightSettings), NULL, this);
	
	
	light_dialog.Show(false);
	manager.AddPane(tb1, wxAuiPaneInfo().Name("tb1").Caption("Toolbar").ToolbarPane().Top());
}

void Frame::CreateSettingsNodeBook() {
	models_tree = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_HIDE_ROOT | wxTR_LINES_AT_ROOT | wxTR_SINGLE | wxTR_HAS_BUTTONS);
	models_tree->Connect(wxEVT_TREE_SEL_CHANGED, wxTreeEventHandler( Frame::OnModelSelected ), NULL, this);
	models_tree->Connect(wxEVT_TREE_ITEM_ACTIVATED, wxTreeEventHandler( Frame::OnModelSelectedSettings ), NULL, this);
	manager.AddPane(models_tree, wxAuiPaneInfo().Name("models").Right().Layer(1).Position(1).BestSize(125, 10));
	
	objects_settings = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);
	objects_settings->Connect(wxEVT_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( Frame::OnObjectSettingsChange ), NULL, this);
	
	manager.AddPane(objects_settings, wxAuiPaneInfo().Name("object_settings").Right().Layer(1).Position(2).MinSize(125, -1).Hide());
}
void Frame::CreateObjectSettingsPanel() {
	
}

void Frame::CreateModelsTreePanel() {
	
	models_tree = new wxTreeCtrl( ctrl, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_HIDE_ROOT | wxTR_LINES_AT_ROOT | wxTR_SINGLE | wxTR_HAS_BUTTONS);
	models_tree->Connect(wxEVT_TREE_SEL_CHANGED, wxTreeEventHandler( Frame::OnModelSelected ), NULL, this);
	models_tree->Connect(wxEVT_TREE_ITEM_ACTIVATED, wxTreeEventHandler( Frame::OnModelSelectedSettings ), NULL, this);
	
	ctrl->AddPage(models_tree, "Models");
}

void Frame::UpdateModelsTree() {
	
	models_tree->DeleteAllItems();

	wxTreeItemId root = models_tree->AddRoot("root");
	for (const auto& [object_name, object] : CGL::objects) {
		wxTreeItemId model_item = models_tree->AppendItem(root, object_name);
		
		for (const auto& sub_object_name : object.GetObjects()) {
			models_tree->AppendItem(model_item, sub_object_name);
		}
		models_tree->Expand(model_item);
	};
}

void Frame::OnClose(wxCloseEvent &event) {
	CGL::app->OnClose();
	Destroy();
}


void Frame::OnViewPerspective(wxAuiToolBarEvent& event) {
	CGL::projection_type = CGL::PRESPECTIVE_PROJECTION;
	CGL::app->Refresh();
	event.Skip();
}

void Frame::OnViewOrthographic(wxAuiToolBarEvent& event) {
	CGL::projection_type = CGL::OTHOGRAPHIC_PROJECTION;
	CGL::app->Refresh();
	event.Skip();
}

void Frame::OnLightSettings(wxAuiToolBarEvent& event) {
	
	light_dialog.Update();
	light_dialog.Show(true);
	
}


void Frame::OnModelSelected(wxTreeEvent& event) {
	
	wxTreeItemId item = event.GetItem();
	wxTreeItemId parent_item = models_tree->GetItemParent(item);
	
	std::string item_text = std::string(models_tree->GetItemText(item));
	std::string parent_item_text = std::string(models_tree->GetItemText(parent_item));
	
	if (CGL::selected_object != nullptr)
		CGL::selected_object->Diselect();
	
	if (parent_item == models_tree->GetRootItem()) {
		CGL::selected_object = &(CGL::objects[item_text]);
	} else {
		CGL::selected_object = &(CGL::objects[parent_item_text].objects[item_text]);
	}
	
	CGL::selected_object->Select();
	CGL::is_object_selected = true;
	
	CGL::app->Refresh();
}

void Frame::OnModelSelectedSettings(wxTreeEvent& event) {
	
	OnModelSelected(event);
	objects_settings->AddPage(new ObjectSettings(objects_settings, CGL::selected_object) , models_tree->GetItemText(event.GetItem()));
	manager.GetPane("object_settings").Show(true);
	manager.Update();
}

void Frame::OnObjectSettingsChange(wxAuiNotebookEvent& event) {
	((ObjectSettings*)objects_settings->GetPage(event.GetSelection()))->OnFocus();
}
