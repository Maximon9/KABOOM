#pragma once

#include <godot_cpp/classes/canvas_item.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class KABOOMCanvasItem : public CanvasItem {
	GDCLASS(KABOOMCanvasItem, CanvasItem);

public:
	KABOOMCanvasItem();
	~KABOOMCanvasItem();

protected:
	static void _bind_methods();
};