/* ASEPRITE
 * Copyright (C) 2001-2012  David Capello
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef WIDGETS_DROP_DOWN_BUTTON_H_INCLUDED
#define WIDGETS_DROP_DOWN_BUTTON_H_INCLUDED

#include "base/signal.h"
#include "ui/box.h"

namespace ui {
  class Button;
  class Event;
}

class DropDownButton : public ui::HBox
{
public:
  DropDownButton(const char* text);

  Signal0<void> Click;
  Signal0<void> DropDownClick;

protected:
  void onButtonClick(ui::Event& ev);
  void onDropDownButtonClick(ui::Event& ev);

private:
  ui::Button* m_button;
  ui::Button* m_dropDown;
};

#endif
