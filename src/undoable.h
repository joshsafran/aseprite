/* ASE - Allegro Sprite Editor
 * Copyright (C) 2001-2009  David Capello
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

#ifndef UNDOABLE_H
#define UNDOABLE_H

class Cel;
class Layer;
class Sprite;
class SpriteWriter;

/**
 * Class with high-level set of routines to modify a sprite.
 *
 * In this class, all modifications in the sprite have an undo
 * counterpart (if the sprite's undo is enabled).
 */
class Undoable
{
  Sprite* m_sprite;
  bool m_committed;
  bool m_enabled_flag;

public:
  Undoable(SpriteWriter& sprite, const char* label);
  virtual ~Undoable();

  inline Sprite* get_sprite() const { return m_sprite;  }
  inline bool is_enabled() const { return m_enabled_flag; }

  void commit();

  // for sprite
  void set_number_of_frames(int frames);
  void set_current_frame(int frame);
  void set_current_layer(Layer* layer);
  void set_sprite_size(int w, int h);
  void crop_sprite(int x, int y, int w, int h, int bgcolor);
  void autocrop_sprite(int bgcolor);
  void set_imgtype(int new_imgtype, int dithering_method);

  // for images in stock
  int add_image_in_stock(Image* image);
  void remove_image_from_stock(int image_index);
  void replace_stock_image(int image_index, Image* new_image);

  // for layers
  Layer* new_layer();
  void remove_layer(Layer* layer);
  void move_layer_after(Layer *layer, Layer *after_this);
  void crop_layer(Layer* layer, int x, int y, int w, int h, int bgcolor);
  void displace_layers(Layer* layer, int dx, int dy);
  void background_from_layer(Layer* layer, int bgcolor);
  void layer_from_background();
  void flatten_layers(int bgcolor);
private:
  void configure_layer_as_background(Layer* layer);

public:
  // for frames
  void new_frame();
  void new_frame_for_layer(Layer* layer, int frame);
  void remove_frame(int frame);
  void remove_frame_of_layer(Layer* layer, int frame);
  void copy_previous_frame(Layer* layer, int frame);
  void set_frame_duration(int frame, int msecs);
  void set_constant_frame_rate(int msecs);
  void move_frame_before(int frame, int before_frame);
  void move_frame_before_layer(Layer* layer, int frame, int before_frame);

  // for cels
  void add_cel(Layer* layer, Cel* cel);
  void remove_cel(Layer* layer, Cel* cel);
  void set_cel_frame_position(Cel* cel, int frame);
  void set_cel_position(Cel* cel, int x, int y);
  Cel* get_current_cel();
  void crop_cel(Cel* cel, int x, int y, int w, int h, int bgcolor);

  // for image
  Image* get_cel_image(Cel* cel);
  void clear_mask(int bgcolor);

  // for mask
  void copy_to_current_mask(Mask* mask);
  void set_mask_position(int x, int y);

};

#endif // UNDOABLE_H