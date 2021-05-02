# Importing Libraries
import serial
import time
import re

_baudrate=115200
_port='/dev/ttyACM1'

_command_re = re.compile('^(Q|CMD|RDY|RCV)(:(.{1,50}))?$')

connection = serial.Serial(port=_port, baudrate=_baudrate, timeout=.5)

class Command:
    command = 'NIL'
    value = ''
    def to_string(self):
        return self.command+':'+self.value


def wait_for_response():
    command = Command()
    line = ''

    while line == '':
        print('Listening...')
        line = connection.readline().decode('utf-8')
    match = _command_re.match(line)

    if match:
        command.command = match.group(1)
        command.value = match.group(3)
    
    return command
            

def send(x):
    connection.write(bytes(x, 'utf-8'))
    response = wait_for_response()
    print('RECEIVED ANSWER > ' + response.to_string())


rdy = False
print('Connecting...')
while not rdy:
    connection.write(bytes('CONN','utf-8'))
    response = wait_for_response()
    if response.command == 'RDY':
        print('Connected : ' + response.value)
        rdy = True

print('\nEnter commands...\n\n')

while True:
    text = input('-> ')
    send(text)
    


# while True:
#     text = input("Enter text: ") # Taking input from user
#     value = write_read(text)
#     print(value) # printing the value