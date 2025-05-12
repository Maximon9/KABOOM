#pragma once

#include <godot_cpp/classes/canvas_item.hpp>

using namespace godot;

class KABOOMControl : public CanvasItem {
	GDCLASS(KABOOMControl, CanvasItem);

protected:
	static void _bind_methods();

public:
	void test();
};