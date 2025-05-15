#pragma region Main

#include "../../includes/kaboom_canvas_item.hpp"

/**
 * "Run-time TRanslate". Performs string replacement for internationalization
 * without the editor. A translation context can optionally be specified to
 * disambiguate between identical source strings in translations. When
 * placeholders are desired, use `vformat(RTR("Example: %s"), some_string)`.
 * If a string mentions a quantity (and may therefore need a dynamic plural form),
 * use `RTRN()` instead of `RTR()`.
 *
 * NOTE: Do not use `RTR()` in editor-only code (typically within the `editor/`
 * folder). For editor translations, use `TTR()` instead.
 */
String RTR(const String &p_text, const String &p_context = "") {
	TranslationServer *ts = TranslationServer::get_singleton();
	if (ts) {
		// String translated = ts->tool_translate(p_text, p_context);
		// if (translated.is_empty() || translated == p_text) {
		return ts->translate(p_text, p_context);
		// }
		// return translated;
	}

	return p_text;
}

#pragma region Godot Bindings

void KABOOMCanvasItem::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_top_level_raise_self"), &KABOOMCanvasItem::_top_level_raise_self);

#ifdef TOOLS_ENABLED
	ClassDB::bind_method(D_METHOD("_edit_set_state", "state"), &KABOOMCanvasItem::_edit_set_state);
	ClassDB::bind_method(D_METHOD("_edit_get_state"), &KABOOMCanvasItem::_edit_get_state);
	ClassDB::bind_method(D_METHOD("_edit_set_position", "position"), &KABOOMCanvasItem::_edit_set_position);
	ClassDB::bind_method(D_METHOD("_edit_get_position"), &KABOOMCanvasItem::_edit_get_position);
	ClassDB::bind_method(D_METHOD("_edit_set_scale", "scale"), &KABOOMCanvasItem::_edit_set_scale);
	ClassDB::bind_method(D_METHOD("_edit_get_scale"), &KABOOMCanvasItem::_edit_get_scale);
	ClassDB::bind_method(D_METHOD("_edit_set_rect", "rect"), &KABOOMCanvasItem::_edit_set_rect);
	ClassDB::bind_method(D_METHOD("_edit_get_rect"), &KABOOMCanvasItem::_edit_get_rect);
	ClassDB::bind_method(D_METHOD("_edit_use_rect"), &KABOOMCanvasItem::_edit_use_rect);
	ClassDB::bind_method(D_METHOD("_edit_set_rotation", "degrees"), &KABOOMCanvasItem::_edit_set_rotation);
	ClassDB::bind_method(D_METHOD("_edit_get_rotation"), &KABOOMCanvasItem::_edit_get_rotation);
	ClassDB::bind_method(D_METHOD("_edit_use_rotation"), &KABOOMCanvasItem::_edit_use_rotation);
	ClassDB::bind_method(D_METHOD("_edit_set_pivot", "pivot"), &KABOOMCanvasItem::_edit_set_pivot);
	ClassDB::bind_method(D_METHOD("_edit_get_pivot"), &KABOOMCanvasItem::_edit_get_pivot);
	ClassDB::bind_method(D_METHOD("_edit_use_pivot"), &KABOOMCanvasItem::_edit_use_pivot);
	ClassDB::bind_method(D_METHOD("_edit_get_transform"), &KABOOMCanvasItem::_edit_get_transform);
