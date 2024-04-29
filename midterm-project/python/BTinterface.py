import logging
from typing import Optional

from BT import Bluetooth

log = logging.getLogger(__name__)

# hint: You may design additional functions to execute the input command,
# which will be helpful when debugging :)


class BTInterface:
    def __init__(self, port: Optional[str] = None):
        log.info("Arduino Bluetooth Connect Program.")
        self.bt = Bluetooth()
        if port is None:
            port = input("PC bluetooth port name: ")
        while not self.bt.do_connect(port):
            if port == "quit":
                self.bt.disconnect()
                quit()
            port = input("PC bluetooth port name: ")

    def start(self):
        input("Press enter to start.")
        self.bt.serial_write_string("s")

    def get_UID(self):
        uid_hex = self.bt.serial_read_byte()

        uid_str = str(uid_hex)[2:]  # Remove the '0x' prefix
        uid_str = uid_str.upper()  # Convert to uppercase
        # Pad with zeros to ensure the length is 8 characters
        uid_str = uid_str.zfill(8)
        uid_str = uid_str[:-2]
        return uid_hex

    def send_action(self, dirc: str):
        # TODO : send the action to car
        self.bt.serial_write_string(dirc)
        #self.bt.serial_write_string('\n')

    def end_process(self):
        self.bt.serial_write_string("e")
        self.bt.disconnect()
        
    def read_uid(self):
        uid = self.bt.serial_read_byte()
        if uid:
            print(f"UID received: {uid}")


if __name__ == "__main__":
    test = BTInterface()
    test.start()
    while(True):
          test.read_uid()