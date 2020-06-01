#include "GUIMyFrame1.h"
#include <wx/wx.h>

GUIMyFrame1::GUIMyFrame1(wxWindow* parent)
	:
	MyFrame1(parent)
{
	Bind(wxEVT_SIZE, &GUIMyFrame1::Form_Resize, this);
}

void GUIMyFrame1::load_imageOnButtonClick(wxCommandEvent& event)
//wczytuje do zmiennej "image" bitmape 
{
	wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Base image file (*.bmp)|*.bmp"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (WxOpenFileDialog.ShowModal() == wxID_OK)
	{
		if (!image.LoadFile((const_cast<char*>((const char*)WxOpenFileDialog.GetPath().mb_str())), wxBITMAP_TYPE_ANY))
		{
			wxMessageBox(_("Nie uda\u0142o si\u0119 za³adowaæ obrazka"));
		}
	}
	if(image.IsOk())
		Repaint();
}

void GUIMyFrame1::load_maskOnButtonClick(wxCommandEvent& event)
//wczytuje do zmiennej "mask" bitmape i odpowiedni kolor
{
	wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Mask file (*.bmp)|*.bmp"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (WxOpenFileDialog.ShowModal() == wxID_OK)
	{
		if (!mask_image.LoadFile((const_cast<char*>((const char*)WxOpenFileDialog.GetPath().mb_str())), wxBITMAP_TYPE_ANY))
		{
			wxMessageBox(_("Nie uda\u0142o si\u0119 za³adowaæ maski"));
		}
		else
		{
			//jak ustawi sie ta maske to w sumie wizualnie nic nie daje wiec nie wiem xd
			mask =new wxMask(mask_image, base_color);
		}
	}
	if (image.IsOk())
	{
		image.SetMask(mask);
		Repaint();
	}
}

void GUIMyFrame1::save_imageOnButtonClick(wxCommandEvent& event)
//zapisuje do pliku to co jest w new_image ( na razie nic )
{
	wxFileDialog WxSaveFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("config files (*.bmp)|*.bmp"), wxFD_SAVE);
	if (WxSaveFileDialog.ShowModal() == wxID_OK && new_image.IsOk()) 
	{
		if (!new_image.SaveFile((const_cast<char*>((const char*)WxSaveFileDialog.GetPath().mb_str())), wxBITMAP_TYPE_BMP))
		{
			wxLogError(_("Nie uda\u0142o si\u0119 zapisaæ obrazka"));
		}
	}
}

void GUIMyFrame1::mask_optionsOnRadioBox(wxCommandEvent& event)
//ustala zmienna pomocnicza mask_choice na odpowiedni int
{
	mask_choice = mask_options->GetSelection();
	
	if (image.IsOk())
		Repaint();
}

void GUIMyFrame1::color_optionsOnRadioBox(wxCommandEvent& event)
//ustala zmienna pomocnicza "base_color" na odpowiedni kolorek
{
	if (color_options->GetSelection() == 0)
		base_color = wxColor(255, 0, 0);
	else if (color_options->GetSelection() == 1)
		base_color = wxColor(0, 255, 0);
	else
		base_color = wxColor(0, 0, 255); 

	//trzeba zrobiæ ¿eby aktualizowalo kolor w masce po zmianie
}

void GUIMyFrame1::Repaint()
//rysuje bitmape obrazka i na razie nie robi nic z maska
{
	wxClientDC dc(m_panel1);
	int	height = image.GetHeight();
	int	width = image.GetWidth();
	m_panel1->SetSize(image.GetSize());
	dc.DrawBitmap(image, 0, 0, true); 

}

void GUIMyFrame1::Form_Resize(wxSizeEvent & e)
//jesli obrazek jest wczytany i zmieniamy rozmiar okna to robi repaint
{
	if (image.IsOk())
		Repaint();
}