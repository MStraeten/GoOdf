/* 
 * GOODF.cpp is a part of GOODF software
 * Copyright (C) 2023 Lars Palo and contributors (see AUTHORS)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * You can contact the author on larspalo(at)yahoo DOT se
 */

#include "GOODF.h"
#include "GOODFDef.h"
#include "GoImages.h"
#include <wx/image.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include "wx/fs_zip.h"

IMPLEMENT_APP(GOODF)

bool GOODF::OnInit() {
	// Create fullAppName with version from cmake
	wxString fullAppName = wxT("GOODF ");
	fullAppName.Append(wxT(GOODF_VERSION));

	// Create the frame window
	m_frame = new GOODFFrame(fullAppName);

	// Fix paths/locations
	wxFileName fn(wxStandardPaths::Get().GetExecutablePath());
	fn = fn.GetPath();
	wxString BaseDir = fn.GetPath();
	wxString ResourceDir = BaseDir + wxFILE_SEP_PATH + wxT("share");

	// the help controller
	wxFileSystem::AddHandler(new wxZipFSHandler);
	m_helpController = new wxHtmlHelpController();
	m_helpController->AddBook(wxFileName(ResourceDir + wxFILE_SEP_PATH + wxT("GOODF/help/help.zip")));
	m_helpController->SetFrameParameters(wxT("%s"), wxDefaultSize, wxDefaultPosition);

	// Load icons
	wxImage::AddHandler(new wxPNGHandler);
	wxString iconPath = ResourceDir + wxFILE_SEP_PATH + wxT("icons") + wxFILE_SEP_PATH + wxT("hicolor");
	wxString appsPath = wxT("apps");
	wxString imgPath = appsPath + wxFILE_SEP_PATH + wxT("GOODF.png");
	m_icons = wxIconBundle(wxIcon(iconPath + wxFILE_SEP_PATH + wxT("16x16") + wxFILE_SEP_PATH + imgPath, wxBITMAP_TYPE_PNG));
	m_icons.AddIcon(wxIcon(iconPath + wxFILE_SEP_PATH + wxT("24x24") + wxFILE_SEP_PATH + imgPath, wxBITMAP_TYPE_PNG));
	m_icons.AddIcon(wxIcon(iconPath + wxFILE_SEP_PATH + wxT("32x32") + wxFILE_SEP_PATH + imgPath, wxBITMAP_TYPE_PNG));
	m_icons.AddIcon(wxIcon(iconPath + wxFILE_SEP_PATH + wxT("48x48") + wxFILE_SEP_PATH + imgPath, wxBITMAP_TYPE_PNG));
	m_icons.AddIcon(wxIcon(iconPath + wxFILE_SEP_PATH + wxT("64x64") + wxFILE_SEP_PATH + imgPath, wxBITMAP_TYPE_PNG));
	m_icons.AddIcon(wxIcon(iconPath + wxFILE_SEP_PATH + wxT("128x128") + wxFILE_SEP_PATH + imgPath, wxBITMAP_TYPE_PNG));
	m_icons.AddIcon(wxIcon(iconPath + wxFILE_SEP_PATH + wxT("256x256") + wxFILE_SEP_PATH + imgPath, wxBITMAP_TYPE_PNG));
	m_icons.AddIcon(wxIcon(iconPath + wxFILE_SEP_PATH + wxT("512x512") + wxFILE_SEP_PATH + imgPath, wxBITMAP_TYPE_PNG));
	m_icons.AddIcon(wxIcon(iconPath + wxFILE_SEP_PATH + wxT("1024x1024") + wxFILE_SEP_PATH + imgPath, wxBITMAP_TYPE_PNG));

	m_frame->SetIcons(m_icons);

	// Extract embedded images
	wxBitmap drawstop1 = wxBITMAP_PNG_FROM_DATA(drawstop01off);
	wxBitmap drawstop2 = wxBITMAP_PNG_FROM_DATA(drawstop02off);
	wxBitmap drawstop3 = wxBITMAP_PNG_FROM_DATA(drawstop03off);
	wxBitmap drawstop4 = wxBITMAP_PNG_FROM_DATA(drawstop04off);
	wxBitmap drawstop5 = wxBITMAP_PNG_FROM_DATA(drawstop05off);
	wxBitmap drawstop6 = wxBITMAP_PNG_FROM_DATA(drawstop06off);
	wxBitmap drawstop7 = wxBITMAP_PNG_FROM_DATA(drawstop07off);
	wxImage drawstopImage = drawstop1.ConvertToImage();
	drawstop1 = wxBitmap(drawstopImage.Scale(32, 32));
	drawstopImage = drawstop2.ConvertToImage();
	drawstop2 = wxBitmap(drawstopImage.Scale(32, 32));
	drawstopImage = drawstop3.ConvertToImage();
	drawstop3 = wxBitmap(drawstopImage.Scale(32, 32));
	drawstopImage = drawstop4.ConvertToImage();
	drawstop4 = wxBitmap(drawstopImage.Scale(32, 32));
	drawstopImage = drawstop5.ConvertToImage();
	drawstop5 = wxBitmap(drawstopImage.Scale(32, 32));
	drawstopImage = drawstop6.ConvertToImage();
	drawstop6 = wxBitmap(drawstopImage.Scale(32, 32));
	drawstopImage = drawstop7.ConvertToImage();
	drawstop7 = wxBitmap(drawstopImage.Scale(32, 32));

	m_drawstopBitmaps.push_back(drawstop1);
	m_drawstopBitmaps.push_back(drawstop2);
	m_drawstopBitmaps.push_back(drawstop3);
	m_drawstopBitmaps.push_back(drawstop4);
	m_drawstopBitmaps.push_back(drawstop5);
	m_drawstopBitmaps.push_back(drawstop6);
	m_drawstopBitmaps.push_back(drawstop7);

	wxBitmap piston1 = wxBITMAP_PNG_FROM_DATA(piston01off);
	wxBitmap piston2 = wxBITMAP_PNG_FROM_DATA(piston02off);
	wxBitmap piston3 = wxBITMAP_PNG_FROM_DATA(piston03off);
	wxBitmap piston4 = wxBITMAP_PNG_FROM_DATA(piston04off);
	wxBitmap piston5 = wxBITMAP_PNG_FROM_DATA(piston05off);
	m_buttonBitmaps.push_back(piston1);
	m_buttonBitmaps.push_back(piston2);
	m_buttonBitmaps.push_back(piston3);
	m_buttonBitmaps.push_back(piston4);
	m_buttonBitmaps.push_back(piston5);

	wxBitmap enclosure1 = wxBITMAP_PNG_FROM_DATA(EnclosureA00);
	wxBitmap enclosure2 = wxBITMAP_PNG_FROM_DATA(EnclosureB00);
	wxBitmap enclosure3 = wxBITMAP_PNG_FROM_DATA(EnclosureC00);
	wxBitmap enclosure4 = wxBITMAP_PNG_FROM_DATA(EnclosureD00);
	m_enclosureStyleBitmaps.push_back(enclosure1);
	m_enclosureStyleBitmaps.push_back(enclosure2);
	m_enclosureStyleBitmaps.push_back(enclosure3);
	m_enclosureStyleBitmaps.push_back(enclosure4);

	wxBitmap label1 = wxBITMAP_PNG_FROM_DATA(label01);
	// wxBitmap label2 = wxBITMAP_PNG_FROM_DATA(label02); Same style as 03 but 80x50
	wxBitmap label3 = wxBITMAP_PNG_FROM_DATA(label03);
	// wxBitmap label4 = wxBITMAP_PNG_FROM_DATA(label04); Same style as 03 but 160x25
	// wxBitmap label5 = wxBITMAP_PNG_FROM_DATA(label05); Same style as 03 but 200x50
	// wxBitmap label6 = wxBITMAP_PNG_FROM_DATA(label06); Same style as 07 but 80x50
	wxBitmap label7 = wxBITMAP_PNG_FROM_DATA(label07);
	// wxBitmap label8 = wxBITMAP_PNG_FROM_DATA(label08); Same style as 07 but 160x25
	// wxBitmap label9 = wxBITMAP_PNG_FROM_DATA(label09); Same style as 10 but 80x50
	wxBitmap label10 = wxBITMAP_PNG_FROM_DATA(label10);
	// wxBitmap label11 = wxBITMAP_PNG_FROM_DATA(label11); Same style as 10 but 160x25
	// wxBitmap label12 = wxBITMAP_PNG_FROM_DATA(label12); Same style as 10 but 200x50
	wxBitmap label13 = wxBITMAP_PNG_FROM_DATA(label13);
	wxImage labelImage = label13.ConvertToImage();
	label13 = wxBitmap(labelImage.Scale(80, 25));
	wxBitmap label14 = wxBITMAP_PNG_FROM_DATA(label14);
	labelImage = label14.ConvertToImage();
	label14 = wxBitmap(labelImage.Scale(80, 25));
	wxBitmap label15 = wxBITMAP_PNG_FROM_DATA(label15);
	labelImage = label15.ConvertToImage();
	label15 = wxBitmap(labelImage.Scale(80, 25));
	m_labelBitmaps.push_back(wxNullBitmap);
	m_labelBitmaps.push_back(label1);
	m_labelBitmaps.push_back(label3);
	m_labelBitmaps.push_back(label3);
	m_labelBitmaps.push_back(label3);
	m_labelBitmaps.push_back(label3);
	m_labelBitmaps.push_back(label7);
	m_labelBitmaps.push_back(label7);
	m_labelBitmaps.push_back(label7);
	m_labelBitmaps.push_back(label10);
	m_labelBitmaps.push_back(label10);
	m_labelBitmaps.push_back(label10);
	m_labelBitmaps.push_back(label10);
	m_labelBitmaps.push_back(label13);
	m_labelBitmaps.push_back(label14);
	m_labelBitmaps.push_back(label15);

	wxBitmap defaultManual1 = wxBITMAP_PNG_FROM_DATA(ManualDefaultComposite01);
	wxBitmap defaultManual2 = wxBITMAP_PNG_FROM_DATA(ManualDefaultComposite02);
	m_defaultManualBitmaps.push_back(defaultManual1);
	m_defaultManualBitmaps.push_back(defaultManual2);

	wxBitmap invertedManual1 = wxBITMAP_PNG_FROM_DATA(ManualInvertedComposite01);
	wxBitmap invertedManual2 = wxBITMAP_PNG_FROM_DATA(ManualInvertedComposite02);
	m_invertedManualBitmaps.push_back(invertedManual1);
	m_invertedManualBitmaps.push_back(invertedManual2);

	wxBitmap woodenManual1 = wxBITMAP_PNG_FROM_DATA(ManualWoodenComposite01);
	wxBitmap woodenManual2 = wxBITMAP_PNG_FROM_DATA(ManualWoodenComposite02);
	m_woodenManualBitmaps.push_back(woodenManual1);
	m_woodenManualBitmaps.push_back(woodenManual2);

	wxBitmap invertedWoodenManual1 = wxBITMAP_PNG_FROM_DATA(ManualInvertedWoodenComposite01);
	wxBitmap invertedWoodenManual2 = wxBITMAP_PNG_FROM_DATA(ManualInvertedWoodenComposite02);
	m_invertedWoodenManualBitmaps.push_back(invertedWoodenManual1);
	m_invertedWoodenManualBitmaps.push_back(invertedWoodenManual2);

	wxBitmap defaultPedal1 = wxBITMAP_PNG_FROM_DATA(PedalDefaultComposite01);
	wxBitmap defaultPedal2 = wxBITMAP_PNG_FROM_DATA(PedalDefaultComposite02);
	m_defaultPedalBitmaps.push_back(defaultPedal1);
	m_defaultPedalBitmaps.push_back(defaultPedal2);

	wxBitmap invertedPedal1 = wxBITMAP_PNG_FROM_DATA(PedalInvertedComposite01);
	wxBitmap invertedPedal2 = wxBITMAP_PNG_FROM_DATA(PedalInvertedComposite02);
	m_invertedPedalBitmaps.push_back(invertedPedal1);
	m_invertedPedalBitmaps.push_back(invertedPedal2);

	// Show the frame
	m_frame->Show(true);

	// Start the event loop
	return true;
}

int GOODF::OnExit() {
	return wxApp::OnExit();
}