#endif //TOOLS_ENABLED

	ClassDB::bind_method(D_METHOD("get_canvas_item"), &KABOOMCanvasItem::get_canvas_item);

	ClassDB::bind_method(D_METHOD("set_visible", "visible"), &KABOOMCanvasItem::set_visible);
	ClassDB::bind_method(D_METHOD("is_visible"), &KABOOMCanvasItem::is_visible);
	ClassDB::bind_method(D_METHOD("is_visible_in_tree"), &KABOOMCanvasItem::is_visible_in_tree);
	ClassDB::bind_method(D_METHOD("show"), &KABOOMCanvasItem::show);
	ClassDB::bind_method(D_METHOD("hide"), &KABOOMCanvasItem::hide);

	ClassDB::bind_method(D_METHOD("queue_redraw"), &KABOOMCanvasItem::queue_redraw);
	ClassDB::bind_method(D_METHOD("move_to_front"), &KABOOMCanvasItem::move_to_front);

	ClassDB::bind_method(D_METHOD("set_as_top_level", "enable"), &KABOOMCanvasItem::set_as_top_level);
	ClassDB::bind_method(D_METHOD("is_set_as_top_level"), &KABOOMCanvasItem::is_set_as_top_level);

	ClassDB::bind_method(D_METHOD("set_light_mask", "light_mask"), &KABOOMCanvasItem::set_light_mask);
	ClassDB::bind_method(D_METHOD("get_light_mask"), &KABOOMCanvasItem::get_light_mask);

	ClassDB::bind_method(D_METHOD("set_modulate", "modulate"), &KABOOMCanvasItem::set_modulate);
	ClassDB::bind_method(D_METHOD("get_modulate"), &KABOOMCanvasItem::get_modulate);

	ClassDB::bind_method(D_METHOD("set_self_modulate", "self_modulate"), &KABOOMCanvasItem::set_self_modulate);
	ClassDB::bind_method(D_METHOD("get_self_modulate"), &KABOOMCanvasItem::get_self_modulate);

	ClassDB::bind_method(D_METHOD("set_z_index", "z_index"), &KABOOMCanvasItem::set_z_index);
	ClassDB::bind_method(D_METHOD("get_z_index"), &KABOOMCanvasItem::get_z_index);

	ClassDB::bind_method(D_METHOD("set_z_as_relative", "enable"), &KABOOMCanvasItem::set_z_as_relative);
	ClassDB::bind_method(D_METHOD("is_z_relative"), &KABOOMCanvasItem::is_z_relative);

	ClassDB::bind_method(D_METHOD("set_y_sort_enabled", "enabled"), &KABOOMCanvasItem::set_y_sort_enabled);
	ClassDB::bind_method(D_METHOD("is_y_sort_enabled"), &KABOOMCanvasItem::is_y_sort_enabled);

	ClassDB::bind_method(D_METHOD("set_draw_behind_parent", "enable"), &KABOOMCanvasItem::set_draw_behind_parent);
	ClassDB::bind_method(D_METHOD("is_draw_behind_parent_enabled"), &KABOOMCanvasItem::is_draw_behind_parent_enabled);

	ClassDB::bind_method(D_METHOD("draw_line", "from", "to", "color", "width", "antialiased"), &KABOOMCanvasItem::draw_line, DEFVAL(-1.0), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("draw_dashed_line", "from", "to", "color", "width", "dash", "aligned", "antialiased"), &KABOOMCanvasItem::draw_dashed_line, DEFVAL(-1.0), DEFVAL(2.0), DEFVAL(true), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("draw_polyline", "points", "color", "width", "antialiased"), &KABOOMCanvasItem::draw_polyline, DEFVAL(-1.0), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("draw_polyline_colors", "points", "colors", "width", "antialiased"), &KABOOMCanvasItem::draw_polyline_colors, DEFVAL(-1.0), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("draw_arc", "center", "radius", "start_angle", "end_angle", "point_count", "color", "width", "antialiased"), &KABOOMCanvasItem::draw_arc, DEFVAL(-1.0), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("draw_multiline", "points", "color", "width", "antialiased"), &KABOOMCanvasItem::draw_multiline, DEFVAL(-1.0), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("draw_multiline_colors", "points", "colors", "width", "antialiased"), &KABOOMCanvasItem::draw_multiline_colors, DEFVAL(-1.0), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("draw_rect", "rect", "color", "filled", "width", "antialiased"), &KABOOMCanvasItem::draw_rect, DEFVAL(true), DEFVAL(-1.0), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("draw_circle", "position", "radius", "color", "filled", "width", "antialiased"), &KABOOMCanvasItem::draw_circle, DEFVAL(true), DEFVAL(-1.0), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("draw_texture", "texture", "position", "modulate"), &KABOOMCanvasItem::draw_texture, DEFVAL(Color(1, 1, 1, 1)));
	ClassDB::bind_method(D_METHOD("draw_texture_rect", "texture", "rect", "tile", "modulate", "transpose"), &KABOOMCanvasItem::draw_texture_rect, DEFVAL(Color(1, 1, 1, 1)), DEFVAL(false));
	ClassDB::bind_method(D_METHOD("draw_texture_rect_region", "texture", "rect", "src_rect", "modulate", "transpose", "clip_uv"), &KABOOMCanvasItem::draw_texture_rect_region, DEFVAL(Color(1, 1, 1, 1)), DEFVAL(false), DEFVAL(true));
	ClassDB::bind_method(D_METHOD("draw_msdf_texture_rect_region", "texture", "rect", "src_rect", "modulate", "outline", "pixel_range", "scale"), &KABOOMCanvasItem::draw_msdf_texture_rect_region, DEFVAL(Color(1, 1, 1, 1)), DEFVAL(0.0), DEFVAL(4.0), DEFVAL(1.0));
	ClassDB::bind_method(D_METHOD("draw_lcd_texture_rect_region", "texture", "rect", "src_rect", "modulate"), &KABOOMCanvasItem::draw_lcd_texture_rect_region, DEFVAL(Color(1, 1, 1, 1)));
	ClassDB::bind_method(D_METHOD("draw_style_box", "style_box", "rect"), &KABOOMCanvasItem::draw_style_box);
	ClassDB::bind_method(D_METHOD("draw_primitive", "points", "colors", "uvs", "texture"), &KABOOMCanvasItem::draw_primitive, DEFVAL(Ref<Texture2D>()));
	ClassDB::bind_method(D_METHOD("draw_polygon", "points", "colors", "uvs", "texture"), &KABOOMCanvasItem::draw_polygon, DEFVAL(PackedVector2Array()), DEFVAL(Ref<Texture2D>()));
	ClassDB::bind_method(D_METHOD("draw_colored_polygon", "points", "color", "uvs", "texture"), &KABOOMCanvasItem::draw_colored_polygon, DEFVAL(PackedVector2Array()), DEFVAL(Ref<Texture2D>()));
	ClassDB::bind_method(D_METHOD("draw_string", "font", "pos", "text", "alignment", "width", "font_size", "modulate", "justification_flags", "direction", "orientation", "oversampling"), &KABOOMCanvasItem::draw_string, DEFVAL(HORIZONTAL_ALIGNMENT_LEFT), DEFVAL(-1), DEFVAL(KABOOMCanvasItem::DEFAULT_FONT_SIZE), DEFVAL(Color(1.0, 1.0, 1.0)), DEFVAL(TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND), DEFVAL(TextServer::DIRECTION_AUTO), DEFVAL(TextServer::ORIENTATION_HORIZONTAL), DEFVAL(0.0));
	ClassDB::bind_method(D_METHOD("draw_multiline_string", "font", "pos", "text", "alignment", "width", "font_size", "max_lines", "modulate", "brk_flags", "justification_flags", "direction", "orientation", "oversampling"), &KABOOMCanvasItem::draw_multiline_string, DEFVAL(HORIZONTAL_ALIGNMENT_LEFT), DEFVAL(-1), DEFVAL(KABOOMCanvasItem::DEFAULT_FONT_SIZE), DEFVAL(-1), DEFVAL(Color(1.0, 1.0, 1.0)), DEFVAL(TextServer::BREAK_MANDATORY | TextServer::BREAK_WORD_BOUND), DEFVAL(TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND), DEFVAL(TextServer::DIRECTION_AUTO), DEFVAL(TextServer::ORIENTATION_HORIZONTAL), DEFVAL(0.0));
	ClassDB::bind_method(D_METHOD("draw_string_outline", "font", "pos", "text", "alignment", "width", "font_size", "size", "modulate", "justification_flags", "direction", "orientation", "oversampling"), &KABOOMCanvasItem::draw_string_outline, DEFVAL(HORIZONTAL_ALIGNMENT_LEFT), DEFVAL(-1), DEFVAL(KABOOMCanvasItem::DEFAULT_FONT_SIZE), DEFVAL(1), DEFVAL(Color(1.0, 1.0, 1.0)), DEFVAL(TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND), DEFVAL(TextServer::DIRECTION_AUTO), DEFVAL(TextServer::ORIENTATION_HORIZONTAL), DEFVAL(0.0));
	ClassDB::bind_method(D_METHOD("draw_multiline_string_outline", "font", "pos", "text", "alignment", "width", "font_size", "max_lines", "size", "modulate", "brk_flags", "justification_flags", "direction", "orientation", "oversampling"), &KABOOMCanvasItem::draw_multiline_string_outline, DEFVAL(HORIZONTAL_ALIGNMENT_LEFT), DEFVAL(-1), DEFVAL(KABOOMCanvasItem::DEFAULT_FONT_SIZE), DEFVAL(-1), DEFVAL(1), DEFVAL(Color(1.0, 1.0, 1.0)), DEFVAL(TextServer::BREAK_MANDATORY | TextServer::BREAK_WORD_BOUND), DEFVAL(TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND), DEFVAL(TextServer::DIRECTION_AUTO), DEFVAL(TextServer::ORIENTATION_HORIZONTAL), DEFVAL(0.0));
	ClassDB::bind_method(D_METHOD("draw_char", "font", "pos", "char", "font_size", "modulate", "oversampling"), &KABOOMCanvasItem::draw_char, DEFVAL(KABOOMCanvasItem::DEFAULT_FONT_SIZE), DEFVAL(Color(1.0, 1.0, 1.0)), DEFVAL(0.0));
	ClassDB::bind_method(D_METHOD("draw_char_outline", "font", "pos", "char", "font_size", "size", "modulate", "oversampling"), &KABOOMCanvasItem::draw_char_outline, DEFVAL(KABOOMCanvasItem::DEFAULT_FONT_SIZE), DEFVAL(-1), DEFVAL(Color(1.0, 1.0, 1.0)), DEFVAL(0.0));
	ClassDB::bind_method(D_METHOD("draw_mesh", "mesh", "texture", "transform", "modulate"), &KABOOMCanvasItem::draw_mesh, DEFVAL(Transform2D()), DEFVAL(Color(1, 1, 1, 1)));
	ClassDB::bind_method(D_METHOD("draw_multimesh", "multimesh", "texture"), &KABOOMCanvasItem::draw_multimesh);
	ClassDB::bind_method(D_METHOD("draw_set_transform", "position", "rotation", "scale"), &KABOOMCanvasItem::draw_set_transform, DEFVAL(0.0), DEFVAL(Size2(1.0, 1.0)));
	ClassDB::bind_method(D_METHOD("draw_set_transform_matrix", "xform"), &KABOOMCanvasItem::draw_set_transform_matrix);
	ClassDB::bind_method(D_METHOD("draw_animation_slice", "animation_length", "slice_begin", "slice_end", "offset"), &KABOOMCanvasItem::draw_animation_slice, DEFVAL(0.0));
	ClassDB::bind_method(D_METHOD("draw_end_animation"), &KABOOMCanvasItem::draw_end_animation);
	ClassDB::bind_method(D_METHOD("get_transform"), &KABOOMCanvasItem::get_transform);
	ClassDB::bind_method(D_METHOD("get_global_transform"), &KABOOMCanvasItem::get_global_transform);
	ClassDB::bind_method(D_METHOD("get_global_transform_with_canvas"), &KABOOMCanvasItem::get_global_transform_with_canvas);
	ClassDB::bind_method(D_METHOD("get_viewport_transform"), &KABOOMCanvasItem::get_viewport_transform);
	ClassDB::bind_method(D_METHOD("get_viewport_rect"), &KABOOMCanvasItem::get_viewport_rect);
	ClassDB::bind_method(D_METHOD("get_canvas_transform"), &KABOOMCanvasItem::get_canvas_transform);
	ClassDB::bind_method(D_METHOD("get_screen_transform"), &KABOOMCanvasItem::get_screen_transform);
	ClassDB::bind_method(D_METHOD("get_local_mouse_position"), &KABOOMCanvasItem::get_local_mouse_position);
	ClassDB::bind_method(D_METHOD("get_global_mouse_position"), &KABOOMCanvasItem::get_global_mouse_position);
	ClassDB::bind_method(D_METHOD("get_canvas"), &KABOOMCanvasItem::get_canvas);
	ClassDB::bind_method(D_METHOD("get_canvas_layer_node"), &KABOOMCanvasItem::get_canvas_layer_node);
	ClassDB::bind_method(D_METHOD("get_world_2d"), &KABOOMCanvasItem::get_world_2d);
	//ClassDB::bind_method(D_METHOD("get_viewport"),&KABOOMCanvasItem::get_viewport);

	ClassDB::bind_method(D_METHOD("set_material", "material"), &KABOOMCanvasItem::set_material);
	ClassDB::bind_method(D_METHOD("get_material"), &KABOOMCanvasItem::get_material);

	ClassDB::bind_method(D_METHOD("set_instance_shader_parameter", "name", "value"), &KABOOMCanvasItem::set_instance_shader_parameter);
	ClassDB::bind_method(D_METHOD("get_instance_shader_parameter", "name"), &KABOOMCanvasItem::get_instance_shader_parameter);

	ClassDB::bind_method(D_METHOD("set_use_parent_material", "enable"), &KABOOMCanvasItem::set_use_parent_material);
	ClassDB::bind_method(D_METHOD("get_use_parent_material"), &KABOOMCanvasItem::get_use_parent_material);

	ClassDB::bind_method(D_METHOD("set_notify_local_transform", "enable"), &KABOOMCanvasItem::set_notify_local_transform);
	ClassDB::bind_method(D_METHOD("is_local_transform_notification_enabled"), &KABOOMCanvasItem::is_local_transform_notification_enabled);

	ClassDB::bind_method(D_METHOD("set_notify_transform", "enable"), &KABOOMCanvasItem::set_notify_transform);
	ClassDB::bind_method(D_METHOD("is_transform_notification_enabled"), &KABOOMCanvasItem::is_transform_notification_enabled);

	ClassDB::bind_method(D_METHOD("force_update_transform"), &KABOOMCanvasItem::force_update_transform);

	ClassDB::bind_method(D_METHOD("make_canvas_position_local", "viewport_point"), &KABOOMCanvasItem::make_canvas_position_local);
	ClassDB::bind_method(D_METHOD("make_input_local", "event"), &KABOOMCanvasItem::make_input_local);

	ClassDB::bind_method(D_METHOD("set_visibility_layer", "layer"), &KABOOMCanvasItem::set_visibility_layer);
	ClassDB::bind_method(D_METHOD("get_visibility_layer"), &KABOOMCanvasItem::get_visibility_layer);
	ClassDB::bind_method(D_METHOD("set_visibility_layer_bit", "layer", "enabled"), &KABOOMCanvasItem::set_visibility_layer_bit);
	ClassDB::bind_method(D_METHOD("get_visibility_layer_bit", "layer"), &KABOOMCanvasItem::get_visibility_layer_bit);

	ClassDB::bind_method(D_METHOD("set_texture_filter", "mode"), &KABOOMCanvasItem::set_texture_filter);
	ClassDB::bind_method(D_METHOD("get_texture_filter"), &KABOOMCanvasItem::get_texture_filter);

	ClassDB::bind_method(D_METHOD("set_texture_repeat", "mode"), &KABOOMCanvasItem::set_texture_repeat);
	ClassDB::bind_method(D_METHOD("get_texture_repeat"), &KABOOMCanvasItem::get_texture_repeat);

	ClassDB::bind_method(D_METHOD("set_clip_children_mode", "mode"), &KABOOMCanvasItem::set_clip_children_mode);
	ClassDB::bind_method(D_METHOD("get_clip_children_mode"), &KABOOMCanvasItem::get_clip_children_mode);

	GDVIRTUAL_BIND(_draw);

	ADD_GROUP("Visibility", "");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "visible"), "set_visible", "is_visible");
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "modulate"), "set_modulate", "get_modulate");
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "self_modulate"), "set_self_modulate", "get_self_modulate");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "show_behind_parent"), "set_draw_behind_parent", "is_draw_behind_parent_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "top_level"), "set_as_top_level", "is_set_as_top_level");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "clip_children", PROPERTY_HINT_ENUM, "Disabled,Clip Only,Clip + Draw"), "set_clip_children_mode", "get_clip_children_mode");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "light_mask", PROPERTY_HINT_LAYERS_2D_RENDER), "set_light_mask", "get_light_mask");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "visibility_layer", PROPERTY_HINT_LAYERS_2D_RENDER), "set_visibility_layer", "get_visibility_layer");

	ADD_GROUP("Ordering", "");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "z_index", PROPERTY_HINT_RANGE, itos(RenderingServer::CANVAS_ITEM_Z_MIN) + "," + itos(RenderingServer::CANVAS_ITEM_Z_MAX) + ",1"), "set_z_index", "get_z_index");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "z_as_relative"), "set_z_as_relative", "is_z_relative");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "y_sort_enabled"), "set_y_sort_enabled", "is_y_sort_enabled");

	ADD_GROUP("Texture", "texture_");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "texture_filter", PROPERTY_HINT_ENUM, "Inherit,Nearest,Linear,Nearest Mipmap,Linear Mipmap,Nearest Mipmap Anisotropic,Linear Mipmap Anisotropic"), "set_texture_filter", "get_texture_filter");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "texture_repeat", PROPERTY_HINT_ENUM, "Inherit,Disabled,Enabled,Mirror"), "set_texture_repeat", "get_texture_repeat");

	ADD_GROUP("Material", "");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "material", PROPERTY_HINT_RESOURCE_TYPE, "CanvasItemMaterial,ShaderMaterial"), "set_material", "get_material");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_parent_material"), "set_use_parent_material", "get_use_parent_material");
	// ADD_PROPERTY(PropertyInfo(Variant::BOOL,"transform/notify"),"set_transform_notify","is_transform_notify_enabled");

	ADD_SIGNAL(MethodInfo("draw"));
	ADD_SIGNAL(MethodInfo("visibility_changed"));
	ADD_SIGNAL(MethodInfo("hidden"));
	ADD_SIGNAL(MethodInfo("item_rect_changed"));

	BIND_CONSTANT(KABOOMCanvasItem::NOTIFICATION_TRANSFORM_CHANGED);
	BIND_CONSTANT(KABOOMCanvasItem::NOTIFICATION_LOCAL_TRANSFORM_CHANGED);
	BIND_CONSTANT(KABOOMCanvasItem::NOTIFICATION_DRAW);
	BIND_CONSTANT(KABOOMCanvasItem::NOTIFICATION_VISIBILITY_CHANGED);
	BIND_CONSTANT(KABOOMCanvasItem::NOTIFICATION_ENTER_CANVAS);
	BIND_CONSTANT(KABOOMCanvasItem::NOTIFICATION_EXIT_CANVAS);
	BIND_CONSTANT(KABOOMCanvasItem::NOTIFICATION_WORLD_2D_CHANGED);

	BIND_ENUM_CONSTANT(KABOOMCanvasItem::TEXTURE_FILTER_PARENT_NODE);
	BIND_ENUM_CONSTANT(KABOOMCanvasItem::TEXTURE_FILTER_NEAREST);
	BIND_ENUM_CONSTANT(KABOOMCanvasItem::TEXTURE_FILTER_LINEAR);
	BIND_ENUM_CONSTANT(KABOOMCanvasItem::TEXTURE_FILTER_NEAREST_WITH_MIPMAPS);
	BIND_ENUM_CONSTANT(KABOOMCanvasItem::TEXTURE_FILTER_LINEAR_WITH_MIPMAPS);
	BIND_ENUM_CONSTANT(KABOOMCanvasItem::TEXTURE_FILTER_NEAREST_WITH_MIPMAPS_ANISOTROPIC);
	BIND_ENUM_CONSTANT(KABOOMCanvasItem::TEXTURE_FILTER_LINEAR_WITH_MIPMAPS_ANISOTROPIC);
	BIND_ENUM_CONSTANT(KABOOMCanvasItem::TEXTURE_FILTER_MAX);

	BIND_ENUM_CONSTANT(KABOOMCanvasItem::TEXTURE_REPEAT_PARENT_NODE);
	BIND_ENUM_CONSTANT(KABOOMCanvasItem::TEXTURE_REPEAT_DISABLED);
	BIND_ENUM_CONSTANT(KABOOMCanvasItem::TEXTURE_REPEAT_ENABLED);
	BIND_ENUM_CONSTANT(KABOOMCanvasItem::TEXTURE_REPEAT_MIRROR);
	BIND_ENUM_CONSTANT(KABOOMCanvasItem::TEXTURE_REPEAT_MAX);

	BIND_ENUM_CONSTANT(KABOOMCanvasItem::CLIP_CHILDREN_DISABLED);
	BIND_ENUM_CONSTANT(KABOOMCanvasItem::CLIP_CHILDREN_ONLY);
	BIND_ENUM_CONSTANT(KABOOMCanvasItem::CLIP_CHILDREN_AND_DRAW);
	BIND_ENUM_CONSTANT(KABOOMCanvasItem::CLIP_CHILDREN_MAX);
}

