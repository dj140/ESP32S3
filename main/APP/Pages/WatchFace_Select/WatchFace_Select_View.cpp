#include "WatchFace_Select_View.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;


WatchFace_Select_View test;

void onFaceSelected(lv_event_t* e) {}

void WatchFace_Select_View::init_face_select(lv_obj_t* par)
{
	ui_faceSelect = lv_obj_create(par);
	lv_obj_clear_flag(ui_faceSelect, LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
	lv_obj_set_width(ui_faceSelect, 300);
	lv_obj_set_height(ui_faceSelect, 320);
	lv_obj_set_align(ui_faceSelect, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(ui_faceSelect, LV_FLEX_FLOW_ROW);
	lv_obj_update_snap(ui_faceSelect, LV_ANIM_ON);
	lv_obj_set_flex_align(ui_faceSelect, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_clear_flag(ui_faceSelect, LV_OBJ_FLAG_SNAPPABLE); /// Flags
	lv_obj_set_scrollbar_mode(ui_faceSelect, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_scroll_snap_x(ui_faceSelect, LV_SCROLL_SNAP_CENTER);
	lv_obj_set_style_radius(ui_faceSelect, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_faceSelect, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_faceSelect, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_faceSelect, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	//lv_obj_set_style_border_color(ui_faceSelect, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);

	//lv_obj_set_style_outline_color(ui_faceSelect, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
	//lv_obj_set_style_outline_opa(ui_faceSelect, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	//lv_obj_set_style_outline_width(ui_faceSelect, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_pad_left(ui_faceSelect, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_faceSelect, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_faceSelect, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_faceSelect, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(ui_faceSelect, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(ui_faceSelect, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
	ui.faceSelect = ui_faceSelect;
}

void WatchFace_Select_View::addWatchface(const char* name, const void* src, int index)
{
	lv_obj_t* ui_faceItem = lv_obj_create(ui.faceSelect);
	lv_obj_set_width(ui_faceItem, 240);
	lv_obj_set_height(ui_faceItem, 300);
	lv_obj_set_align(ui_faceItem, LV_ALIGN_CENTER);
	lv_obj_clear_flag(ui_faceItem, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_add_flag(ui_faceItem, LV_OBJ_FLAG_SNAPPABLE);
	lv_obj_clear_flag(ui_faceItem, LV_OBJ_FLAG_SCROLL_ONE);
	lv_obj_set_style_radius(ui_faceItem, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_faceItem, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_faceItem, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	/*lv_obj_set_style_border_width(ui_faceItem, 3, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_border_color(ui_faceItem, lv_color_hex(0x142ABC), LV_PART_MAIN | LV_STATE_FOCUSED)*/;	//lv_obj_set_style_outline_color(ui_faceItem, lv_color_hex(0x142ABC), LV_PART_MAIN | LV_STATE_DEFAULT);
	//lv_obj_set_style_outline_opa(ui_faceItem, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	//lv_obj_set_style_outline_width(ui_faceItem, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	//lv_obj_set_style_outline_pad(ui_faceItem, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui_faceItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_faceItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_faceItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_faceItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	faces[index].watchface = ui_faceItem;

	lv_obj_t* ui_facePreview = lv_img_create(ui_faceItem);
	lv_img_set_src(ui_facePreview, src);
	lv_img_set_zoom(ui_facePreview,150);
	lv_obj_set_width(ui_facePreview, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(ui_facePreview, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(ui_facePreview, LV_ALIGN_CENTER);
	lv_obj_set_style_radius(ui_facePreview, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_border_width(ui_facePreview, 3, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_border_color(ui_facePreview, lv_color_hex(0x142ABC), LV_PART_MAIN | LV_STATE_FOCUSED);
	//lv_obj_set_style_outline_color(ui_facePreview, lv_color_hex(0x142ABC), LV_PART_MAIN | LV_STATE_DEFAULT);
	//lv_obj_set_style_outline_opa(ui_facePreview, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	//lv_obj_set_style_outline_width(ui_facePreview, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	//lv_obj_set_style_outline_pad(ui_facePreview, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_add_flag(ui_facePreview, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
	lv_obj_clear_flag(ui_facePreview, LV_OBJ_FLAG_SCROLLABLE); /// Flags


	lv_obj_t* ui_faceLabel = lv_label_create(ui_faceItem);
	lv_obj_set_width(ui_faceLabel, 160);
	lv_obj_set_height(ui_faceLabel, LV_SIZE_CONTENT); /// 1
	lv_obj_align(ui_faceLabel, LV_ALIGN_BOTTOM_MID, 0,0);
	lv_label_set_long_mode(ui_faceLabel, LV_LABEL_LONG_DOT);
	lv_label_set_text(ui_faceLabel, name);
	lv_obj_set_style_text_align(ui_faceLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_faceLabel, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_faceLabel, lv_color_white(),LV_PART_MAIN | LV_STATE_DEFAULT);
	//lv_obj_add_event_cb(ui_faceItem, ui_event_faceSelected, LV_EVENT_ALL, (void*)index);
	numFaces++;

}

void WatchFace_Select_View::Create(lv_obj_t* root)
{	
	init_face_select(root);
	addWatchface("cxk", ResourcePool::GetImage("bg_day"), 0);
	addWatchface("apple_watch", ResourcePool::GetImage("apple_watch"), 1);
	addWatchface("Default", ResourcePool::GetImage("image1"), 2);
	addWatchface("Default", ResourcePool::GetImage("image2"), 3);
	addWatchface("Default", ResourcePool::GetImage("image3"), 4);
	addWatchface("Default", ResourcePool::GetImage("watch_face2"), 5);
	addWatchface("Default", ResourcePool::GetImage("image1"), 6);
	addWatchface("Default", ResourcePool::GetImage("image1"), 7);
  
}

void WatchFace_Select_View::Delete()
{

}
