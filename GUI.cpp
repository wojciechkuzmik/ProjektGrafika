///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	load_image = new wxButton(this, wxID_ANY, wxT("Wczytaj obraz"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(load_image, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	load_mask = new wxButton(this, wxID_ANY, wxT("Wczytaj mask\u0119"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(load_mask, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	save_image = new wxButton(this, wxID_ANY, wxT("Zapisz"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(save_image, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticline1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer2->Add(m_staticline1, 0, wxEXPAND | wxALL, 5);

	wxString mask_optionsChoices[] = { wxT("Zamiana kolor\u00F3w"), wxT("Sumowanie kolor\u00F3w"), wxT("Mno\u017Cenie kolor\u00F3w") };
	int mask_optionsNChoices = sizeof(mask_optionsChoices) / sizeof(wxString);
	mask_options = new wxRadioBox(this, wxID_ANY, wxT("Opcje nak\u0142adania"), wxDefaultPosition, wxDefaultSize, mask_optionsNChoices, mask_optionsChoices, 1, wxRA_SPECIFY_COLS);
	mask_options->SetSelection(0);
	bSizer2->Add(mask_options, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticline2 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer2->Add(m_staticline2, 0, wxEXPAND | wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	wxString color_optionsChoices[] = { wxT("Czerwony"), wxT("Zielony"), wxT("Niebieski"), wxT("Wszystkie"), wxT("Inny") };
	int color_optionsNChoices = sizeof(color_optionsChoices) / sizeof(wxString);
	color_options = new wxRadioBox(this, wxID_ANY, wxT("Kolor przezroczysyty"), wxDefaultPosition, wxDefaultSize, color_optionsNChoices, color_optionsChoices, 1, wxRA_SPECIFY_COLS);
	color_options->SetSelection(0);
	bSizer2->Add(color_options, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);
	
	
	color_button = new wxButton(this, wxID_ANY, wxT("Wybierz kolor"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(color_button, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);


	bSizer1->Add(bSizer2, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxVERTICAL);

	m_panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	bSizer3->Add(m_panel1, 1, wxEXPAND | wxALL, 5);


	bSizer1->Add(bSizer3, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	load_image->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::load_imageOnButtonClick), NULL, this);
	load_mask->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::load_maskOnButtonClick), NULL, this);
	save_image->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::save_imageOnButtonClick), NULL, this);
	mask_options->Connect(wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(MyFrame1::mask_optionsOnRadioBox), NULL, this);
	color_options->Connect(wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(MyFrame1::color_optionsOnRadioBox), NULL, this);
	color_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::colorButtonOnButtonClick), NULL, this);

}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	load_image->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::load_imageOnButtonClick), NULL, this);
	load_mask->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::load_maskOnButtonClick), NULL, this);
	save_image->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::save_imageOnButtonClick), NULL, this);
	mask_options->Disconnect(wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(MyFrame1::mask_optionsOnRadioBox), NULL, this);
	color_options->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::colorButtonOnButtonClick), NULL, this);
	color_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::colorButtonOnButtonClick), NULL, this);
}