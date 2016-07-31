
from i3pystatus import Status

status = Status()

status.register("clock",
    format="%a %-d %b %X",)

status.register("temp",
    format="{temp:.0f}°C",)


status.run()
