#ifndef __GUIMyFrame1__
#define __GUIMyFrame1__

/**
@file
Subclass of MyFrame1, which is generated by wxFormBuilder.
*/

#include "GUI.h"
#include <wx/filedlg.h>
//// end generated include

/** Implementing MyFrame1 */
class GUIMyFrame1 : public MyFrame1
{
protected:
	// Handlers for MyFrame1 events.
	void load_imageOnButtonClick(wxCommandEvent& event);
	void load_maskOnButtonClick(wxCommandEvent& event);
	void save_imageOnButtonClick(wxCommandEvent& event);
	void mask_optionsOnRadioBox(wxCommandEvent& event);
	void color_optionsOnRadioBox(wxCommandEvent& event);
	void Form_Resize(wxSizeEvent & e);
	void Repaint();
public:
	/** Constructor */
	GUIMyFrame1(wxWindow* parent);
	//// end generated class members

	wxBitmap image;	//zmienna przechowujaca obrazek tla
	wxBitmap mask_image; // zmienna przechowujaca obrazek maski
	wxMask* mask = nullptr; //zmienna przechowujaca maske 
	wxBitmap new_image; //zmienna w ktorej bedziemy przechowywac ta kombinacje obrazka i maski do zapisu
	int mask_choice; // pomocniczy int do wyboru sposobu kombinacji obrazka z maska
	wxColor base_color; // pomocnicza zmienna wybranego koloru w masce
};

#endif // __GUIMyFrame1__