#pragma endregion

#pragma region Private Functions

#pragma region Blocking

void KABOOMCanvasItem::_block() { _block_count++; }
void KABOOMCanvasItem::_unblock() { _block_count = MAX(_block_count - 1, 0); }
bool KABOOMCanvasItem::_is_blocked() const { return _block_count > 0; }

#pragma endregion

#pragma region Drawing

void KABOOMCanvasItem::_redraw_callback() {
	if (!is_inside_tree()) {
		pending_update = false;
		return;
	}

	RID ci = get_canvas_item();
	RenderingServer *rs = RenderingServer::get_singleton();
	rs->canvas_item_clear(ci);

	//todo updating = true - only allow drawing here
	if (is_visible_in_tree()) {
		drawing = true;
		Ref<TextServer> ts = TextServerManager::get_singleton()->get_primary_interface();
		double oversampling = 1.0;
		if (ts.is_valid()) {
			// ts->font_set_global_oversampling(ts->font_get_global_oversampling());
			// ts->set_current_drawn_item_oversampling(get_viewport()->get_oversampling());

			Ref<Viewport> viewport = get_viewport();

			if (viewport.is_valid()) {
				Size2 canvas_size = viewport->get_visible_rect().size;
				Size2 texture_size = viewport->get_vrs_texture()->get_size();

				if (texture_size.x > 0 && texture_size.y > 0) {
					oversampling = texture_size.x / canvas_size.x;
				}
			}

			// Apply oversampling by scaling the canvas transform if needed
			if (oversampling != 1.0) {
				Transform2D original_xform = Transform2D();
				// Transform2D original_xform = get_transform();
				rs->canvas_item_set_transform(ci, original_xform.scaled(Vector2(oversampling, oversampling)));
			}
		}
		current_item_drawn = this;
		notification(NOTIFICATION_DRAW);
		emit_signal("draw");
		GDVIRTUAL_CALL(_draw);
		current_item_drawn = nullptr;
		if (ts.is_valid()) {
			// ts->font_set_global_oversampling(0.0);
			// ts->set_current_drawn_item_oversampling(0.0);
			if (oversampling != 1.0) {
				rs->canvas_item_set_transform(ci, Transform2D()); // Reset to identity
			}
		}
		drawing = false;
	}
	//todo updating = false
	pending_update = false; // don't change to false until finished drawing (avoid recursive update)
}

#pragma endregion

#pragma region Global Invalid Flag Functions

void KABOOMCanvasItem::_set_global_invalid(bool p_invalid) const {
	if (get_process_thread_group()) {
		if (p_invalid) {
			global_invalid.mt.set();
		} else {
			global_invalid.mt.clear();
		}
	} else {
		global_invalid.st = p_invalid;
	}
}

#pragma endregion

#pragma region Visibility

// void KABOOMCanvasItem::_top_level_raise_self() {
// 	if (!is_inside_tree()) {
// 		return;
// 	}

// 	// if (canvas_layer) {
// 	// 	RenderingServer::get_singleton()->canvas_item_set_draw_index(canvas_item, canvas_layer->get_sort_index());
// 	// } else {
// 	// 	RenderingServer::get_singleton()->canvas_item_set_draw_index(canvas_item, get_viewport()->gui_get_canvas_sort_index());
// 	// }
// }

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

void KABOOMCanvasItem::_top_level_changed() {
	// Inform children that top_level status has changed on a parent.
	int children = get_child_count();
	for (int i = 0; i < children; i++) {
		KABOOMCanvasItem *child = Object::cast_to<KABOOMCanvasItem>(get_child(i));
		if (child) {
			child->_top_level_changed_on_parent();
		}
	}
}
void KABOOMCanvasItem::_top_level_changed_on_parent() {
	// Inform children that top_level status has changed on a parent.
	_top_level_changed();
}

bool KABOOMCanvasItem::is_set_as_top_level() const {
	return top_level;
}

KABOOMCanvasItem *KABOOMCanvasItem::get_parent_item() const {
	ERR_READ_THREAD_GUARD_V(nullptr);
	if (top_level) {
		return nullptr;
	}

	return Object::cast_to<KABOOMCanvasItem>(get_parent());
}

void KABOOMCanvasItem::_window_visibility_changed() {
	_propagate_visibility_changed(window->is_visible());
}

#pragma endregion

#pragma region Misc

void KABOOMCanvasItem::_enter_canvas() {
	// Resolves to nullptr if the node is top_level.
	KABOOMCanvasItem *parent_item = get_parent_item();

	/* if (get_parent()) {
		get_viewport()->canvas_parent_mark_dirty(get_parent());
	} */

	if (parent_item) {
		canvas_layer = parent_item->canvas_layer;
		RenderingServer::get_singleton()->canvas_item_set_parent(canvas_item, parent_item->get_canvas_item());
		RenderingServer::get_singleton()->canvas_item_set_visibility_layer(canvas_item, visibility_layer);
	} else {
		Node *n = this;

		canvas_layer = nullptr;

		while (n) {
			canvas_layer = Object::cast_to<CanvasLayer>(n);
			if (canvas_layer) {
				break;
			}
			if (Object::cast_to<Viewport>(n)) {
				break;
			}
			n = n->get_parent();
		}

		RID canvas;
		if (canvas_layer) {
			canvas = canvas_layer->get_canvas();
		} else {
			canvas = get_viewport()->find_world_2d()->get_canvas();
		}

		RenderingServer::get_singleton()->canvas_item_set_parent(canvas_item, canvas);
		RenderingServer::get_singleton()->canvas_item_set_visibility_layer(canvas_item, visibility_layer);

		canvas_group = "_root_canvas" + itos(canvas.get_id());

		add_to_group(canvas_group);
		/* if (canvas_layer) {
			canvas_layer->reset_sort_index();
		} else {
			get_viewport()->gui_reset_canvas_sort_index();
		} */
	}

	pending_update = false;
	queue_redraw();

	notification(NOTIFICATION_ENTER_CANVAS);
}
void KABOOMCanvasItem::_exit_canvas() {
	notification(NOTIFICATION_EXIT_CANVAS, true); //reverse the notification
	RenderingServer::get_singleton()->canvas_item_set_parent(canvas_item, RID());
	canvas_layer = nullptr;
	if (canvas_group != StringName()) {
		remove_from_group(canvas_group);
		canvas_group = StringName();
	}
}

// void _physics_interpolated_changed() override;
void KABOOMCanvasItem::_physics_interpolated_changed() {
	RenderingServer::get_singleton()->canvas_item_set_interpolated(canvas_item, is_physics_interpolated());
}

void KABOOMCanvasItem::_refresh_texture_repeat_cache() const {
	if (!is_inside_tree()) {
		return;
	}

	if (texture_repeat == TEXTURE_REPEAT_PARENT_NODE) {
		KABOOMCanvasItem *parent_item = get_parent_item();
		if (parent_item) {
			texture_repeat_cache = parent_item->texture_repeat_cache;
		} else {
			texture_repeat_cache = RenderingServer::CANVAS_ITEM_TEXTURE_REPEAT_DEFAULT;
		}
	} else {
		texture_repeat_cache = RenderingServer::CanvasItemTextureRepeat(texture_repeat);
	}
}
void KABOOMCanvasItem::_update_texture_repeat_changed(bool p_propagate) {
	if (!is_inside_tree()) {
		return;
	}
	_refresh_texture_repeat_cache();
	_update_self_texture_repeat(texture_repeat_cache);

	if (p_propagate) {
		for (KABOOMCanvasItem *E : children_items) {
			if (!E->top_level && E->texture_repeat == TEXTURE_REPEAT_PARENT_NODE) {
				E->_update_texture_repeat_changed(true);
			}
		}
	}
}

