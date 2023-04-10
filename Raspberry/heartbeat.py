import os
import time
import os

from CrossCuttingConcerns import mqtt_adapter, raspi_log


def send_heartbeat():

    raspi_log.log_process(str(f"Heartbeat started! parent id: {os.getppid()},  self id: {os.getpid()}"))
    topic = "heartbeat"
    message = "heartbeat"
    mqtt_adapter.connect("hb")
    while True:
        mqtt_adapter.loop()
        mqtt_adapter.publish(message,topic)
        time.sleep(0.5)  # 5 saniye bekleme
