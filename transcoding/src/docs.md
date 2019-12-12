# src.__main__

## main
```python
main(argv)
```

Main entry point of the application

# src.video

## get_video_length
```python
get_video_length(options: dict) -> None
```

Get the length of the video. Attaches it to the options dictionary as
"video_length".

Args:
* options - The options dict that contains config that we will need to
            complete the request.

## get_total_frame_count
```python
get_total_frame_count(config: dict) -> None
```

Get the total number of from the video that we're trying to transcode

## transcode_video_into_chunks
```python
transcode_video_into_chunks(config: dict) -> None
```

Transcode an entire video into chunks given the specified
video file, output directory, chunk size, and video length.

Args:
* config - contains configurations that are needed for transcoding the
           input video into our desired output.

# __init__
```python
__init__(*args, **kwargs)
```
Initialize self.  See help(type(self)) for accurate signature.
