## Ray Tracing in One Weekend

My C99 implementation of [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
by Peter Shirley, Trevor David Black, Steve Hollasch. My implementation uses
tagged unions rather than polymorphism and shared pointers.

![Ray traced image](ray_tracing_in_one_weekend/image.jpg)

## Usage

You can render the scene above as follows:

```sh
cd ray_tracing_in_one_weekend
./scripts/build_release
./build/release/main > image.ppm
open image.ppm
```

The ray tracer is single-threaded so it will take about an hour to render. You
can speed it up by reducing `image_width` or the number of `samples_per_pixel`
in the main function.
