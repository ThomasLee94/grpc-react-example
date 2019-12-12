# Terrace video transcoder

## Description
### Overview

- we need to pre-process videos for streaming
- we do not need to productionize this pre-processing right now, it will
exclusively be run internally by Terrace eng.

### Big picture context

TLDR — our current team lacks the expertise to build a productionized
transcoding server in a timely manner. Instead we're building a hacky solution
that meets our current product needs so that we can launch and acquire more
funding to hire dedicated video eng.

In detail —

Our launch requires streaming videos that we (the Terrace team) select. This
means that video uploads will both be infrequent and performed manually in a
controlled environment. AKA we don't need an on-demand / productionized /
performant solution for transcoding. We just need something that can be used on
occasion to upload new content. This wont change until well after launch by
which time we expect to have additional funding to hire dedicated video eng to
build a productionized C++ transcoding service. Hence why this project allows
for deviations from our normal eng practices. The goal is not to build a long
lasting service, but instead to get us through launch so that we can hire the
right people to build a better solution.

For more information about the specs, check out the
[The local transcoder specification](https://www.notion.so/terrace/local-transcoding-tool-31764fae7fbd4b17a6d80f34ac9ad2bf)

## How to run
### With bazel
Inside of this directory, you can run:

```
bazel run :terrace_transcoder
```

Which will then allow you to access the transcoder.

## Documentation
* [src](./src/docs.md)