void KABOOMCanvasItem::_refresh_texture_filter_cache() const {
	if (!is_inside_tree()) {
		return;
	}

	if (texture_filter == TEXTURE_FILTER_PARENT_NODE) {
		KABOOMCanvasItem *parent_item = get_parent_item();
		if (parent_item) {
			texture_filter_cache = parent_item->texture_filter_cache;
		} else {
			texture_filter_cache = RenderingServer::CANVAS_ITEM_TEXTURE_FILTER_DEFAULT;
		}
	} else {
		texture_filter_cache = RenderingServer::CanvasItemTextureFilter(texture_filter);
	}
}
void KABOOMCanvasItem::_update_texture_filter_changed(bool p_propagate) {
	if (!is_inside_tree()) {
		return;
	}
	_refresh_texture_filter_cache();
	_update_self_texture_filter(texture_filter_cache);

	if (p_propagate) {
		for (KABOOMCanvasItem *E : children_items) {
			if (!E->top_level && E->texture_filter == TEXTURE_FILTER_PARENT_NODE) {
				E->_update_texture_filter_changed(true);
			}
		}
	}
}

const StringName *KABOOMCanvasItem::_instance_shader_parameter_get_remap(const StringName &p_name) const {
	StringName *r = instance_shader_parameter_property_remap.getptr(p_name);
	if (!r) {
		String s = p_name;
		if (s.begins_with("instance_shader_parameters/")) {
			StringName name = s.trim_prefix("instance_shader_parameters/");
			instance_shader_parameter_property_remap[p_name] = name;
			return instance_shader_parameter_property_remap.getptr(p_name);
		}
		return nullptr;
	}
	return r;
}

#pragma endregion

#pragma region Transform

void KABOOMCanvasItem::_notify_transform(KABOOMCanvasItem *p_node) {
	/* This check exists to avoid re-propagating the transform
	 * notification down the tree on dirty nodes. It provides
	 * optimization by avoiding redundancy (nodes are dirty, will get the
	 * notification anyway).
	 */

	if (/*p_node->xform_change.in_list() &&*/ p_node->_is_global_invalid()) {
		return; //nothing to do
	}

	p_node->_set_global_invalid(true);

	if (p_node->notify_transform && !p_node->xform_change.in_list()) {
		if (!p_node->block_transform_notify) {
			if (p_node->is_inside_tree()) {
				// if (is_accessible_from_caller_thread()) {
				// 	get_tree()->xform_change_list.add(&p_node->xform_change);
				// } else {
				// Should be rare, but still needs to be handled.
				callable_mp(p_node, &KABOOMCanvasItem::_notify_transform_deferred).call_deferred();
				// }
			}
		}
	}

	for (KABOOMCanvasItem *ci : p_node->children_items) {
		if (ci->top_level) {
			continue;
		}
		_notify_transform(ci);
	}
}

void KABOOMCanvasItem::_notify_transform_deferred() {
	// if (is_inside_tree() && notify_transform && !xform_change.in_list()) {
	// 	get_tree()->xform_change_list.add(&xform_change);
	// }
}

#pragma endregion

#pragma endregion

#pragma region Protected Functions

#pragma region Misc

bool KABOOMCanvasItem::_set(const StringName &p_name, const Variant &p_value) {
	const StringName *r = _instance_shader_parameter_get_remap(p_name);
	if (r) {
		set_instance_shader_parameter(*r, p_value);
		return true;
	}
	return false;
}
bool KABOOMCanvasItem::_get(const StringName &p_name, Variant &r_ret) const {
	const StringName *r = _instance_shader_parameter_get_remap(p_name);
	if (r) {
		r_ret = get_instance_shader_parameter(*r);
		return true;
	}

	return false;
}
void KABOOMCanvasItem::_get_property_list(List<PropertyInfo> *p_list) const {
	List<PropertyInfo> pinfo;
	// RenderingServer::get_singleton()->canvas_item_get_instance_shader_parameter_list(get_canvas_item(), &pinfo);

	for (PropertyInfo &pi : pinfo) {
		bool has_def_value = false;
		Variant def_value = RenderingServer::get_singleton()->instance_geometry_get_shader_parameter_default_value(get_canvas_item(), pi.name);
		// Variant def_value = RenderingServer::get_singleton()->canvas_item_get_instance_shader_parameter_default_value(get_canvas_item(), pi.name);
		if (def_value.get_type() != Variant::NIL) {
			has_def_value = true;
		}
		if (instance_shader_parameters.has(pi.name)) {
			pi.usage = PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_STORAGE | (has_def_value ? (PROPERTY_USAGE_CHECKABLE | PROPERTY_USAGE_CHECKED) : PROPERTY_USAGE_NONE);
		} else {
			pi.usage = PROPERTY_USAGE_EDITOR | (has_def_value ? PROPERTY_USAGE_CHECKABLE : PROPERTY_USAGE_NONE); // Do not save if not changed.
		}

		pi.name = "instance_shader_parameters/" + pi.name;
		p_list->push_back(pi);
	}
}

void KABOOMCanvasItem::_update_self_texture_repeat(RenderingServer::CanvasItemTextureRepeat p_texture_repeat) {
	RenderingServer::get_singleton()->canvas_item_set_default_texture_repeat(get_canvas_item(), p_texture_repeat);
	queue_redraw();
}
void KABOOMCanvasItem::_update_self_texture_filter(RenderingServer::CanvasItemTextureFilter p_texture_filter) {
	RenderingServer::get_singleton()->canvas_item_set_default_texture_filter(get_canvas_item(), p_texture_filter);
	queue_redraw();
}

void KABOOMCanvasItem::item_rect_changed(bool p_size_changed = true) {
	ERR_MAIN_THREAD_GUARD;
	if (p_size_changed) {
		queue_redraw();
	}
	emit_signal("item_rect_changed");
}

void KABOOMCanvasItem::set_canvas_item_use_identity_transform(bool p_enable) {
	// Prevent sending item transforms to RenderingServer when using global coords.
	// _set_use_identity_transform(p_enable);

	// Let RenderingServer know not to concatenate the parent transform during the render.
	// RenderingServer::get_singleton()->canvas_item_set_use_identity_transform(get_canvas_item(), p_enable);
	// RenderingServer::get_singleton()->canvas_item_set_use_identity_transform(get_canvas_item(), p_enable);

	if (is_inside_tree()) {
		if (p_enable) {
			// Make sure item is using identity transform in server.
			RenderingServer::get_singleton()->canvas_item_set_transform(get_canvas_item(), Transform2D());
		} else {
			// Make sure item transform is up to date in server if switching identity transform off.
			RenderingServer::get_singleton()->canvas_item_set_transform(get_canvas_item(), get_transform());
		}
	}
}

void KABOOMCanvasItem::_notification(int p_what) {
	switch (p_what) {
			// case 3000: {
			// 	RID ae = get_accessibility_element();
			// 	ERR_FAIL_COND(ae.is_null());

			// 	DisplayServer::get_singleton()->accessibility_update_set_flag(ae, DisplayServer::AccessibilityFlags::FLAG_HIDDEN, !visible);
			// } break;

		case NOTIFICATION_ENTER_TREE: {
			ERR_MAIN_THREAD_GUARD;
			ERR_FAIL_COND(!is_inside_tree());

			Node *parent = get_parent();
			if (parent) {
				KABOOMCanvasItem *ci = Object::cast_to<KABOOMCanvasItem>(parent);

				if (ci) {
					parent_visible_in_tree = ci->is_visible_in_tree();
					C = ci->children_items.push_back(this);
				} else {
					CanvasLayer *cl = Object::cast_to<CanvasLayer>(parent);

					if (cl) {
						parent_visible_in_tree = cl->is_visible();
					} else {
						// Look for a window.
						Viewport *viewport = nullptr;

						while (parent) {
							viewport = Object::cast_to<Viewport>(parent);
							if (viewport) {
								break;
							}
							parent = parent->get_parent();
						}

						ERR_FAIL_NULL(viewport);

						window = Object::cast_to<Window>(viewport);
						if (window) {
							window->connect("visibility_changed", callable_mp(this, &KABOOMCanvasItem::_window_visibility_changed));
							parent_visible_in_tree = window->is_visible();
						} else {
							parent_visible_in_tree = true;
						}
					}
				}
			}

			_set_global_invalid(true);
			_enter_canvas();

			RenderingServer::get_singleton()->canvas_item_set_visible(canvas_item, is_visible_in_tree()); // The visibility of the parent may change.
			if (is_visible_in_tree()) {
				notification(NOTIFICATION_VISIBILITY_CHANGED); // Considered invisible until entered.
			}

			_update_texture_filter_changed(false);
			_update_texture_repeat_changed(false);

			// if (!block_transform_notify && !xform_change.in_list()) {
			// 	get_tree()->xform_change_list.add(&xform_change);
			// }

			// if (get_viewport()) {
			// 	get_parent()->connect("child_order_changed", callable_mp(get_viewport(), &Viewport::canvas_parent_mark_dirty).bind(get_parent()), CONNECT_REFERENCE_COUNTED);
			// }

			// If using physics interpolation, reset for this node only,
			// as a helper, as in most cases, users will want items reset when
			// adding to the tree.
			// In cases where they move immediately after adding,
			// there will be little cost in having two resets as these are cheap,
			// and it is worth it for convenience.
			// Do not propagate to children, as each child of an added branch
			// receives its own NOTIFICATION_ENTER_TREE, and this would
			// cause unnecessary duplicate resets.
			if (is_physics_interpolated_and_enabled()) {
				notification(NOTIFICATION_RESET_PHYSICS_INTERPOLATION);
			}

		} break;
		case NOTIFICATION_EXIT_TREE: {
			ERR_MAIN_THREAD_GUARD;

			// if (xform_change.in_list()) {
			// 	get_tree()->xform_change_list.remove(&xform_change);
			// }
			_exit_canvas();
			if (C) {
				Object::cast_to<KABOOMCanvasItem>(get_parent())->children_items.erase(C);
				C = nullptr;
			}
			if (window) {
				window->disconnect("visibility_changed", callable_mp(this, &KABOOMCanvasItem::_window_visibility_changed));
				window = nullptr;
			}
			_set_global_invalid(true);
			parent_visible_in_tree = false;

			// if (get_viewport()) {
			// 	get_parent()->disconnect("child_order_changed", callable_mp(get_viewport(), &Viewport::canvas_parent_mark_dirty).bind(get_parent()));
			// }
		} break;

		case NOTIFICATION_RESET_PHYSICS_INTERPOLATION: {
			if (is_visible_in_tree() && is_physics_interpolated()) {
				RenderingServer::get_singleton()->canvas_item_reset_physics_interpolation(canvas_item);
			}
		} break;

		case NOTIFICATION_VISIBILITY_CHANGED: {
			ERR_MAIN_THREAD_GUARD;

			emit_signal("visibility_changed");
		} break;
		case NOTIFICATION_WORLD_2D_CHANGED: {
			ERR_MAIN_THREAD_GUARD;

			_exit_canvas();
			_enter_canvas();
		} break;
		case NOTIFICATION_PARENTED: {
			// The node is not inside the tree during this notification.
			ERR_MAIN_THREAD_GUARD;

			_notify_transform();
		} break;
	}
}

