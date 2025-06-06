#pragma region Main

#pragma once

// #include <godot_cpp/classes/canvas_item.hpp>
#include <godot_cpp/classes/node.hpp>

#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/text_server.hpp>
#include <godot_cpp/classes/text_server_manager.hpp>
#include <godot_cpp/classes/translation_server.hpp>

#include <godot_cpp/classes/atlas_texture.hpp>
#include <godot_cpp/classes/canvas_group.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/font.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/material.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/multi_mesh.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/style_box.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/world2d.hpp>

#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/theme_db.hpp>

#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/self_list.hpp>

#include <godot_cpp/variant/rid.hpp>
#include <godot_cpp/variant/transform2d.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/variant/char_string.hpp>
#include <godot_cpp/variant/packed_color_array.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>

#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/builtin_ptrcall.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/engine_ptrcall.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/core/method_bind.hpp>
#include <godot_cpp/core/method_ptrcall.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/object_id.hpp>
#include <godot_cpp/core/property_info.hpp>

using namespace godot;

// #define ERR_THREAD_GUARD
// 	if (OS::get_singleton()->get_main_thread_id() != OS::get_singleton()->get_thread_caller_id()) {
// 		ERR_PRINT("Thread check failed: not in main thread.");
// 		return;
// 	}
// #define ERR_THREAD_GUARD_V(m_ret)
// 	if (OS::get_singleton()->get_main_thread_id() != OS::get_singleton()->get_thread_caller_id()) {
// 		ERR_PRINT("Thread check failed: not in main thread.");
// 		return m_ret;
// 	}

#define GDPRINT(p_arg1) \
	UtilityFunctions::print(p_arg1)

#define ERR_DRAW_GUARD \
	ERR_FAIL_COND_MSG(!drawing, "Drawing is only allowed inside this node's `_draw()`, functions connected to its `draw` signal, or when it receives NOTIFICATION_DRAW.")
// #ifdef DEBUG_ENABLED
// #define ERR_THREAD_GUARD ERR_FAIL_COND_MSG(!is_accessible_from_caller_thread(), vformat("Caller thread can't call this function in this node (%s). Use call_deferred() or call_thread_group() instead.", get_description()));
// #define ERR_THREAD_GUARD_V(m_ret) ERR_FAIL_COND_V_MSG(!is_accessible_from_caller_thread(), (m_ret), vformat("Caller thread can't call this function in this node (%s). Use call_deferred() or call_thread_group() instead.", get_description()));
// #define ERR_MAIN_THREAD_GUARD ERR_FAIL_COND_MSG(is_inside_tree() && !is_current_thread_safe_for_nodes(), vformat("This function in this node (%s) can only be accessed from the main thread. Use call_deferred() instead.", get_description()));
// #define ERR_MAIN_THREAD_GUARD_V(m_ret) ERR_FAIL_COND_V_MSG(is_inside_tree() && !is_current_thread_safe_for_nodes(), (m_ret), vformat("This function in this node (%s) can only be accessed from the main thread. Use call_deferred() instead.", get_description()));
// #define ERR_READ_THREAD_GUARD ERR_FAIL_COND_MSG(!is_readable_from_caller_thread(), vformat("This function in this node (%s) can only be accessed from either the main thread or a thread group. Use call_deferred() instead.", get_description()));
// #define ERR_READ_THREAD_GUARD_V(m_ret) ERR_FAIL_COND_V_MSG(!is_readable_from_caller_thread(), (m_ret), vformat("This function in this node (%s) can only be accessed from either the main thread or a thread group. Use call_deferred() instead.", get_description()));
// #else
#define ERR_THREAD_GUARD
#define ERR_THREAD_GUARD_V(m_ret)
#define ERR_MAIN_THREAD_GUARD
#define ERR_MAIN_THREAD_GUARD_V(m_ret)
#define ERR_READ_THREAD_GUARD
#define ERR_READ_THREAD_GUARD_V(m_ret)
// #endif

