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
	if (bitmap_image.IsOk()) {
		img_org = bitmap_image.ConvertToImage();
		img_cpy = img_org.Copy();
		Repaint();
	}
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
	}
	if (bitmap_mask.IsOk()) {
		img_mask = bitmap_mask.ConvertToImage();
		set_mask();
	}
}

void GUIMyFrame1::save_imageOnButtonClick(wxCommandEvent& event)
//zapisuje do pliku to co jest w new_image ( na razie nic )
{
	if (img_cpy.IsOk()) {
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
}

void GUIMyFrame1::mask_optionsOnRadioBox(wxCommandEvent& event)
//ustala zmienna pomocnicza mask_choice na odpowiedni int
{
	mask_choice = mask_options->GetSelection();
	if(img_cpy.IsOk())
		set_mask();
}

void GUIMyFrame1::color_optionsOnRadioBox(wxCommandEvent& event)
//ustala zmienna pomocnicza "base_color" na odpowiedni kolorek
{
	if (color_options->GetSelection() == 0)
		color_choice = 'R';
	else if (color_options->GetSelection() == 1)
		color_choice = 'G';
	else if (color_options->GetSelection() == 2)
		color_choice = 'B';
	else
		color_choice = 'Z';
	if (img_cpy.IsOk())
		set_mask();
}

void GUIMyFrame1::set_mask() 
//glowna funkcja  
{
	img_cpy = img_org.Copy();
	int w = img_mask.GetWidth();
	int h = img_mask.GetHeight();
	int size = w * h * 3;
	unsigned char *data = img_cpy.GetData();
	unsigned char *mask_data = img_mask.GetData();
	//pewnie optymalizacja by byla lepsza gdyby te warunki wyciagnac przed petle i zrobic kilka petli
	//ale kto by sie tym przejmowal

	if (mask_choice == 0) {
		//zamiana kolorow
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (color_choice == 'R') {
					//sprawdzamy czy piksel w masce ma kolor inny niz (255, 0, 0), jesli tak to wchodzimy do warunku
					if (mask_data[3 * w * i + 3 * j] != 255 || mask_data[3 * w * i + 3 * j + 1] + mask_data[3 * w * i + 3 * j + 2] != 0) {
						data[3 * w * i + 3 * j + 0] = mask_data[3 * w * i + 3 * j + 0];
						data[3 * w * i + 3 * j + 1] = mask_data[3 * w * i + 3 * j + 1];
						data[3 * w * i + 3 * j + 2] = mask_data[3 * w * i + 3 * j + 2];
					}
				}
				else if (color_choice == 'G') {
					//sprawdzamy czy piksel w masce ma kolor inny niz (0, 255, 0), jesli tak to wchodzimy do warunku
					if (mask_data[3 * w * i + 3 * j + 1] != 255 || mask_data[3 * w * i + 3 * j] + mask_data[3 * w * i + 3 * j + 2] != 0) {
						data[3 * w * i + 3 * j + 0] = mask_data[3 * w * i + 3 * j + 0];
						data[3 * w * i + 3 * j + 1] = mask_data[3 * w * i + 3 * j + 1];
						data[3 * w * i + 3 * j + 2] = mask_data[3 * w * i + 3 * j + 2];
					}
				}
				else if (color_choice == 'B') {
					//sprawdzamy czy piksel w masce ma kolor inny niz (0, 0, 255), jesli tak to wchodzimy do warunku
					if (mask_data[3 * w * i + 3 * j + 2] != 255 || mask_data[3 * w * i + 3 * j] + mask_data[3 * w * i + 3 * j + 1] != 0) {
						data[3 * w * i + 3 * j + 0] = mask_data[3 * w * i + 3 * j + 0];
						data[3 * w * i + 3 * j + 1] = mask_data[3 * w * i + 3 * j + 1];
						data[3 * w * i + 3 * j + 2] = mask_data[3 * w * i + 3 * j + 2];
					}
				}
				else { //color_choice == 'Z'
					data[3 * w * i + 3 * j + 0] = mask_data[3 * w * i + 3 * j + 0];
					data[3 * w * i + 3 * j + 1] = mask_data[3 * w * i + 3 * j + 1];
					data[3 * w * i + 3 * j + 2] = mask_data[3 * w * i + 3 * j + 2];
				}
			}
		}
	}
	else if (mask_choice == 1) {
		//sumowanie kolorow
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (color_choice == 'R') {
					//sprawdzamy czy piksel w masce ma kolor inny niz (255, 0, 0), jesli tak to wchodzimy do warunku
					if (mask_data[3 * w * i + 3 * j] != 255 || mask_data[3 * w * i + 3 * j + 1] + mask_data[3 * w * i + 3 * j + 2] != 0) {
						data[3 * w * i + 3 * j + 0] = mask_data[3 * w * i + 3 * j + 0];
						data[3 * w * i + 3 * j + 1] = mask_data[3 * w * i + 3 * j + 1];
						data[3 * w * i + 3 * j + 2] = mask_data[3 * w * i + 3 * j + 2];
					}
					//tu dalem petle zeby 3 razy nie wrzucac if-else
					else {
						for (int k = 0; k < 3; k++) {
							if (data[3 * w * i + 3 * j + k] + mask_data[3 * w * i + 3 * j + k] > 255)
								data[3 * w * i + 3 * j + k] = 255;
							else data[3 * w * i + 3 * j + k] += mask_data[3 * w * i + 3 * j + k];
						}
					}
				}
				else if (color_choice == 'G') {
					//sprawdzamy czy piksel w masce ma kolor inny niz (0, 255, 0), jesli tak to wchodzimy do warunku
					if (mask_data[3 * w * i + 3 * j + 1] != 255 || mask_data[3 * w * i + 3 * j] + mask_data[3 * w * i + 3 * j + 2] != 0) {
						data[3 * w * i + 3 * j + 0] = mask_data[3 * w * i + 3 * j + 0];
						data[3 * w * i + 3 * j + 1] = mask_data[3 * w * i + 3 * j + 1];
						data[3 * w * i + 3 * j + 2] = mask_data[3 * w * i + 3 * j + 2];
					}
					else {
						for (int k = 0; k < 3; k++) {
							if (data[3 * w * i + 3 * j + k] + mask_data[3 * w * i + 3 * j + k] > 255)
								data[3 * w * i + 3 * j + k] = 255;
							else data[3 * w * i + 3 * j + k] += mask_data[3 * w * i + 3 * j + k];
						}
					}
				}
				else if (color_choice == 'B') {
					//sprawdzamy czy piksel w masce ma kolor inny niz (0, 0, 255), jesli tak to wchodzimy do warunku
					if (mask_data[3 * w * i + 3 * j + 2] != 255 || mask_data[3 * w * i + 3 * j] + mask_data[3 * w * i + 3 * j + 1] != 0) {
						data[3 * w * i + 3 * j + 0] = mask_data[3 * w * i + 3 * j + 0];
						data[3 * w * i + 3 * j + 1] = mask_data[3 * w * i + 3 * j + 1];
						data[3 * w * i + 3 * j + 2] = mask_data[3 * w * i + 3 * j + 2];
					}
					else {
						for (int k = 0; k < 3; k++) {
							if (data[3 * w * i + 3 * j + k] + mask_data[3 * w * i + 3 * j + k] > 255)
								data[3 * w * i + 3 * j + k] = 255;
							else data[3 * w * i + 3 * j + k] += mask_data[3 * w * i + 3 * j + k];
						}
					}
				}
				else { //color_choice == 'Z'
					for (int k = 0; k < 3; k++) {
						if (data[3 * w * i + 3 * j + k] + mask_data[3 * w * i + 3 * j + k] > 255)
							data[3 * w * i + 3 * j + k] = 255;
						else data[3 * w * i + 3 * j + k] += mask_data[3 * w * i + 3 * j + k];
					}
				}
			}
		}
	}
	else {
		//mnozenie kolorow
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (color_choice == 'Z') {
					for (int k = 0; k < 3; k++) {
						float tmp = mask_data[3 * w * i + 3 * j + k] / 255.0;
						data[3 * w * i + 3 * j + k] *= tmp;
					}
				}
				else if (color_choice == 'R') {
					//sprawdzamy czy piksel w masce ma kolor inny niz (255, 0, 0), jesli tak to wchodzimy do warunku
					float tmp = mask_data[3 * w * i + 3 * j + 1] / 255.0;
					data[3 * w * i + 3 * j + 1] *= tmp;
					tmp = mask_data[3 * w * i + 3 * j + 2] / 255.0;
					data[3 * w * i + 3 * j + 2] *= tmp;
				}
				else if (color_choice == 'G') {
					//sprawdzamy czy piksel w masce ma kolor inny niz (0, 255, 0), jesli tak to wchodzimy do warunku
					float tmp = mask_data[3 * w * i + 3 * j] / 255.0;
					data[3 * w * i + 3 * j] *= tmp;
					tmp = mask_data[3 * w * i + 3 * j + 2] / 255.0;
					data[3 * w * i + 3 * j + 2] *= tmp;
				}
				else {
					//sprawdzamy czy piksel w masce ma kolor inny niz (0, 0, 255), jesli tak to wchodzimy do warunku
					float tmp = mask_data[3 * w * i + 3 * j] / 255.0;
					data[3 * w * i + 3 * j] *= tmp;
					tmp = mask_data[3 * w * i + 3 * j + 1] / 255.0;
					data[3 * w * i + 3 * j + 1] *= tmp;
				}
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