void KABOOMCanvasItem::_validate_property(PropertyInfo &p_property) const {
	if (hide_clip_children && p_property.name == StringName("clip_children")) {
		p_property.usage = PROPERTY_USAGE_NONE;
	}
}

#pragma endregion

#pragma endregion

#pragma region Public Functions

#ifdef DEBUG_ENABLED

// Those need to be available in debug runtime, to allow for node selection.

// Select the node.
bool _edit_is_selected_on_click(const Point2 &p_point, double p_tolerance) const {
	if (_edit_use_rect()) {
		return _edit_get_rect().has_point(p_point);
	} else {
		return p_point.length() < p_tolerance;
	}
}

#endif // DEBUG_ENABLED
#ifdef TOOLS_ENABLED
virtual Transform2D _edit_get_transform() const {
	return Transform2D(_edit_get_rotation(), _edit_get_position() + _edit_get_pivot());
}
#endif // TOOLS_ENABLED

#pragma region Lifecycle

KABOOMCanvasItem::KABOOMCanvasItem() :
		xform_change(this) {
	canvas_item = RenderingServer::get_singleton()->canvas_item_create();
}
KABOOMCanvasItem::~KABOOMCanvasItem() {
	ERR_FAIL_NULL(RenderingServer::get_singleton());
	RenderingServer::get_singleton()->free_rid(canvas_item);
}

#pragma endregion

#pragma region Node Overriden Function

void KABOOMCanvasItem::add_child(Node *p_node, bool p_force_readable_name, Node::InternalMode p_internal) {
#ifdef DEBUG_ENABLED
#endif
	ERR_FAIL_COND_MSG(_is_blocked(), "Parent node is busy setting up children, `add_child()` failed. Consider using `add_child.call_deferred(child)` instead.");

	Node::add_child(p_node, p_force_readable_name, p_internal);
}