class KABOOMCanvasItem : public Node {
	GDCLASS(KABOOMCanvasItem, Node);

	friend class CanvasLayer;
#pragma region Script API

#pragma region Godot Bindings

protected:
	static void _bind_methods();

#pragma endregion

#pragma region Protected Properties and Types

	union MTFlag {
		SafeFlag mt;
		bool st;
		MTFlag() :
				mt{} {}
	};
	// template <typename T>
	// union MTNumeric {
	// 	SafeNumeric<T> mt;
	// 	T st;
	// 	MTNumeric() :
	// 			mt{} {}
	// };

#pragma endregion

#pragma region Public Properties and Types

public:
#pragma region Static Properties

	static constexpr int DEFAULT_FONT_SIZE = 16;

#pragma endregion

#pragma region Enums

	enum {
		NOTIFICATION_TRANSFORM_CHANGED = 2000, //unique
		NOTIFICATION_DRAW = 30,
		NOTIFICATION_VISIBILITY_CHANGED = 31,
		NOTIFICATION_ENTER_CANVAS = 32,
		NOTIFICATION_EXIT_CANVAS = 33,
		NOTIFICATION_LOCAL_TRANSFORM_CHANGED = 35,
		NOTIFICATION_WORLD_2D_CHANGED = 36,
	};

	enum TextureFilter {
		TEXTURE_FILTER_PARENT_NODE,
		TEXTURE_FILTER_NEAREST,
		TEXTURE_FILTER_LINEAR,
		TEXTURE_FILTER_NEAREST_WITH_MIPMAPS,
		TEXTURE_FILTER_LINEAR_WITH_MIPMAPS,
		TEXTURE_FILTER_NEAREST_WITH_MIPMAPS_ANISOTROPIC,
		TEXTURE_FILTER_LINEAR_WITH_MIPMAPS_ANISOTROPIC,
		TEXTURE_FILTER_MAX
	};

	enum TextureRepeat {
		TEXTURE_REPEAT_PARENT_NODE,
		TEXTURE_REPEAT_DISABLED,
		TEXTURE_REPEAT_ENABLED,
		TEXTURE_REPEAT_MIRROR,
		TEXTURE_REPEAT_MAX,
	};

	enum ClipChildrenMode {
		CLIP_CHILDREN_DISABLED,
		CLIP_CHILDREN_ONLY,
		CLIP_CHILDREN_AND_DRAW,
		CLIP_CHILDREN_MAX,
	};

#pragma endregion

#pragma endregion

#pragma region Private Properties

private:
#pragma region Static

	static KABOOMCanvasItem *current_item_drawn;

#pragma endregion

#pragma region Misc

	mutable SelfList<Node>
			xform_change;

	StringName canvas_group;

	List<KABOOMCanvasItem *> children_items;
	List<KABOOMCanvasItem *>::Element *C = nullptr;

	Window *window = nullptr;

#pragma endregion

#pragma region Blocking
	int _block_count = 0;
#pragma endregion

#pragma region Visibility

	bool visible = true;

	Color modulate = Color(1, 1, 1, 1);
	Color self_modulate = Color(1, 1, 1, 1);

	bool parent_visible_in_tree = false;
	bool pending_update = false;
	bool top_level = false;
	bool drawing = false;
	bool block_transform_notify = false;
	bool behind = false;
	bool use_parent_material = false;
	bool notify_local_transform = false;
	bool notify_transform = false;
	bool hide_clip_children = false;

	ClipChildrenMode clip_children_mode = CLIP_CHILDREN_DISABLED;

	int light_mask = 1;
	uint32_t visibility_layer = 1;

#pragma endregion

#pragma region Ordering

	int z_index = 0;
	bool z_relative = true;
	bool y_sort_enabled = false;

#pragma endregion

#pragma region CanvasLayer

	CanvasLayer *canvas_layer = nullptr;

#pragma endregion

#pragma region RIDs

	RID canvas_item;

#pragma endregion

#pragma region Texture

