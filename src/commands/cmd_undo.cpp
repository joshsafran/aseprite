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

#include "config.h"

#include "app.h"
#include "base/thread.h"
#include "commands/command.h"
#include "document_undo.h"
#include "document_wrappers.h"
#include "ini_file.h"
#include "modules/editors.h"
#include "modules/gui.h"
#include "raster/sprite.h"
#include "ui/system.h"
#include "widgets/editor/editor.h"
#include "widgets/status_bar.h"

class UndoCommand : public Command
{
public:
  enum Type { Undo, Redo };

  UndoCommand(Type type);
  Command* clone() { return new UndoCommand(*this); }

protected:
  bool onEnabled(Context* context);
  void onExecute(Context* context);

private:
  Type m_type;
};

UndoCommand::UndoCommand(Type type)
  : Command((type == Undo ? "Undo": "Redo"),
            (type == Undo ? "Undo": "Redo"),
            CmdUIOnlyFlag)
  , m_type(type)
{
}

bool UndoCommand::onEnabled(Context* context)
{
  ActiveDocumentWriter document(context);
  return
    document != NULL &&
    ((m_type == Undo ? document->getUndo()->canUndo():
                       document->getUndo()->canRedo()));
}

void UndoCommand::onExecute(Context* context)
{
  ActiveDocumentWriter document(context);
  DocumentUndo* undo = document->getUndo();
  Sprite* sprite = document->getSprite();

  if (get_config_bool("Options", "UndoGotoModified", true)) {
    SpritePosition spritePosition;

    if (m_type == Undo)
      spritePosition = undo->getNextUndoSpritePosition();
    else
      spritePosition = undo->getNextRedoSpritePosition();

    if (spritePosition != sprite->getCurrentPosition()) {
      sprite->setCurrentPosition(spritePosition);

      current_editor->drawSpriteSafe(0, 0, sprite->getWidth(), sprite->getHeight());
      update_screen_for_document(document);

      ui::dirty_display_flag = true;
      gui_feedback();

      base::this_thread::sleep_for(0.01);
    }
  }

  StatusBar::instance()
    ->showTip(1000, "%s %s",
              (m_type == Undo ? "Undid": "Redid"),
              (m_type == Undo ? undo->getNextUndoLabel():
                                undo->getNextRedoLabel()));

  if (m_type == Undo)
    undo->doUndo();
  else
    undo->doRedo();

  document->generateMaskBoundaries();
  document->destroyExtraCel(); // Regenerate extras

  update_screen_for_document(document);
}

//////////////////////////////////////////////////////////////////////
// CommandFactory

Command* CommandFactory::createUndoCommand()
{
  return new UndoCommand(UndoCommand::Undo);
}

Command* CommandFactory::createRedoCommand()
{
  return new UndoCommand(UndoCommand::Redo);
}
