import math
import subprocess

from absl import logging


def get_video_length(options: dict) -> None:
    """
    Get the length of the video in seconds. Attaches it to the options dictionary
    as "video_length".

    Args:
    * options - The options dict that contains config that we will need to
                complete the request.
    """

    video_file = options["video_file"]

    # Get the length of the video
    get_video_len_command = [
        "ffprobe",
        "-v",
        "error",
        "-show_entries",
        "format=duration",
        "-of",
        "default=noprint_wrappers=1:nokey=1",
        "-sexagesimal",
        video_file,
    ]

    # Run the get_video_len_cmd on our input video
    process = subprocess.Popen(
        get_video_len_command,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        universal_newlines=True,
    )

    # Obtain the commands exit status, the videos lenght, and the error string
    # if any occurred.
    exit_status = process.wait()

    # exit code greater than 0 indicates that something went wrong with ffprobe.
    if exit_status:
        err_output = process.stderr.readline()
        logging.fatal(f"ffprobe did not run correctly.\nThe error:\n{err_output}")

    video_length = str(process.stdout.readline()).rstrip("\n")

    logging.info(f"The length of {video_file} is (h:m:s): {video_length}")

    # Obtain the split time
    hours, minutes, seconds = video_length.split(":")

    # Convert all units into seconds
    video_length = float(hours) * 3600 + float(minutes) * 60 + float(seconds)

    # The video length is then converted to it's overall seconds
    options["video_length"] = video_length


def transcode_video_into_chunks(config: dict) -> None:
    """
    Transcode an entire video into chunks given the specified
    video file, output directory, chunk size, and video length.

    Args:
    * config - contains configurations that are needed for transcoding the
               input video into our desired output.
    """

    video_length = config["video_length"]
    chunk_size = config["chunk_duration_seconds"]
    output_dir = config["output_dir"]
    video_file = config["video_file"]

    # Chunk count
    chunk_split_count = int(math.ceil(video_length / chunk_size))

    # Not enough chunks
    if chunk_split_count == 1:
        logging.fatal("Video length is less than the requested chunk size")

    split_command = ["ffmpeg", "-i", video_file, "-vcodec", "libx264"]

    for i in range(0, chunk_split_count):
        seek_start = chunk_size * i
        chunk_to_split = split_command + [
            "-y",  # Overwite files
            "-ss",  # Seek time
            str(seek_start),  # The seek time start
            "-t",  # The duration we'd like to transcode
            str(chunk_size),  # The size of the chunk in seconds
            "-b:v",  # The video bitrate
            "5000000",  # 5,000 kbps -> bps
            "-vf",  # View format
            "scale=1280:720,setdar=3:2",  # Scale it to 1280 x 720
            "-r",  # FPS
            "60",  # 60 fps
            f"{output_dir}/{i}.mp4",  # The output chunk
        ]

        logging.info(f"Processing chunk {i + 1}/{chunk_split_count}")

        # Spawn the transcoding process
        process = subprocess.Popen(
            chunk_to_split,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            universal_newlines=True,
        )

        # Obtain the exit status.
        exit_status = process.wait()

        # exit status
        if exit_status:
            err_output = process.stderr.read()
            logging.fatal("Chunk #{i} couldn't be processed.\nThe error:\n{err_output}")