	mutable RenderingServer::CanvasItemTextureFilter texture_filter_cache = RenderingServer::CANVAS_ITEM_TEXTURE_FILTER_LINEAR;
	mutable RenderingServer::CanvasItemTextureRepeat texture_repeat_cache = RenderingServer::CANVAS_ITEM_TEXTURE_REPEAT_DISABLED;
	TextureFilter texture_filter = TEXTURE_FILTER_PARENT_NODE;
	TextureRepeat texture_repeat = TEXTURE_REPEAT_PARENT_NODE;

#pragma endregion

#pragma region Material

	Ref<Material> material;
	mutable HashMap<StringName, Variant> instance_shader_parameters;
	mutable HashMap<StringName, StringName> instance_shader_parameter_property_remap;

#pragma endregion

#pragma region Transform

	mutable Transform2D global_transform;

#pragma endregion

#pragma region Global Invalid Flags

	mutable MTFlag global_invalid;

#pragma endregion

#pragma endregion

#pragma region Private Functions

#pragma region Global Invalid Flag Functions

	_FORCE_INLINE_ bool _is_global_invalid() const { return get_process_thread_group() ? global_invalid.mt.is_set() : global_invalid.st; }
	void _set_global_invalid(bool p_invalid) const;

#pragma endregion

#pragma region Blocking

	void _block();
	void _unblock();
	bool _is_blocked() const;

#pragma endregion

#pragma region Drawing

	void _redraw_callback();

#pragma endregion

#pragma region Visibility

	void _top_level_raise_self();

	void _propagate_visibility_changed(bool p_parent_visible_in_tree);
	void _handle_visibility_change(bool p_visible);

	virtual void _top_level_changed();
	virtual void _top_level_changed_on_parent();

	void _window_visibility_changed();

#pragma endregion

#pragma region Misc

	void _enter_canvas();
	void _exit_canvas();

	// virtual void _physics_interpolated_changed() override;
	virtual void _physics_interpolated_changed();

	friend class Viewport;
	void _refresh_texture_repeat_cache() const;
	void _update_texture_repeat_changed(bool p_propagate);
	void _refresh_texture_filter_cache() const;
	void _update_texture_filter_changed(bool p_propagate);

	const StringName *_instance_shader_parameter_get_remap(const StringName &p_name) const;

#pragma endregion

#pragma region Transform

	void _notify_transform(KABOOMCanvasItem *p_node);

	void _notify_transform_deferred();

#pragma endregion

#pragma endregion

#pragma region Protected Functions

protected:
#pragma region Misc

	bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
	void _get_property_list(List<PropertyInfo> *p_list) const;

	virtual void _update_self_texture_repeat(RenderingServer::CanvasItemTextureRepeat p_texture_repeat);
	virtual void _update_self_texture_filter(RenderingServer::CanvasItemTextureFilter p_texture_filter);

	_FORCE_INLINE_ void _notify_transform() {
		if (is_inside_tree() && !block_transform_notify && notify_local_transform) {
			notification(NOTIFICATION_LOCAL_TRANSFORM_CHANGED);
		}
	}

	void item_rect_changed(bool p_size_changed = true);

	void set_canvas_item_use_identity_transform(bool p_enable);

	void _notification(int p_what);

	void _validate_property(PropertyInfo &p_property) const;

	_FORCE_INLINE_ void set_hide_clip_children(bool p_value) { hide_clip_children = p_value; }

#pragma endregion

#pragma region Virtual Godot Functions

	GDVIRTUAL0(_draw)

#pragma endregion

#pragma endregion

#pragma region Public Functions

public:
#ifdef TOOLS_ENABLED
	// Save and restore a KABOOMCanvasItem state
	virtual void _edit_set_state(const Dictionary &p_state) {}
	virtual Dictionary _edit_get_state() const { return Dictionary(); }

	// Used to move the node
	virtual void _edit_set_position(const Point2 &p_position) = 0;
	virtual Point2 _edit_get_position() const = 0;

