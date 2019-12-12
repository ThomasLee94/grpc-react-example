from absl import app, flags

from src.__main__ import main

flags.DEFINE_integer(
    "chunk_duration_seconds",
    2,
    "The chunks in seconds the video should be broken up by.",
)

flags.DEFINE_string("video_file", None, "The path to the video file.")

flags.DEFINE_string(
    "output_dir", None, "The output directory for the N chunked videos."
)

flags.mark_flag_as_required("video_file")
flags.mark_flag_as_required("output_dir")


if __name__ == "__main__":
    app.run(main)
