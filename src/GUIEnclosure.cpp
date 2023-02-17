/*
 * GUIEnclosure.cpp is part of GOODF.
 * Copyright (C) 2023 Lars Palo
 *
 * GOODF is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GOODF is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GOODF.  If not, see <https://www.gnu.org/licenses/>.
 *
 * You can contact the author on larspalo(at)yahoo.se
 */

#include "GUIEnclosure.h"
#include "GOODFFunctions.h"
#include "GOODF.h"

GUIEnclosure::GUIEnclosure(Enclosure *enclosure) : GUIElement(), m_enclosure(enclosure) {
	if (m_enclosure != NULL)
		m_type = wxT("Enclosure");
	else
		m_type = wxT("Swell");

	m_dispLabelColour.setSelectedColorIndex(16);
	m_dispLabelFontSize.setSizeValue(7);
	m_dispLabelFont = wxFont(wxFontInfo(7).FaceName(wxT("Arial")));
	m_dispLabelText = wxEmptyString;
	m_enclosureStyle = 1;
	m_width = 0;
	m_height = 0;
	m_tileOffsetX = 0;
	m_tileOffsetY = 0;
	m_mouseRectLeft = 0;
	m_mouseRectTop = 0;
	m_mouseRectWidth = 0;
	m_mouseRectHeight = 0;
	m_mouseAxisStart = 0;
	m_mouseAxisEnd = 0;
	m_textRectLeft = 0;
	m_textRectTop = 0;
	m_textRectWidth = 0;
	m_textRectHeight = 0;
	m_textBreakWidth = 0;
	m_bitmapWidth = 0;
	m_bitmapHeight = 0;
}

GUIEnclosure::~GUIEnclosure() {

}