	// Used to scale the node
	virtual void _edit_set_scale(const Size2 &p_scale) = 0;
	virtual Size2 _edit_get_scale() const = 0;

	// Used to rotate the node
	virtual bool _edit_use_rotation() const { return false; }
	virtual void _edit_set_rotation(real_t p_rotation) {}
	virtual real_t _edit_get_rotation() const { return 0.0; }

	// Used to resize/move the node
	virtual void _edit_set_rect(const Rect2 &p_rect) {}
	virtual Size2 _edit_get_minimum_size() const { return Size2(-1, -1); } // LOOKS WEIRD

	// Used to set a pivot
	virtual bool _edit_use_pivot() const { return false; }
	virtual void _edit_set_pivot(const Point2 &p_pivot) {}
	virtual Point2 _edit_get_pivot() const { return Point2(); }

	virtual Transform2D _edit_get_transform() const;
#endif // TOOLS_ENABLED

#ifdef DEBUG_ENABLED
	// Those need to be available in debug runtime, to allow for node selection.

	// Select the node.
	virtual bool _edit_is_selected_on_click(const Point2 &p_point, double p_tolerance) const;

	// Used to resize/move the node.
	virtual bool _edit_use_rect() const { return false; } // Maybe replace with _edit_get_editmode().
	virtual Rect2 _edit_get_rect() const { return Rect2(0, 0, 0, 0); }
#endif // DEBUG_ENABLED

#pragma region Lifecycle

	KABOOMCanvasItem();
	~KABOOMCanvasItem();

#pragma endregion

#pragma region Node Overriden Function

	void add_child(Node *p_node, bool p_force_readable_name = false, Node::InternalMode p_internal = Node::INTERNAL_MODE_DISABLED);
	void add_sibling(Node *p_sibling, bool p_force_readable_name = false);
	void remove_child(Node *p_node);
	void move_child(Node *p_child_node, int p_to_index);

#pragma endregion

#pragma region Visibility

	void set_visible(bool p_visible);
	bool is_visible() const;
	bool is_visible_in_tree() const;

	void show();
	void hide();
	void move_to_front();

	void set_visibility_layer(uint32_t p_visibility_layer);
	uint32_t get_visibility_layer() const;

	void set_visibility_layer_bit(uint32_t p_visibility_layer, bool p_enable);
	bool get_visibility_layer_bit(uint32_t p_visibility_layer) const;

#pragma region Top Level API

	void set_as_top_level(bool p_top_level);
	bool is_set_as_top_level() const;

	void set_draw_behind_parent(bool p_enable);
	bool is_draw_behind_parent_enabled() const;
	KABOOMCanvasItem *get_top_level() const;

#pragma endregion

#pragma region Light Mask API

	virtual void set_light_mask(int p_light_mask);
	int get_light_mask() const;

#pragma endregion

#pragma region Clipping API

	void set_clip_children_mode(ClipChildrenMode p_clip_mode);

	ClipChildrenMode get_clip_children_mode() const;

#pragma endregion

#pragma region Modulation API

	void set_modulate(const Color &p_modulate);
	Color get_modulate() const;
	Color get_modulate_in_tree() const;

	virtual void set_self_modulate(const Color &p_self_modulate);
	Color get_self_modulate() const;

#pragma endregion

#pragma endregion

#pragma region Ordering

	virtual void set_z_index(int p_z);
	int get_z_index() const;
	int get_effective_z_index() const;

	void set_z_as_relative(bool p_enabled);
	bool is_z_relative() const;

	virtual void set_y_sort_enabled(bool p_enabled);
	virtual bool is_y_sort_enabled() const;

#pragma endregion

#pragma region Texture

	virtual void set_texture_filter(TextureFilter p_texture_filter);
	TextureFilter get_texture_filter() const;
	TextureFilter get_texture_filter_in_tree() const;