void KABOOMCanvasItem::add_sibling(Node *p_sibling, bool p_force_readable_name) {
	ERR_FAIL_COND_MSG(_is_blocked(), "Parent node is busy setting up children, `add_sibling()` failed. Consider using `add_sibling.call_deferred(sibling)` instead.");

	Node::add_sibling(p_sibling, p_force_readable_name);
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

#pragma region Visibility

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

void KABOOMCanvasItem::show() {
	ERR_MAIN_THREAD_GUARD;
	set_visible(true);
}
void KABOOMCanvasItem::hide() {
	ERR_MAIN_THREAD_GUARD;
	set_visible(false);
}
void KABOOMCanvasItem::move_to_front() {
	ERR_MAIN_THREAD_GUARD;
	if (!get_parent()) {
		return;
	}
	get_parent()->move_child(this, -1);
}

void KABOOMCanvasItem::set_visibility_layer(uint32_t p_visibility_layer) {
	ERR_THREAD_GUARD;
	visibility_layer = p_visibility_layer;
	RenderingServer::get_singleton()->canvas_item_set_visibility_layer(canvas_item, p_visibility_layer);
}
uint32_t KABOOMCanvasItem::get_visibility_layer() const {
	ERR_READ_THREAD_GUARD_V(0);
	return visibility_layer;
}

void KABOOMCanvasItem::set_visibility_layer_bit(uint32_t p_visibility_layer, bool p_enable) {
	ERR_THREAD_GUARD;
	ERR_FAIL_UNSIGNED_INDEX(p_visibility_layer, 32);
	if (p_enable) {
		set_visibility_layer(visibility_layer | (1 << p_visibility_layer));
	} else {
		set_visibility_layer(visibility_layer & (~(1 << p_visibility_layer)));
	}
}
bool KABOOMCanvasItem::get_visibility_layer_bit(uint32_t p_visibility_layer) const {
	ERR_READ_THREAD_GUARD_V(false);
	ERR_FAIL_UNSIGNED_INDEX_V(p_visibility_layer, 32, false);
	return (visibility_layer & (1 << p_visibility_layer));
}

#pragma region Top Level API

void KABOOMCanvasItem::set_as_top_level(bool p_top_level) {
	ERR_MAIN_THREAD_GUARD;
	if (top_level == p_top_level) {
		return;
	}

	if (!is_inside_tree()) {
		top_level = p_top_level;
		_notify_transform();
		return;
	}

	_exit_canvas();
	top_level = p_top_level;
	_top_level_changed();
	_enter_canvas();

	_notify_transform();

	Viewport *viewport = get_viewport();
	/* if (viewport) {
		viewport->canvas_item_top_level_changed();
	} */
}
bool KABOOMCanvasItem::is_set_as_top_level() const {
	return top_level;
}

void KABOOMCanvasItem::set_draw_behind_parent(bool p_enable) {
	ERR_THREAD_GUARD;
	if (behind == p_enable) {
		return;
	}
	behind = p_enable;
	RenderingServer::get_singleton()->canvas_item_set_draw_behind_parent(canvas_item, behind);
}
bool KABOOMCanvasItem::is_draw_behind_parent_enabled() const {
	ERR_READ_THREAD_GUARD_V(false);
	return behind;
}
// void move_to_front();
KABOOMCanvasItem *KABOOMCanvasItem::get_top_level() const {
	ERR_READ_THREAD_GUARD_V(nullptr);
	KABOOMCanvasItem *ci = const_cast<KABOOMCanvasItem *>(this);
	while (!ci->top_level && Object::cast_to<KABOOMCanvasItem>(ci->get_parent())) {
		ci = Object::cast_to<KABOOMCanvasItem>(ci->get_parent());
	}

	return ci;
}

#pragma endregion

#pragma region Light Mask API

void KABOOMCanvasItem::set_light_mask(int p_light_mask) {
	ERR_THREAD_GUARD;
	if (light_mask == p_light_mask) {
		return;
	}

	light_mask = p_light_mask;
	RenderingServer::get_singleton()->canvas_item_set_light_mask(canvas_item, p_light_mask);
}
int KABOOMCanvasItem::get_light_mask() const {
	ERR_READ_THREAD_GUARD_V(0);
	return light_mask;
}
#pragma endregion

#pragma region Clipping API

void KABOOMCanvasItem::set_clip_children_mode(ClipChildrenMode p_clip_mode) {
	ERR_THREAD_GUARD;
	ERR_FAIL_COND(p_clip_mode >= CLIP_CHILDREN_MAX);

	if (clip_children_mode == p_clip_mode) {
		return;
	}
	clip_children_mode = p_clip_mode;

	update_configuration_warnings();

	if (Object::cast_to<CanvasGroup>(this) != nullptr) {
		//avoid accidental bugs, make this not work on CanvasGroup
		return;
	}

	RenderingServer::get_singleton()->canvas_item_set_canvas_group_mode(get_canvas_item(), RenderingServer::CanvasGroupMode(clip_children_mode));
}

KABOOMCanvasItem::ClipChildrenMode KABOOMCanvasItem::get_clip_children_mode() const {
	ERR_READ_THREAD_GUARD_V(CLIP_CHILDREN_DISABLED);
	return clip_children_mode;
}

#pragma endregion

#pragma region Modulation API

void KABOOMCanvasItem::set_modulate(const Color &p_modulate) {
	ERR_THREAD_GUARD;
	if (modulate == p_modulate) {
		return;
	}

	modulate = p_modulate;
	RenderingServer::get_singleton()->canvas_item_set_modulate(canvas_item, modulate);
}
Color KABOOMCanvasItem::get_modulate() const {
	ERR_READ_THREAD_GUARD_V(Color());
	return modulate;
}
Color KABOOMCanvasItem::get_modulate_in_tree() const {
	ERR_READ_THREAD_GUARD_V(Color());
	Color final_modulate = modulate;
	KABOOMCanvasItem *parent_item = get_parent_item();
	while (parent_item) {
		final_modulate *= parent_item->get_modulate();
		parent_item = parent_item->get_parent_item();
	}
	return final_modulate;
}

void KABOOMCanvasItem::set_self_modulate(const Color &p_self_modulate) {
	ERR_THREAD_GUARD;
	if (self_modulate == p_self_modulate) {
		return;
	}

	self_modulate = p_self_modulate;
	RenderingServer::get_singleton()->canvas_item_set_self_modulate(canvas_item, self_modulate);
}
Color KABOOMCanvasItem::get_self_modulate() const {
	ERR_READ_THREAD_GUARD_V(Color());
	return self_modulate;
}

#pragma endregion

#pragma endregion

#pragma region Ordering

void KABOOMCanvasItem::set_z_index(int p_z) {
	ERR_THREAD_GUARD;
	ERR_FAIL_COND(p_z < RenderingServer::CANVAS_ITEM_Z_MIN);
	ERR_FAIL_COND(p_z > RenderingServer::CANVAS_ITEM_Z_MAX);
	z_index = p_z;
	RenderingServer::get_singleton()->canvas_item_set_z_index(canvas_item, z_index);
	update_configuration_warnings();
}
int KABOOMCanvasItem::get_z_index() const {
	ERR_READ_THREAD_GUARD_V(0);
	return z_index;
}
int KABOOMCanvasItem::get_effective_z_index() const {
	ERR_READ_THREAD_GUARD_V(0);
	int effective_z_index = z_index;
	if (is_z_relative()) {
		KABOOMCanvasItem *p = get_parent_item();
		if (p) {
			effective_z_index += p->get_effective_z_index();
		}
	}
	return effective_z_index;
}

void KABOOMCanvasItem::set_z_as_relative(bool p_enabled) {
	ERR_THREAD_GUARD;
	if (z_relative == p_enabled) {
		return;
	}
	z_relative = p_enabled;
	RenderingServer::get_singleton()->canvas_item_set_z_as_relative_to_parent(canvas_item, p_enabled);
}
bool KABOOMCanvasItem::is_z_relative() const {
	ERR_READ_THREAD_GUARD_V(false);
	return z_relative;
}

void KABOOMCanvasItem::set_y_sort_enabled(bool p_enabled) {
	ERR_THREAD_GUARD;
	y_sort_enabled = p_enabled;
	RenderingServer::get_singleton()->canvas_item_set_sort_children_by_y(canvas_item, y_sort_enabled);
}
bool KABOOMCanvasItem::is_y_sort_enabled() const {
	ERR_READ_THREAD_GUARD_V(false);
	return y_sort_enabled;
}

#pragma endregion

#pragma region Texture

void KABOOMCanvasItem::set_texture_filter(TextureFilter p_texture_filter) {
	ERR_MAIN_THREAD_GUARD; // Goes down in the tree, so only main thread can set.
	ERR_FAIL_INDEX(p_texture_filter, TEXTURE_FILTER_MAX);
	if (texture_filter == p_texture_filter) {
		return;
	}
	texture_filter = p_texture_filter;
	_update_texture_filter_changed(true);
	notify_property_list_changed();
}
KABOOMCanvasItem::TextureFilter KABOOMCanvasItem::get_texture_filter() const {
	ERR_READ_THREAD_GUARD_V(TEXTURE_FILTER_NEAREST);
	return texture_filter;
}
KABOOMCanvasItem::TextureFilter KABOOMCanvasItem::get_texture_filter_in_tree() const {
	ERR_READ_THREAD_GUARD_V(TEXTURE_FILTER_NEAREST);
	_refresh_texture_filter_cache();
	return (TextureFilter)texture_filter_cache;
}

void KABOOMCanvasItem::set_texture_repeat(TextureRepeat p_texture_repeat) {
	ERR_MAIN_THREAD_GUARD; // Goes down in the tree, so only main thread can set.
	ERR_FAIL_INDEX(p_texture_repeat, TEXTURE_REPEAT_MAX);
	if (texture_repeat == p_texture_repeat) {
		return;
	}
	texture_repeat = p_texture_repeat;
	_update_texture_repeat_changed(true);
	notify_property_list_changed();
}
KABOOMCanvasItem::TextureRepeat KABOOMCanvasItem::get_texture_repeat() const {
	ERR_READ_THREAD_GUARD_V(TEXTURE_REPEAT_DISABLED);
	return texture_repeat;
}
KABOOMCanvasItem::TextureRepeat KABOOMCanvasItem::get_texture_repeat_in_tree() const {
	ERR_READ_THREAD_GUARD_V(TEXTURE_REPEAT_DISABLED);
	_refresh_texture_repeat_cache();
	return (TextureRepeat)texture_repeat_cache;
}

#pragma endregion

#pragma region Material

void KABOOMCanvasItem::set_material(const Ref<Material> &p_material) {
	ERR_THREAD_GUARD;
	material = p_material;
	RID rid;
	if (material.is_valid()) {
		rid = material->get_rid();
	}
	RenderingServer::get_singleton()->canvas_item_set_material(canvas_item, rid);
	notify_property_list_changed(); //properties for material exposed
}
Ref<Material> KABOOMCanvasItem::get_material() const {
	ERR_READ_THREAD_GUARD_V(Ref<Material>());
	return material;
}

void KABOOMCanvasItem::set_use_parent_material(bool p_use_parent_material) {
	ERR_THREAD_GUARD;
	use_parent_material = p_use_parent_material;
	RenderingServer::get_singleton()->canvas_item_set_use_parent_material(canvas_item, p_use_parent_material);
}
bool KABOOMCanvasItem::get_use_parent_material() const {
	ERR_READ_THREAD_GUARD_V(false);
	return use_parent_material;
}

void KABOOMCanvasItem::set_instance_shader_parameter(const StringName &p_name, const Variant &p_value) {
	if (p_value.get_type() == Variant::NIL) {
		// Variant def_value = RenderingServer::get_singleton()->canvas_item_get_instance_shader_parameter_default_value(get_canvas_item(), p_name);
		Variant def_value = RenderingServer::get_singleton()->instance_geometry_get_shader_parameter_default_value(get_canvas_item(), p_name);
		// RenderingServer::get_singleton()->canvas_item_set_instance_shader_parameter(get_canvas_item(), p_name, def_value);
		RenderingServer::get_singleton()->instance_geometry_set_shader_parameter(get_canvas_item(), p_name, def_value);
		instance_shader_parameters.erase(p_value);
	} else {
		instance_shader_parameters[p_name] = p_value;
		if (p_value.get_type() == Variant::OBJECT) {
			RID tex_id = p_value;
			RenderingServer::get_singleton()->instance_geometry_set_shader_parameter(get_canvas_item(), p_name, tex_id);
			// RenderingServer::get_singleton()->canvas_item_set_instance_shader_parameter(get_canvas_item(), p_name, tex_id);
		} else {
			RenderingServer::get_singleton()->instance_geometry_set_shader_parameter(get_canvas_item(), p_name, p_value);
			// RenderingServer::get_singleton()->canvas_item_set_instance_shader_parameter(get_canvas_item(), p_name, p_value);
		}
	}
}

Variant KABOOMCanvasItem::get_instance_shader_parameter(const StringName &p_name) const {
	// return RenderingServer::get_singleton()->canvas_item_get_instance_shader_parameter(get_canvas_item(), p_name);
	return RenderingServer::get_singleton()->instance_geometry_get_shader_parameter(get_canvas_item(), p_name);
}

#pragma endregion

#pragma region CanvasLayer Functions

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

#pragma region Drawing
void KABOOMCanvasItem::update_draw_order() {
	ERR_MAIN_THREAD_GUARD;

	if (!is_inside_tree()) {
		return;
	}

	if (canvas_group != StringName()) {
		get_tree()->call_group_flags(SceneTree::GROUP_CALL_UNIQUE | SceneTree::GROUP_CALL_DEFERRED, canvas_group, "_top_level_raise_self");
	} else {
		ERR_FAIL_NULL_MSG(get_parent_item(), "Moved child is in incorrect state (no canvas group, no canvas item parent).");
		RenderingServer::get_singleton()->canvas_item_set_draw_index(canvas_item, get_index());
	}
}

void KABOOMCanvasItem::queue_redraw() {
	ERR_THREAD_GUARD; // Calling from thread is safe.
	if (!is_inside_tree()) {
		return;
	}
	if (pending_update) {
		return;
	}

	pending_update = true;

	callable_mp(this, &KABOOMCanvasItem::_redraw_callback).call_deferred();
}

void KABOOMCanvasItem::draw_dashed_line(const Point2 &p_from, const Point2 &p_to, const Color &p_color, real_t p_width = -1.0, real_t p_dash = 2.0, bool p_aligned = true, bool p_antialiased = false) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;
	ERR_FAIL_COND(p_dash <= 0.0);

	float length = (p_to - p_from).length();
	Vector2 step = p_dash * (p_to - p_from).normalized();

	if (length < p_dash || step == Vector2()) {
		RenderingServer::get_singleton()->canvas_item_add_line(canvas_item, p_from, p_to, p_color, p_width, p_antialiased);
		return;
	}

	int steps = (p_aligned) ? Math::ceil(length / p_dash) : Math::floor(length / p_dash);
	if (steps % 2 == 0) {
		steps--;
	}

	Point2 off = p_from;
	if (p_aligned) {
		off += (p_to - p_from).normalized() * (length - steps * p_dash) / 2.0;
	}

	PackedVector2Array points;
	points.resize(steps + 1);
	for (int i = 0; i < steps; i += 2) {
		points[i] = (i == 0) ? p_from : off;
		points[i + 1] = (p_aligned && i == steps - 1) ? p_to : (off + step);
		off += step * 2;
	}

	PackedColorArray colors = { p_color };

	RenderingServer::get_singleton()->canvas_item_add_multiline(canvas_item, points, colors, p_width, p_antialiased);
}
void KABOOMCanvasItem::draw_line(const Point2 &p_from, const Point2 &p_to, const Color &p_color, real_t p_width = -1.0, bool p_antialiased = false) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	RenderingServer::get_singleton()->canvas_item_add_line(canvas_item, p_from, p_to, p_color, p_width, p_antialiased);
}
void KABOOMCanvasItem::draw_polyline(const PackedVector2Array &p_points, const Color &p_color, real_t p_width = -1.0, bool p_antialiased = false) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	PackedColorArray colors = { p_color };
	RenderingServer::get_singleton()->canvas_item_add_polyline(canvas_item, p_points, colors, p_width, p_antialiased);
}
void KABOOMCanvasItem::draw_polyline_colors(const PackedVector2Array &p_points, const PackedColorArray &p_colors, real_t p_width = -1.0, bool p_antialiased = false) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	RenderingServer::get_singleton()->canvas_item_add_polyline(canvas_item, p_points, p_colors, p_width, p_antialiased);
}
void KABOOMCanvasItem::draw_arc(const Vector2 &p_center, real_t p_radius, real_t p_start_angle, real_t p_end_angle, int p_point_count, const Color &p_color, real_t p_width = -1.0, bool p_antialiased = false) {
	ERR_THREAD_GUARD;
	PackedVector2Array points;
	points.resize(p_point_count);
	Point2 *points_ptr = points.ptrw();

	// Clamp angle difference to full circle so arc won't overlap itself.
	const real_t delta_angle = CLAMP(p_end_angle - p_start_angle, -Math_TAU, Math_TAU);
	for (int i = 0; i < p_point_count; i++) {
		real_t theta = (i / (p_point_count - 1.0f)) * delta_angle + p_start_angle;
		points_ptr[i] = p_center + Vector2(Math::cos(theta), Math::sin(theta)) * p_radius;
	}

	draw_polyline(points, p_color, p_width, p_antialiased);
}
void KABOOMCanvasItem::draw_multiline(const PackedVector2Array &p_points, const Color &p_color, real_t p_width = -1.0, bool p_antialiased = false) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	PackedColorArray colors = { p_color };
	RenderingServer::get_singleton()->canvas_item_add_multiline(canvas_item, p_points, colors, p_width, p_antialiased);
}
void KABOOMCanvasItem::draw_multiline_colors(const PackedVector2Array &p_points, const PackedColorArray &p_colors, real_t p_width = -1.0, bool p_antialiased = false) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	RenderingServer::get_singleton()->canvas_item_add_multiline(canvas_item, p_points, p_colors, p_width, p_antialiased);
}
void KABOOMCanvasItem::draw_rect(const Rect2 &p_rect, const Color &p_color, bool p_filled = true, real_t p_width = -1.0, bool p_antialiased = false) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	Rect2 rect = p_rect.abs();

	if (p_filled) {
		if (p_width != -1.0) {
			WARN_PRINT("The draw_rect() \"width\" argument has no effect when \"filled\" is \"true\".");
		}

		RenderingServer::get_singleton()->canvas_item_add_rect(canvas_item, rect, p_color, p_antialiased);
	} else if (p_width >= rect.size.width || p_width >= rect.size.height) {
		RenderingServer::get_singleton()->canvas_item_add_rect(canvas_item, rect.grow(0.5f * p_width), p_color, p_antialiased);
	} else {
		PackedVector2Array points;
		points.resize(5);
		points[0] = rect.position;
		points[1] = rect.position + Vector2(rect.size.x, 0);
		points[2] = rect.position + rect.size;
		points[3] = rect.position + Vector2(0, rect.size.y);
		points[4] = rect.position;

		PackedColorArray colors = { p_color };

		RenderingServer::get_singleton()->canvas_item_add_polyline(canvas_item, points, colors, p_width, p_antialiased);
	}
}
void KABOOMCanvasItem::draw_circle(const Point2 &p_pos, real_t p_radius, const Color &p_color, bool p_filled = true, real_t p_width = -1.0, bool p_antialiased = false) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	if (p_filled) {
		if (p_width != -1.0) {
			WARN_PRINT("The draw_circle() \"width\" argument has no effect when \"filled\" is \"true\".");
		}

		RenderingServer::get_singleton()->canvas_item_add_circle(canvas_item, p_pos, p_radius, p_color, p_antialiased);
	} else if (p_width >= 2.0 * p_radius) {
		RenderingServer::get_singleton()->canvas_item_add_circle(canvas_item, p_pos, p_radius + 0.5 * p_width, p_color, p_antialiased);
	} else {
		// Tessellation count is hardcoded. Keep in sync with the same variable in `RendererCanvasCull::canvas_item_add_circle()`.
		const int circle_segments = 64;

		PackedVector2Array points;
		points.resize(circle_segments + 1);

		Vector2 *points_ptr = points.ptrw();
		const real_t circle_point_step = Math_TAU / circle_segments;

		for (int i = 0; i < circle_segments; i++) {
			float angle = i * circle_point_step;
			points_ptr[i].x = Math::cos(angle) * p_radius;
			points_ptr[i].y = Math::sin(angle) * p_radius;
			points_ptr[i] += p_pos;
		}
		points_ptr[circle_segments] = points_ptr[0];

		PackedColorArray colors = { p_color };

		RenderingServer::get_singleton()->canvas_item_add_polyline(canvas_item, points, colors, p_width, p_antialiased);
	}
}
void KABOOMCanvasItem::draw_texture(const Ref<Texture2D> &p_texture, const Point2 &p_pos, const Color &p_modulate = Color(1, 1, 1, 1)) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	ERR_FAIL_COND(p_texture.is_null());

	p_texture->draw(canvas_item, p_pos, p_modulate, false);
}
void KABOOMCanvasItem::draw_texture_rect(const Ref<Texture2D> &p_texture, const Rect2 &p_rect, bool p_tile = false, const Color &p_modulate = Color(1, 1, 1), bool p_transpose = false) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	ERR_FAIL_COND(p_texture.is_null());
	p_texture->draw_rect(canvas_item, p_rect, p_tile, p_modulate, p_transpose);
}
void KABOOMCanvasItem::draw_texture_rect_region(const Ref<Texture2D> &p_texture, const Rect2 &p_rect, const Rect2 &p_src_rect, const Color &p_modulate = Color(1, 1, 1), bool p_transpose = false, bool p_clip_uv = false) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;
	ERR_FAIL_COND(p_texture.is_null());
	p_texture->draw_rect_region(canvas_item, p_rect, p_src_rect, p_modulate, p_transpose, p_clip_uv);
}
void KABOOMCanvasItem::draw_msdf_texture_rect_region(const Ref<Texture2D> &p_texture, const Rect2 &p_rect, const Rect2 &p_src_rect, const Color &p_modulate = Color(1, 1, 1), double p_outline = 0.0, double p_pixel_range = 4.0, double p_scale = 1.0) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;
	ERR_FAIL_COND(p_texture.is_null());
	RenderingServer::get_singleton()->canvas_item_add_msdf_texture_rect_region(canvas_item, p_rect, p_texture->get_rid(), p_src_rect, p_modulate, p_outline, p_pixel_range, p_scale);
}
void KABOOMCanvasItem::draw_lcd_texture_rect_region(const Ref<Texture2D> &p_texture, const Rect2 &p_rect, const Rect2 &p_src_rect, const Color &p_modulate = Color(1, 1, 1)) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;
	ERR_FAIL_COND(p_texture.is_null());
	RenderingServer::get_singleton()->canvas_item_add_lcd_texture_rect_region(canvas_item, p_rect, p_texture->get_rid(), p_src_rect, p_modulate);
}
void KABOOMCanvasItem::draw_style_box(const Ref<StyleBox> &p_style_box, const Rect2 &p_rect) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	ERR_FAIL_COND(p_style_box.is_null());

	p_style_box->draw(canvas_item, p_rect);
}
void KABOOMCanvasItem::draw_primitive(const PackedVector2Array &p_points, const PackedColorArray &p_colors, const PackedVector2Array &p_uvs, Ref<Texture2D> p_texture = Ref<Texture2D>()) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	RID rid = p_texture.is_valid() ? p_texture->get_rid() : RID();
	RenderingServer::get_singleton()->canvas_item_add_primitive(canvas_item, p_points, p_colors, p_uvs, rid);
}
void KABOOMCanvasItem::draw_polygon(const PackedVector2Array &p_points, const PackedColorArray &p_colors, const PackedVector2Array &p_uvs = PackedVector2Array(), Ref<Texture2D> p_texture = Ref<Texture2D>()) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	const Ref<AtlasTexture> atlas = p_texture;
	if (atlas.is_valid() && atlas->get_atlas().is_valid()) {
		const Ref<Texture2D> &texture = atlas->get_atlas();
		const Vector2 atlas_size = texture->get_size();

		const Vector2 remap_min = atlas->get_region().position / atlas_size;
		const Vector2 remap_max = atlas->get_region().get_end() / atlas_size;

		PackedVector2Array uvs = p_uvs;
		for (Vector2 &p : uvs) {
			p.x = Math::remap(p.x, 0, 1, remap_min.x, remap_max.x);
			p.y = Math::remap(p.y, 0, 1, remap_min.y, remap_max.y);
		}
		RenderingServer::get_singleton()->canvas_item_add_polygon(canvas_item, p_points, p_colors, uvs, texture->get_rid());
	} else {
		RID texture_rid = p_texture.is_valid() ? p_texture->get_rid() : RID();
		RenderingServer::get_singleton()->canvas_item_add_polygon(canvas_item, p_points, p_colors, p_uvs, texture_rid);
	}
}
void KABOOMCanvasItem::draw_colored_polygon(const PackedVector2Array &p_points, const Color &p_color, const PackedVector2Array &p_uvs = PackedVector2Array(), Ref<Texture2D> p_texture = Ref<Texture2D>()) {
	draw_polygon(p_points, { p_color }, p_uvs, p_texture);
}

