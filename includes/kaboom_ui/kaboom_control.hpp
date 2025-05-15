#pragma once

// #include "../kaboom_canvas_item.hpp"
#include <godot_cpp/classes/canvas_item.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class KABOOMControl : public CanvasItem {
	GDCLASS(KABOOMControl, CanvasItem);

public:
	KABOOMControl();
	~KABOOMControl();
	void test();

protected:
	static void _bind_methods();
};