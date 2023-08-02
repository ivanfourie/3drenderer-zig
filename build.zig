const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "3drenderer",
        .root_source_file = .{ .path = "src/main.c" },
        .target = target,
        .optimize = optimize,
    });

    // Link with SDL2
    exe.linkSystemLibrary("SDL2");
    exe.linkLibC();
    // Add all the C files in src directory
    exe.addCSourceFiles(&src_files, &.{"-Wall", "-std=c99"});

    b.installArtifact(exe);
    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}

const src_files = [_][]const u8{
    "src/array.c",
    "src/clipping.c",
    "src/light.c",
    "src/matrix.c",
    "src/swap.c",
    "src/triangle.c",
    "src/vector.c",
    "src/camera.c",
    "src/display.c",
    "src/mesh.c",
    "src/texture.c",
    "src/upng.c",
};
