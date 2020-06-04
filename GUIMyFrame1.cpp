#include "GUIMyFrame1.h"
#include <wx/wx.h>

GUIMyFrame1::GUIMyFrame1(wxWindow* parent)
	:
	MyFrame1(parent)
{
	Bind(wxEVT_SIZE, &GUIMyFrame1::Form_Resize, this);
	color_choice = 'R';
	mask_choice = 0;
}

void GUIMyFrame1::load_imageOnButtonClick(wxCommandEvent& event)
//wczytuje do zmiennej "image" bitmape 
{
	wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Base image file (*.bmp)|*.bmp"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (WxOpenFileDialog.ShowModal() == wxID_OK)
	{
		if (!bitmap_image.LoadFile((const_cast<char*>((const char*)WxOpenFileDialog.GetPath().mb_str())), wxBITMAP_TYPE_ANY))
		{
			wxMessageBox(_("Nie uda\u0142o si\u0119 za³adowaæ obrazka"));
		}
	}
	img_org = bitmap_image.ConvertToImage();
	img_cpy = img_org.Copy();
	Repaint();
}

void GUIMyFrame1::load_maskOnButtonClick(wxCommandEvent& event)
//wczytuje do zmiennej "mask" bitmape i odpowiedni kolor
{
	wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Mask file (*.bmp)|*.bmp"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (WxOpenFileDialog.ShowModal() == wxID_OK)
	{
		if (!bitmap_mask.LoadFile((const_cast<char*>((const char*)WxOpenFileDialog.GetPath().mb_str())), wxBITMAP_TYPE_ANY))
		{
			wxMessageBox(_("Nie uda\u0142o si\u0119 za³adowaæ maski"));
		}
		else
		{
			//jak ustawi sie ta maske to w sumie wizualnie nic nie daje wiec nie wiem xd
			mask = bitmap_mask.GetMask();
		}
	}
	img_mask = bitmap_mask.ConvertToImage();
	set_mask();
}

void GUIMyFrame1::save_imageOnButtonClick(wxCommandEvent& event)
//zapisuje do pliku to co jest w new_image ( na razie nic )
{
	wxBitmap save(img_cpy);
	wxFileDialog WxSaveFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("config files (*.bmp)|*.bmp"), wxFD_SAVE);
	if (WxSaveFileDialog.ShowModal() == wxID_OK) 
	{
		if (!save.SaveFile((const_cast<char*>((const char*)WxSaveFileDialog.GetPath().mb_str())), wxBITMAP_TYPE_BMP))
		{
			wxLogError(_("Nie uda\u0142o si\u0119 zapisaæ obrazka"));
		}
	}
}

void GUIMyFrame1::mask_optionsOnRadioBox(wxCommandEvent& event)
//ustala zmienna pomocnicza mask_choice na odpowiedni int
{
	mask_choice = mask_options->GetSelection();
	set_mask();
}

void GUIMyFrame1::color_optionsOnRadioBox(wxCommandEvent& event)
//ustala zmienna pomocnicza "base_color" na odpowiedni kolorek
{
	if (color_options->GetSelection() == 0)
		color_choice = 'R';
	else if (color_options->GetSelection() == 1)
		color_choice = 'G';
	else
		color_choice = 'B';
	set_mask();
	//trzeba zrobiæ ¿eby aktualizowalo kolor w masce po zmianie
}

void GUIMyFrame1::set_mask() 
//glowna funkcja to 
{
	img_cpy = img_org.Copy();
	int w = img_mask.GetWidth();
	int h = img_mask.GetHeight();
	int size = w * h * 3;
	unsigned char *data = img_cpy.GetData();
	unsigned char *mask_data = img_mask.GetData();
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (color_choice == 'R') {
				data[3 * w * i + 3 * j + 1] = mask_data[3 * w * i + 3 * j + 1];
				data[3 * w * i + 3 * j + 2] = mask_data[3 * w * i + 3 * j + 2];
			}
			else if (color_choice == 'G') {
				data[3 * w * i + 3 * j] = mask_data[3 * w * i + 3 * j];
				data[3 * w * i + 3 * j + 2] = mask_data[3 * w * i + 3 * j + 2];
			}
			else {
				data[3 * w * i + 3 * j] = mask_data[3 * w * i + 3 * j];
				data[3 * w * i + 3 * j + 1] = mask_data[3 * w * i + 3 * j + 1];
			}
		}
	}

	Repaint();
}

void GUIMyFrame1::Repaint()
//rysuje bitmape obrazka i na razie nie robi nic z maska
{	
	wxBitmap bitmap(img_cpy);
	wxClientDC dc(m_panel1);
	m_panel1->SetSize(img_cpy.GetSize());
	dc.DrawBitmap(bitmap, 0, 0, true); 
}

void GUIMyFrame1::Form_Resize(wxSizeEvent & e)
//jesli obrazek jest wczytany i zmieniamy rozmiar okna to robi repaint
{
	if(img_cpy.IsOk())
		Repaint();
}