///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/button.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statline.h>
#include <wx/radiobox.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
	private:

	protected:
		wxButton* load_image;
		wxButton* load_mask;
		wxButton* save_image;
		wxButton* color_options;
		wxStaticLine* m_staticline1;
		wxRadioBox* mask_options;
		wxStaticLine* m_staticline2;
		wxPanel* m_panel1;

		// Virtual event handlers, overide them in your derived class
		virtual void load_imageOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void load_maskOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void save_imageOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mask_optionsOnRadioBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void colorButtonOnButtonClick(wxCommandEvent& event) { event.Skip(); }


	public:

		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = "Projekt nr 16", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1000,500 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MyFrame1();

};