#include "GUIMyFrame1.h"
#include <wx/colordlg.h>
#include <wx/wx.h>

GUIMyFrame1::GUIMyFrame1(wxWindow* parent)
	:
	MyFrame1(parent)
{
	Bind(wxEVT_SIZE, &GUIMyFrame1::Form_Resize, this);
	color_choice = wxColour(255, 0, 0);
	all_colors = false;
	mask_choice = 0;
	color_button->Enable(false);
}

void GUIMyFrame1::load_imageOnButtonClick(wxCommandEvent& event)
//wczytuje do zmiennej "bitmap_image" bitmape i zmienia ja na typ wxImage - zmienna img_org, tworzy kopię w img_cpy
{
	wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Base image file (*.bmp)|*.bmp"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (WxOpenFileDialog.ShowModal() == wxID_OK)
	{
		if (!bitmap_image.LoadFile((const_cast<char*>((const char*)WxOpenFileDialog.GetPath().mb_str())), wxBITMAP_TYPE_ANY))
		{
			wxMessageBox(_("Nie uda\u0142o si\u0119 za\u0142adować obrazka"));
		}
	}
	if (bitmap_image.IsOk()) {
		img_org = bitmap_image.ConvertToImage();
		img_cpy = img_org.Copy();
		Repaint();
	}
}

void GUIMyFrame1::load_maskOnButtonClick(wxCommandEvent& event)
//wczytuje do zmiennej bitmap_mask bitmape i zmienia ja na typ wxImage - zmienna img_mask
{
	wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Mask file (*.bmp)|*.bmp"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (WxOpenFileDialog.ShowModal() == wxID_OK)
	{
		if (!bitmap_mask.LoadFile((const_cast<char*>((const char*)WxOpenFileDialog.GetPath().mb_str())), wxBITMAP_TYPE_ANY))
		{
			wxMessageBox(_("Nie uda\u0142o si\u0119 załadowa\u0107 maski"));
		}
	}
	if (!img_org.IsOk()) {
		wxMessageBox(_("Prosz\u0119 wczyta\u0107 obraz przed wczytaniem maski"));
		return;
	}
	if (bitmap_mask.IsOk()) {
		img_mask = bitmap_mask.ConvertToImage();
		set_mask();
	}
}

void GUIMyFrame1::save_imageOnButtonClick(wxCommandEvent& event)
//zapisuje do pliku to co jest w img_cpy
{
	if (img_cpy.IsOk()) {
		wxBitmap save(img_cpy);
		wxFileDialog WxSaveFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("config files (*.bmp)|*.bmp"), wxFD_SAVE);
		if (WxSaveFileDialog.ShowModal() == wxID_OK)
		{
			if (!save.SaveFile((const_cast<char*>((const char*)WxSaveFileDialog.GetPath().mb_str())), wxBITMAP_TYPE_BMP))
			{
				wxLogError(_("Nie uda\u0142o si\u0119 zapisa\u0107 obrazka"));
			}
		}
	}
	else
		wxMessageBox(_("Brak obrazka do zapisania"));
}

void GUIMyFrame1::mask_optionsOnRadioBox(wxCommandEvent& event)
//ustala zmienna pomocnicza mask_choice na odpowiedni int
{
	mask_choice = mask_options->GetSelection();
	if(img_cpy.IsOk())
		set_mask();
}

void GUIMyFrame1::color_optionsOnRadioBox(wxCommandEvent& event)
//ustala zmienna pomocnicza "color_choice" na odpowiedni char - R, G, B lub Z
{
	if (color_options->GetSelection() == 0) {
		color_choice = wxColour(255, 0, 0);
		all_colors = false;
		color_button->Enable(false);
	}
	else if (color_options->GetSelection() == 1) {
		color_choice = wxColour(0, 255, 0);
		all_colors = false;
		color_button->Enable(false);
	}
	else if (color_options->GetSelection() == 2) {
		color_choice = wxColour(0, 0, 255);
		all_colors = false;
		color_button->Enable(false);
	}
	else if (color_options->GetSelection() == 3) {
		all_colors = true;
		color_button->Enable(false);
	}
	else {
		all_colors = false;
		color_button->Enable(true);
	}
	if (img_cpy.IsOk())
		set_mask();
}


void GUIMyFrame1::colorButtonOnButtonClick(wxCommandEvent & event) {
	wxColourDialog colourDialog(this);
	if (colourDialog.ShowModal() == wxID_OK)
		color_choice = colourDialog.GetColourData().GetColour();
	set_mask(); 

}

void GUIMyFrame1::set_mask() 
//glowna funkcja  
{
	img_mask.Rescale(img_cpy.GetWidth(), img_cpy.GetHeight());

	img_cpy = img_org.Copy();
	int w = img_cpy.GetWidth();
	int h = img_cpy.GetHeight();
	unsigned char *data = img_cpy.GetData();
	unsigned char *mask_data = img_mask.GetData();
	
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (all_colors) {
				if (mask_choice == 1) {
					for (int k = 0; k < 3; k++) {
						if (data[3 * w * i + 3 * j + k] + mask_data[3 * w * i + 3 * j + k] > 255)
							data[3 * w * i + 3 * j + k] = 255;
						else data[3 * w * i + 3 * j + k] += mask_data[3 * w * i + 3 * j + k];
					}
				}
				else if (mask_choice == 2) {
					for (int k = 0; k < 3; k++) {
						float tmp = mask_data[3 * w * i + 3 * j + k] / 255.0;
						data[3 * w * i + 3 * j + k] *= tmp;
					}
				}
			}
			//Jesli piksel ma kolor inny niz "color_choice", maska przykrywa oryginalny obrazek na tym pikselu
			else if (mask_data[3 * w * i + 3 * j] != color_choice.Red() || mask_data[3 * w * i + 3 * j + 1] != color_choice.Green() || mask_data[3 * w * i + 3 * j + 2] != color_choice.Blue()){
				data[3 * w * i + 3 * j + 0] = mask_data[3 * w * i + 3 * j + 0];
				data[3 * w * i + 3 * j + 1] = mask_data[3 * w * i + 3 * j + 1];
				data[3 * w * i + 3 * j + 2] = mask_data[3 * w * i + 3 * j + 2];
			}
			//Jesli kolor piksela odpowiada "color_choice" i zachodzi przypadek sumowania kolorow
			else if (mask_choice == 1){
				for (int k = 0; k < 3; k++) {
					if (data[3 * w * i + 3 * j + k] + mask_data[3 * w * i + 3 * j + k] > 255)
						data[3 * w * i + 3 * j + k] = 255;
					else data[3 * w * i + 3 * j + k] += mask_data[3 * w * i + 3 * j + k];
				}
			}
			//Jesli kolor piksela odpowiada "color_choice" i zachodzi przypadek mnozenia kolorow
			else if(mask_choice == 2){
				float tmp = mask_data[3 * w * i + 3 * j] / 255.0;
				data[3 * w * i + 3 * j] *= tmp;
				tmp = mask_data[3 * w * i + 3 * j + 1] / 255.0;
				data[3 * w * i + 3 * j + 1] *= tmp;
				tmp = mask_data[3 * w * i + 3 * j + 2] / 255.0;
				data[3 * w * i + 3 * j + 2] *= tmp;
			}
		}
	}
	Repaint();
}

void GUIMyFrame1::Repaint()
//rysuje img_cpy - tam powinnien sie znajdowac obrazek oryginalny lub juz z nałożonš maskš
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