	virtual void set_texture_repeat(TextureRepeat p_texture_repeat);
	TextureRepeat get_texture_repeat() const;
	TextureRepeat get_texture_repeat_in_tree() const;

#pragma endregion

#pragma region Material

	virtual void set_material(const Ref<Material> &p_material);
	Ref<Material> get_material() const;

	virtual void set_use_parent_material(bool p_use_parent_material);
	bool get_use_parent_material() const;

	void set_instance_shader_parameter(const StringName &p_name, const Variant &p_value);
	Variant get_instance_shader_parameter(const StringName &p_name) const;

#pragma endregion

#pragma region CanvasLayer Functions

	int get_canvas_layer() const;
	CanvasLayer *get_canvas_layer_node() const;

#pragma endregion

#pragma region Drawing
	void update_draw_order();

	void queue_redraw();

	void draw_dashed_line(const Point2 &p_from, const Point2 &p_to, const Color &p_color, real_t p_width = -1.0, real_t p_dash = 2.0, bool p_aligned = true, bool p_antialiased = false);
	void draw_line(const Point2 &p_from, const Point2 &p_to, const Color &p_color, real_t p_width = -1.0, bool p_antialiased = false);
	void draw_polyline(const PackedVector2Array &p_points, const Color &p_color, real_t p_width = -1.0, bool p_antialiased = false);
	void draw_polyline_colors(const PackedVector2Array &p_points, const PackedColorArray &p_colors, real_t p_width = -1.0, bool p_antialiased = false);
	void draw_arc(const Vector2 &p_center, real_t p_radius, real_t p_start_angle, real_t p_end_angle, int p_point_count, const Color &p_color, real_t p_width = -1.0, bool p_antialiased = false);
	void draw_multiline(const PackedVector2Array &p_points, const Color &p_color, real_t p_width = -1.0, bool p_antialiased = false);
	void draw_multiline_colors(const PackedVector2Array &p_points, const PackedColorArray &p_colors, real_t p_width = -1.0, bool p_antialiased = false);
	void draw_rect(const Rect2 &p_rect, const Color &p_color, bool p_filled = true, real_t p_width = -1.0, bool p_antialiased = false);
	void draw_circle(const Point2 &p_pos, real_t p_radius, const Color &p_color, bool p_filled = true, real_t p_width = -1.0, bool p_antialiased = false);
	void draw_texture(const Ref<Texture2D> &p_texture, const Point2 &p_pos, const Color &p_modulate = Color(1, 1, 1, 1));
	void draw_texture_rect(const Ref<Texture2D> &p_texture, const Rect2 &p_rect, bool p_tile = false, const Color &p_modulate = Color(1, 1, 1), bool p_transpose = false);
	void draw_texture_rect_region(const Ref<Texture2D> &p_texture, const Rect2 &p_rect, const Rect2 &p_src_rect, const Color &p_modulate = Color(1, 1, 1), bool p_transpose = false, bool p_clip_uv = false);
	void draw_msdf_texture_rect_region(const Ref<Texture2D> &p_texture, const Rect2 &p_rect, const Rect2 &p_src_rect, const Color &p_modulate = Color(1, 1, 1), double p_outline = 0.0, double p_pixel_range = 4.0, double p_scale = 1.0);
	void draw_lcd_texture_rect_region(const Ref<Texture2D> &p_texture, const Rect2 &p_rect, const Rect2 &p_src_rect, const Color &p_modulate = Color(1, 1, 1));
	void draw_style_box(const Ref<StyleBox> &p_style_box, const Rect2 &p_rect);
	void draw_primitive(const PackedVector2Array &p_points, const PackedColorArray &p_colors, const PackedVector2Array &p_uvs, Ref<Texture2D> p_texture = Ref<Texture2D>());
	void draw_polygon(const PackedVector2Array &p_points, const PackedColorArray &p_colors, const PackedVector2Array &p_uvs = PackedVector2Array(), Ref<Texture2D> p_texture = Ref<Texture2D>());
	void draw_colored_polygon(const PackedVector2Array &p_points, const Color &p_color, const PackedVector2Array &p_uvs = PackedVector2Array(), Ref<Texture2D> p_texture = Ref<Texture2D>());

