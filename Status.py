
from i3pystatus import Status

status = Status()

status.register("clock", format="%a %-d %b %I : %M",)

status.register("temp", format="{temp:.0f}°C",)

status.register("cpu_usage", format=" CPU: {usage:02}%",)

status.register("mem", format="{avail_mem} mb",)

status.register("network", interface="wlan0", format_up="{essid} {quality:03.0f}%",)

status.register("bitcoin", format="{symbol} {status}{last_price}",)

status.run()