void KABOOMCanvasItem::draw_mesh(const Ref<Mesh> &p_mesh, const Ref<Texture2D> &p_texture, const Transform2D &p_transform = Transform2D(), const Color &p_modulate = Color(1, 1, 1)) {
	ERR_THREAD_GUARD;
	ERR_FAIL_COND(p_mesh.is_null());
	RID texture_rid = p_texture.is_valid() ? p_texture->get_rid() : RID();

	RenderingServer::get_singleton()->canvas_item_add_mesh(canvas_item, p_mesh->get_rid(), p_transform, p_modulate, texture_rid);
}
void KABOOMCanvasItem::draw_multimesh(const Ref<MultiMesh> &p_multimesh, const Ref<Texture2D> &p_texture) {
	ERR_THREAD_GUARD;
	ERR_FAIL_COND(p_multimesh.is_null());
	RID texture_rid = p_texture.is_valid() ? p_texture->get_rid() : RID();
	RenderingServer::get_singleton()->canvas_item_add_multimesh(canvas_item, p_multimesh->get_rid(), texture_rid);
}

void KABOOMCanvasItem::draw_string(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_text, HorizontalAlignment p_alignment = HORIZONTAL_ALIGNMENT_LEFT, float p_width = -1, int p_font_size = DEFAULT_FONT_SIZE, const Color &p_modulate = Color(1.0, 1.0, 1.0), BitField<TextServer::JustificationFlag> p_jst_flags = TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND, TextServer::Direction p_direction = TextServer::DIRECTION_AUTO, TextServer::Orientation p_orientation = TextServer::ORIENTATION_HORIZONTAL) const {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;
	ERR_FAIL_COND(p_font.is_null());

	p_font->draw_string(canvas_item, p_pos, p_text, p_alignment, p_width, p_font_size, p_modulate, p_jst_flags, p_direction, p_orientation);
}
void KABOOMCanvasItem::draw_multiline_string(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_text, HorizontalAlignment p_alignment = HORIZONTAL_ALIGNMENT_LEFT, float p_width = -1, int p_font_size = DEFAULT_FONT_SIZE, int p_max_lines = -1, const Color &p_modulate = Color(1.0, 1.0, 1.0), BitField<TextServer::LineBreakFlag> p_brk_flags = TextServer::BREAK_MANDATORY | TextServer::BREAK_WORD_BOUND, BitField<TextServer::JustificationFlag> p_jst_flags = TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND, TextServer::Direction p_direction = TextServer::DIRECTION_AUTO, TextServer::Orientation p_orientation = TextServer::ORIENTATION_HORIZONTAL) const {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;
	ERR_FAIL_COND(p_font.is_null());

	p_font->draw_multiline_string(canvas_item, p_pos, p_text, p_alignment, p_width, p_font_size, p_max_lines, p_modulate, p_brk_flags, p_jst_flags, p_direction, p_orientation);
}

void KABOOMCanvasItem::draw_string_outline(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_text, HorizontalAlignment p_alignment = HORIZONTAL_ALIGNMENT_LEFT, float p_width = -1, int p_font_size = DEFAULT_FONT_SIZE, int p_size = 1, const Color &p_modulate = Color(1.0, 1.0, 1.0), BitField<TextServer::JustificationFlag> p_jst_flags = TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND, TextServer::Direction p_direction = TextServer::DIRECTION_AUTO, TextServer::Orientation p_orientation = TextServer::ORIENTATION_HORIZONTAL) const {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;
	ERR_FAIL_COND(p_font.is_null());

	p_font->draw_string_outline(canvas_item, p_pos, p_text, p_alignment, p_width, p_font_size, p_size, p_modulate, p_jst_flags, p_direction, p_orientation);
}
void KABOOMCanvasItem::draw_multiline_string_outline(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_text, HorizontalAlignment p_alignment = HORIZONTAL_ALIGNMENT_LEFT, float p_width = -1, int p_font_size = DEFAULT_FONT_SIZE, int p_max_lines = -1, int p_size = 1, const Color &p_modulate = Color(1.0, 1.0, 1.0), BitField<TextServer::LineBreakFlag> p_brk_flags = TextServer::BREAK_MANDATORY | TextServer::BREAK_WORD_BOUND, BitField<TextServer::JustificationFlag> p_jst_flags = TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND, TextServer::Direction p_direction = TextServer::DIRECTION_AUTO, TextServer::Orientation p_orientation = TextServer::ORIENTATION_HORIZONTAL) const {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;
	ERR_FAIL_COND(p_font.is_null());

	p_font->draw_multiline_string_outline(canvas_item, p_pos, p_text, p_alignment, p_width, p_font_size, p_max_lines, p_size, p_modulate, p_brk_flags, p_jst_flags, p_direction, p_orientation);
}

void KABOOMCanvasItem::draw_char(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_char, int p_font_size = DEFAULT_FONT_SIZE, const Color &p_modulate = Color(1.0, 1.0, 1.0)) const {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;
	ERR_FAIL_COND(p_char.length() != 1);
	ERR_FAIL_COND(p_font.is_null());

	p_font->draw_char(canvas_item, p_pos, p_char[0], p_font_size, p_modulate);
}
void KABOOMCanvasItem::draw_char_outline(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_char, int p_font_size = DEFAULT_FONT_SIZE, int p_size = 1, const Color &p_modulate = Color(1.0, 1.0, 1.0)) const {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;
	ERR_FAIL_COND(p_char.length() != 1);
	ERR_FAIL_COND(p_font.is_null());

	p_font->draw_char_outline(canvas_item, p_pos, p_char[0], p_font_size, p_size, p_modulate);
}

