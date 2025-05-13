#pragma region Main

#include "../../includes/kaboom_canvas_item.hpp"

#pragma region Construct and Destroy Functions

KABOOMCanvasItem::KABOOMCanvasItem() :
		xform_change(this) {
	canvas_item = RenderingServer::get_singleton()->canvas_item_create();
	GDPRINT("KABOOMCanvasItem got made");
}

KABOOMCanvasItem::~KABOOMCanvasItem() {
	ERR_FAIL_NULL(RenderingServer::get_singleton());
	RenderingServer::get_singleton()->free_rid(canvas_item);
	GDPRINT("KABOOMCanvasItem got destroyed");
}

#pragma endregion

#pragma region Class Functions

#pragma region Node Override Functions

void KABOOMCanvasItem::add_child(Node *p_node, bool p_force_readable_name, Node::InternalMode p_internal) {
#ifdef DEBUG_ENABLED
#endif
	ERR_FAIL_COND_MSG(_is_blocked(), "Parent node is busy setting up children, `add_child()` failed. Consider using `add_child.call_deferred(child)` instead.");

	Node::add_child(p_node, p_force_readable_name, p_internal);
}

void KABOOMCanvasItem::add_sibling(Node *p_sibling) {
	ERR_FAIL_COND_MSG(_is_blocked(), "Parent node is busy setting up children, `add_sibling()` failed. Consider using `add_sibling.call_deferred(sibling)` instead.");

	Node::add_sibling(p_sibling);
}

void KABOOMCanvasItem::remove_child(Node *p_node) {
	ERR_FAIL_COND_MSG(_is_blocked(), "Parent node is busy adding/removing children, `remove_child()` can't be called at this time. Consider using `remove_child.call_deferred(child)` instead.");

	Node::remove_child(p_node);
}

void KABOOMCanvasItem::move_child(Node *p_child_node, int p_to_index) {
	ERR_FAIL_COND_MSG(_is_blocked(), "Parent node is busy setting up children, `move_child()` failed. Consider using `move_child.call_deferred(child, index)` instead (or `popup.call_deferred()` if this is from a popup).");

	Node::move_child(p_child_node, p_to_index);
}

#pragma endregion

#pragma region Canvas Layer Functions

int KABOOMCanvasItem::get_canvas_layer() const {
	ERR_READ_THREAD_GUARD_V(0);
	if (canvas_layer) {
		return canvas_layer->get_layer();
	} else {
		return 0;
	}
}

CanvasLayer *KABOOMCanvasItem::get_canvas_layer_node() const {
	ERR_READ_THREAD_GUARD_V(nullptr);
	return canvas_layer;
}

#pragma endregion

#pragma region Visibility Functions

void KABOOMCanvasItem::show() {
	ERR_MAIN_THREAD_GUARD;
	set_visible(true);
}

void KABOOMCanvasItem::hide() {
	ERR_MAIN_THREAD_GUARD;
	set_visible(false);
}

void KABOOMCanvasItem::_propagate_visibility_changed(bool p_parent_visible_in_tree) {
	parent_visible_in_tree = p_parent_visible_in_tree;
	if (!visible) {
		return;
	}

	_handle_visibility_change(p_parent_visible_in_tree);
}

void KABOOMCanvasItem::_handle_visibility_change(bool p_visible) {
	RenderingServer::get_singleton()->canvas_item_set_visible(canvas_item, p_visible);
	notification(NOTIFICATION_VISIBILITY_CHANGED);

	if (p_visible) {
		queue_redraw();
	} else {
		emit_signal("hidden");
	}

	_block();
	for (int i = 0; i < get_child_count(); i++) {
		KABOOMCanvasItem *c = Object::cast_to<KABOOMCanvasItem>(get_child(i));

		if (c) { // Should the top_levels stop propagation? I think so, but...
			c->_propagate_visibility_changed(p_visible);
		}
	}
	_unblock();
}

