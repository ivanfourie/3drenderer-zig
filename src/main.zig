const std = @import("std");
const c = @cImport({
    @cInclude("app.h");
});

pub fn main() void {
    // Create a SDL window
    c.is_running = c.initialize_window();

    c.setup();

    // Event loop
    while (c.is_running) {
        c.process_input();
        c.update();
        c.render();
    }

    c.destroy_window();
    c.free_resources();
}