void KABOOMCanvasItem::draw_set_transform(const Point2 &p_offset, real_t p_rot = 0.0, const Size2 &p_scale = Size2(1.0, 1.0)) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	Transform2D xform(p_rot, p_offset);
	xform.scale_basis(p_scale);
	RenderingServer::get_singleton()->canvas_item_add_set_transform(canvas_item, xform);
}
void KABOOMCanvasItem::draw_set_transform_matrix(const Transform2D &p_matrix) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	RenderingServer::get_singleton()->canvas_item_add_set_transform(canvas_item, p_matrix);
}
void KABOOMCanvasItem::draw_animation_slice(double p_animation_length, double p_slice_begin, double p_slice_end, double p_offset = 0) {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	RenderingServer::get_singleton()->canvas_item_add_animation_slice(canvas_item, p_animation_length, p_slice_begin, p_slice_end, p_offset);
}
void KABOOMCanvasItem::draw_end_animation() {
	ERR_THREAD_GUARD;
	ERR_DRAW_GUARD;

	RenderingServer::get_singleton()->canvas_item_add_animation_slice(canvas_item, 1, 0, 2, 0);
}

#pragma endregion

#pragma region Spatial

Transform2D KABOOMCanvasItem::get_global_transform() const {
	ERR_READ_THREAD_GUARD_V(Transform2D());
	if (canvas_layer) {
		return canvas_layer->get_final_transform() * get_global_transform();
	} else if (is_inside_tree()) {
		return get_viewport()->get_canvas_transform() * get_global_transform();
	} else {
		return get_global_transform();
	}
}
Transform2D KABOOMCanvasItem::get_global_transform_const() const {
	ERR_READ_THREAD_GUARD_V(Transform2D());
	ERR_FAIL_COND_V(!is_inside_tree(), Transform2D());
	return get_viewport()->get_final_transform() * get_global_transform_with_canvas();
	// return get_viewport()->get_popup_base_transform() * get_global_transform_with_canvas();
}
Transform2D KABOOMCanvasItem::get_global_transform_with_canvas() const {
	ERR_READ_THREAD_GUARD_V(Transform2D());
	if (canvas_layer) {
		return canvas_layer->get_final_transform() * get_global_transform();
	} else if (is_inside_tree()) {
		return get_viewport()->get_canvas_transform() * get_global_transform();
	} else {
		return get_global_transform();
	}
}
Transform2D KABOOMCanvasItem::get_screen_transform() const {
	ERR_READ_THREAD_GUARD_V(Transform2D());
	ERR_FAIL_COND_V(!is_inside_tree(), Transform2D());
	return get_viewport()->get_screen_transform() * get_global_transform_with_canvas();
}

void KABOOMCanvasItem::set_block_transform_notify(bool p_enable) {
	ERR_THREAD_GUARD;
	block_transform_notify = p_enable;
}
bool KABOOMCanvasItem::is_block_transform_notify_enabled() const {
	ERR_READ_THREAD_GUARD_V(false);
	return block_transform_notify;
}

Transform2D KABOOMCanvasItem::get_canvas_transform() const {
	ERR_READ_THREAD_GUARD_V(Transform2D());
	ERR_FAIL_COND_V(!is_inside_tree(), Transform2D());

	if (canvas_layer) {
		return canvas_layer->get_final_transform();
	} else if (Object::cast_to<KABOOMCanvasItem>(get_parent())) {
		return Object::cast_to<KABOOMCanvasItem>(get_parent())->get_canvas_transform();
	} else {
		return get_viewport()->get_canvas_transform();
	}
}
Transform2D KABOOMCanvasItem::get_viewport_transform() const {
	ERR_READ_THREAD_GUARD_V(Transform2D());
	ERR_FAIL_COND_V(!is_inside_tree(), Transform2D());

	if (canvas_layer) {
		return get_viewport()->get_final_transform() * canvas_layer->get_final_transform();
	} else {
		return get_viewport()->get_final_transform() * get_viewport()->get_canvas_transform();
	}
}

Vector2 KABOOMCanvasItem::make_canvas_position_local(const Vector2 &screen_point) const {
	ERR_READ_THREAD_GUARD_V(Vector2());
	ERR_FAIL_COND_V(!is_inside_tree(), screen_point);

	Transform2D local_matrix = (get_canvas_transform() * get_global_transform()).affine_inverse();

	return local_matrix.xform(screen_point);
}

Vector2 KABOOMCanvasItem::get_global_mouse_position() const {
	ERR_READ_THREAD_GUARD_V(Vector2());
	ERR_FAIL_NULL_V(get_viewport(), Vector2());
	return get_canvas_transform().affine_inverse().xform(get_viewport()->get_mouse_position());
}
Vector2 KABOOMCanvasItem::get_local_mouse_position() const {
	ERR_READ_THREAD_GUARD_V(Vector2());
	ERR_FAIL_NULL_V(get_viewport(), Vector2());

	return get_global_transform().affine_inverse().xform(get_global_mouse_position());
}

void KABOOMCanvasItem::set_notify_local_transform(bool p_enable) {
	ERR_THREAD_GUARD;
	notify_local_transform = p_enable;
}
bool KABOOMCanvasItem::is_local_transform_notification_enabled() const {
	ERR_READ_THREAD_GUARD_V(false);
	return notify_local_transform;
}

void KABOOMCanvasItem::set_notify_transform(bool p_enable) {
	ERR_THREAD_GUARD;
	if (notify_transform == p_enable) {
		return;
	}

	notify_transform = p_enable;

	if (notify_transform && is_inside_tree()) {
		// This ensures that invalid globals get resolved, so notifications can be received.
		// _ALLOW_DISCARD_ get_global_transform();
		get_global_transform();
	}
}
bool KABOOMCanvasItem::is_transform_notification_enabled() const {
	ERR_READ_THREAD_GUARD_V(false);
	return notify_transform;
}

void KABOOMCanvasItem::force_update_transform() {
	ERR_THREAD_GUARD;
	ERR_FAIL_COND(!is_inside_tree());
	if (!xform_change.in_list()) {
		return;
	}

	// get_tree()->xform_change_list.remove(&xform_change);

	notification(NOTIFICATION_TRANSFORM_CHANGED);
}

#pragma endregion

#pragma region Inputs

Ref<InputEvent> KABOOMCanvasItem::make_input_local(const Ref<InputEvent> &p_event) const {
	ERR_READ_THREAD_GUARD_V(Ref<InputEvent>());
	ERR_FAIL_COND_V(p_event.is_null(), p_event);
	ERR_FAIL_COND_V(!is_inside_tree(), p_event);

	return p_event->xformed_by((get_canvas_transform() * get_global_transform()).affine_inverse());
}

#pragma endregion

#pragma region Warnings

// PackedStringArray get_configuration_warnings() const override;
PackedStringArray KABOOMCanvasItem::get_configuration_warnings() const {
	PackedStringArray warnings = Node::_get_configuration_warnings();

	if (clip_children_mode != CLIP_CHILDREN_DISABLED && is_inside_tree()) {
		bool warned_about_ancestor_clipping = false;
		bool warned_about_canvasgroup_ancestor = false;
		Node *n = get_parent();
		while (n) {
			KABOOMCanvasItem *as_canvas_item = Object::cast_to<KABOOMCanvasItem>(n);
			if (!warned_about_ancestor_clipping && as_canvas_item && as_canvas_item->clip_children_mode != CLIP_CHILDREN_DISABLED) {
				warnings.push_back(vformat(RTR("Ancestor \"%s\" clips its children, so this node will not be able to clip its children."), as_canvas_item->get_name()));
				warned_about_ancestor_clipping = true;
			}

			CanvasGroup *as_canvas_group = Object::cast_to<CanvasGroup>(n);
			if (!warned_about_canvasgroup_ancestor && as_canvas_group) {
				warnings.push_back(vformat(RTR("Ancestor \"%s\" is a CanvasGroup, so this node will not be able to clip its children."), as_canvas_group->get_name()));
				warned_about_canvasgroup_ancestor = true;
			}

			// Only break out early once both warnings have been triggered, so
			// that the user is aware of both possible reasons for clipping not working.
			if (warned_about_ancestor_clipping && warned_about_canvasgroup_ancestor) {
				break;
			}
			n = n->get_parent();
		}
	}

	return warnings;
}

#pragma endregion

#pragma region RID Return Functions

RID KABOOMCanvasItem::get_viewport_rid() const {
	ERR_READ_THREAD_GUARD_V(RID());
	ERR_FAIL_COND_V(!is_inside_tree(), RID());
	return get_viewport()->get_viewport_rid();
}
RID KABOOMCanvasItem::get_canvas() const {
	ERR_READ_THREAD_GUARD_V(RID());
	ERR_FAIL_COND_V(!is_inside_tree(), RID());

	if (canvas_layer) {
		return canvas_layer->get_canvas();
	} else {
		return get_viewport()->find_world_2d()->get_canvas();
	}
}

#pragma endregion

#pragma region KABOOMCanvasItem Return Functions

#pragma region Static Functions
KABOOMCanvasItem *KABOOMCanvasItem::get_current_item_drawn() {
	return current_item_drawn;
}
#pragma endregion

KABOOMCanvasItem *KABOOMCanvasItem::get_parent_item() const {
	ERR_READ_THREAD_GUARD_V(nullptr);
	if (top_level) {
		return nullptr;
	}

	return Object::cast_to<KABOOMCanvasItem>(get_parent());
}

#pragma endregion

#pragma region Rect2 Return Functions

Rect2 KABOOMCanvasItem::get_viewport_rect() const {
	ERR_READ_THREAD_GUARD_V(Rect2());
	ERR_FAIL_COND_V(!is_inside_tree(), Rect2());
	return get_viewport()->get_visible_rect();
}

#pragma endregion

#pragma region World2D Return Functions

Ref<World2D> KABOOMCanvasItem::get_world_2d() const {
	ERR_READ_THREAD_GUARD_V(Ref<World2D>());
	ERR_FAIL_COND_V(!is_inside_tree(), Ref<World2D>());

	KABOOMCanvasItem *tl = get_top_level();

	if (tl->get_viewport()) {
		return tl->get_viewport()->find_world_2d();
	} else {
		return Ref<World2D>();
	}
}

#pragma endregion

#pragma region ObjectID Return Functions

ObjectID KABOOMCanvasItem::get_canvas_layer_instance_id() const {
	ERR_READ_THREAD_GUARD_V(ObjectID());
	if (canvas_layer) {
		return ObjectID(canvas_layer->get_instance_id());
	} else {
		return ObjectID();
	}
}

#pragma endregion

#pragma endregion

#pragma endregion