void GUIEnclosure::write(wxTextFile *outFile) {
	GUIElement::write(outFile);
	if (m_enclosure != NULL) {
		wxString encId = wxT("Enclosure=") + GOODF_functions::number_format(::wxGetApp().m_frame->m_organ->getIndexOfOrganEnclosure(m_enclosure));
		outFile->AddLine(encId);
	}
	if (m_positionX != -1)
		outFile->AddLine(wxT("PositionX=") + wxString::Format(wxT("%i"), m_positionX));
	if (m_positionY != -1)
		outFile->AddLine(wxT("PositionY=") + wxString::Format(wxT("%i"), m_positionY));
	if (m_dispLabelColour.getSelectedColorIndex() != 16) {
		if (m_dispLabelColour.getSelectedColorIndex() > -1) {
			outFile->AddLine(wxT("DispLabelColour=") + m_dispLabelColour.getColorName());
		} else {
			outFile->AddLine(wxT("DispLabelColour=") + m_dispLabelColour.getHtmlValue());
		}
	}
	if (m_dispLabelFontSize.getSizeValue() != 7) {
		if (m_dispLabelFontSize.getSelectedSizeIndex() > -1) {
			outFile->AddLine(wxT("DispLabelFontSize=") + m_dispLabelFontSize.getSizeName());
		} else {
			outFile->AddLine(wxT("DispLabelFontSize=") + m_dispLabelFontSize.getSizeValue());
		}
	}
	if (m_dispLabelFont != wxFont(wxFontInfo(7).FaceName(wxT("Arial"))))
		outFile->AddLine(wxT("DispLabelFontName=") + m_dispLabelFont.GetFaceName());
	if (m_dispLabelText != wxEmptyString)
		outFile->AddLine(wxT("DispLabelText=") + m_dispLabelText);
	if (m_enclosureStyle != 1 && m_bitmaps.empty())
		outFile->AddLine(wxT("EnclosureStyle=") + wxString::Format(wxT("%i"), m_enclosureStyle));
	if (!m_bitmaps.empty()) {
		unsigned nbBitmaps = m_bitmaps.size();
		outFile->AddLine(wxT("BitmapCount=") + wxString::Format(wxT("%u"), nbBitmaps));
		unsigned counter = 1;
		for (GoImage& bitmap : m_bitmaps) {
			wxString bitmapId = wxT("Bitmap") + GOODF_functions::number_format(counter) + wxT("=");
			outFile->AddLine(bitmapId + bitmap.getRelativeImagePath());
			if (bitmap.getMask() != wxEmptyString) {
				wxString maskId = wxT("Mask") + GOODF_functions::number_format(counter) + wxT("=");
				outFile->AddLine(maskId + bitmap.getRelativeMaskPath());
			}
			counter++;
		}
	}
	if (m_width != m_bitmapWidth)
		outFile->AddLine(wxT("Width=") + wxString::Format(wxT("%i"), m_width));
	if (m_height != m_bitmapHeight)
		outFile->AddLine(wxT("Height=") + wxString::Format(wxT("%i"), m_height));
	if (m_tileOffsetX != 0)
		outFile->AddLine(wxT("TileOffsetX=") + wxString::Format(wxT("%i"), m_tileOffsetX));
	if (m_tileOffsetY != 0)
		outFile->AddLine(wxT("TileOffsetY=") + wxString::Format(wxT("%i"), m_tileOffsetY));
	if (m_mouseRectLeft != 0)
		outFile->AddLine(wxT("MouseRectLeft=") + wxString::Format(wxT("%i"), m_mouseRectLeft));
	if (m_mouseRectTop != 0)
		outFile->AddLine(wxT("MouseRectTop=") + wxString::Format(wxT("%i"), m_mouseRectTop));
	if (m_mouseRectWidth != m_width)
		outFile->AddLine(wxT("MouseRectWidth=") + wxString::Format(wxT("%i"), m_mouseRectWidth));
	if (m_mouseRectHeight != m_height)
		outFile->AddLine(wxT("MouseRectHeight=") + wxString::Format(wxT("%i"), m_mouseRectHeight));
	if (m_mouseAxisStart != m_mouseRectHeight)
		outFile->AddLine(wxT("MouseAxisStart=") + wxString::Format(wxT("%i"), m_mouseAxisStart));
	if (m_mouseAxisEnd != (m_mouseAxisStart - m_mouseRectHeight))
		outFile->AddLine(wxT("MouseAxisEnd=") + wxString::Format(wxT("%i"), m_mouseAxisEnd));
	if (m_textRectLeft != 0)
		outFile->AddLine(wxT("TextRectLeft=") + wxString::Format(wxT("%i"), m_textRectLeft));
	if (m_textRectTop != 0)
		outFile->AddLine(wxT("TextRectTop=") + wxString::Format(wxT("%i"), m_textRectTop));
	if (m_textRectWidth != m_width)
		outFile->AddLine(wxT("TextRectWidth=") + wxString::Format(wxT("%i"), m_textRectWidth));
	if (m_textRectHeight != m_height)
		outFile->AddLine(wxT("TextRectHeight=") + wxString::Format(wxT("%i"), m_textRectHeight));
	if (m_textBreakWidth != m_textRectWidth)
		outFile->AddLine(wxT("TextBreakWidth=") + wxString::Format(wxT("%i"), m_textBreakWidth));
}

bool GUIEnclosure::isReferencing(Enclosure *enclosure) {
	return m_enclosure == enclosure ? true : false;
}

void GUIEnclosure::updateDisplayName() {
	setDisplayName(m_enclosure->getName());
}

const GoColor& GUIEnclosure::getDispLabelColour() const {
	return m_dispLabelColour;
}

void GUIEnclosure::setDispLabelColour(const GoColor &dispLabelColour) {
	m_dispLabelColour = dispLabelColour;
}

const GoFontSize& GUIEnclosure::getDispLabelFontSize() const {
	return m_dispLabelFontSize;
}

void GUIEnclosure::setDispLabelFontSize(int fontSize) {
	m_dispLabelFontSize.setSizeValue(fontSize);
}

const wxString& GUIEnclosure::getDispLabelText() const {
	return m_dispLabelText;
}

void GUIEnclosure::setDispLabelText(const wxString &dispLabelText) {
	m_dispLabelText = dispLabelText;
}

void GUIEnclosure::setDispLabelFont(wxFont font) {
	m_dispLabelFont = font;
}

wxFont GUIEnclosure::getDispLabelFont() {
	return m_dispLabelFont;
}

int GUIEnclosure::getEnclosureStyle() const {
	return m_enclosureStyle;
}

void GUIEnclosure::setEnclosureStyle(int enclosureStyle) {
	m_enclosureStyle = enclosureStyle;
}