void KABOOMCanvasItem::set_visible(bool p_visible) {
	ERR_MAIN_THREAD_GUARD;
	if (visible == p_visible) {
		return;
	}

	visible = p_visible;

	if (!parent_visible_in_tree) {
		notification(NOTIFICATION_VISIBILITY_CHANGED);
		return;
	}

	_handle_visibility_change(p_visible);
}

bool KABOOMCanvasItem::is_visible() const {
	ERR_READ_THREAD_GUARD_V(false);
	return visible;
}

bool KABOOMCanvasItem::is_visible_in_tree() const {
	ERR_READ_THREAD_GUARD_V(false);
	return visible && parent_visible_in_tree;
}

#pragma endregion

#pragma region Draw Functions

// void KABOOMCanvasItem::queue_redraw() {
// 	ERR_THREAD_GUARD
// 	if (!is_inside_tree()) {
// 		return;
// 	}
// 	if (pending_update) {
// 		return;
// 	}

// 	pending_update = true;

// 	callable_mp(this, &KABOOMCanvasItem::_redraw_callback).call_deferred();
// }
// void KABOOMCanvasItem::_draw() {}

// void KABOOMCanvasItem::_redraw_callback() {
// 	if (!is_inside_tree()) {
// 		pending_update = false;
// 		return;
// 	}

// 	RID ci = get_canvas_item();
// 	RenderingServer::get_singleton()->canvas_item_clear(ci);
// 	//todo updating = true - only allow drawing here
// 	if (is_visible_in_tree()) {
// 		drawing = true;
// 		Ref<TextServer> ts = TextServerManager::get_singleton()->get_primary_interface();
// 		if (ts.is_valid()) {
// 			ts->set_current_drawn_item_oversampling(get_viewport()->get_oversampling());
// 		}
// 		current_item_drawn = this;
// 		notification(NOTIFICATION_DRAW);
// 		emit_signal("draw");
// 		GDVIRTUAL_CALL("_draw");
// 		current_item_drawn = nullptr;
// 		if (ts.is_valid()) {
// 			ts->set_current_drawn_item_oversampling(0.0);
// 		}
// 		drawing = false;
// 	}
// 	//todo updating = false
// 	pending_update = false; // don't change to false until finished drawing (avoid recursive update)
// }

#pragma endregion

#pragma endregion

#pragma region Godot Bindings