	void draw_mesh(const Ref<Mesh> &p_mesh, const Ref<Texture2D> &p_texture, const Transform2D &p_transform = Transform2D(), const Color &p_modulate = Color(1, 1, 1));
	void draw_multimesh(const Ref<MultiMesh> &p_multimesh, const Ref<Texture2D> &p_texture);

	// void draw_string(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_text, HorizontalAlignment p_alignment = HORIZONTAL_ALIGNMENT_LEFT, float p_width = -1, int p_font_size = DEFAULT_FONT_SIZE, const Color &p_modulate = Color(1.0, 1.0, 1.0), BitField<TextServer::JustificationFlag> p_jst_flags = TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND, TextServer::Direction p_direction = TextServer::DIRECTION_AUTO, TextServer::Orientation p_orientation = TextServer::ORIENTATION_HORIZONTAL, float p_oversampling = 0.0) const;
	void draw_string(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_text, HorizontalAlignment p_alignment = HORIZONTAL_ALIGNMENT_LEFT, float p_width = -1, int p_font_size = DEFAULT_FONT_SIZE, const Color &p_modulate = Color(1.0, 1.0, 1.0), BitField<TextServer::JustificationFlag> p_jst_flags = TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND, TextServer::Direction p_direction = TextServer::DIRECTION_AUTO, TextServer::Orientation p_orientation = TextServer::ORIENTATION_HORIZONTAL) const;
	// void draw_multiline_string(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_text, HorizontalAlignment p_alignment = HORIZONTAL_ALIGNMENT_LEFT, float p_width = -1, int p_font_size = DEFAULT_FONT_SIZE, int p_max_lines = -1, const Color &p_modulate = Color(1.0, 1.0, 1.0), BitField<TextServer::LineBreakFlag> p_brk_flags = TextServer::BREAK_MANDATORY | TextServer::BREAK_WORD_BOUND, BitField<TextServer::JustificationFlag> p_jst_flags = TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND, TextServer::Direction p_direction = TextServer::DIRECTION_AUTO, TextServer::Orientation p_orientation = TextServer::ORIENTATION_HORIZONTAL, float p_oversampling = 0.0) const;
	void draw_multiline_string(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_text, HorizontalAlignment p_alignment = HORIZONTAL_ALIGNMENT_LEFT, float p_width = -1, int p_font_size = DEFAULT_FONT_SIZE, int p_max_lines = -1, const Color &p_modulate = Color(1.0, 1.0, 1.0), BitField<TextServer::LineBreakFlag> p_brk_flags = TextServer::BREAK_MANDATORY | TextServer::BREAK_WORD_BOUND, BitField<TextServer::JustificationFlag> p_jst_flags = TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND, TextServer::Direction p_direction = TextServer::DIRECTION_AUTO, TextServer::Orientation p_orientation = TextServer::ORIENTATION_HORIZONTAL) const;