int GUIEnclosure::getHeight() const {
	return m_height;
}

void GUIEnclosure::setHeight(int height) {
	m_height = height;
}

int GUIEnclosure::getMouseAxisEnd() const {
	return m_mouseAxisEnd;
}

void GUIEnclosure::setMouseAxisEnd(int mouseAxisEnd) {
	m_mouseAxisEnd = mouseAxisEnd;
}

int GUIEnclosure::getMouseAxisStart() const {
	return m_mouseAxisStart;
}

void GUIEnclosure::setMouseAxisStart(int mouseAxisStart) {
	m_mouseAxisStart = mouseAxisStart;
}

int GUIEnclosure::getMouseRectHeight() const {
	return m_mouseRectHeight;
}

void GUIEnclosure::setMouseRectHeight(int mouseRectHeight) {
	m_mouseRectHeight = mouseRectHeight;
}

int GUIEnclosure::getMouseRectLeft() const {
	return m_mouseRectLeft;
}

void GUIEnclosure::setMouseRectLeft(int mouseRectLeft) {
	m_mouseRectLeft = mouseRectLeft;
}

int GUIEnclosure::getMouseRectTop() const {
	return m_mouseRectTop;
}

void GUIEnclosure::setMouseRectTop(int mouseRectTop) {
	m_mouseRectTop = mouseRectTop;
}

int GUIEnclosure::getMouseRectWidth() const {
	return m_mouseRectWidth;
}

void GUIEnclosure::setMouseRectWidth(int mouseRectWidth) {
	m_mouseRectWidth = mouseRectWidth;
}

int GUIEnclosure::getTextBreakWidth() const {
	return m_textBreakWidth;
}

void GUIEnclosure::setTextBreakWidth(int textBreakWidth) {
	m_textBreakWidth = textBreakWidth;
}

int GUIEnclosure::getTextRectHeight() const {
	return m_textRectHeight;
}

void GUIEnclosure::setTextRectHeight(int textRectHeight) {
	m_textRectHeight = textRectHeight;
}

int GUIEnclosure::getTextRectLeft() const {
	return m_textRectLeft;
}

void GUIEnclosure::setTextRectLeft(int textRectLeft) {
	m_textRectLeft = textRectLeft;
}

int GUIEnclosure::getTextRectTop() const {
	return m_textRectTop;
}

void GUIEnclosure::setTextRectTop(int textRectTop) {
	m_textRectTop = textRectTop;
}

int GUIEnclosure::getTextRectWidth() const {
	return m_textRectWidth;
}

void GUIEnclosure::setTextRectWidth(int textRectWidth) {
	m_textRectWidth = textRectWidth;
}

int GUIEnclosure::getTileOffsetX() const {
	return m_tileOffsetX;
}

void GUIEnclosure::setTileOffsetX(int tileOffsetX) {
	m_tileOffsetX = tileOffsetX;
}

int GUIEnclosure::getTileOffsetY() const {
	return m_tileOffsetY;
}

void GUIEnclosure::setTileOffsetY(int tileOffsetY) {
	m_tileOffsetY = tileOffsetY;
}

int GUIEnclosure::getWidth() const {
	return m_width;
}

void GUIEnclosure::setWidth(int width) {
	m_width = width;
}

void GUIEnclosure::addBitmap(GoImage bitmap) {
	if (m_bitmaps.size() < 128)
		m_bitmaps.push_back(bitmap);
}

unsigned GUIEnclosure::getNumberOfBitmaps() {
	return m_bitmaps.size();
}

GoImage* GUIEnclosure::getBitmapAtIndex(unsigned index) {
	auto iterator = std::next(m_bitmaps.begin(), index);
	return &(*iterator);
}

void GUIEnclosure::removeBitmapAt(unsigned index) {
	std::list<GoImage>::iterator it = m_bitmaps.begin();
	std::advance(it, index);
	m_bitmaps.erase(it);
}

void GUIEnclosure::setBitmapWidth(int width) {
	m_bitmapWidth = width;
}

int GUIEnclosure::getBitmapWidth() {
	return m_bitmapWidth;
}

void GUIEnclosure::setBitmapHeight(int height) {
	m_bitmapHeight = height;
}

int GUIEnclosure::getBitmapHeight() {
	return m_bitmapHeight;
}