void KABOOMCanvasItem::_bind_methods() {
	// ClassDB::bind_method(D_METHOD("_top_level_raise_self"), &KABOOMCanvasItem::_top_level_raise_self);

	// #ifdef TOOLS_ENABLED
	// 	ClassDB::bind_method(D_METHOD("_edit_set_state", "state"), &KABOOMCanvasItem::_edit_set_state);
	// 	ClassDB::bind_method(D_METHOD("_edit_get_state"), &KABOOMCanvasItem::_edit_get_state);
	// 	ClassDB::bind_method(D_METHOD("_edit_set_position", "position"), &KABOOMCanvasItem::_edit_set_position);
	// 	ClassDB::bind_method(D_METHOD("_edit_get_position"), &KABOOMCanvasItem::_edit_get_position);
	// 	ClassDB::bind_method(D_METHOD("_edit_set_scale", "scale"), &KABOOMCanvasItem::_edit_set_scale);
	// 	ClassDB::bind_method(D_METHOD("_edit_get_scale"), &KABOOMCanvasItem::_edit_get_scale);
	// 	ClassDB::bind_method(D_METHOD("_edit_set_rect", "rect"), &KABOOMCanvasItem::_edit_set_rect);
	// 	ClassDB::bind_method(D_METHOD("_edit_get_rect"), &KABOOMCanvasItem::_edit_get_rect);
	// 	ClassDB::bind_method(D_METHOD("_edit_use_rect"), &KABOOMCanvasItem::_edit_use_rect);
	// 	ClassDB::bind_method(D_METHOD("_edit_set_rotation", "degrees"), &KABOOMCanvasItem::_edit_set_rotation);
	// 	ClassDB::bind_method(D_METHOD("_edit_get_rotation"), &KABOOMCanvasItem::_edit_get_rotation);
	// 	ClassDB::bind_method(D_METHOD("_edit_use_rotation"), &KABOOMCanvasItem::_edit_use_rotation);
	// 	ClassDB::bind_method(D_METHOD("_edit_set_pivot", "pivot"), &KABOOMCanvasItem::_edit_set_pivot);
	// 	ClassDB::bind_method(D_METHOD("_edit_get_pivot"), &KABOOMCanvasItem::_edit_get_pivot);
	// 	ClassDB::bind_method(D_METHOD("_edit_use_pivot"), &KABOOMCanvasItem::_edit_use_pivot);
	// 	ClassDB::bind_method(D_METHOD("_edit_get_transform"), &KABOOMCanvasItem::_edit_get_transform);
	// #endif //TOOLS_ENABLED

	ClassDB::bind_method(D_METHOD("get_canvas_item"), &KABOOMCanvasItem::get_canvas_item);

	// ClassDB::bind_method(D_METHOD("set_visible", "visible"), &KABOOMCanvasItem::set_visible);
	// ClassDB::bind_method(D_METHOD("is_visible"), &KABOOMCanvasItem::is_visible);
	// ClassDB::bind_method(D_METHOD("is_visible_in_tree"), &KABOOMCanvasItem::is_visible_in_tree);
	// ClassDB::bind_method(D_METHOD("show"), &KABOOMCanvasItem::show);
	// ClassDB::bind_method(D_METHOD("hide"), &KABOOMCanvasItem::hide);

	// ClassDB::bind_method(D_METHOD("queue_redraw"), &KABOOMCanvasItem::queue_redraw);
	// ClassDB::bind_method(D_METHOD("move_to_front"), &KABOOMCanvasItem::move_to_front);

	// ClassDB::bind_method(D_METHOD("set_as_top_level", "enable"), &KABOOMCanvasItem::set_as_top_level);
	// ClassDB::bind_method(D_METHOD("is_set_as_top_level"), &KABOOMCanvasItem::is_set_as_top_level);

	// ClassDB::bind_method(D_METHOD("set_light_mask", "light_mask"), &KABOOMCanvasItem::set_light_mask);
	// ClassDB::bind_method(D_METHOD("get_light_mask"), &KABOOMCanvasItem::get_light_mask);

	// ClassDB::bind_method(D_METHOD("set_modulate", "modulate"), &KABOOMCanvasItem::set_modulate);
	// ClassDB::bind_method(D_METHOD("get_modulate"), &KABOOMCanvasItem::get_modulate);

	// ClassDB::bind_method(D_METHOD("set_self_modulate", "self_modulate"), &KABOOMCanvasItem::set_self_modulate);
	// ClassDB::bind_method(D_METHOD("get_self_modulate"), &KABOOMCanvasItem::get_self_modulate);

	// ClassDB::bind_method(D_METHOD("set_z_index", "z_index"), &KABOOMCanvasItem::set_z_index);
	// ClassDB::bind_method(D_METHOD("get_z_index"), &KABOOMCanvasItem::get_z_index);

	// ClassDB::bind_method(D_METHOD("set_z_as_relative", "enable"), &KABOOMCanvasItem::set_z_as_relative);
	// ClassDB::bind_method(D_METHOD("is_z_relative"), &KABOOMCanvasItem::is_z_relative);

	// ClassDB::bind_method(D_METHOD("set_y_sort_enabled", "enabled"), &KABOOMCanvasItem::set_y_sort_enabled);
	// ClassDB::bind_method(D_METHOD("is_y_sort_enabled"), &KABOOMCanvasItem::is_y_sort_enabled);

	// ClassDB::bind_method(D_METHOD("set_draw_behind_parent", "enable"), &KABOOMCanvasItem::set_draw_behind_parent);
	// ClassDB::bind_method(D_METHOD("is_draw_behind_parent_enabled"), &KABOOMCanvasItem::is_draw_behind_parent_enabled);

	// ClassDB::bind_method(D_METHOD("draw_line", "from", "to", "color", "width", "antialiased"), &KABOOMCanvasItem::draw_line, DEFVAL(-1.0), DEFVAL(false));
	// ClassDB::bind_method(D_METHOD("draw_dashed_line", "from", "to", "color", "width", "dash", "aligned", "antialiased"), &KABOOMCanvasItem::draw_dashed_line, DEFVAL(-1.0), DEFVAL(2.0), DEFVAL(true), DEFVAL(false));
	// ClassDB::bind_method(D_METHOD("draw_polyline", "points", "color", "width", "antialiased"), &KABOOMCanvasItem::draw_polyline, DEFVAL(-1.0), DEFVAL(false));
	// ClassDB::bind_method(D_METHOD("draw_polyline_colors", "points", "colors", "width", "antialiased"), &KABOOMCanvasItem::draw_polyline_colors, DEFVAL(-1.0), DEFVAL(false));
	// ClassDB::bind_method(D_METHOD("draw_arc", "center", "radius", "start_angle", "end_angle", "point_count", "color", "width", "antialiased"), &KABOOMCanvasItem::draw_arc, DEFVAL(-1.0), DEFVAL(false));
	// ClassDB::bind_method(D_METHOD("draw_multiline", "points", "color", "width", "antialiased"), &KABOOMCanvasItem::draw_multiline, DEFVAL(-1.0), DEFVAL(false));
	// ClassDB::bind_method(D_METHOD("draw_multiline_colors", "points", "colors", "width", "antialiased"), &KABOOMCanvasItem::draw_multiline_colors, DEFVAL(-1.0), DEFVAL(false));
	// ClassDB::bind_method(D_METHOD("draw_rect", "rect", "color", "filled", "width", "antialiased"), &KABOOMCanvasItem::draw_rect, DEFVAL(true), DEFVAL(-1.0), DEFVAL(false));
	// ClassDB::bind_method(D_METHOD("draw_circle", "position", "radius", "color", "filled", "width", "antialiased"), &KABOOMCanvasItem::draw_circle, DEFVAL(true), DEFVAL(-1.0), DEFVAL(false));
	// ClassDB::bind_method(D_METHOD("draw_texture", "texture", "position", "modulate"), &KABOOMCanvasItem::draw_texture, DEFVAL(Color(1, 1, 1, 1)));
	// ClassDB::bind_method(D_METHOD("draw_texture_rect", "texture", "rect", "tile", "modulate", "transpose"), &KABOOMCanvasItem::draw_texture_rect, DEFVAL(Color(1, 1, 1, 1)), DEFVAL(false));
	// ClassDB::bind_method(D_METHOD("draw_texture_rect_region", "texture", "rect", "src_rect", "modulate", "transpose", "clip_uv"), &KABOOMCanvasItem::draw_texture_rect_region, DEFVAL(Color(1, 1, 1, 1)), DEFVAL(false), DEFVAL(true));
	// ClassDB::bind_method(D_METHOD("draw_msdf_texture_rect_region", "texture", "rect", "src_rect", "modulate", "outline", "pixel_range", "scale"), &KABOOMCanvasItem::draw_msdf_texture_rect_region, DEFVAL(Color(1, 1, 1, 1)), DEFVAL(0.0), DEFVAL(4.0), DEFVAL(1.0));
	// ClassDB::bind_method(D_METHOD("draw_lcd_texture_rect_region", "texture", "rect", "src_rect", "modulate"), &KABOOMCanvasItem::draw_lcd_texture_rect_region, DEFVAL(Color(1, 1, 1, 1)));
	// ClassDB::bind_method(D_METHOD("draw_style_box", "style_box", "rect"), &KABOOMCanvasItem::draw_style_box);
	// ClassDB::bind_method(D_METHOD("draw_primitive", "points", "colors", "uvs", "texture"), &KABOOMCanvasItem::draw_primitive, DEFVAL(Ref<Texture2D>()));
	// ClassDB::bind_method(D_METHOD("draw_polygon", "points", "colors", "uvs", "texture"), &KABOOMCanvasItem::draw_polygon, DEFVAL(PackedVector2Array()), DEFVAL(Ref<Texture2D>()));
	// ClassDB::bind_method(D_METHOD("draw_colored_polygon", "points", "color", "uvs", "texture"), &KABOOMCanvasItem::draw_colored_polygon, DEFVAL(PackedVector2Array()), DEFVAL(Ref<Texture2D>()));
	// ClassDB::bind_method(D_METHOD("draw_string", "font", "pos", "text", "alignment", "width", "font_size", "modulate", "justification_flags", "direction", "orientation", "oversampling"), &KABOOMCanvasItem::draw_string, DEFVAL(HORIZONTAL_ALIGNMENT_LEFT), DEFVAL(-1), DEFVAL(DEFAULT_FONT_SIZE), DEFVAL(Color(1.0, 1.0, 1.0)), DEFVAL(TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND), DEFVAL(TextServer::DIRECTION_AUTO), DEFVAL(TextServer::ORIENTATION_HORIZONTAL), DEFVAL(0.0));
	// ClassDB::bind_method(D_METHOD("draw_multiline_string", "font", "pos", "text", "alignment", "width", "font_size", "max_lines", "modulate", "brk_flags", "justification_flags", "direction", "orientation", "oversampling"), &KABOOMCanvasItem::draw_multiline_string, DEFVAL(HORIZONTAL_ALIGNMENT_LEFT), DEFVAL(-1), DEFVAL(DEFAULT_FONT_SIZE), DEFVAL(-1), DEFVAL(Color(1.0, 1.0, 1.0)), DEFVAL(TextServer::BREAK_MANDATORY | TextServer::BREAK_WORD_BOUND), DEFVAL(TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND), DEFVAL(TextServer::DIRECTION_AUTO), DEFVAL(TextServer::ORIENTATION_HORIZONTAL), DEFVAL(0.0));
	// ClassDB::bind_method(D_METHOD("draw_string_outline", "font", "pos", "text", "alignment", "width", "font_size", "size", "modulate", "justification_flags", "direction", "orientation", "oversampling"), &KABOOMCanvasItem::draw_string_outline, DEFVAL(HORIZONTAL_ALIGNMENT_LEFT), DEFVAL(-1), DEFVAL(DEFAULT_FONT_SIZE), DEFVAL(1), DEFVAL(Color(1.0, 1.0, 1.0)), DEFVAL(TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND), DEFVAL(TextServer::DIRECTION_AUTO), DEFVAL(TextServer::ORIENTATION_HORIZONTAL), DEFVAL(0.0));
	// ClassDB::bind_method(D_METHOD("draw_multiline_string_outline", "font", "pos", "text", "alignment", "width", "font_size", "max_lines", "size", "modulate", "brk_flags", "justification_flags", "direction", "orientation", "oversampling"), &KABOOMCanvasItem::draw_multiline_string_outline, DEFVAL(HORIZONTAL_ALIGNMENT_LEFT), DEFVAL(-1), DEFVAL(DEFAULT_FONT_SIZE), DEFVAL(-1), DEFVAL(1), DEFVAL(Color(1.0, 1.0, 1.0)), DEFVAL(TextServer::BREAK_MANDATORY | TextServer::BREAK_WORD_BOUND), DEFVAL(TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND), DEFVAL(TextServer::DIRECTION_AUTO), DEFVAL(TextServer::ORIENTATION_HORIZONTAL), DEFVAL(0.0));
	// ClassDB::bind_method(D_METHOD("draw_char", "font", "pos", "char", "font_size", "modulate", "oversampling"), &KABOOMCanvasItem::draw_char, DEFVAL(DEFAULT_FONT_SIZE), DEFVAL(Color(1.0, 1.0, 1.0)), DEFVAL(0.0));
	// ClassDB::bind_method(D_METHOD("draw_char_outline", "font", "pos", "char", "font_size", "size", "modulate", "oversampling"), &KABOOMCanvasItem::draw_char_outline, DEFVAL(DEFAULT_FONT_SIZE), DEFVAL(-1), DEFVAL(Color(1.0, 1.0, 1.0)), DEFVAL(0.0));
	// ClassDB::bind_method(D_METHOD("draw_mesh", "mesh", "texture", "transform", "modulate"), &KABOOMCanvasItem::draw_mesh, DEFVAL(Transform2D()), DEFVAL(Color(1, 1, 1, 1)));
	// ClassDB::bind_method(D_METHOD("draw_multimesh", "multimesh", "texture"), &KABOOMCanvasItem::draw_multimesh);
	// ClassDB::bind_method(D_METHOD("draw_set_transform", "position", "rotation", "scale"), &KABOOMCanvasItem::draw_set_transform, DEFVAL(0.0), DEFVAL(Size2(1.0, 1.0)));
	// ClassDB::bind_method(D_METHOD("draw_set_transform_matrix", "xform"), &KABOOMCanvasItem::draw_set_transform_matrix);
	// ClassDB::bind_method(D_METHOD("draw_animation_slice", "animation_length", "slice_begin", "slice_end", "offset"), &KABOOMCanvasItem::draw_animation_slice, DEFVAL(0.0));
	// ClassDB::bind_method(D_METHOD("draw_end_animation"), &KABOOMCanvasItem::draw_end_animation);
	// ClassDB::bind_method(D_METHOD("get_transform"), &KABOOMCanvasItem::get_transform);
	// ClassDB::bind_method(D_METHOD("get_global_transform"), &KABOOMCanvasItem::get_global_transform);
	// ClassDB::bind_method(D_METHOD("get_global_transform_with_canvas"), &KABOOMCanvasItem::get_global_transform_with_canvas);
	// ClassDB::bind_method(D_METHOD("get_viewport_transform"), &KABOOMCanvasItem::get_viewport_transform);
	// ClassDB::bind_method(D_METHOD("get_viewport_rect"), &KABOOMCanvasItem::get_viewport_rect);
	// ClassDB::bind_method(D_METHOD("get_canvas_transform"), &KABOOMCanvasItem::get_canvas_transform);
	// ClassDB::bind_method(D_METHOD("get_screen_transform"), &KABOOMCanvasItem::get_screen_transform);
	// ClassDB::bind_method(D_METHOD("get_local_mouse_position"), &KABOOMCanvasItem::get_local_mouse_position);
	// ClassDB::bind_method(D_METHOD("get_global_mouse_position"), &KABOOMCanvasItem::get_global_mouse_position);
	// ClassDB::bind_method(D_METHOD("get_canvas"), &KABOOMCanvasItem::get_canvas);
	// ClassDB::bind_method(D_METHOD("get_canvas_layer_node"), &KABOOMCanvasItem::get_canvas_layer_node);
	// ClassDB::bind_method(D_METHOD("get_world_2d"), &KABOOMCanvasItem::get_world_2d);
	// //ClassDB::bind_method(D_METHOD("get_viewport"),&KABOOMCanvasItem::get_viewport);

	// ClassDB::bind_method(D_METHOD("set_material", "material"), &KABOOMCanvasItem::set_material);
	// ClassDB::bind_method(D_METHOD("get_material"), &KABOOMCanvasItem::get_material);

	// ClassDB::bind_method(D_METHOD("set_instance_shader_parameter", "name", "value"), &KABOOMCanvasItem::set_instance_shader_parameter);
	// ClassDB::bind_method(D_METHOD("get_instance_shader_parameter", "name"), &KABOOMCanvasItem::get_instance_shader_parameter);

	// ClassDB::bind_method(D_METHOD("set_use_parent_material", "enable"), &KABOOMCanvasItem::set_use_parent_material);
	// ClassDB::bind_method(D_METHOD("get_use_parent_material"), &KABOOMCanvasItem::get_use_parent_material);

	// ClassDB::bind_method(D_METHOD("set_notify_local_transform", "enable"), &KABOOMCanvasItem::set_notify_local_transform);
	// ClassDB::bind_method(D_METHOD("is_local_transform_notification_enabled"), &KABOOMCanvasItem::is_local_transform_notification_enabled);

	// ClassDB::bind_method(D_METHOD("set_notify_transform", "enable"), &KABOOMCanvasItem::set_notify_transform);
	// ClassDB::bind_method(D_METHOD("is_transform_notification_enabled"), &KABOOMCanvasItem::is_transform_notification_enabled);

	// ClassDB::bind_method(D_METHOD("force_update_transform"), &KABOOMCanvasItem::force_update_transform);

	// ClassDB::bind_method(D_METHOD("make_canvas_position_local", "viewport_point"), &KABOOMCanvasItem::make_canvas_position_local);
	// ClassDB::bind_method(D_METHOD("make_input_local", "event"), &KABOOMCanvasItem::make_input_local);

	// ClassDB::bind_method(D_METHOD("set_visibility_layer", "layer"), &KABOOMCanvasItem::set_visibility_layer);
	// ClassDB::bind_method(D_METHOD("get_visibility_layer"), &KABOOMCanvasItem::get_visibility_layer);
	// ClassDB::bind_method(D_METHOD("set_visibility_layer_bit", "layer", "enabled"), &KABOOMCanvasItem::set_visibility_layer_bit);
	// ClassDB::bind_method(D_METHOD("get_visibility_layer_bit", "layer"), &KABOOMCanvasItem::get_visibility_layer_bit);

	// ClassDB::bind_method(D_METHOD("set_texture_filter", "mode"), &KABOOMCanvasItem::set_texture_filter);
	// ClassDB::bind_method(D_METHOD("get_texture_filter"), &KABOOMCanvasItem::get_texture_filter);

	// ClassDB::bind_method(D_METHOD("set_texture_repeat", "mode"), &KABOOMCanvasItem::set_texture_repeat);
	// ClassDB::bind_method(D_METHOD("get_texture_repeat"), &KABOOMCanvasItem::get_texture_repeat);

	// ClassDB::bind_method(D_METHOD("set_clip_children_mode", "mode"), &KABOOMCanvasItem::set_clip_children_mode);
	// ClassDB::bind_method(D_METHOD("get_clip_children_mode"), &KABOOMCanvasItem::get_clip_children_mode);

	// GDVIRTUAL_BIND("_draw");

	// ADD_GROUP("Visibility", "");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "visible"), "set_visible", "is_visible");
	// ADD_PROPERTY(PropertyInfo(Variant::COLOR, "modulate"), "set_modulate", "get_modulate");
	// ADD_PROPERTY(PropertyInfo(Variant::COLOR, "self_modulate"), "set_self_modulate", "get_self_modulate");
	// ADD_PROPERTY(PropertyInfo(Variant::BOOL, "show_behind_parent"), "set_draw_behind_parent", "is_draw_behind_parent_enabled");
	// ADD_PROPERTY(PropertyInfo(Variant::BOOL, "top_level"), "set_as_top_level", "is_set_as_top_level");
	// ADD_PROPERTY(PropertyInfo(Variant::INT, "clip_children", PROPERTY_HINT_ENUM, "Disabled,Clip Only,Clip + Draw"), "set_clip_children_mode", "get_clip_children_mode");
	// ADD_PROPERTY(PropertyInfo(Variant::INT, "light_mask", PROPERTY_HINT_LAYERS_2D_RENDER), "set_light_mask", "get_light_mask");
	// ADD_PROPERTY(PropertyInfo(Variant::INT, "visibility_layer", PROPERTY_HINT_LAYERS_2D_RENDER), "set_visibility_layer", "get_visibility_layer");

	// ADD_GROUP("Ordering", "");
	// ADD_PROPERTY(PropertyInfo(Variant::INT, "z_index", PROPERTY_HINT_RANGE, itos(RenderingServer::CANVAS_ITEM_Z_MIN) + "," + itos(RenderingServer::CANVAS_ITEM_Z_MAX) + ",1"), "set_z_index", "get_z_index");
	// ADD_PROPERTY(PropertyInfo(Variant::BOOL, "z_as_relative"), "set_z_as_relative", "is_z_relative");
	// ADD_PROPERTY(PropertyInfo(Variant::BOOL, "y_sort_enabled"), "set_y_sort_enabled", "is_y_sort_enabled");

	// ADD_GROUP("Texture", "texture_");
	// ADD_PROPERTY(PropertyInfo(Variant::INT, "texture_filter", PROPERTY_HINT_ENUM, "Inherit,Nearest,Linear,Nearest Mipmap,Linear Mipmap,Nearest Mipmap Anisotropic,Linear Mipmap Anisotropic"), "set_texture_filter", "get_texture_filter");
	// ADD_PROPERTY(PropertyInfo(Variant::INT, "texture_repeat", PROPERTY_HINT_ENUM, "Inherit,Disabled,Enabled,Mirror"), "set_texture_repeat", "get_texture_repeat");

	// ADD_GROUP("Material", "");
	// ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "material", PROPERTY_HINT_RESOURCE_TYPE, "CanvasItemMaterial,ShaderMaterial"), "set_material", "get_material");
	// ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_parent_material"), "set_use_parent_material", "get_use_parent_material");
	// // ADD_PROPERTY(PropertyInfo(Variant::BOOL,"transform/notify"),"set_transform_notify","is_transform_notify_enabled");

	// ADD_SIGNAL(MethodInfo("draw"));
	// ADD_SIGNAL(MethodInfo("visibility_changed"));
	// ADD_SIGNAL(MethodInfo("hidden"));
	// ADD_SIGNAL(MethodInfo("item_rect_changed"));

	BIND_CONSTANT(NOTIFICATION_TRANSFORM_CHANGED);
	BIND_CONSTANT(NOTIFICATION_LOCAL_TRANSFORM_CHANGED);
	BIND_CONSTANT(NOTIFICATION_DRAW);
	BIND_CONSTANT(NOTIFICATION_VISIBILITY_CHANGED);
	BIND_CONSTANT(NOTIFICATION_ENTER_CANVAS);
	BIND_CONSTANT(NOTIFICATION_EXIT_CANVAS);
	BIND_CONSTANT(NOTIFICATION_WORLD_2D_CHANGED);

	BIND_ENUM_CONSTANT(TEXTURE_FILTER_PARENT_NODE);
	BIND_ENUM_CONSTANT(TEXTURE_FILTER_NEAREST);
	BIND_ENUM_CONSTANT(TEXTURE_FILTER_LINEAR);
	BIND_ENUM_CONSTANT(TEXTURE_FILTER_NEAREST_WITH_MIPMAPS);
	BIND_ENUM_CONSTANT(TEXTURE_FILTER_LINEAR_WITH_MIPMAPS);
	BIND_ENUM_CONSTANT(TEXTURE_FILTER_NEAREST_WITH_MIPMAPS_ANISOTROPIC);
	BIND_ENUM_CONSTANT(TEXTURE_FILTER_LINEAR_WITH_MIPMAPS_ANISOTROPIC);
	BIND_ENUM_CONSTANT(TEXTURE_FILTER_MAX);

	BIND_ENUM_CONSTANT(TEXTURE_REPEAT_PARENT_NODE);
	BIND_ENUM_CONSTANT(TEXTURE_REPEAT_DISABLED);
	BIND_ENUM_CONSTANT(TEXTURE_REPEAT_ENABLED);
	BIND_ENUM_CONSTANT(TEXTURE_REPEAT_MIRROR);
	BIND_ENUM_CONSTANT(TEXTURE_REPEAT_MAX);

	BIND_ENUM_CONSTANT(CLIP_CHILDREN_DISABLED);
	BIND_ENUM_CONSTANT(CLIP_CHILDREN_ONLY);
	BIND_ENUM_CONSTANT(CLIP_CHILDREN_AND_DRAW);
	BIND_ENUM_CONSTANT(CLIP_CHILDREN_MAX);
}

#pragma endregion

#pragma endregion