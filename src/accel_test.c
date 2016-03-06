#include <pebble.h>

Window *window;
TextLayer *text_layer;



// do something with the obtained data
static void data_handler(AccelData *data, uint32_t num_samples) {    // UNUSED
  
  // Long lived buffer
  static char s_buffer[128];

  // Compose string of all data for 3 samples
  
//   snprintf(s_buffer, sizeof(s_buffer), 
//     "N X,Y,Z\n0 %d,%d,%d\n1 %d,%d,%d\n2 %d,%d,%d", 
//     data[0].x, data[0].y, data[0].z, 
//     data[1].x, data[1].y, data[1].z, 
//     data[2].x, data[2].y, data[2].z
//   );
    
  APP_LOG(APP_LOG_LEVEL_INFO, "X:%d\t\tY:%d\t\tZ:%d\t\tTimestamp:%d", data->x, data->y, data->z, (int)data->timestamp);
  //APP_LOG(APP_LOG_LEVEL_INFO, "X:%d Y:%d Z:%d", data->x, data->y, data->z);
  // %lu is for unsigned long
  
  //Show the data
  // text_layer_set_text(s_output_layer, s_buffer); // no text layer yet?
  
  
}


static void get_data() {  
  
  uint32_t num_samples = 1;
  
  // initialize any data sent to be sent to handler, assume size num_samples?
  accel_data_service_subscribe(num_samples, data_handler); // data_handler is the method defined above
  accel_service_set_sampling_rate(ACCEL_SAMPLING_100HZ);
  
}



void init() {
	// Create a window and text layer
	window = window_create();                               // make a window
	text_layer = text_layer_create(GRect(0, 0, 144, 154));  // size of text space
	
	// Set the text, font, and text alignment
	text_layer_set_text(text_layer, "Hi, I'm a FUCKING PEBBLE!");                    // text
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD)); // font
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);                 // align
	
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));

	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");                  // literally write to the console
}

// clean up
void deinit() {
	// Destroy the text layer
	text_layer_destroy(text_layer);
	
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	init();
  get_data();
	app_event_loop();  // listen?
	deinit();
}
