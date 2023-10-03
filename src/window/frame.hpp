//
//  frame.hpp
//  CGApp
//
//  Created by Shahar Zafran on 01/01/2023.
//

#ifndef frame_hpp
#define frame_hpp

#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/treectrl.h>
#include <wx/clrpicker.h>
#include <wx/colordlg.h>
//#include <wx/frame.h>


#include <stdio.h>

#include "application.hpp"
#include "panel.hpp"

#include "projection.hpp"

#include "light_dialog.hpp"

class Frame : public wxFrame {
	
	
	LightDialog light_dialog;
	
	wxAuiManager manager;
	
	wxTreeCtrl *models_tree;
	wxAuiNotebook* ctrl;
	wxAuiNotebook* objects_settings;
	
	wxAuiToolBar* main_toolbar;
	
	wxMenuBar* menu_bar;
	wxMenu* m_menu1;
	wxMenu* m_menu3;
	wxMenu* m_menu2;
	wxMenu* m_menu21;

	void CreateMenu();
	void CreateMainToolBar();
	
	void CreateSettingsNodeBook();
	void CreateModelsTreePanel();
	void CreateObjectSettingsPanel();
	
	void UpdateModelsTree();
		
	
	//
	/* ====================================================================== */
	virtual void OnAddModel( wxCommandEvent& event );
	virtual void OnAddTexture( wxCommandEvent& event );
	virtual void OnReset( wxCommandEvent& event );
	virtual void OnClear( wxCommandEvent& event );
	virtual void OnExit( wxCommandEvent& event );
	virtual void OnSaveScene( wxCommandEvent& event );
	virtual void OnShowToolbar( wxCommandEvent& event );
	virtual void OnShowModelsTree( wxCommandEvent& event );
	virtual void OnImageBackground( wxCommandEvent& event );
	virtual void OnColorBackground( wxCommandEvent& event );
	/* ====================================================================== */
	
	
	
private:
	
	void OnViewPerspective(wxAuiToolBarEvent& event);
	void OnViewOrthographic(wxAuiToolBarEvent& event);
	void OnLightSettings(wxAuiToolBarEvent& event);
	
	
	void OnModelSelected(wxTreeEvent& event);
	void OnModelSelectedSettings(wxTreeEvent& event);
	void OnObjectSettingsChange(wxAuiNotebookEvent& event);
	
	
	void OnShowToolBar();
	void OnShowModelTreePanel();
	
	
public:
	Frame(const std::string& title, const wxSize& size, const wxPoint& pos);
	
	void OnClose(wxCloseEvent &event);
};


#endif /* frame_hpp */
