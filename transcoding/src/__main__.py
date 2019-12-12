import os.path
import shutil

import pkg_resources
from absl import flags, logging

import src.video as video

FLAGS = flags.FLAGS


def verify_installs() -> None:
    """
    Verify the install of both ffprobe and ffmpeg which
    are the two key components needed for the transcoder to operate.
    """

    # Check through all external dependencies
    external_executables = ["ffmpeg", "ffprobe"]
    for dep in external_executables:
        found = shutil.which(dep)
        if not found:
            logging.fatal(
                f"{dep} is required for the installation but couldn't be found."
            )

    logging.info("External dependencies and executables successfully found.")


def verify_input_paths() -> None:
    """
    Verify the paths of the files that were given to the transcoder. More
    specifically in our case, both the path of the video file and output
    directory.
    """
    paths = [FLAGS.video_file, FLAGS.output_dir]

    for path in paths:
        if not os.path.exists(path):
            logging.fatal(f"Couldn't find the path to{FLAGS.video_file}")

    logging.info("Paths of input files successfully found.")


def main(argv):
    """
    Main entry point of the application
    """

    del argv

    verify_installs()
    verify_input_paths()
    config = {}
    config["chunk_duration_seconds"] = FLAGS.chunk_duration_seconds
    config["output_dir"] = FLAGS.output_dir.rstrip("/")
    config["video_file"] = FLAGS.video_file

    video.get_video_length(config)
    video.transcode_video_into_chunks(config)