	// void draw_string_outline(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_text, HorizontalAlignment p_alignment = HORIZONTAL_ALIGNMENT_LEFT, float p_width = -1, int p_font_size = DEFAULT_FONT_SIZE, int p_size = 1, const Color &p_modulate = Color(1.0, 1.0, 1.0), BitField<TextServer::JustificationFlag> p_jst_flags = TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND, TextServer::Direction p_direction = TextServer::DIRECTION_AUTO, TextServer::Orientation p_orientation = TextServer::ORIENTATION_HORIZONTAL, float p_oversampling = 0.0) const;
	void draw_string_outline(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_text, HorizontalAlignment p_alignment = HORIZONTAL_ALIGNMENT_LEFT, float p_width = -1, int p_font_size = DEFAULT_FONT_SIZE, int p_size = 1, const Color &p_modulate = Color(1.0, 1.0, 1.0), BitField<TextServer::JustificationFlag> p_jst_flags = TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND, TextServer::Direction p_direction = TextServer::DIRECTION_AUTO, TextServer::Orientation p_orientation = TextServer::ORIENTATION_HORIZONTAL) const;
	// void draw_multiline_string_outline(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_text, HorizontalAlignment p_alignment = HORIZONTAL_ALIGNMENT_LEFT, float p_width = -1, int p_font_size = DEFAULT_FONT_SIZE, int p_max_lines = -1, int p_size = 1, const Color &p_modulate = Color(1.0, 1.0, 1.0), BitField<TextServer::LineBreakFlag> p_brk_flags = TextServer::BREAK_MANDATORY | TextServer::BREAK_WORD_BOUND, BitField<TextServer::JustificationFlag> p_jst_flags = TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND, TextServer::Direction p_direction = TextServer::DIRECTION_AUTO, TextServer::Orientation p_orientation = TextServer::ORIENTATION_HORIZONTAL, float p_oversampling = 0.0) const;
	void draw_multiline_string_outline(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_text, HorizontalAlignment p_alignment = HORIZONTAL_ALIGNMENT_LEFT, float p_width = -1, int p_font_size = DEFAULT_FONT_SIZE, int p_max_lines = -1, int p_size = 1, const Color &p_modulate = Color(1.0, 1.0, 1.0), BitField<TextServer::LineBreakFlag> p_brk_flags = TextServer::BREAK_MANDATORY | TextServer::BREAK_WORD_BOUND, BitField<TextServer::JustificationFlag> p_jst_flags = TextServer::JUSTIFICATION_KASHIDA | TextServer::JUSTIFICATION_WORD_BOUND, TextServer::Direction p_direction = TextServer::DIRECTION_AUTO, TextServer::Orientation p_orientation = TextServer::ORIENTATION_HORIZONTAL) const;

	// void draw_char(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_char, int p_font_size = DEFAULT_FONT_SIZE, const Color &p_modulate = Color(1.0, 1.0, 1.0), float p_oversampling = 0.0) const;
	void draw_char(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_char, int p_font_size = DEFAULT_FONT_SIZE, const Color &p_modulate = Color(1.0, 1.0, 1.0)) const;
	// void draw_char_outline(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_char, int p_font_size = DEFAULT_FONT_SIZE, int p_size = 1, const Color &p_modulate = Color(1.0, 1.0, 1.0), float p_oversampling = 0.0) const;
	void draw_char_outline(const Ref<Font> &p_font, const Point2 &p_pos, const String &p_char, int p_font_size = DEFAULT_FONT_SIZE, int p_size = 1, const Color &p_modulate = Color(1.0, 1.0, 1.0)) const;

	void draw_set_transform(const Point2 &p_offset, real_t p_rot = 0.0, const Size2 &p_scale = Size2(1.0, 1.0));
	void draw_set_transform_matrix(const Transform2D &p_matrix);
	void draw_animation_slice(double p_animation_length, double p_slice_begin, double p_slice_end, double p_offset = 0);
	void draw_end_animation();

#pragma endregion

#pragma region Spatial

	virtual Transform2D get_transform() const = 0;
	virtual Transform2D get_global_transform() const;
	virtual Transform2D get_global_transform_const() const;
	virtual Transform2D get_global_transform_with_canvas() const;
	virtual Transform2D get_screen_transform() const;

	void set_block_transform_notify(bool p_enable);
	bool is_block_transform_notify_enabled() const;

	Transform2D get_canvas_transform() const;
	Transform2D get_viewport_transform() const;

	Vector2 make_canvas_position_local(const Vector2 &screen_point) const;

	Vector2 get_global_mouse_position() const;
	Vector2 get_local_mouse_position() const;

	void set_notify_local_transform(bool p_enable);
	bool is_local_transform_notification_enabled() const;

	void set_notify_transform(bool p_enable);
	bool is_transform_notification_enabled() const;

