import heartbeat
import mapping

from CrossCuttingConcerns import configure_ip, mqtt_adapter
import multiprocessing
from Sensors import readingQR, obstacle_detection

sub_mode_topic = "mode"
mode = ""


def callback_for_mode(client,userdata,msg):
    global mode
    message = msg.payload.decode('utf-8')
    mode_functions = {
        "explore": run_explore_mode,
        "import": run_import_mode,
        "export": run_export_mode,
        "duty": run_duty_mode,
    }
    if message in mode_functions:
        mode = message
        mode_functions[message]()


def run_explore_mode():
    print("Mapping active")
    try:
        process_mapping.start()
    except AssertionError:
        print("Cannot start a process twitce")


def run_duty_mode():
    print("Duty active")
    process_mapping.terminate()


def run_import_mode():
    try:
        print("importing")
    except AssertionError:
        print("Cannot start a process twitce")


def run_export_mode():
    try:
        print("exporting")
    except AssertionError:
        print("Cannot start a process twitce")


def main():
    global process_mapping
    process_setup = multiprocessing.Process(target=configure_ip.setup_ip())
    process_setup.start()  # setup ip for connecting access point
    process_setup.join()

    mqtt_adapter.connect("mn")

    process_qr = multiprocessing.Process(target=readingQR.main)
    process_heartbit = multiprocessing.Process(target=heartbeat.send_heartbeat)
    process_mapping = multiprocessing.Process(target=mapping.main)
    process_obstacle = multiprocessing.Process(target=obstacle_detection.main)
    process_heartbit.start()
    # process_obstacle.start()
    process_qr.start()

    mqtt_adapter.subscribe(sub_mode_topic, callback_for_mode)
    mqtt_adapter.loop_forever()
    process_qr.join()
    process_heartbit.join()



if __name__ == '__main__':
    main()
