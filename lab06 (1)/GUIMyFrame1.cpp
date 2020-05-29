#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
 m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
 this->SetBackgroundColour(wxColor(192, 192, 192));
 m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy().ConvertToGreyscale();
}

void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Blur(5);
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Mirror();
}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{
	m_scrolledWindow->ClearBackground();
	Img_Cpy = Img_Org.Scale(320, 240);
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy().Rotate(30. * 3.1415 / 180., wxPoint(Img_Org.GetWidth(), Img_Org.GetHeight()));
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.RotateHue(0.5);
}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event )
{
	m_scrolledWindow->ClearBackground();
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
Brightness(m_s_brightness->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
Contrast(m_s_contrast->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	int i, j, k, tmp;
	int w = Img_Org.GetWidth();
	int h = Img_Org.GetHeight();
	int size = w * h * 3;
	unsigned char *newData = Img_Cpy.GetData();
	unsigned char *oldData = new unsigned char[size];
	for (i = 0; i < size; i++) oldData[i] = newData[i];

	for (i = 1; i < h - 1; i++) {
		for (j = 1; j < w - 1; j++) {
			for (k = 0; k < 3; k++) {
				tmp = 0;
				tmp += oldData[3 * w * (i - 1) + 3 * (j + 1) + k];
				tmp += oldData[3 * w * i + 3 * (j + 1) + k];
				tmp += oldData[3 * w * (i + 1) + 3 * (j + 1) + k];
				tmp -= oldData[3 * w * (i - 1) + 3 * (j - 1) + k];
				tmp -= oldData[3 * w * i + 3 * (j - 1) + k];
				tmp -= oldData[3 * w * (i + 1) + 3 * (j - 1) + k];
				newData[3 * w * i + 3 * j + k] = fabs(tmp)/3.;
			}
		}
	}
	delete[] oldData;
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	int w = Img_Org.GetWidth();
	int h = Img_Org.GetHeight();
	int size = w * h * 3;
	unsigned char *data = Img_Cpy.GetData();
	for (int i = 0; i < size; i++) {
		if (data[i] < 128) data[i] = 0;
		else data[i] = 255;
	}
}


void GUIMyFrame1::Contrast(int value)
{
	Img_Cpy = Img_Org.Copy();
	int w = Img_Org.GetWidth();
	int h = Img_Org.GetHeight();
	int size = w * h * 3;
	unsigned char *data = Img_Cpy.GetData();
	int tmp;
	double contrast = (value + 100.) / (100.1 - value);
	for (int i = 0; i < size; i++) {
		tmp = (data[i] - 255. / 2.) * contrast + 255. / 2.;
		if (tmp > 255) tmp = 255;
		if (tmp < 0) tmp = 0;
		data[i] = tmp;
	}
}

void GUIMyFrame1::Repaint()
{
 wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
 wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
 m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
 dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

void GUIMyFrame1::Brightness(int value)
{
	Img_Cpy = Img_Org.Copy();
	int w = Img_Org.GetWidth();
	int h = Img_Org.GetHeight();
	int size = w * h * 3;
	unsigned char *data = Img_Cpy.GetData();
	int tmp;
	for (int i = 0; i < size; i++) {
		tmp = data[i] + value;
		if (tmp > 255) tmp = 255;
		if (tmp < 0) tmp = 0;
		data[i] = tmp;
	}
}