	void force_update_transform();

#pragma endregion

#pragma region Inputs

	Ref<InputEvent> make_input_local(const Ref<InputEvent> &p_event) const;

#pragma endregion

#pragma region Warnings

	// virtual PackedStringArray get_configuration_warnings() const override;
	virtual PackedStringArray get_configuration_warnings() const;

#pragma endregion

#pragma region RID Return Functions

	_FORCE_INLINE_ RID get_canvas_item() const {
		return canvas_item;
	}

	RID get_viewport_rid() const;
	RID get_canvas() const;

#pragma endregion

#pragma region KABOOMCanvasItem Return Functions

#pragma region Static Functions
	static KABOOMCanvasItem *get_current_item_drawn();
#pragma endregion

	KABOOMCanvasItem *get_parent_item() const;

#pragma endregion

#pragma region Rect2 Return Functions

	Rect2 get_viewport_rect() const;

	// Used by control nodes to retrieve the parent's anchorable area
	virtual Rect2 get_anchorable_rect() const { return Rect2(0, 0, 0, 0); }

#pragma endregion

#pragma region World2D Return Functions

	Ref<World2D> get_world_2d() const;

#pragma endregion

#pragma region ObjectID Return Functions

	ObjectID get_canvas_layer_instance_id() const;

#pragma endregion

#pragma endregion

#pragma endregion
};

VARIANT_ENUM_CAST(KABOOMCanvasItem::TextureFilter)
VARIANT_ENUM_CAST(KABOOMCanvasItem::TextureRepeat)
VARIANT_ENUM_CAST(KABOOMCanvasItem::ClipChildrenMode)
/*

class CanvasTexture : public Texture2D {
	GDCLASS(CanvasTexture, Texture2D);
	// OBJ_SAVE_TYPE(Texture2D); // Saves derived classes with common type so they can be interchanged.

	Ref<Texture2D> diffuse_texture;
	Ref<Texture2D> normal_texture;
	Ref<Texture2D> specular_texture;
	Color specular = Color(1, 1, 1, 1);
	real_t shininess = 1.0;

	RID canvas_texture;

	KABOOMCanvasItem::TextureFilter texture_filter = KABOOMCanvasItem::TEXTURE_FILTER_PARENT_NODE;
	KABOOMCanvasItem::TextureRepeat texture_repeat = KABOOMCanvasItem::TEXTURE_REPEAT_PARENT_NODE;

protected:
	static void _bind_methods();

public:
	void set_diffuse_texture(const Ref<Texture2D> &p_diffuse);
	Ref<Texture2D> get_diffuse_texture() const;

	void set_normal_texture(const Ref<Texture2D> &p_normal);
	Ref<Texture2D> get_normal_texture() const;

	void set_specular_texture(const Ref<Texture2D> &p_specular);
	Ref<Texture2D> get_specular_texture() const;

	void set_specular_color(const Color &p_color);
	Color get_specular_color() const;

	void set_specular_shininess(real_t p_shininess);
	real_t get_specular_shininess() const;

	void set_texture_filter(KABOOMCanvasItem::TextureFilter p_filter);
	KABOOMCanvasItem::TextureFilter get_texture_filter() const;

	void set_texture_repeat(KABOOMCanvasItem::TextureRepeat p_repeat);
	KABOOMCanvasItem::TextureRepeat get_texture_repeat() const;

	// virtual int get_width() const override;
	// virtual int get_height() const override;

	// virtual bool is_pixel_opaque(int p_x, int p_y) const override;
	// virtual bool has_alpha() const override;

	// virtual Ref<Image> get_image() const override;

	// virtual RID get_rid() const override;
	virtual int get_width() const;
	virtual int get_height() const;

	virtual bool is_pixel_opaque(int p_x, int p_y) const;
	virtual bool has_alpha() const;

	virtual Ref<Image> get_image() const;

	virtual RID get_rid() const;

	CanvasTexture();
	~CanvasTexture();
};
*/

#pragma endregion